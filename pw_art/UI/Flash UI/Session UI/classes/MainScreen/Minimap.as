package MainScreen
{

	import Enums.EMiniMapEffects;
	import Events.ToggleButtonClickedEvent;
	import flash.display.DisplayObject;
	import flash.display.MovieClip;
	import flash.display.Bitmap;
	import flash.events.Event;
	import flash.events.MouseEvent;
	import flash.display.Shape;
	import flash.utils.Dictionary;
	import src.ButtonTooltipEvent;
	import flash.geom.Point;
	import Components.ButtonRound;
	import Components.RoundFrame;
	import Components.Dragonval;
	import Events.MouseRightEvents;
	import Effects.AttentionEffect;
	import Effects.TargetZoneEffect;
	
	public class Minimap extends MovieClip
	{

		public var mapImage:Bitmap;

		private const IN:int = 1;
		private const OUT:int = 0;
		private const LEFT:int = 1;
		private const RIGHT:int = 0;
		
		private var signals:Vector.<AttentionEffect> = new Vector.<AttentionEffect>();
		
		//reference to stageObject
		public var timer_mc:GameTimer;
		public var miniMapAnim_mc:MovieClip;
		public var roundFrame:RoundFrame;
		public var iconBase_mc:MovieClip;
		public var miniMapZone_mc:MovieClip;
		public var signalBtn:ButtonRound;
		public var cameraBtn:ButtonRound;
		public var selfShadow_mc:MovieClip;
		public var dragonval_mc:Dragonval;
		public var dragonvalAdornIco_mc:MovieClip;
		public var dragonvalDoctIco_mc:MovieClip;

		private var globalPoint:Point;
		
		private var isHeroIsDead:Boolean = false;
		private var lockCameraBtn:Boolean = false;
		
		private var isCameraWasLocked:Boolean = false;
		private var isWasClickedWhenHeroIsDead:Boolean;
		
		public var __exportedProperties : Array = ['CameraTooltip','CameraToggledTooltip','SignalTooltip'];	
		private var waitingToSendProp:int = -1;
		
		private var effects:Dictionary = new Dictionary();
		
		private var _targetZoneEffect:TargetZoneEffect = new TargetZoneEffect();
		
		public function Minimap()
		{
			this.mouseEnabled = false;
			dragonvalAdornIco_mc.visible = false;
			dragonvalDoctIco_mc.visible = false;
	
			selfShadow_mc.stop();

			mapImage = new Bitmap();
			mapImage.name = "mapImage";

			correctSize();
			
			iconBase_mc.removeChildAt(0);
			iconBase_mc.addChild( mapImage );
						
			var shMask:Shape = new Shape();
			shMask.graphics.beginFill(0x000000,0.5);
			shMask.graphics.drawCircle(135, 135, 132);
			shMask.graphics.endFill();
			addChild(shMask);
			iconBase_mc.mask = shMask
			
			miniMapZone_mc.buttonMode = true;
			miniMapZone_mc.addEventListener(MouseEvent.MOUSE_OUT, minimapOut);
			miniMapZone_mc.addEventListener(MouseEvent.MOUSE_DOWN, minimapDown);
			miniMapZone_mc.addEventListener(MouseEvent.MOUSE_UP, minimapUp);
			miniMapZone_mc.addEventListener(MouseEvent.MOUSE_MOVE, minimapMove);
			miniMapZone_mc.addEventListener(MouseRightEvents.MOUSE_RIGHT_DOWN, minimapRightMouseDown);
			miniMapZone_mc.addEventListener(MouseRightEvents.MOUSE_RIGHT_UP, MinimapRightMouseUp);
			
			signalBtn.addEventListener('Up', OnSignalDown);
			cameraBtn.addEventListener(ToggleButtonClickedEvent.EVENT_TYPE, OnCameraDown);
			
			CameraTooltip = Localization.Tooltip_MinimapCameraBtn;
			CameraToggledTooltip = Localization.Tooltip_MinimapToggledCameraBtn;
			SignalTooltip = Localization.Tooltip_MinimapSignalBtn;	
			if (Localization.CompleteEventDispatcher != null)
				Localization.CompleteEventDispatcher.addEventListener(Event.COMPLETE, FillLocalization);
			
			addChild(_targetZoneEffect);
			
			_targetZoneEffect.mask = shMask;
		}
		private function FillLocalization(e:Event):void
		{
			CameraTooltip = Localization.Tooltip_MinimapCameraBtn;
			CameraToggledTooltip = Localization.Tooltip_MinimapToggledCameraBtn;
			SignalTooltip = Localization.Tooltip_MinimapSignalBtn;
		}
		
		public function set CameraTooltip(value:String):void
		{
			cameraBtn.Tooltip = value;
		}
		
		public function get CameraTooltip():String
		{
			return cameraBtn.Tooltip;
		}
		
		public function set CameraToggledTooltip(value:String):void
		{
			cameraBtn.TogledTooltip = value;
		}
		
		public function get CameraToggledTooltip():String
		{
			return cameraBtn.TogledTooltip;
		}
		
		public function set SignalTooltip(value:String):void
		{
			signalBtn.Tooltip = value;
		}
		
		public function get SignalTooltip():String
		{
			return signalBtn.Tooltip;
		}
		
		private function minimapOut(e:MouseEvent):void
		{
			e.stopPropagation();
			FSCommands.Send(FSCommands.MINIMAP_MOUSEOVER, this.OUT.toString() + ' ' + miniMapPlace);
		}
		private function minimapDown(e:MouseEvent):void
		{	
			e.stopPropagation();
			FSCommands.Send(FSCommands.MINIMAP_MOUSEDOWN, this.LEFT.toString() + ' ' + miniMapPlace);
		}
		
		private function minimapRightMouseDown(e:Event):void 
		{
			e.stopPropagation();
			FSCommands.Send(FSCommands.MINIMAP_MOUSEDOWN, this.RIGHT.toString() + ' ' + miniMapPlace);
		}
		
		public function AddSignal(X:Number, Y:Number, color:uint, lifeTime:Number):void
		{	
			var signal:AttentionEffect = null;
			
			for (var index:int = 0, count = signals.length; index < count; ++index)
			{
				if (signals[index].Available)
				{
					signal = signals[index];
					break;
				}
			}
			
			if (signal == null)
			{
				signal = new _AttentionEffect();
				
				addChild(signal);
				
				signals.push(signal);
			}
			
			signal.x = X * miniMapZone_mc.width;
			signal.y = Y * miniMapZone_mc.height;
			signal.Color = color;
			signal.Play(lifeTime);
		}
		
		public function set TargetZoneColor(value:uint):void
		{
			_targetZoneEffect.Color = value;
		}
		
		public function set TargetZoneThickness(value:uint):void
		{
			_targetZoneEffect.Thickness = value;
		}
		
		public function ShowTargetZone(X:Number, Y:Number, radius:Number):void
		{
			var w:Number = miniMapZone_mc.width;
			var h:Number = miniMapZone_mc.height;
			
			var zx:Number = X * w;
			var zy:Number = Y * h;
			var zr:Number = radius * Math.sqrt(w * w + h * h);
			
			_targetZoneEffect.x = zx;
			_targetZoneEffect.y = zy;
			_targetZoneEffect.Radius = zr;
			_targetZoneEffect.visible = true;
			_targetZoneEffect.Update();
		}
		
		public function HideTargetZone():void
		{
			_targetZoneEffect.visible = false;
		}
		
		private function minimapUp(e:MouseEvent):void
		{
			e.stopPropagation();
			FSCommands.Send(FSCommands.MINIMAP_MOUSEUP,this.LEFT.toString()+ ' ' + miniMapPlace);
		}
		
		private function MinimapRightMouseUp(e:MouseEvent):void
		{
			e.stopPropagation();
			FSCommands.Send(FSCommands.MINIMAP_MOUSEUP,this.RIGHT.toString()+ ' ' + miniMapPlace);
		}
		
		private function minimapMove(e:MouseEvent):void
		{
			e.stopPropagation();
			if(e.buttonDown)
			{
				FSCommands.Send(FSCommands.MINIMAP_ACTIONMOVE, miniMapPlace);
			}
			FSCommands.Send(FSCommands.MINIMAP_MOUSEOVER, this.IN.toString() + ' ' + miniMapPlace);
		}
		
		private function OnSignalDown(e:Event):void
		{
			e.stopPropagation();
			FSCommands.Send(FSCommands.SIGNAL_MOUSECLICK);
		}
		private function OnCameraDown(e:ToggleButtonClickedEvent):void
		{
			e.stopPropagation();
			
			if (isHeroIsDead) 
				waitingToSendProp = int(lockCameraBtn /*e.Checked*/);
			
			SendCameraLock(e.Checked);
		}
		
		private function SendCameraLock(checked:Boolean):void
		{
			FSCommands.Send(FSCommands.CAMERA_MOUSECLICK, int(checked).toString());
		}
		
		
		public function correctSize():void
		{
			mapImage.width = roundFrame.width;
			mapImage.height = roundFrame.height;
		}
		
		public function SetCameraMode(cameraOn:Boolean):void 
		{
			if (cameraOn)
				cameraBtn.SwitchOn();
			else
				cameraBtn.SwitchOff();
		}
		
		public function SetMinimapEffect(index:int, effectNum:int):void 
		{
			if (effectNum == EMiniMapEffects.None && effects[index]!=null)
			{
				removeChild(effects[index]);
				effects[index] = null;
				return;
			}
			
			if (effects[index] == null)
			{
				var effect = CreateEffect(effectNum);
				if (effect == null) return;

				effects[index] = effect;
				addChild(effect);
			}
			
			effects[index].visible = true;
			effects[index].play();
			effects[index].mouseChildren = false;
			effects[index].mouseEnabled = false;
		}
		
		private function CreateEffect(effectNum:int):MovieClip 
		{
			switch (effectNum) 
			{
				case EMiniMapEffects.EggEffect:
					return new EggMoveEffect();
				case EMiniMapEffects.FriendEffect:
					return new SpotEffectGreen()
				case EMiniMapEffects.EnemyEffect:
					return new SpotEffectRed()
				case EMiniMapEffects.ChatEffect:
					return new SpotEffectBlue();
			}
			
			return null;
		} 
		
		public function UpdateMinimapEffect(index:int, posX:Number, posY:Number):void 
		{
			if (effects[index] == null) return;
			
			effects[index].x = posX* miniMapZone_mc.width;
			effects[index].y = posY* miniMapZone_mc.height;
		}
		
		public function ShowCTEUi(show:Boolean):void 
		{
			dragonval_mc.visible = show;
			dragonvalAdornIco_mc.visible = show;
			dragonvalDoctIco_mc.visible = show;
		}
		
		public function SetCTEAltarStatus(fraction:int, curHealth:int, maxHealth:int, damageType:int):void 
		{
			dragonval_mc.SetCTEAltarStatus(fraction, curHealth, maxHealth, damageType);
		}
		
		private function get miniMapPlace():String
		{
			return (miniMapZone_mc.mouseX/miniMapZone_mc.width).toString() + ' ' + (miniMapZone_mc.mouseY/miniMapZone_mc.height).toString();
		}
		
		public function set GameTime(value:int):void
		{
			timer_mc.GameTime = value;
		}
		
		public function DisablePingButton() : void
		{
			signalBtn.disable();
		}
		
		public function set HeroIsDead(isDead:Boolean):void
		{
			if (isHeroIsDead == isDead) return;
			
			isHeroIsDead = isDead;

			if (isHeroIsDead)
			{
				cameraBtn.disable();
				return;
			}
			else
				cameraBtn.enable();

			/*
			if (cameraBtn.IsChecked&&isDead)
			{
				isCameraWasLocked = lockCameraBtn;// cameraBtn.IsChecked;
				cameraBtn.SwitchOff();
				SendCameraLock(false);
				return;
			}
			
			if (isCameraWasLocked)
			{
				cameraBtn.SwitchOn();
				SendCameraLock(true);
			}
			
			if (!isHeroIsDead && waitingToSendProp != -1)
			{
				FSCommands.Send(FSCommands.CAMERA_MOUSECLICK, waitingToSendProp.toString());
				waitingToSendProp = -1;
			}
			
			isCameraWasLocked = false;
			*/
		}
		
		public function set CameraBtnStatus(isLocked:Boolean):void
		{
			if (lockCameraBtn == isLocked) return;

			//if (isHeroIsDead) return;			

			lockCameraBtn = isLocked;
			
			if (lockCameraBtn)
				cameraBtn.SwitchOn();
			else	
				cameraBtn.SwitchOff();

			SendCameraLock(lockCameraBtn);
		}
	}
}