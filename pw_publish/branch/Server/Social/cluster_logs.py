# -*- coding: utf-8 -*-
#
# (C) Svetlana Torikova 2010
#
# async log send queries for Tornado

#FIXME: судя по всему, это уже не используется?
# Ссылки на этот модуль есть только в закомментированном коде.

import os, sys, time, logging, socket, shelve

from base.helpers import *

# ----------------------------------
from cluster_base import crc_hash, IClusterThreadPool, asyncThreadFunc

from tools.scribe import scribe

from thrift.transport import TTransport, TSocket, THttpClient
from thrift.transport.TTransport import TTransportException
from thrift.protocol import TBinaryProtocol

class ScribeLogError(Exception): pass
class ScribeTransportError(Exception): pass
class ScribeHandlerBufferError(Exception): pass

class LogSender(object):

    def __init__(self, options, file_buffer=None):
        self.options = options

        self.__buffer = None
        self.file_buffer=file_buffer

        transport = options.log_scribe_transport

        if transport == 'none':
            self.transport = None
            self.client = None
            return

        if transport == 'http':
            if options.log_scribe_uri is None:
                raise ScribeLogError('http transport with no uri')
            self.transport = THttpClient.THttpClient(options.log_scribe_host, options.log_scribe_port, options.log_scribe_uri)
        else:
            socket = TSocket.TSocket(host=options.log_scribe_host, port=options.log_scribe_port)

            if transport == 'framed':
                self.transport = TTransport.TFramedTransport(socket)
            elif transport == 'unframed':
                self.transport = TTransport.TBufferedTransport(socket)
            else:
                raise ScribeLogError('Unsupported transport type')

    def _get_buffer(self):
        if self.file_buffer is None:
            raise ScribeHandlerBufferError('No buffer file defined')

        try:
            self.__buffer.keys()
        except AttributeError:
            self.__buffer = None
        except ValueError:
            self.__buffer = None

        if self.__buffer is None:
            self.__buffer = shelve.open(self.file_buffer)

        return self.__buffer

    def _make_client(self):
        protocol = TBinaryProtocol.TBinaryProtocol(trans=self.transport,
            strictRead=False, strictWrite=False)
        self.client = scribe.Client(protocol)

    def __setattr__(self, var, val):
        ## Filterer is an old style class through at least 3.1
        self.__dict__[var] = val

        if var == 'transport':
            self._make_client()

    def get_entries(self, new):
        if self.file_buffer is not None:
            self._get_buffer()
        else:
            yield (None,new)
            return

        self.add_entry(new)

        sortedkeys = self.__buffer.keys()
        sortedkeys.sort()

        for k in sortedkeys:
            yield (k,self.__buffer[k])

        self.__buffer.close()

    def pop_entry(self, key):
        if self.file_buffer is None:
            return
        ## buffer should already be open
        self.__buffer.pop(key)
        self.__buffer.sync()

    def add_entry(self, new):
        if self.file_buffer is None:
            return

        self._get_buffer()

        try:
            topkey = max(self.__buffer.keys())
        except ValueError:
            topkey = -1

        newkey = '%s' % (int(topkey) + 1)
        self.__buffer[newkey] = new
        self.__buffer.sync()

    def sendLogs(self, logs):
        try:
            count = len(logs['m'])
            self.transport.open()
        except TTransportException:
            for entry in logs['m']:
                category, message = entry['m']
                log_entry = scribe.LogEntry(category=category, message=message)
                self.add_entry(log_entry)
        else:
            try:
                for entry in logs['m']:
                    category, message = entry['m']
                    log_entry = scribe.LogEntry(category=category, message=message)
                    for le in self.get_entries(log_entry):
                        result = self.client.Log(messages=[le[1]])
                        if result != scribe.ResultCode.OK:
                            raise ScribeLogError(result)
                        self.pop_entry(le[0])
                self.transport.close()
            except TTransportException:
                if self.file_buffer is not None:
                    self.add_entry(log_entry)
                self._do_error(count)
            except Exception, e:
                sys.stderr.write(str(e))

    def _do_error(self, count):
        if self.file_buffer is not None:
            self.__buffer.sync()
            self.__buffer.close()
        else:
            pass # if no file_buffer defined then messages just disappering

    def close(self):
        pass

class LogHandler(logging.Handler):

    def __init__(self, processor, category=None):
        self.processor = processor

        if category is None:
            self.category = '%(hostname)s-%(loggername)s'
        else:
            self.category = category
        logging.Handler.__init__(self)

    def emit(self, record):
        """
        Emit a record.

        If a formatter is specified, it is used to format the record.
        The record is then logged to Scribe with a trailing newline.
        """
        # apply formatting to the record.
        msg = self.format(record)
        # for backwards-compatibility, do not add in a line break if it
        # is already being manually added into each record.
        if not msg.startswith('\n') or msg.endswith('\n'):
          msg += '\n'

        # It looks like pypy Does not have logging.logRecord.processName
        # This is a hackish workaround.
        if hasattr(record, 'processName'):
            pn = record.processName
        else:
            pn = '<unknown>'

        category = self.category % {
            'module' : record.module,
            'levelname': record.levelname,
            'loggername' : record.name,
            'processName' : pn,
            'hostname' : socket.gethostname(),
        }
        self.processor.addLog(category=category, message=msg)

## ----------------------------------------------------------------------------------------
class AsyncLogsManager( IClusterThreadPool ):
    """ thread pool и очереди отсылки логов """
    CNAME = "logs"

    def newConnection(self, threadNum, threadID, options):
        #assert(False)
        info( "Async logs thread %s.%d {%d} start: %5.3f (host %s:%d)" % ('LogSender', threadNum, threadID, time.time(), options.log_scribe_host, options.log_scribe_port) )
        scribe_log_prefix = options.log_file_prefix or 'logs/log' # не надо чтобы по умолчанию scribe логи валились в корень
        return LogSender(options, file_buffer = scribe_log_prefix + "._scribeLogBuffer"), options.log_scribe_host

    def closeConnection(self, connection):
        if connection:
            connection.close()

    ## ----------------------------------------------------------------------------------------
    def __init__(self, options, num_connections=1, syncWait=20.0):
        IClusterThreadPool.__init__(self, num_connections, syncWait)

        self.options = options

        self.startThreads()

    #~ def __del__(self):
        #~ info( "~AsyncLogsManager " + str(self) )


    ## -------------------------------------------------------------------------------------
    ## добавляем в очередь новое сообщение
    def addLog(self, category, message):
        self.conditionQueries.acquire()

        query = { "m":(category, message), "tq":time.time(), 'cb' : self.onReply }

        self.queries.append( query )

        self.conditionQueries.notify()
        self.conditionQueries.release()
        
    def onReply(self, reply):
        if 'e' in reply and reply['e']:
            sys.stderr.write(reply['e'])

    def popQuery(self):
        query = None
        self.conditionQueries.acquire()

        if not len(self.queries):
            self.conditionQueries.wait()

        if len(self.queries):
            query = { 'm' : self.queries, 'tq' : self.queries[0]['tq'], 'cb' : self.onReply }    # берем все накопившиеся сообщения чтобы не отсылать поодиночке
            self.queries = []

        self.conditionQueries.release()
        return query

    ## ----------- OVERRIDE (IClusterThreadPool) --------------
    def runQuery(self, query, connection):
        connection.sendLogs(query)
        return {'cb' : self.onReply }
