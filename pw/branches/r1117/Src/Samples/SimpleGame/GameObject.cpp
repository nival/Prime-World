#include "stdafx.h"

#include "GameObject.h"
#include "World.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace 
{
  static float g_AngularPursuitThreshold = 45.f;
  static float g_LinearVelocity = 40.f; 
  static float g_LinearVelocityMax = 70.f; 

  REGISTER_VAR("angular_pursuit_threshold", g_AngularPursuitThreshold, STORAGE_GLOBAL);

  REGISTER_VAR("town_player_velocity", g_LinearVelocity, STORAGE_GLOBAL);
  REGISTER_VAR("town_player_velocity_max", g_LinearVelocityMax, STORAGE_GLOBAL);

  static NDebug::DebugVar<int> debugCellX( "Player Cell X", "Town" );
  static NDebug::DebugVar<int> debugCellY( "Player Cell Y", "Town" );
  static NDebug::DebugVar<float> debugLinearVelocity( "Player Linear Velocity", "Town" );

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace Location
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
GameObject::GameObject() : 
	placement(NULLPLACEMENT),
	objectID(Protocol::invalidObjectId),
  targetPos(VNULL3),
  linearVelocity(g_LinearVelocity),
  movementFinishTime(0),
  clientResource("/Heroes/Female/_.SOBJ"),
  pursuitID(Protocol::invalidObjectId),
  isPassive(true),
  isPlayer(false),
  neighbourCount(0)
{
  linearVelocity = Max( FP_EPSILON, linearVelocity );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
GameObject::~GameObject()
{
  if ( IsValid( world ) )
  {
    VoxelGrid& voxelGrid = world->GetVoxelGrid();

    if ( voxelGridElement.thisElement != -1 )
      voxelGrid.RemoveObject( voxelGridElement );
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GameObject::SetWorldAndID( World* _world, Protocol::ObjectID _objectID )
{
	world = _world;
	objectID = _objectID;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GameObject::AddNeighbourCount( int count )
{
  neighbourCount += count;

#ifdef CHECK_TOWN_CONSISTENCY
  NI_ASSERT( neighbourCount >= 0, "Negative neighbour counter" );
#endif
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GameObject::MoveTo( const CVec2& _targetPos, Protocol::AbsoluteTime _finishTime )
{
//   systemLog( NLogg::LEVEL_MESSAGE ) << "Move Base: " << objectID << " " << movementInitTime << endl;
//   systemLog( NLogg::LEVEL_MESSAGE ) << "Move Base (sec): " << objectID << " " << NHPTimer::Time2Seconds(movementInitTime) << endl;
  
  targetPos.x = _targetPos.x;
  targetPos.y = _targetPos.y;
  targetPos.z = TownDebug::TOWN_GROUND_Z;

  movementFinishTime = _finishTime;

  isPassive = false;
  world->SetObjectPassive( objectID, isPassive );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GameObject::InitPlacement( const CVec2& _startPos, const CVec2& _targetPos, Protocol::AbsoluteTime _finishTime )
{
  if ( !IsValid( connectionToServer ) )
    return;

  CVec3 startPos3D( _startPos.x, _startPos.y, TownDebug::TOWN_GROUND_Z );
  CVec3 targetPos3D( _targetPos.x, _targetPos.y, TownDebug::TOWN_GROUND_Z );

  CVec3 direction = startPos3D - targetPos3D;
  float distance = direction.Length();
  float timeToGo = _finishTime - connectionToServer->GetServerTime();

  float deltaS = Clamp( timeToGo * linearVelocity, 0.f, distance );

  Normalize( &direction );

  MoveTo( _targetPos, _finishTime );
  placement.pos = targetPos + direction * deltaS;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool GameObject::RegisterInVoxelGrid()
{
  bool cellChanged = false;

  VoxelGrid& voxelGrid = world->GetVoxelGrid();
  
  VoxelCoords voxelCoords;
  voxelGrid.GetCoords( placement.pos.x, placement.pos.y, voxelCoords );

  if ( voxelGridElement.thisElement == -1 || 
       voxelGridElement.cellX != voxelCoords.x || voxelGridElement.cellY != voxelCoords.y )
  {
    if ( voxelGridElement.thisElement != -1 )
    {
      voxelGrid.RemoveObject( voxelGridElement );
      cellChanged = true;
    }

    voxelGridElement = voxelGrid.AddObject( placement.pos.x, placement.pos.y, objectID );
  }

  return cellChanged;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool GameObject::RegisterInVoxelGrid( byte cellX, byte cellY )
{
  VoxelGrid& voxelGrid = world->GetVoxelGrid();

  if ( voxelGridElement.cellX != cellX || voxelGridElement.cellY != cellY )
  {
    if ( voxelGridElement.thisElement != -1 )
      voxelGrid.RemoveObject( voxelGridElement );

    voxelGridElement = voxelGrid.AddObjectAtCell( cellX, cellY, objectID );

    return true;
  }

  return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GameObject::Pursuit( Protocol::ObjectID _pursuitID )
{
  pursuitID = _pursuitID;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GameObject::SetPosition( const CVec2& _pos, bool _register )
{
  placement.pos.x = _pos.x;
  placement.pos.y = _pos.y;
  placement.pos.z = TownDebug::TOWN_GROUND_Z;

  if ( _register )
    RegisterInVoxelGrid();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GameObject::SetPlacement( const Placement& _placement ) 
{ 
  placement = _placement;
  RegisterInVoxelGrid();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GameObject::OnTouch( int _objectID )
{

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GameObject::Step( Protocol::Time deltaTime, Protocol::AbsoluteTime currentHPTime )
{
  CVec3 direction = targetPos - placement.pos;
  float distance = direction.Length();
  float currentVelocity = linearVelocity;
  float restOfTime = movementFinishTime - currentHPTime;

  if ( deltaTime < FP_EPSILON || restOfTime < 0.f )
    currentVelocity = g_LinearVelocityMax;
  else
    currentVelocity = Clamp( distance / restOfTime, 0.f, g_LinearVelocityMax );

  if ( isPlayer )
    debugLinearVelocity.SetValue( currentVelocity );

  Normalize( &direction );

  float deltaS = Clamp( currentVelocity * deltaTime, 0.f, distance );

  placement.pos += direction * deltaS;

  placement.pos.z = TownDebug::TOWN_GROUND_Z;

  if ( isPlayer && fabs( direction * deltaS ) > FP_EPSILON  )
    systemLog( NLogg::LEVEL_MESSAGE ) << "POS: " << placement.pos << " D: " << direction * deltaS << endl;

  CheckRegistration();
  CheckPursuit();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GameObject::CheckPursuit()
{
  if ( Protocol::invalidObjectId != pursuitID && isPlayer )
  {
    CPtr<GameObject> gameObject = world->GetObjectById( pursuitID );

    if ( IsValid( gameObject ) )
    {
      CVec3 pursuitTarget = gameObject->GetPlacement().pos;
      CVec3 toPursuitTraget = pursuitTarget - placement.pos;
      CVec3 toMyTarget = targetPos - placement.pos;

      if ( toPursuitTraget.Length() < connectionToServer->GetMinimalDistance( pursuitID, objectID ) )
        return;

      Normalize( &toPursuitTraget );
      Normalize( &toMyTarget );

      if ( acos( toMyTarget.Dot( toPursuitTraget ) ) > ToRadian( g_AngularPursuitThreshold ) )
      {
        connectionToServer->MovePlayerTo( pursuitTarget, pursuitID );
      }
    }
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void GameObject::CheckRegistration()
{
  struct SwitchPassiveHelper
  {
    CPtr<World> world;

    void operator()( int objectID ) 
    { 
      world->SetObjectPassive( objectID, true ); 
    }
  };

  int oldCellX = voxelGridElement.cellX;
  int oldCellY = voxelGridElement.cellY;

  if ( RegisterInVoxelGrid() )
  {
    if ( isPlayer )
    {
      connectionToServer->RegisterPlayer( voxelGridElement.cellX, voxelGridElement.cellY );

      SwitchPassiveHelper goPassive;
      goPassive.world = world;

      int sx = voxelGridElement.cellX - oldCellX;
      int sy = voxelGridElement.cellY - oldCellY;

      world->GetVoxelGrid().ForAllNeighboursDelta( voxelGridElement.cellX, voxelGridElement.cellY, -sx, -sy, 1, goPassive );
    }
    else
    {
      const PoolElement& voxel = connectionToServer->GetPlayerVoxel();

      if ( abs( voxel.cellX - voxelGridElement.cellX) > 1 || abs( voxel.cellY - voxelGridElement.cellY) > 1 )
        isPassive = true;
    }
  }

  if ( isPlayer )
  {
    debugCellX.SetValue( voxelGridElement.cellX );
    debugCellY.SetValue( voxelGridElement.cellY );
  }
}

} // namespace Location

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BASIC_REGISTER_CLASS( Location::GameObject )	

