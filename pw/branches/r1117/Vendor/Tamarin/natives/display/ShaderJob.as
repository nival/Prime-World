package flash.display
{
    import flash.events.*;

    [native(cls="ShaderJobClass", instance="ShaderJobObject", methods="auto")]
    public class ShaderJob extends EventDispatcher
    {

        public function ShaderJob(shader:Shader = null, target:Object = null, width:int = 0, height:int = 0)
        {
            if (shader)
            {
                this.shader = shader;
            }
            if (target)
            {
                this.target = target;
            }
            this.width = width;
            this.height = height;
            return;
        }// end function

        public native function start(waitForCompletion:Boolean = false) : void;

        public native function get shader() : Shader;

        public native function get width() : int;

        public native function get height() : int;

        public native function set target(s:Object) : void;

        public native function set shader(s:Shader) : void;

        public native function set width(v:int) : void;

        public native function get progress() : Number;

        public native function set height(v:int) : void;

        public native function get target() : Object;

        public native function cancel() : void;

    }
}
