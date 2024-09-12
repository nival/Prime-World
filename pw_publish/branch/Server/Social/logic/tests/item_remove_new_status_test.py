import sys
sys.path.append('../')
from logic.item_remove_new_status import *
from binascii import crc32
sys.path.append('../..')
from enums import *

class item_remove_new_status_test:
  def item_remove_new_status_test( self, env ):  
    modeldata = env.acc.model
    
    talent = env.add_talent(modeldata, 'G137')
    modeldata.UserInventory.add( talent )
    talent.IsNew = True

    requests =  [ ( Item_remove_new_status , ItemRemoveNewStatusRequest( modeldata, {"talent_id" : ["" + str( talent.id ) + ""] }, False ) ) ]
    changeList = env.execActions( requests )

    assert( talent.IsNew == False )