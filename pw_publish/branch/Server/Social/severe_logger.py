# -*- coding: utf-8 -*-

#!/usr/bin/env python
#
# (C) Dan Vorobiev 2013, Nival Network

import sys, os, time, json
import functools

from base.helpers import *
from ihttp import IAsyncHttpFetcher


class PacketedJsonHttpLogHandler( logging.Handler ):
    """ """
    def __init__( self, level=logging.WARNING, max_queue_size=1000, channel_name="", retry_pause=10.0, events_path="pw/logs", service_id="", process_id="" ):
        logging.Handler.__init__(self, level)
        self.queue = []
        self.max_queue_size = max_queue_size
        self.skipped = 0
        self.channel_name = channel_name
        self.service_id = service_id
        self.process_id = process_id
        self.host = socket.gethostname()
        self.retry_pause = retry_pause
        self.next_retry_time = 0
        self.events_path = events_path
        self.log_http_urls = []
        self.HTTP = None
        
    def setHTTP(self, log_http_urls, HTTP):
        self.log_http_urls = log_http_urls
        self.HTTP = IAsyncHttpFetcher( HTTP )
        
    def emit( self, record ):
        # apply formatting to the record.
        msg = self.format(record)
        # looks like pypy Does not have logging.logRecord.processName; this is a hackish workaround.
        if hasattr(record, 'processName'):
            self.process_name = record.processName
        else:
            pn = '<unknown>'
        args = {
            'tm': record.created,       # время создания сообщения
            'datetime': time.strftime("%Y.%m.%d %H:%M:%S", time.gmtime(record.created)), # читабельное время создания сообщения
            'type': record.levelname,   # тип сообщения (error, warning, critical, debug, info)
            'msg': utf8convert(msg),    # текст сообщения в utf8
            'channel': self.channel_name, # канал (?)
            'file': record.pathname,    # полное имя файла, где случился лог
            'line': record.lineno,      # строчка, где случился лог
        }
        self.queue.append( args )
        self.truncate_queue()
        
    def truncate_queue(self):
        l = len(self.queue)
        if l > self.max_queue_size:
            skip_count = l - self.max_queue_size
            self.skipped += skip_count
            self.queue = self.queue[ skip_count: ]
            info("truncate_queue: skipped %s msgs", skip_count)
            return skip_count
        return 0

    def send( self ):
        if self.queue and (time.time() > self.next_retry_time):
            post_args = {
                'host': self.host,
                'sid': self.service_id,
                'pid': self.process_id, 
                'skipped': self.skipped,
            }
            info("PacketedJsonHttpLogHandler.send (len=%s, args=%s)", len(self.queue), post_args)
            
            messages = self.queue[:]
            skipped_count = self.skipped
            
            self.queue = []
            self.skipped = 0
            
            if self.HTTP:
                post_body = json_dumps( messages )
                _callback = functools.partial( self.onSend, messages=messages, skipped_count=skipped_count )
                url = http_prefix( pickRandom(self.log_http_urls) ) # каждую пачку логов отсылаем на произвольный инстанс (если часть из них лежит, сможем проскочить через работающий)
                self.HTTP.post( url, post_args, post_body, _callback, subrequest=self.events_path )
            else:
                warn("No HTTP handler set for PacketedJsonHttpLogHandler, %s messages skipped", len(messages))
            

    def onSend(self, response, messages=[], skipped_count=0):
        info("PacketedJsonHttpLogHandler.onSend response: %s (messages count=%s, skipped_count=%s)", response, len(messages), skipped_count)
        if not response:
            self.next_retry_time = time.time() + self.retry_pause
            # возвращаем события в начало очереди (при этом порядок их может перемешиваться, т.к. отлупы/таймауты на onSend могут приходить в произвольном порядке)
            self.skipped += skipped_count
            self.queue.extend( messages )
            was_skipped = self.truncate_queue()
            info("PacketedJsonHttpLogHandler.onSend: returned %s messages to queue (and %s were skipped); queue len now: %s, total skipped=%s, next_retry_time=%s",
                len(messages), was_skipped, len(self.queue), self.skipped, self.next_retry_time)
        
