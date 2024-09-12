import sys
sys.path.append('../')
from logic.add_talent import *
from binascii import crc32
import time
sys.path.append('../..')
from enums import *

class group_answer_test:
  def group_answer_test( self, env ):
    modeldata = env.acc.model

    persistentId = -1828546151
    
    requests = [ ( Add_talent, AddTalentRequest( modeldata, { "static_talent_id" : ["" + str(persistentId) + ""], "rid" : "0" }, False ) ) ]
    changeList = env.execActions( requests )
    text = str(changeList)
    assert text.count( "upd" ) == 1 or text.count( "upd" ) == 2
