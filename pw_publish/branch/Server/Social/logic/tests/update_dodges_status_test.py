import sys, time
sys.path.append('../')
sys.path.append('../..')
from logic.add_dodges import *
from binascii import crc32
from base.helpers import *
from enums import *

class update_dodges_status_test:

  def update_dodges_status_test( self, env ):
    # dodges must be removed if last update time was more than 
    # EPIC_HERO_RETIRE_LIFETIME seconds ago

    modeldata = env.acc.model
    assert modeldata.LordInfo.GuardInfo.Dodges == 0
    requests =  [ ( Add_dodges, AddDodgesRequest( modeldata, { "dodges" : ["3"] }, False ) ) ]
    changeList = env.execActions( requests )

    assert modeldata.LordInfo.GuardInfo.Dodges == 3
    assert modeldata.LordInfo.GuardInfo.RetiredTime > 0
    assert modeldata.LordInfo.lastDodgesUpdateTime_ > 0
    # checks last dodges time was updated to current
    now = time.time()
    assert modeldata.LordInfo.lastDodgesUpdateTime_ > now - 1

    # emulating thas last dodge lifetime was expired
    modeldata.LordInfo.lastDodgesUpdateTime_ -= env.acc.getConfig().EPIC_HERO_RETIRE_LIFETIME

    modeldata.updateDodgesStatus( env.acc )
    # checking that dodges was cleared
    
    assert modeldata.LordInfo.GuardInfo.Dodges == 0
    assert modeldata.LordInfo.GuardInfo.RetiredTime == 0
    # checks last dodges time was updated to current
    now = time.time()
    assert modeldata.LordInfo.lastDodgesUpdateTime_ > now - 1