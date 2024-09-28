package flash.geom
{

    public class Rectangle extends Object
    {
        public var width:Number;
        public var height:Number;
        public var x:Number;
        public var y:Number;

        public function Rectangle(x:Number = 0, y:Number = 0, width:Number = 0, height:Number = 0)
        {
            this.x = x;
            this.y = y;
            this.width = width;
            this.height = height;
            return;
        }// end function

        public function containsPoint(point:Point) : Boolean
        {
            if (point.x >= this.x)
            {
            }
            if (point.x < this.x + this.width)
            {
            }
            if (point.y >= this.y)
            {
            }
            return point.y < this.y + this.height;
        }// end function

        public function get size() : Point
        {
            return new Point(this.width, this.height);
        }// end function

        public function set size(value:Point) : void
        {
            this.width = value.x;
            this.height = value.y;
            return;
        }// end function

        public function isEmpty() : Boolean
        {
            if (this.width > 0)
            {
            }
            return this.height <= 0;
        }// end function

        public function get left() : Number
        {
            return this.x;
        }// end function

        public function inflatePoint(point:Point) : void
        {
            this.x = this.x - point.x;
            this.width = this.width + 2 * point.x;
            this.y = this.y - point.y;
            this.height = this.height + 2 * point.y;
            return;
        }// end function

        public function setEmpty() : void
        {
            this.x = 0;
            this.y = 0;
            this.width = 0;
            this.height = 0;
            return;
        }// end function

        public function set left(value:Number) : void
        {
            this.width = this.width + (this.x - value);
            this.x = value;
            return;
        }// end function

        public function union(toUnion:Rectangle) : Rectangle
        {
            var _loc_2:Rectangle = null;
            if (this.isEmpty())
            {
                return toUnion.clone();
            }
            if (toUnion.isEmpty())
            {
                return this.clone();
            }
            _loc_2 = new Rectangle();
            _loc_2.x = Math.min(this.x, toUnion.x);
            _loc_2.y = Math.min(this.y, toUnion.y);
            _loc_2.width = Math.max(this.x + this.width, toUnion.x + toUnion.width) - _loc_2.x;
            _loc_2.height = Math.max(this.y + this.height, toUnion.y + toUnion.height) - _loc_2.y;
            return _loc_2;
        }// end function

        public function set right(value:Number) : void
        {
            this.width = value - this.x;
            return;
        }// end function

        public function offset(dx:Number, dy:Number) : void
        {
            this.x = this.x + dx;
            this.y = this.y + dy;
            return;
        }// end function

        public function get top() : Number
        {
            return this.y;
        }// end function

        public function set bottom(value:Number) : void
        {
            this.height = value - this.y;
            return;
        }// end function

        public function equals(toCompare:Rectangle) : Boolean
        {
            if (toCompare.x == this.x)
            {
            }
            if (toCompare.y == this.y)
            {
            }
            if (toCompare.width == this.width)
            {
            }
            return toCompare.height == this.height;
        }// end function

        public function intersection(toIntersect:Rectangle) : Rectangle
        {
            var _loc_2:* = new Rectangle();
            if (!this.isEmpty())
            {
                this.isEmpty();
            }
            if (toIntersect.isEmpty())
            {
                _loc_2.setEmpty();
                return _loc_2;
            }
            _loc_2.x = Math.max(this.x, toIntersect.x);
            _loc_2.y = Math.max(this.y, toIntersect.y);
            _loc_2.width = Math.min(this.x + this.width, toIntersect.x + toIntersect.width) - _loc_2.x;
            _loc_2.height = Math.min(this.y + this.height, toIntersect.y + toIntersect.height) - _loc_2.y;
            if (_loc_2.width > 0)
            {
            }
            if (_loc_2.height <= 0)
            {
                _loc_2.setEmpty();
            }
            return _loc_2;
        }// end function

        public function get right() : Number
        {
            return this.x + this.width;
        }// end function

        public function clone() : Rectangle
        {
            return new Rectangle(this.x, this.y, this.width, this.height);
        }// end function

        public function inflate(dx:Number, dy:Number) : void
        {
            this.x = this.x - dx;
            this.width = this.width + 2 * dx;
            this.y = this.y - dy;
            this.height = this.height + 2 * dy;
            return;
        }// end function

        public function set bottomRight(value:Point) : void
        {
            this.width = value.x - this.x;
            this.height = value.y - this.y;
            return;
        }// end function

        public function containsRect(rect:Rectangle) : Boolean
        {
            var _loc_2:* = rect.x + rect.width;
            var _loc_3:* = rect.y + rect.height;
            var _loc_4:* = this.x + this.width;
            var _loc_5:* = this.y + this.height;
            if (rect.x >= this.x)
            {
            }
            if (rect.x < _loc_4)
            {
            }
            if (rect.y >= this.y)
            {
            }
            if (rect.y < _loc_5)
            {
            }
            if (_loc_2 > this.x)
            {
            }
            if (_loc_2 <= _loc_4)
            {
            }
            if (_loc_3 > this.y)
            {
            }
            return _loc_3 <= _loc_5;
        }// end function

        public function set top(value:Number) : void
        {
            this.height = this.height + (this.y - value);
            this.y = value;
            return;
        }// end function

        public function get bottom() : Number
        {
            return this.y + this.height;
        }// end function

        public function toString() : String
        {
            return "(x=" + this.x + ", y=" + this.y + ", w=" + this.width + ", h=" + this.height + ")";
        }// end function

        public function contains(x:Number, y:Number) : Boolean
        {
            if (x >= this.x)
            {
            }
            if (x < this.x + this.width)
            {
            }
            if (y >= this.y)
            {
            }
            return y < this.y + this.height;
        }// end function

        public function get bottomRight() : Point
        {
            return new Point(this.right, this.bottom);
        }// end function

        public function intersects(toIntersect:Rectangle) : Boolean
        {
            if (!this.isEmpty())
            {
                this.isEmpty();
            }
            if (toIntersect.isEmpty())
            {
                return false;
            }
            var _loc_2:* = Math.max(this.x, toIntersect.x);
            var _loc_3:* = Math.max(this.y, toIntersect.y);
            var _loc_4:* = Math.min(this.x + this.width, toIntersect.x + toIntersect.width) - _loc_2;
            var _loc_5:* = Math.min(this.y + this.height, toIntersect.y + toIntersect.height) - _loc_3;
            if (_loc_4 > 0)
            {
            }
            if (_loc_5 <= 0)
            {
                return false;
            }
            return true;
        }// end function

        public function get topLeft() : Point
        {
            return new Point(this.x, this.y);
        }// end function

        public function offsetPoint(point:Point) : void
        {
            this.x = this.x + point.x;
            this.y = this.y + point.y;
            return;
        }// end function

        public function set topLeft(value:Point) : void
        {
            this.width = this.width + (this.x - value.x);
            this.height = this.height + (this.y - value.y);
            this.x = value.x;
            this.y = value.y;
            return;
        }// end function

    }
}
