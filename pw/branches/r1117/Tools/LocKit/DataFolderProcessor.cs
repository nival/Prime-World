using System;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.Diagnostics;
using System.IO;
using System.Text;
using System.Xml.Linq;
using LocKit.Localization;
using LocKit.Tokens;

namespace LocKit
{
  static class DataFolderProcessor
  {
    public static NameValueCollection CollectTexts( string folderPath )
    {
      return CollectTexts( folderPath, null );
    }

    public static NameValueCollection CollectTexts( string folderPath, Func<string, bool> isSuitableString )
    {
      var result = new NameValueCollection();
      int skippedTexts = 0;
      string fullPath = Path.GetFullPath( folderPath ).TrimEnd( Path.DirectorySeparatorChar, Path.AltDirectorySeparatorChar );
      int trimLegth = fullPath.Length + 1;
      string fileContent = string.Empty;
      string path = string.Empty;
      foreach ( string filePath in Directory.GetFiles( fullPath, "*.txt", SearchOption.AllDirectories ) )
      {
        fileContent = File.ReadAllText( filePath );
        path = filePath.Substring( trimLegth );
        if ( isSuitableString != null )
          if ( !isSuitableString( fileContent ) )
          {
            Trace.WriteLine( string.Format( "Skip text file '{0}' beacause it contains not suitable text \n----\n{1}\n----\n", path, fileContent ) );
            skippedTexts++;
            continue;
          }

        result.Add( path, fileContent );
      }

      if ( skippedTexts > 0 )
        Trace.WriteLine( string.Format( "{0} files was skipped", skippedTexts ) );

      return result;
    }

    /// <summary>
    /// Сохранить тексты в xml файл.
    /// </summary>
    /// <param name="texts">Тексты.</param>
    /// <param name="filename">Имя xml файла.</param>
    /// <param name="stopOnWarnings">Прерывать процесс при возникновении Warning.</param>
    public static void CreateLocalizationFile( NameValueCollection texts, string filename, bool stopOnWarnings )
    {
      var tproc = new TokenProcessor();
      var lproc = new LocalizationProcessor();
      bool success = true;

      var xD = new XDocument();
      xD.Add( new XElement( "localization" ) );

      foreach ( string key in texts.Keys )
      {
        List<Token> tokens;

        try
        {
          tokens = tproc.ProcessText( texts[key] );
        }
        catch ( Exception ex )
        {
          Trace.TraceError( "Parsing error in file {0}.\n{1}", key, ex.Message );
          continue;
        }

        // Валидация полученного результата
        int warncount = 0, errorcount = 0;
        tproc.SyntaxVerification( tokens, ref warncount, ref errorcount );
        if ( errorcount > 0 || ( warncount > 0 && stopOnWarnings ) )
        {
          Trace.TraceError( "Failed to parse file '{0}'. Error count = {1}, Warning count= {2}",
                           key, errorcount, warncount );
          success = false;
          continue;
        }
        else if ( warncount > 0 )
        {
          Trace.TraceWarning( "Warning while parsing file {0}. Error count = {1}, Warning count= {2}",
                           key, errorcount, warncount );
        }

        LocalizationFile lfile;
        try
        {
          lfile = lproc.TokensToLocalization( key, tokens );
        }
        catch ( Exception ex )
        {
          Trace.TraceError( "Failed to create localization file from {0}.\n{1}", key, ex.Message );
          continue;
        }

        XElement elem = lfile.ToXML();

        xD.Root.Add( elem );
      }

      if ( success )
        xD.Save( filename );
      else
        Trace.TraceError( "Localization file has not been formed." );
    }

    public static void UpdateTexts( string folderPath, NameValueCollection texts, Dictionary<string, object> brokenFiles )
    {
      string fullPath = Path.GetFullPath( folderPath );

      foreach ( string fileName in texts.Keys )
      {
        if ( brokenFiles.ContainsKey( fileName ) )
          continue;

        string filePath = Path.Combine( fullPath, fileName );

        string text = texts[fileName];
        if ( string.IsNullOrEmpty( text ) )
          continue;

        string shortDash = string.Format( "{0}{1}{2}", (char)32, (char)45, (char)32 );
        string longDash = string.Format( "{0}{1}{2}", (char)32, (char)8211, (char)32 );

        if ( text.Contains( shortDash ) )
          text = text.Replace( shortDash, longDash );

        if ( !Directory.Exists( Path.GetDirectoryName( filePath ) ) )
          Directory.CreateDirectory( Path.GetDirectoryName( filePath ) );
        File.WriteAllText( filePath, text, Encoding.Unicode );
      }
    }
  }
}
