package flash.geom
{

    public class Matrix extends Object
    {
        public var a:Number;
        public var c:Number;
        public var ty:Number;
        public var b:Number;
        public var d:Number;
        public var tx:Number;

        public function Matrix(a:Number = 1, b:Number = 0, c:Number = 0, d:Number = 1, tx:Number = 0, ty:Number = 0)
        {
            this.a = a;
            this.b = b;
            this.c = c;
            this.d = d;
            this.tx = tx;
            this.ty = ty;
            return;
        }// end function

        public function createBox(scaleX:Number, scaleY:Number, rotation:Number = 0, tx:Number = 0, ty:Number = 0) : void
        {
            this.identity();
            this.rotate(rotation);
            this.scale(scaleX, scaleY);
            this.tx = tx;
            this.ty = ty;
            return;
        }// end function

        public function toString() : String
        {
            return "(a=" + this.a + ", b=" + this.b + ", c=" + this.c + ", d=" + this.d + ", tx=" + this.tx + ", ty=" + this.ty + ")";
        }// end function

        public function translate(dx:Number, dy:Number) : void
        {
            this.tx = this.tx + dx;
            this.ty = this.ty + dy;
            return;
        }// end function

        public function scale(sx:Number, sy:Number) : void
        {
            var _loc_3:* = new Matrix(sx, 0, 0, sy, 0, 0);
            this.concat(_loc_3);
            return;
        }// end function

        public function concat(m:Matrix) : void
        {
            var _loc_2:Number = NaN;
            var _loc_3:Number = NaN;
            var _loc_4:Number = NaN;
            var _loc_5:Number = NaN;
            var _loc_6:Number = NaN;
            var _loc_7:Number = NaN;
            _loc_2 = this.a * m.a;
            _loc_5 = this.d * m.d;
            var _loc_8:Number = 0;
            _loc_4 = 0;
            _loc_3 = _loc_8;
            _loc_6 = this.tx * m.a + m.tx;
            _loc_7 = this.ty * m.d + m.ty;
            if (this.b == 0)
            {
            }
            if (this.c == 0)
            {
            }
            if (m.b == 0)
            {
            }
            if (m.c != 0)
            {
                _loc_2 = _loc_2 + this.b * m.c;
                _loc_5 = _loc_5 + this.c * m.b;
                _loc_3 = _loc_3 + (this.a * m.b + this.b * m.d);
                _loc_4 = _loc_4 + (this.c * m.a + this.d * m.c);
                _loc_6 = _loc_6 + this.ty * m.c;
                _loc_7 = _loc_7 + this.tx * m.b;
            }
            this.a = _loc_2;
            this.b = _loc_3;
            this.c = _loc_4;
            this.d = _loc_5;
            this.tx = _loc_6;
            this.ty = _loc_7;
            return;
        }// end function

        public function invert() : void
        {
            var _loc_1:Number = NaN;
            var _loc_2:Number = NaN;
            var _loc_3:Number = NaN;
            var _loc_4:Number = NaN;
            var _loc_5:Number = NaN;
            var _loc_6:Point = null;
            if (this.b == 0)
            {
            }
            if (this.c == 0)
            {
                this.a = 1 / this.a;
                this.d = 1 / this.d;
                var _loc_7:Number = 0;
                this.c = 0;
                this.b = _loc_7;
                this.tx = (-this.a) * this.tx;
                this.ty = (-this.d) * this.ty;
            }
            else
            {
                _loc_1 = this.a;
                _loc_2 = this.b;
                _loc_3 = this.c;
                _loc_4 = this.d;
                _loc_5 = _loc_1 * _loc_4 - _loc_2 * _loc_3;
                if (_loc_5 == 0)
                {
                    this.identity();
                    return;
                }
                _loc_5 = 1 / _loc_5;
                this.a = _loc_4 * _loc_5;
                this.b = (-_loc_2) * _loc_5;
                this.c = (-_loc_3) * _loc_5;
                this.d = _loc_1 * _loc_5;
                _loc_6 = this.deltaTransformPoint(new Point(this.tx, this.ty));
                this.tx = -_loc_6.x;
                this.ty = -_loc_6.y;
            }
            return;
        }// end function

        public function transformPoint(point:Point) : Point
        {
            return new Point(this.a * point.x + this.c * point.y + this.tx, this.d * point.y + this.b * point.x + this.ty);
        }// end function

        public function rotate(angle:Number) : void
        {
            var _loc_2:* = Math.cos(angle);
            var _loc_3:* = Math.sin(angle);
            var _loc_4:* = new Matrix(_loc_2, _loc_3, -_loc_3, _loc_2, 0, 0);
            this.concat(_loc_4);
            return;
        }// end function

        public function deltaTransformPoint(point:Point) : Point
        {
            return new Point(this.a * point.x + this.c * point.y, this.d * point.y + this.b * point.x);
        }// end function

        public function clone() : Matrix
        {
            return new Matrix(this.a, this.b, this.c, this.d, this.tx, this.ty);
        }// end function

        public function identity() : void
        {
            var _loc_1:int = 1;
            this.d = 1;
            this.a = _loc_1;
            var _loc_2:Number = 0;
            this.c = 0;
            this.b = _loc_2;
            var _loc_3:Number = 0;
            this.ty = 0;
            this.tx = _loc_3;
            return;
        }// end function

        public function createGradientBox(width:Number, height:Number, rotation:Number = 0, tx:Number = 0, ty:Number = 0) : void
        {
            this.createBox(width / 1638.4, height / 1638.4, rotation, tx + width / 2, ty + height / 2);
            return;
        }// end function

    }
}
