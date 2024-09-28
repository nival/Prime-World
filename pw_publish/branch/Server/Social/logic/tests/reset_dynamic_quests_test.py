import sys
sys.path.append('../')
sys.path.append('../..')
from logic.reset_dynamic_quests import *
from binascii import crc32
from base.helpers import *
from enums import *
import EC

class reset_dynamic_quests_test:

  def reset_dynamic_quests_test( self, env ):
    model = env.acc.model
    model.CompletedDynamicQuests.append(1)
    model.CompletedDynamicQuests.append(2)
    model.CompletedDynamicQuests.append(111)

    assert len(model.CompletedDynamicQuests) == 3

    requests = [ ( Reset_dynamic_quests, ResetDynamicQuestsRequest( model, { }, False ) ) ]
    changeList = env.execActions( requests )

    assert len(model.CompletedDynamicQuests) == 0