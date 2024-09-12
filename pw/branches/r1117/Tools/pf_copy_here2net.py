""" pf_net_copy.py -
    (some source code was taken from pyrobocopy.py)
    Company: Driver Inter
"""

import filecmp
import os
import re
import shutil
import stat
import sys
import time

class SyncFolders:
    def __init__(self, sourceDir, targetDir, recursive = True, purge = True, ignore = []):
        self.__sourceDir = sourceDir
        self.__targetDir = targetDir

        self.__makeTarget = True
        self.__purge      = purge
        self.__forceCopy  = True
        self.__recursive  = recursive;
        self.__createDirs = self.__recursive;
        self.__ignoreMask = ignore;
        self.__ignoreRe   = [];

        self.__startTime       = 0
        self.__endTime         = 0
        self.__numDirs         = 0
        self.__numDelFiles     = 0
        self.__numDelFolders   = 0
        self.__numCopyingFiles = 0
        self.__numUpdates      = 0

        for s in self.__ignoreMask:
            rs = s.replace('.', '\.', 100);
            rs = rs.replace('*', '.*', 100);
            rs = rs.replace('?', '.',  100);
            rs = rs + '\Z';
            reg = re.compile(rs);
            self.__ignoreRe.append(reg);

    def run(self):
        """ Main routine """
        self.__startTime = time.time();

        if not os.path.isdir(self.__sourceDir):
            print 'Unable to open source directory ', self.__sourceDir
            return None
        if not os.path.isdir(self.__targetDir):
            if self.__makeTarget:
                print 'Create target directory ', self.__targetDir
                try:
                    os.makedirs(self.__targetDir)
                except Exception, e:
                    print e
                    return None

        self.__dowork(self.__sourceDir, self.__targetDir, self.__copy, self.__update)

        self.__endTime   = time.time();

    def __dowork(self, sourceDir, targetDir, copyfunc, updatefunc):
        self.__numDirs += 1;

        dcmp = filecmp.dircmp(sourceDir, targetDir, ['.svn', 'log'])

        # Remove files and folder which present only in target directory
        if self.__purge:
            for f in dcmp.right_only:
                fullf = os.path.join(targetDir, f)
                try:
                    if os.path.isfile(fullf):
                        try:
                            os.remove(fullf)                            
                            self.__numDelFiles += 1
                        except OSError, e:
                            print e
                    elif os.path.isdir(fullf):
                        try:
                            shutil.rmtree(fullf, True)
                            self.__numDelFolders += 1
                        except shutil.Error, e:
                            print e
                except Exception, e:
                    print e
                    continue

        for f in dcmp.left_only:
            try:
               st = os.stat(os.path.join(sourceDir, f))
            except os.error:
                continue

            if stat.S_ISREG(st.st_mode):
                # This is regular file'
                if self.__ignore(f):
                    continue
                if copyfunc: copyfunc(f, sourceDir, targetDir)
            elif stat.S_ISDIR(st.st_mode):
                fulld1 = os.path.join(sourceDir, f)
                fulld2 = os.path.join(targetDir, f)

                if self.__createDirs:
                    try:
                        os.makedirs(fulld2)
                    except Exception, e:
                        print e
                        # jump to next file/dir in loop since this op failed
                        continue
                    
                # Call tail recursive
                if os.path.exists(fulld2) and self.__recursive:
                    self.__dowork(fulld1, fulld2, copyfunc, updatefunc)

        # common files/directories
        for f in dcmp.common:
            try:
                st = os.stat(os.path.join(sourceDir, f))
            except os.error:
                continue

            if stat.S_ISREG(st.st_mode):
                if self.__ignore(f):
                    if self.__purge:
                        fullf = os.path.join(targetDir, f);
                        try:
                            os.remove(fullf)                            
                            self.__numDelFiles += 1
                        except OSError, e:
                            print e
                    continue
                if updatefunc: updatefunc(f, sourceDir, targetDir)
            elif stat.S_ISDIR(st.st_mode):
                fulld1 = os.path.join(sourceDir, f)
                fulld2 = os.path.join(targetDir, f)
                
                # Call tail recursive
                if self.__recursive:
                    self.__dowork(fulld1, fulld2, copyfunc, updatefunc)

        # if Target directory is empty: kill it
        if len(os.listdir(targetDir)) == 0:
            try:
                shutil.rmtree(targetDir, True)
            except shutil.Error, e:
                print e
            

    def __ignore(self, fileName):
        for r in self.__ignoreRe:
            if r.match(fileName):
                return True
        return False
                
    def __copy(self, fileName, sourceDir, targetDir):
        sourcefile = os.path.join(sourceDir, fileName)
        print 'Copying file', fileName, ' from ', sourceDir
        try:
            shutil.copy(sourcefile, targetDir)
            self.__numCopyingFiles += 1
        except (IOError, OSError), e:
            print e

    def __cmptimestamps(self, filest1, filest2):
        """ Compare time stamps of two files and return True
        if file1 (source) is more recent than file2 (target) """
        return ((filest1.st_mtime > filest2.st_mtime) or (filest1.st_ctime > filest2.st_mtime) or (filest1.st_size != filest2.st_size))

    def __update(self, fileName, sourceDir, targetDir):
        file1 = os.path.join(sourceDir, fileName)
        file2 = os.path.join(targetDir, fileName)

        try:
            st1 = os.stat(file1)
            st2 = os.stat(file2)
        except os.error:
            return -1


        if self.__cmptimestamps( st1, st2 ):
            print 'Updating file ', file2 # source to target
            try:
                if self.__forceCopy:
                    os.chmod(file2, 0666)

                try:
                    shutil.copy(file1, file2)
                    self.__numUpdates += 1
                    return 0
                except (IOError, OSError), e:
                    print e
                    #self.__numupdsfld += 1
                    return -1

            except Exception, e:
                    print e
                    return -1
        return 0

def SyncF(sourceFolder, targetFolder, recursive, purge, ignore):
    copier = SyncFolders(sourceFolder, targetFolder, recursive, purge, ignore);
    copier.run();

if __name__ == '__main__':
    
    targetDir = "\\\\Primat_server\\public\\_PROJECTS_\\PrimalForces\\NetGame\\"
    sourceDir = os.path.join(os.getcwd(), "..")
    
    SyncF(sourceDir, targetDir, False, False, [])
    SyncF(os.path.join(sourceDir,'Bin'), os.path.join(targetDir, 'Bin'), True, True, ['*.txt', '*.log', '*.rpl', '*.dmp'])
    SyncF(os.path.join(sourceDir,'Data'), os.path.join(targetDir, 'Data'), True, True, [])
    SyncF(os.path.join(sourceDir,'Profiles'), os.path.join(targetDir, 'Profiles'), True, True, ['private.cfg'])
    SyncF(os.path.join(sourceDir,'Src'), os.path.join(targetDir, 'Src'), False, True, ['*.sln', '*.ncb', '*.cs', '*.xslt', '*.config'])
    SyncF(os.path.join(sourceDir,'Src\\_Release'), os.path.join(targetDir, 'Src\\_Release'), False, True, ['*.obj', '*.htm', '*.pdb', '*.meta', '*.lib', '*.res', '*.manifest', '*.exp', '*.ilk'])
    SyncF(os.path.join(sourceDir,'Src\\_Debug'), os.path.join(targetDir, 'Src\\_Debug'), False, True,     ['*.obj', '*.htm', '*.pdb', '*.meta', '*.lib', '*.res', '*.manifest', '*.exp', '*.ilk'])

    print "Sync finished"