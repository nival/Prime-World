package flash.display
{
    import flash.geom.*;

    final public class GraphicsShaderFill extends Object implements IGraphicsFill, IGraphicsData
    {
        public var matrix:Matrix;
        public var shader:Shader;

        public function GraphicsShaderFill(shader:Shader = null, matrix:Matrix = null)
        {
            this.shader = shader;
            this.matrix = matrix;
            return;
        }// end function

    }
}
