import sys
sys.path.append('../')
from logic.set_new_status import *
from binascii import crc32
sys.path.append('../..')

class set_new_status_test:
  def set_new_status_test( self, env ):
    modeldata = env.acc.model
    talent = env.add_talent(modeldata, "G137")
    modeldata.UserInventory.add( talent )

    requests =  [ ( Set_new_status, SetNewStatusRequest( modeldata, { "talent_id" : ["" + str(talent.id) + ""] }, False ) ) ]
    changeList = env.execActions( requests )

    assert talent.IsNew == True