import sys
sys.path.append('../')
from logic.reset_new_talents import *
from binascii import crc32
sys.path.append('../..')
from enums import *

class reset_new_talents_test:
  def reset_new_talents_test( self, env ):
    modeldata = env.acc.model
    talent = env.add_talent(modeldata, "G137")
    modeldata.UserInventory.add( talent )
    talent.IsNew = True

    requests = [ ( Reset_new_talents, ResetNewTalentsRequest( modeldata, {  }, False ) ) ]
    changeList = env.execActions( requests )

    assert talent.IsNew == False  

  def reset_new_talents_many_test( self, env ):
    modeldata = env.acc.model
    talent = env.add_talent(modeldata, "G137")
    talent.IsNew = True
    talent2 = env.add_talent(modeldata, "G137")
    talent2.IsNew = True
    requests = [ ( Reset_new_talents, ResetNewTalentsRequest( modeldata, {  }, False ) ) ]
    changeList = env.execActions( requests )

    assert talent.IsNew == False 
    assert talent2.IsNew == False  