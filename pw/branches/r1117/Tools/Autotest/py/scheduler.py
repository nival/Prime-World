# -*- coding: cp1251 -*-
from autotestcommon import *
import threading

# ########################################################################################
def IsStopRequested():
    return os.path.isfile(stopSchedulerFileName)


#########################################################################################
def StartTest():
    call(["autotest.cmd"], shell=True)

#########################################################################################
# main
#########################################################################################

logFileName = "scheduler-log-" + datetime.datetime.now().strftime("%Y.%m.%d-%H.%M.%S") + ".txt"
foutput = open(logFileName, "a")
SetLogFile(foutput)

RemoveFile(stopSchedulerFileName)

PrintMessage("Read config file...")
settings = Settings("settings.txt")
PrintMessage("Read config file OK")

if settings.startTime == "":
    PrintMessage("Start time isn't set! Abort scheduling.")
    sys.exit()

startTime = datetime.datetime.strptime(settings.startTime, "%H:%M")
PrintMessage("Start time is:", startTime.strftime("%H:%M"))
if not settings.stopTime == "":
    stopTime = datetime.datetime.strptime(settings.stopTime, "%H:%M")
    PrintMessage("Stop time is:", stopTime.strftime("%H:%M"))
else:
    PrintMessage("Stop time is:", startTime.strftime("%H:%M"))

isAutotestStarted = False
isStopRequested = False

if settings.stopTime == "" or stopTime < startTime:
    daysDelta = 1
else:
    daysDelta = 0

curTime = datetime.datetime.now()
if curTime.hour > startTime.hour or curTime.hour == startTime.hour and curTime.minute >= startTime.minute:
    curTime = curTime + datetime.timedelta(days=1)
nextStartTime = curTime.replace(hour=startTime.hour, minute=startTime.minute, second=0)

stopSheduler = False

PrintMessage("Autotest will start at", nextStartTime.strftime("%d.%m.%y %H:%M"))

while not stopSheduler:
    curTime = datetime.datetime.now()
    if IsStopRequested():
        if not isStopRequested:
            PrintMessage("Scheduler stop requested...")
        isStopRequested = True
    if not isAutotestStarted:
        if isStopRequested:
            stopSheduler = True
        else:
            if curTime >= nextStartTime:
                PrintMessage("Starting autotest...")
                threadTest = threading.Thread(target=StartTest)
                threadTest.start()
                PrintMessage("Starting autotest finished")
                isAutotestStarted = True
                if not settings.stopTime == "":
                    nextStopTime = curTime.replace(hour=stopTime.hour, minute=stopTime.minute, second=0)
                else:
                    nextStopTime = curTime.replace(hour=startTime.hour, minute=startTime.minute, second=0)
                if daysDelta > 0:
                    nextStopTime = nextStopTime + datetime.timedelta(days=1)
                PrintMessage("Autotest will stop at", nextStopTime.strftime("%d.%m.%y %H:%M"))
    else:
        if curTime >= nextStopTime or isStopRequested:
            PrintMessage("Stopping autotest...")
            call(["stopautotest.cmd"], shell=True)
            threadTest.join()
            PrintMessage("Stopping autotest finished")
            isAutotestStarted = False
            nextStartTime = curTime.replace(hour=startTime.hour, minute=startTime.minute, second=0)
            if daysDelta == 0:
                nextStartTime = nextStartTime + datetime.timedelta(days=1)
            if not isStopRequested:
                PrintMessage("Autotest will start at", nextStartTime.strftime("%d.%m.%y %H:%M"))
    if not stopSheduler:
        wait(5, True)

PrintMessage("Scheduler stopped")
RemoveFile(stopSchedulerFileName)
foutput.close()
