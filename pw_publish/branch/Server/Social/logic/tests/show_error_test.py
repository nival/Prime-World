import sys
sys.path.append('../')
from logic.show_error import *
from binascii import crc32
sys.path.append('../..')

class show_error_test:
  def show_error_test( self, env ):
    modeldata = env.acc.model

    requests =  [ ( Show_error, ShowErrorRequest( modeldata, { "code" : [52], "args" : ["cost:100501, gold:100500"] }, False ) ) ]
    changeList = env.execActions( requests )

  def show_unknown_error_test( self, env ):
    modeldata = env.acc.model

    requests =  [ ( Show_error, ShowErrorRequest( modeldata, { "code" : [100500] }, False ) ) ]
    changeList = env.execActions( requests )


