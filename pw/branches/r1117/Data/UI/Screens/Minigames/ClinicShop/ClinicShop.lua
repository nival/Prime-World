--ClinicShop.lua

ClinicShopExitBtn =
{
  OnAction = function( wnd )
    wnd.context:ExitGame()
  end
}

ClinicShopItem =
{
  OnMouseDown = function( itemWnd, button, x, y )
    if ( button ~= 0) then
      return;
    end;

    if ( itemWnd.context:SelectItem( itemWnd ) ) then
      itemWnd.context:HiliteItem( itemWnd, true );
    end
  end;

  OnMouseOver = function( itemWnd, x, y )
    itemWnd.context:HiliteItem( itemWnd, false );
  end;

  OnMouseMove = function( itemWnd, x, y )
    itemWnd.context:HiliteItem( itemWnd, false );
    return true;
  end;
  
  SetItemState = function( itemWnd, id )
    itemWnd:GetChild( "Hilite" ):Show( id == "hilited" );
    itemWnd:GetChild( "Selection" ):Show( id == "selected" );
  end;
}

ClinicShopBuyBtn =
{
  OnAction = function( itemWnd )
    itemWnd.context:BuyNow();
  end;
}
