import datetime
import threading

def _do(level, message):
    t = datetime.datetime.now() 
    print '(%d) %s:%d %s: %s' % (threading.currentThread().ident or 0, t.strftime("%H:%M:%S"), t.microsecond/1000, level, message)

def log(message):
    _do('m', message)

def debug(message):
    _do('d', message)

def error(message):
    _do('e', message)

def warning(message):
    _do('w', message)

def critical(message):
    _do('c', message)

def error(message):
    _do('e', message)
