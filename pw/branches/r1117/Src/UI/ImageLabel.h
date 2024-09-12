#ifndef IMAGELABEL_H_INCLUDED
#define IMAGELABEL_H_INCLUDED

#include "NameMappedWindow.h"
#include "TextComponent.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace UI
{
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  class ImageLabel : public NameMappedWindow
	{
		NI_DECLARE_REFCOUNT_CLASS_1( ImageLabel, NameMappedWindow );
    DECLARE_LUA_TYPEINFO(ImageLabel);

  private:
    bool needUpdate;
		ImageComponent BackGround; //@iA@TODO: поле BackGround инициализируется из BD, на ее изменение нужно будет переинициализировать BackGround
		TextComponent Text;
    bool forbidSaturation;

    NDb::UIImageLabelLayout * GetImageLabelLayout() { return GetLayoutClone<NDb::UIImageLabelLayout>(); }
    const NDb::UIImageLabelLayout * GetImageLabelLayout() const { return GetLayoutClone<NDb::UIImageLabelLayout>(); }

	protected:
		virtual bool TestOpaque( int x, int y ) const;
		virtual void RenderBetweenBackgroundAndText() {}

    TextComponent & GetTextComponent() { return Text; }

    bool SetFontStyle( TextComponent *component, const string &styleName );

	public:
		ImageLabel() : needUpdate(true) {}

    const Rect & GetCaptionMargins() { return GetImageLabelLayout()->textMargins; }

    virtual void OnDataChanged();
		virtual void OnRefresh( float deltaTime );
    virtual void OnInvalidate() { NameMappedWindow::OnInvalidate(); needUpdate = true; }
		virtual void OnMovedSized() { needUpdate = true; NameMappedWindow::OnMovedSized(); }
		virtual void OnInit();
    virtual void Render();

    //from NameMappedWindow
    virtual void OnNameMapChanged() { ForceTextUpdate( ETextUpdateMode::KeepNamemaps ); }

    void ForbidSaturation (bool _forbid) {forbidSaturation = _forbid;}

    void SetParametersFromDb();

    void ForceTextUpdate( ETextUpdateMode::Enum mode = ETextUpdateMode::Full );
    void ForceTextUpdateLua() { ForceTextUpdate( ETextUpdateMode::Full ); }

    void SetCaptionTextW( const wstring & txt );
    string GetCaptionText();
    wstring const &GetCaptionTextW() const { return Text.GetText(); }

		void SetCaptionTextA( const char *text );

    bool SetCaptionStyle( const char *styleName );

		void SetCaptionMargins( int left, int right, int top, int bottom );

    void SetCaptionWordWrap( bool enable );
    void SetCaptionStretch( bool enable );

		void SetCaptionVAlign( int align );
		void SetCaptionHAlign( int align );

    void SetCaptionOpacity( float opacity ) { GetImageLabelLayout()->captionOpacity = opacity; Text.SetOpacity( opacity * GetOpacity() / 255.0f ); }
    float GetCaptionOpacity() { return GetImageLabelLayout()->captionOpacity; }

    void FixHeightToFitCaption( int minHeight, int extraMargin );
    void FixWidthToFitCaption( int minWidth, int extraMargin );
		int GetCaptionFitWidth() { return (int)( Text.GetTextWidth() + 0.5f ); }
		int GetCaptionFitHeight() { return (int)( Text.GetTextHeight() + 0.5f ); }

    virtual bool SetBackgroundMaterial( const NDb::BaseUIMaterial * _material );
    virtual bool SetBackgroundMaterialByName( const char *_resourceName );
    virtual void SetBackgroundTexture(const Render::Texture2DRef &_pTexture);

    Render::UIRenderMaterial& GetRenderMaterial() { return BackGround.GetRenderMaterial(); }

    bool SetShapeMaterial( const NDb::BaseUIMaterial * _material );
		void SetShapeType( int type );

    void SetBackgroundColor( float r, float g, float b, float a );
		void SetMaterialCoef3( float c3 );
		void SetMaterialCoef4( float c4 );
	};
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif //IMAGELABEL_H_INCLUDED
