#include "CommandIdResolver.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFBaseHero : public CObjectBase
{
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFBaseUnit : public CObjectBase
{
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFFlagpole : public CObjectBase
{
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFShop : public CObjectBase
{
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFEaselPlayer : public CObjectBase
{
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFBuilding : public CObjectBase
{
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFBaseMaleHero : public CObjectBase
{
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class IWorldSessionInterface : public CObjectBase
{
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFPickupableObjectBase : public CObjectBase
{
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct Target
{
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NWorld
{
  class PFBaseHero : public CObjectBase
  {
  };
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NDb
{
  enum EEmotion
  {
  };
  enum ImpulseBuffs
  {
  };
  enum EBoostType
  {
  };
  enum EFaction
  {
  };
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace EEaselKeyboardEvents
{
  enum Enum
  {
  };
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define DEFINE_1_PARAM_CMD( N, name, type1, name1 ) \
{ if ( id == N ) { if ( nameOnly ) { return string( #name ); } else { string arg1 = ParseArgument( #name1, stream, (type1*)0 ); return Combine( #name, arg1 ); } } }
#define DEFINE_2_PARAM_CMD( N, name, type1, name1, type2, name2 ) \
{ if ( id == N ) { if ( nameOnly ) { return string( #name ); } else { string arg1 = ParseArgument( #name1, stream, (type1*)0 ); string arg2 = ParseArgument( #name2, stream, (type2*)0 ); return Combine( #name, arg1, arg2 ); } } }
#define DEFINE_3_PARAM_CMD( N, name, type1, name1, type2, name2, type3, name3 ) \
{ if ( id == N ) { if ( nameOnly ) { return string( #name ); } else { string arg1 = ParseArgument( #name1, stream, (type1*)0 ); string arg2 = ParseArgument( #name2, stream, (type2*)0 ); string arg3 = ParseArgument( #name3, stream, (type3*)0 ); return Combine( #name, arg1, arg2, arg3 ); } } }
#define DEFINE_4_PARAM_CMD( N, name, type1, name1, type2, name2, type3, name3, type4, name4 ) \
{ if ( id == N ) { if ( nameOnly ) { return string( #name ); } else { string arg1 = ParseArgument( #name1, stream, (type1*)0 ); string arg2 = ParseArgument( #name2, stream, (type2*)0 ); string arg3 = ParseArgument( #name3, stream, (type3*)0 ); string arg4 = ParseArgument( #name4, stream, (type4*)0 ); return Combine( #name, arg1, arg2, arg3, arg4 ); } } }
#define DEFINE_5_PARAM_CMD( N, name, type1, name1, type2, name2, type3, name3, type4, name4, type5, name5 ) \
{ if ( id == N ) { if ( nameOnly ) { return string( #name ); } else { string arg1 = ParseArgument( #name1, stream, (type1*)0 ); string arg2 = ParseArgument( #name2, stream, (type2*)0 ); string arg3 = ParseArgument( #name3, stream, (type3*)0 ); string arg4 = ParseArgument( #name4, stream, (type4*)0 ); string arg5 = ParseArgument( #name5, stream, (type5*)0 ); return Combine( #name, arg1, arg2, arg3, arg4, arg5 ); } } }
#define DEFINE_6_PARAM_CMD( N, name, type1, name1, type2, name2, type3, name3, type4, name4, type5, name5, type6, name6 ) \
{ if ( id == N ) { if ( nameOnly ) { return string( #name ); } else { string arg1 = ParseArgument( #name1, stream, (type1*)0 ); string arg2 = ParseArgument( #name2, stream, (type2*)0 ); string arg3 = ParseArgument( #name3, stream, (type3*)0 ); string arg4 = ParseArgument( #name4, stream, (type4*)0 ); string arg5 = ParseArgument( #name5, stream, (type5*)0 ); string arg6 = ParseArgument( #name6, stream, (type6*)0 ); return Combine( #name, arg1, arg2, arg3, arg4, arg5, arg6 ); } } }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define DEFINE_1_PARAM_CMD_CHECK DEFINE_1_PARAM_CMD
#define DEFINE_2_PARAM_CMD_CHECK DEFINE_2_PARAM_CMD
#define DEFINE_3_PARAM_CMD_CHECK DEFINE_3_PARAM_CMD
#define DEFINE_4_PARAM_CMD_CHECK DEFINE_4_PARAM_CMD
#define DEFINE_5_PARAM_CMD_CHECK DEFINE_5_PARAM_CMD
#define DEFINE_6_PARAM_CMD_CHECK DEFINE_6_PARAM_CMD
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
string Combine( const char* name, const string& arg1 )
{
  return string( name ) + " { " + arg1 + " }"; 
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
string Combine( const char* name, const string& arg1, const string& arg2 )
{
  return string( name ) + " { " + arg1 + ", " + arg2 + " }"; 
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
string Combine( const char* name, const string& arg1, const string& arg2, const string& arg3 )
{
  return string( name ) + " { " + arg1 + ", " + arg2 + ", " + arg3 + " }"; 
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
string Combine( const char* name, const string& arg1, const string& arg2, const string& arg3, const string& arg4 )
{
  return string( name ) + " { " + arg1 + ", " + arg2 + ", " + arg3 + ", " + arg4 + " }"; 
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
string Combine( const char* name, const string& arg1, const string& arg2, const string& arg3, const string& arg4, const string& arg5 )
{
  return string( name ) + " { " + arg1 + ", " + arg2 + ", " + arg3 + ", " + arg4 + ", " + arg5 + " }"; 
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
string Combine( const char* name, const string& arg1, const string& arg2, const string& arg3, const string& arg4, const string& arg5, const string& arg6 )
{
  return string( name ) + " { " + arg1 + ", " + arg2 + ", " + arg3 + ", " + arg4 + ", " + arg5 + ", " + arg6 + " }"; 
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
string Combine( const char* name, const string& arg1, const string& arg2, const string& arg3, const string& arg4, const string& arg5, const string& arg6, const string& arg7 )
{
  return string( name ) + " { " + arg1 + ", " + arg2 + ", " + arg3 + ", " + arg4 + ", " + arg5 + ", " + arg6 + ", " + arg7 + " }"; 
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
string Combine( const char* name, const string& arg1, const string& arg2, const string& arg3, const string& arg4, const string& arg5, const string& arg6, const string& arg7, const string& arg8 )
{
  return string( name ) + " { " + arg1 + ", " + arg2 + ", " + arg3 + ", " + arg4 + ", " + arg5 + ", " + arg6 + ", " + arg7 + ", " + arg8 + " }"; 
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
string ParseArgument( const char* name, Stream* stream, int* ptr )
{
  int value;
  stream->Read( &value, sizeof( value ) );
  return string( NStr::StrFmt( "%s = %d", name, value ) );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
string ParseArgument( const char* name, Stream* stream, uint* ptr )
{
  int value;
  stream->Read( &value, sizeof( value ) );
  return string( NStr::StrFmt( "%s = %d", name, value ) );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
string ParseArgument( const char* name, Stream* stream, float* ptr )
{
  float value;
  stream->Read( &value, sizeof( value ) );
  return string( NStr::StrFmt( "%s = %2.3f", name, value ) );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
string ParseArgument( const char* name, Stream* stream, bool* ptr )
{
  bool value;
  stream->Read( &value, 1 );
  return string( NStr::StrFmt( "%s = %s", name, value ? "true" : "false" ) );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
string ParseArgument( const char* name, Stream* stream, Target* ptr )
{
  int pUnit, pObject;
  float x, y, z;
  int type;
  stream->Read( &pUnit, sizeof( pUnit ) );
  stream->Read( &pObject, sizeof( pObject ) );
  stream->Read( &x, sizeof( x ) );
  stream->Read( &y, sizeof( y ) );
  stream->Read( &z, sizeof( z ) );
  stream->Read( &type, sizeof( type ) );
  return string( NStr::StrFmt( "%s = { pUnit = id:%05d, pObject = id:%05d, vPosition = { %2.3f, %2.3f, %2.3f }, type = enum:%d", name, pUnit, pObject, x, y, z, type ) );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
string ParseArgument( const char* name, Stream* stream, CVec2* ptr )
{
  float x, y;
  stream->Read( &x, sizeof( x ) );
  stream->Read( &y, sizeof( y ) );
  return string( NStr::StrFmt( "%s = { %2.3f, %2.3f }", name, x, y ) );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
string ParseArgument( const char* name, Stream* stream, CPtr<T>* ptr )
{
  int value;
  stream->Read( &value, sizeof( value ) );
  return string( NStr::StrFmt( "%s = id:%05d", name, value ) );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
string ParseArgument( const char* name, Stream* stream, void* ptr )
{
  int value;
  stream->Read( &value, sizeof( value ) );
  return string( NStr::StrFmt( "%s = enum:%d", name, value ) );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace ReplayPlayer
{
string ResolveCommandId( Stream* stream, bool nameOnly /*= false*/ )
{
  int id = 0;
  stream->Seek( 0, SEEKORIGIN_BEGIN );
  stream->Read( &id, 4 );

  // huge copy-paste from HeroActions.cpp
  DEFINE_3_PARAM_CMD_CHECK( 0x2C5B9CC0, CmdCombatMoveHero, CPtr<PFBaseHero>, pHero, CVec2, target, bool, isShiftPressed);
  DEFINE_3_PARAM_CMD_CHECK( 0x2C59C380, CmdMoveHero,       CPtr<PFBaseHero>, pHero, CVec2, target, bool, isShiftPressed);
  DEFINE_1_PARAM_CMD_CHECK( 0x2C5B9481, CmdStopHero,       CPtr<PFBaseHero>, pHero);
  DEFINE_2_PARAM_CMD_CHECK( 0x2C5B9480, CmdAttackTarget,   CPtr<PFBaseHero>, pHero, CPtr<PFBaseUnit>, pTarget);
  DEFINE_4_PARAM_CMD_CHECK( 0x2C5C6480, CmdUseMagicTo,     CPtr<PFBaseHero>, pHero, INT32, magic, Target, target, bool, isShiftPressed);
  DEFINE_2_PARAM_CMD_CHECK( 0x2C5C6481, CmdToggleAutocastMagic, CPtr<PFBaseHero>, pHero, INT32, magic);
  DEFINE_3_PARAM_CMD_CHECK( 0xA05CB340, CmdDropConsumable,   CPtr<PFBaseHero>, pHero, INT32, slot, bool, isShiftPressed);
  DEFINE_3_PARAM_CMD      ( 0xB688C40,  CmdSwapConsumable,   CPtr<PFBaseHero>, pHero, INT32, slot1, INT32, slot2);
  DEFINE_4_PARAM_CMD_CHECK( 0x2C61F340, CmdBuyConsumable,    CPtr<PFBaseHero>, pHero, CPtr<PFShop>, pShop, int, index, int, slotIndex);
  DEFINE_2_PARAM_CMD      ( 0x2C622C41, CmdRemoveConsumable, CPtr<PFBaseHero>, pHero, INT32, slot );
  DEFINE_3_PARAM_CMD      ( 0x2C69BC40, CmdStackConsumables, CPtr<PFBaseHero>, pHero, INT32, src, INT32, dst);
  DEFINE_3_PARAM_CMD_CHECK( 0xB721280,  CmdSellConsumable, CPtr<PFBaseHero>, pHero, CPtr<PFShop>, pShop, INT32, slot );
  
  DEFINE_2_PARAM_CMD      ( 0xB69CB00,  CmdRedeemHero,       CPtr<PFBaseHero>, pHero, float, cost );
  DEFINE_3_PARAM_CMD_CHECK( 0x2C6A2BC0, CmdFollowUnit,       CPtr<PFBaseHero>, pHero, CPtr<PFBaseUnit>, pUnit, bool, isShiftPressed );
  DEFINE_1_PARAM_CMD_CHECK( 0x2C6BBB40, CmdHold,             CPtr<PFBaseHero>, pHero );
  DEFINE_2_PARAM_CMD_CHECK( 0xB76AAC0,  CmdRaiseFlag,        CPtr<PFBaseHero>, pHero, CPtr<PFFlagpole>, pFlagpole);

  DEFINE_4_PARAM_CMD_CHECK( 0xF5CC401,  CmdUseConsumable,    CPtr<PFBaseMaleHero>, pHero, INT32, slot, Target, target, bool, isShiftPressed);
  DEFINE_3_PARAM_CMD      ( 0xB695200,  CmdActivateTalent,   CPtr<PFBaseMaleHero>, pHero, INT32, level, INT32, slot);
  DEFINE_5_PARAM_CMD_CHECK( 0xB695201,  CmdUseTalent,        CPtr<PFBaseMaleHero>, pHero, INT32, level, INT32, slot, Target, target, bool, isShiftPressed);
  DEFINE_2_PARAM_CMD      ( 0xB6C3C40,  CmdDropTalent,       CPtr<PFBaseMaleHero>, pHero, INT32, index);
  DEFINE_3_PARAM_CMD      ( 0xB6C3C41,  CmdSwapTalents,      CPtr<PFBaseMaleHero>, pHero, INT32, index1, INT32, index2);
  DEFINE_4_PARAM_CMD      ( 0xB6C3C42,  CmdSetActiveTalent,  CPtr<PFBaseMaleHero>, pHero, INT32, level, INT32, slot, INT32, index);

  DEFINE_3_PARAM_CMD_CHECK( 0xA05CCB40, CmdPickupObject,   CPtr<PFBaseHero>, pHero, CPtr<PFPickupableObjectBase>, pPickupable, bool, isShiftPressed);
  DEFINE_3_PARAM_CMD      ( 0xB622CC0,  CmdMinimapSignal,  CPtr<PFBaseHero>, pHero, CVec2, target, NDb::EFaction, faction);
  DEFINE_2_PARAM_CMD      ( 0xB624B80,  CmdUpgradeAbility, CPtr<PFBaseHero>, pHero, int, nAbilityId);

  DEFINE_3_PARAM_CMD_CHECK( 0x9D62D440, CmdInitMinigame,   CPtr<PFEaselPlayer>, easelPlayer, INT32, objId, bool, isShiftPressed );

  DEFINE_2_PARAM_CMD      ( 0xF659340,  CmdDenyBuilding,   CPtr<PFBaseHero>, pHero, CPtr<PFBuilding>, pBuilding );

  DEFINE_2_PARAM_CMD_CHECK( 0x2C6614C0, CmdEmote,          CPtr<PFBaseHero>, pHero, NDb::EEmotion, emotion );

  // huge copy-paste from EaselCommands.cpp
  DEFINE_1_PARAM_CMD( 0xC565EB01, LeaveMinigameCommand,  CPtr<IWorldSessionInterface>, intrface );
  DEFINE_2_PARAM_CMD( 0xC5636C00, PauseMinigameCommand,  CPtr<IWorldSessionInterface>, intrface, bool, enablePause );

  DEFINE_4_PARAM_CMD( 0xF4682A80, EaselStartLevelCommand, CPtr<IWorldSessionInterface>, intrface, int, levelID, int, paintID, int, randomSeed );
  DEFINE_2_PARAM_CMD( 0xF4682A81, EaselStopLevelCommand, CPtr<IWorldSessionInterface>, intrface, uint, stepID );
  DEFINE_6_PARAM_CMD( 0xF46ADB40, EaselRemoteUpdateCommand, CPtr<IWorldSessionInterface>, intrface, uint, stepID , short, inputX, short, inputY, bool, mouseLeft, bool, mouseRight );
  DEFINE_3_PARAM_CMD( 0xF4683400, EaselBoostFiredCommand, CPtr<IWorldSessionInterface>, intrface, uint, stepID, NDb::EBoostType, boostType );
  DEFINE_4_PARAM_CMD( 0xF469BB41, EaselRegenerateBoostsCommand, CPtr<IWorldSessionInterface>, intrface, int, levelID, int, randomSeed, bool, needToPay );
  DEFINE_2_PARAM_CMD( 0xC572C440, EaselKeyboardEventCommand, CPtr<IWorldSessionInterface>, intrface, EEaselKeyboardEvents::Enum, event );
  DEFINE_3_PARAM_CMD( 0xC5829500, EaselTransferItemCommand, CPtr<IWorldSessionInterface>, sessionInterface, CPtr<NWorld::PFBaseHero>, target, int, transactionId );

  DEFINE_1_PARAM_CMD( 0xC5716280, EaselCheatDropCooldownsCommand, CPtr<IWorldSessionInterface>, sessionInterface );

  DEFINE_3_PARAM_CMD( 0xF668B00, CmdUseImpulse, CPtr<PFBaseHero>, hero, NDb::ImpulseBuffs, impulseType, Target, target );

  return string( NStr::StrFmt( "<Unknown> id=0x%08X", id ) );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} // namespace ReplayPlayer