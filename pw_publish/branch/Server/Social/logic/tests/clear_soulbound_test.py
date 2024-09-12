import sys
sys.path.append('../')
from logic.clear_soulbound import *
from binascii import crc32
import time
from modeldata.changes import IGuidGenerator
sys.path.append('../..')
from enums import *
import EC


class clear_soulbound_test:
  def clear_soulbound_test( self, env ):
    modeldata = env.acc.model
    
    hero = env.add_hero(modeldata, "mowgly")
    talent = env.add_talent(modeldata, "G137") 

    talent.Soulbound = hero
    
    modeldata.UserInventory.add( talent ) 

    requests = [ ( Clear_soulbound, ClearSoulboundRequest( modeldata, {  }, False ) ) ]
    changeList = env.execActions( requests )

    assert( modeldata.getTalentByID(talent.id).Soulbound == IGuidGenerator.InvalidUID )   

  def clear_soulbound_many_test( self, env ):
    modeldata = env.acc.model
    
    hero = env.add_hero(modeldata, "mowgly")
    talent = env.add_talent(modeldata, "G137") 
    talent2 = env.add_talent(modeldata, "G137")
    
    modeldata.UserInventory.add( talent )    
    modeldata.UserInventory.add( talent2 )

    talent.Soulbound = hero
    talent2.Soulbound = hero

    requests = [ ( Clear_soulbound, ClearSoulboundRequest( modeldata, {  }, False ) ) ]
    changeList = env.execActions( requests )

    assert( modeldata.getTalentByID(talent.id).Soulbound == IGuidGenerator.InvalidUID ) 
    assert( modeldata.getTalentByID(talent2.id).Soulbound == IGuidGenerator.InvalidUID ) 