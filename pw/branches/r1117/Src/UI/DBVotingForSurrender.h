#pragma once
// Automatically generated file, don't change it manually!

#include "../libdb/Db.h"
#include "../libdb/Animated.h"
#include "../libdb/AnimatedAlgorithms.h"

struct IXmlSaver;

namespace NDb
{
struct VotingForSurrenderPerMission;

enum VFSMessageType
{
	VFSMESSAGETYPE_SHOWMESSAGETOPLAYER = 0,
	VFSMESSAGETYPE_SHOWMESSAGETOCOMMAND = 1,
	VFSMESSAGETYPE_SHOWMESSAGETOALL = 2,
};

const char *EnumToString( const VFSMessageType value );
const VFSMessageType StringToEnum_VFSMessageType( const char* value );

template <>
struct KnownEnum< VFSMessageType >
{
	enum { isKnown = 1 };
	enum { sizeOf = 3 };
	static const char *ToString( const VFSMessageType value ) { return EnumToString( value ); }
	static const VFSMessageType ToEnum( const char* value ) { return StringToEnum_VFSMessageType( value ); }
	static const VFSMessageType ToEnum( const string& value ) { return StringToEnum_VFSMessageType( value.c_str() ); }
	static const int SizeOf() { return 3; }
};

enum VFSUserMessages
{
	VFSUSERMESSAGES_CANTSTARTANOTHERINPROGRESS = 0,
	VFSUSERMESSAGES_CANTSTARTCOOLDOWN = 1,
	VFSUSERMESSAGES_PLAYERSTARTVOTING = 2,
	VFSUSERMESSAGES_CANTMAKEDECISIONISNTINPROGRESS = 3,
	VFSUSERMESSAGES_CANTMAKEDECISIONALREADYVOTED = 4,
	VFSUSERMESSAGES_COMMANDACCEPTSURRENDER = 5,
	VFSUSERMESSAGES_COMMANDDECLINESURRENDER = 6,
};

const char *EnumToString( const VFSUserMessages value );
const VFSUserMessages StringToEnum_VFSUserMessages( const char* value );

template <>
struct KnownEnum< VFSUserMessages >
{
	enum { isKnown = 1 };
	enum { sizeOf = 7 };
	static const char *ToString( const VFSUserMessages value ) { return EnumToString( value ); }
	static const VFSUserMessages ToEnum( const char* value ) { return StringToEnum_VFSUserMessages( value ); }
	static const VFSUserMessages ToEnum( const string& value ) { return StringToEnum_VFSUserMessages( value.c_str() ); }
	static const int SizeOf() { return 7; }
};

struct VFSMessageDesc
{
public:
	VFSMessageType type;
	CTextRef text;

	VFSMessageDesc();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }
};

struct VotingForSurrender : public DbResource
{
	DBRESOURCE_METHODS( VotingForSurrender );
public:
	Ptr< VotingForSurrenderPerMission > defaultMissionSettings;
	float delayBeforeVotingComplete;
	float votingDuration;
	int warforOpenedRadius;
	vector< VFSMessageDesc > messages;

	VotingForSurrender();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	VotingForSurrender& operator = ( const VotingForSurrender &_votingForSurrender ) { Assign( _votingForSurrender ); return *this; }
	VotingForSurrender( const VotingForSurrender &_votingForSurrender ) { Assign( _votingForSurrender ); }
	virtual void Assign( const VotingForSurrender &_votingForSurrender );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const VotingForSurrender * pOther = dynamic_cast< const VotingForSurrender * > ( _pResource );
		if ( pOther ) VotingForSurrender::Assign( *pOther );
	}
};

struct VotingForSurrenderPerMission : public DbResource
{
	DBRESOURCE_METHODS( VotingForSurrenderPerMission );
public:
	float cooldownAfterStart;
	float cooldownAfterPrevisionVoting;
	int maxUsersForFightIgnored;
	float timeDisconnectedPlayersVoteForFight;

	VotingForSurrenderPerMission();

	int operator&( IBinSaver &saver );
	int operator&( IXmlSaver &saver );
	void SerializeSelf( IXmlSaver &saver );

	DbResource::checksum_type CalcCheckSum() const { return 0; }

	VotingForSurrenderPerMission& operator = ( const VotingForSurrenderPerMission &_votingForSurrenderPerMission ) { Assign( _votingForSurrenderPerMission ); return *this; }
	VotingForSurrenderPerMission( const VotingForSurrenderPerMission &_votingForSurrenderPerMission ) { Assign( _votingForSurrenderPerMission ); }
	virtual void Assign( const VotingForSurrenderPerMission &_votingForSurrenderPerMission );
	virtual void OverridableAssign( const DbResource * _pResource )
	{
		const VotingForSurrenderPerMission * pOther = dynamic_cast< const VotingForSurrenderPerMission * > ( _pResource );
		if ( pOther ) VotingForSurrenderPerMission::Assign( *pOther );
	}
};

}; // namespace NDb
