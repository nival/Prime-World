package LoaderSources {

	import flash.display.MovieClip;
	import flash.text.TextField;
	import BaseClasses.BaseResizableObject;
	
	public class TeamForceWrapper extends MovieClip 
	{

		public var mightLeft_txt:TextField;
		public var mightRight_txt:TextField;
		
		public function TeamForceWrapper()
		{
			visible = false;
		}
		
		public function SetTeamForce(forceLeft:String, forceRight:String):void
		{
			mightLeft_txt.text = forceLeft;
			mightRight_txt.text = forceRight;

		}

	}

}
