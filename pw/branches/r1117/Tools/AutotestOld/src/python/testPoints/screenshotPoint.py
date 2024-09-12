from bmptools import *
from errors import *
from settingsManager import getStringList
from testPoints import TestPoint

class ScreenshotPoint(TestPoint):
  '''
    Screenshot comparison test point
  '''

  def __init__(self, frameNo, filename):
    '''
      Ctor

      frameNo --- frame at which screenshot was taken
      filename --- filename of screenshot .BMP file
    '''
    self.frameNo = frameNo
    self.filename = filename

  def __str__(self):
    return 'screenshot(%d, %s)' % (self.frameNo, self.filename)

  def compare(self, testPoint):
    warnings = super(ScreenshotPoint, self).compare(testPoint)

    if self.frameNo != testPoint.frameNo:
      raise DifferentFrameNo(self, testPoint)

    def check(cond, info):
      if not cond: raise DifferentScreenshots(self, testPoint, info)

    image0, image1 = readBmp(self.filename), readBmp(testPoint.filename)

    check(image0.shape == image1.shape, "images' sizes differ")

    for norm, errorThreshold, warningThreshold in self.norms:
      diff = norm(image0, image1)

      def msg(threshold):
        return '[%s] diff = %.3f, threshold = %.3f' % (norm.name, diff, threshold)

      check(diff < errorThreshold, msg(errorThreshold))
      if diff >= warningThreshold:
        warnings.append(DifferentScreenshots(self, testPoint, msg(warningThreshold)))

    return warnings

  @classmethod
  def configure(cls, settings):
    def get(option): return settings.get('screenshots', option)

    def createCountingNorm():
      pixelNorm = getattr(PixelNorms, get('counting.pixelNorm'))
      threshold = int(get('counting.threshold'))
      bg = tuple([int(s) for s in get('counting.BG').split(',')])
      errorThreshold = float(get('counting.errorThreshold'))
      warningThreshold = float(get('counting.warningThreshold'))
      return CountingNorm(pixelNorm, threshold, bg), errorThreshold, warningThreshold

    def createAvgNorm():
      pixelNorm = getattr(PixelNorms, get('average.pixelNorm'))
      errorThreshold = float(get('average.errorThreshold'))
      warningThreshold = float(get('average.warningThreshold'))
      return AvgNorm(pixelNorm), errorThreshold, warningThreshold

    mappings = dict(counting = createCountingNorm, average = createAvgNorm)
    cls.norms = [mappings[norm]() for norm in getStringList(settings, 'screenshots', 'norms')]
