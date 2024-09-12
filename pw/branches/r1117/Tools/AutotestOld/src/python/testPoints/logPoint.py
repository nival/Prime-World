import os
from errors import *
from testPoints import TestPoint

class LogPoint(TestPoint):
  '''
    Log comparison test point
  '''

  def __init__(self, filename):
    '''
      Ctor

      filename --- filename of log file
    '''
    self.filename = filename

  def __str__(self):
    return 'log(%s)' % (self.filename)

  def compare(self, testPoint):
    warnings = super(LogPoint, self).compare(testPoint)

    exitCode = os.system('fc.exe "%s" "%s"' % (self.filename, testPoint.filename))

    if not exitCode == 0:
      raise DifferentLogs(self, testPoint, '')

    return warnings

  @classmethod
  def configure(cls, settings):
    pass
