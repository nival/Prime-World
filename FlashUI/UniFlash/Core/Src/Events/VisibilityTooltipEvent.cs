
namespace Flash.Controls
{
  public enum TooltipPosition
  {
    Default,
    CentrateHorisontal,  // центрирует по горизонтали, т.е. будет над элементом по центру
    CentrateVerticle, // центрирует по вертикали, т.е. будет сбоку по центру.
    DownCenterTooltip // ставит тултип вниз, по центру.
  }

  public class VisibilityTooltipEvent : Event
  {
    public TooltipPosition CentrateTooltip { get; private set; }
    public bool Show { get; private set; }
    public float Delay { get; private set; }

    public InteractiveObject Target { get; private set; }

    public UnityEngine.RectTransform Target2 { get; private set; }
    public UnityEngine.Canvas Target2Canvas { get; private set; }

    public VisibilityTooltipEvent( bool show, InteractiveObject target, TooltipPosition centrateTooltip )
      : base( typeof( VisibilityTooltipEvent ).Name, true )
    {
      Show = show;
      Target = target;
      CentrateTooltip = centrateTooltip;
      Delay = 0f;
    }

    public VisibilityTooltipEvent( bool show, InteractiveObject target )
      : this( show, target, TooltipPosition.Default )
    {

    }

    public VisibilityTooltipEvent(bool show, UnityEngine.RectTransform target, UnityEngine.Canvas canvas, TooltipPosition centrateTooltip, float delay)
      : base(typeof(VisibilityTooltipEvent).Name, true)
    {
      Show = show;
      Target2 = target;
      Target2Canvas = canvas;
      CentrateTooltip = centrateTooltip;
      Delay = delay;
    }

    public VisibilityTooltipEvent(bool show, UnityEngine.RectTransform target, UnityEngine.Canvas canvas)
      : this(show, target, canvas, TooltipPosition.Default, 0f)
    {

    }
  }
}
