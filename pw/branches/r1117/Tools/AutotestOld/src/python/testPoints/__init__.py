from errors import *
from os.path import join, exists

class TestPoint(object):
  def compare(self, testPoint):
    if self.__class__ != testPoint.__class__:
      raise DifferentTestPoints(self, testPoint)

    return [] # No warnings

from screenshotPoint import ScreenshotPoint
from performancePoint import PerformancePoint
from logPoint import LogPoint

def gatherTestPoints(folder):
  resultList = []

  def screenshot(frameNo, filename):
    resultList.append(ScreenshotPoint(frameNo, join(folder, filename)))

  def performance(
    internalTotalMem,
    workingSetSize,
    quotaPagedPoolUsage,
    quotaNonPagedPoolUsage,
    pagefileUsage,
    mspf
  ):
    resultList.append(
      PerformancePoint(
        internalTotalMem,
        workingSetSize,
        quotaPagedPoolUsage,
        quotaNonPagedPoolUsage,
        pagefileUsage,
        mspf
      )
    )

  def log(filename):
    resultList.append(LogPoint(join(folder, filename)))

  lcls = {
    'screenshot': screenshot,
    'performance': performance,
    'log': log,
  }

  testLogName = folder + '/testlog'
  
  if exists(testLogName):
    execfile(testLogName, lcls)

  return resultList

def compareTestPoints(imageTestPoints, runTestPoints):
  if len(imageTestPoints) != len(runTestPoints):
    raise DifferentNoTestPoints()

  warnings = []
  for i, r in zip(imageTestPoints, runTestPoints):
    warnings.extend(i.compare(r))
  return warnings

TEST_POINTS = [ScreenshotPoint, PerformancePoint, LogPoint]

def configureTestpoints(settings):
  for point in TEST_POINTS:
    point.configure(settings)
