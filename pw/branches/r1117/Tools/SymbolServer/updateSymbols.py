#-*- coding: cp1251 -*-
import pysvn
import sys
import os
import time
#import shutil
import SyncF as SyncFolders
# Import the email modules we'll need
import smtplib
from email.mime.text import MIMEText

#Skype based error reports
try:
    sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), "../ScriptRunner")))
    from SkypeInterface import SkypeManager
except:
    class SkypeManager():
        def __init__(self):
            pass
        def sendMessage(self, msg):
            print msg

NivalRepository = "https://svn.SITE/pw/branches/publish"
LocalNivalSVNFold = "C:/Projects/pf_nival_branches_publish"
LocalDiSVNFold = "C:/Projects/pf_di_branches_publish"
Path_to_Symbol_Server = "\\\\Primat_server\\public\\_PROJECTS_\\Symbols"
MappingTempl = "Nival revision = "
StartRevisionNum = 17150

Mail_From = "TestSrv@d-inter.ru"
Mail_To = ["matthew@d-inter.ru", "oleg@d-inter.ru", "eugbel@d-inter.ru"]

#create svn client
client = pysvn.Client()

def rmDirRecursive_svn(dirName):
    ld = os.listdir(dirName)
    for f in ld:
        fileName = os.path.join(dirName, f)
        if os.path.isdir(fileName):
            if f != ".svn":
                rmDirRecursive_svn(fileName)
    client.remove(dirName)
    return 1

def mkDirCall_svn(dirName):
    client.add(path=dirName, recurse=False)
    return 0
def rmvDirCall_svn(dirName):
    rmDirRecursive_svn(dirName)
    return 1
def mkFileCall_svn(fName):
    client.add(fName)
    return 0
def rmvFileCall_svn(fName):
    client.remove(fName)
    return 1
def updFileCall_svn(fName):
    return 0
svnCallList = [mkDirCall_svn, rmvDirCall_svn, mkFileCall_svn, rmvFileCall_svn, updFileCall_svn]

def get_login_Nival(realm, username, may_save):
    return True, "dinter", "EOf7FxnFxn", True

def get_login_DI(realm, username, may_save):
    return True, "builder", "qwerty", True

def ssl_server_trust_prompt( trust_dict ):
    return True, 100, True

OneSuccesfullIteration = False
rev = 0
startRev = 0

def main():
    global client, OneSuccesfullIteration, rev, startRev

    client.callback_ssl_server_trust_prompt = ssl_server_trust_prompt
    client.callback_get_login = get_login_Nival

    #if we haven't own repository
    if os.path.exists(LocalDiSVNFold) == False:
       return LocalDiSVNFold + "doesn't exist"

    #first cleanup
    client.cleanup(LocalNivalSVNFold)
    client.cleanup(LocalDiSVNFold)

    currentRevision = client.info2(NivalRepository, revision=pysvn.Revision(pysvn.opt_revision_kind.head), recurse=False)[0][1].rev.number
    lastRevision = client.info2(LocalNivalSVNFold, revision=pysvn.Revision(pysvn.opt_revision_kind.base), recurse=False)[0][1].rev.number
    client.callback_get_login = get_login_DI
    diRev = client.info2(LocalDiSVNFold, revision=pysvn.Revision(pysvn.opt_revision_kind.base), recurse=False)[0][1].rev.number
    client.callback_get_login = get_login_Nival

    #define last checkined nival revision
    if diRev == 0:
        lastRevision = StartRevisionNum
    else:
        #find last commited revison by automatically generated commit messages
        client.update(LocalDiSVNFold)
        log_messages = client.log(LocalDiSVNFold, revision_start = pysvn.Revision( pysvn.opt_revision_kind.head ), revision_end = pysvn.Revision( pysvn.opt_revision_kind.number, diRev - 1))
        for logMsg in log_messages:
            try:
                lastRevision = int(logMsg.message[len(MappingTempl) : len(MappingTempl)+ 5]) + 1
                break
            except ValueError:
                lastRevision = -1
        if lastRevision == -1:
            lastRevision = StartRevisionNum

    rev = lastRevision
    startRev = lastRevision

    #if we haven't nival temporary storage
    if os.path.exists(LocalNivalSVNFold) == False:
        return LocalNivalSVNFold + "doesn't exist"

    #copy revisions one by one
    log_messages = client.log(NivalRepository, revision_start = pysvn.Revision( pysvn.opt_revision_kind.head ), revision_end = pysvn.Revision( pysvn.opt_revision_kind.number, lastRevision))
    log_messages.reverse()

    for log in log_messages:
        rev = log.revision.number
        print "\n-----------------------------------------------------\nProcessing Nival revision = " + str(rev)
        # Get build from Nival SVN
        sys.stdout.write("\nUpdating from Nival repos... ")
        client.update(LocalNivalSVNFold, revision=pysvn.Revision(pysvn.opt_revision_kind.number, rev), recurse=True)
        sys.stdout.write("ok")
        # Synchronize changes with our local folder
        sys.stdout.write("\nSynchronizing folders... ")
        SyncFolders.SyncF(LocalNivalSVNFold, LocalDiSVNFold, True, True, [], svnCallList)
        sys.stdout.write("ok")
        # Commit new build to our SVN
        sys.stdout.write("\nCommitting to DI repos... ")
        diRev = client.checkin(LocalDiSVNFold, MappingTempl + str(rev))
        sys.stdout.write("ok")
        # index symbols
        sys.stdout.write("\nProcessing symbols... ")
        os.chdir(LocalDiSVNFold)
        os.system("svnindex")
        os.system("symstore add /r /f ./*.* /s " + Path_to_Symbol_Server + " /t 'PF'")
        sys.stdout.write("ok")
        OneSuccesfullIteration = True

    return "\nOperation complete!"

def sendNotifications(subj, report):
    msg = MIMEText(report)
    msg['Subject'] = subj
    msg['From'] = Mail_From
    msg['To'] = Mail_To[0]

    s = smtplib.SMTP("10.0.0.3")
    s.sendmail(Mail_From, Mail_To, msg.as_string())
    s.quit()

    print "ok"

if __name__ == "__main__":
    eh = SkypeManager()
    while (1):
        print "\n\nLaunching script...\n----------------------\n\n"
        msg = ""
        while (1):
            try:
                OneSuccesfullIteration = False
                msg = main()
                break
            except Exception as e:
                if OneSuccesfullIteration == False:
                    eh.sendMessage("[svn/sym] Symbols extraction FAILED. Rev = " + str(rev) + "\n" + e.args[0])
                    print "Error!\n-----------------\n"
                    print e.args[0]
                    print "Notifications were sent via skype.."
                    break
        print msg
        print "\nSleeping from: " + time.strftime("%H:%M")
        time.sleep(60*60) #Every 1 hour
