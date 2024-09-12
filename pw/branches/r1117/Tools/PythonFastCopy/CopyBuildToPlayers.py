"""
This script copy build to different shared folders in local network
It used for daily test

@Company Driver-Inter
"""

import os

import Config
import SyncFolders

# ---------------------------------------------------------------------
def ForceSync(destPath):
    workList = [
        ('', False, False, []),
        ('Bin', True, True, ['*.txt', '*.log', '*.rpl', '*.dmp']),
        ('Data', True, True, []),
        ('Profiles', True, True, ['private.cfg']),
        ('Src', False, True, ['*.sln', '*.ncb', '*.cs', '*.xslt', '*.config']),
        ('Src\\_Release', False, True, ['*.obj', '*.htm', '*.pdb', '*.meta', '*.lib', '*.res', '*.manifest', '*.exp', '*.ilk']),
        ('Src\\_Debug', False, True, ['*.obj', '*.htm', '*.pdb', '*.meta', '*.lib', '*.res', '*.manifest', '*.exp', '*.ilk'])
    ]

    if not os.path.exists:
        print "ERROR: Path not found! " + destPath
        return
    
    for directory, reqursive, purge, ignore in workList:
           sourceDir = os.path.join(Config.pathToBuild, directory);
           targetDir = os.path.join(destPath, directory);
           copier = SyncFolders.SyncFolders(sourceDir, targetDir, reqursive, purge, ignore)
           copier.run();

# ---------------------------------------------------------------------
def main():
    print "Copy build to players. Ver. 1.0. Author Oleg Talalov"
    print "The build from " + '"' + Config.pathToBuild + '"' + " will be uploaded to " + str(len(Config.userList)) + " player(s)."
    
    numberOfUsers = len(Config.userList)
    for i in range(numberOfUsers):
        name, path = Config.userList[i]
        print "Start synchonization with " + name
        print "Destination path is " + path
        ForceSync(path);
        

# ---------------------------------------------------------------------
if __name__ == "__main__":
    main();
