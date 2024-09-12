import filecmp
import os
import shutil
import time
import Config

def main():
    
    # Make folder on server
    folderName = time.strftime("%Y_%m_%d-%H.%M")
    fullPath   = os.path.join(Config.pathToLogs, folderName)

    if not os.path.exists(fullPath):
        try:
            os.makedirs(fullPath)
        except Exception, e:
            print e
            return None
        
    for name, userPath in Config.userList:
        print "Copy logs from ", name
        targetDir = os.path.join(fullPath, name)
        if not os.path.exists(targetDir):
            try:
                os.makedirs(targetDir)
            except Exception, e:
                print e, "Unable to create target directory"
                continue
        sourceDir = os.path.join(userPath, "Bin\\log")
        if not os.path.exists(sourceDir):
            print "Source dir not found ", sourceDir
            continue
        dcmp = filecmp.dircmp(sourceDir, targetDir)
        for f in dcmp.left_only:
            fullf = os.path.join(sourceDir, f)
            if os.path.isfile(fullf):
                try:
                    shutil.copy(fullf, targetDir)
                except (IOError, OSError), e:
                    print e
                ### PURGE LOGS
                try:
                    os.remove(fullf)                            
                except OSError, e:
                    print e
        print "complete"
    return None

if __name__=="__main__":
    main()
