#!/usr/bin/env python
# -"- coding: utf8 -"- 
# (C) Dmitry Kolb 2014, Nival Network 
__author__ = 'dmitry.kolb'
from functools import partial
from base.helpers import *


MAX_SEMAPHORE_LOCK = 300 # seconds, 5 minutes should be enough for locking operation!

class ServiceLock(object):
    "Multi-process service locking semaphore using mongo db"

    def __init__(self, DB, name, callback=None):
        self.DB = DB
        self.name = name
        DB.find_one("vars", "vars", {'_id': name}, callback=partial(self.onVarCheck, callback=callback))

    def onVarCheck(self, response, callback):
        if response and response.get("r"):
            if callback:
                callback()
            return # already exists
        self.DB.insert("vars", "vars", {'_id': self.name, 'value': 0}, callback=partial(self.dummyCallbck, callback=callback))
        info("ServiceLock '%s' is ready", self.name)

    def dummyCallbck(self, response, callback):
        # no problem if it fails on duplicate key
        if callback:
            callback()

    # Calls the calback with True if the lock acqured of False if the semaphore is busy.
    def tryAcquire(self, callback):
        self.DB.find_and_modify("vars", "vars", {'_id': self.name, 'value': 0}, update={'value': int(time.time())}, new=False,
                                callback=partial(self.onAcquire, callback=callback))

    def onAcquire(self, response, callback):
        now = int(time.time())
        if response and response.get("r"):
            flag = response["r"]
            if flag['value'] and (now - flag['value'] > MAX_SEMAPHORE_LOCK):
                warn("Overriding stale (%s seconds) semaphore '%s'", now - flag['value'], self.name)
                self.DB.update("vars", "vars", {'_id': self.name}, {'value': now})
                callback(True)
            else:
                callback(not flag['value'])
        else:
            msg = (response.get('ex') or ('result = %s' % response.get("r"))) if response else 'EMPTY response'
            err("Locking '%s' fails: %s", self.name, msg)
            callback(False)

    def release(self):
        self.DB.update("vars", "vars", {'_id': self.name}, {'value': 0})

    def removeVar(self):
        self.DB.remove('vars', 'vars', {"_id":  self.name})
