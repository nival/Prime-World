# -*- coding: utf-8 -*-

#!/usr/bin/env python
#
# (C) Dan Vorobiev 2011, Nival Network

import sys, os, time, logging
import functools

# чтобы питон правильно понимал относительные пути модулей:
def _addPath(strPath):
    importPath = os.path.abspath(strPath)
    if not (importPath in sys.path):
        sys.path.append(importPath)

_addPath('cfg')
import cfg

from base.helpers import *

_addPath('tornado')
import tornado.ioloop
import tornado.options

def AsyncSMTP():
    return tornado.ioloop.IOLoop.instance().smtp
    
WS_MAX_SMTP_THREADS = 4

# ------------------------------------------------------
class ISmtp(object):
    """ абстрактный """
    def __init__(self):
        pass
        
    # отправить email msg адресату
    def sendMail(self, *args, **kwargs):
        pass
        
    
# ------------------------------------------------------
class IDummySmtp:
    """ вместо отправки email пишет сообщения в текстовый файл """
    
    def __init__(self, dumpfilename="logs/SMTP.out.txt"):
        self.dumpfile = open(dumpfilename, "wt")
        
    # отправить email msg адресату
    def sendMail(self, toaddr, subj, msg, plain_text_msg="", auid=None, callback=None):
        self.dumpfile.write( "[%s] SENDMAIL (auid=%s)\nTO:%r\nSUBJ:%r\nMSG:%r\n\n" % (time.ctime(), auid, toaddr, subj, msg) )
        self.dumpfile.flush()
        

# ------------------------------------------------------
class IRealSmtp:
    """ пытается реально отправить по SMTP """
    
    # отправить email msg адресату
    def sendMail(self, toaddr, subj, msg, plain_text_msg="", auid=None, callback=None):
        AsyncSMTP().addQuery( "sendmail", (toaddr, subj, msg, plain_text_msg), callback )

