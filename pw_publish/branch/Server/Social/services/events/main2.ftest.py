import logging 
import urllib2
import urllib
import socket
import time
import json

def loggingSeverity( name ):
    return getattr( logging, name.upper(), 0) if name else 0

class LogHandler(logging.Handler):

    def __init__(self, url):
        logging.Handler.__init__(self)
        self.url = url

    def emit(self, record):
        msg = self.format(record)
        if not msg.startswith('\n') or msg.endswith('\n'):
          msg += '\n'

        # It looks like pypy Does not have logging.logRecord.processName
        # This is a hackish workaround.
        if hasattr(record, 'processName'):
            pn = record.processName
        else:
            pn = '<unknown>'

        print msg
        print pn, record.__dict__

        params = {
            'host' : socket.gethostname(),
            'sid' : 'sid',
            'pid' : record.process,
            'skipped' : 0
        }
        messages = [
            {
                'msg' : msg,
                'tm' : record.created,
                'type' : record.levelname.lower(),
                'channel' : record.name,
                'file' : record.filename,
                'line' : record.lineno,
            }
        ]
        furl = self.url+'?'+urllib.urlencode(params)
        print furl
        request = urllib2.Request(furl, data=json.dumps(messages, indent=4))  
        reply = urllib2.urlopen(request).read()
        print reply

url = r'http://localhost:88/ev/pw/logs'
#url = r'http://localhost:10007/pw/logs'
handler = LogHandler(url) 
handler.setFormatter( logging.Formatter("(%(thread)d) %(asctime)s %(levelname)s: %(message)s") )
handler.setLevel( loggingSeverity( 'debug' ) )

logger = logging.getLogger()
logger.addHandler(handler)

from logging import error, warning, critical
error ('test')
warning ('test')
critical ('test')
