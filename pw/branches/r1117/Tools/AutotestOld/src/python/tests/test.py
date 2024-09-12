from os.path import abspath, join, normpath
from os import listdir
from re import match
import processes
import errors
import time
import errors
import settingsManager
import sourceManager

TIME_FORMAT = '%Y.%m.%d-%H.%M.%S'
LOG_PATTERN = '%s-PRIVATE-0\.0\.00\.0000-(.*)-%s'

def findLog(appName, logName, path, laterThan):
  for file in listdir(path):
    m = match(LOG_PATTERN % (appName, logName), file)
    if m != None:
      try:
        fTime = time.mktime(time.strptime(m.group(1), TIME_FORMAT))
        if fTime - laterThan >= -1:   # we need this threshold in order to compensate for time rounding in log names
          return join(path, file)
      except ValueError, e:
        pass

class PersistentData(object):
  pass

class Test(object):
  def __init__(self, configuration):
    self.pd = PersistentData()
    self.pd.configuration = configuration
  
  '''
    Base Test class

    This class defines interface and standard configuration method
  '''
  def key(self):
    '''
      Returns unique test key string

      To be overriden
    '''
    pass

  # Return test application for a test, arguments to pass and expected timeout
  def info(self, configuration):
    '''
      Returns a tuple (path to test application, arguments for test application, timeout)
      for the given configuration

      configuration - configuration to get info for
    '''
    pass

  def __str__(self): return self.key()

  def run(self):
    app, wd, args, timeout = self.info(self.pd.configuration)
    isHanged, exitCode,_ = processes.launchApp(app, args, wd, timeout)
    if isHanged:
      raise errors.TestHanged(self)
    elif exitCode != 0:
      raise errorCodes.get(exitCode, GeneralTestProblem)(self)

  def collectOutput(self, configuration, folder):
    pass

  def execute(self):
    self.pd.lastRunDate = time.time()
    self.pd.lastRunSrcDate = sourceManager.singleton.getLastUpdateTime()

    try:
      self.run()
      
      # test executed OK, register this
      self.lastRunException = None
      self.pd.lastGoodRunDate = self.pd.lastRunDate
      self.pd.lastGoodSrcDate = self.pd.lastRunSrcDate
      
      return True
      
    except errors.TestFailed, e:
      self.lastRunException = e
      return False

  @classmethod
  def configure(cls, settings):
    '''
      Basic configuration

      settings - settings to configure by
    '''
    cls.root = settingsManager.getRoot(settings)
    cls.fps = settings.getint('general', 'fps')

  @staticmethod
  def useGoldenImages():
    '''
      Tells whether this class of tests uses golden images
      (and thus requires 'make golden images' step to be performed before testing)
    '''
    return True

  @staticmethod
  def getRequiredComponents():
    '''
      Returns a list of strings identifying components that have to be built before running this test
    '''
    return []
