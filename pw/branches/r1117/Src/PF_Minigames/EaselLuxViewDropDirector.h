#pragma once

namespace PF_Minigames
{

class Easel;

//////////////////////////////////////////////////////////////////////////
//
// calculate orientation of drop by two last known positions
//
//////////////////////////////////////////////////////////////////////////
class LuxViewDropDirector
{
public:
  LuxViewDropDirector();
  ~LuxViewDropDirector();

  // 
  void SetEasel( Easel* _easel );

  // returns accumulated rotation
  const CQuat GetRotation() const { return rotationQuat; }

  // returns true if new orientation provided
  bool SetDirection( const SVector& _direction );

private:
  LuxViewDropDirector(const LuxViewDropDirector& rhs);
  LuxViewDropDirector& operator=(const LuxViewDropDirector& rhs);

  bool CalculateOrientation();


  CPtr<Easel> easel;

  CVec3 zeroDist;

  SVector direction;

  CQuat rotationQuat;

};

} // namespace PF_Minigames