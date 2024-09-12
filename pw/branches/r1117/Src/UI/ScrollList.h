#pragma once
#include "ScrollArea.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace UI
{
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	class ScrollList : public ScrollArea
	{
		NI_DECLARE_REFCOUNT_CLASS_1( ScrollList, ScrollArea );

		vector<Weak<Window> > items;
		int itemNamerIndex;
		
		Weak<Window> pHighlighted;
		Weak<Window> pSelected;
    //@iA@TODO: Динамически обновлять стили ImageComponent из layout
		ImageComponent Highlight;
		ImageComponent Selection;
		bool highlightChanged;
		bool selectionChanged;
		int highlightItem;

    CTPoint<int> maxRealItemSize;

    NDb::UIScrollListLayout * GetScrollListLayout() { return GetLayoutClone<NDb::UIScrollListLayout>(); }

		Window *CreateItemInt( const string & name, const string & relatedLayout );
		int GetItemAtInt( int x, int y );    
		void HighlightItemInt( int item );
		void SelectItemInt( int item );
		void RemoveHighlightAndSelectionInt( Window *p );
    void UpdateHiliteUndSelection();
    enum EScrollOpType { eScrollOpNone, eScrollOpAtBegin, eScrollOpAtEnd };
    void ArrangeChildren( EScrollOpType opType = eScrollOpNone, const Point & heightAdded = Point( 0, 0 ) );

    virtual void OnScrollUpdated() { highlightChanged = true; selectionChanged = true; }

	public:
		ScrollList();

		virtual void OnInit();
		virtual void OnRemoveChild( Window *child );
		virtual void OnMovedSized() { ArrangeChildren(); }

		virtual void OnMouseOver( bool over, const Point & mouse );
		virtual bool OnMouseMove( const Point & mouse );
		virtual bool OnMouseDown( EMButton::Enum mbutton, const Point & point );
		virtual bool OnMouseUp( EMButton::Enum mbutton );

		virtual void Render();

		void SetPlacingOrigin( int _origin ) { GetScrollListLayout()->placingOrigin = NDb::EUIListItemsPlacingOrigin( _origin ); ArrangeChildren(); }
    int  GetPlacingOrigin() { return GetScrollListLayout()->placingOrigin; }
		void SetPlacingOrder( int _order ) { GetScrollListLayout()->placingOrder = NDb::EUIListItemsPlacingOrder( _order ); ArrangeChildren(); }
		void SetMinItemSize( int w, int h ) { GetScrollListLayout()->minItemSize.Set( w,h ); ArrangeChildren(); }
		void SetMaxItemSize( int w, int h ) { GetScrollListLayout()->maxItemSize.Set( w,h ); ArrangeChildren(); }
		void SetMaxItemsTotal( int count ) { GetScrollListLayout()->maxItemsTotal = count; ArrangeChildren(); }
		void SetMaxStrideItems( int count ) { GetScrollListLayout()->maxStrideItems  = count; ArrangeChildren(); }
    const CTPoint<int> & GetMaxRealItemSize() const { return maxRealItemSize; }

		int GetItemsCount() { return items.size(); }
    Window* GetItemByIndex( int index ) const;
		int GetItemIndex( string item );
		string GetItemName( int item );

		Window * AddItem( string name, string relatedLayout );
		Window * AddItemToFront( string name, string relatedLayout );
		Window * InsertItemAfter( string name, string relatedLayout, int pos );
		Window * InsertItemBefore( string name, string relatedLayout, int pos );
		bool MoveItemAfter( int item, int pos );
		bool MoveItemBefore( int item, int pos );
		bool RemoveItem( int item );
		void SortItems( string luaSortFunction );
		void ClearItems();    

    void HoldView() { /*needUpdate = false;*/ }
    void ScrollToLastItem();

    DECLARE_LUA_TYPEINFO(ScrollList);
	};
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
