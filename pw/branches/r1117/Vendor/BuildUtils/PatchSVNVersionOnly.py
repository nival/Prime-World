import pysvn
import os
PFFolder = os.path.abspath("..") #path relative to Src folder
targetXSLT = os.path.join(PFFolder, "Src\\PF_Game\\Version.h.xslt")
targetXML = os.path.join(PFFolder, "Src\\PF_Game\\Version.h")
pattern = "#define VERSION_REVISION	0"
replacePatternWith = "#define VERSION_REVISION "


#create svn client
client = pysvn.Client()

def patchFile(fileName):
    currentRevision = client.info2(PFFolder, revision=pysvn.Revision(pysvn.opt_revision_kind.base), recurse=False)[0][1].rev.number
    file = open(fileName)
    fLines = file.readlines()
    newLines = []
    for line in fLines:
        if pattern in line:
            newLines.append(line.replace(pattern, replacePatternWith + str(currentRevision)))
        else:
            newLines.append(line)
    file.close()
    file = open(fileName, "w")
    for line in newLines:
        file.write(line)
    file.close()
    return currentRevision

#import sys
#from xml.xslt.Processor import Processor

def main():
    rev = patchFile(targetXML)
    print "Done! Revision " + str(rev) + " writed"

if __name__ == "__main__":
    main()
