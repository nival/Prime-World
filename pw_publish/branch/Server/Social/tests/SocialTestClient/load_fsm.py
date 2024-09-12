# -*- coding: utf-8 -*-
import time, os, hashlib
import fsm
import transport 
import context

#from logs import log
import logging, datetime
from logging import debug, info

from main_fsm import * 
from fsm import ContextFSM, TimeoutFailFSM

# ------------------------------------------------------------------
# ------------------------------------------------------------------

class Cyclic_LoginLogoutFSM( LoginHashFSM ):
    """ вместо того чтобы радостно выйти, зацикливаем процесс: авторизовались? пора на logout! """
    def WaitAuth(self):
        if self.context.loaded:
            return self.Logout()

    def Logout(self):
        debug("Cyclic_LoginLogoutFSM Logout")
        self.context.Logout()
        self.SetPeriod( 3.0 ) # после logout подождем подольше, пока сервер прибьет контекст юзера
        return self.WaitLogout

    def WaitLogout(self):
        debug("Cyclic_LoginLogoutFSM WaitLogout")
        if not self.context.uid:
            debug("Cyclic_LoginLogoutFSM WaitLogout 2")
            self.SetPeriod( 0.5 ) # больше не ждем подолгу
            return self.Login()


# ------------------------------------------------------------------
# ------------------------------------------------------------------

class IncSaveCounterFSM( TimeoutFailFSM ):
    """ выполняем inc_save """
    def __init__(self, context, run_count=1, **kwargs):
        super(IncSaveCounterFSM, self).__init__(self.IncSave, context, **kwargs)
        self.tag = self.context.tag
        self.run_count = run_count
        info("IncSaveCounterFSM.__init__: tag %s, run_count %d" % (self.tag, self.run_count))
        
    def IncSave(self):
        info("%s IncSaveCounterFSM.IncSave" % (self.tag))
        self.context.IncSave()
        return self.WaitForReply
        
    def WaitForReply(self):
        if self.context.inc_save_ok:
            info("%s inc_save_counter: %s" % (self.tag, self.context.inc_save_counter) )

            self.run_count -= 1
            if self.run_count > 0:
                return self.IncSave
                
            self.Pass()
            return self.Exit()
            
        info("%s IncSaveCounterFSM.WaitForReply" % (self.tag))


# ------------------------------------------------------------------
# ------------------------------------------------------------------

class CheckAuthFSM( TimeoutFailFSM ):
    """ дожидаемся auth """
    def __init__(self, context, **kwargs):
        info("CheckAuthFSM.__init__")
        super(CheckAuthFSM, self).__init__(self.Auth, context, **kwargs)
        self.tag = self.context.tag
        
    def Auth(self):
        warning("%s Auth" % (self.tag))
        self.context.loaded = 0
        self.context.Auth()
        return self.WaitForAuth
        
    def WaitForAuth(self):
        if self.context.loaded:
            self.Pass()
            return self.Exit()
            
        info("%s CheckAuthFSM.WaitForAuth" % (self.tag))
        
        
# ------------------------------------------------------------------
# ------------------------------------------------------------------

class CheckAuthAndFractionFSM( TimeoutFailFSM ):
    """ делаем auth, проверяем совпадение save_counter """
    def __init__(self, context, fraction='A', **kwargs):
        info("CheckAuthAndFractionFSM.__init__")
        super(CheckAuthAndFractionFSM, self).__init__(self.Auth, context, **kwargs)
        self.tag = self.context.tag
        self.fraction = fraction
        
    def Auth(self):
        warning("%s Auth" % (self.tag))
        self.context.loaded = 0
        self.context.Auth()
        return self.WaitForAuth
        
    def WaitForAuth(self):
        if self.context.loaded:
            # если у нас нет фракции, давайте установим
            if self.context.db.fraction == 'N':
                return self.SetFraction
                
            self.Pass()
            return self.Exit()
            
        info("%s CheckAuthAndFractionFSM.WaitForAuth" % (self.tag))

    # кстати, если у нас нет фракции, давайте установим
    def SetFraction(self):
        warning("%s SetFraction" % (self.tag))
        assert self.fraction
        self.context.db.fraction = 'N'
        self.context.SetFraction(self.fraction)
        return self.WaitFraction

    def WaitFraction(self):
        if self.context.db and self.context.db.fraction != 'N':
            self.Pass()
            return self.Exit()
            
        info("%s CheckAuthAndFractionFSM.WaitFraction" % (self.tag))

# ------------------------------------------------------------------
# ------------------------------------------------------------------

class CheckSaveCounterFSM( CheckAuthAndFractionFSM ):
    """ отличается только проверкой на совпадение save_counter """
        
    def WaitForAuth(self):
        if self.context.loaded:
            warning("%s db.save_counter: %s" % (self.tag, self.context.db.save_counter) )
            if self.context.db.save_counter == self.context.inc_save_counter:
                
                # кстати, если у нас нет фракции, давайте установим
                if self.context.db.fraction == 'N':
                    return self.SetFraction
                    
                self.Pass()
            else:
                self.context.Fail( "bad save_counter! db: %s, inc_save: %s" % (self.context.db.save_counter, self.context.inc_save_counter) )
            
            return self.Exit()
            
        info("%s CheckSaveCounterFSM.WaitForAuth" % (self.tag))
        

# ------------------------------------------------------------------
# ------------------------------------------------------------------

class PersistentGuestLoginFSM( TimeoutFailFSM ):
    """ заходим как persistent guest, авторизуемся, делаем set_fraction """
    def __init__(self, context, **kwargs):
        info("PersistentGuestLoginFSM.__init__")
        super(PersistentGuestLoginFSM, self).__init__(self.Login, context, **kwargs)
        self.tag = self.context.tag
        
    def Login(self):
        info("%s PersistentGuestLogin" % (self.tag))
        self.context.PersistentGuestLogin()
        return self.WaitLogin
        
    def WaitLogin(self):
        if self.context.uid:
            warning("%s logged in: uid %s" % (self.tag, self.context.uid))
            self.context.guest_uid = self.context.uid
            self.Pass()
            return self.Exit()



# ------------------------------------------------------------------
# ------------------------------------------------------------------

class DoKeepaliveCountFSM( ContextFSM ):
    """ выполняем keepalive, пока run_count не треснет """
    def __init__(self, context, run_count=1, keepalive_period=5.0, keepalive_timeout=5.0, **kwargs):
        super(DoKeepaliveCountFSM, self).__init__(self.Keepalive, context, **kwargs)
        self.tag = self.context.tag
        self.run_count = run_count
        self.keepalive_period = keepalive_period
        self.keepalive_timeout = keepalive_timeout
        info("DoKeepaliveCountFSM.__init__: tag %s, run_count %d, keepalive_period %5.3f seconds" % (self.tag, self.run_count, self.keepalive_period))
        
    def Keepalive(self):
        warning( "%s Keepalive [%d run(s) left]" % (self.tag, self.run_count) )
        self.ts = time.time()
        self.context.Keepalive()
        self.SetPeriod( self.keepalive_period ) # вызывать наш Update теперь можно пореже
        return self.WaitForKeepalive
        
    def WaitForKeepalive(self):
        if self.context.keepalive_ok:
            self.run_count -= 1
            if self.run_count > 0:
                return self.Keepalive()
                
            self.Pass()
            return self.Exit()
            
        if time.time() > self.ts + self.keepalive_timeout:
            self.context.Fail( "keepalive timeout (%s seconds)" % (self.keepalive_timeout) )
            return self.Exit()
            
        info("%s WaitForKeepalive" % (self.tag))

