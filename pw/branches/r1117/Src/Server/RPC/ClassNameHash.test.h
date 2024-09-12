#include "cxxtest/TestSuite.h"
#include "ClassNameHash.h"


class ClassNameHashTestSuite : public CxxTest::TestSuite 
{

public:
    void testHash()
    {
      TS_ASSERT_EQUALS( rpc::get_class_name_hash( "PerfCounterSample" ), 912063915 );
      TS_ASSERT_EQUALS( rpc::get_class_name_hash( "SvcInfo" ), 1739996 );
      TS_ASSERT_EQUALS( rpc::get_class_name_hash( "ClusterInfo" ), 922133746 );
      TS_ASSERT_EQUALS( rpc::get_class_name_hash( "ServicesStartInfo" ), 1408723022 );
      TS_ASSERT_EQUALS( rpc::get_class_name_hash( "SvcNetAddresses" ), 1256541977 );
      TS_ASSERT_EQUALS( rpc::get_class_name_hash( "ServerDef" ), 42542182 );
      TS_ASSERT_EQUALS( rpc::get_class_name_hash( "SUserInfo" ), 41258746 );
      TS_ASSERT_EQUALS( rpc::get_class_name_hash( "GameGuildData" ), 1896121997 );
      TS_ASSERT_EQUALS( rpc::get_class_name_hash( "SGameParameters" ), 686679165 );
      TS_ASSERT_EQUALS( rpc::get_class_name_hash( "SPlayerGameContext" ), -819135277 );
      TS_ASSERT_EQUALS( rpc::get_class_name_hash( "SGameMember" ), 997523569 );
      TS_ASSERT_EQUALS( rpc::get_class_name_hash( "SDevGameInfo" ), 672667700 );
      TS_ASSERT_EQUALS( rpc::get_class_name_hash( "SPreGamePerUserData" ), 1957893284 );
      TS_ASSERT_EQUALS( rpc::get_class_name_hash( "SPreGameData" ), 808604306 );
      TS_ASSERT_EQUALS( rpc::get_class_name_hash( "SPostGamePerUserData" ), -946940225 );
      TS_ASSERT_EQUALS( rpc::get_class_name_hash( "SPostGameData" ), -238497799 );
      TS_ASSERT_EQUALS( rpc::get_class_name_hash( "SForgeRollData" ), 636536893 );
      TS_ASSERT_EQUALS( rpc::get_class_name_hash( "SAwardInfo" ), 198743746 );
      TS_ASSERT_EQUALS( rpc::get_class_name_hash( "SUserAward" ), 206289845 );
      TS_ASSERT_EQUALS( rpc::get_class_name_hash( "SGuildAward" ), 1005183595 );
      TS_ASSERT_EQUALS( rpc::get_class_name_hash( "SessionStartEvent" ), 178144296 );
      TS_ASSERT_EQUALS( rpc::get_class_name_hash( "SessionStartPlayer" ), 890749419 );
      TS_ASSERT_EQUALS( rpc::get_class_name_hash( "SessionServerResultsPlayer" ), -232644134 );
      TS_ASSERT_EQUALS( rpc::get_class_name_hash( "SessionResultEvent" ), 858917841 );
      TS_ASSERT_EQUALS( rpc::get_class_name_hash( "MMakingMember" ), -2003420832 );
      TS_ASSERT_EQUALS( rpc::get_class_name_hash( "MMakingGame" ), 950654446 );
      TS_ASSERT_EQUALS( rpc::get_class_name_hash( "MMakingCanceled" ), 1453247207 );
      TS_ASSERT_EQUALS( rpc::get_class_name_hash( "ExceedingStepTimeInfoServer" ), -918123106 );
      TS_ASSERT_EQUALS( rpc::get_class_name_hash( "ReconnectAttemptInfo" ), 1715377844 );
      TS_ASSERT_EQUALS( rpc::get_class_name_hash( "SessionTrafficInfo" ), 895521771 );
      TS_ASSERT_EQUALS( rpc::get_class_name_hash( "SessionUserContext" ), 909224516 );
      TS_ASSERT_EQUALS( rpc::get_class_name_hash( "UserCheatEvent" ), 623220094 );
      TS_ASSERT_EQUALS( rpc::get_class_name_hash( "UserDisconnectEvent" ), -74435285 );
      TS_ASSERT_EQUALS( rpc::get_class_name_hash( "UserStatusEvent" ), -999126715 );
      TS_ASSERT_EQUALS( rpc::get_class_name_hash( "SessionClientResults" ), 844799461 );
      TS_ASSERT_EQUALS( rpc::get_class_name_hash( "SessionClientResultsPlayer" ), 1557410786 );
      TS_ASSERT_EQUALS( rpc::get_class_name_hash( "PermittedStatisticsMethods" ), 938527793 );
      TS_ASSERT_EQUALS( rpc::get_class_name_hash( "SMatchmakingRequestCore" ), -44052463 );
      TS_ASSERT_EQUALS( rpc::get_class_name_hash( "SMatchmakingRequest" ), -144381404 );
      TS_ASSERT_EQUALS( rpc::get_class_name_hash( "SGameResults" ), 692735099 );
      TS_ASSERT_EQUALS( rpc::get_class_name_hash( "SMatchmakingStatus" ), -28865749 );
      TS_ASSERT_EQUALS( rpc::get_class_name_hash( "SServerStatus" ), -188299926 );
      TS_ASSERT_EQUALS( rpc::get_class_name_hash( "SPlayerData" ), 1018851602 );
      TS_ASSERT_EQUALS( rpc::get_class_name_hash( "PlayerDetails" ), 268302879 );
      TS_ASSERT_EQUALS( rpc::get_class_name_hash( "PvxGameDetails" ), 114979854 );
      TS_ASSERT_EQUALS( rpc::get_class_name_hash( "SLocationPing" ), -468827998 );
      TS_ASSERT_EQUALS( rpc::get_class_name_hash( "SGeoInfo" ), 7991246 );
      TS_ASSERT_EQUALS( rpc::get_class_name_hash( "SRequestMember" ), -1196885936 );
      TS_ASSERT_EQUALS( rpc::get_class_name_hash( "SRequestCommonData" ), -744813269 );
      TS_ASSERT_EQUALS( rpc::get_class_name_hash( "SGameParty" ), 199506301 );
      TS_ASSERT_EQUALS( rpc::get_class_name_hash( "SBotGameMember" ), -382699890 );
      TS_ASSERT_EQUALS( rpc::get_class_name_hash( "SGame" ), 63821 );
      TS_ASSERT_EQUALS( rpc::get_class_name_hash( "SReconnectSlot" ), -1342357634 );
      TS_ASSERT_EQUALS( rpc::get_class_name_hash( "LoginResultData" ), -436458410 );
      TS_ASSERT_EQUALS( rpc::get_class_name_hash( "UserEnvInfo" ), 1104554996 );
      TS_ASSERT_EQUALS( rpc::get_class_name_hash( "UserSessionInfo" ), -1021650285 );
      TS_ASSERT_EQUALS( rpc::get_class_name_hash( "RelayInfo" ), 42000621 );
      TS_ASSERT_EQUALS( rpc::get_class_name_hash( "PartialReconnectInfo" ), -6545986 );
      TS_ASSERT_EQUALS( rpc::get_class_name_hash( "UserInfo" ), 8836871 );
      TS_ASSERT_EQUALS( rpc::get_class_name_hash( "ClientInfo" ), 183256871 );
      TS_ASSERT_EQUALS( rpc::get_class_name_hash( "ClientStartInfo" ), 1451462753 );
      TS_ASSERT_EQUALS( rpc::get_class_name_hash( "SAuxUserData" ), 676759306 );
      TS_ASSERT_EQUALS( rpc::get_class_name_hash( "SAuxData" ), 7952227 );
      TS_ASSERT_EQUALS( rpc::get_class_name_hash( "SClientStatistics" ), 1898736445 );
      TS_ASSERT_EQUALS( rpc::get_class_name_hash( "ChatUserInfo" ), 235744575 );
      TS_ASSERT_EQUALS( rpc::get_class_name_hash( "ChannelInfo" ), 906020621 );
      TS_ASSERT_EQUALS( rpc::get_class_name_hash( "SessionInfo" ), 1063787496 );
      TS_ASSERT_EQUALS( rpc::get_class_name_hash( "LoginHello" ), 201889101 );
      TS_ASSERT_EQUALS( rpc::get_class_name_hash( "LoginReply" ), 201895461 );
      TS_ASSERT_EQUALS( rpc::get_class_name_hash( "ServiceRequest" ), -195347710 );
      TS_ASSERT_EQUALS( rpc::get_class_name_hash( "ServiceReqReply" ), -976760419 );
      TS_ASSERT_EQUALS( rpc::get_class_name_hash( "FrontendHello" ), -1759430300 );
      TS_ASSERT_EQUALS( rpc::get_class_name_hash( "FrontendHelloReply" ), -661481284 );
    }

}; // class ClassNameHashTestSuite
