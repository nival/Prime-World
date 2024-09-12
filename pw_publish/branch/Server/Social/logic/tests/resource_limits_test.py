import sys
sys.path.append('../')
from binascii import crc32
sys.path.append('../..')
from enums import *


class resource_limits_test:
  def resource_limits_negative_test( self, env ):
    modeldata = env.acc.model
    modeldata.Resources.Silver = 0
    modeldata.Resources.Resource1 = 0
    resources = modeldata.createResourcesTable(Silver = -100500100500, Resource1 = -100500100500)
    modeldata.sell(resources, None)
    assert modeldata.Resources.Silver == 0
    assert modeldata.Resources.Resource1 == 0
    
  def resource_limits_positive_test( self, env ):
    modeldata = env.acc.model
    res = 100500100500
    resources = modeldata.createResourcesTable(Resource1 = res)
    modeldata.sell(resources, None)
    assert modeldata.Resources.Resource1 < res
