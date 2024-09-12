from os.path import join, dirname
from runGameTest import RunGameTest
from networkGameTest import NetworkGameTest
from auditTest import AuditTest

TESTS = [RunGameTest, NetworkGameTest, AuditTest]

def configureTests(settings):
  '''
    Configure all the tests

    settings - settings to configure by
  '''
  for test in TESTS:
    test.configure(settings)

def relativeTo(baseFilename, filename):
  '''
    Calculates new file name that filename relative to the folder of baseFilename

    For example relativeTo('foo/bar.suite', 'zoo/moo.suite') will
    return 'foo/zoo/moo.suite'
  '''
  return join(dirname(baseFilename), filename)

class TestGatherer(object):
  '''
    Auxilary class to gather tests
  '''
  def __init__(self):
    self.testList = []

  def include(self, filename):
    lcls = {
      'runGameTest': lambda config: self.addTest(RunGameTest(config)),
      'networkGameTest': lambda config, maxPlayers, *clients: self.addTest(NetworkGameTest(config, maxPlayers, clients)),
      'auditTest': lambda config: self.addTest(AuditTest(config)),
      'include': lambda fn: self.include(relativeTo(filename, fn))
    }

    execfile(filename, {}, lcls)

  def addTest(self, test): self.testList.append(test)

  def standardTest(self, testClass): return lambda fn: self.addTest(testClass(fn))

def gatherTests(filename):
  '''
    Returns a list of tests gathered from filename suite file

    filename - suite file to gather tests from
  '''
  tg = TestGatherer()
  tg.include(filename)
  return tg.testList
