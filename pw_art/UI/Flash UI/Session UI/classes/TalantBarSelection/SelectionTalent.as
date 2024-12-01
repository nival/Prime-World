package TalantBarSelection
{
	import flash.display.Shape;
	import flash.display.Sprite;
	import flash.display.MovieClip;

	import fl.transitions.Tween;
	import fl.transitions.easing.Strong;

	import flash.events.MouseEvent;
	import flash.geom.Point;
	import flash.display.DisplayObject;
	
	import flash.display.Loader;
	import flash.events.Event;
	import flash.net.URLRequest;

	import src.SeladonColor;
	import src.Desaturate;

	import fl.transitions.TweenEvent;
	import flash.display.Bitmap;
	import flash.utils.getDefinitionByName;
	
	import Enums.TalentUIState;

	
	public class SelectionTalent extends MovieClip
	{
		public var path:String;
				
		private const SIZE:Number = 70;

		private var configPath:String = 'art/general/';
		
		//unTour;
		public var column:int=0;
		public var raw:int=0;
		
		private var cooldown:Number = 0;
		
		private var ico_ld:Loader;
		private var _isActive:Boolean = false;
		
		private var isAddEffect:Boolean = true;
		//referense
		public var icoCont_mc:MovieClip;
		public var lock_bm:Shape;
		
		private var downPosition:Point = new Point( -10, -10);
		private var desiredIndex:int = -1;
		private var activeTalent_png:Bitmap;
		private var currentUpgradeLevelPos:Number = SIZE/2;
		private var maxUpgradeLevel:int = 3;
		private var upgradeLevels:Array = [];
		public function SelectionTalent()
		{
			lock_bm = icoCont_mc.getChildAt(0) as Shape;
			lock_bm.visible = false;
			
			ico_ld = new Loader;
			icoCont_mc.addChild(ico_ld);
			icoCont_mc.setChildIndex(ico_ld, 0);
			ico_ld.contentLoaderInfo.addEventListener(Event.INIT,icoInit);
			this.addEventListener(MouseEvent.MOUSE_OVER,onOver);
			this.addEventListener(MouseEvent.MOUSE_OUT,onOut);
		}
		
		public function set IsActive(value:Boolean):void
		{
			_isActive = value;
			
			if(_isActive&&activeTalent_png==null)
			{
				activeTalent_png = new Bitmap(new ActiveTalent_png());
				activeTalent_png.x = (SIZE - activeTalent_png.width) / 2;
				activeTalent_png.y = (SIZE - activeTalent_png.height) / 2;
				addChild(activeTalent_png);
				return;
			}
			
			if (!_isActive&&activeTalent_png!=null)
			{
				removeChild(activeTalent_png);
				activeTalent_png = null;
			}
		}
		public function get IsActive()
		{
			return _isActive;
		}
		
		private function onOver(e:MouseEvent):void
		{
			FSCommands.Send(FSCommands.SELECTION_TALENT_TOOLTIP,'1'+' '+column.toString()+ ' '+ raw.toString());
		}
		private function onOut(e:MouseEvent):void
		{	
			FSCommands.Send(FSCommands.SELECTION_TALENT_TOOLTIP,'0'+' '+column.toString()+ ' '+ raw.toString());
		}
		
		private function ResetState():void
		{
			SeladonColor.saturate(ico_ld);
			lock_bm.visible = false;
			
			if (upgradeLevels.length == 0) return;
			
			for each (var item:Bitmap in upgradeLevels) 
			{
				SeladonColor.saturate(item);
			}
		}
		
				
		public function setEnable():void
		{
			ResetState();
		}
		
		public function setOnTur():void
		{
			ResetState();
			SeladonColor.seladon(ico_ld);
			
				
			if (upgradeLevels.length == 0) return;
			
			for each (var item:Bitmap in upgradeLevels) 
			{
				SeladonColor.seladon(item);
			}
		}
		
		public function SetUpgradeLevel(upgradeLevel:int):void 
		{
			var image:Class = getDefinitionByName("upgradeLevelIcon") as Class;
			
			if (upgradeLevel < 0 ||upgradeLevel > maxUpgradeLevel ) return;
			
			for (var j:int = 0; j < upgradeLevels.length; j++) 
			{
				icoCont_mc.removeChild(upgradeLevels[j]);
			}
			
			currentUpgradeLevelPos = SIZE / 2;
			
			upgradeLevels = new Array();
			
			for (var i:int = 0; i < upgradeLevel; i++) 
			{
				var bitm:Bitmap = new Bitmap(new image)
				icoCont_mc.addChild(bitm);
				bitm.x = currentUpgradeLevelPos - bitm.width;
				bitm.y = -SIZE/2;
				upgradeLevels.push(bitm);
				currentUpgradeLevelPos = bitm.x;
			}
		}
		
		public function set icon(_path:String):void
		{
			path = _path;

			if (path.length == 0)
			{
				ico_ld.unload();
				return;
			}

			var myURLRequest:URLRequest = new URLRequest(_path);

			ico_ld.unload();
			ico_ld.load(myURLRequest);
		}

		public function get icon():String
		{
			return path;
		}
		private function icoInit(e:Event):void
		{
			ico_ld.x = - (SIZE + ico_ld.width) / 4;
			ico_ld.y = - (SIZE + ico_ld.height) / 4;
			e.target.content.smoothing = true;
		}
	}
}