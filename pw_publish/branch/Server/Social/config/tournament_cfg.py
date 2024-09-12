# -*- coding: utf-8 -*-
# this file is to be loaded through execfile() called from some config class' method
# so `self.` refers to the loader method's object

self.TournamentSettings.IS_TOURNAMENT_SERVER = True
self.TournamentSettings.HOURS_FROM_LAST_PLAY = 36

self.overrideData( "/Social/Constructions/Buildings/Library::LibraryLevels.Item.[0].additionalTalentSlots", "99999" )

self.overrideData( "/Social/Constructions/Buildings/Library::Levels.Item.[0].price.Resource1", "99999" )
self.overrideData( "/Social/Constructions/Buildings/Library::Levels.Item.[0].price.Resource2", "99999" )
self.overrideData( "/Social/Constructions/Buildings/Library::Levels.Item.[0].price.Resource3", "99999" )
self.overrideData( "/Social/Constructions/Buildings/Library::Levels.Item.[1].price.Resource1", "99999" )
self.overrideData( "/Social/Constructions/Buildings/Library::Levels.Item.[1].price.Resource2", "99999" )
self.overrideData( "/Social/Constructions/Buildings/Library::Levels.Item.[1].price.Resource3", "99999" )

self.overrideData( "/Social.ROOT::TalentLevelToPointsAndRarity.Item.[0].levelToPoints", "[]" )
self.overrideData( "/Social.ROOT::TalentLevelToPointsAndRarity.Item.[1].levelToPoints", "[]" )
self.overrideData( "/Social.ROOT::TalentLevelToPointsAndRarity.Item.[2].levelToPoints", "[]" )
self.overrideData( "/Social.ROOT::TalentLevelToPointsAndRarity.Item.[3].levelToPoints", "[]" )
self.overrideData( "/Social.ROOT::TalentLevelToPointsAndRarity.Item.[4].levelToPoints", "[]" )
self.overrideData( "/Social.ROOT::TalentLevelToPointsAndRarity.Item.[5].levelToPoints", "[]" )

self.overrideData( "/Social.ROOT::ResetStatsPriceCoef.Resource1", "0" )
self.overrideData( "/Social.ROOT::ResetStatsPriceCoef.Resource2", "0" )
self.overrideData( "/Social.ROOT::ResetStatsPriceCoef.Resource3", "0" )
self.overrideData( "/Social.ROOT::ResetStatsPriceCoef.Resource1_Rare", "0" )
self.overrideData( "/Social.ROOT::ResetStatsPriceCoef.Resource2_Rare", "0" )
self.overrideData( "/Social.ROOT::ResetStatsPriceCoef.Resource3_Rare", "0" )
self.overrideData( "/Social.ROOT::ResetStatsPriceCoef.Perl", "1" )
self.overrideData( "/Social.ROOT::ResetStatsPriceCoef.Silver", "0" )
self.overrideData( "/Social.ROOT::ResetStatsPriceCoef.Gold", "0" )
self.overrideData( "/Social.ROOT::ResetStatsPriceCoef.Population", "0" )

self.overrideData( "/Social.ROOT::GoldTalentsUnsoulboundPrice.Item.[1].Silver", "1")
self.overrideData( "/Social.ROOT::GoldTalentsUnsoulboundPrice.Item.[2].Silver", "1")
self.overrideData( "/Social.ROOT::GoldTalentsUnsoulboundPrice.Item.[3].Silver", "1")
self.overrideData( "/Social.ROOT::GoldTalentsUnsoulboundPrice.Item.[4].Silver", "1")
self.overrideData( "/Social.ROOT::GoldTalentsUnsoulboundPrice.Item.[4].Gold", "0")
self.overrideData( "/Social.ROOT::GoldTalentsUnsoulboundPrice.Item.[5].Silver", "1")
self.overrideData( "/Social.ROOT::GoldTalentsUnsoulboundPrice.Item.[5].Gold", "0")

##Удаляем все акции
for id in xrange( 0, len(self.MARKETING_EVENTS) ):
  self.MARKETING_EVENTS.pop()

for id in xrange( 0, len(self.DEFAULT_SKINS) ):
  self.DEFAULT_SKINS.pop()


self.MARKETING_EVENTS.append( "/UI/Content/MarketingEvents/BuyTournamentTicketEvent" )
self.MARKETING_EVENTS.append( "/UI/Content/MarketingEvents/TournamentInProgressEvent" )

##С самого начала выдать всех героев
self.GIVE_ALL_HEROES = True

##Стартовый ретинг героев
self.HERO_START_RATING = 1500

##Не учтывать уровень при сбросе статов героя
self.USE_LEVEL_SCALE_FOR_RESET_PRICE = False

##Сколько стоит снятие soulbound'a с синего таланта
#self.COST_UNSOULBOUND_TALENT_BLUE = -1
##Сколько стоит снятие soulbound'a с фиолетвого таланта
#self.COST_UNSOULBOUND_TALENT_VIOLET = -1
##Сколько стоит снятие soulbound'a с оранжевого таланта
#self.COST_UNSOULBOUND_TALENT_ORANGE = -1

## Запретить договорные игры
self.TournamentSettings.IS_ENEMY_PORTRAITS_DISABLED = True

##Доступны все скины
self.DEFAULT_SKINS.append("alchemist_S1")
self.DEFAULT_SKINS.append("archeress_S1_A")
self.DEFAULT_SKINS.append("archeress_S1_B")
self.DEFAULT_SKINS.append("archeress_S2_A")
self.DEFAULT_SKINS.append("archeress_S2_B")
self.DEFAULT_SKINS.append("artist_S1")
self.DEFAULT_SKINS.append("artist_S2")
self.DEFAULT_SKINS.append("assassin_S1_A")
self.DEFAULT_SKINS.append("assassin_S1_B")
self.DEFAULT_SKINS.append("bard_S1_A")
self.DEFAULT_SKINS.append("bard_S1_B")
self.DEFAULT_SKINS.append("demonolog_S1")
self.DEFAULT_SKINS.append("faceless_S1_A")
self.DEFAULT_SKINS.append("faceless_S1_B")
self.DEFAULT_SKINS.append("faceless_S2_A")
self.DEFAULT_SKINS.append("faceless_S2_B")
self.DEFAULT_SKINS.append("fairy_S1_A")
self.DEFAULT_SKINS.append("fairy_S1_B")
self.DEFAULT_SKINS.append("firefox_S1_A")
self.DEFAULT_SKINS.append("firefox_S1_B")
self.DEFAULT_SKINS.append("frogenglut_S1_A")
self.DEFAULT_SKINS.append("frogenglut_S1_B")
self.DEFAULT_SKINS.append("frogenglut_S2_A")
self.DEFAULT_SKINS.append("frogenglut_S2_B")
self.DEFAULT_SKINS.append("ghostlord_S1_A")
self.DEFAULT_SKINS.append("ghostlord_S1_B")
self.DEFAULT_SKINS.append("ghostlord_S2_A")
self.DEFAULT_SKINS.append("ghostlord_S2_B")
self.DEFAULT_SKINS.append("healer_S1_A")
self.DEFAULT_SKINS.append("healer_S1_B")
self.DEFAULT_SKINS.append("healer_S3_A")
self.DEFAULT_SKINS.append("healer_S3_B")
self.DEFAULT_SKINS.append("highlander_S1_A")
self.DEFAULT_SKINS.append("highlander_S1_B")
self.DEFAULT_SKINS.append("highlander_S2_A")
self.DEFAULT_SKINS.append("highlander_S2_B")
self.DEFAULT_SKINS.append("hunter_S1_A")
self.DEFAULT_SKINS.append("hunter_S1_B")
self.DEFAULT_SKINS.append("hunter_S2_A")
self.DEFAULT_SKINS.append("hunter_S2_B")
self.DEFAULT_SKINS.append("inventor_S1")
self.DEFAULT_SKINS.append("inventor_S2")
self.DEFAULT_SKINS.append("invisible_S1_A")
self.DEFAULT_SKINS.append("invisible_S1_B")
self.DEFAULT_SKINS.append("mage_S1_A")
self.DEFAULT_SKINS.append("mage_S1_B")
self.DEFAULT_SKINS.append("manawyrm_S1_A")
self.DEFAULT_SKINS.append("manawyrm_S1_B")
self.DEFAULT_SKINS.append("marine_S1_A")
self.DEFAULT_SKINS.append("marine_S1_B")
self.DEFAULT_SKINS.append("marine_S2_A")
self.DEFAULT_SKINS.append("marine_S2_B")
self.DEFAULT_SKINS.append("mowgly_S1_A")
self.DEFAULT_SKINS.append("mowgly_S1_B")
self.DEFAULT_SKINS.append("mowgly_S2_A")
self.DEFAULT_SKINS.append("mowgly_S2_B")
self.DEFAULT_SKINS.append("naga_S1_A")
self.DEFAULT_SKINS.append("naga_S1_B")
self.DEFAULT_SKINS.append("night_S1_A")
self.DEFAULT_SKINS.append("night_S1_B")
self.DEFAULT_SKINS.append("night_S3_A")
self.DEFAULT_SKINS.append("night_S3_B")
self.DEFAULT_SKINS.append("prince_S1_A")
self.DEFAULT_SKINS.append("prince_S1_B")
self.DEFAULT_SKINS.append("ratcatcher_S1_A")
self.DEFAULT_SKINS.append("ratcatcher_S1_B")
self.DEFAULT_SKINS.append("rockman_S1_A")
self.DEFAULT_SKINS.append("rockman_S1_B")
self.DEFAULT_SKINS.append("rockman_S2_A")
self.DEFAULT_SKINS.append("rockman_S2_B")
self.DEFAULT_SKINS.append("snowqueen_S1_A")
self.DEFAULT_SKINS.append("snowqueen_S1_B")
self.DEFAULT_SKINS.append("snowqueen_S2_A")
self.DEFAULT_SKINS.append("snowqueen_S2_B")
self.DEFAULT_SKINS.append("thundergod_S1_A")
self.DEFAULT_SKINS.append("thundergod_S1_B")
self.DEFAULT_SKINS.append("thundergod_S2_A")
self.DEFAULT_SKINS.append("thundergod_S2_B")
self.DEFAULT_SKINS.append("unicorn_S1_A")
self.DEFAULT_SKINS.append("unicorn_S1_B")
self.DEFAULT_SKINS.append("vampire_S1_A")
self.DEFAULT_SKINS.append("vampire_S1_B")
self.DEFAULT_SKINS.append("warlord_S1_A")
self.DEFAULT_SKINS.append("warlord_S1_B")
self.DEFAULT_SKINS.append("werewolf_S1_A")
self.DEFAULT_SKINS.append("werewolf_S1_B")
self.DEFAULT_SKINS.append("witchdoctor_S1_A")
self.DEFAULT_SKINS.append("witchdoctor_S1_B")
self.DEFAULT_SKINS.append("witcher_S1")

self.TALENTS_NOT_FOR_ROLL.append('G347')
self.TALENTS_NOT_FOR_ROLL.append('G348')
self.TALENTS_NOT_FOR_ROLL.append('G289')
self.TALENTS_NOT_FOR_ROLL.append('G290')
self.TALENTS_NOT_FOR_ROLL.append('G291')
self.TALENTS_NOT_FOR_ROLL.append('G292')
self.TALENTS_NOT_FOR_ROLL.append('G293')

# запрещаем играть в одном пати крстоносцам разных фракций
self.FORBIDDEN_FOR_PARTY_HERO_PAIRS.append("crusader_A;crusader_B");

# сообщение о расписании игр на турнире
self.overrideData( "/Social/ErrorMessages/ErrorMessagesTable::Errors.[73].Message.Text", "Сейчас бои недоступны.<br>Следующие матчи начнутся {tm:DateTime: dd.MM.yyyy в HH:mm}")
self.overrideData( "/Social/ErrorMessages/ErrorMessagesTable::Errors.[74].Message.Text", "Сейчас бои недоступны.<br>Следующие матчи начнутся {tm:DateTime: dd.MM.yyyy в HH:mm}")

