#-*- coding: cp1251 -*-
import zipfile
import sys
import fileinput
import os
from shutil import move, copy


def main():   
    # decide revision of project   
    revision = $WCREV$
    outFName = "Nival3dPlugin_inst_Win.xpi"

    # patch rdf file
    f = file("update.rdf")
    newlines = []
    for line in f:
        if "<version>" in line:
            line="    <version>0.0.0." + str(revision) + "</version>\n"
        newlines.append(line)
    f.close()
    outfile = file("../deploy/update.rdf", 'w')
    outfile.writelines(newlines)
    outfile.close()
 
    # patch rdf file
    f = file("install.rdf")
    newlines = []
    for line in f:
        if "<em:version>" in line:
            line="    <em:version>0.0.0." + str(revision) + "</em:version>\n"
        newlines.append(line)
    f.close()

    outfile = file("install1.rdf", 'w')
    outfile.writelines(newlines)
    outfile.close()
    
    # open the zip file for writing, and write stuff to it
    myZipFile = zipfile.ZipFile(outFName, "w")
    myZipFile.write("install1.rdf", "install.rdf", zipfile.ZIP_DEFLATED)
    myZipFile.write("license.rtf", "plugins/license.rtf", zipfile.ZIP_DEFLATED)
    os.unlink("install1.rdf")

    # release by default
    if len(sys.argv) > 1:
        myZipFile.write("../../../../_"+sys.argv[1]+"/npDllLoader.dll", "plugins/npDllLoader.dll", zipfile.ZIP_DEFLATED)    
        myZipFile.close()
        move(outFName, "../../../../_"+sys.argv[1]+"/"+outFName)
    else:
        myZipFile.write("../../../../_Release/npDllLoader.dll", "plugins/npDllLoader.dll", zipfile.ZIP_DEFLATED)    
        myZipFile.close()
        move(outFName, "../../../../_Release/"+outFName)
        
    

    print "Operation complete!"
    
if __name__ == "__main__":
    main()