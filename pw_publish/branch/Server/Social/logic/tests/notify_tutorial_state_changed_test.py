import sys
sys.path.append('../')
sys.path.append('../..')
from logic.notify_tutorial_state_changed import *
from binascii import crc32
from base.helpers import *
from enums import *
import EC

class notify_tutorial_state_changed_test:

  def notify_tutorial_state_changed_test( self, env ):
    modeldata = env.acc.model
    modeldata.LordInfo.TutorialState = TutorialState.BattleQuestAdded

    requests =  [ ( Notify_tutorial_state_changed, NotifyTutorialStateChangedRequest( modeldata, { "newState" : ["" + str(TutorialState.Completed) + ""] }, False ) ) ]
    changeList = env.execActions( requests )

    assert modeldata.LordInfo.TutorialState == TutorialState.Completed