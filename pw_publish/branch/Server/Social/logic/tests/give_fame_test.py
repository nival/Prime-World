import sys
sys.path.append('../')
from logic.give_fame import *
from binascii import crc32
sys.path.append('../..')
from enums import *

class give_fame_test:
  def give_fame_test( self, env ):
    modeldata = env.acc.model

    modeldata.LordInfo.Fame = 100
    fame = modeldata.LordInfo.Fame
    addValue = 100

    requests = [ ( Give_fame, GiveFameRequest( modeldata, { "value" : ["" + str(addValue) + ""] }, False ) ) ]
    changeList = env.execActions( requests )

    assert modeldata.LordInfo.Fame == fame + addValue

  def give_max_fame_test( self, env ):
    modeldata = env.acc.model

    fame = modeldata.LordInfo.Fame
    addValue = 1000000

    requests = [ ( Give_fame, GiveFameRequest( modeldata, { "value" : ["" + str(addValue) + ""] }, False ) ) ]
    changeList = env.execActions( requests )

    assert modeldata.LordInfo.Fame == env.acc.SD.getMaxLordFame()

  def give_levelup_with_bonus_test( self, env ):
    modeldata = env.acc.model

    modeldata.LordInfo.Fame = 0
    addValue = env.acc.SD.getMaxLordFame()
    resource1 = modeldata.Resources.Resource1 = 0
    resource2 = modeldata.Resources.Resource2 = 0
    resource3 = modeldata.Resources.Resource3 = 0
    silver = modeldata.Resources.Silver = 0
    perl = modeldata.Resources.Perl = 0
    oldRes = resource1 + resource2 + resource3 + silver + perl

    requests = [ ( Give_fame, GiveFameRequest( modeldata, { "value" : ["" + str(addValue) + ""] }, False ) ) ]
    changeList = env.execActions( requests )

    assert modeldata.LordInfo.Fame == env.acc.SD.getMaxLordFame()
  
    newRes = modeldata.Resources.Resource1 + modeldata.Resources.Resource2 + modeldata.Resources.Resource3 + modeldata.Resources.Silver + modeldata.Resources.Perl
    assert newRes > oldRes
    
  def give_levelup_bonus_with_full_storage_test( self, env ):
    modeldata = env.acc.model

    modeldata.LordInfo.Fame = 0
    addValue = env.acc.SD.getMaxLordFame()
    resource1 = modeldata.Resources.Resource1 = 100
    resource2 = modeldata.Resources.Resource2 = 100
    resource3 = modeldata.Resources.Resource3 = 100
    modeldata.ResourcesLimit.Resource1 = 100
    modeldata.ResourcesLimit.Resource2 = 100
    modeldata.ResourcesLimit.Resource3 = 100
    silver = modeldata.Resources.Silver = 0
    perl = modeldata.Resources.Perl = 0
    oldRes = resource1 + resource2 + resource3

    requests = [ ( Give_fame, GiveFameRequest( modeldata, { "value" : ["" + str(addValue) + ""] }, False ) ) ]
    changeList = env.execActions( requests )

    assert modeldata.LordInfo.Fame == env.acc.SD.getMaxLordFame()
  
    newRes = modeldata.Resources.Resource1 + modeldata.Resources.Resource2 + modeldata.Resources.Resource3
    assert newRes > oldRes
