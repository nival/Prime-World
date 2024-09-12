import consts
import os
import shutil
import time
import zipfile

from os.path import basename, join, isdir, isfile, walk
from reporters.mail import MailReporter
from reporters.xhtml import XhtmlReporter

def recreateFolder(folder):
  '''
    Function creates a clean folder
  '''
  shutil.rmtree(folder, ignore_errors = True)
  os.mkdir(folder)

class Results(object):
  '''
    Class to gather results of test runs
  '''
  def __init__(self, configurations):
    '''
      Ctor

      configurations - configurations being tested
    '''
    self.passed_ = []
    self.warned_ = []
    self.failed_ = []

  @staticmethod
  def add_(r, configuration, info): r[configuration].append(info)

  def addPassed(self, info):
    '''
      Add information about passed test
    '''
    self.passed_.append(info)

  def addWarned(self, info):
    '''
      Add information about warned test
    '''
    self.warned_.append(info)

  def addFailed(self, info):
    '''
      Add information about failed test
    '''
    self.failed_.append(info)

  def digest(self):
    '''
      The function returns digest of results
    '''
    succeed = ( len(self.warned_) == 0 and len(self.failed_) == 0 )
    shortReport = ([str(t) for t in self.passed_], [str(t) for t, i in self.warned_], [str(t) for t, i in self.failed_])
    detailedReport = (self.warned_, self.failed_)

    return succeed, shortReport, detailedReport

REPORTERS = [MailReporter]

class Log(object):
  '''
    autotest log class
  '''

  FOLDER = consts.LOG_FOLDER # Just to bring it into namespace

  FILES_FOLDER = 'files' # Folder there files (like screenshots) are stored

  @classmethod
  def configure(cls, settings):
    '''
      Configure log

      settings - settings to configure by
    '''
    cls.configurations = list(settings.configurations)
    cls.backupFolder = settings.get('general', 'backupFolder')

  class FileManager(object):
    '''
      Class to manage files needed for log
    '''
    def __init__(self):
      '''
        Ctor

        folder - folder to store files into (MUST exist)
      '''
      recreateFolder(join(Log.FOLDER, Log.FILES_FOLDER))
      self.fileCounter_ = 0

    def add(self, filename):
      '''
        Add a file into a log

        Returns name of the file stored in the log (relative to Log.FOLDER folder)

        filename - file to store
      '''
      name = basename(filename)
      newname = join(Log.FILES_FOLDER, '%04d-%s' % (self.fileCounter_, name))
      self.fileCounter_ += 1
      shutil.copyfile(filename, join(Log.FOLDER, newname))
      return newname

  def init(self):
    '''
      Init the log

      Note: I don't use __init__ as Log should be configured (by Log.configure)
            before it's initialized. Any better way is appreciated.
    '''
    recreateFolder(Log.FOLDER)

    self.results_ = Results(Log.configurations)
    self.fileManager_ = Log.FileManager()
    self.reporters_ = [cls() for cls in REPORTERS]

  def passed(self, test):
    '''
      Log that test passed

      configuration - test configuration
      test - test that passed
    '''
    self.results_.addPassed(test)

  def warned(self, test, info):
    '''
      Log that test warned

      configuration - test configuration
      test - test that warned
    '''
    self.results_.addWarned((test, info))

  def failed(self, test, info):
    '''
      Log that test failed

      configuration - test configuration
      test - test that failed
    '''
    self.results_.addFailed((test, info))

  def addFile(self, filename):
    '''
      Add a file into a log

      Returns name of the file stored in the log

      filename - file to store
    '''
    return self.fileManager_.add(filename)

  def report(self):
    '''
      Report test runs results
    '''
    digest = self.results_.digest()
    for reporter in self.reporters_:
      reporter.report(*digest)

  def fatalFailure(self, info):
    '''
      Log fatal failure
    '''
    for reporter in self.reporters_:
      reporter.fatalFailure(info)

  @staticmethod
  def addToZip((zip, root), path, files):
    for f in files:
      if (isfile(join(path, f))):
        zip.write(join(path, f), join(join(root, path), f))

  def backup(self):
    name = time.strftime('%Y-%b-%d-%H-%M')

    if isfile(consts.BACKUP_ZIP):
      zip = zipfile.ZipFile(consts.BACKUP_ZIP, 'a', zipfile.ZIP_DEFLATED)
    else:
      zip = zipfile.ZipFile(consts.BACKUP_ZIP, 'w', zipfile.ZIP_DEFLATED)
      
    curdir = os.getcwd()
    os.chdir(Log.FOLDER)
    walk('', Log.addToZip, (zip, name))
    os.chdir(curdir)
    zip.close()

log = Log()

def init(settings):
  '''
    Configure log and reporters
  '''
  Log.configure(settings)
  for reporter in REPORTERS:
    reporter.configure(settings)

  log.init()

def reset():
  '''
    Reset logger to empty state
  '''
  log.init()