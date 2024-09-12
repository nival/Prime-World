#ifndef FONTSTYLE_H_INCLUDED
#define FONTSTYLE_H_INCLUDED

#include "FontRender.h"

namespace UI
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class FontStyle : public IFontStyle, public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_2( FontStyle, IFontStyle, BaseObjectST );

public:
  FontStyle();
  FontStyle( const NDb::UIFontStyle* _uiFontStyle );
  ~FontStyle();

  void SetStyle( const NDb::UIFontStyle* _uiFontStyle );

  void SetDefaultSize( int size );

  //IFontStyle
  virtual const NDb::UIFontStyle* GetStyle() const { return uiFontStyle; }
  virtual Render::BaseMaterial* GetMaterial() { return renderMaterial; }
  virtual bool CheckModified()
  {
    bool changed = isModified;
    isModified = false;
    return changed;
  }

  virtual void DrawString( const wchar_t * text, unsigned length, float x, float y, const Render::Color & color, const Rect & cropRect );
  virtual float GetStringLength( const wchar_t * text, unsigned length );
  virtual IAlphabet * GetAlphabet();
  virtual const SFontMetric & GetMetric() const { return metric; }

private:
  void OnStyleResourceChanged( const NDb::DBID & );
  void SetupMaterial();
  IAlphabet * FindAlphabet( const NDb::UIFontStyle * dbStyle );

private:
  NDb::ChangeablePtr<NDb::UIFontStyle> uiFontStyle;
  Render::BaseMaterial * renderMaterial;
  Weak<UI::IAlphabet> alphabet;

  int   defaultSize;

  SFontMetric metric;

  bool isModified;
};

} // namespace UI

#endif //FONTSTYLE_H_INCLUDED
