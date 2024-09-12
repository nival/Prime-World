import sys

sys.path.append('../')
from logic.collect_production_results import *
from logic.start_building_production import *
from logic.stop_building_production import *
from logic.keepalive import *
from logic.buy_cycle import *
from binascii import crc32
import time, datetime
from modeldata.StaticData import StaticData

sys.path.append('../..')
from enums import *


class collect_production_results_test:
    def collect_production_results_repeated_test(self, env):
        modeldata = env.acc.model
        env.I.Config.getMainConfig().CHECK_REQUESTS_REPEATABILITY = True
        construction = env.add_construction(modeldata, "Production_Crystal")
        construction.cycle = 0
        construction.ProductionState = ProductionState.Busy
        construction.StartProductionTime = modeldata.FatClientServerTime - 1200

        for x in xrange(20):
            requests = [(Collect_production_results,
                         CollectProductionResultsRequest(modeldata,
                                                         {"construction_id": ["" + str(construction.id) + ""],
                                                          "client_time": [
                                                              "" + str(modeldata.FatClientServerTime) + ""]}, False))]
            env.execActions(requests)

    def collect_production_results_tavern_test(self, env):
        modeldata = env.acc.model
        env.I.Config.getMainConfig().CHECK_REQUESTS_REPEATABILITY = True

        modeldata.Resources = env.generate_resources(1000000)
        construction = env.add_construction(modeldata, "Tavern", 2)
        construction.cycle = 0
        construction.ProductionState = ProductionState.Idle
        construction.StartProductionTime = modeldata.FatClientServerTime - 1200

        for x in xrange(1):
            request = [(Start_building_production, StartBuildingProductionRequest(modeldata, {
                "construction_id": ["" + str(construction.id) + ""], "cycle": [str(0)], "aftercontext": ["false"]},
                                                                                   False))]
            env.execActions(request)
            time.sleep(1)

            request = [
                (Buy_cycle, BuyCycleRequest(modeldata, {"construction_id": ["" + str(construction.id) + ""]}, False))]
            env.execActions(request)
            time.sleep(1)

            requests = [(Collect_production_results, CollectProductionResultsRequest(modeldata, {
                "construction_id": ["" + str(construction.id) + ""],
                "client_time": ["" + str(modeldata.FatClientServerTime) + ""]}, False))]
            env.execActions(requests)

    def collect_production_results_with_stop_repeated_test(self, env):
        modeldata = env.acc.model
        env.I.Config.getMainConfig().CHECK_REQUESTS_REPEATABILITY = True

        construction_ = env.add_construction(modeldata, "Tavern")
        construction_.cycle = 0
        construction_.ProductionState = ProductionState.Busy
        construction_.StartProductionTime = modeldata.FatClientServerTime - 1200

        construction = env.add_construction(modeldata, "Production_Crystal", 10)
        construction.cycle = 0
        construction.ProductionState = ProductionState.Busy
        construction.StartProductionTime = modeldata.FatClientServerTime - 1200

        for x in xrange(3):
            request = [(Stop_building_production,
                        StopBuildingProductionRequest(modeldata, {"construction_id": ["" + str(construction.id) + ""]},
                                                      False))]
            env.execActions(request)

            time.sleep(1)

            requests = [(Collect_production_results, CollectProductionResultsRequest(modeldata, {
                "construction_id": ["" + str(construction.id) + ""],
                "client_time": ["" + str(modeldata.FatClientServerTime) + ""]}, False))]
            env.execActions(requests)

    def collect_production_results_pearl_cheat_test(self, env):
        modeldata = env.acc.model
        env.I.Config.getMainConfig().CHECK_REQUESTS_REPEATABILITY = False
        construction = env.add_construction(modeldata, "Production_Crystal")
        construction.cycle = 0
        construction.ProductionState = ProductionState.Finished
        construction.StartProductionTime = modeldata.FatClientServerTime - 3600*46
        modeldata.LordInfo.PremiumAccountEnd = modeldata.FatClientServerTime + 100500
        perl = modeldata.Resources.Perl = 10
        diff_time = 1000000000
        diff_time1 = 900000000
        profit = 0

        for x in xrange(20):
            if x % 2 == 0:
                client_time = modeldata.FatClientServerTime - diff_time
            else:
                client_time = modeldata.FatClientServerTime - diff_time1
            requests = [(Collect_production_results,
                         CollectProductionResultsRequest(modeldata,
                                                         {"construction_id": ["" + str(construction.id) + ""],
                                                          "client_time": [
                                                              "" + str(client_time) + ""]}, False))]

            env.execActions(requests)
            profit += modeldata.Resources.Perl - perl


        profit += modeldata.Resources.Perl - perl
        assert profit == 0

    def collect_production_results_test(self, env):
        modeldata = env.acc.model

        construction = env.add_construction(modeldata, "Production_Resource1")
        construction.cycle = 0
        construction.ProductionState = ProductionState.Busy
        construction.StartProductionTime = modeldata.FatClientServerTime - 1200

        silver = modeldata.Resources.Silver = 1000
        resource1 = modeldata.Resources.Resource1 = 100

        requests = [(Collect_production_results,
                     CollectProductionResultsRequest(modeldata,
                                                     {"construction_id": ["" + str(construction.id) + ""],
                                                      "client_time": ["" + str(modeldata.FatClientServerTime) + ""]}, False) )]
        changeList = env.execActions(requests)

        assert construction.ProductionState == ProductionState.Busy

        profit = modeldata.Resources.Resource1 - resource1
        cost = silver - modeldata.Resources.Silver

        assert profit > 0
        assert cost == 0
        assert construction.StartProductionTime == modeldata.FatClientServerTime
        assert construction.EndProductionTime == 0

    def collect_production_results_Resource1_test(self, env):
        modeldata = env.acc.model

        construction = env.add_construction(modeldata, "Production_Resource1")
        construction.cycle = 0
        construction.ProductionState = ProductionState.Finished
        construction.StartProductionTime = modeldata.FatClientServerTime - 1200

        silver = modeldata.Resources.Silver = 1000
        resource1 = modeldata.Resources.Resource1 = 100

        requests = [(Collect_production_results,
                     CollectProductionResultsRequest(modeldata,
                                                     {"construction_id": ["" + str(construction.id) + ""],
                                                      "client_time": ["" + str(modeldata.FatClientServerTime) + ""]}, False) )]
        changeList = env.execActions(requests)

        assert construction.ProductionState == ProductionState.Busy

        profit = modeldata.Resources.Resource1 - resource1
        cost = silver - modeldata.Resources.Silver

        assert profit > 0
        assert cost == 0
        assert construction.StartProductionTime == modeldata.FatClientServerTime

    @staticmethod
    def collect_production_results_with_add_buf_test(env):
        model_data = env.acc.model
        model_data.FatClientServerTime = int(time.time())
        staticBuff = env.acc.SD.getGuildBufById(crc32('Buf13'))
        assert staticBuff
        construction = env.add_construction(model_data, "Production_Resource3")
        period_time = env.acc.SD.getStaticConstruction(construction)['productionTimePeriod']

        construction.cycle = 0
        construction.ProductionState = ProductionState.Busy
        construction.StartProductionTime = model_data.FatClientServerTime - period_time

        resource3 = model_data.Resources.Resource3 = 0
        model_data.ResourcesLimit.Resource3 = 10000

        requests = [(Collect_production_results,
                     CollectProductionResultsRequest(model_data,
                                                     {"construction_id": ["" + str(construction.id) + ""],
                                                      "client_time": ["" + str(model_data.FatClientServerTime) + ""]}, False) )]
        env.execActions(requests)

        single_profit = model_data.Resources.Resource3 - resource3
        assert single_profit > 0

        expireTime = int(model_data.FatClientServerTime)
        env.acc.model.addGuildBuff(env.acc, env.acc.SD, expireTime, staticBuff)

        construction.cycle = 0
        construction.ProductionState = ProductionState.Busy
        construction.StartProductionTime = model_data.FatClientServerTime - period_time

        resource3 = model_data.Resources.Resource3 = 0
        model_data.ResourcesLimit.Resource3 = 10000

        requests = [(Collect_production_results,
                     CollectProductionResultsRequest(model_data,
                                                     {"construction_id": ["" + str(construction.id) + ""],
                                                      "client_time": ["" + str(model_data.FatClientServerTime) + ""]}, False) )]
        env.execActions(requests)

        buffed_profit = model_data.Resources.Resource3 - resource3

        assert buffed_profit > 0
        assert buffed_profit > single_profit

        expireTime = int(model_data.FatClientServerTime - period_time / 2)
        env.acc.model.addGuildBuff(env.acc, env.acc.SD, expireTime, staticBuff)

        construction.cycle = 0
        construction.ProductionState = ProductionState.Busy
        construction.StartProductionTime = model_data.FatClientServerTime - period_time

        resource3 = model_data.Resources.Resource3 = 0
        model_data.ResourcesLimit.Resource3 = 10000

        requests = [(Collect_production_results,
                     CollectProductionResultsRequest(model_data,
                                                     {"construction_id": ["" + str(construction.id) + ""],
                                                      "client_time": ["" + str(model_data.FatClientServerTime) + ""]}, False) )]
        env.execActions(requests)

        mixed_profit = model_data.Resources.Resource3 - resource3

        assert mixed_profit > 0
        assert mixed_profit > single_profit
        assert buffed_profit > mixed_profit

        delta = buffed_profit - single_profit
        assert mixed_profit == int((single_profit * 0.5) + ((single_profit + delta) * 0.5))

    def collect_production_results_Resource3_with_bufMult_test(self, env):

       # env.add_guild_buff('Buf14')
        env.add_guild_buff('Buf19')
        env.add_guild_buff('Buf24')
       # env.add_guild_buff('Buf31')

        modeldata = env.acc.model

        construction = env.add_construction(modeldata, "Production_Resource2", 18)
        construction.cycle = 0
        #construction.Level = 18
        modeldata.FatClientServerTime = int(time.time())
        construction.ProductionState = ProductionState.Finished
        construction.StartProductionTime = modeldata.FatClientServerTime - 82800
        modeldata.LordInfo.PremiumAccountEnd = modeldata.FatClientServerTime + 100500

        #silver = modeldata.Resources.Silver = 1000
        resource_res = modeldata.Resources.Resource2 = 0
        modeldata.ResourcesLimit.Resource2 = 50000

        client_time = modeldata.FatClientServerTime
        requests = [(Collect_production_results,
                     CollectProductionResultsRequest(modeldata,
                                                     {"construction_id": ["" + str(construction.id) + ""],
                                                      "client_time": ["" + str(client_time) + ""]}, False) )]
        changeList = env.execActions(requests)

        assert construction.ProductionState == ProductionState.Busy
        profit = modeldata.Resources.Resource2 - resource_res
        # cost = silver - modeldata.Resources.Silver

        assert profit == 8240
        # assert cost == 0
        assert construction.StartProductionTime == client_time

    def collect_production_results_house_test(self, env):
        # No more production in houses
        return
        modeldata = env.acc.model

        construction = env.add_construction(modeldata, "House_4")

        construction.cycle = 0
        construction.ProductionState = ProductionState.Finished
        construction.ProductionPremium = False
        construction.StartProductionTime = modeldata.FatClientServerTime - 1200

        silver = modeldata.Resources.Silver = 1000
        resource1 = modeldata.Resources.Resource1 = 100

        requests = [(Collect_production_results,
                     CollectProductionResultsRequest(modeldata,
                                                     {"construction_id": ["" + str(construction.id) + ""],
                                                      "client_time": ["" + str(modeldata.FatClientServerTime) + ""]}, False) )]
        changeList = env.execActions(requests)

        assert construction.ProductionState == ProductionState.Finished

        profit = modeldata.Resources.Silver - silver
        assert profit > 0
        staticConstruction = env.acc.SD.getStaticConstruction(construction)
        finalprice = StaticData.getPriceInterpolated(staticConstruction['HouseLevels'], construction.Level, -1,
                                                     "resourcesToProduce", None)
        assert profit == finalprice.Silver

    def collect_production_results_house_with_PA_test(self, env):
        # No more production in houses
        return
        modeldata = env.acc.model

        construction = env.add_construction(modeldata, "House_1")

        construction.cycle = 0
        construction.ProductionState = ProductionState.Finished
        construction.ProductionPremium = True
        construction.StartProductionTime = modeldata.FatClientServerTime - 1200

        silver = modeldata.Resources.Silver = 1000
        resource1 = modeldata.Resources.Resource1 = 100

        requests = [(Collect_production_results,
                     CollectProductionResultsRequest(modeldata,
                                                     {"construction_id": ["" + str(construction.id) + ""],
                                                      "client_time": ["" + str(modeldata.FatClientServerTime) + ""]}, False) )]
        changeList = env.execActions(requests)

        assert construction.ProductionState == ProductionState.Finished

        profit = modeldata.Resources.Silver - silver
        assert profit > 0
        staticConstruction = env.acc.SD.getStaticConstruction(construction)
        finalprice = StaticData.getPriceInterpolated(staticConstruction['HouseLevels'], construction.Level, -1,
                                                     "resourcesToProduce", None)
        bonus = int(env.I.Config.getConfig(env.acc.userlocale).PREMIUM_ACCOUNT_BONUS)
        assert profit == finalprice.Silver * bonus

    def collect_talent_production_results_test(self, env):
        modeldata = env.acc.model

        construction = env.add_construction(modeldata, "Talent_Production")
        construction.cycle = 0
        construction.ProductionState = ProductionState.Busy
        construction.EndProductionTime = 1

        requests = [( Keepalive, KeepaliveRequest(modeldata, {}, False) )]
        changeList = env.execActions(requests)

        assert construction.ProductionState == ProductionState.Finished

    def collect_premium_production_results_test(self, env):
        modeldata = env.acc.model

        construction = env.add_construction(modeldata, "Production_Resource1")
        construction.cycle = 0
        construction.ProductionState = ProductionState.Finished
        construction.StartProductionTime = modeldata.FatClientServerTime - 3600

        Silver = modeldata.Resources.Silver = 0
        Resource1 = modeldata.Resources.Resource1 = 0

        requests = [(Collect_production_results,
                     CollectProductionResultsRequest(modeldata,
                                                     {"construction_id": ["" + str(construction.id) + ""],
                                                      "client_time": ["" + str(modeldata.FatClientServerTime) + ""]}, False) )]
        changeList = env.execActions(requests)

        assert construction.ProductionState == ProductionState.Busy

        profit = modeldata.Resources.Resource1 - Resource1
        cost = Silver - modeldata.Resources.Silver

        assert profit > 0
        staticConstruction = env.acc.SD.getStaticConstruction(construction)
        limit = env.acc.SD.getPriceInterpolated(staticConstruction["ProductionLevels"], 0, None, "totalProduceCapacity", None, True)

        construction.ProductionState = ProductionState.Finished
        construction.StartProductionTime = modeldata.FatClientServerTime - 3600*23
        modeldata.LordInfo.PremiumAccountEnd = modeldata.FatClientServerTime - 1200*23

        Silver = modeldata.Resources.Silver = 0
        Resource1 = modeldata.Resources.Resource1 = 0
        cTime = modeldata.FatClientServerTime

        requests = [(Collect_production_results,
                     CollectProductionResultsRequest(modeldata,
                                                     {"construction_id": ["" + str(construction.id) + ""],
                                                      "client_time": ["" + str(cTime) + ""]}, False) )]
        changeList = env.execActions(requests)

        construction = modeldata.getConstructionByID(construction.id)
        assert construction != None
        assert construction.ProductionState == ProductionState.Busy

        premiumProfit = modeldata.Resources.Resource1 - Resource1
        premiumcost = Silver - modeldata.Resources.Silver

        assert premiumProfit > 0
        assert premiumProfit > limit["Resource1"]

        construction.ProductionState = ProductionState.Finished
        construction.StartProductionTime = modeldata.FatClientServerTime - 3600
        modeldata.LordInfo.PremiumAccountEnd = modeldata.FatClientServerTime + 1200*23

        Silver = modeldata.Resources.Silver = 0
        Resource1 = modeldata.Resources.Resource1 = 0
        cTime = modeldata.FatClientServerTime

        requests = [(Collect_production_results,
                     CollectProductionResultsRequest(modeldata,
                                                     {"construction_id": ["" + str(construction.id) + ""],
                                                      "client_time": ["" + str(cTime) + ""]}, False) )]
        changeList = env.execActions(requests)

        construction = modeldata.getConstructionByID(construction.id)
        assert construction != None
        assert construction.ProductionState == ProductionState.Busy

        premiumProfit = modeldata.Resources.Resource1 - Resource1
        premiumcost = Silver - modeldata.Resources.Silver

        assert premiumProfit > 0
        assert premiumcost == 0
        assert premiumProfit == profit * env.I.Config.getConfig(env.acc.userlocale).PREMIUM_ACCOUNT_BONUS
        assert construction.StartProductionTime == cTime

    def collect_premium_production_results_test2(self, env):
        modeldata = env.acc.model

        construction = env.add_construction(modeldata, "Production_Resource2")
        construction.cycle = 0
        construction.ProductionState = ProductionState.Finished
        construction.StartProductionTime = modeldata.FatClientServerTime - 3600

        Silver = modeldata.Resources.Silver = 0
        Resource2 = modeldata.Resources.Resource2 = 0

        requests = [(Collect_production_results,
                     CollectProductionResultsRequest(modeldata,
                                                     {"construction_id": ["" + str(construction.id) + ""],
                                                      "client_time": ["" + str(modeldata.FatClientServerTime) + ""]}, False) )]
        changeList = env.execActions(requests)

        assert construction.ProductionState == ProductionState.Busy

        profit = modeldata.Resources.Resource2 - Resource2
        cost = Silver - modeldata.Resources.Silver

        assert profit > 0
        assert cost == 0

        construction.cycle = 0
        construction.ProductionState = ProductionState.Finished
        construction.StartProductionTime = modeldata.FatClientServerTime - 3600
        modeldata.LordInfo.PremiumAccountEnd = modeldata.FatClientServerTime + 100500

        Silver = modeldata.Resources.Silver = 0
        Resource2 = modeldata.Resources.Resource2 = 0
        cTime = modeldata.FatClientServerTime

        requests = [(Collect_production_results,
                     CollectProductionResultsRequest(modeldata,
                                                     {"construction_id": ["" + str(construction.id) + ""],
                                                      "client_time": ["" + str(cTime) + ""]}, False) )]
        changeList = env.execActions(requests)

        assert construction.ProductionState == ProductionState.Busy

        premiumProfit = modeldata.Resources.Resource2 - Resource2
        premiumcost = Silver - modeldata.Resources.Silver

        assert premiumProfit > 0
        assert premiumcost == 0
        assert premiumProfit == profit * env.I.Config.getConfig(env.acc.userlocale).PREMIUM_ACCOUNT_BONUS
        assert construction.StartProductionTime == cTime

    def collect_premium_production_results_test3(self, env):
        modeldata = env.acc.model

        construction = env.add_construction(modeldata, "Production_Resource3")
        construction.cycle = 0
        construction.ProductionState = ProductionState.Finished
        construction.StartProductionTime = modeldata.FatClientServerTime - 3600

        Silver = modeldata.Resources.Silver = 0
        Resource3 = modeldata.Resources.Resource3 = 0

        requests = [(Collect_production_results,
                     CollectProductionResultsRequest(modeldata,
                                                     {"construction_id": ["" + str(construction.id) + ""],
                                                      "client_time": ["" + str(modeldata.FatClientServerTime) + ""]}, False) )]
        changeList = env.execActions(requests)

        assert construction.ProductionState == ProductionState.Busy

        profit = modeldata.Resources.Resource3 - Resource3
        cost = Silver - modeldata.Resources.Silver

        assert profit > 0
        assert cost == 0

        construction.cycle = 0
        construction.ProductionState = ProductionState.Finished
        construction.StartProductionTime = modeldata.FatClientServerTime - 3600
        modeldata.LordInfo.PremiumAccountEnd = modeldata.FatClientServerTime + 100500

        Silver = modeldata.Resources.Silver = 0
        Resource3 = modeldata.Resources.Resource3 = 0
        cTime = modeldata.FatClientServerTime

        requests = [(Collect_production_results,
                     CollectProductionResultsRequest(modeldata,
                                                     {"construction_id": ["" + str(construction.id) + ""],
                                                      "client_time": ["" + str(cTime) + ""]}, False) )]
        changeList = env.execActions(requests)

        assert construction.ProductionState == ProductionState.Busy

        premiumProfit = modeldata.Resources.Resource3 - Resource3
        premiumcost = Silver - modeldata.Resources.Silver

        assert premiumProfit > 0
        assert premiumcost == 0
        assert premiumProfit == profit * env.I.Config.getConfig(env.acc.userlocale).PREMIUM_ACCOUNT_BONUS
        assert construction.StartProductionTime == cTime

    def collect_premium_production_results_test4(self, env):
        modeldata = env.acc.model

        construction = env.add_construction(modeldata, "Production_Silver_fromRes1")
        construction.cycle = 0
        construction.ProductionState = ProductionState.Finished
        construction.StartProductionTime = modeldata.FatClientServerTime - 3600

        Silver = modeldata.Resources.Silver = 0
        Resource1 = modeldata.Resources.Resource1 = 100

        requests = [(Collect_production_results,
                     CollectProductionResultsRequest(modeldata,
                                                     {"construction_id": ["" + str(construction.id) + ""],
                                                      "client_time": ["" + str(modeldata.FatClientServerTime) + ""]}, False) )]
        changeList = env.execActions(requests)

        assert construction.ProductionState == ProductionState.Busy

        cost = Resource1 - modeldata.Resources.Resource1
        profit = modeldata.Resources.Silver - Silver

        assert profit > 0

        construction.cycle = 0
        construction.ProductionState = ProductionState.Finished
        construction.StartProductionTime = modeldata.FatClientServerTime - 3600
        modeldata.LordInfo.PremiumAccountEnd = modeldata.FatClientServerTime + 100500

        Silver = modeldata.Resources.Silver = 0
        Resource1 = modeldata.Resources.Resource1 = 100
        cTime = modeldata.FatClientServerTime

        requests = [(Collect_production_results,
                     CollectProductionResultsRequest(modeldata,
                                                     {"construction_id": ["" + str(construction.id) + ""],
                                                      "client_time": ["" + str(cTime) + ""]}, False) )]
        changeList = env.execActions(requests)

        assert construction.ProductionState == ProductionState.Busy

        premiumcost = Resource1 = modeldata.Resources.Resource1
        premiumProfit = modeldata.Resources.Silver - Silver

        assert premiumProfit > 0
        assert premiumProfit == profit * env.I.Config.getConfig(env.acc.userlocale).PREMIUM_ACCOUNT_BONUS
        assert construction.StartProductionTime == cTime

    def collect_premium_production_results_test5(self, env):
        modeldata = env.acc.model

        construction = env.add_construction(modeldata, "Production_Silver_fromRes1")
        construction.cycle = 0
        construction.ProductionState = ProductionState.Finished
        construction.StartProductionTime = int(time.time()) - 3600

        Silver = modeldata.Resources.Silver = 0
        Resource1 = modeldata.Resources.Resource1 = 100

        requests = [(Collect_production_results,
                     CollectProductionResultsRequest(modeldata,
                                                     {"construction_id": ["" + str(construction.id) + ""],
                                                      "client_time": ["" + str(modeldata.FatClientServerTime) + ""]}, False) )]
        changeList = env.execActions(requests)

        assert construction.ProductionState == ProductionState.Busy

        cost = Resource1 - modeldata.Resources.Resource1
        profit = modeldata.Resources.Silver - Silver

        assert profit > 0

        construction.cycle = 0
        construction.ProductionState = ProductionState.Finished
        construction.StartProductionTime = int(time.time()) - 3600
        modeldata.LordInfo.PremiumAccountStart = construction.StartProductionTime - 1
        modeldata.LordInfo.PremiumAccountEnd = modeldata.LordInfo.PremiumAccountStart + 100500

        Silver = modeldata.Resources.Silver = 0
        Resource1 = modeldata.Resources.Resource1 = 100
        cTime = modeldata.FatClientServerTime

        requests = [(Collect_production_results,
                     CollectProductionResultsRequest(modeldata,
                                                     {"construction_id": ["" + str(construction.id) + ""],
                                                      "client_time": ["" + str(cTime) + ""]}, False) )]
        changeList = env.execActions(requests)

        assert construction.ProductionState == ProductionState.Busy

        premiumcost = Resource1 = modeldata.Resources.Resource1
        premiumProfit = modeldata.Resources.Silver - Silver

        assert premiumProfit > 0
        assert premiumProfit == profit * env.I.Config.getConfig(env.acc.userlocale).PREMIUM_ACCOUNT_BONUS
        assert construction.StartProductionTime == cTime

    def collect_premium_production_results_test6(self, env):
        modeldata = env.acc.model

        construction = env.add_construction(modeldata, "Production_Silver_fromRes1")

        construction.cycle = 0
        construction.ProductionState = ProductionState.Idle
        construction.StartProductionTime = int(time.time()) - 1

        modeldata.LordInfo.PremiumAccountStart = construction.EndProductionTime + 100500
        modeldata.LordInfo.PremiumAccountEnd = modeldata.FatClientServerTime + 100500

        Silver = modeldata.Resources.Silver = 0
        Resource1 = modeldata.Resources.Resource1 = 100

        requests = [(Collect_production_results,
                     CollectProductionResultsRequest(modeldata,
                                                     {"construction_id": ["" + str(construction.id) + ""],
                                                      "client_time": ["" + str(modeldata.FatClientServerTime) + ""]}, False) )]
        changeList = env.execActions(requests)

        assert changeList[0]['ok'] == 0

    def collect_premium_production_results_test7(self, env):
        modeldata = env.acc.model

        construction = env.add_construction(modeldata, "FirstBuy_Cat")

        construction.ProductionState = ProductionState.Finished
        construction.EndProductionTime = 100500
        construction.ResourceToProduce = CastleResources.Silver  # Silver
        construction.ProductionPremium = False

        modeldata.LordInfo.PremiumAccountStart = construction.EndProductionTime + 100500
        modeldata.LordInfo.PremiumAccountEnd = modeldata.LordInfo.PremiumAccountStart + 100500

        Silver = modeldata.Resources.Silver = 0

        requests = [(Collect_production_results,
                     CollectProductionResultsRequest(modeldata,
                                                     {"construction_id": ["" + str(construction.id) + ""],
                                                      "client_time": ["" + str(modeldata.FatClientServerTime) + ""]}, False) )]
        changeList = env.execActions(requests)

        assert construction.ProductionState == ProductionState.Busy

        profit = modeldata.Resources.Silver - Silver

        assert profit > 0

        construction.ProductionState = ProductionState.Finished
        construction.EndProductionTime = 0
        construction.ProductionPremium = True
        construction.ResourceToProduce = CastleResources.Silver  # Silver

        Silver = modeldata.Resources.Silver = 0
        cTime = modeldata.FatClientServerTime

        requests = [(Collect_production_results,
                     CollectProductionResultsRequest(modeldata,
                                                     {"construction_id": ["" + str(construction.id) + ""],
                                                      "client_time": ["" + str(cTime) + ""]}, False) )]
        changeList = env.execActions(requests)

        assert construction.ProductionState == ProductionState.Busy

        premiumProfit = modeldata.Resources.Silver - Silver

        assert premiumProfit > 0
        assert premiumProfit == profit * env.I.Config.getConfig(env.acc.userlocale).PREMIUM_ACCOUNT_BONUS

    @staticmethod
    def collect_premium_production_results_test8(env):
        modelData = env.acc.model

        construction = env.add_construction(modelData, "Production_Resource2")
        construction.cycle = 0
        construction.ProductionState = ProductionState.Busy
        construction.StartProductionTime = modelData.FatClientServerTime - 7200
        modelData.LordInfo.PremiumAccountEnd = modelData.FatClientServerTime - 7200

        Silver = modelData.Resources.Silver = 0
        Resource2 = modelData.Resources.Resource2 = 0

        requests = [(Collect_production_results,
                     CollectProductionResultsRequest(modelData,
                                                     {"construction_id": ["" + str(construction.id) + ""],
                                                      "client_time": ["" + str(modelData.FatClientServerTime) + ""]}, False) )]
        env.execActions(requests)

        assert construction.ProductionState == ProductionState.Busy

        profit = modelData.Resources.Resource2 - Resource2
        cost = Silver - modelData.Resources.Silver

        assert profit > 0
        assert cost == 0

        construction.ProductionState = ProductionState.Busy
        construction.StartProductionTime = modelData.FatClientServerTime - 7200
        modelData.LordInfo.PremiumAccountEnd = modelData.FatClientServerTime - 3600

        Silver = modelData.Resources.Silver = 0
        Resource2 = modelData.Resources.Resource2 = 0
        cTime = modelData.FatClientServerTime

        requests = [(Collect_production_results,
                     CollectProductionResultsRequest(modelData,
                                                     {"construction_id": ["" + str(construction.id) + ""],
                                                      "client_time": ["" + str(cTime) + ""]}, False) )]
        env.execActions(requests)

        construction = modelData.getConstructionByID(construction.id)
        assert construction is not None
        assert construction.ProductionState == ProductionState.Busy

        premiumProfit = modelData.Resources.Resource2 - Resource2
        premiumCost = Silver - modelData.Resources.Silver

        assert premiumProfit > 0
        assert premiumCost == 0
        debug("profit = " + str(profit))
        debug("premiumProfit = " + str(premiumProfit))
        debug("coefficient = " + str(env.I.Config.getConfig(env.acc.userlocale).PREMIUM_ACCOUNT_BONUS))
        predictedProfit = profit * env.I.Config.getConfig(env.acc.userlocale).PREMIUM_ACCOUNT_BONUS * 0.75
        debug("predictedProfit = " + str(predictedProfit))
        assert premiumProfit == predictedProfit
        assert construction.StartProductionTime == cTime

    @staticmethod
    def collect_crystal_production_results_with_PA_test(env):
        modelData = env.acc.model

        construction = env.add_construction(modelData, "Production_Crystal")
        construction.cycle = 0
        construction.ProductionState = ProductionState.Busy
        construction.StartProductionTime = modelData.FatClientServerTime - 3600 * 46
        modelData.LordInfo.PremiumAccountEnd = modelData.FatClientServerTime - 3600 * 46

        Perl = modelData.Resources.Perl = 0

        debug("modelData.FatClientServerTime = " + str(modelData.FatClientServerTime))

        requests = [(Collect_production_results,
                     CollectProductionResultsRequest(modelData,
                                                     {"construction_id": ["" + str(construction.id) + ""],
                                                      "client_time": ["" + str(modelData.FatClientServerTime) + ""]}, False))]
        env.execActions(requests)

        assert construction.ProductionState == ProductionState.Busy

        profit = modelData.Resources.Perl - Perl

        assert profit > 0

        construction.ProductionState = ProductionState.Busy
        construction.StartProductionTime = modelData.FatClientServerTime - 3600 * 46
        modelData.LordInfo.PremiumAccountEnd = modelData.FatClientServerTime

        Perl = modelData.Resources.Perl = 0
        cTime = modelData.FatClientServerTime

        requests = [(Collect_production_results,
                     CollectProductionResultsRequest(modelData,
                                                     {"construction_id": ["" + str(construction.id) + ""],
                                                      "client_time": ["" + str(cTime) + ""]}, False))]
        env.execActions(requests)

        construction = modelData.getConstructionByID(construction.id)
        assert construction is not None
        assert construction.ProductionState == ProductionState.Busy

        premiumProfit = modelData.Resources.Perl - Perl

        assert premiumProfit > 0
        debug("profit = " + str(profit))
        debug("premiumProfit = " + str(premiumProfit))
        debug("coefficient = " + str(env.I.Config.getConfig(env.acc.userlocale).PREMIUM_ACCOUNT_BONUS))
        predictedProfit = profit
        debug("predictedProfit = " + str(predictedProfit))
        assert premiumProfit == predictedProfit
        assert construction.StartProductionTime == cTime

    @staticmethod
    def collect_crystal_production_results_with_boost_test(env):
        modelData = env.acc.model

        construction = env.add_construction(modelData, "Production_Crystal")
        construction.cycle = 0
        construction.ProductionState = ProductionState.Busy
        construction.StartProductionTime = modelData.FatClientServerTime - 3600 * 46
        construction.BoostEndTime = modelData.FatClientServerTime - 3600 * 46

        Perl = modelData.Resources.Perl = 0

        requests = [(Collect_production_results,
                     CollectProductionResultsRequest(modelData,
                                                     {"construction_id": ["" + str(construction.id) + ""],
                                                      "client_time": ["" + str(modelData.FatClientServerTime) + ""]}, False))]
        env.execActions(requests)

        assert construction.ProductionState == ProductionState.Busy

        profit = modelData.Resources.Perl - Perl

        assert profit > 0

        construction.ProductionState = ProductionState.Busy
        construction.StartProductionTime = modelData.FatClientServerTime - 3600 * 46
        construction.BoostEndTime = modelData.FatClientServerTime

        Perl = modelData.Resources.Perl = 0
        cTime = modelData.FatClientServerTime

        requests = [(Collect_production_results,
                     CollectProductionResultsRequest(modelData,
                                                     {"construction_id": ["" + str(construction.id) + ""],
                                                      "client_time": ["" + str(cTime) + ""]}, False))]
        env.execActions(requests)

        construction = modelData.getConstructionByID(construction.id)
        assert construction is not None
        assert construction.ProductionState == ProductionState.Busy

        premiumProfit = modelData.Resources.Perl - Perl

        assert premiumProfit > 0
        debug("profit = " + str(profit))
        debug("premiumProfit = " + str(premiumProfit))
        debug("coefficient = " + str(2))
        predictedProfit = profit * 2
        debug("predictedProfit = " + str(predictedProfit))
        assert premiumProfit == predictedProfit
        assert construction.StartProductionTime == cTime

    @staticmethod
    def collect_crystal_production_results_with_boost_test(env):
        modelData = env.acc.model

        construction = env.add_construction(modelData, "Production_Crystal")
        construction.cycle = 0
        construction.ProductionState = ProductionState.Busy
        construction.StartProductionTime = modelData.FatClientServerTime - 3600 * 46 * 2
        construction.BoostEndTime = modelData.FatClientServerTime - 3600 * 46 * 2

        Perl = modelData.Resources.Perl = 0

        requests = [(Collect_production_results,
                     CollectProductionResultsRequest(modelData,
                                                     {"construction_id": ["" + str(construction.id) + ""],
                                                      "client_time": ["" + str(modelData.FatClientServerTime) + ""]}, False))]
        env.execActions(requests)

        assert construction.ProductionState == ProductionState.Busy

        profit = modelData.Resources.Perl - Perl

        assert profit > 0

        construction.ProductionState = ProductionState.Busy
        construction.StartProductionTime = modelData.FatClientServerTime - 3600 * 46 * 2
        construction.BoostEndTime = modelData.FatClientServerTime - 3600 * 46

        Perl = modelData.Resources.Perl = 0
        cTime = modelData.FatClientServerTime

        requests = [(Collect_production_results,
                     CollectProductionResultsRequest(modelData,
                                                     {"construction_id": ["" + str(construction.id) + ""],
                                                      "client_time": ["" + str(modelData.FatClientServerTime) + ""]}, False))]
        env.execActions(requests)

        construction = modelData.getConstructionByID(construction.id)
        assert construction is not None
        assert construction.ProductionState == ProductionState.Busy

        premiumProfit = modelData.Resources.Perl - Perl

        assert premiumProfit > 0
        debug("profit = " + str(profit))
        debug("premiumProfit = " + str(premiumProfit))
        debug("coefficient = " + str(2))
        predictedProfit = profit
        debug("predictedProfit = " + str(predictedProfit))
        assert premiumProfit == predictedProfit
        assert construction.StartProductionTime == cTime

    def collect_firstbuy_results_test(self, env):
        modeldata = env.acc.model

        construction = env.add_construction(modeldata, "FirstBuy_Cat")
        construction.cycle = 0
        construction.ProductionState = ProductionState.Finished
        construction.EndProductionTime = 0
        construction.ResourceToProduce = CastleResources.Silver  # Silver

        silver = modeldata.Resources.Silver = 0

        requests = [(Collect_production_results,
                     CollectProductionResultsRequest(modeldata,
                                                     {"construction_id": ["" + str(construction.id) + ""],
                                                      "client_time": ["" + str(modeldata.FatClientServerTime) + ""]}, False) )]
        changeList = env.execActions(requests)

        assert construction.ProductionState == ProductionState.Busy

        profit = modeldata.Resources.Silver - silver
        staticConstruction = env.acc.SD.getStaticConstruction(construction)
        finalprice = StaticData.getPriceInterpolated(staticConstruction['FirstBuyLevels'], construction.Level, -1,
                                                     "resourcesToProduce", None)
        assert profit == int(finalprice.Silver)

    def collect_guild_results_test(self, env):
        modeldata = env.acc.model

        level = 5
        construction = env.add_construction(modeldata, "Guild", level)
        construction.ProductionLevel = level
        construction.cycle = 0
        construction.ProductionState = ProductionState.Finished
        construction.EndProductionTime = 0
        construction.ResourceToProduce = CastleResources.Resource2

        resource2 = modeldata.Resources.Resource2 = 0

        requests = [(Collect_production_results,
                     CollectProductionResultsRequest(modeldata, {"construction_id": ["" + str(construction.id) + ""],
                                                      "client_time": ["" + str(modeldata.FatClientServerTime) + ""]}, False) )]
        changeList = env.execActions(requests)

        assert construction.ProductionState == ProductionState.Busy

        profit = modeldata.Resources.Resource2 - resource2
        staticConstruction = env.acc.SD.getStaticConstruction(construction)
        finalprice = env.acc.SD.getGuildProductionCycle(construction.Level)['resourcesToProduce']
        assert profit == finalprice['Resource2']

    def collect_production_results_goldhouse_test(self, env):
        modeldata = env.acc.model

        construction = env.add_construction(modeldata, "GoldProductionHouse")

        construction.cycle = 0
        construction.ProductionState = ProductionState.Finished
        construction.ProductionPremium = False

        gold = modeldata.Resources.Gold

        requests = [(Collect_production_results,
                     CollectProductionResultsRequest(modeldata, {"construction_id": ["" + str(construction.id) + ""],
                                                      "client_time": ["" + str(modeldata.FatClientServerTime) + ""]},
                                                     False))]
        changeList = env.execActions(requests)

        assert construction.ProductionState == ProductionState.Busy

    def collect_productionvalue_with_empty_cycle(self, env):
        modeldata = env.acc.model

        construction = env.add_construction(modeldata, "Production_Resource1")
        construction.cycle = 0
        construction.ProductionState = ProductionState.Finished
        construction.StartProductionTime = modeldata.FatClientServerTime
        construction.ProductionValue = 80

        modeldata.Resources.Resource1 = 100

        requests = [(Collect_production_results,
                     CollectProductionResultsRequest(modeldata, {"construction_id": ["" + str(construction.id) + ""],
                                                      "client_time": ["" + str(modeldata.FatClientServerTime) + ""]}, False) )]
        changeList = env.execActions(requests)

        assert construction.ProductionState == ProductionState.Busy
        assert modeldata.Resources.Resource1 == 180
        assert construction.StartProductionTime == modeldata.FatClientServerTime or construction.StartProductionTime == modeldata.FatClientServerTime - 1
        assert construction.ProductionValue == 0
