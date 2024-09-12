import sys
import os
import time
import re
import SvnTools
import Checkers
import hooks
import re
import XmlUtils
#import wingdbstub

def checkMissedFilesByHandler(text, missed_files, handler, svn):
    is_some_errors_found = False
    p = XmlUtils.parseString(text)
    if p.error:
        return True
        
    handler.parse(p)

    for file_name in handler.files:
        result = svn.isPathExist(file_name)
        if not result:
            is_some_errors_found = True
            missed_files.append(file_name)
    return is_some_errors_found
    
class CppFileHandler:

    def __init__(self, name):
        self.files = []    
        self.path = os.path.dirname(name)
        
    def parse(self, p):
        self.enumSections(p.root['VisualStudioProject']['Files'])
            
    def enumSections(self, root):
        if root.has('Filter'):
            for f in root['Filter']:
                self.enumSections(f)
        if root.has('File'):
            for f in root['File']:
                self.files.append(os.path.normpath(os.path.join(self.path, f('RelativePath'))))
                    
class CsFileHandler:

    def __init__(self, name):
        self.files = []    
        self.path = os.path.dirname(name)
        
    def parse(self, p):
        for item_group in p.root['Project']['ItemGroup']:
            if item_group.has('Compile'):
                for c in item_group['Compile']:
                    if not c.has('AutoGen'):
                        self.files.append(os.path.normpath(os.path.join(self.path, c('Include'))))

class LogChecker:                            

    def __init__(self, log):
        self.log = log

    def check(self, s):
        text = s.getLog()
        if s.result != 0:
            return True
            
        text = text.replace('\r', '').replace('\n', '')            
        if len(text) > 0:
            return False

        self.log.writeln('Log message should not be empty!')      
        return True

class NameChecker:

    def __init__(self, log):
        self.log = log
        self.name = None

    def check(self, svn, name, extension, status):
        if status != 'D':
            result = re.search('[a-zA-Z0-9_\(\)\+\-./]*', name)
            if result.group(0) != name:
                self.name = name
                return True
        return False                        

    def flush(self):
        if self.name:
            self.log.writeln('Incorrect file name: "%s", please rename' % self.name)

from PythonChecker import process
import PythonChecker

class DoNotCommitChecker:

    def __init__(self, log): 
        self.log = log
        self.files = []
        PythonChecker.warning_printer = PythonChecker.InfoPrinter(log.writeln)
            
    def check(self, svn, name, extension, status):
        if status != 'D':
            if not process(name, svn.getContent):
                return True
            text = svn.getContent(name)
            if 'DO_NOT_COMMIT' in text:
                self.files.append(name)
                return True
        return False
        
    def flush(self):             
        for name in self.files:
            self.log.writeln('DO_NOT_COMMIT tag found in %r' % name)

class XdbChecker:

    def __init__(self, log): 
        self.log = log
        self.files = []
            
    def check(self, svn, name, extension, status):
        if status != 'D':
            text = svn.getContent(name)
            p = XmlUtils.parseString(text)
            if p.error:
                self.files.append((name, p.error))
                return True
        return False
        
    def flush(self):             
        for name, details in self.files:
            self.log.writeln('Incorrect syntax in %r (%s)' % (name, str(details)))
        
class VCProjCSProjChecker:

    def __init__(self, log): 
        self.missed_files = {}
        self.log = log

    def check(self, svn, name, extension, status):
        if extension == '.vcproj':
            handler = CppFileHandler(name)
        elif extension == '.csproj':
            handler = CsFileHandler(name)
        else:
            handler = None
        is_errors_found = False    
        if handler:
            text = svn.getContent(name)
            self.missed_files[name] = []
            is_errors_found = checkMissedFilesByHandler(text, self.missed_files[name], handler, svn)
        return is_errors_found

    def flush(self):             
        for name, files in self.missed_files.items():
            if files:
                self.log.writeln('Following files were added to the '+repr(name)+', but not to SVN:')
                for file_name in files:
                    self.log.writeln(' '*4+file_name)
        self.missed_files.clear()                    
        
class ProhibitedExtensionChecker:

    def __init__(self, log):
        self.name = None
        self.log = log

    def check(self, svn, name, extension, status):
        self.name = name            
        return True

    def flush(self):
        if self.name:
            self.log.writeln( self.name + ': *%s files are not allowed in this repository' % os.path.splitext(self.name)[1] )

class PreCommitProcessor:

    def __init__(self, is_offline_mode=False):
        self.is_offline_mode = is_offline_mode

    def createSvnLook(self, log, repository, action_id):
        if self.is_offline_mode:
            return SvnTools.SvnLook(log, repository, None, action_id)
        else:
            return SvnTools.SvnLook(log, repository, action_id)

    def process(self, log, sc, email, email_options):
        extension_checkers = {
#            '.vcproj' : VCProjCSProjChecker(log),
#            '.csproj' : VCProjCSProjChecker(log),
            '.tga' : ProhibitedExtensionChecker(log),
            '.mb' : ProhibitedExtensionChecker(log),
            '.ma' : ProhibitedExtensionChecker(log),
            '.ncb' : ProhibitedExtensionChecker(log),
            '.xdb' : XdbChecker(log),
            '.cpp' : DoNotCommitChecker(log),
            '.h' : DoNotCommitChecker(log),
            '.hpp' : DoNotCommitChecker(log),
            '.cs' : DoNotCommitChecker(log),
            '.hlsl' : DoNotCommitChecker(log),
            '.cfg' : DoNotCommitChecker(log),
            None : NameChecker(log),
        }

        checkers = [
            LogChecker(log),
            Checkers.FileByExtensionChecker(extension_checkers),
        ]
         
        for checker in checkers:
            if checker.check(sc):
                return 1
        return 0
                    
if __name__ == '__main__':
    repository = sys.argv[1]
    if len(sys.argv) > 2:
        transaction = sys.argv[2]
        log_path = os.path.abspath(os.path.join(repository, transaction+'.pre.log'))
    else:
        transaction = None
        log_path = None

    processor = PreCommitProcessor()        
    email_config_path = os.path.join(repository, 'email.cfg')
    return_code = hooks.processHook(repository, transaction, processor, log_path, email_config_path)
    sys.exit(return_code)
           