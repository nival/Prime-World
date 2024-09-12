class AuctionService:
    METHOD_LIST = ['GetArtifactList',
                   'GetCharactersList',
                   'CreateLot',
                   'MakeBid',
                   'SearchArtifact',
                   'SearchLot',
                   'GetLotDetails',
                   'BuyMallItem',
                   'BuyLotBuyOutPriceBid',
                   'FinishAuction',
                   'GetPurchasesHistory',]

    def _method_call(self, method_name):
        def method(**kwargs):
            print method_name, kwargs
        return method
    def __getattr__(self, attr):
        if attr in self.METHOD_LIST:
            return self._method_call(attr)
        else:
            raise AttributeError()

from suds.client import Client
class SoapAuctionService(AuctionService):
    def __init__(self, url="http://b210.nivalnetwork.com:8037/Auction.asmx?wsdl"):
        self.url = url
        print "soap url:%r" % url
        self.client = Client(url)
        
    def _method_call(self, method_name):
        def method(**kwargs):
            if not "crc" in kwargs:
                kwargs["crc"] = "dummycrc"
            return dict(getattr(self.client.service, method_name)(kwargs))
        return method

import json
import urllib
import urllib2
class RestfulAuctionService(AuctionService):
    REQUEST_OBJECT_NAMES = {'GetArtifactList': 'getArtifactListReq',
                            'GetCharactersList': 'getCharacterListReq',
                            'CreateLot': 'createLotReq',
                            'MakeBid': 'makeBidReq',
                            'SearchArtifact': 'searchArtifactReq',
                            'SearchLot': 'searchLotReq',
                            'GetLotDetails': 'getLotDetailsReq',
                            'BuyMallItem': 'buyMallItemReq',
                            'BuyLotBuyOutPriceBid': 'buyOutReq',
                            'FinishAuction': 'finishAuctionReq',
                            'GetPurchasesHistory': 'getPurchasesHistoryReq', }
    def __init__(self, url="http://b210.nivalnetwork.com:8036/Auction"):
        self.url = url.rstrip('/')
    def _method_call(self, method_name):
        def method(**kwargs):
            #~ if not "crc" in kwargs:
                #~ kwargs["crc"] = "dummycrc"
            #~ dthandler = lambda obj: obj.isoformat() if isinstance(obj, datetime.datetime) else None
            #~ args = json.dumps(kwargs, default=dthandler, separators=(',',':'))
            #~ url = self.url + "/" + method_name + "?" + urllib.urlencode({self.REQUEST_OBJECT_NAMES[method_name]:args})
            
            args = ""
            method_key = self.REQUEST_OBJECT_NAMES[method_name]
            for name,value in kwargs.iteritems():
                args += "%s=%s&" % (name,value)
            if args:
                args = args[:-1]
            url = self.url + "/" + method_name + "?" + args
            
            print "rest url=%r" % url
            response = urllib2.urlopen(url).read()
            return json.loads(response)
        return method

import datetime

if __name__=='__main__':
    r = RestfulAuctionService()

##	print "REST GetArtifactList:"
##	print r.GetArtifactList(fromServiceName='Shaiya', categoryID=3, gameName='Shaiya')
##	print "SOAP GetArtifactList:"
##	print s.GetArtifactList(fromServiceName='Shaiya', categoryID=3, gameName='Shaiya')
##	print
##	print "REST GetCharactersList:"
##	print "(Doesn't work yet)"
###	print r.GetCharactersList(fromServiceName='Shaiya', gameName='Shaiya', userName='nkmrov2')
##	print "SOAP GetCharactersList:"
##	print s.GetCharactersList(fromServiceName='Shaiya', gameName='Shaiya', userName='nkmrov2')
##	print
##	print "REST CreateLot:"
##	print r.CreateLot(fromServiceName='Shaiya', artifactID='44', buyOutPrice='33', nominalPrice='33', character=333, count=3, finishTime=datetime.datetime.now()+datetime.timedelta(days=14), gameName='Shaiya' )
##	print "SOAP CreateLot:"
##	print s.CreateLot(fromServiceName='Shaiya', artifactID='44', buyOutPrice='33', nominalPrice='33', character=333, count=3, finishTime=datetime.datetime.now()+datetime.timedelta(days=14), gameName='Shaiya' )
##	print
##	print "REST MakeBid:"
##	print r.MakeBid(fromServiceName='Shaiya')
##	print "SOAP MakeBid:"
##	print s.MakeBid(fromServiceName='Shaiya')
##	print
##	print "REST SearchArtifact:"
##	print r.SearchArtifact(fromServiceName='Shaiya')
##	print "SOAP SearchArtifact:"
##	print s.SearchArtifact(fromServiceName='Shaiya')
##	print
    print "REST SearchLot:"
    print r.SearchLot(searchLotReq='{"lot":{"Skip":0,"Take":0,"Lot":"MySuperLot","AuctionRoomID":0,"Category":null,"CategoryID":0,"CurrentPrice":null,"BuyOutPrice":null,"IsAutoAuction":true,"Winner":null,"Creator":null,"IsActive":null,"Artefact":null,"StartTime":{"From":"\/Date(1305112271011)\/","To":"\/Date(1321009871011)\/"},"FinishTime":null,"Tags":[],"Attributes":[1,2,3],"GameName":"shaiya","Redro":null},"crc":null,"fromServiceName":"shaiya"}')
##	print "SOAP SearchLot:"
##	print s.SearchLot(fromServiceName='Shaiya')
##	print
##	print "REST GetLotDetails:"
##	print r.GetLotDetails(fromServiceName='Shaiya')
##	print "SOAP GetLotDetails:"
##	print s.GetLotDetails(fromServiceName='Shaiya')
##	print
##	print "REST BuyMallItem:"
##	print r.BuyMallItem(fromServiceName='Shaiya')
##	print "SOAP BuyMallItem:"
##	print s.BuyMallItem(fromServiceName='Shaiya')
##	print
##	print "REST BuyLotBuyOutPriceBid:"
##	print r.BuyLotBuyOutPriceBid(fromServiceName='Shaiya')
##	print "SOAP BuyLotBuyOutPriceBid:"
##	print s.BuyLotBuyOutPriceBid(fromServiceName='Shaiya')
##	print
##	print "REST FinishAuction:"
##	print r.FinishAuction(fromServiceName='Shaiya')
##	print "SOAP FinishAuction:"
##	print s.FinishAuction(fromServiceName='Shaiya')
##	print
##	print "REST GetPurchasesHistory:"
##	print r.GetPurchasesHistory(fromServiceName='Shaiya', gameName='Shaiya', userName='nkmrov2', dateTime={'From': datetime.datetime.now(), 'To': datetime.datetime.now() - datetime.timedelta(days=60)})
##	print "SOAP GetPurchasesHistory:"
##	print s.GetPurchasesHistory(fromServiceName='Shaiya', gameName='Shaiya', userName='nkmrov2', dateTime={'From': datetime.datetime.now(), 'To': datetime.datetime.now() - datetime.timedelta(days=60)})

##    s = SoapAuctionService()
