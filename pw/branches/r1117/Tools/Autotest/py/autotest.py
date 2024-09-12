# -*- coding: cp1251 -*-
from autotestcommon import *
import re, threading, os

# ########################################################################################
# для отправки на емайл
import smtplib
from email.MIMEText import MIMEText
from email.MIMEMultipart import MIMEMultipart
from email.Header import make_header
from email.Utils import formatdate

#########################################################################################
def CreateLog():
    logDirName = "start_logz"
    logFileName = os.path.join(logDirName, "autotest-log-" + datetime.datetime.now().strftime("%Y.%m.%d-%H.%M.%S") + ".txt")
    foutput = open(logFileName, "a")
    SetLogFile(foutput)
    return foutput

#########################################################################################
Assertions = {}  # { "первая строка" : { (номер клиента, итерация ) : сколько раз повторился } }
Exceptions = {}  # { "первая строка калстека" : { (номер клиента, итерация ) : сколько раз повторился } }
Asyncs = {}  # { "crc" : { (номер клиента, итерация ) : сколько раз повторился } }
Datas = {}  # { "первая строка" : { (номер клиента, итерация ) : сколько раз повторился } }
version = ''

#########################################################################################
def waitCheckStop(seconds):
    partTime = 5
    restTime = seconds;
    while (restTime > 0 and not IsStopRequested()):
        time.sleep(partTime)
        restTime -= partTime;


#########################################################################################
def SendMail(subject, message, settings):
    PrintMessage("Sending e-mail to: " + settings.sendGroupName)
    PrintMessage("===========================================================\n" + subject + "\n" + message)
    PrintMessage("===========================================================")	
    
    try:
        s = smtplib.SMTP(settings.SMTPServer1, 25)
        s.starttls()
        s.login(settings.user1, settings.password1)
    except:
        try:
            s = smtplib.SMTP(settings.SMTPServer2, 25)
            s.starttls()
            s.login(settings.user2, settings.password2)        
        except:
            PrintMessage("SMTP connect failed, e-mail not sent!")
            return False

    icharset = 'cp1251'
    msg = MIMEMultipart()
    hdr = make_header([(subject, icharset)])
    msg['From'] = settings.testName
    msg['To'] = settings.sendGroupName
    msg['Date'] = formatdate(localtime=True)
    msg['Subject'] = hdr
    msg.attach(MIMEText(message, "", _charset=icharset))

    s.sendmail(settings.testName, settings.sendGroupName, msg.as_string())
    s.quit()
    return True


#########################################################################################
def EnsureDir(dir):
    if not os.path.exists(dir):
        try:
            os.makedirs(dir)
        except:
            PrintMessage("Failed to create directory", dir, "!", str(sys.exc_info()[1]))
            return False
    return True


#########################################################################################
def CopyDir(dst, src):
    if os.path.exists(src):
        try:
            shutil.copytree(src, dst)
            return True
        except:
            PrintMessage("Failed to copy directory", src, "to", dst, "!", str(sys.exc_info()[1]))
    else:
        PrintMessage("Failed to copy directory", src, "to", dst, "! Source directory not found.")
    return False


#########################################################################################
def UnzipFile(dstPath, srcZip):
    if os.path.exists(dstPath) and os.path.isfile(srcZip):
        zip = ZipFile(srcZip)
        try:
            zip.extractall(dstPath)
            return True
        except:
            PrintMessage("Failed to unzip", srcZip, "to", dstPath, "!", str(sys.exc_info()[1]))
    else:
        PrintMessage("Failed to unzip", srcZip, "to", dstPath, "! Destination path or zip file are incorrect.")
    return false


#########################################################################################
def IsStopRequested():
    return os.path.isfile(stopAutotestFileName)


#########################################################################################
def GetClient(dstPath, settings, versionInfo, results, idx):
    PrintMessage("Getting version for Client" + str(idx))
    results[idx] = False
    sameVersion = False
    dstVersionFile = dstPath + "/version.txt"
    if settings.clientDstCheckVersion:
        if os.path.isfile(dstVersionFile):
            f = open(dstVersionFile, "r")
            firstLine = f.readline();
            if firstLine == versionInfo["ver"]:
                PrintMessage("Client" + str(idx) + " already has version " + versionInfo["ver"])
                sameVersion = True
            f.close()
    if not sameVersion:
        if not RemoveDir(dstPath):
            PrintMessage("Fail remove dir ", dstPath)
            return
        srcPath = versionInfo["path"] + "/" + versionInfo["ver"]
        if not versionInfo["isTrunk"]:
            srcPath += "/PvP"
        if not CopyDir(dstPath, srcPath):
            PrintMessage("Fail copy dir ", dstPath, srcPath)
            return
        if not versionInfo["isTrunk"]:
            for name in os.listdir(dstPath):
                if (name.endswith(".zip")):
                    srcZip = dstPath + "\\" + name
                    PrintMessage("Unzipping", srcZip, "to", dstPath)
                    if not UnzipFile(dstPath, srcZip):
                        PrintMessage("Fail unzip ", dstPath, srcZip)
                        return
        f = open(dstVersionFile, "w")
        f.write(versionInfo["ver"])
        f.close()
    PrintMessage("Getting version for Client" + str(idx) + " finished")
    results[idx] = True


#########################################################################################
def GetServer(dstPath, srcSvn, revision, attempts, result):
    PrintMessage("Updating server...")
    StopServer(settings)
    PrintMessage("Target directory is ", dstPath)

    retcode = -1
    success = False
    if (attempts <= 0):
        attempts = 1
    attemptsLeft = attempts

    while attemptsLeft > 0 and not success:
        PrintMessage("GetServer attempt %r" % attemptsLeft)
        if os.path.exists(dstPath):
            RemoveFile(dstPath + "\\Profiles\\server.cfg.bak")
            if 0 != call(
                    ["svn", "revert", dstPath + "\\Profiles\\server.cfg", "--non-interactive", "--trust-server-cert",
                     "-q"], shell=True):
                PrintMessage("Server config reverting failed!")
            call(["svn", "cleanup", "--non-interactive", "--trust-server-cert", dstPath], shell=True)
            if revision == "":
                retcode = call(
                    ["svn", "update", "--non-interactive", "--trust-server-cert", "--accept", "theirs-full", dstPath,
                     "-q"], shell=True)
            else:
                retcode = call(
                    ["svn", "update", "--non-interactive", "--trust-server-cert", "--accept", "theirs-full", dstPath,
                     "-r", revision, "-q"], shell=True)
        else:
            PrintMessage("Getting server from", srcSvn, "...")
            if revision == "":
                retcode = call(["svn", "checkout", "--non-interactive", "--trust-server-cert", srcSvn, dstPath, "-q"],
                               shell=True)
            else:
                retcode = call(
                    ["svn", "checkout", "--non-interactive", "--trust-server-cert", srcSvn, dstPath, "-r", revision,
                     "-q"], shell=True)

        if 0 == retcode:
            success = True
        else:
            attemptsLeft -= 1
            if attemptsLeft > 0:
                PrintMessage("Updating server failed... will retry after waiting")
                wait(60)

    if success:
        PrintMessage("Updating server finished")
    else:
        PrintMessage("Updating server failed after", attempts, "attempts")
    result[0] = success


def GetPatternForPath(versionInfo):
    if versionInfo["isTrunk"]:
        return re.compile(r'^PvP-trunk-\w+\.\w+\.\w+\.(?P<verCode_name>(\w+))\.\w+\.(?P<verData_name>(\w+))\.\w+',
                          re.I | re.U)
    return re.compile(
        r'^CommonClient-Starforce-(?P<ap_name>(\w+\.*)+)-(?P<loc1_name>(\w+\.*)+)-(?P<loc2_name>(\w+\.*)+)-(?P<verCode_name>(\w+)+)\.*\w*-(?P<verData_name>(\w+)+)',
        re.I | re.U)


class RevsInfo:
    def __init__(self, verCode, verData, name):
        self.verCode = verCode
        self.verData = verData
        self.name = name

    def __eq__(self, other):
        return self.verCode == other.verCode and self.verData == other.verData

    def __repr__(self):
        return ""


def GetVersionsAvalible(versionInfo):
    pattern_re = versionInfo["pattern"]
    lst = []
    if os.path.isdir(versionInfo["path"]):
        for name in os.listdir(versionInfo["path"]):
            res = pattern_re.match(name)
            if res:
                verCode = res.group('verCode_name')
                verData = res.group('verData_name')
                revInfo = RevsInfo(verCode, verData, name)
                lst.append(revInfo)
        lst.sort(key=lambda x: x.verCode)
        lst.reverse()
    else:
        PrintMessage("Failed to access", versionInfo["path"])

    return lst


def GetVersionName(versionName):
    if len(versionName) == 0:
        PrintMessage("Versions are empty! Fail")
        return None

    isTrunk = versionName[0]["isTrunk"]

    for ver in versionName:
        if ver["isTrunk"] != isTrunk:
            PrintMessage("Failed try to test Trunk and AP!")
            return None
        isTrunk = ver["isTrunk"]

    revisions = None

    for rev in versionName[0]["revs"]:
        isInAll = True
        for newIdx in xrange(0, len(versionName)):
            isFind = False
            for revIdx in xrange(0, len(versionName[newIdx]["revs"])):
                if rev == versionName[newIdx]["revs"][revIdx]:
                    versionName[newIdx]["ver"] = versionName[newIdx]["revs"][revIdx].name
                    isFind = True
            if not isFind:
                isInAll = False
                break

        if isInAll:
            revisions = rev
            break

    if not revisions:
        PrintMessage("Failed find compatible revisions!")
        return None

    return versionName


def GetVersion(settings):
    serverUpdate = settings.serverUpdate
    clientUpdate = settings.clientUpdate

    if (serverUpdate):
        serverPath = "\\\\" + settings.serverComp + "\\" + settings.serverShare + "\\" + settings.serverDir
        resultSrv = [None] * 1
        threadSrv = threading.Thread(target=GetServer, args=(
        serverPath, settings.serverSrcSvn, settings.serverRevision, settings.serverUpdateAttempts, resultSrv))
        threadSrv.start()
        wait(1, True)
        if settings.udpEnable:
            serverMMPath = "\\\\" + settings.serverComp + "\\" + settings.serverShare + "\\" + settings.serverMMDir
            resultMMSrv = [None] * 1
            threadMMSrv = threading.Thread(target=GetServer, args=(
            serverMMPath, settings.serverSrcSvn, settings.serverRevision, settings.serverUpdateAttempts, resultMMSrv))
            threadMMSrv.start()
            wait(1, True)
    else:
        PrintMessage("Server update skipped")

    success = True

    if (clientUpdate):
        versionName = [None] * settings.clients
        for idx in xrange(0, settings.clients):
            versionInfo = {}

            versionInfo["path"] = settings.clientSrcPath[idx]

            if versionInfo["path"].lower().find("trunk") != -1:
                versionInfo["isTrunk"] = True
            else:
                versionInfo["isTrunk"] = False

            versionInfo["pattern"] = GetPatternForPath(versionInfo)
            versionInfo["revs"] = GetVersionsAvalible(versionInfo)

            versionName[idx] = versionInfo

            if ( versionInfo["revs"] == [] ):
                PrintMessage("Failed to get client version name!")
                success = False
                clientUpdate = False

        if success:
            versionName = GetVersionName(versionName)
            if not versionName:
                success = False
                clientUpdate = False

        if success:
            PrintMessage("Client version:", versionName)
            threads = [None] * settings.clients
            results = [None] * settings.clients
            for idx in xrange(0, settings.clients):
                clientPath = "\\\\" + settings.clientComp[idx] + "\\" + settings.clientShare + "\\" + settings.clientDir
                threads[idx] = threading.Thread(target=GetClient,
                                                args=(clientPath, settings, versionName[idx], results, idx))
                threads[idx].start()
                wait(1, True)
    else:
        PrintMessage("Clients update skipped")

    if (serverUpdate):
        threadSrv.join()
        if settings.udpEnable:
            threadMMSrv.join()

        if resultSrv[0]:
            PrintMessage("Got version for server")
        else:
            PrintMessage("Failed to get version for server!")
            SendMail("Version", "Failed to get version for server!", settings)
            success = False

    if (clientUpdate):
        for idx in xrange(0, settings.clients):
            threads[idx].join()
            if results[idx]:
                PrintMessage("Got version for Client" + str(idx))
            else:
                PrintMessage("Failed to get version for Client" + str(idx), "!")
                SendMail("Version", "Failed to get version for Client " + str(idx) + " !", settings)
                success = False

    if (not success):
        counter = settings.AttemptToGetVersion
        while ( counter and not success ):

            if (serverUpdate):
                if (not resultSrv[0]):
                    PrintMessage("Trying to get version for server again")
                    threadSrv = threading.Thread(target=GetServer, args=(
                    serverPath, settings.serverSrcSvn, settings.serverRevision, settings.serverUpdateAttempts,
                    resultSrv))
                    threadSrv.start()

            if (clientUpdate):
                for idx in xrange(0, settings.clients):
                    if (not results[idx]):
                        PrintMessage("Trying to get version for Client" + str(idx) + " again")
                        clientPath = "\\\\" + settings.clientComp[
                            idx] + "\\" + settings.clientShare + "\\" + settings.clientDir
                        threads[idx] = threading.Thread(target=GetClient,
                                                        args=(clientPath, settings, versionName[idx], results, idx))
                        threads[idx].start()

            if (clientUpdate):
                for idx in xrange(0, settings.clients):
                    threads[idx].join()
                    if results[idx]:
                        PrintMessage("Got version for Client" + str(idx))

            if (serverUpdate):
                threadSrv.join()

            counter -= 1
            success = not (False in results) and resultSrv[0]

        if (serverUpdate and resultSrv[0]):
            PrintMessage("Got version for server")

    return success


#########################################################################################
def GetLinesFromFile(inputFile):
    f = open(inputFile, "r")
    inputLines = []
    for fline in f:
        line = ' '.join(fline.split())
        if line != "" and len(line) > 2:
            inputLines.append(line + "\n")
    f.close()
    return inputLines

########################################################################################
def StartMMServer(settings):
    PrintMessage("Preparing MM cluster...")
    cfgDir = "\\\\" + settings.serverComp + "\\" + settings.serverShare + "\\" + settings.serverMMDir + "\\Profiles"
    if settings.serverUpdate:
        # Set up server custom config
        if not os.path.isfile(cfgDir + "\\server.cfg.bak"):
            os.rename(cfgDir + "\\server.cfg", cfgDir + "\\server.cfg.bak")
        inputfile = open(cfgDir + "\\server.cfg.bak", "r")
        outputfile = open(cfgDir + "\\server.cfg", "w")
        lines = inputfile.readlines()

        outputfile.writelines(lines)
        newlines = []
        newlines.append("\n\n// Autotest overrides:\n")
        #newlines.append( "lobby_custom_autostart_players "+str(settings.clients)+"\n" )
        #newlines.append( "lobby_custom_autostart_players -1\n" )
        newlines.append("frontend_ip_addr " + settings.serverIp + "\n")
        newlines.append("backend_ip_addr " + settings.serverIp + "\n")
        newlines.append("setvar coordinator_address = " + settings.serverIp + ":35000\n")
        newlines.append("uniserver_svcpath mm\n")
        newlines.append("setvar cluster_name = Local_mm\n")
        newlines.append("setvar first_server_port = 35010\n")

        outputfile.writelines(newlines)
        outputfile.close()
        inputfile.close()

        outputfile = open(cfgDir + "\\pvx_srv_custom_social_lobby.cfg", "w")
        newlines = []
        newlines.append("\n\n// Autotest overrides:\n")
        newlines.append('soclobby_ext_addr "' + settings.serverIp + ':35099"\n')
        outputfile.writelines(newlines)
        outputfile.close()

        # Set up login svc custom config
        outputfile = open(cfgDir + "\\pvx_srv_custom_login.cfg", "w")
        newlines = []
        newlines.append("\n\n// Autotest overrides:\n")
        newlines.append("setvar login_address = " + settings.serverIp + ":35001\n")
        outputfile.writelines(newlines)
        outputfile.close()


    replayDir = "\\\\" + settings.serverComp + "\\" + settings.serverShare + "\\" + settings.serverMMDir + "\\Bin\\" + serverReplayDir
    CleanDir(replayDir)
    logsDir = "\\\\" + settings.serverComp + "\\" + settings.serverShare + "\\" + settings.serverMMDir + "\\Bin\\" + serverLogsDir
    CleanDir(logsDir)

    PrintMessage("Preparing server OK")

    PrintMessage("Starting server...")
    serverDir = settings.serverDrive + "\\" + settings.serverMMDir + "\\Bin"
    PSExecRun(["-w", serverDir, "\\\\" + settings.serverComp, serverDir + "\\update.cmd"],
              settings.runInBackgroundServer)
    wait(10)
    # Стартуем только cluster MM
    PSExecRun(["-w", serverDir, "\\\\" + settings.serverComp, serverDir + "\\run_mm.cmd"], settings.runInBackgroundServer)

    wait(settings.serverWait)
    PrintMessage("Starting MM cluster OK")


#########################################################################################
def StartServer(settings):
    PrintMessage("Preparing server...")
    if settings.udpEnable:
        PrintMessage("Preparing UDP game server...")
    cfgDir = "\\\\" + settings.serverComp + "\\" + settings.serverShare + "\\" + settings.serverDir + "\\Profiles"

    if settings.serverUpdate:
        # Set up server custom config
        if not os.path.isfile(cfgDir + "\\server.cfg.bak"):
            os.rename(cfgDir + "\\server.cfg", cfgDir + "\\server.cfg.bak")
        inputfile = open(cfgDir + "\\server.cfg.bak", "r")
        outputfile = open(cfgDir + "\\server.cfg", "w")
        lines = inputfile.readlines()

        outputfile.writelines(lines)
        newlines = []
        newlines.append("\n\n// Autotest overrides:\n")
        #newlines.append( "lobby_custom_autostart_players "+str(settings.clients)+"\n" )
        #newlines.append( "lobby_custom_autostart_players -1\n" )
        newlines.append("frontend_ip_addr " + settings.serverIp + "\n")
        newlines.append("backend_ip_addr " + settings.serverIp + "\n")

        if settings.udpEnable and "rdp_enable 1" not in lines:
            newlines.append("uniserver_svcpath ru0\n")
            newlines.append("setvar cluster_name = Local_ru0\n")
            newlines.append("coordinator_address " + settings.serverIp + ":35100\n")
            newlines.append("setvar first_server_port = 35110\n")
            newlines.append("rdp_enable 1\n")
        else:
            newlines.append("coordinator_address " + settings.serverIp + ":35000\n")
            newlines.append("rdp_enable 0\n")

        outputfile.writelines(newlines)
        outputfile.close()
        inputfile.close()

        if settings.udpEnable:
            outputfile = open(cfgDir + "\\pvx_srv_custom_lobby.cfg", "w")
            newlines = []
            newlines.append("\n\n// Autotest overrides:\n")
            newlines.append('lobby_ext_social_addr "' + settings.serverIp + ':35099"\n')
            newlines.append('lobby_my_ext_location "ru0"\n')
            newlines.append('lobby_login_address "' + settings.serverIp + ':35101"\n')
            outputfile.writelines(newlines)
            outputfile.close()

        if settings.udpEnable:
            outputfile = open(cfgDir + "\\pvx_srv_custom_newlogin.cfg", "w")
            newlines = []
            newlines.append("\n\n// Autotest overrides:\n")
            newlines.append("login_address " + settings.serverIp + ":35101\n")
            outputfile.writelines(newlines)
            outputfile.close()
        else:
            # Set up login svc custom config
            outputfile = open(cfgDir + "\\pvx_srv_custom_login.cfg", "w")
            newlines = []
            newlines.append("\n\n// Autotest overrides:\n")
            newlines.append("login_address " + settings.serverIp + ":35001\n")
            outputfile.writelines(newlines)
            outputfile.close()

        # Set up game svc custom config
        outputfile = open(cfgDir + "\\pvx_srv_custom_gamesvc.cfg", "w")
        newlines = []
        newlines.append("\n\n// Autotest overrides:\n")
        newlines.append("game_trust_gap 5\n")
        newlines.append("game_afc_disconnect_time 0.0\n")
        newlines.append("game_send_async_to_all_clients_enabled 1\n")
        newlines.append("game_timescale_enabled 1\n")
        newlines.append("game_save_replay 1\n")
        newlines.append("game_bds_replays 1\n")
        newlines.append("game_bds_replays_folder " + serverReplayDir + "\n")
        outputfile.writelines(newlines)
        outputfile.close()

    replayDir = "\\\\" + settings.serverComp + "\\" + settings.serverShare + "\\" + settings.serverDir + "\\Bin\\" + serverReplayDir
    CleanDir(replayDir)
    logsDir = "\\\\" + settings.serverComp + "\\" + settings.serverShare + "\\" + settings.serverDir + "\\Bin\\" + serverLogsDir
    CleanDir(logsDir)

    PrintMessage("Preparing server OK")

    PrintMessage("Starting server...")
    serverDir = settings.serverDrive + "\\" + settings.serverDir + "\\Bin"
    PSExecRun(["-w", serverDir, "\\\\" + settings.serverComp, serverDir + "\\update.cmd"],
              settings.runInBackgroundServer)
    wait(10)
    if settings.udpEnable:
        # Стартуем только сессию если у нас udp
        PSExecRun(["-w", serverDir, "\\\\" + settings.serverComp, serverDir + "\\run_udp.cmd"],
                  settings.runInBackgroundServer)
    else:
        PSExecRun(["-w", serverDir, "\\\\" + settings.serverComp, serverDir + "\\run.cmd"],
                  settings.runInBackgroundServer)
    wait(settings.serverWait)
    PrintMessage("Starting server OK")


#########################################################################################
def CollectLogsError(rootFolderName, clientNumber, iteration):
    PrintMessage("Collecting logs errors for client" + str(clientNumber) + " folder=" + rootFolderName + "...")
    if not os.path.isdir(rootFolderName):
        PrintMessage("Collecting logs errors failed!")
        return
    patternAssert = r"^.+[0-9.-]+assert.log"
    patternData = r"^.+[0-9.-]+data.log"
    patternAsync = r"crc-[0-9]+-[0-9A-Fa-fx]+\.bin$"
    patternAsync_re = re.compile(patternAsync)
    patternExceptionFirstString = r"^[a-fA-F0-9 ]+$"
    patternException = r"^.+[0-9.-]+exception.log"
    patternAssert_re = re.compile(patternAssert)
    patternData_re = re.compile(patternData)
    patternException_re = re.compile(patternException)
    patternFirstString = r"^.+[()0-9.:]+\s+[mdWEAC]: "  # mdWEAC взято отсюда \Src\System\LogHelpers.cpp
    patternFirstString_re = re.compile(patternFirstString)
    patternExceptionFirstString_re = re.compile(patternExceptionFirstString)
    patternExceptionAddress = r" \([0-9a-fA-Fx]+\)$"
    patternExceptionAddress_re = re.compile(patternExceptionAddress)
    patternVersion = r"^PW-[0-9a-zA-Z\.]+-[0-9\.]+"
    patternVersion_re = re.compile(patternVersion)
    global Assertions
    global Exceptions
    global Asyncs
    global Datas
    global version

    for dirn in os.listdir(rootFolderName):
        folderName = os.path.join(rootFolderName, dirn)
        for name in os.listdir(folderName):
            if (not version):
                matchObj = patternVersion_re.match(name)
                if (matchObj):
                    version = name[len("PW-"):matchObj.end()]

            assertFound = patternAssert_re.match(name)
            dataFound = patternData_re.match(name)
            if (dataFound or assertFound):
                f = open(folderName + "\\" + name, "rt")
                firstline = f.readline();
                f.close()
                if (firstline):
                    matchObj = patternFirstString_re.match(firstline)
                    if (matchObj):
                        firstline = firstline[matchObj.end():]
                        if (assertFound):
                            if ( firstline in Assertions.keys() ):
                                if ((clientNumber, iteration) in Assertions[firstline].keys()):
                                    Assertions[firstline][(clientNumber, iteration)] += 1
                                else:
                                    Assertions[firstline][(clientNumber, iteration)] = 1
                            else:
                                Assertions[firstline] = {(clientNumber, iteration): 1}
                        if (dataFound):
                            if ( firstline in Datas.keys() ):
                                if ((clientNumber, iteration) in Datas[firstline].keys()):
                                    Datas[firstline][(clientNumber, iteration)] += 1
                                else:
                                    Datas[firstline][(clientNumber, iteration)] = 1
                            else:
                                Datas[firstline] = {(clientNumber, iteration): 1}

            if (patternException_re.match(name)):
                f = open(folderName + "\\" + name, "rt")
                firstline = f.readline();
                while (firstline):
                    firstline = f.readline();
                    if (patternExceptionFirstString_re.match(firstline)):
                        break

                firstline = f.readline();
                f.close()
                if (firstline):
                    searchObj = patternExceptionAddress_re.search(firstline)
                    if (searchObj):
                        firstline = firstline[:searchObj.start()]
                    if ( firstline in Exceptions.keys() ):
                        if ((clientNumber, iteration) in Exceptions[firstline].keys()):
                            Exceptions[firstline][(clientNumber, iteration)] += 1
                        else:
                            Exceptions[firstline][(clientNumber, iteration)] = 1
                    else:
                        Exceptions[firstline] = {(clientNumber, iteration): 1}
                        subj = firstline + " on client " + str(clientNumber) + " (" + settings.clientComp[
                            clientNumber] + "), iteration " + str(iteration)
                        SendMail("Exception", subj, settings)

            searchObj = patternAsync_re.search(name)
            if (searchObj):
                AsyncId = name[searchObj.start() + len('crc-'): searchObj.end() - len(".bin")]
                if ( AsyncId in Asyncs.keys() ):
                    if ((clientNumber, iteration) in Asyncs[AsyncId].keys()):
                        Asyncs[AsyncId][(clientNumber, iteration)] += 1
                    else:
                        Asyncs[AsyncId][(clientNumber, iteration)] = 1
                else:
                    Asyncs[AsyncId] = {(clientNumber, iteration): 1}
                    subj = AsyncId + " on client " + str(clientNumber) + " (" + settings.clientComp[
                        clientNumber] + "), iteration " + str(iteration)
                    SendMail("Async", subj, settings)

    PrintMessage("Collecting logs errors OK")


#########################################################################################
def removeBadClients(settings, badClients):
    for idx in badClients:
        SendMail("Fail start computer", str(settings.clientComp[idx]), settings)
        del settings.clientComp[idx]
        del settings.nullRender[idx]
        del settings.runInBackground[idx]
        settings.clients -= 1


#########################################################################################
def prepareClientsCommonSettings(settings):
    badClients = []
    for idx in xrange(0, settings.clients):
        try:
            cfgDir = "\\\\" + settings.clientComp[
                idx] + "\\" + settings.clientShare + "\\" + settings.clientDir + "\\Profiles"
            if not os.path.isfile(cfgDir + "\\default.cfg.bak"):
                os.rename(cfgDir + "\\default.cfg", cfgDir + "\\default.cfg.bak")

            inputfile = open(cfgDir + "\\default.cfg.bak", "r")
            outputfile = open(cfgDir + "\\default.cfg", "w")
            newlines = []
            newlines.append("setvar ignoreAsserts = 1\n")
            newlines.append("setvar ignoreWarnings = 1\n")
            newlines.append("setvar full_dump = 0\n")
            outputfile.writelines(newlines)
            lines = inputfile.readlines()
            outputfile.writelines(lines)
            outputfile.close()
            inputfile.close()

            if not os.path.isfile(cfgDir + "\\game.cfg.bak"):
                os.rename(cfgDir + "\\game.cfg", cfgDir + "\\game.cfg.bak")

            inputfile = open(cfgDir + "\\game.cfg.bak", "r")
            outputfile = open(cfgDir + "\\game.cfg", "w")
            newlines = []
            newlines.append("setvar ignoreAsserts = 1\n")
            newlines.append("setvar ignoreWarnings = 1\n")
            newlines.append("setvar full_dump = 0\n")
            newlines.append("setvar exit_on_finish = 1\n")
            newlines.append("setvar gfx_fullscreen = 0\n")
            newlines.append("setvar nullrender = " + str(settings.nullRender[idx]) + "\n")
            newlines.append("setvar nullrender_no_log_box = 0\n")
            newlines.append("setvar register_replay_extention = 0\n")
            if settings.udpEnable:
                newlines.append("login_address " + settings.serverIp + ":35101@10" + " \n")

            outputfile.writelines(newlines)
            lines = inputfile.readlines()
            writelines = []
            for ln in lines:
                if ln.find("custom.cfg") == -1:
                    if ln.find("login_address") == -1:
                        writelines.append(ln)
                    else:
                        if settings.udpEnable:
                            newlines.append("login_address " + settings.serverIp + ":35101@10" + " \n")
                        else:
                            writelines.append("login_address " + settings.serverIp + ":35001\n")

            outputfile.writelines(writelines)
            newlines = []
            newlines.append("setvar debug_crc_mode = 2\n")
            newlines.append("setvar calc_crc_in_separate_thread  = 0\n")
            newlines.append("setvar stat_enabled = 0\n")
            outputfile.writelines(newlines)

            if os.path.isfile("cfg\\game.cfg"):
                gameCfgLines = GetLinesFromFile("cfg\\game.cfg")
                outputfile.writelines(gameCfgLines)

            outputfile.close()
            inputfile.close()
            shutil.copyfile("py\\startclient.py", "\\\\" + settings.clientComp[
                idx] + "\\" + settings.clientShare + "\\" + settings.clientDir + "\\Bin\\startclient.py")
            shutil.copyfile("py\\stopclient.py", "\\\\" + settings.clientComp[
                idx] + "\\" + settings.clientShare + "\\" + settings.clientDir + "\\Bin\\stopclient.py")

        except:
            badClients.append(idx)

    if badClients:
        removeBadClients(settings, badClients)


#########################################################################################
def CheckRunningCorrect(logDir):
    fileOutput = defineLastOutputFileName(logDir)
    if ( not os.access(logDir + "\\\\" + fileOutput, os.F_OK) or len(fileOutput) == 0):
        return False
    f = open(logDir + "\\\\" + fileOutput)
    s = f.read();
    f.close()

    if ( s.find('GameClient.Running') >= 0 ):
        return True
    else:
        return False


#########################################################################################
def PrepareSession(settings, iteration):
    heroFile = None
    if os.path.isfile("cfg\\hero.cfg"):
        heroFile = "cfg\\hero.cfg"
    if os.path.isfile("cfg\\hero_" + str(iteration) + ".cfg"):
        heroFile = "cfg\\hero_" + str(iteration) + ".cfg"

    settings.clientHero = []
    for idx in xrange(0, 10):
        settings.clientHero.append("rockman")

    if heroFile:
        heroesLines = GetLinesFromFile(heroFile)
        if len(heroesLines) > 0:
            for idx in xrange(0, 10):
                clhero = heroesLines[idx % len(heroesLines)]
                settings.clientHero[idx] = clhero

    for idx in xrange(0, 10):
        PrintMessage("Client hero %r %r " % (settings.clientHero[idx], idx))

    botsFile = None
    if os.path.isfile("cfg\\bots.cfg"):
        botsFile = "cfg\\bots.cfg"
    if os.path.isfile("cfg\\bots_" + str(iteration) + ".cfg"):
        botsFile = "cfg\\bots_" + str(iteration) + ".cfg"

    botsLines = []
    if botsFile:
        botsLines = GetLinesFromFile(botsFile)
    else:
        botsLines.append("//use default")

    badClients = []
    for idx in xrange(0, settings.clients):
        try:
            cfgDir = "\\\\" + settings.clientComp[
                idx] + "\\" + settings.clientShare + "\\" + settings.clientDir + "\\Profiles"
            clientBotsFile = open(cfgDir + "\\bots.cfg", "w")
            clientBotsFile.writelines(botsLines)
            clientBotsFile.close()

            logDir = "\\\\" + settings.clientComp[
                idx] + "\\" + settings.clientShare + "\\" + settings.clientDir + "\\Bin\\" + clientLogsDir + "\\"
            CleanDir(logDir)
        except:
            badClients.append(idx)

    if badClients:
        removeBadClients(settings, badClients)


#########################################################################################
def StartClient(iteration, settings, mode, idx, reconnect, block):
    cfgDir = "\\\\" + settings.clientComp[idx] + "\\" + settings.clientShare + "\\" + settings.clientDir + "\\Profiles"
    if not os.path.isdir(cfgDir):
        return invalidPid

    pidFileName = "\\\\" + settings.clientComp[
        idx] + "\\" + settings.clientShare + "\\" + settings.clientDir + "\\Bin\\pid.txt"
    RemoveFile(pidFileName)
    cfgDir = "\\\\" + settings.clientComp[idx] + "\\" + settings.clientShare + "\\" + settings.clientDir + "\\Profiles"
    autoexecFile = open(cfgDir + "\\autoexec.cfg", "w")
    autoexecFile.write("login " + settings.userNamePrefix + str(idx) + " " + settings.userHeloWorld + "\n")
    if settings.useSkins:
        autoexecFile.write("use_random_skins 1\n")
    if settings.useTestTalentSet:
        autoexecFile.write("use_test_talentset 1\n")

    playersCount = min(settings.clients, mode.playersCount)
    if reconnect:
        sessionId = iteration + 1
        autoexecFile.write(
            "custom_game_reconnect " + str(sessionId) + " " + str((idx + 1) % 2) + " " + settings.clientHero[
                idx] + "\n")
    elif idx == 0:
        #autoexecFile.write( "custom_game_create " + str(playersCount) + " " + mode.sessionMap + "\n" )
        autoexecFile.write(
            "custom_game_create " + str(mode.playersCount) + " " + mode.sessionMap + " " + str(playersCount) + "\n")
    else:
        autoexecFile.write("custom_game_join\n")

    autoexecFile.write("exec hero.cfg\n")
    autoexecFile.write("exec bots.cfg\n")

    autoexecFile.write("add_ai self " + mode.aiFlags + "\n")
    if idx == playersCount - 1:
        autoexecFile.write("add_ai bots " + mode.aiFlags + "\n")
        if not settings.timeScale in ["", "1.0", "1"]:
            # timescale must be after add_ai to be executed on session start
            autoexecFile.write("timescale " + settings.timeScale + "\n")
    autoexecFile.close()

    heroFile = open(cfgDir + "\\hero.cfg", "w")
    heroFile.write("custom_game_settings " + str((idx + 1) % 2) + " " + settings.clientHero[idx] + "\n")
    heroFile.close()

    clientDir = settings.clientDrive + "\\" + settings.clientDir + "\\Bin"
    if block:
        PrintMessage("Start block!")
        PSExecRun(["-w", clientDir, "\\\\" + settings.clientComp[idx], "python", clientDir + "\\startclient.py"],
                  settings.runInBackground[idx])
    else:
        PrintMessage("Start non block!")
        PSExecRun(["-d", "-w", clientDir, "\\\\" + settings.clientComp[idx], "python", clientDir + "\\startclient.py"],
                  settings.runInBackground[idx])

    wait(settings.clientWait)

    if os.path.isfile(pidFileName):
        f = open(pidFileName, "r")
        pid = f.read()
        f.close()
        PrintMessage("Start client", idx, "with pid", pid, "OK")
    else:
        pid = invalidPid
        PrintMessage("Start client", idx, "FAIL")

    return int(pid)


#########################################################################################
def SendCollectedLogs(settings):
    outputMessage = "results-" + datetime.datetime.now().strftime("%Y.%m.%d-%H.%M.%S-") + version + "\n"
    outputMessage += "+++++++++++++++++Assertions+++++++++++++++++\n"

    for i in Assertions.keys():
        outputMessage += ("-------------%s-----------\n" % i)
        for j in Assertions[i].keys():
            outputMessage += ("for client %i, iter %i : %s times\n" % ( j[0], j[1], Assertions[i][j] ))

    outputMessage += "+++++++++++++++++Datas+++++++++++++++++\n"
    for i in Datas.keys():
        outputMessage += ("-------------%s-----------\n" % i)
        for j in Datas[i].keys():
            outputMessage += ("for client %i, iter %i : %s times\n" % ( j[0], j[1], Datas[i][j] ))

    outputMessage += "+++++++++++++++++Exceptions+++++++++++++++++\n"
    for i in Exceptions.keys():
        outputMessage += ("-------------%s-----------\n" % i)
        for j in Exceptions[i].keys():
            outputMessage += ( "for client %i, iter %i : %s times\n" % ( j[0], j[1], Exceptions[i][j] ))

    outputMessage += "+++++++++++++++++Asyncs+++++++++++++++++\n"
    for i in Asyncs.keys():
        outputMessage += ("-------------%s-----------\n" % i)
        for j in Asyncs[i].keys():
            outputMessage += ("for client %i, iter %i : %s times\n" % ( j[0], j[1], Asyncs[i][j] ))

    SendMail("Report", outputMessage, settings)


#########################################################################################
def defineLastOutputFileName(logDir):
    if not os.path.isdir(logDir):
        return ""

    lastDir = ""
    lastTime = 0

    for dirn in os.listdir(logDir):
        if lastTime < os.path.getctime(os.path.join(logDir, dirn)):
            lastTime = os.path.getctime(os.path.join(logDir, dirn))
            lastDir = dirn

    patternOutput = r"^PW-[A-Za-z0-9\.]+-([0-9\.]+-){3}output.txt$"
    patternOutput_re = re.compile(patternOutput)
    lst = []

    for name in os.listdir(os.path.join(logDir, lastDir)):
        if ( patternOutput_re.match(name) ):
            lst.append(os.path.join(lastDir, name))

    lst.sort()
    if (len(lst) > 0):
        return lst[len(lst) - 1]
    else:
        return ""


#########################################################################################
def StopClientsAndCollectLogs(settings, mode, iteration):
    playersCount = min(settings.clients, mode.playersCount)
    PrintMessage("StopClientsAndCollectLogs %r" % mode.playersCount)
    for idx in xrange(0, playersCount):
        if settings.clientsPIDs[idx] != invalidPid:
            stopClient(settings, idx)
            wait(15)
            logDir = "\\\\" + settings.clientComp[
                idx] + "\\" + settings.clientShare + "\\" + settings.clientDir + "\\Bin\\" + clientLogsDir
            PrintMessage("StopClientsAndCollectLogs %r" % logDir)
            CollectLogsError(logDir, idx, iteration)

            configDir = "\\\\" + settings.clientComp[
                idx] + "\\" + settings.clientShare + "\\" + settings.clientDir + "\\Profiles"

            ZipFiles(logDir, idx, iteration, settings, version, configDir)
        else:
            PrintMessage("StopClientsAndCollectLogs invalidPid %r %r" % (settings.clientsPIDs[idx], invalidPid))


#########################################################################################
def CollectServerReplay(settings, iteration):
    PrintMessage("Archiving replay...")
    replayDir = "\\\\" + settings.serverComp + "\\" + settings.serverShare + "\\" + settings.serverDir + "\\Bin\\" + serverReplayDir
    if not os.path.isdir(replayDir):
        PrintMessage("Archiving replay failed, wrong dir!")
        return
    if not os.listdir(replayDir):
        PrintMessage("Archiving replay failed, no replay!")
        return
    if ( os.access(settings.ZipDir, os.F_OK) == False ):
        os.mkdir(settings.ZipDir)
    zipFileName = settings.ZipDir + "\\" + datetime.datetime.now().strftime(
        "%Y.%m.%d-%H.%M.%S-") + version + "-replay-iter-" + str(iteration) + ".zip"
    zf = ZipFile(zipFileName, mode='w')
    for name in os.listdir(replayDir):
        zf.write(replayDir + "\\" + name, name)
    zf.close()
    CleanDir(replayDir)
    PrintMessage("Archiving replay OK")


#########################################################################################
def CollectServerLogs(settings, iteration):
    PrintMessage("Archiving server logs...")
    logsDir = "\\\\" + settings.serverComp + "\\" + settings.serverShare + "\\" + settings.serverDir + "\\Bin\\" + serverLogsDir
    if not os.path.isdir(logsDir):
        PrintMessage("Archiving server logs failed, wrong dir!")
        return
    if not os.listdir(logsDir):
        PrintMessage("Archiving server logs failed, no replay!")
        return
    if ( os.access(settings.ZipDir, os.F_OK) == False ):
        os.mkdir(settings.ZipDir)
    zipFileName = settings.ZipDir + "\\" + datetime.datetime.now().strftime(
        "%Y.%m.%d-%H.%M.%S-") + version + "-serverlogs-iter-" + str(iteration) + ".zip"
    zf = ZipFile(zipFileName, mode='w')
    for name in os.listdir(logsDir):
        zf.write(logsDir + "\\" + name, name)
    zf.close()
    CleanDir(logsDir)
    PrintMessage("Archiving server logs OK")


#########################################################################################
def StartTest(settings, mode, iteration):
    PrintMessage("Prepare session:", iteration)
    PrepareSession(settings, iteration)
    PrintMessage("Prepare session OK")
    PrintMessage("Session map =", mode.sessionMap)

    playersCount = min(settings.clients, mode.playersCount)
    settings.clientsPIDs = [invalidPid] * playersCount
    allClientsStarted = True
    for idx in xrange(0, playersCount):
        if IsStopRequested():
            break
        PrintMessage("Start client:", idx)
        block = False
        if idx == playersCount - 1 and mode.reconnectTime == 0:
            block = True
        settings.clientsPIDs[idx] = StartClient(iteration, settings, mode, idx, False, block)
        if settings.clientsPIDs[idx] == invalidPid:
            allClientsStarted = False
            break

    if not IsStopRequested() and allClientsStarted:
        wait(settings.WaitForConnecting)

    if not IsStopRequested():
        sessionStarted = False
        if allClientsStarted:
            for idx in xrange(0, playersCount):
                if (CheckRunningCorrect("\\\\" + settings.clientComp[
                    idx] + "\\" + settings.clientShare + "\\" + settings.clientDir + "\\Bin\\" + clientLogsDir) ):
                    sessionStarted = True
                    break

        if ( not sessionStarted):
            PrintMessage("Session starting FAIL")
            StopClientsAndCollectLogs(settings, mode, iteration)
            SendMail("Session starting FAIL", "Session starting FAIL", settings)
            return False

        PrintMessage("Session starting OK")

        if mode.reconnectTime > 0:
            for rn in xrange(0, mode.reconnectCount):
                wait(mode.reconnectTime)
                if IsStopRequested():
                    break
                clientToReconnect = random.randint(0, playersCount - 2)
                PrintMessage("Kill client", clientToReconnect, "with pid", settings.clientsPIDs[clientToReconnect])
                stopClient(settings, clientToReconnect)
                PrintMessage("Kill OK")
                wait(10)
                PrintMessage("Reconnecting client", clientToReconnect)
                block = False
                if rn == mode.reconnectCount - 1:
                    block = True
                settings.clientsPIDs[clientToReconnect] = StartClient(iteration, settings, mode, clientToReconnect,
                                                                      True, block)

    if not IsStopRequested():
        wait(settings.killWait)
    else:
        PrintMessage("Stopping session due to external request...")

    StopClientsAndCollectLogs(settings, mode, iteration)
    CollectServerReplay(settings, iteration)
    CollectServerLogs(settings, iteration)

    return True


#########################################################################################
def IterationsTest(settings):
    done = True
    currentMode = 0
    timesBeforeNextMode = 0
    if settings.modesCount == 1:
        timesBeforeNextMode = settings.times + 1  # We won't change mode
    else:
        timesBeforeNextMode = settings.modes[currentMode].times

    PrintMessage("Total iterations:", settings.times)
    for iteration in xrange(0, settings.times):
        PrintMessage("Start iteration:", iteration)
        if ( not StartTest(settings, settings.modes[currentMode], iteration) ):
            counter = settings.AttemptToConnect - 1
            while ( counter > 0 and (not StartTest(settings, settings.modes[currentMode], iteration)) ):
                counter -= 1
            if counter <= 0:
                PrintMessage("Autotest failed on iteration", iteration)
                done = False
                break
        PrintMessage("End iteration:", iteration)
        if IsStopRequested():
            PrintMessage("Stopping autotest due to external request...")
            break
        timesBeforeNextMode -= 1
        if timesBeforeNextMode == 0:
            currentMode += 1
            if currentMode == settings.modesCount:
                currentMode = 0
            timesBeforeNextMode = settings.modes[currentMode].times

    SendCollectedLogs(settings)

    StopServer(settings)
    if (not done and not IsStopRequested()):
        if ( iteration == 0 ):
            waitCheckStop(settings.WaitForGettingVersion)
            if (GetVersion(settings)):
                StartServer(settings)
                if settings.udpEnable:
                    StartMMServer(settings)
                PrintMessage("Prepare clients common settings...")
                prepareClientsCommonSettings(settings)
                PrintMessage("Prepare clients common settings OK")
        else:
            StartServer(settings)
            if settings.udpEnable:
                StartMMServer(settings)
            PrintMessage("Prepare clients common settings...")
            prepareClientsCommonSettings(settings)
            PrintMessage("Prepare clients common settings OK")

    return done

#########################################################################################
# main
#########################################################################################

if __name__ == "__main__":
    foutput = CreateLog()
    settings = Settings("settings.txt")
    RemoveFile(stopAutotestFileName)

    PrintMessage("Start autotest")
    PrintMessage("Total clients:", settings.clients)
    PrintMessage("Get IPs...")
    settings.getIPs()
    PrintMessage("Server name " + settings.serverComp + " ip " + settings.serverIp)
    for idx in xrange(0, settings.clients):
        PrintMessage("Client" + str(idx) + " name " + settings.clientComp[idx] + " ip " + settings.clientIp[idx])
    PrintMessage("Get IPs OK")
    for idx in range(0, settings.clients):
        stopClient(settings, idx)
    if GetVersion(settings):
        StartServer(settings)
        if settings.udpEnable:
            StartMMServer(settings)

        PrintMessage("Prepare clients common settings...")
        prepareClientsCommonSettings(settings)
        PrintMessage("Prepare clients common settings OK")

        attempts = 3  # временно. Возможно вынести в конфиг
        while ( attempts > 0 and not IsStopRequested() ):
            if ( IterationsTest(settings) ):
                break
            attempts -= 1

    PrintMessage("End autotest")
    RemoveFile(stopAutotestFileName)
    foutput.close()

