import sandbox

import sys
sys.path.append('../../services/common/py')
import System.logs
import Network.Web.sandbox

System.logs.setup('sa.log', 'debug')


#ec2-46-137-34-36.eu-west-1.compute.amazonaws.com
agg = Network.Web.sandbox.Caller('http://ec2-46-137-34-36.eu-west-1.compute.amazonaws.com:8080', version='0.3.94')

def ShowInfo(auid, snid='fb'):
    return agg.get_info(auid=auid, include_secure_data=1)

#ShowInfo(2)

def LoginPWC(snuid):
    acc = agg.login(snid='pwc', sntoken='token', snuid=snuid, auto=0)
    agg.get_info(auid=acc.auid, include_secure_data=1)
    return acc
  #  agg.join(auid=acc.auid, snid='fb', snuid='100000204558976', sntoken='AAAB9M8ptmXMBAPVtdlCb4kKyylG5vcjwIlOZAw4XB7iZAa2xZCsxTAwWZB9ro2bjdHH2cihKIasI1CzuPEH7hE861ZCvVxdbAZAxDa4iYUugZDZD')


    #acc1 = agg.login(snid='fb', sntoken='AAAB9M8ptmXMBAMHLXgq3nHYiG5wWigZCZAwdukElKUlvyV6Y1IlxSyUOaZC2QZCeMZCysR8A7eBDatqa1S0kMOaLEEuKC9daWlfT2BvBbpgZDZD', snuid='100003543598114', auto=0)
    #if acc1.error != 0:
    #    acc1 = agg.register(snid='fb', sntoken='AAAB9M8ptmXMBAMHLXgq3nHYiG5wWigZCZAwdukElKUlvyV6Y1IlxSyUOaZC2QZCeMZCysR8A7eBDatqa1S0kMOaLEEuKC9daWlfT2BvBbpgZDZD', snuid='100003543598114')
    #agg.get_info(auid=acc1.auid, include_secure_data=1)
    #agg.merge(auid1=acc.auid, auid2=acc1.auid)

    #agg.get_info(auid=acc.auid, include_secure_data=1)

def Merge(auid1, auid2):
    agg.merge(auid1=auid1, auid2=auid2)
    agg.get_info(auid=auid1, include_secure_data=1)
    agg.get_info(auid=auid2, include_secure_data=1)
 
def Show(auid):
    agg.get_info(auid=auid, include_secure_data=1)

def Find(snid, snuid):
    return agg.find_user(snid=snid, snuid=snuid)

#agg.get_friends_info_all(auid=45106)

#acc0 = Find('fb', '100000204558976')
#ShowInfo(acc0.auid)
acc0 = ShowInfo(45106)
#acc1 = ShowInfo(83412)
#Merge(83412, 45106)
#ShowInfo(83396)
#ShowInfo(83398)


#acc1 = LoginPWC('505418866491393')

#Merge(acc0.auid, acc1.auid)

#LoginPWConnect()
#Find('pwc', '375702264217609')