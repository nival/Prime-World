using UnityEngine;

namespace Flash.Controls
{
  class TextColorDisable
  {
    private readonly Color _textColor = new Color( 1, 1, 1 );
    private readonly Color _textOutlineColor;
    private readonly TextField _textField;

    public TextColorDisable( TextField textField )
    {
      _textField = textField;
      _textColor = textField.TextColor;
      _textOutlineColor = textField.OutlineColor;
    }

    public void Enable (bool isEnabled)
    {
      if ( isEnabled )
      {
        _textField.TextColor = _textColor;
        _textField.OutlineColor = _textOutlineColor;
        _textField.Alpha = 1;
      }
      else
      {
        _textField.TextColor = new Color( 0.6f, 0.6f, 0.6f );
        _textField.OutlineColor = new Color( 0.3f, 0.3f, 0.3f );
        _textField.Alpha = 0.8f;
      }
    }
  }
}
