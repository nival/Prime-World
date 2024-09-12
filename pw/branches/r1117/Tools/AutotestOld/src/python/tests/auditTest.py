import os.path
from os.path import join
import test
import time
import logging
import settingsManager
import processes
import errors

COMPONENT = r'Src\Game\PF\Audit\audit_wx.application'

def getApp(component, configuration):
  path, file = os.path.split(component)
  name, ext = os.path.splitext(file)
  return join(AuditTest.root, path, '.auto', configuration, name + '.exe')
 

class AuditTest(test.Test):
  def __init__(self, configuration):
    super(AuditTest, self).__init__(configuration)
#    self.cfgFile = cfgFile

  def key(self): return '|'.join([self.__class__.__name__, self.pd.configuration])

  def info(self, configuration):
    return (getApp(COMPONENT, self.pd.configuration), join(AuditTest.root, 'Bin'), '', 60000)

  @classmethod
  def configure(cls, settings):
    super(AuditTest, cls).configure(settings)

    cls.configurations = settings.configurations
    cls.root = settingsManager.getRoot(settings)

  @staticmethod
  def useGoldenImages():
    return False

  @staticmethod
  def getRequiredComponents():
    return [COMPONENT]

  def run(self):
    app, wd, args, timeout = self.info(self.pd.configuration)
    launchTime = time.time()
    isHanged, exitCode,_ = processes.launchApp(app, args, wd, timeout)
    
    # check for assert / exception log
    logDir = join(wd, 'log')
    assertLog = test.findLog('PFAudit', 'assert\.log', logDir, launchTime)
    excptLog = test.findLog('PFAudit', 'exception\.log', logDir, launchTime)
    if assertLog != None:
      raise errors.TestAssert(os.path.abspath(join(wd, logDir, assertLog)))
    elif excptLog != None:
      raise errors.TestException(os.path.abspath(join(wd, logDir, excptLog)))
