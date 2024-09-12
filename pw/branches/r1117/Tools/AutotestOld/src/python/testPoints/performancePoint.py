from errors import *
from testPoints import TestPoint

class PerformancePoint(TestPoint):
  def __init__(
    self,
    internalTotalMem,
    workingSetSize,
    quotaPagedPoolUsage,
    quotaNonPagedPoolUsage,
    pagefileUsage,
    mspf
  ):
    self.itm = internalTotalMem
    self.wss = workingSetSize
    self.qpp = quotaPagedPoolUsage
    self.qnpp = quotaNonPagedPoolUsage
    self.pf = pagefileUsage
    self.mspf = mspf

  def __str__(self):
    return 'performance(itm = %d, ws = %d, qpp = %d, qnpp = %d, pf = %d, mspf = %.5f)' % (self.itm, self.ws, self.qpp, self.qnpp, self.pf, self.mspf)

  def compare(self, testPoint):
    warnings = super(PerformancePoint, self).compare(testPoint)

    def cmp(x, y, threshold): return float(x)/y > (1 + threshold/100.0)

    def fullCmp(x, y, (errorThreshold, warningThreshold, improvementThreshold), cls):
      if cmp(x, y, errorThreshold): raise cls(x, y)
      if cmp(x, y, warningThreshold): warnings.append(cls(x, y))
      if cmp(y, x, improvementThreshold): warnings.append(cls(x, y))

#    fullCmp(self.itm, testPoint.itm, self.internalMemoryUsageThresholds, DifferentInternalMemoryUsage)
    fullCmp(self.wss, testPoint.wss, self.externalMemoryUsageThresholds, DifferentExternalMemoryUsage)
    fullCmp(self.mspf, testPoint.mspf, self.mspfThreasholds, DifferentMspf)

    return warnings

  @classmethod
  def configure(cls, settings):
    def get(option): return settings.getfloat('performance', option)

    def getThresholds(name):
      return tuple(get('%s.%sThreshold' % (name, kind)) for kind in ['error', 'warning', 'improvement'])

    cls.internalMemoryUsageThresholds = getThresholds('internalMemoryUsage')
    cls.externalMemoryUsageThresholds = getThresholds('externalMemoryUsage')
    cls.mspfThreasholds = getThresholds('mspf')
