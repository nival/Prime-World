using System;
using DBTypes;
using System.Collections.Generic;
using libdb.UndoRedo;

namespace EditorPlugins.Editors.AnimGraph
{
  public class NormalNode : Node
  {
    private readonly AnGrFormula startPar = null;
    private readonly AnGrFormula stopPar = null;
    private readonly AnGrFormula speed = null;
    private string sequenceName = string.Empty;
    private OwnedReportingList<Marker, NormalNode> markers;
    private List<float> markersVirtPars = null;
    private List<float> linksMinFrom = null;
    private List<float> linksMaxFrom = null;

    protected NormalNode()
    {
      InitMarkers();
    }

    public NormalNode(AnimGraphContext _context, AnGrMacronode _agNode)
      : base (_context, _agNode)
    {
      // Добавим сиквенсы
      startPar = agNode.startPar;
      stopPar = agNode.stopPar;
      speed = agNode.speed;
      sequenceName = agNode.sequenceName;

      InitMarkers();
    }

    [AnimationSelected]
    public virtual string Animation
    {
      get { return sequenceName; }
      set
      {
        if ( sequenceName != value )
        {
          animInfo = FindAnimInfo(value);
        }
        sequenceName = value;
        agNode.sequenceName = sequenceName;
        UpdatedMinorSeq();
      }
    }

    private float GetMeasureCoeff()
    {
      if ( AnimGraphContext.MeasureInFrames )
      {
        //Выводим в фреймах
        return (float)FramesCount;
      }
      else
      {
        //Выводим в секундах
        return (float)( FramesCount / AnimGraphContext.FramesPerSecond );
      }
    }

    public override float In
    {
      get
      {
        return (float)Math.Round(startPar.value * GetMeasureCoeff(), 3);
      }
      set
      {
        SaveMarkersVirtParsAndLinks();
        float scaledValue = value / GetMeasureCoeff();
        startPar.value = Math.Max( 0.0f, Math.Min( scaledValue, 1.0f ) );
        stopPar.value = Math.Max(startPar.value, Math.Min(stopPar.value, 1.0f));
        UpdatedMinorSeq();
        ResotreMarkersVirtParsAndLinks();
      }
    }

    public override float Out
    {
      get
      {
        return (float)Math.Round(stopPar.value * GetMeasureCoeff(), 3);
      }
      set
      {
        SaveMarkersVirtParsAndLinks();
        float scaledValue = value / GetMeasureCoeff();
        stopPar.value = Math.Max(startPar.value, Math.Min(scaledValue, 1.0f));
        UpdatedMinorSeq();
        ResotreMarkersVirtParsAndLinks();
      }
    }

    public float Speed 
    {
      get { return speed.value; }
      set { speed.value = value; }
    }

    #region Markers

    private void InitMarkers()
    {
      markers = new OwnedReportingList<Marker, NormalNode>( this );

      if( agNode == null )
        return;

      foreach( AnGrMarker nativeMarker in agNode.markers )
      {
        markers.Add( new Marker( nativeMarker ) );
      }

      markers.OnItemInserted += OnMarkerInserted;
      markers.OnItemDeleting += OnMarkerDeleting;
      markers.OnListCleared += OnMarkersCleared;
    }

    private void OnMarkerDeleting( int _pos )
    {
      agNode.markers.RemoveAt( _pos );
    }

    private void OnMarkerInserted( int _pos )
    {
      agNode.markers.Insert( _pos, markers[_pos].NativeMarker );
      markers[_pos] = new Marker( agNode.markers[_pos] );
    }

    private void OnMarkersCleared()
    {
      agNode.markers.Clear();
    }

    public ReportingList<Marker> Markers
    {
      get { return markers; }
    }

    #endregion

    private void UpdatedMinorSeq()
    {
      Context.Controller.SetSequenceInfo(0, 0, startPar, stopPar, speed, sequenceName);
    }

    protected override AnGrFlMultiTransaction InitAgLink(Node _toNode)
    {
      var result = new AnGrFlMultiTransaction
      {
        targetNode = _toNode.Name,
        probability = 0
      };

      result.parameters.fromMin.value = 0;
      result.parameters.fromMax.value = 1;
      result.parameters.duration = 1.0f / 10.0f;

      UpdatedMajor();

      return result;
    }

    private void SaveMarkersVirtParsAndLinks()
    {
      markersVirtPars = new List<float>( markers.Count );
      for ( int i = 0; i < markers.Count; i++ )
      {
        markersVirtPars.Add( markers[i].VirtPar );
      }
      linksMinFrom = new List<float>( Links.Count );
      linksMaxFrom = new List<float>( Links.Count );
      foreach ( Link l in Links )
      {
        linksMinFrom.Add( l.MinFrom );
        linksMaxFrom.Add( l.MaxFrom );
      }
    }

    private void ResotreMarkersVirtParsAndLinks()
    {
      using ( UndoRedoTransaction trans = new UndoRedoTransaction( "Resotre Markers VirtPars" ) )
      {
        for ( int i = 0; i < markers.Count; i++ )
        {
          markers[i].VirtPar = markersVirtPars[i];
        }

        for ( int i = 0; i < linksMinFrom.Count; i++ )
        {
          Links[i].MinFrom = linksMinFrom[i];
          Links[i].MaxFrom = linksMaxFrom[i];
        }

        trans.Commit();
      }
    }

  }
}
