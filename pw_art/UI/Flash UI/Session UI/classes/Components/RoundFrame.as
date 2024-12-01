package Components
{
	import flash.display.Sprite;
	import flash.display.Shape;

	public class RoundFrame extends Sprite
	{
		private var radius:Number = 50;

		private var lines:Number = 3;
		private var tickness:Number = 1;
		private var back:Boolean = true;
		private var backColor:Number = 0x000000;
		private var backAlpha:Number = 0.5;

		private var color1:Number = 0x5b5c3c;
		private var color2:Number = 0x9a956c;
		private var color3:Number = 0x363525;
		private var color4:Number = 0x8a7c57;
		private var color5:Number = 0xb6976e;

		private var colors:Array;
		private var roundsSp:Sprite;

		public function RoundFrame()
		{
			colors = [color1,color2,color3,color4,color5];

			roundsSp = new Sprite();
			this.addChild(roundsSp);
			
			this.mouseEnabled = false;
			this.mouseChildren = false;
			configUI();
			this.removeChildAt(0);
		}

		protected function configUI():void
		{
			var r:Number = rotation;
			rotation = 0;
			var w:Number = super.width;
			var h:Number = super.height;
			super.scaleX = super.scaleY = 1;
			setSize(w,h);
			rotation = r;
		}

		private function getRoundFrame()
		{
			this.removeChild(roundsSp);
			roundsSp = null;

			roundsSp = new Sprite();
			this.addChild(roundsSp);

			if (back)
			{
				var backSh:Shape = new Shape();
				backSh.graphics.beginFill(backColor,backAlpha);
				backSh.graphics.drawCircle(0,0,radius);
				backSh.graphics.endFill();
				backSh.x = radius + tickness / 2;
				backSh.y = radius + tickness / 2;

				roundsSp.addChild(backSh);
			}

			for (var i:int=0; i<lines; i++)
			{
				var roundShape:Shape = createCircle(colors[i],tickness,radius - (i*tickness),back,backColor,backAlpha);
				roundShape.x = (roundShape.width/2)+(i*tickness);
				roundShape.y = (roundShape.height/2)+(i*tickness);
				roundsSp.addChild(roundShape);
			}
		}

		private function createCircle(color:Number,tickness:Number,radius:Number,back:Boolean,backColor:Number,backAlpha:Number):Shape
		{

			var round:Shape = new Shape();
			round.graphics.lineStyle(tickness,color);
			round.graphics.drawCircle(0,0,radius);
			return (round);

		}
		public function setSize(_width:Number, _height:Number):void
		{
			radius = _width / 2;
			getRoundFrame();
		}

		public function set Lines(_lines:Number)
		{
			lines = _lines;
		}
		public function set Tickness(_tickness:Number)
		{
			tickness = _tickness;
			getRoundFrame();
		}
		public function set Back(_back:Boolean)
		{
			back = _back;
		}
		public function set BackColor(_backColor:Number)
		{
			backColor = _backColor;
		}
		public function set BackAlpha(_backAlpha:Number)
		{
			backAlpha = _backAlpha;
		}
		public function set Color1(_color1:Number)
		{
			color1 = _color1;
			colors = [color1,color2,color3,color4,color5];
		}
		public function set Color2(_color2:Number)
		{
			color2 = _color2;
			colors = [color1,color2,color3,color4,color5];
		}
		public function set Color3(_color3:Number)
		{
			color3 = _color3;
			colors = [color1,color2,color3,color4,color5];
		}
		public function set Color4(_color4:Number)
		{
			color4 = _color4;
			colors = [color1,color2,color3,color4,color5];
		}
		public function set Color5(_color5:Number)
		{
			color5 = _color5;
			colors = [color1,color2,color3,color4,color5];
		}

		public function get BackAlpha():Number
		{
			return (backAlpha);
		}
		public function get BackColor():Number
		{
			return (backColor);
		}
		public function get Back():Boolean
		{
			return (back);
		}
		public function get Tickness():Number
		{
			return (tickness);
		}
		public function get Lines():Number
		{
			return (lines);
		}
		public function get Color1():Number
		{
			return (color1);
		}
		public function get Color2():Number
		{
			return (color2);
		}

		public function get Color3():Number
		{
			return (color3);
		}

		public function get Color4():Number
		{
			return (color4);
		}

		public function get Color5():Number
		{
			return (color5);
		}
	}
}