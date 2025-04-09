MinigamePauseScreenResumeBtn =
{
  OnAction = function( wnd )
    wnd.context:YesButtonPressed()
  end
}

MinigamePauseScreenExitBtn =
{
  OnAction = function( wnd )
    wnd.context:NoButtonPressed()
  end
}
