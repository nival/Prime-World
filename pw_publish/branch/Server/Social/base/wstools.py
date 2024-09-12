# -*- coding: utf-8 -*-
__author__ = 'danil.lavrentyuk'
"wstools - some helpers for request processing flow control"
from base.helpers import info, debug, warn, err
from time import time as gettime
from functools import wraps, partial
import tornado.ioloop
import signal

# добавить таймаут через N секунд
def AddLoopCallback(callback, timeout_seconds=1.0):
    loop = tornado.ioloop.IOLoop.instance()
    return loop.add_timeout(gettime() + timeout_seconds, callback)

def RemoveLoopCallback(task):
    tornado.ioloop.IOLoop.instance().remove_timeout(task)

# Decorator to make a methods to add on once timer (ITIMER_REAL) for non-occurrence of blocking alarm in ioloop.
# !!! Use carefully !!!
def IncreaseBlockingAlarm(seconds, interval=0):
    def real_decorator(function):
        def wrapper(*args, **kwargs):
            debug("IncreaseBlockingAlarm [%r] >>> get old timer ", signal.getitimer(signal.ITIMER_REAL))
            signal.setitimer(signal.ITIMER_REAL, seconds, interval)
            debug("IncreaseBlockingAlarm [%r] >>> get new timer ", signal.getitimer(signal.ITIMER_REAL))
            function(*args, **kwargs)
        return wrapper
    return real_decorator

# Decorator to make a methods to suspend it's work waiting for some flag in self.I.WS
# This version is for methods like 'def onStart(self)' -- no args except self
def waitflag(flag_name):
    def flag_wrapper(method):
        @wraps(method)
        def wrapper(self):
            if not getattr(self.I.WS, flag_name, True): # no self.I.WS.ready exists -- no suspendig!
                info("%s.%s isn't ready. Suspended", self.__class__.__name__, method.__name__)
                AddLoopCallback(getattr(self, method.__name__), timeout_seconds = 2.1)
                return
            return method(self)
        return wrapper
    return flag_wrapper

# This version is for methods with any number of args
def waitflag_a(flag_name):
    def flag_wrapper(method):
        @wraps(method)
        def wrapper(self, *args, **kwargs):
            if not getattr(self.I.WS, flag_name, True): # no self.I.WS.ready exists -- no suspendig!
                info("%s.%s isn't ready. Suspended", self.__class__.__name__, method.__name__)
                AddLoopCallback( partial(getattr(self, method.__name__), *args, **kwargs), timeout_seconds = 2.1 )
                return
            return method(self, *args, **kwargs)
        return wrapper
    return flag_wrapper


def checkflag(name='enabled', send_ok=True):
    def flag_wrapper(method):
        @wraps(method)
        def wrapper(self):
            if not getattr(self.I.WS, name, True): # no self.I.WS.enabled exists -- no check!
                info("%s.%s isn't enabled. Do nothing", self.__class__.__name__, method.__name__)
                self.response["ok"] = int(send_ok)
                self.fin()
                return
            return method(self)
        return wrapper
    return flag_wrapper
