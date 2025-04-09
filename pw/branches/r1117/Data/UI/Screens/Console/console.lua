LuaConsole = LuaConsole or {}

function LuaConsole:OnInit()
  -- cache windows
  self["Console_Input"] = self:FindChild("Input")
  self["Console_Log"]   = self:FindChild("View")
    
  self:SetBind( 'console_prevcommand', 'PrevCommand' )
  self:SetBind( 'console_nextcommand', 'NextCommand' )
  self:SetBind( 'console_home',        'Home' )
  self:SetBind( 'console_end',         'End' )

  self:SetRepeatBind( 'console_scrollup',      'ScrollUp',       20, 20 )
  self:SetRepeatBind( 'console_scrolldown',    'ScrollDown',     20, 20 )
  --self:SetRepeatBind( 'console_eraselastchar', 'EraseLastChar', 500, 50 )
  --self:SetRepeatBind( 'console_charleft',      'CharLeft',      500, 50 )
  --self:SetRepeatBind( 'console_charright',     'CharRight',     500, 50 )

  self:SetBind( 'console_runcommand',          'RunCommand' )

  self:SetBind( 'console_autocomplete', 'AutoComplete' )
  self:SetBind( 'console_clear',        'Clear' )
end

function LuaConsole:OnShow( show )
  self.Console_Input:SetFocus( show )
end

function LuaConsole:PrevCommand()
  self.context:GetPrevCommand()
  self.Console_Input:SetInputText( self.context.currentCommand )
  self.Console_Input:EventEnd();
end

function LuaConsole:NextCommand()
  self.context:GetNextCommand()
  self.Console_Input:SetInputText( self.context.currentCommand )
  self.Console_Input:EventEnd();
end

function LuaConsole:RunCommand()
  self:PostCommandWide( self.Console_Input.inputText )
  self.Console_Input:Clear()
  self.context:ScrollToLast()
  self.context:SetToLastCommand()
end

function LuaConsole:ScrollUp(delta)
  self.context:Scroll( 4 )
end

function LuaConsole:ScrollDown(delta)
  self.context:Scroll( -4 )
end

function LuaConsole:AutoComplete()
  self.context:AutoComplete( self.Console_Input.inputText );
  self.Console_Input:SetInputText( self.context.currentCommand )
  self.context:ScrollToLast()
end

function LuaConsole:Clear()
  self.Console_Input:Clear()
  self.context:SetToLastCommand()
end

function LuaConsole:EraseLastChar()
  self.Console_Input:EventBack()
end

function LuaConsole:CharLeft()
  self.Console_Input:EventLeft()
end

function LuaConsole:CharRight()
  self.Console_Input:EventRight()
end

function LuaConsole:Home(obj)
  self.Console_Input:EventHome()
end

function LuaConsole:End(obj)
  self.Console_Input:EventEnd()
end