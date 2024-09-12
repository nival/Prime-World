import sys
sys.path.append('../')
from logic.add_talent import *
from binascii import crc32
sys.path.append('../..')
from enums import *

class add_talent_test:
  def add_talent_test( self, env ):
    modeldata = env.acc.model

    PersistentId = -1828546151
    id = modeldata.next_uid_ + 1
    defaultinventoryLength = len(modeldata.UserInventory)

    requests = [ ( Add_talent, AddTalentRequest( modeldata, { "static_talent_id" : ["" + str(PersistentId) + ""] }, False ) ) ]
    changeList = env.execActions( requests )

    assert len(modeldata.UserInventory) == 1 + defaultinventoryLength

    talent_id = id

    assert( modeldata.getTalentByID(talent_id).PersistentId == PersistentId )
    assert( modeldata.getTalentByID(talent_id).IsNew == True )
    assert( talent_id in modeldata.UserInventory )

  def add_talent_for_new_sn( self, env ):
    modeldata = env.acc.model

    defaultinventoryLength = len(modeldata.UserInventory)
    talentId = modeldata.next_uid_ + 1
    modeldata.giveBonusTalent( 1, ['vk'], env.I.Config.getConfig( env.acc.userlocale ), env.acc, env.I )
    assert len(modeldata.UserInventory) == 1 + defaultinventoryLength
    talent = modeldata.getTalentByID( talentId )
    assert talent.PersistentId == 1124223207
    modeldata.giveBonusTalent( 0, [], env.I.Config.getConfig( env.acc.userlocale ), env.acc, env.I )
    assert len(modeldata.UserInventory) == 1 + defaultinventoryLength
    modeldata.giveBonusTalent( 45, [], env.I.Config.getConfig( env.acc.userlocale ), env.acc, env.I )
    assert len(modeldata.UserInventory) == 1 + defaultinventoryLength