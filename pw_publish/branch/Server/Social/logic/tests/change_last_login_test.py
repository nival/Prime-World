import sys
sys.path.append('../')
from logic.change_last_login import *
from binascii import crc32
from base.helpers import *
sys.path.append('../..')
from enums import *

class change_last_login_test:

  def change_last_login_test( self, env ):
    modeldata = env.acc.model
    
    modeldata.LordInfo.LastLoginTime = 100500
    modeldata.LordInfo.CurrentLoginTime = 100500

    requests =  [ ( Change_last_login, ChangeLastLoginRequest( modeldata, {"days" : [60] }, False ) ) ]
    changeList = env.execActions( requests )
    
    assert modeldata.LordInfo.LastLoginTime == 100500 - 60*60*60*24
    assert modeldata.LordInfo.CurrentLoginTime == 100500