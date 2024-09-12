#ifndef OVERTIPS_H_INCLUDED
#define OVERTIPS_H_INCLUDED

#include "../Render/aabb.h"

namespace NScene
{
  _interface IScene;
}


namespace UI
{
  class Window;
}

namespace NDb
{
  struct UIObjectOvertips;
}


namespace Overtips
{

const static int InvalidId = 0;

//Used to identify overtip on target object
struct SOvertipId
{
  bool      isPlain;
  int       dbIndex;

  SOvertipId() : isPlain( false ), dbIndex( -1 ) {}
  SOvertipId( bool plain, int index ) : isPlain( plain ), dbIndex( index ) {}
};

inline bool operator < ( const SOvertipId & left, const SOvertipId & right )
{
  if( !left.isPlain && right.isPlain )
    return true;
  if( left.isPlain && !right.isPlain )
    return false;
  return left.dbIndex < right.dbIndex;
}



//Overtip target object must derive from this interface
_interface ITarget : public IObjectBase
{
  virtual bool IsOvertipVisible() const = 0;
  virtual void SetupOvertipLayout( UI::Window * pWindow, const SOvertipId & overtipId ) = 0;
  virtual void UpdateOvertipLayout( UI::Window * pWindow, const SOvertipId & overtipId ) = 0;

  //Used for plain overtips
  virtual const Render::AABB & GetOvertipAabb() const = 0;

  //Used for full 3D overtips
  virtual const SHMatrix & GetOvertipWorldPosition() const = 0;

  virtual void OnOvertipRemoval() = 0;
};



//Overtips manager object interface
_interface IManager : public IBaseInterfaceST
{
  NI_DECLARE_CLASS_1( IManager, IBaseInterfaceST );

  virtual void InitOvertips( NScene::IScene * pScene ) = 0;
  virtual void StepOvertips() = 0;
  virtual int CreateOvertip( const NDb::UIObjectOvertips * pOvertips, ITarget * pTarget = 0 ) = 0;
  virtual bool RemoveOvertip( int id ) = 0;

  //Эти функции дублируют функционал колбеков:
  virtual UI::Window * GetOvertipWindow( int id, const SOvertipId & overtipId ) = 0;
  virtual bool UpdateOvertipWorldPosition( int id, const SHMatrix & matrix ) = 0;
  virtual bool UpdateOvertipAabb( int id, const CVec3 & center, const CVec3 & halfsize ) = 0;
};

} //namespace Overtips

#endif //OVERTIPS_H_INCLUDED
