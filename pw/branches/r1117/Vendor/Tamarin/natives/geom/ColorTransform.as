package flash.geom
{

    public class ColorTransform extends Object
    {
        public var redOffset:Number;
        public var greenMultiplier:Number;
        public var blueOffset:Number;
        public var alphaOffset:Number;
        public var redMultiplier:Number;
        public var blueMultiplier:Number;
        public var greenOffset:Number;
        public var alphaMultiplier:Number;

        public function ColorTransform(redMultiplier:Number = 1, greenMultiplier:Number = 1, blueMultiplier:Number = 1, alphaMultiplier:Number = 1, redOffset:Number = 0, greenOffset:Number = 0, blueOffset:Number = 0, alphaOffset:Number = 0)
        {
            this.redMultiplier = redMultiplier;
            this.greenMultiplier = greenMultiplier;
            this.blueMultiplier = blueMultiplier;
            this.alphaMultiplier = alphaMultiplier;
            this.redOffset = redOffset;
            this.greenOffset = greenOffset;
            this.blueOffset = blueOffset;
            this.alphaOffset = alphaOffset;
            return;
        }// end function

        public function get color() : uint
        {
            return this.redOffset << 16 | this.greenOffset << 8 | this.blueOffset;
        }// end function

        public function set color(newColor:uint) : void
        {
            var _loc_2:int = 0;
            this.blueMultiplier = 0;
            var _loc_2:* = _loc_2;
            this.greenMultiplier = _loc_2;
            this.redMultiplier = _loc_2;
            this.redOffset = newColor >> 16 & 255;
            this.greenOffset = newColor >> 8 & 255;
            this.blueOffset = newColor & 255;
            return;
        }// end function

        public function toString() : String
        {
            return "(redMultiplier=" + this.redMultiplier + ", greenMultiplier=" + this.greenMultiplier + ", blueMultiplier=" + this.blueMultiplier + ", alphaMultiplier=" + this.alphaMultiplier + ", redOffset=" + this.redOffset + ", greenOffset=" + this.greenOffset + ", blueOffset=" + this.blueOffset + ", alphaOffset=" + this.alphaOffset + ")";
        }// end function

        public function concat(second:ColorTransform) : void
        {
            this.alphaOffset = this.alphaOffset + this.alphaMultiplier * second.alphaOffset;
            this.alphaMultiplier = this.alphaMultiplier * second.alphaMultiplier;
            this.redOffset = this.redOffset + this.redMultiplier * second.redOffset;
            this.redMultiplier = this.redMultiplier * second.redMultiplier;
            this.greenOffset = this.greenOffset + this.greenMultiplier * second.greenOffset;
            this.greenMultiplier = this.greenMultiplier * second.greenMultiplier;
            this.blueOffset = this.blueOffset + this.blueMultiplier * second.blueOffset;
            this.blueMultiplier = this.blueMultiplier * second.blueMultiplier;
            return;
        }// end function

    }
}
