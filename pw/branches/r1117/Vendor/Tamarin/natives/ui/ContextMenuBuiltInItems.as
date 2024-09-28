package flash.ui
{

    final public class ContextMenuBuiltInItems extends Object
    {
        public var loop:Boolean = true;
        public var print:Boolean = true;
        public var zoom:Boolean = true;
        public var play:Boolean = true;
        public var forwardAndBack:Boolean = true;
        public var rewind:Boolean = true;
        public var save:Boolean = true;
        public var quality:Boolean = true;

        public function ContextMenuBuiltInItems()
        {
            return;
        }// end function

        public function clone() : ContextMenuBuiltInItems
        {
            var _loc_1:* = new ContextMenuBuiltInItems();
            _loc_1.save = this.save;
            _loc_1.zoom = this.zoom;
            _loc_1.quality = this.quality;
            _loc_1.play = this.play;
            _loc_1.loop = this.loop;
            _loc_1.rewind = this.rewind;
            _loc_1.forwardAndBack = this.forwardAndBack;
            _loc_1.print = this.print;
            return _loc_1;
        }// end function

    }
}
