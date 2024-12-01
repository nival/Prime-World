package TalentBar
{	
	import ActionBar.ActionBarShortcut;
	import ActionBar.ActionBar;
	import Enums.ActionBarSlotState;
	import Interfaces.IActionButton;
	
	public class TalentShortCut extends ActionBarShortcut
	{

		private var talent:Talent;
		
		public function TalentShortCut(_talent:Talent,actionBar:ActionBar)
		{
			super(actionBar);
			talent = _talent;
			State = _talent.TalantState;
		}
		
		override public function set State(_state:int):void
		{
			if ( _actionButton && talent.altPath != "" )
			{
				if ( talent.IsAlternativStateActivated )
					_actionButton.iconPath = talent.altPath;
				else
					_actionButton.iconPath = talent.path;
			}
			super.State = _state;
		}
		
		override public function Press():void 
		{	
			super.Press();
			talent.Press();
		}
		override public function showTooltip():void
		{
			FSCommands.Send(FSCommands.TALENT_ACTIONTOOLTIP, FSCommands.TOOLTIP_SHOW + talent.column.toString() + ' ' + talent.raw.toString());
		}
		
		override public function hideTooltip():void
		{
			FSCommands.Send(FSCommands.TALENT_ACTIONTOOLTIP,  FSCommands.TOOLTIP_HIDE + talent.column.toString()+' '+talent.raw.toString());
		}

		override public function set actionButton(button:IActionButton)
		{
			super.actionButton = button;

			talent.shortcut = this;
			
			if (_actionButton == null) return;
	
			_actionButton.iconPath = talent.icon;
		}
		
		override public function get icon():String {
				return talent.icon;
			}
		
		override public function RemoveFromActionbar():void 
		{
			actionBar.RemoveShortcut(this);
			talent.shortcut = null;
		}
		
		override public function get DesirableIndex():int 
		{
			return talent.DesiredIndex;
		}
	}
}