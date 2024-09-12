#ifndef CONTROLSSET_H_INCLUDED
#define CONTROLSSET_H_INCLUDED

namespace Input
{

class HwEvent;
class Section;


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class ControlsSet : public CObjectBase
{
  OBJECT_BASIC_METHODS( ControlsSet );

public:
  ControlsSet( Section * _section = 0 ) : factor( 1.0f ), axisHwCtrlId( -1 ), allKeysPressed( false ), section( _section ) {}

  void AddKey( int hwKeyId );
  void SetAxis( int hwAxisId );
  bool GotAxis() const { return axisHwCtrlId >= 0; }

  void ProcessHwKeyEvent( const HwEvent & hwEvent, bool & _allKeysPressed );
  void ProcessHwMouseEvent( const HwEvent & hwEvent, float & delta, float & value, bool & _deltaUpdated, bool & _valueUpdated );

  void SetFactor( float _factor ) { factor = _factor; }
  float Factor() const { return factor; }
  bool Pressed() const { return allKeysPressed && !GotAxis(); }

  void Reset(); //Used on app focus loss

  bool Include( ControlsSet * other );
  void ClearSupersets() { supersets.clear(); }

  void GetControls(vector<int>& controls) const;

private:
  struct SKey
  {
    int   controlId;
    bool  pressed;
    SKey( int _controlId = -1 ) : controlId( _controlId ), pressed( false ) {}
  };

  typedef vector<CPtr<ControlsSet>> TCombinations;

  vector<SKey>      keys;
  int               axisHwCtrlId;
  float             factor;
  bool              allKeysPressed;

  TCombinations     supersets;

  CPtr<Section>     section;
};

} //namespace Input

#endif //CONTROLSSET_H_INCLUDED
