# -*- coding: cp1251 -*-
import subprocess, os, sys, time, datetime, shutil, random
from  zipfile import ZipFile

stopAutotestFileName = "stopautotest.flag"
stopSchedulerFileName = "stopsheduler.flag"
invalidPid = -1
serverReplayDir = "replays"
serverLogsDir = "logs"
clientLogsDir = "logs"

logFile = None

# ########################################################################################
def check_output(*popenargs, **kwargs):
    process = subprocess.Popen(stdout=subprocess.PIPE, *popenargs, **kwargs)
    output, unused_err = process.communicate()
    retcode = process.poll()
    return output


#########################################################################################
def call(*popenargs, **kwargs):
    return subprocess.Popen(*popenargs, **kwargs).wait()


#########################################################################################
# TODO: would be better to write more generic call without exposing psexec and its flags
def PSExecRun(args, runInBackground):
    openArgs = ["bin\\psexec", "-s"]
    if not runInBackground:
        openArgs += ["-i"]
    openArgs += args
    check_output(openArgs, shell=True)


#########################################################################################
def SetLogFile(newLogFile):
    global logFile
    logFile = newLogFile


#########################################################################################
def PrintMessage(*args):
    message = datetime.datetime.now().strftime("[%d.%m.%y %H:%M:%S] ") + ' '.join(map(str, args))
    print message
    if logFile != None:
        logFile.write(message + '\n')


#########################################################################################
def RemoveFile(file):
    if os.path.isfile(file):
        try:
            os.unlink(file)
        except:
            PrintMessage("Failed to remove file", file, "!", str(sys.exc_info()[1]))
            return False
    return True


#########################################################################################
def wait(seconds, silent=False):
    if not silent:
        PrintMessage("Waiting", seconds, "seconds...")
    time.sleep(seconds)


#########################################################################################
class Mode:
    def __init__(self):
        self.times = 0
        self.playersCount = 0
        self.sessionMap = ""
        self.aiFlags = ""
        self.reconnectTime = 0
        self.reconnectCount = 0


class Settings:
    def __init__(self, configfile):
        self.serverWait = 120
        self.clientWait = 30
        self.killWait = 60

        f = open(configfile, "r")
        self.serverDrive = self.getString(f, "serverDrive")
        self.clientDrive = self.getString(f, "clientDrive")
        self.serverShare = self.getString(f, "serverShare")
        self.clientShare = self.getString(f, "clientShare")
        self.serverDir = self.getString(f, "serverDir")
        self.serverMMDir = self.getString(f, "serverMMDir")
        self.clientDir = self.getString(f, "clientDir")
        self.serverComp = self.getString(f, "serverComp")
        self.ZipDir = self.getString(f, "ZipDir")
        self.AttemptToConnect = int(self.getString(f, "AttemptToConnect"))
        self.AttemptToGetVersion = int(self.getString(f, "AttemptToGetVersion"))
        self.WaitForConnecting = int(self.getString(f, "WaitForConnecting"))
        self.WaitForGettingVersion = int(self.getString(f, "WaitForGettingVersion"))

        self.clientUpdate = self.getBool(f, "clientUpdate")

        self.clientSrcPath = []
        for idx in xrange(0, 10):
            self.clientSrcPath.append(self.getString(f, "clientSrcPath" + str(idx)))

        maxPath = 0
        for idx in xrange(0, 10):
            if maxPath > 0:
                self.clientSrcPath[idx] = self.clientSrcPath[idx % maxPath]
            elif len(self.clientSrcPath[idx]) < 5:
                maxPath = idx
                self.clientSrcPath[idx] = self.clientSrcPath[idx % maxPath]

        self.clientDstCheckVersion = self.getBool(f, "clientDstCheckVersion")
        self.serverUpdate = self.getBool(f, "serverUpdate")
        self.serverUpdateAttempts = int(self.getString(f, "serverUpdateAttempts"))
        self.serverSrcSvn = self.getString(f, "serverSrcSvn")
        self.serverRevision = self.getString(f, "serverRevision")

        #email
        self.sendGroupName = self.getString(f, "sendGroupName")
        self.testName = self.getString(f, "testName")
        self.SMTPServer1 = self.getString(f, "SMTPServer1")
        self.user1 = self.getString(f, "user1")
        self.password1 = self.getString(f, "password1")
        self.SMTPServer2 = self.getString(f, "SMTPServer2")
        self.user2 = self.getString(f, "user2")
        self.password2 = self.getString(f, "password2")

        self.times = int(self.getString(f, "times"))
        self.startTime = self.getString(f, "startTime")
        self.stopTime = self.getString(f, "stopTime")

        self.userNamePrefix = self.getString(f, "userNamePrefix")
        self.userHeloWorld = self.getString(f, "userHeloWorld")
        self.useSkins = self.getBool(f, "useSkins")
        self.useTestTalentSet = self.getBool(f, "useTestTalentSet")

        self.timeScale = self.getString(f, "timeScale")

        self.defaultNullRender = int(self.getString(f, "nullRender"))
        self.defaultRunInBackground = self.getBool(f, "runInBackground")
        self.runInBackgroundServer = self.getBool(f, "runInBackgroundServer", self.defaultRunInBackground, False)
        self.udpEnable = self.getBool(f, "udpEnable", True)
        self.clientComp = []
        self.nullRender = []
        self.runInBackground = []
        for idx in xrange(0, 10):
            self.clientComp.append(self.getString(f, "clientComp" + str(idx)))
            self.nullRender.append(int(self.getString(f, "nullRenderClient" + str(idx), self.defaultNullRender, False)))
            self.runInBackground.append(
                self.getBool(f, "runInBackgroundClient" + str(idx), self.defaultRunInBackground, False))

        self.clients = 0
        for cl in self.clientComp:
            if cl:
                self.clients += 1

        self.modesCount = int(self.getString(f, "modesCount"))
        self.modes = []
        for i in xrange(0, self.modesCount):
            self.modes.append(Mode())
            self.modes[i].times = int(self.getString(f, "mode" + str(i + 1) + "Times"))
            self.modes[i].playersCount = int(self.getString(f, "mode" + str(i + 1) + "PlayersCount"))
            self.modes[i].sessionMap = self.getString(f, "mode" + str(i + 1) + "SessionMap")
            self.modes[i].aiFlags = self.getString(f, "mode" + str(i + 1) + "AiFlags")
            self.modes[i].reconnectTime = int(self.getString(f, "mode" + str(i + 1) + "ReconnectTime"))
            self.modes[i].reconnectCount = int(self.getString(f, "mode" + str(i + 1) + "ReconnectCount"))

        f.close()

    def getBool(self, f, name, default=False, echo=True):
        return self.getString(f, name, ("False", "True")[default], echo) in ["True", "true", "1"]

    def getString(self, f, name, default="0", echo=True):
        f.seek(0)
        for line in f:
            if line.find(name) != -1:
                value = line[line.find("=") + 1:]
                value = value.strip()
                return value
        if echo:
            PrintMessage(name, " - not found, using", default)
        return default

    def __repr__(self):
        str_repr = "nullRender = " + str(self.nullRender) + "\n"
        str_repr += "serverDrive = " + self.serverDrive + "\n"
        str_repr += "clientDrive = " + self.clientDrive + "\n"
        str_repr += "serverShare = " + self.serverShare + "\n"
        str_repr += "clientShare = " + self.clientShare + "\n"

        str_repr += "serverDir = " + self.serverDir + "\n"
        str_repr += "clientDir = " + self.clientDir + "\n"
        str_repr += "serverComp = " + self.serverComp + "\n"

        str_repr += "times = " + str(self.times) + "\n"
        str_repr += "userNamePrefix = " + self.userNamePrefix + "\n"
        str_repr += "userHeloWorld = " + self.userHeloWorld + "\n"
        str_repr += "useSkins = " + str(self.useSkins) + "\n"
        str_repr += "useTestTalentSet = " + str(self.useTestTalentSet) + "\n"
        str_repr += "sessionMap = " + self.sessionMap + "\n"

        str_repr += "playersCount = " + str(self.playersCount) + "\n"
        str_repr += "reconnectTime = " + str(self.reconnectTime) + "\n"
        str_repr += "reconnectNumbers = " + str(self.reconnectNumbers) + "\n"

        for idx in xrange(0, len(self.clientComp)):
            str_repr += "client" + str(idx) + " = " + str(self.clientComp[idx]) + "\n"

        str_repr += "total clients = " + str(self.clients) + "\n"
        return str_repr

    def getIPs(self):
        self.serverIp = check_output(["bin\\getip.exe", self.serverComp], shell=True)
        self.clientIp = []
        for idx in xrange(0, self.clients):
            self.clientIp.append(check_output(["bin\\getip.exe", self.clientComp[idx]], shell=True))


#########################################################################################
def StopServer(settings):
    PrintMessage("Stopping server...")
    serverDir = settings.serverDrive + settings.serverDir + "\\Bin"
    autotestDir = settings.serverDrive + "Autotest\\Autotest"
    PrintMessage("Run StopPVX.bat...")
    PSExecRun(["-w", serverDir, "\\\\" + settings.serverComp, autotestDir + "\\StopPVX.bat"], settings.runInBackgroundServer)
    wait(10)
    PrintMessage("Run stopcluster.cmd...")
    PSExecRun(["-w", serverDir, "\\\\" + settings.serverComp, serverDir + "\\stopcluster.cmd"], settings.runInBackgroundServer)
    wait(10)
    # call(["taskkill", "/s", settings.serverComp, "/im", "UniServerApp\"\*", "/F", "/T"], shell=True)
    # call(["taskkill", "/s", settings.serverComp, "/im", "ToolsServer\"\*", "/F", "/T"], shell=True)
    PrintMessage("Stopping server OK")


#########################################################################################
def RemoveDir(dir):
    if os.path.exists(dir):
        try:
            shutil.rmtree(dir)
        except:
            PrintMessage("Failed to remove directory", dir, "!", str(sys.exc_info()[1]))
            return False
    return True


#########################################################################################
def CleanDir(dirName):
    PrintMessage("Cleaning directory", dirName, "...")
    for root, dirs, files in os.walk(dirName):
        for file in files:
            RemoveFile(os.path.join(root, file))
        for dir in dirs:
            RemoveDir(os.path.join(root, dir))
    PrintMessage("Cleaning directory", dirName, "finished")


#########################################################################################
def ZipDir(path, zip):
    for root, dirs, files in os.walk(path):
        for file in files:
            PrintMessage("ZipDir file %r" % file)
            zip.write(os.path.join(root, file), os.path.join(os.path.basename(root), file))


#########################################################################################
def ZipFiles(folderName, clientNumber, iteration, settings, version, configDir):
    PrintMessage("Archiving folder...")
    PrintMessage("ZipFiles %r %r" % (clientNumber, iteration))
    if not os.path.isdir(folderName):
        PrintMessage("Archiving folder failed!")
        return
    if ( os.access(settings.ZipDir, os.F_OK) == False ):
        os.mkdir(settings.ZipDir)
    filename = settings.ZipDir + "\\" + datetime.datetime.now().strftime(
        "%Y.%m.%d-%H.%M.%S-") + version + "-client-%i-iter-%i" % (clientNumber, iteration) + ".zip"
    zf = ZipFile(filename, mode='w')
    #for name in os.listdir( folderName ):
    #  zf.write( folderName + "\\" + name, name )
    ZipDir(folderName, zf)

    configNames = ["default.cfg", "game.cfg", "custom.cfg", "hero.cfg", "bots.cfg", "autoexec.cfg"]
    for conf in configNames:
        PrintMessage("Add config %r %r %r" % (
        conf, os.path.join(configDir, conf), os.path.join(os.path.basename(configDir), conf)))
        zf.write(os.path.join(configDir, conf), os.path.join(os.path.basename(configDir), conf))

    zf.close()
    CleanDir(folderName)
    PrintMessage("Archiving folder OK")


#########################################################################################
def stopClient(settings, idx):
    clientDir = settings.clientDrive + "\\" + settings.clientDir + "\\Bin"
    # PSExecRun(["-w", clientDir, "\\\\" + settings.clientComp[idx], "python", clientDir + "\\stopclient.py", str(pid)], settings.runInBackground[idx])
    PrintMessage("Trying to kill PW_Game.exe on client " + settings.clientComp[idx])
    os.system("taskkill /s " + settings.clientComp[idx] + " /f /fi \"IMAGENAME eq PW_Game.exe\"")
    wait(5)
    PrintMessage("Trying to kill castle.exe on client " + settings.clientComp[idx])
    os.system("taskkill /s " + settings.clientComp[idx] + " /f /fi \"IMAGENAME eq castle.exe\"")
    wait(5)
