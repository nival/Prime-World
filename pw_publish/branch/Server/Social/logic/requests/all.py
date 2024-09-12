#automatically generated file. do not modify it!!!

import os
__all__ = ["LoginRequest",
"ZzLoginRequest",
"SnLoginRequest",
"QueueLoginRequest",
"QueuePollRequest",
"QueueCancelRequest",
"AuthRequest",
"SetNicknameRequest",
"CheckNicknameRequest",
"StartMatchMakingRequest",
"StartSpectateRequest",
"PlaceHeroToBuildingRequest",
"RemoveHeroFromBuildingRequest",
"StartBuildingProductionRequest",
"StopBuildingProductionRequest",
"CollectProductionResultsRequest",
"UpdateMatchMakingStatusRequest",
"CancelMatchMakingRequest",
"LeaveTamburMatchMakingRequest",
"LeaveMatchMakingRequest",
"ReconnectMatchMakingRequest",
"AcceptMatchMakingRequest",
"SetFractionRequest",
"LogoutRequest",
"KeepaliveRequest",
"TouchRequest",
"ItemMoveTsToTsRequest",
"ItemMoveTsToInvRequest",
"CheckTalentRequest",
"RecalcHeroForcesRequest",
"ItemMoveInvToTsRequest",
"ItemSetActoinBarIndexRequest",
"ItemRemoveNewStatusRequest",
"BuildingMoveRequest",
"BuildingPlaceRequest",
"BuildingRemoveRequest",
"BuildingUpgradeRequest",
"IncreaseBuildingLvlRequest",
"AddTalentRequest",
"AddTalentExRequest",
"AddAllTalentsRequest",
"AddAllTalentUpgradeEntitiesRequest",
"RemoveTalentsRequest",
"RemoveAllTalentsRequest",
"GiveFameRequest",
"ResetNewTalentsRequest",
"SetNewStatusRequest",
"GiveExperienceRequest",
"GiveRatingRequest",
"IncreaseStatRequest",
"GiveStatPointsRequest",
"ResetStatPointsRequest",
"GiveResourceRequest",
"HireHeroRequest",
"PartyInviteRequest",
"PartyMapRequest",
"PartyAcceptRequest",
"PartyDeclineRequest",
"PartyDisbandRequest",
"PartyKickRequest",
"PartyHeroRequest",
"PartyGoRequest",
"PartyDodgeRequest",
"PartyStatusRequest",
"PartyFlagRequest",
"PartyInventoryIsFullRequest",
"ClearSoulboundRequest",
"ChangeFractionRequest",
"BanAccountRequest",
"MuteAccountRequest",
"ExpansionRequest",
"MoveToPocketRequest",
"MoveFromPocketRequest",
"ChangeNicknameRequest",
"PurchaseGuildIconChangeRequest",
"ResetCountersRequest",
"ClearItemSoulboundRequest",
"BuyCycleRequest",
"CollectTalentRequest",
"AddIgnoreRequest",
"RemoveIgnoreRequest",
"FinishProductionRequest",
"AddStatisticRequest",
"AddQuestRequest",
"TryCompleteObjectiveRequest",
"ForceCompleteObjectiveRequest",
"CompleteQuestRequest",
"AcceptQuestRequest",
"SkipObjectiveRequest",
"ShowErrorRequest",
"AddFriendToFavoritesRequest",
"RemoveFriendFromFavoritesRequest",
"TestBoolRequest",
"ClearMmRequest",
"BuyPremiumAccountRequest",
"BuyPremiumAccountGMRequest",
"BuyUnbanGMRequest",
"UpdateCameraFlybyRequest",
"ChangeMapRequest",
"ChangePAEndRequest",
"ChangeLastLoginRequest",
"RemoveFriendRequest",
"UsesUpgHeroTalRequest",
"InviteFriendRequest",
"AcceptFriendRequest",
"DeclineFriendRequest",
"SearchFriendRequest",
"AddFriendRequest",
"ReturnFriendRequest",
"AddFakeFriendsRequest",
"AddToPocketRequest",
"MarkEventViewedRequest",
"BuyHeroRequest",
"BuyHeroGoldRequest",
"UpgradeHeroRequest",
"MergeTalentsRequest",
"SetGuardRequest",
"AddDodgesRequest",
"UnretireRequest",
"SetWinsRequest",
"ReadyMatchMakingRequest",
"UpgradeTalentRequest",
"OnlyGuardRequest",
"GetPricesRequest",
"BuySpecialHeroRequest",
"CheckPendingQuestsRequest",
"BuySkinRequest",
"SelectSkinRequest",
"ClearFWODRequest",
"RefreshPingResultsRequest",
"GuildCreateRequest",
"GuildRenameRequest",
"GuildLeaveRequest",
"GuildDestroyRequest",
"GuildInviteRequest",
"GuildAcceptRequest",
"GuildDeclineRequest",
"GuildPromoteRequest",
"GuildDemoteRequest",
"GuildChangeOwnerRequest",
"GuildKickRequest",
"GuildInvestResourcesRequest",
"GuildMsgRequest",
"GuildRecalcRequest",
"GuildPutTalentToBankRequest",
"GuildTakeTalentFromBankRequest",
"GuildGiveBackRequest",
"GuildReturnTalentToBankRequest",
"GuildBankLimitsResetRequest",
"GuildBuyShopItemRequest",
"GiveActionRequest",
"SetLastPaymentRequest",
"TavernRerollRequest",
"BuySteamItemRequest",
"ConfirmSteamItemRequest",
"SetSteamSexRequest",
"GiveMuidDLCRequest",
"UpdateDLCRequest",
"RegisterDLCRequest",
"UnregisterDLCRequest",
"TestECRequest",
"BuyAeriaItemRequest",
"BuyGamigoItemRequest",
"BuyArcGamesItemRequest",
"BuyZZimaItemRequest",
"BillingReserveAmountRequest",
"BillingConfirmWriteOffRequest",
"BillingWriteOffRequest",
"BillingReplenishRequest",
"CreateComplaintRequest",
"ResetComplaintsRequest",
"SetLampLastDropTimeRequest",
"BuyTournamentTicketRequest",
"UpdateTournamentInfoRequest",
"ResetTournamentAccountRequest",
"GuildDeleteMsgRecievedRequest",
"BuyCustomFlagRequest",
"ChangeFlagRequest",
"AddCustomFlagRequest",
"SetMDVersionRequest",
"SetAFKStateRequest",
"NotifyTutorialStateChangedRequest",
"NotifySessionEndedRequest",
"AcceptDynamicQuestRequest",
"ForceCompleteDynamicObjectiveRequest",
"TryCompleteDynamicObjectiveRequest",
"CompleteDynamicQuestRequest",
"ReforgeTalentRequest",
"ReforgeUpgradeTalentRequest",
"ResetDynamicQuestsRequest",
"ClearDynamicQuestsFromServerRequest",
"AddTalentQuestRequest",
"CraftTalentsRequest",
"ResetLastPlayedTimeRequest",
"SetConditionRewardStateRequest",
"GiveDecreaseRatingQuestRequest",
"BuyBeginnersPackRequest",
"GetGuildDataForMapRequest",
"GuildInviteSuzerainRequest",
"StartSiegeRequest",
"LeaveSiegeRequest",
"GuildAcceptVassalRequest",
"GuildDeclineVassalRequest",
"RemoveVassalRequest",
"GetExVassalsListRequest",
"GetRecommendedVassalsListRequest",
"GetGuildsListRequest",
"GetGuildRequestsListRequest",
"SetGuildExperienceRequest",
"HideRecommendedVassalRequest",
"ResetSiegesCounterRequest",
"RemoveSuzerainRequest",
"RemoveNPCSuzerainRequest",
"SetSiegeDurationRequest",
"AddVassalRequest",
"GuildShopItemsLimitResetRequest",
"SetSiegeScoreRequest",
"RemoveGuildBuffsRequest",
"SetGuildBuffDurationRequest",
"AddGuildBuffRequest",
"SetGuildTodayRatingRequest",
"RecalcMyGuildRequest",
"UpdateTopBuildsRequest",
"SetExVassalEndTimeRequest",
"SetLostTargetLeftTimeRequest",
"SetHeroLastPlayedRequest",
"GuildSetRecruitmentMessageRequest",
"GuildSetRecruitmentLocaleRequest",
"GuildSetRecruitmentRatingRequest",
"GuildAcceptRecruitRequest",
"GuildDeclineRecruitRequest",
"CreateRecruitApplicationRequest",
"WithdrawRecruitApplicationRequest",
"GetRecommendedGuildsListRequest",
"GuildGerRecruitsListRequest",
"RemoveOutOfDateRecruitApplicationsRequest",
"DecreaseRecruitApplicationLifetimeRequest",
"ChoosePartyAgainRequest",
"SetLeavesRequest",
"RemoveRecentAllyRequest",
"ReinitRecentAllyRequest",
"AddRecentAllyRequest",
"ContextResourceBuyRequest",
"BoostBuildingProductionRequest",
"SetBoostedProductionRequest",
"SetLastBuyValue",
"GiveNewQuestFromPullRequest",
"GuildAddActiveBuffRequest",
"ResetPunishedNextUpdateTimeRequest",
"ModeratorMuteUserRequest",
"RerollShopRequest",
"RerollShopForFreeRequest",
"BuyRerollShopItemRequest",
"AddRerollShopItemRequest",
"RerollShopWithStatisticsRequest",
"ResetRerollShopRequest",
"RemoveRerollShopGroupRequest",
"RemoveRerollShopIsNewStateRequest",
"RemoveTalentUpgradeEntitiesIsNewStateRequest",
"SetActiveTalentSetRequest",
"SetTalentSetMessageRequest",
"SetGamesRequest",
"SetPlayerRatingRequest",
"ChangeFriendsPageRequest",
"GetLegendLeagueRequest",
"SetSeasonsResultShowedRequest",
"UpdateHeroSeasonPlaceRequest",
"RollEventRoll",
"QuestEventChooseRequest",
"DbgQuestEventClearRequest",
"DbgQuestEventChooseRequest",
"TradeEventBuyRequest",
"TradeEventGiveRewardRequest",
"DbgTradeEventClearRequest",
"SeasonEventBuyItemRequest",
"SeasonEventGiveRewardRequest",
"DbgSeasonEventClearRequest",
"AddLootboxRequest",
"OpenLootboxRequest",
"RemoveLootboxRequest",
"UpgradeTalentByEntityRequest",
"EndCurrentGuildWarEvent",
"SrvDebugRequest",
]

from .LoginRequest import *
from .ZzLoginRequest import *
from .SnLoginRequest import *
from .QueueLoginRequest import *
from .QueuePollRequest import *
from .QueueCancelRequest import *
from .AuthRequest import *
from .SetNicknameRequest import *
from .CheckNicknameRequest import *
from .StartMatchMakingRequest import *
from .StartSpectateRequest import *
from .PlaceHeroToBuildingRequest import *
from .RemoveHeroFromBuildingRequest import *
from .StartBuildingProductionRequest import *
from .StopBuildingProductionRequest import *
from .CollectProductionResultsRequest import *
from .UpdateMatchMakingStatusRequest import *
from .CancelMatchMakingRequest import *
from .LeaveTamburMatchMakingRequest import *
from .LeaveMatchMakingRequest import *
from .ReconnectMatchMakingRequest import *
from .AcceptMatchMakingRequest import *
from .SetFractionRequest import *
from .LogoutRequest import *
from .KeepaliveRequest import *
from .TouchRequest import *
from .ItemMoveTsToTsRequest import *
from .ItemMoveTsToInvRequest import *
from .CheckTalentRequest import *
from .RecalcHeroForcesRequest import *
from .ItemMoveInvToTsRequest import *
from .ItemSetActoinBarIndexRequest import *
from .ItemRemoveNewStatusRequest import *
from .BuildingMoveRequest import *
from .BuildingPlaceRequest import *
from .BuildingRemoveRequest import *
from .BuildingUpgradeRequest import *
from .IncreaseBuildingLvlRequest import *
from .AddTalentRequest import *
from .AddTalentExRequest import *
from .AddAllTalentsRequest import *
from .AddAllTalentUpgradeEntitiesRequest import *
from .RemoveTalentsRequest import *
from .RemoveAllTalentsRequest import *
from .GiveFameRequest import *
from .ResetNewTalentsRequest import *
from .SetNewStatusRequest import *
from .GiveExperienceRequest import *
from .GiveRatingRequest import *
from .IncreaseStatRequest import *
from .GiveStatPointsRequest import *
from .ResetStatPointsRequest import *
from .GiveResourceRequest import *
from .HireHeroRequest import *
from .PartyInviteRequest import *
from .PartyMapRequest import *
from .PartyAcceptRequest import *
from .PartyDeclineRequest import *
from .PartyDisbandRequest import *
from .PartyKickRequest import *
from .PartyHeroRequest import *
from .PartyGoRequest import *
from .PartyDodgeRequest import *
from .PartyStatusRequest import *
from .PartyFlagRequest import *
from .PartyInventoryIsFullRequest import *
from .ClearSoulboundRequest import *
from .ChangeFractionRequest import *
from .BanAccountRequest import *
from .MuteAccountRequest import *
from .ExpansionRequest import *
from .MoveToPocketRequest import *
from .MoveFromPocketRequest import *
from .ChangeNicknameRequest import *
from .PurchaseGuildIconChangeRequest import *
from .ResetCountersRequest import *
from .ClearItemSoulboundRequest import *
from .BuyCycleRequest import *
from .CollectTalentRequest import *
from .AddIgnoreRequest import *
from .RemoveIgnoreRequest import *
from .FinishProductionRequest import *
from .AddStatisticRequest import *
from .AddQuestRequest import *
from .TryCompleteObjectiveRequest import *
from .ForceCompleteObjectiveRequest import *
from .CompleteQuestRequest import *
from .AcceptQuestRequest import *
from .SkipObjectiveRequest import *
from .ShowErrorRequest import *
from .AddFriendToFavoritesRequest import *
from .RemoveFriendFromFavoritesRequest import *
from .TestBoolRequest import *
from .ClearMmRequest import *
from .BuyPremiumAccountRequest import *
from .BuyPremiumAccountGMRequest import *
from .BuyUnbanGMRequest import *
from .UpdateCameraFlybyRequest import *
from .ChangeMapRequest import *
from .ChangePAEndRequest import *
from .ChangeLastLoginRequest import *
from .RemoveFriendRequest import *
from .UsesUpgHeroTalRequest import *
from .InviteFriendRequest import *
from .AcceptFriendRequest import *
from .DeclineFriendRequest import *
from .SearchFriendRequest import *
from .AddFriendRequest import *
from .ReturnFriendRequest import *
from .AddFakeFriendsRequest import *
from .AddToPocketRequest import *
from .MarkEventViewedRequest import *
from .BuyHeroRequest import *
from .BuyHeroGoldRequest import *
from .UpgradeHeroRequest import *
from .MergeTalentsRequest import *
from .SetGuardRequest import *
from .AddDodgesRequest import *
from .UnretireRequest import *
from .SetWinsRequest import *
from .ReadyMatchMakingRequest import *
from .UpgradeTalentRequest import *
from .OnlyGuardRequest import *
from .GetPricesRequest import *
from .BuySpecialHeroRequest import *
from .CheckPendingQuestsRequest import *
from .BuySkinRequest import *
from .SelectSkinRequest import *
from .ClearFWODRequest import *
from .RefreshPingResultsRequest import *
from .GuildCreateRequest import *
from .GuildRenameRequest import *
from .GuildLeaveRequest import *
from .GuildDestroyRequest import *
from .GuildInviteRequest import *
from .GuildAcceptRequest import *
from .GuildDeclineRequest import *
from .GuildPromoteRequest import *
from .GuildDemoteRequest import *
from .GuildChangeOwnerRequest import *
from .GuildKickRequest import *
from .GuildInvestResourcesRequest import *
from .GuildMsgRequest import *
from .GuildRecalcRequest import *
from .GuildPutTalentToBankRequest import *
from .GuildTakeTalentFromBankRequest import *
from .GuildGiveBackRequest import *
from .GuildReturnTalentToBankRequest import *
from .GuildBankLimitsResetRequest import *
from .GuildBuyShopItemRequest import *
from .GiveActionRequest import *
from .SetLastPaymentRequest import *
from .TavernRerollRequest import *
from .BuySteamItemRequest import *
from .ConfirmSteamItemRequest import *
from .SetSteamSexRequest import *
from .GiveMuidDLCRequest import *
from .UpdateDLCRequest import *
from .RegisterDLCRequest import *
from .UnregisterDLCRequest import *
from .TestECRequest import *
from .BuyAeriaItemRequest import *
from .BuyGamigoItemRequest import *
from .BuyArcGamesItemRequest import *
from .BuyZZimaItemRequest import *
from .BillingReserveAmountRequest import *
from .BillingConfirmWriteOffRequest import *
from .BillingWriteOffRequest import *
from .BillingReplenishRequest import *
from .CreateComplaintRequest import *
from .ResetComplaintsRequest import *
from .SetLampLastDropTimeRequest import *
from .BuyTournamentTicketRequest import *
from .UpdateTournamentInfoRequest import *
from .ResetTournamentAccountRequest import *
from .GuildDeleteMsgRecievedRequest import *
from .BuyCustomFlagRequest import *
from .ChangeFlagRequest import *
from .AddCustomFlagRequest import *
from .SetMDVersionRequest import *
from .SetAFKStateRequest import *
from .NotifyTutorialStateChangedRequest import *
from .NotifySessionEndedRequest import *
from .AcceptDynamicQuestRequest import *
from .ForceCompleteDynamicObjectiveRequest import *
from .TryCompleteDynamicObjectiveRequest import *
from .CompleteDynamicQuestRequest import *
from .ReforgeTalentRequest import *
from .ReforgeUpgradeTalentRequest import *
from .ResetDynamicQuestsRequest import *
from .ClearDynamicQuestsFromServerRequest import *
from .AddTalentQuestRequest import *
from .CraftTalentsRequest import *
from .ResetLastPlayedTimeRequest import *
from .SetConditionRewardStateRequest import *
from .GiveDecreaseRatingQuestRequest import *
from .BuyBeginnersPackRequest import *
from .GetGuildDataForMapRequest import *
from .GuildInviteSuzerainRequest import *
from .StartSiegeRequest import *
from .LeaveSiegeRequest import *
from .GuildAcceptVassalRequest import *
from .GuildDeclineVassalRequest import *
from .RemoveVassalRequest import *
from .GetExVassalsListRequest import *
from .GetRecommendedVassalsListRequest import *
from .GetGuildsListRequest import *
from .GetGuildRequestsListRequest import *
from .SetGuildExperienceRequest import *
from .HideRecommendedVassalRequest import *
from .ResetSiegesCounterRequest import *
from .RemoveSuzerainRequest import *
from .RemoveNPCSuzerainRequest import *
from .SetSiegeDurationRequest import *
from .AddVassalRequest import *
from .GuildShopItemsLimitResetRequest import *
from .SetSiegeScoreRequest import *
from .RemoveGuildBuffsRequest import *
from .SetGuildBuffDurationRequest import *
from .AddGuildBuffRequest import *
from .SetGuildTodayRatingRequest import *
from .RecalcMyGuildRequest import *
from .UpdateTopBuildsRequest import *
from .SetExVassalEndTimeRequest import *
from .SetLostTargetLeftTimeRequest import *
from .SetHeroLastPlayedRequest import *
from .GuildSetRecruitmentMessageRequest import *
from .GuildSetRecruitmentLocaleRequest import *
from .GuildSetRecruitmentRatingRequest import *
from .GuildAcceptRecruitRequest import *
from .GuildDeclineRecruitRequest import *
from .CreateRecruitApplicationRequest import *
from .WithdrawRecruitApplicationRequest import *
from .GetRecommendedGuildsListRequest import *
from .GuildGerRecruitsListRequest import *
from .RemoveOutOfDateRecruitApplicationsRequest import *
from .DecreaseRecruitApplicationLifetimeRequest import *
from .ChoosePartyAgainRequest import *
from .SetLeavesRequest import *
from .RemoveRecentAllyRequest import *
from .ReinitRecentAllyRequest import *
from .AddRecentAllyRequest import *
from .ContextResourceBuyRequest import *
from .BoostBuildingProductionRequest import *
from .SetBoostedProductionRequest import *
from .SetLastBuyValue import *
from .GiveNewQuestFromPullRequest import *
from .GuildAddActiveBuffRequest import *
from .ResetPunishedNextUpdateTimeRequest import *
from .ModeratorMuteUserRequest import *
from .RerollShopRequest import *
from .RerollShopForFreeRequest import *
from .BuyRerollShopItemRequest import *
from .AddRerollShopItemRequest import *
from .RerollShopWithStatisticsRequest import *
from .ResetRerollShopRequest import *
from .RemoveRerollShopGroupRequest import *
from .RemoveRerollShopIsNewStateRequest import *
from .RemoveTalentUpgradeEntitiesIsNewStateRequest import *
from .SetActiveTalentSetRequest import *
from .SetTalentSetMessageRequest import *
from .SetGamesRequest import *
from .SetPlayerRatingRequest import *
from .ChangeFriendsPageRequest import *
from .GetLegendLeagueRequest import *
from .SetSeasonsResultShowedRequest import *
from .UpdateHeroSeasonPlaceRequest import *
from .RollEventRoll import *
from .QuestEventChooseRequest import *
from .DbgQuestEventClearRequest import *
from .DbgQuestEventChooseRequest import *
from .TradeEventBuyRequest import *
from .TradeEventGiveRewardRequest import *
from .DbgTradeEventClearRequest import *
from .SeasonEventBuyItemRequest import *
from .SeasonEventGiveRewardRequest import *
from .DbgSeasonEventClearRequest import *
from .AddLootboxRequest import *
from .OpenLootboxRequest import *
from .RemoveLootboxRequest import *
from .UpgradeTalentByEntityRequest import *
from .EndCurrentGuildWarEvent import *
from .SrvDebugRequest import *
