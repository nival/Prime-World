import sys
sys.path.append('../')
sys.path.append('../..')
from logic.guild_invest_resources import *
from binascii import crc32
from base.helpers import *
from enums import *
import EC

class guild_invest_resources_test:

  def guild_invest_resources_test( self, env ):
    env.acc.db.guildAuid = 100500
    modeldata = env.acc.model
    amount = 100500
    res1 = modeldata.Resources.Resource1 = amount

    requests = [ ( Guild_invest_resources, GuildInvestResourcesRequest( modeldata, { "res1" : [amount], "res2" : [0], "res3" : [0] , "silver" : [0]}, False ) ) ]
    changeList = env.execActions( requests )
    
    assert modeldata.Resources.Resource1 == 0
    
  def guild_invest_many_resources_test( self, env ):
    env.acc.db.guildAuid = 100500
    modeldata = env.acc.model
    amount = 100500
    res1 = modeldata.Resources.Resource1 = amount
    res2 = modeldata.Resources.Resource2 = amount
    res3 = modeldata.Resources.Resource3 = amount
    silver = modeldata.Resources.Silver = amount

    requests = [ ( Guild_invest_resources, GuildInvestResourcesRequest( modeldata, { "res1" : [amount], "res2" : [amount], "res3" : [amount], "silver" : [amount] }, False ) ) ]
    changeList = env.execActions( requests )
    
    assert modeldata.Resources.Resource1 == 0
    assert modeldata.Resources.Resource2 == 0
    assert modeldata.Resources.Resource3 == 0
    assert modeldata.Resources.Silver == 0
    
  def guild_invest_many_resources_test( self, env ):
    env.acc.db.guildAuid = 100500
    modeldata = env.acc.model
    amount = 100500
    res1 = modeldata.Resources.Resource1 = amount
    res2 = modeldata.Resources.Resource2 = amount
    res3 = modeldata.Resources.Resource3 = amount
    silver = modeldata.Resources.Silver = amount

    requests = [ ( Guild_invest_resources, GuildInvestResourcesRequest( modeldata, { "res1" : [amount + 1], "res2" : [amount], "res3" : [amount], "silver" : [amount] }, False ) ) ]
    changeList = env.execActions( requests )
    
    changeList[0]['ec'] = EC.NOT_ENOUGH_RESOURCES
    
    assert modeldata.Resources.Resource1 == amount
    assert modeldata.Resources.Resource2 == amount
    assert modeldata.Resources.Resource3 == amount
    assert modeldata.Resources.Silver == amount