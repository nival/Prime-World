import sys
sys.path.append('../')
from logic.add_ignore import *
from binascii import crc32
sys.path.append('../..')
from enums import *

class add_ignore_test:
  def add_ignore_test( self, env ):
    modeldata = env.acc.model

    requests =  [ ( Add_ignore, AddIgnoreRequest( modeldata, { "auid" : ["20"], "reason" : ["you're looser"] }, False ) ) ]
    changeList = env.execActions( requests )


