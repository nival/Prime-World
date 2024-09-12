import sys
sys.path.append('../')
sys.path.append('../..')
from logic.dlc_update import *
from binascii import crc32
from base.helpers import *
from enums import *
import EC
import cfg

class dlc_update_test:

  def dlc_update_test( self, env ):
    modeldata = env.acc.model

    requests =  [ ( Dlc_update, UpdateDLCRequest( modeldata, { "dlcIdx" : ["dlc_for_test"] }, False ) ) ]
    changeList = env.execActions( requests )


  def dlc_doubleapply_test( self, env ):
    modeldata = env.acc.model
    assert len( env.acc.db.dlcs ) == 0
    oldSilver = modeldata.Resources.Silver
    modeldata.tryApplyDLCs( ["dlc_for_test"], env.acc, env.I )
    assert len( env.acc.db.dlcs ) == 1
    assert (modeldata.Resources.Silver - oldSilver) == cfg.DLCs_INFO["dlc_for_test"]["Resources"]["Silver"]

    modeldata.tryApplyDLCs( ["dlc_for_test"], env.acc, env.I )
    assert len( env.acc.db.dlcs ) == 1
    assert (modeldata.Resources.Silver - oldSilver) == cfg.DLCs_INFO["dlc_for_test"]["Resources"]["Silver"]


  def dlc_multiapply_test( self, env ):
    modeldata = env.acc.model
    assert len( env.acc.db.dlcs ) == 0
    oldSilver = modeldata.Resources.Silver
    modeldata.tryApplyDLCs( ["dlc_for_test_multi"], env.acc, env.I )
    assert len( env.acc.db.dlcs ) == 1
    assert (modeldata.Resources.Silver - oldSilver) == cfg.DLCs_INFO["dlc_for_test_multi"]["Resources"]["Silver"]

    modeldata.tryApplyDLCs( ["dlc_for_test_multi"], env.acc, env.I )
    assert len( env.acc.db.dlcs ) == 1
    assert (modeldata.Resources.Silver - oldSilver) == 2*cfg.DLCs_INFO["dlc_for_test_multi"]["Resources"]["Silver"]


  def dlc_apply_ref_dlcs_test( self, env ):
    modeldata = env.acc.model
    assert len( env.acc.db.dlcs ) == 0
    modeldata.tryApplyDLCs( [ "ref_resources", "ref_premium", "ref_crystals", "ref_random_rar4_talent", "ref_random_rar5_talent" ], env.acc, env.I )
    assert len( env.acc.db.dlcs ) == 5

    modeldata.tryApplyDLCs( [ "ref_prince_unique_skin_a", "ref_prince_unique_skin_b" ], env.acc, env.I )
    assert len( env.acc.db.dlcs ) == 7

