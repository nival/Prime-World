import sys
sys.path.append('../')
sys.path.append('../..')
from logic.set_md_version import *
from binascii import crc32
from base.helpers import *
from enums import *
import EC

class set_md_version_test:

  def set_md_version_test( self, env ):
    modeldata = env.acc.model

    oldVersion = modeldata.version.revision
    requests =  [ ( Set_md_version, SetMDVersionRequest( modeldata, { "versionNum" : ["100500"] }, False ) ) ]
    changeList = env.execActions( requests )

    assert modeldata.version.revision != oldVersion
    assert modeldata.version.revision == 100500