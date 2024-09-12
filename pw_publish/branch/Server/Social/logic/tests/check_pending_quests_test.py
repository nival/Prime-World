import sys
sys.path.append('../')
sys.path.append('../..')
from logic.check_pending_quests import *
from binascii import crc32
from base.helpers import *
from enums import *

class check_pending_quests_test:

  def check_pending_quests_test( self, env ):
    modeldata = env.acc.model
    staticID = crc32('c11_qB')
    modeldata.PendingQuests.append(staticID)
       
    assert len( modeldata.PendingQuests ) == 1
    
    requests =  [ ( Check_pending_quests, CheckPendingQuestsRequest( modeldata,{  }, False ) ) ]
    changeList = env.execActions( requests )    

    assert len( modeldata.PendingQuests ) == 0