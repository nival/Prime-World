import fnmatch
import os
import re

def matchPatterns(name, patterns, ignored = []):
    for mask in ignored:
        #print "MASK", mask, fnmatch.translate( mask ), name
        if re.match( fnmatch.translate( mask ), name ):
            return None
    for pattern in patterns:        
        if re.match( fnmatch.translate( pattern ), name ):
            return pattern        
    return None        

def collectFiles(path, patterns, ignored = [], recursive=True, add_root=True):
    result = []
    for root, dirs, files in os.walk(path):
        for name in files:
            relativePath = os.path.join( root, name )[len(path)+1:]
            if matchPatterns(relativePath, patterns, ignored):
                value = os.path.join(root, name)
                if not add_root:
                    value = value[len(path)+1:]    
                result.append(value)
        if not recursive:
            break                    
    return result


def fixFile(filename):
    file = open( filename, 'r' )
    fstr = file.read()
    file.close()
    indexstart = fstr.find("/Terrain/Flora/BigTrees")
    while indexstart != -1:
        indexend = fstr.find('\"', indexstart)
        if indexend == -1:
            break
        fstr = fstr[:indexstart] + "/Terrain/Flora/Trees/Spruces/_.TREE" + fstr[indexend:]
        indexstart = fstr.find("/Terrain/Flora/BigTrees", indexend)
    file = open( filename, 'w' )
    file.write(fstr)
    file.close()


def main():
    files = collectFiles('.','*.xdb')
    for file in files:
        if file.find(".ADMP.xdb") != -1 and file.find("svn-base") == -1:
            print file
            fixFile(file)

main()