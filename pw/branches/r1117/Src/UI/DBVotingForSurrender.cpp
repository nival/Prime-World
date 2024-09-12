// Automatically generated file, don't change it manually!
#include "stdafx.h"
#include "../libdb/Checksum.h"
#include "../libdb/XmlSaver.h"
#include "../Scripts/lua.hpp"
#include "../Scripts/ScriptMacroses.h"
#include "System/StrUtils.h"

#include "DBVotingForSurrender.h"
namespace
{
	char enumToStrBuffer[12];
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
REGISTER_DBRESOURCE( VotingForSurrender );
REGISTER_DBRESOURCE( VotingForSurrenderPerMission );
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace NDb
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const VFSMessageType value )
{
	switch( value )
	{
		case VFSMESSAGETYPE_SHOWMESSAGETOPLAYER:
			return "ShowMessageToPlayer";
		case VFSMESSAGETYPE_SHOWMESSAGETOCOMMAND:
			return "ShowMessageToCommand";
		case VFSMESSAGETYPE_SHOWMESSAGETOALL:
			return "ShowMessageToAll";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum VFSMessageType", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const VFSMessageType StringToEnum_VFSMessageType( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (VFSMessageType)(NStr::ToInt( value ));
	if ( strcmp( value, "ShowMessageToPlayer" ) == 0 || strcmp( value, "VFSMESSAGETYPE_SHOWMESSAGETOPLAYER" ) == 0 )
		return VFSMESSAGETYPE_SHOWMESSAGETOPLAYER;
	if ( strcmp( value, "ShowMessageToCommand" ) == 0 || strcmp( value, "VFSMESSAGETYPE_SHOWMESSAGETOCOMMAND" ) == 0 )
		return VFSMESSAGETYPE_SHOWMESSAGETOCOMMAND;
	if ( strcmp( value, "ShowMessageToAll" ) == 0 || strcmp( value, "VFSMESSAGETYPE_SHOWMESSAGETOALL" ) == 0 )
		return VFSMESSAGETYPE_SHOWMESSAGETOALL;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum VFSMessageType", value ) );
	return VFSMESSAGETYPE_SHOWMESSAGETOPLAYER;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *EnumToString( const VFSUserMessages value )
{
	switch( value )
	{
		case VFSUSERMESSAGES_CANTSTARTANOTHERINPROGRESS:
			return "CantStartAnotherInProgress";
		case VFSUSERMESSAGES_CANTSTARTCOOLDOWN:
			return "CantStartCooldown";
		case VFSUSERMESSAGES_PLAYERSTARTVOTING:
			return "PlayerStartVoting";
		case VFSUSERMESSAGES_CANTMAKEDECISIONISNTINPROGRESS:
			return "CantMakeDecisionIsntInProgress";
		case VFSUSERMESSAGES_CANTMAKEDECISIONALREADYVOTED:
			return "CantMakeDecisionAlreadyVoted";
		case VFSUSERMESSAGES_COMMANDACCEPTSURRENDER:
			return "CommandAcceptSurrender";
		case VFSUSERMESSAGES_COMMANDDECLINESURRENDER:
			return "CommandDeclineSurrender";
	};

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %d for enum VFSUserMessages", value ) );
	NStr::ItoA( value, enumToStrBuffer, sizeof( enumToStrBuffer ) ); 
	return enumToStrBuffer;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const VFSUserMessages StringToEnum_VFSUserMessages( const char* value )
{
	if ( NStr::IsDecNumber( value ) )
		return (VFSUserMessages)(NStr::ToInt( value ));
	if ( strcmp( value, "CantStartAnotherInProgress" ) == 0 || strcmp( value, "VFSUSERMESSAGES_CANTSTARTANOTHERINPROGRESS" ) == 0 )
		return VFSUSERMESSAGES_CANTSTARTANOTHERINPROGRESS;
	if ( strcmp( value, "CantStartCooldown" ) == 0 || strcmp( value, "VFSUSERMESSAGES_CANTSTARTCOOLDOWN" ) == 0 )
		return VFSUSERMESSAGES_CANTSTARTCOOLDOWN;
	if ( strcmp( value, "PlayerStartVoting" ) == 0 || strcmp( value, "VFSUSERMESSAGES_PLAYERSTARTVOTING" ) == 0 )
		return VFSUSERMESSAGES_PLAYERSTARTVOTING;
	if ( strcmp( value, "CantMakeDecisionIsntInProgress" ) == 0 || strcmp( value, "VFSUSERMESSAGES_CANTMAKEDECISIONISNTINPROGRESS" ) == 0 )
		return VFSUSERMESSAGES_CANTMAKEDECISIONISNTINPROGRESS;
	if ( strcmp( value, "CantMakeDecisionAlreadyVoted" ) == 0 || strcmp( value, "VFSUSERMESSAGES_CANTMAKEDECISIONALREADYVOTED" ) == 0 )
		return VFSUSERMESSAGES_CANTMAKEDECISIONALREADYVOTED;
	if ( strcmp( value, "CommandAcceptSurrender" ) == 0 || strcmp( value, "VFSUSERMESSAGES_COMMANDACCEPTSURRENDER" ) == 0 )
		return VFSUSERMESSAGES_COMMANDACCEPTSURRENDER;
	if ( strcmp( value, "CommandDeclineSurrender" ) == 0 || strcmp( value, "VFSUSERMESSAGES_COMMANDDECLINESURRENDER" ) == 0 )
		return VFSUSERMESSAGES_COMMANDDECLINESURRENDER;

	NI_DATA_ALWAYS_ASSERT( NStr::StrFmt( "Invalid value %s for enum VFSUserMessages", value ) );
	return VFSUSERMESSAGES_CANTSTARTANOTHERINPROGRESS;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
VFSMessageDesc::VFSMessageDesc() :
		type( VFSMESSAGETYPE_SHOWMESSAGETOALL )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int VFSMessageDesc::operator&( IBinSaver &saver )
{
	saver.Add( 2, &type );
	saver.Add( 3, &text );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int VFSMessageDesc::operator&( IXmlSaver &saver )
{
	saver.Add( "type", &type );
	saver.Add( "text", &text );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
VotingForSurrender::VotingForSurrender() :
		delayBeforeVotingComplete( 5.0f )
	, votingDuration( 60.0f )
	, warforOpenedRadius( 80 )
{
	messages.resize( 7 );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int VotingForSurrender::operator&( IBinSaver &saver )
{
	saver.Add( 2, &defaultMissionSettings );
	saver.Add( 3, &delayBeforeVotingComplete );
	saver.Add( 4, &votingDuration );
	saver.Add( 5, &warforOpenedRadius );
	saver.Add( 6, &messages );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int VotingForSurrender::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			VotingForSurrender* parentPtr = (VotingForSurrender*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void VotingForSurrender::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "defaultMissionSettings", &defaultMissionSettings );
	saver.Add( "delayBeforeVotingComplete", &delayBeforeVotingComplete );
	saver.Add( "votingDuration", &votingDuration );
	saver.Add( "warforOpenedRadius", &warforOpenedRadius );
	messages.resize( 7 );
	saver.Add( "messages", &messages );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void VotingForSurrender::Assign( const VotingForSurrender& _votingForSurrender )
{
	defaultMissionSettings = _votingForSurrender.defaultMissionSettings;
	delayBeforeVotingComplete = _votingForSurrender.delayBeforeVotingComplete;
	votingDuration = _votingForSurrender.votingDuration;
	warforOpenedRadius = _votingForSurrender.warforOpenedRadius;
	messages = _votingForSurrender.messages;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
VotingForSurrenderPerMission::VotingForSurrenderPerMission() :
		cooldownAfterStart( 60.0f )
	, cooldownAfterPrevisionVoting( 15.0f )
	, maxUsersForFightIgnored( 1 )
	, timeDisconnectedPlayersVoteForFight( 180.0f )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int VotingForSurrenderPerMission::operator&( IBinSaver &saver )
{
	saver.Add( 2, &cooldownAfterStart );
	saver.Add( 3, &cooldownAfterPrevisionVoting );
	saver.Add( 4, &maxUsersForFightIgnored );
	saver.Add( 5, &timeDisconnectedPlayersVoteForFight );

	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int VotingForSurrenderPerMission::operator&( IXmlSaver &saver )
{
	if ( saver.HasParentAttr() )
	{
		string parent_str = saver.GetParentAttrValue();
		__parent = ReadResource( saver, DBID(parent_str) );
		if ( __parent.GetPtr() )
		{
			VotingForSurrenderPerMission* parentPtr = (VotingForSurrenderPerMission*)__parent.GetPtr();
			Assign( *parentPtr );
		}
	}

	SerializeSelf( saver );
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void VotingForSurrenderPerMission::SerializeSelf( IXmlSaver &saver )
{
	saver.Add( "cooldownAfterStart", &cooldownAfterStart );
	saver.Add( "cooldownAfterPrevisionVoting", &cooldownAfterPrevisionVoting );
	saver.Add( "maxUsersForFightIgnored", &maxUsersForFightIgnored );
	saver.Add( "timeDisconnectedPlayersVoteForFight", &timeDisconnectedPlayersVoteForFight );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void VotingForSurrenderPerMission::Assign( const VotingForSurrenderPerMission& _votingForSurrenderPerMission )
{
	cooldownAfterStart = _votingForSurrenderPerMission.cooldownAfterStart;
	cooldownAfterPrevisionVoting = _votingForSurrenderPerMission.cooldownAfterPrevisionVoting;
	maxUsersForFightIgnored = _votingForSurrenderPerMission.maxUsersForFightIgnored;
	timeDisconnectedPlayersVoteForFight = _votingForSurrenderPerMission.timeDisconnectedPlayersVoteForFight;
}
}; // namespace NDb
