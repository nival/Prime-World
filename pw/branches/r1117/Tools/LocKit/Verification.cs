using System.Collections.Generic;
using System.Collections.Specialized;
using System.Diagnostics;
using LocKit.Tokens;

namespace LocKit
{
  static class Verification
  {
    private static Token GetNextToken( List<Token> tokens, ref int index )
    {
      if ( tokens == null )
        return null;
      while ( index < tokens.Count )
      {
        Token token = tokens[index];
        ++index;
        if ( token.GetType() != typeof( TextToken ) )
          return token;
      }

      return null;
    }

    private static bool CheckTags( string fileName, List<Token> textTokens, List<Token> origTokens )
    {
      bool result = true;
      int textIndex = 0;
      int origIndex = 0;
      Token textToken = GetNextToken( textTokens, ref textIndex );
      Token origToken = GetNextToken( origTokens, ref origIndex );
      while ( textToken != null || origToken != null )
      {
        string message = string.Empty;
        if ( textToken == null )
          message = string.Format( "missed translated token for {0} (\"{1}\")", origToken.GetType().Name, origToken.Text.Trim() );
        else if ( origToken == null )
          message = string.Format( "unnecessary translated token {0} (\"{1}\")", textToken.GetType().Name, textToken.Text.Trim() );
        else
        {
          if ( textToken.GetType() != origToken.GetType() )
            message = string.Format( "tokens mismatch {0} (\"{1}\") - {2} (\"{3}\")", textToken.GetType().Name, textToken.Text.Trim(), origToken.GetType().Name, origToken.Text.Trim() );
          else
          {
            var textIfToken = textToken as IfToken;
            var origIfToken = origToken as IfToken;
            if ( textIfToken != null && origIfToken != null )
            {
              if ( !CheckTags( result ? string.Empty : fileName, textIfToken.childTokens, origIfToken.childTokens ) )
                result = false;
            }
          }
        }

        if ( !string.IsNullOrEmpty( message ) )
        {
          if ( !string.IsNullOrEmpty( fileName ) )
            Trace.TraceError( string.Format( "Item \"{0}\" has mismatched tokens", fileName ) );
          Trace.TraceError( string.Format( "  {0}", message ) );
          fileName = string.Empty;
          result = false;
        }

        textToken = GetNextToken( textTokens, ref textIndex );
        origToken = GetNextToken( origTokens, ref origIndex );
      }

      return result;
    }

    /// <summary>
    /// Сравнивает оригинальный и переведенный списки файлов. Возвращает Dictionary с  _битыми_ файлами. Если файл ок - его не будет в результате
    /// </summary>
    public static void Check( NameValueCollection originals, NameValueCollection texts, Dictionary<string, object> brokenFiles )
    {
      foreach ( string fileName in originals.Keys )
      {
        if ( texts[fileName] == null )
        {
          Trace.TraceWarning( string.Format( "Item \"{0}\" found in data folder but not found in translated file", fileName ) );
          brokenFiles.Add( fileName, null );
        }
      }

      var proc = new TokenProcessor();

      foreach ( string fileName in texts.Keys )
      {
        string orig = originals[fileName];
        string text = texts[fileName];
        if ( orig == null )
        {
          Trace.TraceWarning( string.Format( "Item \"{0}\" found in translated file but not found in data folder", fileName ) );
          brokenFiles.Add( fileName, null );
          continue;
        }

        List<Token> origTokens = proc.ProcessText( orig );
        List<Token> textTokens = proc.ProcessText( text );

        if ( !CheckTags( fileName, origTokens, textTokens ) )
          brokenFiles.Add( fileName, null );
      }
    }
  }
}
