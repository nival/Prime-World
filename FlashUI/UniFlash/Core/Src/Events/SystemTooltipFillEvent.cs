
namespace Flash
{
  public class SystemTooltipFillEvent : Event
  {
    public string Text { get; private set; }

    public SystemTooltipFillEvent( string text )
      : base( typeof( SystemTooltipFillEvent ).Name, true )
    {
      Text = text;
    }
  }
}
