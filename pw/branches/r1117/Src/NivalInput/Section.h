#ifndef SECTION_H_INCLUDED
#define SECTION_H_INCLUDED

namespace Input
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Section : public CObjectBase
{
  OBJECT_BASIC_METHODS( Section );

public:
  Section() : active( true ), muted( false ) {}
  Section( const char * _name ) : dbgName( _name ), active( true ), muted( false ) {}

  const string & DbgName() const { return dbgName; }
  
  bool Enabled() const { return active && !muted; }

  void Activate( bool on ) { active = on; }
  void Mute( bool mute ) { muted = mute; }

private:
  string  dbgName;
  bool    active;
  bool    muted;
};

} //namespace Input

#endif //SECTION_H_INCLUDED
