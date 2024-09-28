using System;
using System.ComponentModel;
using DBTypes;
using libdb.DB;
using libdb.Diagnostics;

namespace EditorPlugins.Editors.AnimGraph
{
  [IndexField( "Name" )]
  public class Marker : IOwnedListElement<NormalNode>
  {
    [Browsable(false)]
    public AnGrMarker NativeMarker { get; private set; }

    [Browsable( false ), HideInOutliner]
    public NormalNode Owner { get; set; }

    [Description( "Name of the Marker" )]
    public string Name 
    {
      get { return NativeMarker.name; }
      set { NativeMarker.name = value; }
    }

    [Description( "Virtual parameter of the Marker: in [0..1]" )]
    public float VirtPar 
    {
      get
      {
        Log.Assert( Owner != null, "You must set Owner before using VirtPar property" );
        return GetPartAbsolute( NativeMarker.virtPar );
      }
      set
      {
        Log.Assert( Owner != null, "You must set Owner before using VirtPar property" );

        if ( Owner != null && value <= Owner.Out && value >= Owner.In )
        {
          float virtPart = ( value - Owner.In ) / ( Owner.Out - Owner.In );
          NativeMarker.virtPar = virtPart;
        }
      }
    }

    public Marker()
    {
      NativeMarker = new AnGrMarker();
    }

    public Marker( AnGrMarker _marker )
    {
      NativeMarker = _marker;
    }

    private float GetPartAbsolute( float _virtPart )
    {
      if( Owner == null )
        return -1;

      return (float)Math.Round( _virtPart * ( Owner.Out - Owner.In ) + Owner.In, 3 );
    }
  }
}
