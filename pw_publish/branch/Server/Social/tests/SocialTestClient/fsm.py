# -*- coding: utf-8 -*-
import time, traceback, sys, hashlib

from logging import debug, info, warning, error
# -------------------------------------------------------------
# -------------------------------------------------------------

# GetPassedStatus() results
PASSED_STATUS_OK = 1
PASSED_STATUS_FAIL = -1

class SerialFSM(object):

    def __init__(self, fsm, period=1.0):
        self.fsm = fsm
        self.finished = False
        self.nextFsm = None
        self.period = period
        self.lastPassedStatus = 0

    def _RefreshPeriod(self):
        if self.fsm:
            self.fsm.SetPeriod(self.period)

    def SetPeriod(self, period):
        self.period = period
        self._RefreshPeriod()

    def Update(self):
        self.fsm.Update()
        passed_status = self.fsm.GetPassedStatus()
        if self.fsm.finished or passed_status:
            fail_message = self.fsm.GetFailMessage() 
            ##warning( "self.fsm: %s, finished: %s, fail_message: %s, passed_status: %s" % (self.fsm, self.fsm.finished, fail_message, passed_status) )
            if passed_status:
                self.lastPassedStatus = passed_status
            ##warning( "self.fsm.nextFsm: %s" % (self.fsm.nextFsm) )
            if self.fsm.nextFsm:
                self.fsm = self.fsm.nextFsm
                self._RefreshPeriod()
            else:
                self.finished = True

    def __add__(self, other):
        self.nextFsm = other
        return SerialFSM(self)

    def GetFailMessage(self):
        return self.fsm.GetFailMessage()

    def GetPassedStatus(self):
        if self.finished:
            return self.lastPassedStatus
        else:
            return self.fsm.GetPassedStatus()
        
# -------------------------------------------------------------
# -------------------------------------------------------------

class FSM(object):

    def __init__(self, state=None, period=1.0):
        self._SetState(state)
        self.finished = False
        self.nextFsm = None
        self.nextTime = time.clock()
        self.period = period
        self.failMessage = None
        self.passedStatus = 0

    def GetFailMessage(self):
        return self.failMessage

    def GetPassedStatus(self):
        return self.passedStatus
        
    def SetPeriod(self, period):
        self.period = period

    def _SetState(self, state):
        self.state = state

    def Exit(self):
        self.finished = True
        self.isPassed = True

    def Fail(self, message):
        self.failMessage = message
        self.passedStatus = PASSED_STATUS_FAIL
        warning(">>>>>>>>>>>> FAIL: fsm %s, message %s" % (self, message) )
        
    def Pass(self, message=""):
        self.passedStatus = PASSED_STATUS_OK
        warning( "-- PASS: fsm %s %s --" % (self, message) )

    def Update(self):
        currentTime = time.clock()
        if currentTime < self.nextTime:
            return
        self.nextTime = currentTime + self.period        
        try:
            newState = self.state()
            ##info( "fsm %s, newState %s, self state %s" % (self, newState, self.state) )
            if newState:
                self._SetState(newState)    
        except Exception:
            ##warning( "Exception: %s" % (traceback.format_exc()) )
            self.Fail('FSM exception, halted:\n'+traceback.format_exc())

    def __add__(self, other):
        self.nextFsm = other
        return SerialFSM(self)

# -------------------------------------------------------------
# -------------------------------------------------------------


class ContextFSM( FSM ):
    
    def __init__(self, state, context, **kwargs):
        FSM.__init__(self, state, **kwargs)
        self.context = context
        self.context.fsm = self
    
    def Update(self):
        if self.context.failMessage:
            self.Exit()
        else:
            super(ContextFSM, self).Update()
            
    def GetFailMessage(self):
        return self.failMessage or self.context.GetFailMessage()

    def GetPassedStatus(self):
        return self.passedStatus or self.context.GetPassedStatus()

    def Fail(self, message):
        self.failMessage = message
        self.passedStatus = PASSED_STATUS_FAIL
        warning(">>>>>>>>>>>> %s FAIL: fsm %s, message %s" % (self.context.tag, self, message) )
        
    def Pass(self, message=""):
        self.passedStatus = PASSED_STATUS_OK
        warning( "-- %s PASS: fsm %s %s --" % (self.context.tag, self, message) )

# ------------------------------------------------------------------
# ------------------------------------------------------------------

class TimeoutFailFSM( ContextFSM ):
    """ исполняем обычную логику child FSM, но если истечет указанный таймаут, вызываем Fail """
    def __init__(self, state, context, timeoutFail=10.0, **kwargs):
        super(TimeoutFailFSM, self).__init__(state, context, **kwargs)
        self.timeStart = 0
        self.timeoutFail = timeoutFail
    
    def Update(self):
        if not self.timeStart: 
            self.timeStart = time.time() # время начинаем отсчитывать от запуска первого состояния
        super(TimeoutFailFSM, self).Update()
        if time.time() > self.timeStart + self.timeoutFail:
            self.context.Fail("timeout: %s seconds elapsed\n(timeout state: %s)" % (self.timeoutFail, self.state))
