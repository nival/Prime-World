import sys
sys.path.append('../../services/common/py')

import System.logs
import Network.Web.sandbox

System.logs.setup(None, 'debug')

host = sys.argv[1]
snid = sys.argv[2]
auid = sys.argv[3]
#agg = Network.Web.sandbox.Caller(host, version='0.3.93')
agg = Network.Web.sandbox.Caller(host, version='0.1.5')

data0 = agg.get_info(auid=auid, include_secure_data=1)
data1 = agg.get_candidates_info_all(auid=auid, snid=snid)
#if data0.error == 0:
#    data1 = agg.delete_sn(auid=auid, snid=snid)
#    if data1.error == 0:
#        agg.get_info(auid=auid, include_secure_data=1)
if len(sys.argv) > 4:
    snuid = sys.argv[4]
data2 = agg.login(snid=snid, snuid=snuid, verify=0)
# '100000257782810'

