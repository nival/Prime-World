from os.path import join, abspath, normpath
from testApplications.gameApp import GameApp
import test
from os import listdir
from re import match
import time
import settingsManager
import processes
import errors

TIME_FORMAT = '%Y.%m.%d-%H.%M.%S'

class RunGameTest(test.Test):
  def __init__(self, configuration):
    super(RunGameTest, self).__init__(configuration)

  def key(self): return '|'.join([self.__class__.__name__, self.pd.configuration])

  def info(self, configuration):
    return (GameApp.application(configuration), GameApp.workingDir(configuration), 'exec "../Tools/Autotest/scripts/single.quit.cfg"', 180000)

  @classmethod
  def configure(cls, settings):
    super(RunGameTest, cls).configure(settings)

    # UnitTests can be shared between configurations
    cls.configurations = settings.configurations
    cls.root = settingsManager.getRoot(settings)

  @staticmethod
  def useGoldenImages():
    return False

  @staticmethod
  def getRequiredComponents():
    return ['Src/PF.sln']

  def run(self):
    app, wd, args, timeout = self.info(self.pd.configuration)
    launchTime = time.time()
    isHanged, exitCode,_ = processes.launchApp(app, args, wd, timeout)
    if isHanged:
      # check for assert / exception log
      logDir = join(wd, 'log')
      assertLog = test.findLog('PF', 'assert\.log', logDir, launchTime)
      excptLog = test.findLog('PF', 'exception\.log', logDir, launchTime)
      if assertLog != None:
        raise errors.TestAssert(abspath(join(wd, logDir, assertLog)))
      elif excptLog != None:
        raise errors.TestException(abspath(join(wd, logDir, excptLog)))
      else:
        raise errors.TestHanged
    elif exitCode != 0:
      raise errors.errorCodes.get(exitCode, errors.GeneralTestProblem)
