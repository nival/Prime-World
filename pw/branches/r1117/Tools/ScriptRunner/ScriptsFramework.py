import threading
import sys
import os
import SkypeInterface

ScriptNames = []
ScriptNames.append('C:\\Projects\\PF_trunk\\Tools\\ZDATAChecker\\ZdataDailyCheck.py')
ScriptNames.append('C:\\Projects\\PF_trunk\\Tools\\SymbolServer\\updateSymbols.py')

class ScriptThread(threading.Thread):
    '''Separate thread to run one script
    Pass the full python script file name to constructor, then call start()
    '''
    def __init__(self, scrName):
        self.scrName = scrName
        threading.Thread.__init__(self)
        self._stop = threading.Event()

    def run ( self ):
        os.system("start /WAIT cmd /k python " + self.scrName)

    def stop (self):
        self._stop.set()

exitFlag = False
def cmdExit():
    global exitFlag
    exitFlag = True

ChatCommands = {"do exit" : cmdExit }
def onMessage(message, status):
    if status == 'RECEIVED':
        cmd = ChatCommands.get(message.Body, None)
        if cmd:
            message.Chat.SendMessage("Doing command %s" % message.Body)
            cmd()
        if len(message.Chat.Members) == 2:
            if message.FromDisplayName == "Matthew":
                message.Chat.SendMessage("(bow) Hello, Masta!")
            else:
                message.Chat.SendMessage("I'm doing fine ;)")

#scriptLaunchTime = time.time()
def main():
    #start skype
    skype = SkypeInterface.SkypeManager(onMessage)

    #start threads
    scrThreads = []
    for scrName in ScriptNames:
        scr = ScriptThread(scrName)
        scr.start()
        scrThreads.append(scr)

    #take care of running threads
    while(len(scrThreads) > 0):
        if exitFlag:
            for thr in scrThreads:
                thr.stop()
                skype.sendMessage("Script: \"%s\" was closed manually" % thr.scrName)
            break

        for thr in scrThreads:
            if thr.is_alive() == False:
                skype.sendMessage("Script: \"%s\" was closed" % thr.scrName)
                scrThreads.remove(thr)

    skype.sendMessage("Watching script finished")

if __name__ == "__main__":
    main()