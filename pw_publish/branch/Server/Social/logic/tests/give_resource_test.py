import sys
sys.path.append('../')
from logic.give_resource import *
from binascii import crc32
sys.path.append('../..')
from enums import *

class give_resource_test:
  def give_resource_silver_test( self, env ):
    modeldata = env.acc.model

    silver = modeldata.Resources.Silver = 100
    addValue = 100

    requests =  [ ( Give_resource, GiveResourceRequest( modeldata, { "resource" : ["Silver"], "value" : ["" + str(addValue) + ""] }, False ) ) ]
    changeList = env.execActions( requests )

    assert( modeldata.Resources.Silver == silver + addValue )   
    
  def give_resource_negative_test( self, env ):
    modeldata = env.acc.model

    silver = modeldata.Resources.Resource1 = 100
    addValue = -100

    requests =  [ ( Give_resource, GiveResourceRequest( modeldata, { "resource" : ["Resource1"], "value" : ["" + str(addValue) + ""] }, False ) ) ]
    changeList = env.execActions( requests )

    assert( modeldata.Resources.Resource1 == 0 ) 
    
  def give_resource_negative2_test( self, env ):
    modeldata = env.acc.model

    silver = modeldata.Resources.Resource1 = 100
    addValue = -200

    requests =  [ ( Give_resource, GiveResourceRequest( modeldata, { "resource" : ["Resource1"], "value" : ["" + str(addValue) + ""] }, False ) ) ]
    changeList = env.execActions( requests )

    assert( modeldata.Resources.Resource1 == 0 )

  def give_resource_shard_test( self, env ):
    modeldata = env.acc.model

    modeldata.Resources.Shard = 100
    addValue = 100

    requests =  [ ( Give_resource, GiveResourceRequest( modeldata, { "resource" : ["Shard"], "value" : ["" + str(addValue) + ""] }, False ) ) ]
    changeList = env.execActions( requests )

    # assert( modeldata.Resources.Resource1 == limit )
    
  def give_resource_max_int_test( self, env ):
    modeldata = env.acc.model

    silver = modeldata.Resources.Resource1 = 100
    limit = 2147483647#int limit in C#

    requests =  [ ( Give_resource, GiveResourceRequest( modeldata, { "resource" : ["Resource1"], "value" : ["" + str(limit) + ""] }, False ) ) ]
    changeList = env.execActions( requests )

    assert( modeldata.Resources.Resource1 == limit )

  def give_resource_custom_currency_test(self, env):
    modeldata = env.acc.model

    modeldata.Resources.Shard = 100
    addValue = 100

    requests = [(Give_resource,
                 GiveResourceRequest(modeldata, {"resource": ["Currency:testCurrencyId"], "value": ["" + str(addValue) + ""]}, False))]
    changeList = env.execActions(requests)

    assert (modeldata.Resources.Currencies["testCurrencyId"] == addValue)


