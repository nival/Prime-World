package  StatisticBars
{
	
	import fl.transitions.TweenEvent;
	import flash.display.MovieClip;
	import fl.transitions.Tween;
	import fl.transitions.easing.Strong;
	
	
	public class TerrainDominate extends MovieClip 
	{
		private var dwarfenMaskTween:Tween;
		private var dwarfenLightTween:Tween;
		
		private var elfenMaskTween:Tween;
		private var elfenLightTween:Tween;
		
		private var dwarfenTerrain:Number = 1;
		private var elfenTerrain:Number = 1;
		
		private var time:int = 40;

		//reference in stage		
		public var dwarfenMask_mc:MovieClip;
		public var elfenMask_mc:MovieClip;
		public var neutral_mc:MovieClip;
		
		public var dwarfenLight_mc:MovieClip;
		public var elfenLight_mc:MovieClip;
	
		
				
		public function TerrainDominate() 
		{
			// constructor code.
			this.stop();
			dwarfenMaskTween = new Tween(dwarfenMask_mc, 'width', Strong.easeOut, 1, 1, time);
			dwarfenMaskTween.stop();
			
			dwarfenLightTween = new Tween(dwarfenLight_mc, 'x', Strong.easeOut, dwarfenLight_mc.x, dwarfenLight_mc.x, time);
			dwarfenLightTween.stop();			
			
			elfenMaskTween = new Tween(elfenMask_mc, 'width', Strong.easeOut, 1, 1, time);
			elfenMaskTween.stop();
			
			elfenLightTween = new Tween(elfenLight_mc, 'x', Strong.easeOut, elfenLight_mc.x, elfenLight_mc.x, time);
			elfenLightTween.stop();
			
			//asinkhron animation in light;
			elfenLight_mc.gotoAndPlay(25);
		}
		
		public function SetLightAlpha(humanTerr:Number, ElfTerr:Number):void 
		{
			if ((humanTerr + ElfTerr) == 1) 
			{
				dwarfenLight_mc.alpha = 0.8;
				elfenLight_mc.alpha = 0.8;
			}
			else 
			{
				dwarfenLight_mc.alpha = 1;
				elfenLight_mc.alpha = 1;
			}
		}
		
		
		public function set DwarfenTerrain(terrain:Number):void
		{
			dwarfenTerrain = Math.floor(this.width*terrain);
			
			dwarfenMaskTween.stop();
			dwarfenMaskTween.continueTo(dwarfenTerrain, time);
			dwarfenMaskTween.start();
			
			dwarfenLight_mc.visible = terrain > 0;
			dwarfenLightTween.stop();
			dwarfenLightTween.continueTo(dwarfenTerrain, time);
			dwarfenLightTween.start();
		}
		
		public function set ElfenTerrain(terrain:Number):void
		{
			
			elfenTerrain = Math.floor(this.width*terrain);
			
			elfenMaskTween.stop();
			elfenMaskTween.continueTo(elfenTerrain, time);
			elfenMaskTween.start();
			
			elfenLight_mc.visible = terrain > 0;
			elfenLightTween.stop();
			elfenLightTween.continueTo(neutral_mc.width - elfenTerrain, time);
			elfenLightTween.start();
		}
	}
}