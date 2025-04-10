package flash.display
{

    final public class Scene extends Object
    {
        private var _name:String;
        private var _numFrames:int;
        private var _labels:Array;

        public function Scene(name:String, labels:Array, numFrames:int)
        {
            this._name = name;
            this._labels = labels;
            this._numFrames = numFrames;
            return;
        }// end function

        public function get numFrames() : int
        {
            return this._numFrames;
        }// end function

        public function get name() : String
        {
            return this._name;
        }// end function

        public function get labels() : Array
        {
            return this._labels;
        }// end function

    }
}
