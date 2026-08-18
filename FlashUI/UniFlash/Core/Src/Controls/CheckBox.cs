namespace Flash.Controls
{
  public class CheckBox : ToggleButton
  {
    [Bind( "txt" )]
    protected readonly TextField _textField = new TextField();

    public CheckBox()
    {
      _textField.AutoWidth = true;
      _textField.MultiLine = false;
    }

    public virtual string Text
    {
      get { return _textField.Text; }
      set { _textField.Text = value; }
    }
  }
}
