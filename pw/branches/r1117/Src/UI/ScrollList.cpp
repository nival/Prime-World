#include "stdafx.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "ScrollList.h"

namespace UI
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BEGIN_LUA_TYPEINFO(ScrollList, ScrollArea)
  LUA_METHOD(SetPlacingOrigin)
  LUA_METHOD(SetPlacingOrder)
  LUA_METHOD(SetMinItemSize)
  LUA_METHOD(SetMaxItemSize)
  LUA_METHOD(SetMaxItemsTotal)
  LUA_METHOD(SetMaxStrideItems)
  LUA_METHOD(GetItemsCount)
  LUA_METHOD(GetItemIndex)
  LUA_METHOD(GetItemName)
  LUA_METHOD(AddItem)
  LUA_METHOD(AddItemToFront)
  LUA_METHOD(InsertItemAfter)
  LUA_METHOD(InsertItemBefore)
  LUA_METHOD(MoveItemAfter)
  LUA_METHOD(MoveItemBefore)
  LUA_METHOD(RemoveItem)
  LUA_METHOD(SortItems)
  LUA_METHOD(ClearItems)
END_LUA_TYPEINFO(ScrollList)

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ScrollList::ScrollList()
: itemNamerIndex(0)
, highlightChanged( true )
, selectionChanged( true )
, highlightItem( -1 )
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ScrollList::OnInit()
{
  ScrollArea::OnInit();

  if ( GetScrollListLayout() )
  {
    Highlight.SetImageMaterial( GetScrollListLayout()->hilightMaterial, GetContext() );
    Selection.SetImageMaterial( GetScrollListLayout()->selectionMaterial, GetContext() );
    Highlight.SetRenderable( false );
    Selection.SetRenderable( false );
    highlightItem = -1;
  }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void ClampByLimits( int & x, int a, int b )
{
  if ( a > 0 && x < a )
    x = a;
  if ( b > 0 && x > b )
    x = b;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ScrollList::OnRemoveChild( Window *child )
{
  for ( int i = 0; i < items.size(); ++i )
  {
    if ( items[i] == child )
    {
      RemoveHighlightAndSelectionInt( child );
      RemoveItem( i );
      break;
    }
  }

  ScrollArea::OnRemoveChild( child );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ScrollList::OnMouseMove( const Point & mouse )
{
  HighlightItemInt( GetItemAtInt( mouse.x, mouse.y ) );

  ScrollArea::OnMouseMove( mouse ); //????

  return false; //don't processed. pass the processing to another screen
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ScrollList::OnMouseOver( bool over, const Point & mouse )
{
  if ( !over )
  {
    HighlightItemInt( -1 );
    return;
  }

  ScrollArea::OnMouseOver( over, mouse );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ScrollList::OnMouseDown( EMButton::Enum mbutton, const Point & point )
{
  if ( mbutton != EMButton::Left )
    return false;

  Highlight.SetImageMaterial( GetScrollListLayout()->preselectMaterial, GetContext() );
  highlightChanged = true;
  Invalidate();
  return false;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ScrollList::OnMouseUp( EMButton::Enum mbutton  )
{
  if ( mbutton != EMButton::Left )
    return false;

  Highlight.SetImageMaterial( GetScrollListLayout()->hilightMaterial, GetContext() );
  highlightChanged = true;
  Invalidate();

  if ( true )
    SelectItemInt( highlightItem );

  return false;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ScrollList::Render()
{
  ScrollArea::Render();

  UpdateHiliteUndSelection();

  Highlight.Render();
  Selection.Render();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ScrollList::GetItemAtInt( int x, int y )
{
  for ( int i = 0; i < items.size(); ++i )
  {
    if ( !items[i] )
      continue;
    Window *child = items[i];

    if ( child->IsVisible() && child->IsInsideWindow( Point( x, y ) ) )
      return i;
  }

  return -1;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ScrollList::HighlightItemInt( int item )
{
  Window *child = ( item >= 0 && item < items.size() ) ? items[item] : 0;
  if ( pHighlighted == child )
    return;
  Highlight.SetRenderable( false );
  pHighlighted = child;
  highlightChanged = true;
  highlightItem = item;
  Invalidate();
  if ( !GetScrollListLayout()->spawnMsgOnItemHighlighted.empty() )
    SendMsgAll( this, GetScrollListLayout()->spawnMsgOnItemHighlighted.c_str(), GetWindowName().c_str(), highlightItem );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ScrollList::SelectItemInt( int item )
{
  Window *child = ( item >= 0 && item < items.size() ) ? items[item] : 0;
  if ( pSelected == child )
    return;
  Selection.SetRenderable( false );
  pSelected = child;
  selectionChanged = true;
  Invalidate();
  if ( !GetScrollListLayout()->spawnMsgOnItemSelected.empty() )
    SendMsgAll( this, GetScrollListLayout()->spawnMsgOnItemSelected.c_str(), GetWindowName().c_str(), pSelected ? item : -1 );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ScrollList::RemoveHighlightAndSelectionInt( Window *p )
{
  if ( pHighlighted == p )
    HighlightItemInt( -1 );
  if ( pSelected == p )
    SelectItemInt( -1 );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ScrollList::UpdateHiliteUndSelection()
{
  if ( highlightChanged )
  {
    highlightChanged = false;

    if ( pHighlighted )
    {
      Highlight.SetDrawRect( pHighlighted->GetWindowRect() );
      Highlight.SetCropRect( pHighlighted->GetCropRect() );
      Highlight.SetRenderable( true );
    }
    else
      Highlight.SetRenderable( false );
  }

  if ( selectionChanged )
  {
    selectionChanged = false;

    if ( pSelected )
    {
      Selection.SetDrawRect( pSelected->GetWindowRect() );
      Selection.SetCropRect( pSelected->GetCropRect() );
      Selection.SetRenderable( true );
    }
    else
      Selection.SetRenderable( false );
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ScrollList::ArrangeChildren( EScrollOpType opType, const Point & heightAddedBefore )
{
  if ( items.empty() || !GetScrollListLayout() )
    return;

  //data to keep current scroll
  Point prevSz( GetScrollXSize(), GetScrollYSize() );
  prevSz -= GetWindowLayout()->size;
  CVec2 prevScroll( GetScrollX(), GetScrollY() );

  const bool leftNotRight = ( GetScrollListLayout()->placingOrigin == NDb::UILISTITEMSPLACINGORIGIN_LEFTTOP || GetScrollListLayout()->placingOrigin == NDb::UILISTITEMSPLACINGORIGIN_LEFTBOTTOM );
  const bool topNotBottom = ( GetScrollListLayout()->placingOrigin == NDb::UILISTITEMSPLACINGORIGIN_LEFTTOP || GetScrollListLayout()->placingOrigin == NDb::UILISTITEMSPLACINGORIGIN_RIGHTTOP );

  const int kx = ( leftNotRight ? 1 : -1 );
  const int ky = ( topNotBottom ? 1 : -1 );

  const bool byRows = ( GetScrollListLayout()->placingOrder == NDb::UILISTITEMSPLACINGORDER_BYROWS );
  const bool byCols = ( GetScrollListLayout()->placingOrder == NDb::UILISTITEMSPLACINGORDER_BYCOLUMNS );
  const bool byRowsOfCols = ( GetScrollListLayout()->placingOrder == NDb::UILISTITEMSPLACINGORDER_BYROWSOFCOLUMNS );
  const bool byColsOfRows = ( GetScrollListLayout()->placingOrder == NDb::UILISTITEMSPLACINGORDER_BYCOLUMNSOFROWS );

  const CTPoint<int> & listSize = GetSize();

  const int akx = ( byRows || byRowsOfCols ) ? kx : 0;
  const int aky = ( byCols || byColsOfRows ) ? ky : 0;
  const int bkx = ( byCols || byColsOfRows ) ? kx : 0;
  const int bky = ( byRows || byRowsOfCols ) ? ky : 0;
  const int aMaxItems = ( byRows || byCols ) ? 1 : GetScrollListLayout()->maxStrideItems;
  const int aMaxSize = byRowsOfCols ? listSize.x : ( byColsOfRows ? listSize.y : 0 );

  int px = 0;
  int py = 0;
  int bSize = 0;			
  int bSizeMax = 0;
  int aSize = aMaxSize;
  int aItems = aMaxItems;
  int aSizeMax = 0;
  maxRealItemSize.Set(0, 0);
  for ( int i = 0; i < items.size(); ++i )
  {
    if ( !items[i] )
      continue;
    Window *child = items[i];

    const CTPoint<int> & childSize = child->GetSize();
    int cx = childSize.x;
    int cy = childSize.y;
    ClampByLimits( cx, GetScrollListLayout()->minItemSize.x, GetScrollListLayout()->maxItemSize.x );
    ClampByLimits( cy, GetScrollListLayout()->minItemSize.y, GetScrollListLayout()->maxItemSize.y );
    if ( cx != childSize.x || cy != childSize.y )
      child->SetSize( cx, cy, false );

    maxRealItemSize.x = max(maxRealItemSize.x, cx);
    maxRealItemSize.y = max(maxRealItemSize.y, cy);

    const int aChildSize = cx * abs(akx) + cy * abs(aky);
    const int bChildSize = cx * abs(bkx) + cy * abs(bky);
    aSize += aChildSize;

    if ( ( aMaxItems > 0 && aItems >= aMaxItems ) || ( aMaxItems <= 0 && aSize >= aMaxSize ) )
    {
      aSize = aChildSize;
      aItems = 0;
      bSize += bSizeMax;
      bSizeMax = 0;
      px = bSize * bkx;
      py = bSize * bky;
    }

    aSizeMax = Max( aSizeMax, aSize );
    bSizeMax = Max( bSizeMax, bChildSize );

    child->SetLocation( px + ( !leftNotRight ? -cx : 0 ), py + ( !topNotBottom ? -cy : 0 ) );
    ++aItems;

    px += cx * akx;
    py += cy * aky;
  }

  bSize += bSizeMax;
  const int xScrollSize = ( byRows || byRowsOfCols ) ? aSizeMax : bSize;
  const int yScrollSize = ( byCols || byColsOfRows ) ? aSizeMax : bSize;
  ScrollArea::SetScrollXLimits( 0, 1, kx < 0 ? Min( -listSize.x, -xScrollSize ) : 0, kx < 0 ? -listSize.x : Max( 0, xScrollSize - listSize.x ) );
  ScrollArea::SetScrollYLimits( 0, 1, ky < 0 ? Min( -listSize.y, -yScrollSize ) : 0, ky < 0 ? -listSize.y : Max( 0, yScrollSize - listSize.y ) );

  //Restore previous scroll offset
  if ( opType != eScrollOpNone )
  {
    Point newSz( GetScrollXSize(), GetScrollYSize() );
    newSz -= GetWindowLayout()->size;

    CVec2 prevOffs( prevScroll.x * prevSz.x, prevScroll.y * prevSz.y );
    if ( opType == eScrollOpAtBegin )
    {
      if ( leftNotRight )
        prevOffs.x += heightAddedBefore.x;
      if ( topNotBottom )
        prevOffs.y += heightAddedBefore.y;
    }

    float newScrollX = newSz.x ? ( prevOffs.x / newSz.x ) : prevScroll.x;
    float newScrollY = newSz.y ? ( prevOffs.y / newSz.y ) : prevScroll.y;

    const NDb::UIScrollLimits & xlimits = XLimits(), & ylimits = YLimits();
    newScrollX = Clamp( newScrollX, xlimits.inMin, xlimits.inMax );
    newScrollY = Clamp( newScrollY, ylimits.inMin, ylimits.inMax );

    SetScroll( newScrollX, newScrollY );
  }

  highlightChanged = true;
  selectionChanged = true;
  Invalidate();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ScrollList::GetItemIndex( string item )
{
  for ( int i = 0; i < items.size(); ++i )
    if ( items[i] && items[i]->GetWindowName() == item )
      return i;
  return -1;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
string ScrollList::GetItemName( int item )
{
  if ( item < 0 || item > items.size() )
    return "";
  if ( !items[item] )
    return "";
  return items[item]->GetWindowName();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Window *ScrollList::CreateItemInt( const string & name, const string & relatedLayout )
{
  if ( GetScrollListLayout()->maxItemsTotal > 0 && items.size() >= GetScrollListLayout()->maxItemsTotal )
    return 0;
  string realName = name;
  if ( realName.empty() )
    realName = NStr::StrFmt( "UI_ScrollList_Item_AutoName_%d", itemNamerIndex++ );
  Window * item = Window::CreateChild( name.c_str(), relatedLayout.c_str(), 0,0,-1,-1, NDb::UIELEMENTHALIGN_LEFT, NDb::UIELEMENTVALIGN_TOP );
  if ( !item )
    return 0;
  NI_VERIFY( item, "Error adding item!", return 0 );
  return item;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Window * ScrollList::AddItem( string name, string relatedLayout )
{
  if ( Window * item = CreateItemInt( name, relatedLayout ) )
  {
    items.push_back( item );
    ArrangeChildren( eScrollOpAtEnd );
    //@iA@TODO: перерасставлять итемы в листе после добавления каждого нового нерационально
    //Надо бы все-таки вернуть _опциональное_ отложенное обновление чилдов..
    return item;
  }
  return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Window * ScrollList::AddItemToFront( string name, string relatedLayout )
{
  if ( Window * item = CreateItemInt( name, relatedLayout ) )
  {
    items.insert( items.begin(), item );
    ArrangeChildren( eScrollOpAtBegin, item->GetSize() );
    return item;
  }
  return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Window * ScrollList::InsertItemAfter( string name, string relatedLayout, int pos )
{
  pos = Clamp( pos, 0, ((int)items.size())-1 );
  if ( Window *item = CreateItemInt( name, relatedLayout ) )
  {
    items.insert( items.begin() + pos + 1, item );
    ArrangeChildren();
    return item;
  }
  return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Window * ScrollList::InsertItemBefore( string name, string relatedLayout, int pos )
{
  pos = Clamp( pos, 0, ((int)items.size())-1 );
  if ( Window *item = CreateItemInt( name, relatedLayout ) )
  {
    items.insert( items.begin() + pos, item );
    ArrangeChildren();
    return item;
  }
  return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ScrollList::MoveItemAfter( int item, int pos )
{
  if ( item < 0 || item >= items.size() )
    return false;

  pos = Clamp( pos, 0, ((int)items.size())-1 );
  if ( pos == item || pos == item-1 )
    return true;
  if ( pos > item )
    --pos;

  Weak<Window> p = items[item];
  items.erase( items.begin() + item );
  items.insert( items.begin() + pos + 1, p );
  ArrangeChildren();
  return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ScrollList::MoveItemBefore( int item, int pos )
{
  if ( item < 0 || item >= items.size() )
    return false;

  pos = Clamp( pos, 0, ((int)items.size())-1 );
  if ( pos == item || pos == item+1 )
    return true;
  if ( pos > item+1 )
    --pos;

  Weak<Window> p = items[item];
  items.erase( items.begin() + item );
  items.insert( items.begin() + pos, p );
  ArrangeChildren();
  return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ScrollList::RemoveItem( int item )
{
  if ( item < 0 || item >= items.size() )
    return false;

  if ( items[item] )
  {
    RemoveHighlightAndSelectionInt( items[item] );
    items[item]->Close();
  }

  items.erase( items.begin() + item );
  ArrangeChildren();
  return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ScrollList::ClearItems()
{
  for ( int i = 0; i < items.size(); ++i )
  {
    if ( items[i] )
    {
      RemoveHighlightAndSelectionInt( items[i] );
      items[i]->Close();
    }
  }
  items.clear();
  ArrangeChildren();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Window* ScrollList::GetItemByIndex( int index ) const
{
  if ( index < 0 || index >= items.size() )
    return NULL;

  return items[index];
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ScrollList::ScrollToLastItem()
{
  const CTPoint<int> outputAreaSize = GetSize();

  //if the last added item is out of our scroll area - move all children up/down
  if ( GetItemsCount() > 1 )
  {        
    const bool topNotBottom = (  GetPlacingOrigin() == NDb::UILISTITEMSPLACINGORIGIN_LEFTTOP 
      || GetPlacingOrigin() == NDb::UILISTITEMSPLACINGORIGIN_RIGHTTOP );

    int itemIndex(0);
    if ( topNotBottom )
    {
      //all items will be added at the bottom of items list
      itemIndex = GetItemsCount() - 2; //get the last before last item
    }
    else
    {
      NI_ASSERT(false, "Not tested!!!!");
      //all items will be added at the top of items list
      itemIndex = GetItemsCount() - 2; //get the last before last item
    }

    //last before last item
    Window* pLastBeforeLastItem = GetItemByIndex( itemIndex );

    //last item
    Window* pLastItem = GetItemByIndex( itemIndex + 1 );

    if ( pLastBeforeLastItem != NULL && pLastItem != NULL )
    {
      int pos( pLastBeforeLastItem->GetPos().y );
      pos += pLastBeforeLastItem->GetSize().y;

      //add the height of last added item
      pos += pLastItem->GetSize().y;// + pLastItem->GetCaptionMargins().y1 + pLastItem->GetCaptionMargins().y2;

      if ( pos > outputAreaSize.y )
      {        
        SetChildrenShift( GetChildrenShift().x, outputAreaSize.y - pos );
        ArrangeChildren();
      }          
    }
  }//if ( GetItemsCount() > 1 )
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma warning( push )
#pragma warning( disable: 4512 )
struct SItemsComparator
{
  Window *pWindow;
  const string & luaFunction;
  SItemsComparator( Window *p, const string & func )
    : pWindow(p)
    , luaFunction( func )
  {}
  bool operator ()( Weak<Window> & p1, Weak<Window> & p2 )
  {
    if ( !p1 )
      return false;
    if ( !p2 )
      return true;
    const string & name1 = (p1)->GetWindowName();
    const string & name2 = (p2)->GetWindowName();
    if ( name1.empty() )
      return false;
    if ( name2.empty() )
      return true;
    return pWindow->CallLuaSortCompareFunction( luaFunction.c_str(), name1.c_str(), name2.c_str() ) < 0.0f;
  }
};
#pragma warning( pop )
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ScrollList::SortItems( string luaSortFunction )
{
  SItemsComparator comparator( this, luaSortFunction );
  sort( items.begin(), items.end(), comparator );
  ArrangeChildren();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
REGISTER_CONTROLTYPE( NDb::UIScrollListLayout, ScrollList );
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
