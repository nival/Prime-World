#include "stdafx.h"

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <list>
#include <set>
#include <math.h>
#include <conio.h>

#include "System/Pointers/Pointers.h"
#include "System/JobThread.h"
#include "System/HPTimer.h"
#include "TestClassB.h"
#include "TestInterface.h"

//#define MTTEST_VISUALIZE

#ifdef MTTEST_VISUALIZE
#include "megacon.h"
#pragma comment( lib, "../megacon" )
#endif //MTTEST_VISUALIZE


struct Point
{
  int x, y;

  Point() : x( 0 ), y( 0 ) {}
  Point( int _x, int _y ) : x( _x ), y( _y ) {}
  explicit Point( ULONG64 l )
  {
    x = (int)(( l & 0xffffffff00000000ul ) >> 32 );
    y = (int)( l & 0x00000000fffffffful );
  }
  operator ULONG64 () const
  {
    return ( ( (ULONG64)x ) << 32 ) | ( (ULONG64)y & 0x00000000fffffffful );
  }
};


const static Point  FieldSize( 65536, 65536 );
const static int    OneSecond = 1024;
const static int    HalfSecond = OneSecond / 2 - 1;
const static int    MinTimeQuant = 3;

const static int    HitDistance = 4096;
const static int    PlayerSpeed = 2000;
const static int    MissileSpeed = 30000;
const static int    MaxItems2Draw = 32;

static volatile LONG  PlayersSpawned = 0;
static volatile LONG  MissilesSpawned = 0;

const static NHPTimer::FTime  ThreadDumpPeriod = 60.0;
const static NHPTimer::FTime  GlobalDumpPeriod = 600.0;


class Player;
class World;



class TargetPipeline : public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS( TargetPipeline )
    NI_DECLARE_BASE( BaseObjectMT )
  NI_DECLARE_END

public:
  TargetPipeline() : requestedTargets( 0 ) {}

  StrongMT<Player> AcquireTarget()
  {
    threading::MutexLock lock( mutex );

    if ( !targets.empty() )
    {
      StrongMT<Player> result = targets.front();
      targets.pop_front();
      return result;
    }
    ++requestedTargets;
    return 0;
  }

  bool AddTarget( Player * target )
  {
    threading::MutexLock lock( mutex );
    if ( requestedTargets <= 0 )
      return false;
    targets.push_back( target );
    --requestedTargets;
    return ( requestedTargets > 0 );
  }

  bool TargetsNeeded()
  {
    threading::MutexLock lock( mutex );
    return ( requestedTargets > 0 );
  }

private:
  threading::Mutex            mutex; //TODO: use spinlock
  int                         requestedTargets;
  std::list<StrongMT<Player>> targets;
};




class Entity : public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_1( Entity, BaseObjectMT );

public:
  Entity() : pos( 0 ), vel( 0 )
  {
  }

  void RandomizePos( const Point & field )
  {
    Point p;
    p.x = (__int64)rand() * (__int64)FieldSize.x / (__int64)RAND_MAX;
    p.y = (__int64)rand() * (__int64)FieldSize.y / (__int64)RAND_MAX;
    pos = p;
  }

  void RandomizeVel( int speed )
  {
    float a = 2.0f * 3.1415 * (float)rand() / (float)RAND_MAX;
    Point v;
    v.x = (int)( speed * cosf( a ) );
    v.y = (int)( speed * sinf( a ) );
    vel = v;
  }

  Point Position() const { return Point( pos ); }
  Point Velocity() const { return Point( vel ); }
  void SetPosition( const Point & _pos ) { pos = _pos; }
  void SetVelocity( const Point & _vel ) { vel = _vel; }

  void UpdatePosition( Point & _pos, Point & _vel, int dt )
  {
    _pos.x += ( _vel.x * dt + HalfSecond ) / OneSecond;
    _pos.y += ( _vel.y * dt + HalfSecond ) / OneSecond;
  }

protected:
  LONG64  pos;
  LONG64  vel;
};




class Player : public Entity
{
  NI_DECLARE_REFCOUNT_CLASS_1( Player, Entity );

public:
  Player( int _health ) :
  health( _health )
  {
    RandomizePos( FieldSize );
    RandomizeVel( PlayerSpeed );
  }

  void Update( int dt )
  {
    Point p( pos ), v( vel );

    UpdatePosition( p, v, dt );

    if ( p.x < 0 )
    {
      p.x = 0;
      v.x = +abs( v.x );
    }
    else if ( p.x >= FieldSize.x )
    {
      p.x = FieldSize.x;
      v.x = -abs( v.x );
    }

    if ( p.y < 0 )
    {
      p.y = 0;
      v.y = +abs( v.y );
    }
    else if ( p.y > FieldSize.y )
    {
      p.y = FieldSize.y;
      v.y = -abs( v.y );
    }

    pos = p;
    vel = v;
  }

  void Hit( int damage )
  {
    InterlockedExchangeAdd( &health, -damage );
  }

  bool Active() const { return health > 0; }

private:
  LONG    health;
};

NI_DEFINE_REFCOUNT( Player );



class Missile : public Entity
{
  NI_DECLARE_REFCOUNT_CLASS_1( Missile, Entity );

public:
  Missile( int _speed, int _damage, Player * _target ) :
  speed( _speed ), damage( _damage ), active( true ),
  target( _target )
  {
    RandomizePos( FieldSize );
  }

  void Update( int dt )
  {
    StrongMT<Player> player = target.Lock();
    if ( !player )
    {
      active = false;
      return;
    }

    if ( !player->Active() )
    {
      active = false;
      return;
    }

    Point p( pos );
    Point tgtPos = player->Position();
    
    Point dir( tgtPos.x - p.x, tgtPos.y - p.y );
    if ( ( abs( dir.x ) < HitDistance ) && ( abs( dir.y ) < HitDistance ) )
    {
      player->Hit( damage );
      active = false;
      return;
    }

    int len = (int)sqrtf( sqr( dir.x ) + sqr( dir.y ) );

    Point v( dir.x * speed / len, dir.y * speed / len );

    UpdatePosition( p, v, dt );

    pos = p;
    vel = v;
  }

  bool Active() const { return active; }

private:
  const int     speed;
  const int     damage;
  bool          active;
  WeakMT<Player> target;
};




class WorldThread : public threading::IThreadJob, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( WorldThread, threading::IThreadJob, BaseObjectMT );

  WorldThread() : nextDumpTime(), spawnedPlayers(), spawnedMissiles() {}

public:
  WorldThread( int _index, TargetPipeline * _targets, int _maxPlayers, int _maxMissiles ) :
  index( _index ),
  targets( _targets ),
  nextDumpTime( NHPTimer::GetScalarTime() ),
  spawnedPlayers( 0 ), spawnedMissiles( 0 )
  {
    assert( ( _maxPlayers > 0 ) && ( _maxMissiles > 0 ) );
    players.resize( _maxPlayers );
    missiles.resize( _maxMissiles );
  }

  ~WorldThread()
  {
  }

  virtual void Work( volatile bool & isRunning )
  {
    srand( index * 55 );

    int lastIntTime = (int)( NHPTimer::GetScalarTime() * OneSecond + 0.5 );
    
    while ( isRunning )
    {
      NHPTimer::FTime now = NHPTimer::GetScalarTime();

      if ( now > nextDumpTime )
      {
        nextDumpTime = now + ThreadDumpPeriod;
        printf( "Thread #%d spawned %dk / %dk objects\n", index, spawnedPlayers / 1000, spawnedMissiles / 1000 );
      }

      int newIntTime = (int)( now * OneSecond + 0.5 );

      if ( newIntTime >= lastIntTime + MinTimeQuant )
      {
        Update( newIntTime - lastIntTime );
        lastIntTime = newIntTime;
      }

      Sleep( 1 );
    }
  }

#ifdef MTTEST_VISUALIZE
  static void DrawTriangle( const Point & p, int size, Megacon::EColor color )
  {
    const int h3 = 289 * size / 1000; // sin(60)/3
    Megacon::Vec2 p0( p.x - size / 2, p.y + h3 );
    Megacon::Vec2 p1( p.x + size / 2, p.y + h3 );
    Megacon::Vec2 p2( p.x, p.y - 2 * h3 );

    Megacon::AddLine( p0, p1, color );
    Megacon::AddLine( p1, p2, color );
    Megacon::AddLine( p2, p0, color );
  }

  void Draw()
  {
    threading::MutexLock lock( drawMutex );

    const int playerSize = HitDistance * 2;
    for ( int i = 0; ( i < players.size() ) && ( i < MaxItems2Draw ); ++i )
      if ( players[i] )
      {
        Megacon::EColor color = ( index == 0 ) ? Megacon::eGreen : Megacon::eBlue;
        Point p = players[i]->Position();
        DrawTriangle( p, playerSize, color );
      }

    const int missSize = HitDistance / 2;
    const int missLen = HitDistance;
    for ( int i = 0; ( i < missiles.size() ) && ( i < MaxItems2Draw ); ++i )
      if ( missiles[i] )
      {
        Megacon::EColor color = ( index == 0 ) ? Megacon::eYellow : Megacon::eCyan;

        Point p = missiles[i]->Position(), v = missiles[i]->Velocity();
        float len = sqrtf( v.x * v.x + v.y * v.y );
        if ( len > 1 )
        {
          v.x = v.x * missLen / len;
          v.y = v.y * missLen / len;
          Megacon::AddLine( Megacon::Vec2( p.x + v.x, p.y + v.y ), Megacon::Vec2( p.x, p.y ), Megacon::eYellow );
        }
        DrawTriangle( p, missSize, color );
      }
  }
#endif //MTTEST_VISUALIZE

private:
  Player * SpawnPlayer()
  {
    ++spawnedPlayers;
    InterlockedIncrement( &PlayersSpawned );
    return new Player( 100 );
  }

  Missile * SpawnMissile( Player * target )
  {
    ++spawnedMissiles;
    InterlockedIncrement( &MissilesSpawned );
    return new Missile( MissileSpeed, 40, target );
  }

  void Update( int dt )
  {
    threading::MutexLock lock( drawMutex );

    for ( int i = 0; i < players.size(); ++i )
    {
      if ( !players[i] )
        players[i] = SpawnPlayer();

      if ( players[i] )
      {
        players[i]->Update( dt );
        if ( !players[i]->Active() )
        {
          players[i] = 0;
          players[i] = SpawnPlayer();
        }
      }
    }

    for ( int i = 0; i < missiles.size(); ++i )
    {
      if ( !missiles[i] )
      {
        StrongMT<Player> target = targets->AcquireTarget();
        if ( !target )
          continue;
        missiles[i] = SpawnMissile( target );
      }

      missiles[i]->Update( dt );
      if ( !missiles[i]->Active() )
        missiles[i] = 0;
    }

    while ( true )
    {
      int r = rand() % players.size();
      assert( players[r] );
      if ( !targets->AddTarget( players[r] ) )
        break;
    }
  }

private:
  int                       index;
  StrongMT<TargetPipeline>  targets;
  vector<StrongMT<Player>>  players;
  vector<StrongMT<Missile>> missiles;
  threading::Mutex          drawMutex;
  NHPTimer::FTime           nextDumpTime;
  int                       spawnedPlayers, spawnedMissiles;
};




class World : public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_1( World, BaseObjectMT );

public:
  World( int _threadsNum, int _playersNum, int _missNum ) :
  nextDraw( 0 ),
  nextDumpTime( NHPTimer::GetScalarTime() )
  {
    StrongMT<TargetPipeline> targets = new TargetPipeline;

    jobs.resize( _threadsNum );
    threads.resize( _threadsNum );
    for ( int i = 0; i < _threadsNum; ++i )
    {
      jobs[i] = new WorldThread( i, targets, _playersNum / _threadsNum, _missNum / _threadsNum );
      threads[i] = new threading::JobThread( jobs[i], "TestWorldThread" );
    }
  }

  ~World()
  {
    jobs.clear();
    threads.clear();
  }

  void Update()
  {
    const NHPTimer::FTime t = NHPTimer::GetScalarTime();

    if ( t > nextDumpTime )
    {
      nextDumpTime = t + GlobalDumpPeriod;
      int sec = (int)t;
      printf( "Total %dk / %dk objects spawned, uptime is %dd %02d:%02d:%02d\n",
        PlayersSpawned / 1000, MissilesSpawned / 1000,
        sec / 86400, ( sec % 86400 ) / 3600, ( sec % 3600 ) / 60, sec % 60 );
    }

#ifdef MTTEST_VISUALIZE
    if ( t > nextDraw )
    {
      nextDraw = t + 0.075;

      Megacon::Frame();
      Megacon::SetInfo( "spawn_status", "Spawned %dk players, %dk missiles", PlayersSpawned / 1000, MissilesSpawned / 1000 );

      Megacon::ClearLayer( "Entities" );
      Megacon::SetLayer( "Entities" );

      for ( int i = 0; i < jobs.size(); ++i )
        jobs[i]->Draw();
    }
#endif //MTTEST_VISUALIZE
  }

private:
  vector<StrongMT<WorldThread>>       jobs;
  vector<StrongMT<threading::JobThread>>  threads;
  NHPTimer::FTime                     nextDraw;
  NHPTimer::FTime                     nextDumpTime;
};


int main( int argc, char **argv )
{
#ifdef MTTEST_VISUALIZE
  Megacon::Init();
  Megacon::SetTitle( "Boink!" );
  Megacon::SetLayer( "Utility" );

  int margin = ( 2 * HitDistance );
  Megacon::AddRect( Megacon::Vec2( -margin, -margin ), Megacon::Vec2( FieldSize.x + margin, FieldSize.y + margin ), Megacon::eGrey );
  Megacon::AddRect( Megacon::Vec2( 0, 0 ), Megacon::Vec2( FieldSize.x, FieldSize.y ), Megacon::eWhite );
#endif //MTTEST_VISUALIZE

  printf( "\nUsage: MTTest [threads] [players] [missiles]\n" );

  int threads = 2;
  int players = 8000;
  int missiles = 16000;
  if ( argc >= 2 )
    threads = Max( threads, atoi( argv[1] ) );
  if ( argc >= 3 )
    players = Max( players, atoi( argv[2] ) );
  if ( argc >= 4 )
    players = Max( players, atoi( argv[3] ) );

  printf( "Checking type system across dll...\n" );
  
  Strong<TestClassB> b = new TestClassB( 5 );
  Strong<ITestInterface> a = ITestInterface::Produce( b, "A" );
  Weak<ITestInterface> wa = a;
  printf( "Test passed, name: %s\n", wa->Name().c_str() );

  printf( "Running endless test...\nPress Q to quit.\n" );

  StrongMT<World> w = new World( threads, players, missiles );

  while ( true )
  {
    if ( _kbhit() )
    {
      char c = _getch();
      if ( c == 'q' || c == 'Q' )
        break;
    }

    w->Update();
    Sleep ( 1 );
  }

#ifdef MTTEST_VISUALIZE
  Megacon::Shutdown();
#endif MTTEST_VISUALIZE

  return 0;
}
