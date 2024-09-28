from logger import log
from logger.reports import *

class FatalFailure(Exception):
  '''
    Fatal failure exception class

    Fatal failures are failures that prevented tests from running like
    failure to update or build sources, etc.
  '''
  pass

class TestFailed(Exception):
  def report(self):
    '''
      Error report
    '''
    t = self.text()
    if hasattr(self, 'args'):
      t += ':' + ' '.join(str(self.args))
    
    return TextReport(t)

  @staticmethod
  def text(): return 'unknown failure'

class GeneralTestProblem(TestFailed):
  '''
    Auxilary class that reports general test problem like hanging, crashing, etc
  '''
  @staticmethod
  def text(): return 'general test problem'

class TestHanged(GeneralTestProblem):
  '''
    Test application hanged exception
  '''
  @staticmethod
  def text(): return 'hanged'

class TestCrashed(GeneralTestProblem):
  '''
    Test application crashed
  '''
  @staticmethod
  def text(): return 'crashed'

class TestAssert(TestCrashed):
  '''
    Test application crashed with assert
  '''
  def __init__(self, logfile):
    TestCrashed.__init__(self)
    self.log = logfile

  @staticmethod
  def text(): return 'crashed with assert'
    
  def report(self): return TextFile(self.log)

class TestException(TestCrashed):
  '''
    Test application crashed with exception
  '''
  def __init__(self, logfile):
    TestCrashed.__init__(self)
    self.log = logfile

  @staticmethod
  def text(): return 'crashed with exception'
    
  def report(self): return TextFile(self.log)

class NetworkTestCrashed(TestCrashed):
  '''
    One of the applications run inside network game test crashed
  '''
  def __init__(self, assertLogs, excptLogs):
    TestCrashed.__init__(self)
    
    self.assertLogs = assertLogs
    self.excptLogs = excptLogs

  @staticmethod
  def text(): return 'crashed on one or more machines'
    
  def report(self): return NetworkReport( [(m, TextFile(l)) for (m,l) in self.assertLogs], [(m, TextFile(l)) for (m,l) in self.excptLogs] )

class TestFailedToOpen(GeneralTestProblem):
  '''
    Test application failed to open VRML file exception
  '''
  @staticmethod
  def text(): 'failed to open'

class TestFailedToExecute(GeneralTestProblem):
  '''
    Test application failed to execute exception
  '''
  @staticmethod
  def text(): return 'failed to execute'

class TestNonFatalError(GeneralTestProblem):
  '''
    Test application produced internal error (seASSERT, seERROR, etc) exception
  '''
  def __init__(self, logfile):
    GeneralTestProblem.__init__(self)
    self.log = logfile

  def report(self): return TextFile(self.log)

# Standard errors codes
errorCodes = {1: TestCrashed, 2: TestFailedToOpen, 3: TestFailedToExecute, 4: TestNonFatalError}

class TestDiffers(TestFailed):
  '''
    Test points differ exception
  '''
  def report(self): return ComparisonReport(self.text, self.image, self.produced)

class NoTestPoints(TestFailed):
  '''
    Test hasn't generated any test points
  '''
  @staticmethod
  def text(): return 'generated no testpoints'

class DifferentNoTestPoints(TestDiffers):
  '''
    This exception is raisen when number of test points differs
  '''
  text = 'different number of test points'
  image = Text('N/A')
  produced = Text('N/A')

class DifferentTestPoints(TestDiffers):
  '''
    Test points are of different classes (ergo, cannot be compared) exception
  '''
  def __init__(self, image, produced):
    '''
      Ctor

      image - test point from golden images
      run - test point from test run
    '''
    TestDiffers.__init__(self)

    self.image = Text(image)
    self.produced = Text(produced)

  text = 'different test points'

class DifferentFrameNo(TestDiffers):
  '''
    Screenshots were taken at different frames exception
  '''
  def __init__(self, image, produced):
    TestDiffers.__init__(self)
    self.image = Text(image.frameNo)
    self.produced = Text(produced.frameNo)

  text = 'different test point frames'

class DifferentScreenshots(TestDiffers):
  '''
    Screenshots are notably different exception
  '''
  def __init__(self, image, produced, info):
    '''
      Ctor

      image - filename of screenshot from golden images
      produced - filename of screenshot from test run
    '''
    TestDiffers.__init__(self)

    self.image = Image(log.addFile(image.filename))
    self.produced = Image(log.addFile(produced.filename))
    self.text = 'different screenshots: %s' % info

class DifferentLogs(TestDiffers):
  '''
    Logs are different exception
  '''
  def __init__(self, image, produced, info):
    '''
      Ctor

      image - filename of log from golden images
      produced - filename of log from test run
    '''
    TestDiffers.__init__(self)

    self.image = TextFile(image.filename)
    self.produced = TextFile(produced.filename)
    self.text = 'different logs: %s' % info

class PerformanceTestPointException(TestDiffers):
  '''
    Base class for performance test exceptions
  '''
  def __init__(self, image, produced):
    '''
      Ctor

      image - golden images metrics value
      produced - test run metrics value
    '''
    TestDiffers.__init__(self)
    self.image = Text(image)
    self.produced = Text(produced)

class DifferentInternalMemoryUsage(PerformanceTestPointException):
  '''
    Notably different internal memory usage exception

    Internal memory usage is usage reported by engine's memory manager
  '''
  text = 'different internal memory usage'

class DifferentExternalMemoryUsage(PerformanceTestPointException):
  '''
    Notably different external memory usage exception

    External memory usage is usage reported by Win PSAPI
  '''
  text = 'different external memory usage'

class DifferentMspf(PerformanceTestPointException):
  '''
    Notably different MSPF (MilliSeconds Per Frame) exception
  '''
  text = 'different MSPF'
