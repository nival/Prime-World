using FlashView.Controls;

namespace Flash.Controls
{
  public class ToggleTextButton : ToggleButton
  {
    [Bind("txt")] protected readonly TextField TextField;

    private float _startTextY;
    private float _startTextH;

    public bool AutopositionTextVertically { get; set; }

    public ToggleTextButton(): this(false) {}

    public ToggleTextButton(bool trimmed)
    {
      if (trimmed)
      {
        TextField = new TrimmedTooltipText();
        var textField = (TrimmedTooltipText) TextField;
        MouseOver += (sender, @event) => textField.ShowTooltip();
        MouseOut += (sender, @event) => textField.HideTooltip();
      }
      else
      {
        TextField = new TextField();
      }
    }

    public TextAlignment TextAlignment
    {
      get { return TextField.Align; }
      set { TextField.Align = value; }
    }

    protected override void Init()
    {
      base.Init();

      _startTextY = TextField.Y;
      _startTextH = TextField.Height;

      //TextField.ShowBounds = true;
    }

    public virtual string Text
    {
      get { return TextField.Text; }
      set 
      { 
        TextField.Text = value; 

        if (AutopositionTextVertically && TextField.Height > _startTextH )
        {
          TextField.Y = _startTextY - (TextField.Height - _startTextH)/2;
        }
        else
        {
          TextField.Y = _startTextY;
        }
      }
    }

    public void InitTextField()
    {
      TextField.TrimOverflow = true;
      TextField.TrimOverflowLength = 0;
      TextField.MultiLine = false;
    }

    public void InitTextField(bool multiline)
    {
      TextField.TrimOverflow = true;
      TextField.TrimOverflowLength = 0;
      TextField.MultiLine = multiline;
    }
  }
}
