# -*- coding: utf-8 -*-

import sys, thread, time

MAX_SAFE_LOCK_SECONDS = 10

# ----------------------------------------------------------

class JustLock:
    """ обертка вокруг обычного thread.lock """
    def __init__(self, logFunc):
        self.log = logFunc
        self.lock = thread.allocate_lock()
        #~ if not self.lock:
            #~ self.log("LOCK_WARNING: lock cannot be aquired!")
    
    def acquireSafe(self):
        self.lock.acquire(1)
        
    def releaseSafe(self):
        self.lock.release()
        
    def isLocked(self):
        return self.lock.locked()
        

# ----------------------------------------------------------

class SafeLock:
    """ экспериментальная система веревочек для _надеюсь_более_безопасного_ получения thread.lock """
    def __init__(self, logFunc):
        self.log = logFunc
        self.lockID = 0
        self.lockTime = 0
        self.lock = thread.allocate_lock()
        if not self.lock:
            self.log("ERROR: lock cannot be aquired!")
        
        
    ## экспериментальная система веревочек для _надеюсь_более_безопасного_ получения room lock
    def acquireSafe(self):
        threadID = thread.get_ident()
        
        self.checkStale(threadID) # проверяем, не завис ли замочек; если таки завис - отпускаем
                            
        self.lock.acquire(1)
        self.lockID = threadID
        self.lockTime = time.time()            
        
        
    ## проверяем, не завис ли замочек; если таки завис - отпускаем
    def checkStale(self, threadID=0):
        if self.lock.locked():
            if self.lockID == threadID:
                # упс, мы сами же, похоже, и делали лок; какая-то проблема с непойманным exception-ом и неотпущенным локом
                self.log("LOCK_WARNING: lockID %d == threadID %d" % (self.lockID, threadID) )
                self.lock.release()
            else:
                now = time.time() 
                prev = self.lockTime
                if prev and now - prev > MAX_SAFE_LOCK_SECONDS:
                    self.lockTime = now # чтобы больше никто не мог разлочить параллельно, за время пока пишется лог
                    self.log("LOCK_WARNING: waiting>%d sec: lockID %d, lockTime %d (now %d)" \
                        % (MAX_SAFE_LOCK_SECONDS, self.lockID, prev, now) )
                    self.lock.release()
            
            
    ## экспериментальная система веревочек для отпускания room lock
    def releaseSafe(self):
        self.lockID = 0
        if self.lock.locked():
            self.lock.release()
        
    def isLocked(self):
        return self.lock.locked()
