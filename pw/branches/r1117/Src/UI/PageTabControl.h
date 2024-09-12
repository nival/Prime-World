#pragma once
#include "ImageLabel.h"
#include "DBUI.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace UI
{
	class ImageLabel;
	class Button;
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	struct PageTabElement
	{
		Weak<Window> button;
		Weak<Window> page;

		PageTabElement(Weak<Window> _button, Weak<Window> _page) :
    button( _button ), page( _page )
    {}
	};

	class PageTabControl : public ImageLabel
	{
		NI_DECLARE_REFCOUNT_CLASS_1( PageTabControl, ImageLabel );

	private:
		int  nSelectedTab;
		vector<PageTabElement> elements;
    string eventSelect;

	protected:
		virtual void OnInit();
		
		virtual void OnEnable( bool _enable );
		virtual void OnShow( bool _show );

    virtual bool OnMouseMove( const Point & mouse ) { ImageLabel::OnMouseMove( mouse ); return true; }
		virtual void OnMouseOver( bool over, const Point & mouse );
		virtual bool OnMouseUp( EMButton::Enum mbutton );
		bool OnTabClick( Window *wndFrom, const UIMessage & msg );		
		void ActivateTab( int idx, bool bShow );		

	private:
		virtual bool GetCustomCursor( string * name, const Point & screenCoords ) const;

	public:
		void SelectTab( int idx );		
		void AddTabPage(const PageTabElement& tab);
		int GetSelectedTabPageIdx() const { return nSelectedTab; }
		PageTabElement GetTabPage(int idx);

    DECLARE_LUA_TYPEINFO(PageTabControl);
	};
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
