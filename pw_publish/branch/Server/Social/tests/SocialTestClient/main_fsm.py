# -*- coding: utf-8 -*-
import sys, time, os, hashlib
import subprocess
import fsm
import transport 
import context

#from logs import log
import logging, datetime
from logging import debug, info, warning, error

sys.path.append('../../')
from base.helpers import *

# ------------------------------------------------------------------
# ------------------------------------------------------------------

class LogoutFSM(fsm.ContextFSM):

    def __init__(self, context):
        super(LogoutFSM, self).__init__(self.Logout, context)
        
    def Logout(self):
        self.context.Logout()
        return self.WaitLogout

    def WaitLogout(self):
        if not self.context.uid:
            self.Exit()

# ------------------------------------------------------------------
# ------------------------------------------------------------------

class EmptyFSM(fsm.ContextFSM):
    """ чисто для тестирования порядка исполнения FSM """
    def __init__(self, context):
        super(EmptyFSM, self).__init__(self.DoExit, context)
        
    def DoExit(self):
        self.Exit()
        
# ------------------------------------------------------------------
# ------------------------------------------------------------------

class LoginFSM(fsm.ContextFSM):

    def __init__(self, context, user, password, loginType='zzima'):
        super(LoginFSM, self).__init__(self.Login, context)
        self.user = user
        self.password = password
        self.loginType = loginType
        assert type(loginType) != bool

    def Login(self):
        pwd = self.password
        if self.password and self.loginType != 'fb':
            pwd = hashlib.md5(self.password).hexdigest()
        
        self.context.Login(self.user, pwd, self.loginType)
        return self.WaitLogin

    def WaitLogin(self):
        if self.context.uid:
            return self.Auth

    def Auth(self):
        info("%s LoginFSM.Auth" % (self.context.tag))
        self.context.Auth()
        return self.WaitAuth

    def WaitAuth(self):
        if self.context.loaded:
            self.Exit()

# ------------------------------------------------------------------

class LoginHashFSM(LoginFSM):
    """ нам передают не password, а сразу md5(pwd).hexdigest() """
    def Login(self):
        self.context.Login(self.user, self.password, self.loginType)
        return self.WaitLogin

# ------------------------------------------------------------------
# ------------------------------------------------------------------

class StartClientFSM( fsm.ContextFSM ):

    def __init__(self, context, path, exeName, **kwargs):
        super(StartClientFSM, self).__init__(self.Start, context, **kwargs)
        self.path = os.path.abspath(path)
        self.exeName = exeName

    def Start(self):
        if self.context.mm.sessionId:
            cwd = os.getcwd()
            args = [
                self.exeName,
                '-session_login',
                self.context.mm.sessionId,
            ]
            os.chdir(self.path)
            
            args_string = '%s -session_login %s' % (self.exeName, self.context.mm.sessionId)
            warning( "starting subprocess: %s" % args_string )
            
            self.context.pvx_process = subprocess.Popen(args_string)  ## self.context.pvx_process_id = os.spawnv(os.P_NOWAIT, self.exeName, args) 
            os.chdir(cwd)
            
        else:
            warning( "skipping StartClientFSM: no mm.sessionId" )            
        return self.AfterStart()

    # OVERRIDABLE
    def AfterStart(self):
        self.Pass()
        self.Exit()
        

# ------------------------------------------------------------------
# ------------------------------------------------------------------

class TerminateClientFSM( fsm.ContextFSM ):
    """ делаем kill процесса pvx client """
    def __init__(self, context, **kwargs):
        super(TerminateClientFSM, self).__init__(self.TerminateProcess, context, **kwargs)
        
    def TerminateProcess(self):
        if self.context.pvx_process:
            info( "TerminateProcess %s" % str(self.context.pvx_process) )
            self.context.pvx_process.terminate()
        self.Exit()

# ------------------------------------------------------------------
# ------------------------------------------------------------------

class StartClientAndLeaveFSM(StartClientFSM):
    def AfterStart(self):
        self.allowRunTimer = 10
        return self.WaitRun
    
    def WaitRun(self):
        info( "WaitRun %s, mmid %s" % (self.allowRunTimer, self.context.mm.mmid) )
        if (self.context.mm.progress == 104) or (self.allowRunTimer <= 0):
            self.context.pvx_process.terminate()
            return self.WaitForDrop
        else:
            self.allowRunTimer -= 1
            self.context.PingMM()
            
    def WaitForDrop(self):
        info( "WaitForDrop %s" % self.context.mm.mmid )
        if self.context.mm.progress == 102:
            warning( "FAIL: PW_GAME did not launch!" )
            self.context.Fail("PW_GAME did not launch")
            self.Exit()
        elif self.context.mm.progress == 106:
            return self.WaitForExit()
        elif self.context.mm.progress != 107:
            self.context.PingMM()
        else:
            return self.LeaveGame
            
    def LeaveGame(self):
        info( "LeaveGame %s" % self.context.mm.mmid )
        self.context.LeaveMM()
        return self.WaitForExit
        
    def WaitForExit(self):
        if self.context.mm.progress == 106:
            print "SUCCESS: GAME FINISHED! -> exit"
            self.Pass()
            return self.Exit()
        elif self.context.mm.mmid:
            self.context.PingMM()
        else:
            return self.Exit()
        

# ------------------------------------------------------------------
# ------------------------------------------------------------------


# этот вариант запускает не игровой, а нагрузочный pvx клиент.
#  строчки SessionKey ему нужно подкладывать в файлики
class StartGameTestClientFSM( fsm.ContextFSM ):
    """ умеет добавлять файловый ключик для GTC; при указанном spawnGTC=0 поднимает процесс GTC из указанного exeName """
    isGameTestClientSpawned = 0
    processGTC = 0
    
    def __init__(self, context, key_dir_path, path, exeName, spawnGTC=0, scenario_duration=60):
        super(StartGameTestClientFSM, self).__init__(self.Start, context)
        self.path = os.path.abspath(path)
        self.key_path = os.path.abspath(key_dir_path)
        self.exeName = exeName
        self.spawnGTC = spawnGTC
        self.scenario_duration = scenario_duration
        
    def Start(self):
        self.WriteSessionKeyFile()               
        
        ## если нагрузочный клиент еще не запущен, запускаем?..
        global isGameTestClientSpawned
        if self.spawnGTC and (not StartGameTestClientFSM.isGameTestClientSpawned):
            try:
                cwd = os.getcwd()
                os.chdir(self.path)
                args_string = '%s -l localhost:35001 --scenario loadsocial -m 10 --socpickupdir %s --scenarioduration %s >soc_server_GTC.log' \
                    % (self.exeName, self.key_path, self.scenario_duration)
                warning( "starting subprocess: %s" % args_string )
                
                StartGameTestClientFSM.processGTC = subprocess.Popen(args_string)  ## self.context.pvx_process_id = os.spawnv(os.P_NOWAIT, self.exeName, args) 
                os.chdir(cwd)
                StartGameTestClientFSM.isGameTestClientSpawned = 1
            except:
                self.context.Fail( "CAN'T SPAWN GameTestClient process: exeName=%r" % self.exeName )
                return self.Exit()

        ## return self.WriteSessionKeyFile()               

    def WriteSessionKeyFile(self):
        ## подкладываем SessionKey в новый текстовый файлик, в указанной клиентской директории
        session_key = self.context.mm.sessionId
        session_file_name = self.key_path + "/" + self.context.mm.sessionId.replace("/", ".").replace(":", ".") + ".pw.sess.key"
        session_key_file = open( session_file_name + ".~", "w+b", len(session_key) )
        if session_key_file:
            session_key_file.write( session_key )
            session_key_file.close()
            # убираем временное расширение (с этого момента нагрузочный клиент может подчитывать файл)
            try:
                os.rename( session_file_name + ".~", session_file_name )
                self.Pass()
            except:
                self.context.Fail( "CAN'T RENAME session key file to %r" % session_file_name )
        else:
            self.context.Fail( "CAN'T CREATE session key file %r" % (session_file_name + ".~") )

        self.Exit()
        
    @staticmethod
    def KillGTC():
        if StartGameTestClientFSM.processGTC:
            warning( "TerminateProcess %s" % str(StartGameTestClientFSM.processGTC) )
            StartGameTestClientFSM.processGTC.terminate()

# ------------------------------------------------------------------
# ------------------------------------------------------------------

class MatchmakingFSM( fsm.TimeoutFailFSM ): 

    def __init__(self, context, hero, fraction, gameType, cancelCount=0, timeoutFail=20.0):
        super(MatchmakingFSM, self).__init__(self.Check, context, timeoutFail)
        self.hero = hero
        self.fraction = fraction
        self.gameType = gameType
        self.cancelCount = cancelCount

    def Check(self):
        if self.context.db.fraction != 'N':
            # загрузились нормально (есть сохранение)
            if not self.context.mmid:
                # нет текущей мм-сессии, можно заводить новую
                return self.AddMM
            else:
                # есть текущая мм-сессия, придется сбросить
                print "have old mm-session (%s), CANCELING" % self.context.mmid
                self.cancelCount += 1
                return self.CancelMatchmaking()
        else:
            # нету фракции, нужно заново
            return self.SetFraction    
        
        ##DAN: после уборки костылей: после логина нам могут вернуться старые mm-сессии; желательно всегда делать set_fraction, чтобы заресетить их
        ##return self.SetFraction
        
    def SetFraction(self):
        assert self.fraction
        self.context.SetFraction(self.fraction)
        return self.WaitFraction

    def WaitFraction(self):
        if self.context.db and self.context.db.fraction:
            return self.AddMM

    def AddMM(self):
        self.context.AddMM(self.hero, self.fraction, self.gameType)
        return self.WaitMM

    def WaitMM(self):
        if not self.context.mm:
            self.context.PingMM()
        else:
            return self.WaitForPending        

    def WaitForPending(self):
        if self.context.mm.progress < 50:
            self.context.PingMM()
        else:
            return self.WaitForMatchmakingSuccess        
            
    def CancelMatchmaking(self):
        self.cancelCount -= 1
        print "CANCELING session", self.context.mm.mmid
        self.context.CancelMM()
        return self.AddMM

    def WaitForMatchmakingSuccess(self):
        if self.context.mm.progress == 100:
            if self.cancelCount <= 0:
                print "Accepting game %s session %s" % (self.context.mm.gameId, self.context.mm.mmid)
                self.context.AcceptMM()
                self.context.mm.progress = 103 # поскольку FSM работает по тикам, а не по ответам сервера, делаем себе как бы prediction
                return self.WaitForSession
            else:
                return self.CancelMatchmaking()
        elif self.context.mm.progress == 102: #in some cases server can auto-accept and skip phase "100"
            print "Matchmaking succeeded (WITHOUT accept) with session", self.context.mm.sessionId
            self.Exit()
        else: # self.context.mm.progress != 100
            self.context.PingMM()
            

    def WaitForSession(self):
        if self.context.mm.progress == 100:
            # сессия распалась, возвращаемся в состояние "ждем когда смейкают"
            print "Matchmaking session fell apart, accepting again:", self.context.mm.mmid
            return self.WaitForMatchmakingSuccess
        elif self.context.mm.progress != 102:
            self.context.PingMM()
        else:
            print "Matchmaking succeeded with session", self.context.mm.sessionId
            self.Pass()
            self.Exit()
            
# ------------------------------------------------------------------
# ------------------------------------------------------------------

class MatchmakingAddAcceptCancelFSM( MatchmakingFSM ): 
    """ отличается тем, что после Cancel не пытается мейкаться заново, а сразу выходит """
    def CancelMatchmaking(self):
        print "CANCELING session", self.context.mm.mmid
        self.context.CancelMM()
        self.Exit()

# ------------------------------------------------------------------
# ------------------------------------------------------------------

class ReloginFSM( fsm.TimeoutFailFSM ):
    """ при релогине используем параметры, уже прописанные в user контексте (uid, key, mmid..)  """
    def __init__(self, context, timeoutFail=3.0):
        super(ReloginFSM, self).__init__(self.Relogin, context, timeoutFail)

    def Relogin(self):
        self.context.auid = 0 # сбрасываем, чтобы ждать auid как признак успешного Relogin
        self.context.worker = None # якобы мы unlogged

        if self.context.uid and self.context.key:
            warning( "%s Relogin..." % self.context.tag )
            username = "guest:%d" % self.context.uid
            pwd = self.context.key
            self.context.Login(username, pwd, 'guest_relogin')
            return self.WaitForRelogin
        else:
            self.Fail("no uid/key info in context")
            self.Exit()
            
    def WaitForRelogin(self):
        if self.context.auid:
            warning( "%s Relogin OK" % self.context.tag )
            self.Pass()
            self.Exit()
        info( "%s WaitForRelogin" % self.context.tag )
    
# ------------------------------------------------------------------
# ------------------------------------------------------------------

class MatchmakingAddAcceptFSM( MatchmakingFSM ): 
    """ сразу стартуем MM, без проверки фракции; отваливаемся после Accept """
    def Check(self):
        return self.AddMM()

# ------------------------------------------------------------------
# ------------------------------------------------------------------

class MatchmakingContextHeroAddAcceptFSM( MatchmakingAddAcceptFSM ): 
    """ отличается тем, что берет героя из context -- предварительно его нужно там поставить, например через ChooseIndexedHeroFSM """
    def AddMM(self):
        self.hero = self.context.hero
        return super(MatchmakingContextHeroAddAcceptFSM, self).AddMM()

# ------------------------------------------------------------------
# ------------------------------------------------------------------

class ChooseIndexedHeroFSM( fsm.ContextFSM ): 
    """ выбирает N-ного по списку героя из ModelData, и ставит context.hero -- индекс N нужно ставить через context.SetHeroIndex() """
    def __init__(self, context, hero_index):
        super(ChooseIndexedHeroFSM, self).__init__(self.ChooseContextHero, context)
        self.context.hero_index = hero_index

    def ChooseContextHero(self):
        if self.context.model:
            hk = pathFind(self.context.model, "ModelData/HeroesKeeper/Keeper")
            hero_id = hk.keys()[ self.context.hero_index % len(hk.keys()) ]
            hero_class = hk[hero_id]["Hero"]["class_name"]
            info("%s ChooseContextHero: chosen hero_id %s (%r)" % (self.context.tag, hero_id, hero_class))
            self.context.hero = hero_id
            self.Pass()
        else:
            self.context.Fail("can't choose hero")
        self.Exit()

# ------------------------------------------------------------------
# ------------------------------------------------------------------

class MakeGuardContextHeroFSM( fsm.TimeoutFailFSM ): 
    """ юзаем читовые debug actions, чтобы сделать героя context.hero гвардейским """
    def __init__(self, context, guard=True, win_count=100, timeoutFail=5.0):
        super(MakeGuardContextHeroFSM, self).__init__(self.SetGuard, context, timeoutFail)
        self.win_count = win_count
        self.guard = guard
    
    def SetGuard(self):
        info( "%s SetGuard..." % self.context.tag )
        self.context.SetGuard(self.context.hero, self.guard)
        return self.WaitForGuard
        
    def WaitForGuard(self):
        if self.context.set_guard_ok:
            info( "%s WaitForGuard OK" % self.context.tag )
            return self.SetLordWins()
        info( "%s WaitForGuard" % self.context.tag )
    
    def SetLordWins(self):
        info( "%s SetLordWins..." % self.context.tag )
        self.context.SetLordWins( self.win_count )
        return self.WaitForLordWins
        
    def WaitForLordWins(self):
        if self.context.lord_wins_ok:
            info( "%s WaitForLordWins OK" % self.context.tag )
            self.Pass()
            self.Exit()
        info( "%s WaitForLordWins" % self.context.tag )
        
# ------------------------------------------------------------------
# ------------------------------------------------------------------
    
class ReconnectFSM( fsm.TimeoutFailFSM ):
    def __init__(self, context, timeoutFail=2.0):
        super(ReconnectFSM, self).__init__(self.Reconnect, context, timeoutFail)
        
    def Reconnect(self):
        warning( "%s Reconnect..." % self.context.tag )
        self.context.ReconnectMM()
        return self.WaitForReconnect

    def WaitForReconnect(self):
        if self.context.mm_reconnect_ok:
            warning( "%s Reconnected ok" % self.context.tag )
            self.Pass()
            self.Exit()
        info( "%s WaitForReconnect" % self.context.tag )

# ------------------------------------------------------------------
# ------------------------------------------------------------------
    
class LeaveSessionFSM( fsm.TimeoutFailFSM ):
    def __init__(self, context, timeoutFail=2.0):
        super(LeaveSessionFSM, self).__init__(self.MmLeave, context, timeoutFail)
        
    def MmLeave(self):
        warning( "%s MM_Leave..." % self.context.tag )
        self.context.LeaveMM()
        return self.WaitForLeave

    def WaitForLeave(self):
        if self.context.mm_leave_ok:
            warning( "%s mm_leave ok" % self.context.tag )
            self.Pass()
            self.Exit()
        info( "%s WaitForLeave" % self.context.tag )


# ------------------------------------------------------------------
# ------------------------------------------------------------------
    
class CancelSessionFSM( fsm.TimeoutFailFSM ):
    def __init__(self, context, timeoutFail=2.0):
        super(CancelSessionFSM, self).__init__(self.MmCancel, context, timeoutFail)
        
    def MmCancel(self):
        warning( "%s MmCancel..." % self.context.tag )
        self.context.CancelMM()
        return self.WaitForCancel

    def WaitForCancel(self):
        if self.context.mm is None:
            warning( "%s mm canceled ok" % self.context.tag )
            self.Pass()
            self.Exit()
        info( "%s WaitForCancel" % self.context.tag )


# ------------------------------------------------------------------
# ------------------------------------------------------------------

class WaitForPvxGameFSM( fsm.TimeoutFailFSM ):
    
    def __init__(self, context, timeoutFail=10.0):
        super(WaitForPvxGameFSM, self).__init__(self.WaitRun, context, timeoutFail)
        
    def WaitRun(self):
        info( "WaitRun mmid %s" % self.context.mm.mmid )
        if not (self.context.mm and self.context.mm.mmid):
            self.context.Fail( "no mm context! %s" % self)
            self.Exit()
        elif (self.context.mm.progress == 104):
            self.Pass()
            self.Exit()
        else:
            self.context.PingMM()
            
# ------------------------------------------------------------------
# ------------------------------------------------------------------

class WaitForPvxFinishFSM( fsm.TimeoutFailFSM ):
    
    def __init__(self, context, timeoutFail=10.0):
        super(WaitForPvxFinishFSM, self).__init__(self.CheckGameAlive, context, timeoutFail)
        
    def CheckGameAlive(self):
        if self.context.mm and self.context.mm.mmid:
            self.context.expectFailMessage("no active matchmaking sessions")
            return self.WaitForDrop
        else:
            self.context.Fail( "no mm context! %s" % self)
            self.Exit()
            
    def WaitForDrop(self):
        info( "WaitForDrop mmid %s" % self.context.mm.mmid )
        if (not self.context.mm) or self.context.receivedFailMessage("no active matchmaking sessions"):
            warning( "%s Game deleted (no active sessions)" % self.context.tag )
            self.Pass()
            self.Exit()
        elif self.context.mm.progress == 102:
            self.context.Fail("PW_GAME did not launch")
            self.Exit()
        elif self.context.mm.progress == 106:
            warning( "%s Game finished (106)" % self.context.tag )
            self.Pass()
            self.Exit()
        else:
            self.context.PingMM()
            
# ------------------------------------------------------------------
# ------------------------------------------------------------------

class SetGeolocationFSM( fsm.TimeoutFailFSM ):
    
    def __init__(self, context, geolocation, timeoutFail=10.0):
        super(SetGeolocationFSM, self).__init__(self.SetGeolocationFSM, context, timeoutFail)
        self.geolocation = geolocation
        self.tag = self.context.tag

    def SetGeolocationFSM(self):
        info("%s SetGeolocation(%s)" % (self.tag, self.geolocation))
        self.context.db.geolocation = ''
        self.context.SetGeolocation( self.geolocation )
        return self.WaitForGeolocation
        
    def WaitForGeolocation(self):
        if self.context.db.geolocation:
            warning( "%s set geolocation=%s" % (self.tag, self.context.db.geolocation) )
            self.Pass()
            return self.Exit()
            
        info("%s SetGeolocationFSM.WaitForGeolocation" % (self.tag))
        