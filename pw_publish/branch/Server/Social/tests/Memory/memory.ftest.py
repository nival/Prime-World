# -----------------------------------------------
# Start program 
import time
import os
import sys
import json
from logging import info
import logging
import gc

gc.disable() 
logging.getLogger().setLevel(logging.INFO)


os.chdir('../..')
sys.path.append( os.path.abspath('.') )
sys.path.append( os.path.abspath('cfg') )
N = 0

print 'Start'
time.sleep(N)

# -----------------------------------------------
# Import game code
import coord_cfg

import modeldata.persistent_data
import base.helpers

from modeldata.ModelData import ModelData
from friendsdata.FriendsData import FriendsData
from party.PartyData import PartyData

print 'Import'
time.sleep(N)

# -----------------------------------------------
# Create environment
options_xdb_path = "xdb"
modeldata_path = os.path.realpath("modeldata")
info("modeldata_path: %s" % modeldata_path)
I = base.helpers.ClassDict()
I.coord_res = { 'deploy_name' : 'RU' }

modeldata.persistent_data.createStandalonePersistentInterface(I, options_xdb_path, modeldata_path)

pdm = modeldata.persistent_data.PersistentDataManager(I)
print 'Create env'
time.sleep(N)

# -----------------------------------------------
# Create account
acc = base.helpers.ClassDict( uid=1, guest=1, pending_events=[] )
acc.sex = 0 
acc.loaded = 1
acc.db = base.helpers.ClassDict()
acc.data = base.helpers.ClassDict()
acc.db.fraction = "A"
acc.db.nick = "RedJack"
acc.db.nickChanged = 0
acc.db.fractionChanged = 0
acc.db.Gold = 100
acc.auid = 6109
acc.snid = "fb"
acc.snuid = "100001"
acc.Config = I.Config
acc.SD = I.SD

f = open('tests/Memory/6109.json', 'rb')
data = json.load(f)

print 'Load data'
time.sleep(N)

# -----------------------------------------------
# Load account
pdm.loadAccountData( acc, data['data'] )

print 'Create model'
time.sleep(N)
