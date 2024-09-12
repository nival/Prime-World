
ClinicLobbyStartBtn =
{
  OnAction = function ( wnd )
    wnd.context:Start( 'Clinic' )
  end
}

ClinicLobbyShopBtn =
{
  OnAction = function( wnd )
    wnd.context:OpenShop()
  end
}

ClinicLobbyPrevLevelBtn =
{
  OnAction = function( wnd )
    wnd.context:SwitchToPrevLevel()
  end
}

ClinicLobbyNextLevelBtn =
{
  OnAction = function( wnd )
    wnd.context:SwitchToNextLevel()
  end
}

ClinicLobbyExitBtn =
{
  OnAction = function( wnd )
    wnd.context:Exit()
  end
}
