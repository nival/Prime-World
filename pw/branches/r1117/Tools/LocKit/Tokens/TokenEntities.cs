using System.Collections.Generic;
using System.Text;

namespace LocKit.Tokens
{
  /// <summary>
  /// Базовый класс для всех токенов.
  /// </summary>
  public abstract class Token
  {
    public string Text { get; set; }

    public virtual string GetAllText()
    {
      return Text;
    }
  }

  /// <summary>
  /// Базовый токен для всех тегов.
  /// </summary>
  public class TagToken : Token { }

  public class AtomToken : TagToken { }
  public class AtomCloseToken : TagToken { }
  public class BrToken : TagToken { }
  public class CenterToken : TagToken { }
  public class FJustifyToken : TagToken { }
  public class FRightToken : TagToken { }
  public class IfToken : TagToken
  {
    public List<Token> childTokens;

    public override string GetAllText()
    {
      if (childTokens == null)
        return base.GetAllText();

      var sb = new StringBuilder();
      sb.Append(base.GetAllText());
      childTokens.ForEach(t => sb.Append(t.GetAllText()));
      return sb.ToString();
    }
  }
  public class IfCloseToken : TagToken { }
  public class IfElseToken : IfToken { }
  public class ImageToken : TagToken { }
  public class JustifyToken : TagToken { }
  public class LeftToken : TagToken { }
  public class RightToken : TagToken { }
  public class SpaceToken : TagToken { }
  public class StyleToken : TagToken { }
  public class StyleCloseToken : TagToken { }
  public class ValueToken : TagToken { }

  /// <summary>
  /// Базовый токен для всех "псевдо-тегов" $(###).
  /// </summary>
  public class PTagToken : Token { }

  /// <summary>
  /// Подпорочный токен для одиночных угловых скобок
  /// </summary>
  public class AngleBracketToken : Token { }

  /// <summary>
  /// Токен для простого текста.
  /// </summary>
  public class TextToken : Token
  {
  }

}