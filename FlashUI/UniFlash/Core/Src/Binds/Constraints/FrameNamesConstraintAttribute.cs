using System;
using System.Collections.Generic;
using System.Linq;

namespace Flash
{
  [AttributeUsage( AttributeTargets.Field | AttributeTargets.Class )]
  public class FrameNamesConstraintAttribute : ConstraintAttribute
  {
    private readonly string[] _frameNames;

    public FrameNamesConstraintAttribute( params string[] frameNames )
    {
      _frameNames = frameNames;
    }

    private string _lastValidationError;
    public override string LastValidationError
    {
      get { return _lastValidationError; }
    }

    public override bool Validate( MovieClip target )
    {
      List<string> invalidFrames = new List<string>();

      foreach ( string name in _frameNames )
      {
        if ( target.GetFrameByName( name ) == -1 )
        {
          //Debug.Log( "### " + target.Name + " frame:" + name );
          invalidFrames.Add( name );
        }
      }

      if ( invalidFrames.Count > 0 )
      {
        ControlNode node = ( (IBindable)target ).ControlNode;
        String path = node.GetPath();

        _lastValidationError = "BIND WARNING: Node " + path + " don't has frames: " + string.Join( ",", invalidFrames.ToArray() ) + 
          " declared for class " + target.GetType().Name;

        return false;
      }

      return true;
    }

    public override string ToString()
    {
      return base.ToString() + " Frames: " + string.Join( ",", _frameNames.ToArray() );
    }
  }
}
