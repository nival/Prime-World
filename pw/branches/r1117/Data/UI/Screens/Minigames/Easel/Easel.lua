function ShowTooltip( wnd, enter, pos )
  local tooltiplayout = wnd.base:GetChild( "TooltipLayout" )
  if enter then
    tooltiplayout:Show( true )
    tooltiplayout:GetChild( "BoostName" ):SetCaptionTextW( tooltiplayout:GetRelatedText( "boost_name" .. pos ) )
    tooltiplayout:GetChild( "BoostDescription" ):SetCaptionTextW( tooltiplayout:GetRelatedText( "boost_desc" .. pos ) )
  else
    tooltiplayout:Show( false )
  end
end

function FindPosAndShowTooltip( wnd, enter )
    local name = wnd:GetParent().name
    local prefix_pos = string.len( "Boost" ) + 1
    local index = tonumber( string.sub( name, prefix_pos, prefix_pos ) )
    ShowTooltip( wnd, enter, index )
end


-------------------------------------------------------------------------------------------------------------------------------
Boost_button = {}

function Boost_button:OnAction()
  local main = self.parent.parent
  local heroic = ( self.parent.name == "HeroicBoost" )
  self.context:FireBoostByButtIndex( GetIndexFromString( main.name ), heroic )
end


-------------------------------------------------------------------------------------------------------------------------------
EaselScreenAtExitBtn = {}
function EaselScreenAtExitBtn:OnAction()
end

function EaselScreenAtExitBtn:OnMouseOver( enter )
  ShowTooltip( self, enter, 6 )
end

Cooldown = 
{
  --OnMouseOver = FindPosAndShowTooltip
}

BoostNoMoney = 
{
  --OnMouseOver = FindPosAndShowTooltip

  OnShow = function( wnd, show )
    local elem_price = wnd:GetParent():GetChild( "Price" )
    clog( elem_price.name )
    if show then
      elem_price:SetCaptionStyle( "price_red" )
    else
      elem_price:SetCaptionStyle( "price" )
    end
  end
}

BoostLock = 
{
  --OnMouseOver = FindPosAndShowTooltip
}
