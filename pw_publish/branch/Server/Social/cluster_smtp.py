# -*- coding: utf-8 -*-
#
# (C) Dan Vorobiev 2010
#
# async sql queries for Tornado

from base.helpers import *
import threading
import tornado.ioloop
import base64, binascii

import smtplib, socket
from email.mime.text import MIMEText
from email.mime.multipart import MIMEMultipart
from email.utils import formataddr, formatdate

from base.safelock import *

from binascii import crc32   # zlib version is not cross-platform

# ----------------------------------
from cluster_base import IClusterFunctorThreadPool, asyncThreadFunc

##------------------------------------------------------------------------------------------------
class AsyncSmtpManager( IClusterFunctorThreadPool ):
    """ Thread pool и очереди запросов/ответов для общения с SMTP (email transfer). 
        Метод вызова запросов стандартный, наследуем от FunctorThreadPool: query["f"] содержит имя функции, query["a"] -- аргументы (tuple).
    """
    CNAME = "smtp"
    
    # ----------- IClusterThreadPool overridables -----------
    def newConnection(self, threadNum, threadID, options):
        info( "AsyncSmtp thread %d {%d} start: %5.3f", threadNum, threadID, time.time() )

        connection = ClassDict() 
        connection.local_hostname = socket.gethostname()
        connection.threadID = threadID
        return connection, "smtp"
                
    ## ----------------------------------------------------------------------------------------
    def runQuery(self, query, connection):
        info( "smtp runQuery [thread %d]: query %s" % ( connection.threadID, str(query) ) )

        params = query["a"]
        #methodName = query["f"]

        if self.options.smtp_ssl:
            smtp = smtplib.SMTP_SSL( self.options.smtp_host, self.options.smtp_port, connection.local_hostname, timeout=self.options.smtp_timeout )
        else:
            smtp = smtplib.SMTP( self.options.smtp_host, self.options.smtp_port, connection.local_hostname, self.options.smtp_timeout )
        info( "smtp connect: %s" % smtp )

        result = smtp.login( str(self.options.smtp_username), str(self.options.smtp_pwd) )
        info( "smtp.login result: %s" % str(result) )

        toaddr, subj, msgtext, plaintext = params

        ##msg = MIMEText( msgtext, "html", "utf8" )

        # Record the MIME types of both parts - text/plain and text/html.
        msg = MIMEMultipart('alternative')
        part1 = MIMEText(plaintext, 'plain', 'utf8')
        part2 = MIMEText(msgtext, 'html', 'utf8')

        # Attach parts into message container.
        # According to RFC 2046, the last part of a multipart message, in this case
        # the HTML message, is best and preferred.
        msg.attach(part1)
        msg.attach(part2)

        msg['Subject'] = subj
        msg['From'] = formataddr( (self.options.smtp_fromname, self.options.smtp_fromaddr) )
        msg['To'] = toaddr
        msg['Date'] = formatdate( localtime=True )

        sendresult = smtp.sendmail( self.options.smtp_fromaddr, utf8convert(toaddr), msg.as_string() )
        info( "smtp.sendmail result: %s" % sendresult )

        smtp.quit()
        
        # если что-то пойдет не так, smtp.login/sendmail бросят exception, и вернется "r":None, "e":<traceback ошибки>;
        return True # а в случае успеха надо вернуть что-то ненулевое

    ## ----------------------------------------------------------------------------------------
    def __init__(self, options, num_connections=4, syncWait=8.0):
        IClusterFunctorThreadPool.__init__(self, num_connections, syncWait)
        self.options = options
        self.startThreads()

        
