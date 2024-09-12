import sys
sys.path.append('../')
from logic.remove_ignore import *
from binascii import crc32
sys.path.append('../..')
from enums import *

class remove_ignore_test:
  def remove_ignore_test( self, env ):
    modeldata = env.acc.model

    requests =  [ ( Remove_ignore, RemoveIgnoreRequest( modeldata, { "auid" : ["20"] }, False ) ) ]
    changeList = env.execActions( requests )

