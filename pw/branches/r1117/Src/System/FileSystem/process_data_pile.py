import os
import sys
import getopt
import argparse
from os.path import isfile, join

# globals and their default values
_packLeftovers = False
_processedFolders = []
_processedFiles = []
_outputPileFile = 'data.pile'
_outputDir = ''
_ignoreDirs = []
_backupDir = ''
_crossCheckingFiles = []
# the default settings settings
_args = { 'excl_masks' : [],
            'binary' : 'FilePileCompiler.exe ',
            'buffer' : ' -buffer 16 ',
            'comp_size' : ' -comp_size 1 ',
            'max_comp_ratio' : ' -max_comp_ratio 90 ',
            'packdir' : ' -packdir '}

def main(argv):

    def cleanup():
        # cleanup the file lists
        import glob
        for fl in glob.glob(os.path.join(_outputDir, '*.fl.tmp')):
            os.remove(fl)

    def backupProcessedFiles():
        for item in _processedFiles:
            global _backupDir
            _backupDir = join(args.packdir, "_processedFiles")
            if not os.path.isdir(_backupDir):
                os.makedirs(_backupDir)

            fileFullPath = join(args.packdir, item)
            if isfile(fileFullPath):
                import shutil
                try:
                    os.makedirs(join(_backupDir, os.path.split(item)[0]))
                except:
                    pass
                shutil.move(fileFullPath, join(_backupDir, item))
            else:
                print "Can not move " + fileFullPath + ". File does not exist"

    def restoreProcessedFiles():
        if _backupDir:
            print 'Moving back the backed up files...'
            for item in _processedFiles:
                import shutil
                shutil.move(join(_backupDir, item), join(args.packdir, item))
            shutil.rmtree(_backupDir)

    def processExcludeFile(inputFile):
        with open(inputFile, 'r') as f:
            for line in f:
                if line.startswith('-'):
                    global _args
                    _args['excl_masks'].append(line[1:].strip('\n'))
                else:
                    global _ignoreDirs
                    _ignoreDirs.append(line.strip('\n'))
            f.close()


    def processCrossCheckFl(filelist):
        global _crossCheckingFiles
        with open(filelist, 'r') as f:
            for line in f:
                if not line.startswith('/'):
                    line = '/' + line
                _crossCheckingFiles.append(line.strip('\n'))
            f.close()

    def crossCheckDir(dataDir):
        global _crossCheckingFiles
        dirFL = []
        fullPath = os.path.join(args.packdir,dataDir)
        #print "Crosschecking dir:" + fullPath
        #print "CCList:" + str(_crossCheckingFiles)
        for r,d,f in os.walk(fullPath):
            for file in f:
                localPath = '/' + os.path.join(r,  file)[len(args.packdir) + 1:].replace('\\', '/')
                if localPath in _crossCheckingFiles:
                    dirFL.append(localPath)
                    _processedFiles.append(os.path.join(r, file).replace('\\', '/'))
                #else:
                    #print "File '" + localPath + "' not found in the CC list"
        return dirFL

    def processInputFile(inputFile):
        includeMasks = []
        excludeMasks = []
        regularDirs = []
        if '\\' in inputFile:
            inputFile = inputFile.replace('\\', '/')
        outputPileFile = _outputDir + inputFile.split('/')[-1].split('.')[0] + '.pile'

        args = _args['binary'] + '-output ' + outputPileFile + _args['max_comp_ratio'] + _args['comp_size'] + _args['buffer']

        with open(inputFile, 'r') as f:
            for line in f:
                if line.startswith('-'):
                    excludeMasks.append(line[1:].strip('\n'))
                elif line.startswith('+'):
                    includeMasks.append(line[1:].strip('\n'))
                else:
                    if (line not in _ignoreDirs):
                        regularDirs.append(line.strip('\n'))
            f.close()

        if includeMasks:
            args += ' -masks ' + ';'.join(includeMasks)


        if excludeMasks and _args['excl_masks']:
            # an additional semi-colon between the local and the global masks is not a typo
            args += ' -excl_masks ' + ';'.join(_args['excl_masks']) + ';' + ';'.join(excludeMasks)
        elif excludeMasks:
            args += ' -excl_masks ' + ';'.join(excludeMasks)
        elif _args['excl_masks']:
            args += ' -excl_masks ' + ';'.join(_args['excl_masks'])

        if regularDirs:
            # process only the cross-checked files in the specified dirs
            pileFL = []
            for dir in regularDirs:
                pileFL = pileFL + crossCheckDir(dir)

            pileFLPath = outputPileFile + '.fl.tmp'
            with open (pileFLPath, 'w') as f:
                for file in pileFL:
                    f.write(file + '\n')
                f.close()
            args += _args['packdir'] + ' ' + pileFLPath
            _processedFolders.append(regularDirs)
        else:
            # no dirs specified, process the whole 'Data' dir using
            # the available masks (if any were defined)
            pileFL = crossCheckDir("")

            pileFLPath = outputPileFile + '.fl.tmp'
            with open (pileFLPath, 'w') as f:
                for file in pileFL:
                    f.write(file + '\n')
                f.close()
            args += _args['packdir'] + ' ' + pileFLPath
            _processedFolders.append(regularDirs)

        return args

    def processFileList(inputFile):
        includeMasks = []
        excludeMasks = []
        regularFiles = []
        masks = ''
        if '\\' in inputFile:
            inputFile = inputFile.replace('\\', '/')
        outputPileFile = _outputDir + inputFile.split('/')[-1].split('.')[0] + '.pile'
        print "Trying to open file list:" + inputFile

        with open(inputFile, 'r') as f:
            for line in f:
                if line.startswith('-'):
                    excludeMasks.append(line[1:].strip('\n'))
                elif line.startswith('+'):
                    includeMasks.append(line[1:].strip('\n'))
                else:
                    if (line not in _ignoreDirs):
                        regularFiles.append(line.strip('\n'))
            f.close()

        if includeMasks:
            masks += ' -masks ' + ';'.join(includeMasks)

        if excludeMasks and _args['excl_masks']:
            # an additional semi-colon between the local and the global masks is not a typo
            masks += ' -excl_masks ' + ';'.join(_args['excl_masks']) + ';' + ';'.join(excludeMasks)
        elif excludeMasks:
            masks += ' -excl_masks ' + ';'.join(excludeMasks)
        elif _args['excl_masks']:
            masks += ' -excl_masks ' + ';'.join(_args['excl_masks'])



        # find all the *.txt files and append them to the file list
        dataDir = args.packdir
        print "Processing all the *.txt files..."
        txts = []
        for r,d,f in os.walk(dataDir):
            for file in f:
                if file.endswith(".txt"):
                    # sort of a hack: make the full path from the root (dataDir), then cut out the leading data dir substring
                    # because FilePileCompiler does not like absolute paths (?)
                    filepath = os.path.join(r, file)[len(dataDir) + 1:]
                    txts.append(filepath)
                    if not (len(txts) % 1000) :
                        print "Found: " + str(len(txts)) + ' *.txt files...'

        print "Done with the *.txts. Writing the total file list to pack..."
        # write the valid file list to be later processed by the FilePileCompiler
        fileListName = inputFile + '.filelist '
        with open (fileListName, 'w') as f:
            for file in regularFiles:
                #print dataDir + '/' + file
                if os.path.isfile(os.path.join(dataDir, file)):
                    _processedFiles.append(file.replace('\\', '/'))
                    f.write(file + '\n')
            for file in txts:
                # we do not add txts to the list of the processed files
                # because they are easily filtered out by the exclude masks
                f.write(file + '\n')
            f.close()

        compilerArgs = _args['binary'] + '-output ' + outputPileFile + masks +\
                       _args['max_comp_ratio'] + _args['comp_size'] + _args['buffer'] +\
                       _args['packdir'] + ' ' + fileListName

        return compilerArgs, fileListName

    def buildExecString(outputFilePath = _outputPileFile):
        compilerArgs = _args['binary'] + '-output ' + outputFilePath + _args['max_comp_ratio'] + _args['comp_size'] + _args['buffer'] + _args['packdir']
        if _args['excl_masks']:
            compilerArgs += ' -excl_masks ' + ';'.join(_args['excl_masks'])

        return compilerArgs

    parser = argparse.ArgumentParser()
    parser.add_argument('-I', '--infiles', help='list of directories and masks to include in the pile file')
    parser.add_argument('-F', '--filelists', help='list of files and masks to include in the pile file (e.g., localisation resources)')

    parser.add_argument('-X', '--exfiles', type=str, help='list of files and masks to ignore while creating pile files')
    parser.add_argument('-D', '--dir', type=str, help='directory to hold the resulting pile files', required=True)
    parser.add_argument('-P', '--packdir', type=str, help='directory that contains data files to be processed', required=True)
    parser.add_argument('-A', '--allfiles', help='set this to "true" to pack all the non-explicitly-specified files in the Data directory (default is "false")')
    parser.add_argument('-C', '--compiler', help='set path to the FilePileCompiler utility')
    parser.add_argument('-CCL', '--cclist', help='cross-checking file list, which explicitly specifies the files to pack', required=True)

    args = parser.parse_args()
    if (not args.infiles and not args.filelists) or \
       not args.packdir or not args.dir:
        parser.print_help()
        sys.exit()

    print '--------Args:-------'
    print args.infiles
    print args.exfiles
    print args.dir
    if args.allfiles:
        global _packLeftovers
        _packLeftovers = args.allfiles.lower() in ['yes', 'true', 'y', '1', 't']

    print '--------------------'
    # FilePileCompiler binary path
    if args.compiler:
        _args['binary'] = args.compiler + ' '
    # processing directory
    if args.packdir:
        #global _packdir
        _args['packdir'] += args.packdir

    # Output directory
    if args.dir:
        global _outputDir
        _outputDir += args.dir + '/'
    try:
        os.makedirs(_outputDir)
    except:
        pass

    # Build directory and masks list to exclude from the further processing
    if args.exfiles:
        exfiles = []
        if ';' in args.exfiles:
            exfiles = args.exfiles.split(';')
        elif ',' in args.exfiles:
            exfiles = args.exfiles.split(',')
        else:
            exfiles.append(args.exfiles)

        for file in exfiles:
            processExcludeFile(file)

    # Get and process the file lists
    if args.filelists:
        filelists = []
        if ';' in args.filelists:
            filelists = args.filelists.split(';')
        elif ',' in args.filelists:
            filelists = args.filelists.split(',')
        else:
            filelists.append(args.filelists)
        # build exec lines for all the input files
        for index in range(len(filelists)):
            compilerArgs, fileListName = processFileList(filelists[index])
            print compilerArgs
            os.system(compilerArgs)
            # remove the filelist file when the FilePileCompiler finishes
            os.remove(fileListName)

    # move the already packed files to the separate directory
    # to skip their possible erroneus processing as leftovers
    # (and to avoid the kilometers of explicitly specified exclude masks)
    backupProcessedFiles()
    _ignoreDirs.append('_processedFiles')

    # Get and process cross-checking file list
    if args.cclist:
        processCrossCheckFl(args.cclist)

    # Get and process the input file directories list
    if args.infiles:
        infiles = []
        if ';' in args.infiles:
            infiles = args.infiles.split(';')
        elif ',' in args.infiles:
            infiles = args.infiles.split(',')
        else:
            infiles.append(args.infiles)

        # build exec lines for all the input files
        for index in range(len(infiles)):
            compilerArgs = processInputFile(infiles[index])
            print compilerArgs
            os.system(compilerArgs)

    if not _packLeftovers:
        print 'All done (leftovers are ignored)'
        cleanup()
        # copy the backed up files to their original location
        restoreProcessedFiles()
        sys.exit(0)

    # build exec lines for the leftovers
    # append *.txt exclude mask for the rest of the tasks (we have already packed these files with the localisation resources)
    _args['excl_masks'].append("*.txt")

    print '-------LEFTOVERS---------'
    _1dFolders = sum(_processedFolders, [])
    print "Processed folders: " + str(_1dFolders).strip('[]')
    print "Ignored folders:" + str(_ignoreDirs).strip('[]')
    if len(_processedFiles) > 5:
        print "Already processed files number:" + str(len(_processedFiles))
    else:
        print "Already processed files list:" + str(_processedFiles)
    allDirs = os.listdir(args.packdir)
    print "Writing leftover files and directories in the root directory..."
    leftoverDirs = []

    with open(join(_outputDir,'leftovers.fl.tmp'), 'w+') as f:
        for item in _crossCheckingFiles:
            itemPath = ''.join([args.packdir.replace('\\', '/'),item])
            if itemPath not in _processedFiles:
                # if it exists and is a file, write it to the leftovers list file
                if isfile(itemPath):
                    f.write(item + "\n")
        f.close()


    # the dataXX.txt should have mapped all the needed directories,
    # so the non-empty 'leftoverDirs' means that something was forgotten
    # and has to be packed
    if (len(leftoverDirs)):
        leftoversArg = ' -folders ' + ';'.join(leftoverDirs)
        compilerArgs = buildExecString(_outputDir + '_dataExtra.pile') + leftoversArg
        print compilerArgs
        os.system(compilerArgs)

    _args['packdir'] +=  ' ' + join(_outputDir, 'leftovers.fl.tmp') + ' '
    compilerArgs = buildExecString(_outputDir + '_data.pile')
    print compilerArgs
    os.system(compilerArgs)

    cleanup()
    # copy the backed up files to their original location
    restoreProcessedFiles()
    print 'All done'

if __name__ == "__main__":
    # pass all the args, including the script name
    main(sys.argv)
#######################
##### Usage notes #####
# The input files(-I and -X) should be separated using either comma or semicolon.
# The input files (-I/--infiles) are expected to contain a single
# folder name(as they are named under the pw/Data directory) on each of the file's line.
# The input list file name determines the output .pile file name.
# E.g.,
# critters_and_pets.txt
#                       Critters
#                       Pets
# The resulting pile file will be named critters_and_pets.pile, and it will contain
# the contents of the pw/Data/Critters and pw/Data/Pets directories.
# The include/exclude masks are specified with the '+' and '-' line prefixes.
# E.g., to pack only the '.dds' files in the 'Heroes' directory:
#    pack_only_dds.txt
#                       Heroes
#                       +*.dds
# To pack all the GameLogic contents, except the '.xdb', '.lua' and '.txt' files:
#    pack_all_game_logic_except_xdb.txt
#                       GameLogic
#                       -*.xdb
#                       -*.lua
#                       -*.txt
# The list of global exclude masks should be specified as '-X/--exfiles' option.
# The masks in this file wil be applied to all FilePileCompiler calls.

# The -CCL argument is mandatory and specifies an explicit list of all the
# resource files that must be packed (omitting the useless)
