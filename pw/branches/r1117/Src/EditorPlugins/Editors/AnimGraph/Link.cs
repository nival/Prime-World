using System;
using System.ComponentModel;
using DBTypes;
using libdb.DB;

namespace EditorPlugins.Editors.AnimGraph
{
  [IndexField("NameForIndex")]
  public class Link : INotifyPropertyChanged
  {
    [Browsable(false), HideInOutliner]
    public AnimGraphContext Context { get; set; }

    [Browsable(false), HideInOutliner]
    public AnGrFlMultiTransaction AgLink { get; private set; }

    [Browsable(false)]
    public string NameForIndex { get { return string.Format("{0}->{1}", FromNode.Name, ToNode.Name); } }

    [Browsable(false), HideInOutliner]
    public Node FromNode { get; private set; }

    [Browsable(false), HideInOutliner]
    public Node ToNode { get; private set; }

    [Browsable(false)]
    public int IndexFrom { get { return FromNode.AnGrNodeIndex; } }

    [Browsable(false)]
    public int IndexTo { get { return ToNode.AnGrNodeIndex; } }

    /// <summary>
    /// Конструктор создает обертку вокруг переданного линка(aglink), либо создает новый, если aglink==null
    /// </summary>
    public Link(AnimGraphContext _context, AnGrFlMultiTransaction _agLink, Node _fromNode, Node _toNode)
    {
      if (_fromNode == null || _toNode == null)
        throw new ArgumentException(string.Format("Can't create {0} with null passed to constructor in _fromNode or _toNode.", GetType()));

      Context = _context;
      FromNode = _fromNode;
      ToNode = _toNode;
      AgLink = _agLink;
    }

    private AnGrFlTransaction AgLinkPart
    {
      get { return AgLink.parameters; }
    }

    public EAnGrTransactionUpdate Blending
    {
      get { return AgLinkPart.blending; }
      set
      {
        AgLinkPart.blending = value;
        UpdatedMinorPart();
        NotifyPropertyChanged("Blending");
      }
    }

    public float GetMinFrom()
    {
      return AgLinkPart.fromMin.value;
    }

    public void SetMinFrom( float val )
    {
      AgLinkPart.fromMin.value = val;
    }

    public float GetMaxFrom()
    {
      return AgLinkPart.fromMax.value;
    }

    public void SetMaxFrom( float val )
    {
      AgLinkPart.fromMax.value = val;
    }

    public float MinFrom
    {
      get
      {
        if( InEqualsOut() )
          return FromNode.In;

        return GetPartAbsolute( AgLinkPart.fromMin.value );
      }
      set
      {
        if ( value > FromNode.Out )
          value = FromNode.Out;
        else if ( value < FromNode.In )
          value = FromNode.In;

        float virtPart = 0.0f;

        if( InNotEqualsOut() )
        {
          virtPart = ( value - FromNode.In ) / ( FromNode.Out - FromNode.In );
        }

        AgLinkPart.fromMin.value = virtPart;
        AgLinkPart.fromMax.value = Math.Max( AgLinkPart.fromMax.value, AgLinkPart.fromMin.value );

        UpdatedMinorPart();
        NotifyPropertyChanged("MinFrom");
      }
    }

    public float MaxFrom
    {
      get
      {
        if( InEqualsOut() )
          return FromNode.Out;

        return GetPartAbsolute( AgLinkPart.fromMax.value );
      }
      set
      {
        if ( value > FromNode.Out )
          value = FromNode.Out;
        else if ( value < FromNode.In )
          value = FromNode.In;

        float virtPart = 1.0f;

        if( InNotEqualsOut() )
        {
          virtPart = ( value - FromNode.In ) / ( FromNode.Out - FromNode.In );
        }
        
        AgLinkPart.fromMax.value = virtPart;

        UpdatedMinorPart();
        NotifyPropertyChanged("MaxFrom");
      }
    }

    public float Duration
    {
      get
      {
				return AnimGraphContext.MeasureInFrames
                ? (float)Math.Round( AgLinkPart.duration * AnimGraphContext.FramesPerSecond )
                : AgLinkPart.duration;
      }
      set
      {
				AgLinkPart.duration = (float)( value / ( AnimGraphContext.MeasureInFrames ? AnimGraphContext.FramesPerSecond : 1.0 ) );
        UpdatedMinorPart();
        NotifyPropertyChanged("Duration");
      }
    }

    private void UpdatedMinorPart()
    {
      if (Context != null)
      {
        Context.Controller.SetFlTransactionsInfo(IndexFrom, IndexTo, 0, AgLinkPart);       
      }
    }

    private float GetPartAbsolute( float _virtPart )
    {
      return (float)Math.Round( _virtPart * ( FromNode.Out - FromNode.In ) + FromNode.In, 3 );
    }

    #region In Out Equality
    
    /// <summary>
    ///Значения параметров In и Out равны
    /// </summary>
    /// <returns></returns>
    private bool InEqualsOut()
    {
      return Math.Abs( FromNode.Out - FromNode.In ) < 1.0e-3f;
    }

    /// <summary>
    ///Значения параметров In и Out не равны
    /// </summary>
    /// <returns></returns>
    private bool InNotEqualsOut()
    {
      return Math.Abs( FromNode.Out - FromNode.In ) >= 1.0e-3f;
    }

    #endregion

    #region INotifyPropertyChanged Members

    public event PropertyChangedEventHandler PropertyChanged;

    private void NotifyPropertyChanged(String _info)
    {
      if (PropertyChanged != null)
      {
        PropertyChanged(this, new PropertyChangedEventArgs(_info));
      }
    }

    #endregion
  }
}
