#ifndef TEXTCOMPONENTBASIC_H_INCLUDED
#define TEXTCOMPONENTBASIC_H_INCLUDED

#include "TextMarkup.h"

namespace UI
{

_interface IWindowNameMapInterface;

class TextComponentBasic : public NMarkup::INameMapResolver
{
public:
  TextComponentBasic() : nameMapregistrationEnabled( false ) {}
  virtual ~TextComponentBasic() {}

  void SetNameMapInterface( IWindowNameMapInterface * iface ) { nameMapInterface = iface; } //NOTE: Stores RAW pointer!

protected:
  //NMarkup::INameMapResolver
  virtual NNameMap::ReadonlyVariant * GetVariant( const char * name );

  void EnableNameMapRegistration( bool enable ) { nameMapregistrationEnabled = enable; }

private:
  bool  nameMapregistrationEnabled;
  Weak<IWindowNameMapInterface>  nameMapInterface;
};

} //namespace UI

#endif //TEXTCOMPONENTBASIC_H_INCLUDED
