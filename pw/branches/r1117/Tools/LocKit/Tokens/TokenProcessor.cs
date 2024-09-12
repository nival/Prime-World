using System;
using System.Collections.Generic;
using System.Diagnostics;

namespace LocKit.Tokens
{
  /// <summary>
  /// ¬спомогательный класс дл€ работы с токенами.
  /// </summary>
  public class TokenProcessor
  {
    /// <summary>
    /// ѕреобразует вход€щий текст в последовательность токенов.
    /// </summary>
    public List<Token> ProcessText( string text )
    {
      var tokens = new List<Token>();
      int pos = 0;

      // ќписываютс€ какие токены будут парситьс€ и в каком пор€дке приоритета.
      var fqs = new List<ITokenFabrique>
                  {
                    new TagTokenFabrique(),
                    new PTagTokenFabrique(),
                    new AngleBracketTokenFabrique(),
                    new TextTokenFabrique()
                  };

      // Ћексический разбор файла.
      while ( pos < text.Length )
      {
        string filepart = text.Substring( pos );
        Token t = null;

        foreach ( ITokenFabrique fq in fqs )
        {
          t = fq.GetToken( filepart );
          if ( t != null ) break;
        }

        if ( t == null )
          throw new Exception( "Cannot parse string :\n" + filepart );

        pos += t.Text.Length;
        tokens.Add( t );
      }

      // —интаксический разбор.
      List<Token> result = Syntax( tokens );

      return result;
    }

    /// <summary>
    /// —интаксический разбор полученных токенов, построение иерархии.
    /// </summary>
    private List<Token> Syntax( List<Token> tokens )
    {
      var result = new List<Token>();
      //  аунтер обновл€етс€ по ссылке и хранит обрабатываемый элемент входного множества.
      int pos = 0;
      while ( pos < tokens.Count )
      {
        // ≈сли встретилс€ IfToken, то все остальные токены до IfCloseToken считаютс€ его подмножеством.
        if ( tokens[pos] is IfToken )
          SyntaxIf( tokens, ref pos, result );
        else
          result.Add( tokens[pos] );
        pos++;
      }
      return result;
    }

    /// <summary>
    /// ¬ыделение If-then блока из массива токенов.
    /// </summary>
    private void SyntaxIf( List<Token> tokens, ref int pos, List<Token> result )
    {
      IfToken token = tokens[pos] as IfToken;
      if ( token == null )
        throw new Exception( "This is not IF! pos = " + pos );

      result.Add( token );
      // ≈сли if пр€мо тут же не заканчиваетс€, то нужно иницилизовать множество дочерних токенов
      if ( !( tokens[pos + 1] is IfElseToken ) && !( tokens[pos + 1] is IfCloseToken ) )
        token.childTokens = new List<Token>();

      do
      {
        pos++;
        Token item = tokens[pos];
        if ( item is IfElseToken )
        {
          // ќбработка else
          SyntaxIfElse( tokens, ref pos, result );
          break;
        }
        else if ( item is IfToken )
        {
          // ќбработка вложенных if'ов.
          SyntaxIf( tokens, ref pos, token.childTokens );
        }
        else if ( item is IfCloseToken )
        {
          // IfCloseToken завершает обработку.
          result.Add( item );
          break;
        }
        else
        {
          token.childTokens.Add( item );
        }
      } while ( pos < tokens.Count - 1 );
    }

    /// <summary>
    /// ¬ыделение If-else блока из массива токенов.
    /// </summary>
    private void SyntaxIfElse( List<Token> tokens, ref int pos, List<Token> result )
    {
      IfElseToken token = tokens[pos] as IfElseToken;
      if ( token == null )
        throw new Exception( "This is not ELSE! pos = " + pos );

      result.Add( token );
      // ≈сли else пр€мо тут же не заканчиваетс€, то нужно иницилизовать множество дочерних токенов
      if ( !( tokens[pos + 1] is IfCloseToken ) )
        token.childTokens = new List<Token>();

      do
      {
        pos++;
        Token item = tokens[pos];
        if ( item is IfToken )
        {
          // ќбработка вложенных if'ов.
          SyntaxIf( tokens, ref pos, token.childTokens );
        }
        else if ( item is IfCloseToken )
        {
          // IfCloseToken завершает обработку.
          result.Add( item );
          break;
        }
        else
        {
          token.childTokens.Add( item );
        }
      } while ( pos < tokens.Count - 1 );
    }

    /// <summary>
    /// ¬алидаци€ полученного массива токенов
    /// </summary>
    /// <param name="tokens"></param>
    /// <param name="warncount"></param>
    /// <param name="errorcount"></param>
    public void SyntaxVerification( List<Token> tokens, ref int warncount, ref int errorcount )
    {
      for ( int i = 0; i < tokens.Count; i++ )
      {
        if ( ( tokens[i] is IfToken ) && ( ( tokens.Count - i ) > 1 )
          && !( tokens[i + 1] is IfElseToken ) && !( tokens[i + 1] is IfCloseToken ) )
        {
          Trace.TraceError( String.Format( "ERROR : {0} after {1}", tokens[i + 1].GetType().Name, tokens[i].GetType().Name ) );
          errorcount++;
        }
        if ( ( tokens[i] is IfElseToken ) && ( ( tokens.Count - i ) > 1 )
          && !( tokens[i + 1] is IfCloseToken ) )
        {
          Trace.TraceError( String.Format( "ERROR : {0} after {1}", tokens[i + 1].GetType().Name, tokens[i].GetType().Name ) );
          errorcount++;
        }
        if ( tokens[i] is IfToken )
        {
          var t = (IfToken)tokens[i];
          if ( t.childTokens != null )
            SyntaxVerification( t.childTokens, ref warncount, ref errorcount );
        }
        if ( tokens[i] is IfElseToken )
        {
          var t = (IfElseToken)tokens[i];
          if ( t.childTokens != null )
            SyntaxVerification( t.childTokens, ref warncount, ref errorcount );
        }
      }
    }


  }
}