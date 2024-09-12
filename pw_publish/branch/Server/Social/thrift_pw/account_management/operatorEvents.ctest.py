# -*- coding: utf-8 -*-
import sys, time
sys.path.append('gen-py')

from thrift import Thrift
from thrift.transport import TTransport
from thrift.transport import THttpClient
from thrift.protocol import TBinaryProtocol

sys.path.append('gen-py/AccountManagementAPI')
import AccountManagement
import ttypes

sys.path.append('../../')
from base.helpers import pretty, json_loads, utf8convert

#~SERVER_ADDR = "pw.nivalnetwork.com"
SERVER_ADDR = "127.0.0.1"

if __name__ == "__main__":
    try:
        transport = THttpClient.THttpClient('http://%s:8706/thrift?service=account_management' % SERVER_ADDR)
        transport = TTransport.TBufferedTransport(transport)
        protocol = TBinaryProtocol.TBinaryProtocolAccelerated(transport)
        client = AccountManagement.Client(protocol)
        transport.open()

        eventInfo = ttypes.TransmutationTalentsPerPerl(
            startTime=50,
            endTime=1429455040,
            persistentId=1,
            talents=8,
            enabled=False,
            description="TalentEvent3"
        )

        newsBanner = ttypes.NewsBanner(
            locale="RU",
            startTime=50,
            endTime=1429455040,
            persistentId=2,
            buttonText=utf8convert("Обвиняша"),
            windowCaption=utf8convert("Обвиняша"),
            buttonUrl="http://ru.playpw.com/images/promo/justice-icon.png",
            mainUrl="http://ru.playpw.com/images/promo/justice-doct-ru.png",
            tooltip=utf8convert("Законы Праи честны и справедливы! Обрушьте всю силу правосудия и красоты на головы врагов с новым образом Обвиняшка! Приобрести данный скин можно в окне информации для героя Крио/Вьюга."),
            mainUrlB="http://ru.playpw.com/images/promo/justice-adorn-ru.png",
            LoginNetworks="",
            minLordLevel=0,
            hideIfViewed=False,
            enabled=True,
            description="NewsBanner"
        )

        customEvent = ttypes.CustomEvent(
            startTime=50,
            endTime=1429455040,
            persistentId=3,
            type=utf8convert("give_lamp \"20, 10000, 10, 86400\""),
            enabled=True,
            description="Custom event for lamp"
        )

        customSkinPrice1 = ttypes.SkinGoldPrice(persistentId="ghostlord_S1_A",
                                                heroClassId=12345,
                                                price=25)
        customSkinPrice2 = ttypes.SkinGoldPrice(persistentId="ghostlord_S1_B",
                                                heroClassId=12345,
                                                price=25)
        skinPriceEvent = ttypes.SkinGoldPriceEvent(
                                              startTime=50,
                                              endTime=1429455040,
                                              persistentId=4,
                                              skins=[customSkinPrice1, customSkinPrice2],
                                              enabled=True,
                                              description="Price event for marine skins")

        customHeroPrice1 = ttypes.HeroPrice(persistentId="faceless",
                                                silverPrice=128000,
                                                goldPrice=20)
        customHeroPrice2 = ttypes.HeroPrice(persistentId="witcher",
                                                silverPrice=45000,
                                                goldPrice=85)
        heroPriceEvent = ttypes.HeroPriceEvent(
                                              startTime=55,
                                              endTime=1429455040,
                                              persistentId=5,
                                              heroes=[customHeroPrice1, customHeroPrice2],
                                              enabled=True,
                                              description="Price event for witcher and mage")

        customMap = ttypes.CustomMap(
                                     startTime=55,
                                     endTime=1429455040,
                                     persistentId=6,
                                     day="all",
                                     startHour="00:00",
                                     endHour="23:59",
                                     mapDbid="/Maps/Multiplayer/MidOnly/_.ADMPDSCR",
                                     mapType="CTF",
                                     mapEnabled=True,
                                     enabled=True,
                                     description="Event for forpost map")

        customMapPVP = ttypes.CustomMap(
                                        startTime=55,
                                        endTime=1429455040,
                                        persistentId=7,
                                        day="all",
                                        startHour="00:00",
                                        endHour="23:59",
                                        mapDbid="/Maps/Multiplayer/MOBA/_.ADMPDSCR",
                                        mapType="PVP",
                                        mapEnabled=True,
                                        enabled=True,
                                        description="Event for usual moba map")
        dropRarity = ttypes.TalentDropRarity(classRar=0,
                                             ordinary=0,
                                             good=40,
                                             excellent=42,
                                             magnificent=12,
                                             exclusive=6)

        talentDropEvent = ttypes.TalentDropRarityEvent(
                                                       startTime=55,
                                                       endTime=1429455040,
                                                       persistentId=7,
                                                       dropRarity=dropRarity,
                                                       enabled=True,
                                                       premium=False,
                                                       description="Event for ordinary drop rarities")

        techsEvent = ttypes.TechsInfo(
                                       startTime=55,
                                       endTime=1429455040,
                                       persistentId=8,
                                       time=60*60*4,
                                       type="premium,rating,guild_buffs,sieges",
                                       description="Test techs event")


        customRerollShopGroupPrice1 = ttypes.RerollShopGroupPrice(persistentId="group_A",
                                                                  minPrice=5000,
                                                                  maxPrice=10000)
        customRerollShopGroupPrice2 = ttypes.RerollShopGroupPrice(persistentId="group_B",
                                                                  minPrice=80,
                                                                  maxPrice=85)
        groupPriceEvent = ttypes.RerollShopGroupPriceEvent(
                                              startTime=55,
                                              endTime=1429455040,
                                              persistentId=46,
                                              groups=[customRerollShopGroupPrice1, customRerollShopGroupPrice2],
                                              enabled=True,
                                              description="Price event for group_A and group_B")

        customRerollShopGroupProbability1 = ttypes.RerollShopGroupProbability(persistentId="group_A",
                                                                              rerollTime=0,
                                                                              probability=57)
        customRerollShopGroupProbability2 = ttypes.RerollShopGroupProbability(persistentId="group_B",
                                                                              rerollTime=0,
                                                                              probability=85)
        groupProbabilityEvent = ttypes.RerollShopGroupProbabilityEvent(
                                            startTime=55,
                                            endTime=1429455040,
                                            persistentId=48,
                                            groups=[customRerollShopGroupProbability1, customRerollShopGroupProbability2],
                                            enabled=True,
                                            description="Probability event for group_A and group_B")

        customRerollShopGroupCurrencies1 = ttypes.RerollShopGroupCurrencies(persistentId="group_A",
                                                                            currencies=24)
        customRerollShopGroupCurrencies2 = ttypes.RerollShopGroupCurrencies(persistentId="group_B",
                                                                            currencies=19)
        groupCurrenciesEvent = ttypes.RerollShopGroupCurrenciesEvent(
                                            startTime=55,
                                            endTime=1429455040,
                                            persistentId=48,
                                            groups=[customRerollShopGroupCurrencies1, customRerollShopGroupCurrencies2],
                                            enabled=True,
                                            description="Currencies event for group_A and group_B")

        customRerollShopSlotPrice1 = ttypes.RerollShopSlotPrice(groupId="group_A",
                                                                persistentId="res1_medium",
                                                                minPrice=5000,
                                                                maxPrice=10000)
        customRerollShopSlotPrice2 = ttypes.RerollShopSlotPrice(groupId="group_B",
                                                                persistentId="perl1_medium",
                                                                minPrice=80,
                                                                maxPrice=85)
        slotPriceEvent = ttypes.RerollShopSlotPriceEvent(
                                              startTime=55,
                                              endTime=1429455040,
                                              persistentId=49,
                                              slots=[customRerollShopSlotPrice1, customRerollShopSlotPrice2],
                                              enabled=True,
                                              description="Price event for group_A slot res1_medium and group_B slot perl1_medium")

        customRerollShopSlotAmount1 = ttypes.RerollShopSlotAmount(groupId="group_A",
                                                                persistentId="res1_medium",
                                                                amount=12345)
        customRerollShopSlotAmount2 = ttypes.RerollShopSlotAmount(groupId="group_B",
                                                                persistentId="perl1_medium",
                                                                amount=10)

        slotAmountEvent = ttypes.RerollShopSlotAmountEvent(
                                              startTime=55,
                                              endTime=1491458165,
                                              persistentId=10,
                                              slots=[customRerollShopSlotAmount1, customRerollShopSlotAmount2],
                                              enabled=True,
                                              description="Amount event for group_A slot res1_medium and group_B slot perl1_medium")

        customFirstBuyPrice1 = ttypes.FirstBuyGoldPrice(persistentId="FirstBuy_Cat",
                                                        price=25)
        customFirstBuyPrice2 = ttypes.FirstBuyGoldPrice(persistentId="FirstBuy_Dog",
                                                        price=30)
        firstBuyPriceEvent = ttypes.FirstBuyGoldPriceEvent(
                                              startTime=50,
                                              endTime=1450458165,
                                              persistentId=4,
                                              firstBuys=[customFirstBuyPrice1, customFirstBuyPrice2],
                                              enabled=True,
                                              description="Price event for cat and dog")

        rerollShopPremiumNotInactiveInfo = ttypes.RerollShopPremiumNotInactiveEvent(
            startTime=50,
            endTime=1451458165,
            persistentId=5,
            isInactive=True,
            enabled=False,
            description="TalentEvent3"
        )

        customRerollShopGroupSlots1 = ttypes.RerollShopGroupSlots(persistentIds=["talentsList_rar6_set1", "talentsList_rar6_set2"],
                                                                  groupId="group_A1")
        customRerollShopGroupSlots2 = ttypes.RerollShopGroupSlots(persistentIds=["talentsList_rar6_set1", "talentsList_rar6_set2"],
                                                                  groupId="group_F1")
        groupSlotsEvent = ttypes.RerollShopGroupSlotsEvent(
                                              startTime=55,
                                              endTime=1491458165,
                                              persistentId=13,
                                              groups=[customRerollShopGroupSlots1, customRerollShopGroupSlots2],
                                              enabled=False,
                                              description="Slots event for group_A and group_B")

        rerollShopBanner = ttypes.RerollShopBanner(
            locale="RU",
            startTime=50,
            endTime=1429455040,
            persistentId=19,
            mainUrl="http://ru.playpw.com/images/promo/justice-doct-ru.png",
            enabled=True,
            description="RerollShopBanner"
        )

        #print client.DeleteEventById(2)
        #print client.ChangeEventStateById(1, True)

        #client.AddTalentPerPerlEvent(eventInfo)
        #client.EditTalentPerPerlEvent(eventInfo)
        #print client.GetTransmutationTalentsPerPerlById(1)
        #print client.GetTransmutationTalentsPerPerl()

        #client.AddNewsBanner(newsBanner)
        #client.EditNewsBanner(newsBanner)
        #print client.GetNewsBannerById(2)

        #client.AddCustomEvent(customEvent)
        #client.EditCustomEvent(customEvent)
        #print client.GetCustomEvents()

        #client.AddSkinPricesEvent(skinPriceEvent)
        #client.EditSkinPricesEvent(skinPriceEvent)
        #print client.GetSkinPrices()
        #print client.GetSkinPriceById(4)

        #client.AddHeroPricesEvent(heroPriceEvent)
        #client.EditHeroPricesEvent(heroPriceEvent)
        #print client.GetHeroPrices()
        #print client.GetHeroPriceById(5)

        #client.AddCustomMap(customMapPVP)
        #client.EditCustomMap(customMapPVP)
        #print client.GetCustomMaps()
        #print client.GetCustomMapById(6)

        #client.AddTalentDropRarities(talentDropEvent)
        #client.EditTalentDropRarities(talentDropEvent)
        #print client.GetTalentDropRarities()
        #print client.GetTalentDropRarityById(7)

        #client.AddTechs(techsEvent)
        #client.EditTechs(techsEvent)
        #print client.GetTechsInfos()
        #print client.GetTechsInfoById(8)

        #client.AddRerollShopGroupPricesEvent(groupPriceEvent)
        #client.EditRerollShopGroupPricesEvent(groupPriceEvent)
        #print client.GetRerollShopGroupPrices()
        #print client.GetRerollShopGroupPriceById(46)

        #client.AddRerollShopGroupProbabilityEvent(groupProbabilityEvent)
        #client.EditRerollShopGroupProbabilityEvent(groupProbabilityEvent)
        #print client.GetRerollShopGroupProbabilities()
        #print client.GetRerollShopGroupProbabilityById(47)

        #client.AddRerollShopGroupCurrenciesEvent(groupCurrenciesEvent)
        #client.EditRerollShopGroupCurrenciesEvent(groupCurrenciesEvent)
        #print client.GetRerollShopGroupCurrencies()
        #print client.GetRerollShopGroupCurrenciesById(48)

        #client.AddRerollShopSlotPricesEvent(slotPriceEvent)
        #client.EditRerollShopSlotPricesEvent(slotPriceEvent)
        #print client.GetRerollShopSlotPrices()
        #print client.GetRerollShopSlotPriceById(49)

        #client.AddFirstBuyPricesEvent(firstBuyPriceEvent)
        #client.EditFirstBuyPricesEvent(firstBuyPriceEvent)
        #print client.GetFirstBuyPrices()
        #print client.GetFirstBuyPriceById(4)

        #client.AddRerollShopPremiumNotInactiveEvent(rerollShopPremiumNotInactiveInfo)
        #client.EditRerollShopPremiumNotInactiveEvent(rerollShopPremiumNotInactiveInfo)
        #print client.GetRerollShopPremiumNotInactive()
        #print client.GetRerollShopPremiumNotInactiveById(5)

        #client.AddRerollShopSlotAmountsEvent(slotAmountEvent)
        #client.EditRerollShopSlotAmountsEvent(slotAmountEvent)
        #print client.GetRerollShopSlotAmount()
        #print client.GetRerollShopSlotAmountById(10)

        #client.AddRerollShopGroupSlotsEvent(groupSlotsEvent)
        #client.EditRerollShopGroupSlotsEvent(groupSlotsEvent)
        #print client.GetRerollShopGroupSlots()
        #print client.GetRerollShopGroupSlotsById(13)

        client.AddRerollShopBanner(rerollShopBanner)
        client.EditRerollShopBanner(rerollShopBanner)
        print client.GetRerollShopBanners()
        print client.GetRerollShopBannerById(19)

        transport.close()
    except Thrift.TException, tx:
        print '%s' % (tx.message)