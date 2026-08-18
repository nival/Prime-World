using System.Collections.Generic;
using System.Text.RegularExpressions;
using Flash;
using UnityEngine;

namespace FlashView.Utils.FormatParser
{
  class FormatParser
  {
    private const string DEFAULT_FONT_NAME = "DejaVuLGCSans";
    //private const string SPACES = @"\s+"; //ищет все пробелы и переносы строк
    private const string SPACES_BETWEEN_TAGS = @"(?<=>)\s+(?=<)"; //ищет все пробелы и переносы строк между тэгами
    private const string IGNORED_TAGS = @"<castle>|</castle>|<session>.*?</session>";

    #region Predefined Styles

    private static readonly Dictionary<string, Style> _predefinedStyles = new Dictionary<string, Style>();
    public static Dictionary<string, Style> PredefinedStyles
    {
      get { return _predefinedStyles; }
    }

    private static readonly Dictionary<string, Texture2D> _predefinedImages = new Dictionary<string, Texture2D>();
    public static Dictionary<string, Texture2D> PredefinedImages
    {
      get { return _predefinedImages; }
    }

    #endregion

    #region States

    private readonly StateContext _context = null;
    private IState _currentState;

    private readonly TextState _textState = null;
    private readonly TagState _tagState = null;
    private readonly CloseTagState _closeTagState = null;
    private readonly BrTagState _brTagState = null;
    private readonly UnaryTagState _unaryTagState = null;
    private readonly FormattingTagState _formattingTagState = null;

    #endregion

    public FormatParser()
    {
      _context = new StateContext();

      _textState = new TextState( _context );
      _tagState = new TagState( _context );
      _closeTagState = new CloseTagState( _context );
      _brTagState = new BrTagState( _context );
      _unaryTagState = new UnaryTagState( _context );
      _formattingTagState = new FormattingTagState( _context );
    }

    public FormatedText Parse( string input, Style defaultStyle )
    {
      if ( string.IsNullOrEmpty( input ) )
        return new FormatedText();

      //удаляем пробелы между тегами
      input = Regex.Replace( input, SPACES_BETWEEN_TAGS, string.Empty, RegexOptions.IgnoreCase | RegexOptions.Singleline );
      //заменяем пробелы на один пробел, не может идти 2 пробела подряд
      //input = Regex.Replace( input, SPACES, " ", RegexOptions.IgnoreCase | RegexOptions.Singleline );

      input = Regex.Replace( input, IGNORED_TAGS, string.Empty, RegexOptions.IgnoreCase | RegexOptions.Singleline );

      //Debug.Log( "##input:" + input );

      for ( int i = 0; i < input.Length; i++ )
      {
        UpdateState( input, i );
      }

      //Debug.Log( "##" + PrintEntries( _context.RootEntry ) );

      FormatConverter converter = new FormatConverter( PredefinedStyles, PredefinedImages );
      IEnumerable<FormatEntry> entries = converter.GetFormatingItems(_context.RootEntry, defaultStyle);

      //Debug.Log( "##formatted: " + PrintFormatedText( entries ) );

      return new FormatedText( entries );
    }

    //здесь описываются условия перехода
    private void UpdateState( string input, int pos )
    {
      char ch = input[pos];

      if ( ch == '<' && CharIs( '/', input, pos + 1 ) )//enter to CloseTagState
      {
        //выходим из предыдущего стейта
        if ( _currentState != null )
          _currentState.Leave();

        //заходим в стейт обработки тэгов
        _currentState = _closeTagState;
        if ( _currentState != null )
          _currentState.Enter();
        return;
      }

      if ( ch == '<' )//enter to TagState
      {
        //выходим из предыдущего стейта
        if ( _currentState != null )
          _currentState.Leave();

        if ( IsBrTag( input, pos + 1 ) )
        {
          _currentState = _brTagState;
          _textState.IgnoreSpace = true;//при переходе на новую строку, надо запрещать пробелы в начале строки в TextState
        }
        else if ( IsUnaryTag( input, pos + 1 ) )
        {
          _currentState = _unaryTagState;
          _textState.IgnoreSpace = false;//если в тексте вдруг встретился унарный тег, то пробелы вокруг него не игнориуем
        }
        else if ( IsFormattingTag( input, pos + 1 ) )
        {
          _currentState = _formattingTagState;
        }
        else
        {
          _currentState = _tagState;  //заходим в стейт обработки тэгов
        }

        if ( _currentState != null )
          _currentState.Enter();
        return;
      }

      if ( ch == '>' )//leave from TagState
      {
        if ( _currentState != null )
          _currentState.Leave();
        _currentState = null;
        return;
      }

      if ( _currentState == null )//enter to textState
      {
        _currentState = _textState;
        if ( _currentState != null )
          _currentState.Enter();
      }

      if ( _currentState != null )
      {
        _currentState.Update( ch );
      }
    }

    private static bool CharIs( char ch, string input, int index )
    {
      if ( index >= 0 || index < input.Length )
      {
        return input[index] == ch;
      }

      return false;
    }

    private static bool IsUnaryTag( string input, int index )
    {
      if ( index >= 0 && index < input.Length )
      {
        string[] unaryTags = new[] { "space", "image", "value" };

        foreach ( string tag in unaryTags )
        {
          if ( input.IndexOf( tag, index ) == index )
            return true;
        }
      }

      return false;
    }

    private static bool IsBrTag( string input, int index )
    {
      if ( index >= 0 && index < input.Length )
      {
        return input.IndexOf( "br", index ) == index;
      }

      return false;
    }

    private static bool IsFormattingTag( string input, int index )
    {
      if ( index >= 0 && index < input.Length )
      {
        string[] unaryTags = new[] { "center", "left", "right", "f_right" };

        foreach ( string tag in unaryTags )
        {
          if ( input.IndexOf( tag, index ) == index )
            return true;
        }
      }

      return false;
    }

    #region Debug Output
    #if UNITY_EDITOR
    private static string PrintEntries( Entry root )
    {
      string result = string.Empty;

      int indent = 0;
      Entry parent = root.Parent;

      while ( parent != null )
      {
        indent++;
        parent = parent.Parent;
      }

      string text = root.Text;

      if ( root.EntryType == EntryType.Root )
        text = "root";

      result = '-' + text + "\n";

      foreach ( Entry child in root.Children )
      {
        result += PrintEntries( child );
      }

      return result;
    }

    private static string PrintFormatedText( IEnumerable<FormatEntry> entries )
    {
      string result = string.Empty;

      foreach ( FormatEntry style in entries )
      {
        result += string.Format( "[{0}][{1}]\n", style.Style, style.Data.ToString().Replace( "\n", "\\n" ) );
      }

      return result;
    }
    #endif
    #endregion
  }
}
