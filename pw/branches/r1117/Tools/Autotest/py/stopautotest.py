# -*- coding: cp1251 -*-
from autotestcommon import *


def StopClients(settings):
    PrintMessage("Stopping clients...")
    for idx in xrange(0, settings.clients):
        fileName = "\\\\" + settings.clientComp[
            idx] + "\\" + settings.clientShare + "\\" + settings.clientDir + "\\Bin\\pid.txt"
        if os.path.isfile(fileName):
            f = open(fileName, "r")
            pid = f.read()
            f.close()
            PrintMessage("Stopping client", idx, "on", settings.clientComp[idx], "with PID", pid)
            stopClient(settings, idx)
    PrintMessage("Stopping clients OK")


PrintMessage("Stop autotest")
PrintMessage("Read config file...")
settings = Settings("settings.txt")
PrintMessage("Read config file OK")
PrintMessage("Total clients:", settings.clients)
PrintMessage("Get IPs...")
settings.getIPs()
PrintMessage("Server name " + settings.serverComp + " ip " + settings.serverIp)
for idx in xrange(0, settings.clients):
    PrintMessage("Client" + str(idx) + " name " + settings.clientComp[idx] + " ip " + settings.clientIp[idx])
PrintMessage("Get IPs OK")

StopServer(settings)
StopClients(settings)

fStopFile = open(stopAutotestFileName, "w")
fStopFile.close()

PrintMessage("Autotest stopped")
