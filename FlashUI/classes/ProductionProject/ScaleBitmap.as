package {
	import flash.display.Bitmap;
	import flash.display.BitmapData;
	import flash.geom.Matrix;
	import flash.geom.Rectangle;	

	public class ScaleBitmap extends Bitmap {

		protected var _originalBitmap : BitmapData;
		protected var _scale9Grid : Rectangle = null;
		public var __internalUsage__ : Boolean = false;

		
		function ScaleBitmap(bmpData : BitmapData = null, pixelSnapping : String = "auto", smoothing : Boolean = false) {
			
			// super constructor
			super(bmpData, pixelSnapping, smoothing);

			if ( __internalUsage__ )
				return;
		
			// original bitmap
			_originalBitmap = bmpData.clone();
		}

		override public function set bitmapData(bmpData : BitmapData) : void 
		{
			if ( __internalUsage__ )
			{
				super.bitmapData = bmpData;
			}
			else
			{
				_originalBitmap = bmpData.clone();
				
				if (_scale9Grid != null) {
					if (!validGrid(_scale9Grid)) {
						_scale9Grid = null;
					}
					setSize(bmpData.width, bmpData.height);
				} else {
					assignBitmapData(_originalBitmap.clone());
				}
			}
		} 

		override public function set width(w : Number) : void {
			if ( __internalUsage__ )
			{
				super.width = w;
			}
			else if (w != width) {
				setSize(w, height);
			}
		}

		override public function set height(h : Number) : void {
			if ( __internalUsage__ )
			{
				super.height = h;
			}
			else if (h != height) {
				setSize(width, h);
			}
		}

		override public function set scale9Grid(r : Rectangle) : void {
			if ( __internalUsage__ )
			{
				super.scale9Grid = r;
			}
			else
			{
				// Check if the given grid is different from the current one
				if ((_scale9Grid == null && r != null) || (_scale9Grid != null && !_scale9Grid.equals(r))) {
					if (r == null) {
						// If deleting scalee9Grid, restore the original bitmap
						// then resize it (streched) to the previously set dimensions
						var currentWidth : Number = width;
						var currentHeight : Number = height;
						_scale9Grid = null;
						assignBitmapData(_originalBitmap.clone());
						setSize(currentWidth, currentHeight);
					} else {
						if (!validGrid(r)) {
							throw (new Error("#001 - The _scale9Grid does not match the original BitmapData"));
							return;
						}
						
						_scale9Grid = r.clone();
						resizeBitmap(width, height);
						scaleX = 1;
						scaleY = 1;
					}
				}
			}
		}

		/**
		 * assignBitmapData
		 * Update the effective bitmapData
		 */
		private function assignBitmapData(bmp : BitmapData) : void {
			super.bitmapData.dispose();
			super.bitmapData = bmp;
		}

		private function validGrid(r : Rectangle) : Boolean {
			return r.right <= _originalBitmap.width && r.bottom <= _originalBitmap.height;
		}

		/**
		 * get scale9Grid
		 */
		override public function get scale9Grid() : Rectangle {
			if ( __internalUsage__ )
			{
				return super.scale9Grid;
			}
			else
			{
				return _scale9Grid;
			}
		}

		
		/**
		 * setSize
		 */
		public function setSize(w : Number, h : Number) : void {
			
			if ( __internalUsage__ )
			{
				if ( bitmapData != null && scale9Grid != null )
				{
					w = Math.max(w, bitmapData.width - scale9Grid.width);
					h = Math.max(h, bitmapData.height - scale9Grid.height);
				}
				
				super.width = w;
				super.height = h;
			}
			else
			{
				if (_scale9Grid == null) {
					super.width = w;
					super.height = h;
				} else {
					w = Math.max(w, _originalBitmap.width - _scale9Grid.width);
					h = Math.max(h, _originalBitmap.height - _scale9Grid.height);
					resizeBitmap(w, h);
				}
			}
		}

		// ------------------------------------------------
		//
		// ---o protected methods
		//
		// ------------------------------------------------
		
		/**
		 * resize bitmap
		 */
		protected function resizeBitmap(w : Number, h : Number) : void {
			
			if ( __internalUsage__ )
			{
				
			}
			else
			{
				var bmpData : BitmapData = new BitmapData(w, h, true, 0x00000000);
				
				var rows : Array = [0, _scale9Grid.top, _scale9Grid.bottom, _originalBitmap.height];
				var cols : Array = [0, _scale9Grid.left, _scale9Grid.right, _originalBitmap.width];
				
				var dRows : Array = [0, _scale9Grid.top, h - (_originalBitmap.height - _scale9Grid.bottom), h];
				var dCols : Array = [0, _scale9Grid.left, w - (_originalBitmap.width - _scale9Grid.right), w];
	
				var origin : Rectangle;
				var draw : Rectangle;
				var mat : Matrix = new Matrix();
	
				
				for (var cx : int = 0;cx < 3; cx++) {
					for (var cy : int = 0 ;cy < 3; cy++) {
						origin = new Rectangle(cols[cx], rows[cy], cols[cx + 1] - cols[cx], rows[cy + 1] - rows[cy]);
						draw = new Rectangle(dCols[cx], dRows[cy], dCols[cx + 1] - dCols[cx], dRows[cy + 1] - dRows[cy]);
						mat.identity();
						mat.a = draw.width / origin.width;
						mat.d = draw.height / origin.height;
						mat.tx = draw.x - origin.x * mat.a;
						mat.ty = draw.y - origin.y * mat.d;
						bmpData.draw(_originalBitmap, mat, null, null, draw, smoothing);
					}
				}
				assignBitmapData(bmpData);
			}
		}
	}
}