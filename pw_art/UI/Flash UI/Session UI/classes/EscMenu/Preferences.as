package EscMenu
{
	public class Preferences
	{
		private var main:Main;
		public function Preferences(_main:Main)
		{
			main = _main;
		}
		
		public function AddCheckBoxControl(controlName:String):void
		{
			main.optionsWindow.AddCheckBoxControl(controlName);
		}
		
		public function AddSliderControl(controlName:String,maxCount:int):void
		{
			main.optionsWindow.AddSliderControl(controlName, maxCount);
		}
		
		public function AddComboBoxControl(controlName:String,comboboxValues:Array):void
		{
			main.optionsWindow.AddComboBoxControl(controlName,comboboxValues);
		}
		
		public function SetControlValue(controlName:String, value:int, active:Boolean):void
		{
			main.optionsWindow.SetControlValue(controlName, value, active);
		}
		
		public function ActivateAbilityToChange(activate:Boolean):void
		{
			main.optionsWindow.ActivateAbilityToChange(activate);
		}
	}
}