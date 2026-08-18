using Unity.Components.SoundsManager;
using UnityEngine;

namespace Flash.Controls
{
  public class TextButton : Button
  {
    [Bind( "txt" )]
    protected readonly TextField _textField = new TextField();


    private TextColorDisable _setText;

    protected override void Init()
    {
      base.Init();

      _setText = new TextColorDisable( _textField );

      ClickSound = Sound.Click;
      //_textField.Align = TextAlignment.MiddleCenter;
      _textField.MultiLine = false;
      //Can be removed after PF-48094
      _textField.Y *= Scale.y;
    }

    public virtual string Text
    {
      get { return _textField.Text; }
      set { _textField.Text = value; }
    }

    public virtual string FormatedText
    {
      set 
      { 
        _textField.Text = string.Empty;
        _textField.SetFormatedText(value);
      }
    }

    public override bool Enabled
    {
      get { return base.Enabled; }
      set
      {
        base.Enabled = value;
        
        _setText.Enable(value);

      }
    }

  }
}
