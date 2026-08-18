using System;

namespace Flash
{
  [AttributeUsage( AttributeTargets.Field | AttributeTargets.Class )]
  public class FramesCountConstraintAttribute : ConstraintAttribute
  {
    private readonly int _framesCount;
    public int FramesCount
    {
      get { return _framesCount; }
    }

    private string _lastValidationError;
    public override string LastValidationError
    {
      get { return _lastValidationError; }
    }

    public FramesCountConstraintAttribute( int framesCount )
    {
      _framesCount = framesCount;
    }
    public override bool Validate( MovieClip target )
    {
      if ( target.TotalFrames < _framesCount )
      {
        ControlNode node = ( (IBindable)target ).ControlNode;
        String path = node.GetPath();

        _lastValidationError = "BIND WARNING: Node " + path + " has less frames count, " + _framesCount +
                               " declared for class " + target.GetType().Name + ", " + target.TotalFrames + " exist !";
        return false;
      }
      return true;
    }
    public override string ToString()
    {
      return base.ToString() + " FramesCount " + _framesCount;
    }
  }
}
