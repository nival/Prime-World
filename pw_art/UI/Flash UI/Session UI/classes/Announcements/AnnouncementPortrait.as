package Announcements
{
	import flash.display.DisplayObject;
	import flash.display.MovieClip;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.geom.ColorTransform;
	import flash.text.TextField;
	
	import BaseClasses.MateInfoBase;
	import Enums.EFraction;
	public class AnnouncementPortrait extends MateInfoBase
	{		
		public var announcementGlow_mc:MovieClip;
		public var miniLensFlare:MovieClip;
		
		private var lensFlare:DisplayObject;
		
		private var elfColor:uint = 0xFF1318;
		private var humanColor:uint = 0x30B7FF;
		private var neutralColor:uint = 0x00FF00;
		
		public function AnnouncementPortrait()
		{
			lensFlare = miniLensFlare.getChildAt(0) as DisplayObject;
			
			this.addChildAt(lensFlare, this.getChildIndex(miniLensFlare));
			lensFlare.x = miniLensFlare.x;
			lensFlare.y = miniLensFlare.y;
			this.removeChild(miniLensFlare);
			
			miniLensFlare = null;	
		}
	
		override protected function AddedToStage(e:Event):void 
		{
			onOverEffect = null;
			selectionEffect = null;
		}
		
		public function set AnnouncementColor(_color:uint):void
		{
			var colorTrans:ColorTransform = announcementGlow_mc.transform.colorTransform;

			colorTrans.redMultiplier = (_color >> 16 & 255) / 255;
			colorTrans.greenMultiplier = (_color >> 8 & 255) / 255;
			colorTrans.blueMultiplier = (_color & 255) / 255;
			
			announcementGlow_mc.transform.colorTransform = colorTrans;
			announcementGlow_mc.transform.colorTransform = colorTrans;
		}
		
		public function FractionColor(fraction:int):void
		{
			announcementGlow_mc.visible = true;
			
			if (fraction == EFraction.ELF_FACTION)
			{
				AnnouncementColor = elfColor;
				return;
			}
			if (fraction == EFraction.HUMAN_FACTION)
			{
				AnnouncementColor = humanColor;
				return;
			}
			
			if (fraction == EFraction.NEUTRAL)
			{
				AnnouncementColor = neutralColor;
				return;
			}
			
			announcementGlow_mc.visible = false;
		}
		
		override public function get level():int 
		{
			return super.level;
		}
		
		override public function set level(value:int):void 
		{
			var show:Boolean = value >= 1;
			
			levelRoundFrame.visible = show;
			if (lensFlare != null)
				lensFlare.visible = show;
				
			level_txt.visible = show;
			super.level = value;
		}
		
		public function set NeutralColor(value:uint):void
		{
			neutralColor = value;
			
		}
		
		public function get NeutralColor():uint
		{
			return neutralColor;
		}
		
		public function set HumanColor(value:uint):void
		{
			humanColor = value;
		}
		
		public function get HumanColor():uint
		{
			return humanColor;
		}
		
		public function set ElfColor(value:uint):void
		{
			elfColor = value;
		}
		
		public function get ElfColor():uint
		{
			return elfColor;
		}
	}
	
}