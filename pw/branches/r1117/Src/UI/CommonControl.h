#ifndef COMMONCONTROL_H_INCLUDED
#define COMMONCONTROL_H_INCLUDED

#include "ImageLabel.h"

namespace UI
{

class CommonControl : public ImageLabel
{
  NI_DECLARE_REFCOUNT_CLASS_1( CommonControl, ImageLabel );

public:
  DECLARE_LUA_TYPEINFO( CommonControl );

  CommonControl() {}

  virtual void OnInit();

  void PlayHiliteSound();
  void SetActivationBind( const char * commandName );

  virtual bool SetBackgroundMaterial( const NDb::BaseUIMaterial * _material );

  void OverrideDiffuseTexture( const NDb::Texture * _texture );

protected:
  bool IsMouseActionUsable( EMButton::Enum button );

  virtual bool OnActivationBind( const string & commandName );
  virtual bool OnActivationBind() { return false; }

private:
  NDb::UICommonControl *GetCommonCtlLayout() { return GetLayoutClone<NDb::UICommonControl>(); }

  NDb::Ptr<NDb::Texture> diffuseTextureOverride;
};

} //namespace UI

#endif //COMMONCONTROL_H_INCLUDED
