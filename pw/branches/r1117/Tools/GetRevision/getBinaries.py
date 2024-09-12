#-*- coding: cp1251 -*-
import pysvn
import sys
import os.path
import SyncF as SyncFolders

NivalRepository = "https://svn.SITE/pw/branches/publish"
DiSVNRepository = "http://10.0.0.3:49555/svn/svnsymbols"
DiMappingTempl = "Nival revision = "
BrownieName = "brownie"
brownieMsgTempl = "- PF-Trunk-1.0.0."

#create svn client
client = pysvn.Client()

def get_login_Nival(realm, username, may_save):
    return True, "dinter", "EOf7FxnFxn", True

def get_login_DI(realm, username, may_save):
    return True, "builder", "qwerty", True

def ssl_server_trust_prompt( trust_dict ):
    return True, 100, True


def findBuild(revision):
    #find corresponding brownie commit
    log_messages = client.log(NivalRepository, revision_start = pysvn.Revision( pysvn.opt_revision_kind.head ), revision_end = pysvn.Revision( pysvn.opt_revision_kind.number, revision))
    if log_messages == []:
        return -1, -1

    brownieCommentRevNum = -1
    for logMsg in log_messages:
        if logMsg["author"] == BrownieName:
            msgText = logMsg["message"]
            if brownieMsgTempl in msgText:
                try:
                    brownieCommentRevNum = int(msgText[len(brownieMsgTempl) : len(brownieMsgTempl)+ 5])
                    if brownieCommentRevNum <= revision:
                        break
                except ValueError:
                    pass
    return brownieCommentRevNum, logMsg["revision"].number

def findDIsvnRev(nivalRev):
    log_messages = client.log(DiSVNRepository, revision_start = pysvn.Revision( pysvn.opt_revision_kind.head ), revision_end = pysvn.Revision( pysvn.opt_revision_kind.number, 0))
    if log_messages == []:
        return -1, -1

    for logMsg in log_messages:
        msgText = logMsg["message"]
        try:
            msgNivalRev = int(msgText[len(DiMappingTempl) : ])
            if msgNivalRev <= nivalRev:
                break
        except ValueError:
            pass
    return msgNivalRev, logMsg["revision"].number

def main():
    global client

    client.callback_ssl_server_trust_prompt = ssl_server_trust_prompt
    client.callback_get_login = get_login_Nival

    #get command line params
    revision = 0
    if len (sys.argv) < 2:
        print "USAGE: diGetNivalRev.py revision_number [Path]"
        print "Example: diGetNivalRev.py 15339"
        print "Example: diGetNivalRev.py 15339 t:\\build_nival_15399\\"
        print "[Path] should exists!"
        return
    revision = int(sys.argv[1])

    #find Nival revision num
    foundRev, nivalRev = findBuild(revision)
    if foundRev != revision:
        print "Can't find revision = " + str(revision) + " among brownie commits. Nearest found revision = " + str(foundRev)
        return

    #find DI svn revision num
    client.callback_get_login = get_login_DI
    foundRev, diSVNrev = findDIsvnRev(nivalRev)
    if foundRev != nivalRev:
        print "Can't find nival revision = " + str(nivalRev) + " on DI svn"
        return

    symbFold = "build_" + str(revision)
    if len(sys.argv) > 2:
        symbFold = sys.argv[2]

    print "  Revision    = " + str(revision)
    print "  Branches Revision = " + str(nivalRev)
    print "  DI svn Revision   = " + str(diSVNrev)
    print "Getting revision from diSVN..."
    client.export(src_url_or_path=DiSVNRepository, dest_path=symbFold, revision = pysvn.Revision( pysvn.opt_revision_kind.number, diSVNrev))
    print "Revision successfully extracted into folder: " + symbFold

if __name__ == "__main__":
    main()


