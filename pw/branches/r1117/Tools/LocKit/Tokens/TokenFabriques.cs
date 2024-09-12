using System.Collections.Generic;
using System.Text.RegularExpressions;

namespace LocKit.Tokens
{
  /// <summary>
  /// Интерфейс фабрики токенов.
  /// </summary>
  interface ITokenFabrique
  {
    /// <summary>
    /// Получить токен из строки.
    /// </summary>
    Token GetToken(string text);
  }

  /// <summary>
  /// Базовый класс для фабрик.
  /// </summary>
  /// <typeparam name="T">Конкретный тип токена.</typeparam>
  abstract class TokenFabrique<T> : ITokenFabrique where T : Token, new()
  {
    /// <summary>
    /// Регулярное выражение, описывающее токен.
    /// </summary>
    protected abstract string Pattern { get; }

    /// <summary>
    /// Дочерние фабрики, конкретизирующие данный токен.
    /// </summary>
    protected List<ITokenFabrique> childFabriques;

    public virtual Token GetToken(string text)
    {
      var match = new Regex(@"^\s*" + Pattern).Match(text);
      if (!match.Success)
        return null;

      if (childFabriques != null)
        foreach (var fabrique in childFabriques)
        {
          Token t = fabrique.GetToken(text);
          if (t != null)
            return t;
        }

      return new T { Text = match.Value };
    }
  }

  /// <summary>
  /// Базовая фабрика для всех тегов.
  /// </summary>
  class TagTokenFabrique : TokenFabrique<TagToken>
  {
    protected override string Pattern
    {
      // Позволяет матчить не только простые теги вида <abc...>
      // но и дикие вложенные теги-мутанты вида <abc...<def...>..>
      get { return @"<[^<]*?(<[^<]*?>)*?[^<]*?>"; }
    }
    public TagTokenFabrique()
    {
      childFabriques = new List<ITokenFabrique>
                   {
                     new AtomTokenFabrique(),
                     new AtomCloseTokenFabrique(),
                     new BrTokenFabrique(),
                     new CenterTokenFabrique(),
                     new FJustifyTokenFabrique(),
                     new FRightTokenFabrique(),
                     new IfTokenFabrique(),
                     new IfCloseTokenFabrique(),
                     new IfElseTokenFabrique(),
                     new ImageTokenFabrique(),
                     new JustifyTokenFabrique(),
                     new LeftTokenFabrique(),
                     new RightTokenFabrique(),
                     new SpaceTokenFabrique(),
                     new StyleTokenFabrique(),
                     new StyleCloseTokenFabrique(),
                     new ValueTokenFabrique()
                   };
    }
  }
  class AtomTokenFabrique : TokenFabrique<AtomToken>
  {
    protected override string Pattern
    {
      get { return @"<atom>"; }
    }
  }
  class AtomCloseTokenFabrique : TokenFabrique<AtomCloseToken>
  {
    protected override string Pattern
    {
      get { return @"</atom>"; }
    }
  }
  class BrTokenFabrique : TokenFabrique<BrToken>
  {
    protected override string Pattern
    {
      get { return @"<br(:\d+)?>"; }
    }
  }
  class CenterTokenFabrique : TokenFabrique<CenterToken>
  {
    protected override string Pattern
    {
      get { return @"<center[\w\d=_. ]*>"; }
    }
  }
  class FJustifyTokenFabrique : TokenFabrique<FJustifyToken>
  {
    protected override string Pattern
    {
      get { return @"<fjustify[\w\d=_. ]*>"; }
    }
  }
  class FRightTokenFabrique : TokenFabrique<FRightToken>
  {
    protected override string Pattern
    {
      get { return @"<f_right>"; }
    }
  }
  class IfTokenFabrique : TokenFabrique<IfToken>
  {
    protected override string Pattern
    {
      get { return @"<if\s*=[\w\d_.\s]+>"; }
    }
  }
  class IfCloseTokenFabrique : TokenFabrique<IfCloseToken>
  {
    protected override string Pattern
    {
      get { return @"</if>"; }
    }
  }
  class IfElseTokenFabrique : TokenFabrique<IfElseToken>
  {
    protected override string Pattern
    {
      get { return @"<else>"; }
    }
  }
  class ImageTokenFabrique : TokenFabrique<ImageToken>
  {
    protected override string Pattern
    {
      get { return @"<image:[\w\d=_. ]+>"; }
    }
  }
  class JustifyTokenFabrique : TokenFabrique<JustifyToken>
  {
    protected override string Pattern
    {
      get { return @"<justify[\w\d=_. ]*>"; }
    }
  }
  class LeftTokenFabrique : TokenFabrique<LeftToken>
  {
    protected override string Pattern
    {
      get { return @"<left[\w\d=_. ]*>"; }
    }
  }
  class RightTokenFabrique : TokenFabrique<RightToken>
  {
    protected override string Pattern
    {
      get { return @"<right[\w\d=_. ]*>"; }
    }
  }
  class SpaceTokenFabrique : TokenFabrique<SpaceToken>
  {
    protected override string Pattern
    {
      get { return @"<space(:\d+)?[\w\d=_. ]*>"; }
    }
  }
  class StyleTokenFabrique : TokenFabrique<StyleToken>
  {
    protected override string Pattern
    {
      get { return @"<style:[\w\d._]+>"; }
    }
  }
  class StyleCloseTokenFabrique : TokenFabrique<StyleCloseToken>
  {
    protected override string Pattern
    {
      get { return @"</style>"; }
    }
  }
  class ValueTokenFabrique : TokenFabrique<ValueToken>
  {
    protected override string Pattern
    {
      get { return @"<value[:=][\w\d=_. ]+>"; }
    }
  }

  /// <summary>
  /// Базовая фабрика для псевдо-тегов.
  /// </summary>
  class PTagTokenFabrique : TokenFabrique<PTagToken>
  {
    protected override string Pattern
    {
      get { return @"\$\([^<]*?\)"; }
    }
  }

  /// <summary>
  /// Фабрика для угловых тегов.
  /// </summary>
  class AngleBracketTokenFabrique : TokenFabrique<AngleBracketToken>
  {
    protected override string Pattern
    {
      get { return @"[<>]"; }
    }
  }

  /// <summary>
  /// Базовая фабрика для текстовых элементов.
  /// </summary>
  class TextTokenFabrique : TokenFabrique<TextToken>
  {
    protected override string Pattern
    {
      get { return @"[^<\$]+"; }
    }
  }

}