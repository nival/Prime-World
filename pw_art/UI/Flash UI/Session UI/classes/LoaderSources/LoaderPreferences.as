package LoaderSources 
{
	public class LoaderPreferences 
	{
		private var main:LoaderMain;
		public function LoaderPreferences(_main:LoaderMain)
		{
			main = _main;
		}
		
		public function AddCheckBoxControl(controlName:String):void
		{
		}
		
		public function AddSliderControl(controlName:String,maxCount:int):void
		{
		}
		
		public function AddComboBoxControl(controlName:String,comboboxValues:Array):void
		{
		}
		
		public function SetControlValue(controlName:String, value:int, active:Boolean):void
		{
		}
		
		public function ActivateAbilityToChange(activate:Boolean):void
		{
		}
		
	}

}