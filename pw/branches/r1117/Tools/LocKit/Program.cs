using System;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text.RegularExpressions;
using LocKit.ExcelUtils;
using LocKit.Localization;

namespace LocKit
{
  static class Program
  {
    [CommandLineParser.Argument()]
    private static List<string> inputArgs = new List<string>();

    [CommandLineParser.Argument( "t", "translate", "Update content of data folder using translate file" )]
    private static bool translate = false;

    [CommandLineParser.Argument( "c", "collect", "Collect texts from data folder and atore in in translate file" )]
    private static bool collect = false;

    [CommandLineParser.Argument( "?", "help", "Show this usage screen" )]
    private static bool showHelp = false;

    [CommandLineParser.Argument( "f", "copyfile", "Specify file with list of copiing files. Translated files will be copied to folder with translate file" )]
    private static string copyFile = string.Empty;

    [CommandLineParser.Argument( "", "copyfileout", "File with list of copied files." )]
    private static string copyFileOut = string.Empty;

    [CommandLineParser.Argument( "r", "verify", "Just verify content of translate file using specified data folder" )]
    private static bool verify = false;

    [CommandLineParser.Argument( "i", "ignore", "Update all files even with warings" )]
    private static bool ignoreWarnings = false;

    [CommandLineParser.Argument( "w", "warnings", "Do not update data folder if any warning found" )]
    private static bool stopOnWarnings = false;

    [CommandLineParser.Argument( "v", "verbose", "Set verbose level (0 - only criticals, 1 (default) - criticals and warnings, 2 - all)" )]
    private static int verbose = 1;

    [CommandLineParser.Argument( "cmp", "compare", "Compare translate files and save result in Excel" )]
    private static bool compare = false;

    [CommandLineParser.Argument( "d", "decode", "Decode Excel file and resave it in translate xml format" )]
    private static bool decode = false;

    [CommandLineParser.Argument( "md", "mergedups", "Merge dups in single line in translation file" )]
    private static bool mergedups = false;

    [CommandLineParser.Argument( "umd", "unmergedups", "Unmerge dups from single lines in translation file" )]
    private static bool unmergedups = false;

    [CommandLineParser.Argument( "inl", "ignorenl", "Ignore system (not localizable) texts" )]
    private static bool ignoreNotLocalizable = false;

    static int Main( string[] args )
    {
      Trace.Listeners.Remove( "Default" );
      Trace.Listeners.Add( new DebugTraceListener() );

      if ( !CommandLineParser.FillObject( typeof( Program ), args,
        ( string arg ) => { Console.WriteLine( "Invalid argument \"{0}\"", arg ); return false; },
        ( string arg, string value ) => { Console.WriteLine( "Invalid value \"{0}\" for argument \"{1}\"", value, arg ); return false; } ) )
      {
        return 1;
      }

      if ( showHelp || args.Length == 0 )
      {
        Console.WriteLine( "Usage: lockit.exe <data_folder> <translate_file(s)> commands" );
        Console.WriteLine( "       lockit.exe -cmp <old_original_file> <old_localized_file> <new_original_file> <output_file>" );
        Console.WriteLine( "       lockit.exe -cmp -d <excel_file> <new_translate_file>" );
        Console.WriteLine( "       lockit.exe -md <source_translate_file> <result_translate_file>" );
        Console.WriteLine( "       lockit.exe -umd <source_translate_file> <result_translate_file>" );
        CommandLineParser.ShowHelp( typeof( Program ), true, null );
        return 0;
      }

      if ( !compare && inputArgs.Count != 2 )
      {
        Console.WriteLine( "Data folder and translate file should be both specified" );
        return 1;
      }
      if ( ( compare && !decode && inputArgs.Count != 4 ) || ( compare && decode && inputArgs.Count != 2 ) )
      {
        Console.WriteLine( "All comparing parameters should be specified" );
        return 1;
      }

      if ( ( unmergedups || mergedups ) && !collect && inputArgs.Count != 2 && !compare )
      {
        Console.WriteLine( "you must specified at least source and result files for merging dups operation" );
        return 1;
      }

      if ( ( translate || verify ) == collect && !compare && !( mergedups || unmergedups ) )
      {
        Console.WriteLine( "translate and verify operations cannot be used with collect one" );
        return 1;
      }



      Trace.Listeners.Add( new ShortConsoleTraceListener( (ShortConsoleTraceListener.VerboseLevel)verbose ) );
      try
      {
        if ( translate || verify )
        {
          string dataFolder = inputArgs[0];
          var start = DateTime.Now;
          Trace.WriteLine( string.Format( "Searching texts in folder \"{0}\"...", dataFolder ) );
          NameValueCollection originals = DataFolderProcessor.CollectTexts( dataFolder );
          Trace.WriteLine( string.Format( " done ({0} s)", ( DateTime.Now - start ).TotalSeconds ) );

          List<string> ignoredKeys = new List<string>();
          if ( ignoreNotLocalizable )
          {
            Trace.WriteLine( string.Format( "Searching for not localizable texts..." ) );
            foreach ( var k in originals.AllKeys )
              if ( !IsLocalizableText( originals[k] ) )
                ignoredKeys.Add( k );

            Trace.WriteLine( string.Format( "{0} not localizable texts found", ignoredKeys.Count ) );
          }

          List<string> translateFiles = new List<string>();
          foreach ( var file in inputArgs[1].Split( new string[] { SEPARATOR_CHAR }, StringSplitOptions.RemoveEmptyEntries ) )
            if ( File.Exists( file ) )
              translateFiles.Add( file );
            else
              Trace.WriteLine( string.Format( "File \"{0}\" not found, skipping", file ) );

          List<NameValueCollection> textContainers = new List<NameValueCollection>();
          Dictionary<string, object> brokenFiles = new Dictionary<string, object>();

          foreach ( var file in translateFiles )
          {
            start = DateTime.Now;
            Trace.WriteLine( string.Format( "Reading file \"{0}\" ...", file ) );
            var texts = TranslateFileProcessor.CollectTexts( file );
            Trace.WriteLine( string.Format( " done ({0} s)", ( DateTime.Now - start ).TotalSeconds ) );

            start = DateTime.Now;
            Trace.WriteLine( string.Format( "Unmerging dups..." ) );
            int beforeUnMergeSize = texts.Count;
            UnMergeDups( ref texts );
            Trace.WriteLine( string.Format( "Texts count after unmerge '{0}'->'{1}'", beforeUnMergeSize, texts.Count ) );
            Trace.WriteLine( string.Format( " unmerge done ({0} s)", ( DateTime.Now - start ).TotalSeconds ) );

            textContainers.Add( texts );
          }

          if ( textContainers.Count == 0 )
          {
            Trace.TraceError( "No translate files was found from '{0}'. Exit.", inputArgs[1] );
            return 1;
          }

          for ( int i = textContainers.Count - 1; i >= 0; i-- )
          {
            var container = textContainers[i];
            var fileName = translateFiles[i];
            foreach ( var key in ignoredKeys )
            {
              container.Remove( key );
              Trace.WriteLine( string.Format( "Text with key '{0}' from file '{1}' will be ignored, because source file content in '{2}' is not localizable.", key, fileName, dataFolder ) );
            }
          }

          if ( verify )
          {
            var texts = textContainers[0];
            var translateFile = translateFiles[0];

            if ( textContainers.Count > 1 )
              Trace.TraceError( "Verify operation doesn't support multiply translation files for now. Using '{0}'.", translateFile );



            start = DateTime.Now;
            Trace.WriteLine( string.Format( "Verifying translation ({0} items)...", texts.Count ) );
            Verification.Check( originals, texts, brokenFiles );
            Trace.WriteLine( string.Format( " done ({0} s)", ( DateTime.Now - start ).TotalSeconds ) );

            if ( !string.IsNullOrEmpty( copyFile ) )
            {
              start = DateTime.Now;
              Trace.WriteLine( string.Format( "Verifying translated localizable files..." ) );
              FilesListProcessor.VerifyTranslatedFiles( dataFolder, Path.GetDirectoryName( translateFile ), brokenFiles );
              Trace.WriteLine( string.Format( " done ({0} s)", ( DateTime.Now - start ).TotalSeconds ) );
            }

            if ( stopOnWarnings && brokenFiles.Count > 0 )
            {
              Trace.TraceError( "{0} warnings found and --warnings specified", brokenFiles.Count );
              return 1;
            }
          }

          if ( translate )
          {
            if ( ignoreWarnings )
              brokenFiles.Clear();

            var resultValues = new Dictionary<string, string>();
            var sourceInfos = new Dictionary<string, string>();

            foreach ( var k in originals.AllKeys )
            {
              resultValues.Add( k, originals[k] );
              sourceInfos.Add( k, string.Empty );
            }


            for ( int i = textContainers.Count - 1; i >= 0; i-- )
            {
              var texts = textContainers[i];
              var fileName = translateFiles[i];
              start = DateTime.Now;
              Trace.Write( string.Format( "Updating texts in folder \"{0}\" with \"{1}\"...", dataFolder, fileName ) );
              DataFolderProcessor.UpdateTexts( dataFolder, texts, brokenFiles );
              Trace.WriteLine( string.Format( " done ({0} s)", ( DateTime.Now - start ).TotalSeconds ) );

              foreach ( var k in texts.AllKeys )
              {
                if ( resultValues.ContainsKey( k ) )
                {
                  resultValues[k] = texts[k];
                  sourceInfos[k] = fileName;
                }
                else
                  Trace.TraceWarning( "File with key '{0}' described in '{1}' but not found in '{2}'", k, fileName, dataFolder );
              }
            }

            #region Printing report
            Trace.WriteLine( string.Format( "Result printing..." ) );
            for ( int i = textContainers.Count - 1; i > 0; i-- )
            {
              var fileName = translateFiles[i];
              Trace.WriteLine( string.Format( "Texts applied from '{0}':", fileName ) );
              foreach ( var kp in sourceInfos )
                if ( string.Equals( kp.Value, fileName ) )
                  Trace.WriteLine( string.Format( "\n----\n'{0}':\n\n{1}\n----", kp.Key, resultValues[kp.Key] ) );
              Trace.WriteLine( string.Format( "done" ) );
              Trace.WriteLine( string.Empty );
            }

            Trace.WriteLine( string.Format( "Not changed (not found in localizations) texts:" ) );
            foreach ( var kp in sourceInfos )
              if ( string.IsNullOrEmpty( kp.Value ) )
                Trace.WriteLine( string.Format( "\n----\n'{0}':\n\n{1}\n----", kp.Key, resultValues[kp.Key] ) );

            Trace.WriteLine( string.Format( "done" ) );
            Trace.WriteLine( string.Format( "Result printing...done" ) );
            #endregion
          }



          if ( !string.IsNullOrEmpty( copyFile ) )
          {
            var translateFile = translateFiles[0];
            if ( textContainers.Count > 1 )
              Trace.TraceError( "Files copying operation doesn't support multiply translation files for now. Using '{0}'.", translateFile );

            start = DateTime.Now;
            Trace.WriteLine( string.Format( "Verifying translated localizable files..." ) );
            FilesListProcessor.UpdateFileInData( dataFolder, Path.GetDirectoryName( translateFile ), copyFile, copyFileOut, brokenFiles );
            Trace.WriteLine( string.Format( " done ({0} s)", ( DateTime.Now - start ).TotalSeconds ) );
          }
        }
        else if ( collect )
        {
          string dataFolder = inputArgs[0];
          string translateFile = inputArgs[1];

          DateTime start = DateTime.Now;
          Trace.WriteLine( string.Format( "Searching texts in folder \"{0}\"...", dataFolder ) );
          NameValueCollection originals = ignoreNotLocalizable
                                            ? DataFolderProcessor.CollectTexts(dataFolder, IsLocalizableText)
                                            : DataFolderProcessor.CollectTexts(dataFolder);
          Trace.WriteLine( string.Format( " done ({0} s)", ( DateTime.Now - start ).TotalSeconds ) );

          if ( mergedups )
          {
            start = DateTime.Now;
            int beforeMergeSize = originals.Count;
            Trace.WriteLine( string.Format( "Merging dups..." ) );
            MergeDups( ref originals );
            Trace.WriteLine( string.Format( "Texts count after merge '{0}'->'{1}'", beforeMergeSize, originals.Count ) );
            Trace.WriteLine( string.Format( " done ({0} s)", ( DateTime.Now - start ).TotalSeconds ) );
          }

          start = DateTime.Now;
          Trace.WriteLine( string.Format( "Parsing files and creating localization file '{0}' with '{1}' items...", translateFile, originals.Count ) );
          DataFolderProcessor.CreateLocalizationFile( originals, translateFile, stopOnWarnings );
          Trace.WriteLine( string.Format( " done ({0} s)", ( DateTime.Now - start ).TotalSeconds ) );

          if ( !string.IsNullOrEmpty( copyFile ) )
          {
            start = DateTime.Now;
            Trace.WriteLine( "Collection localizable non text files from line \"{0}\"...", copyFile );
            FilesListProcessor.CopyFilesFromData( dataFolder, Path.GetDirectoryName( translateFile ), copyFile );
            Trace.WriteLine( string.Format( " done ({0} s)", ( DateTime.Now - start ).TotalSeconds ) );
          }
        }
        else if ( compare )
        {
          if ( !decode )
          {
            bool all_files_exists = true;

            for ( int i = 0; i < 3; i++ )
            {
              if ( !File.Exists( inputArgs[i] ) )
              {
                Trace.WriteLine( "File \"{0}\" is not exists.", inputArgs[i] );
                all_files_exists = false;
              }
            }
            if ( !all_files_exists ) return 1;

            Trace.WriteLine( "Comparing localizations..." );

            var filesOldOriginal = TranslateFileProcessor.CollectLocalizationFiles( inputArgs[0] );
            var filesOldLocalized = TranslateFileProcessor.CollectLocalizationFiles( inputArgs[1] );
            var filesNewOriginal = TranslateFileProcessor.CollectLocalizationFiles( inputArgs[2] );
            Compare( filesOldOriginal, filesOldLocalized, filesNewOriginal, inputArgs[3] );
          }
          else
          {
            if ( !File.Exists( inputArgs[0] ) )
            {
              Trace.WriteLine( String.Format( "File \"{0}\" is not exists.", inputArgs[0] ) );
              return 1;
            }
            NameValueCollection decoded = Decode( inputArgs[0] );

            DataFolderProcessor.CreateLocalizationFile( decoded, inputArgs[1], false );
          }
        }
        else if ( mergedups )
        {
          string file = inputArgs[0];
          string resultFile = inputArgs[1];
          var start = DateTime.Now;
          Trace.WriteLine( string.Format( "Reading file '{0}'...", file ) );
          var originals = TranslateFileProcessor.CollectTexts( file );
          Trace.WriteLine( string.Format( " done ({0} s)", ( DateTime.Now - start ).TotalSeconds ) );

          start = DateTime.Now;
          int beforeMergeSize = originals.Count;
          Trace.WriteLine( string.Format( "Merging dups..." ) );
          MergeDups( ref originals );
          Trace.WriteLine( string.Format( "Texts count after merge '{0}'->'{1}'", beforeMergeSize, originals.Count ) );
          Trace.WriteLine( string.Format( " done ({0} s)", ( DateTime.Now - start ).TotalSeconds ) );

          Trace.WriteLine( string.Format( "Saving file '{0}'...", resultFile ) );
          DataFolderProcessor.CreateLocalizationFile( originals, resultFile, stopOnWarnings );
          Trace.WriteLine( string.Format( " done ({0} s)", ( DateTime.Now - start ).TotalSeconds ) );
        }
        else if ( unmergedups )
        {
          string file = inputArgs[0];
          string resultFile = inputArgs[1];
          var start = DateTime.Now;
          Trace.WriteLine( string.Format( "Reading file '{0}'...", file ) );
          var originals = TranslateFileProcessor.CollectTexts( file );
          Trace.WriteLine( string.Format( " done ({0} s)", ( DateTime.Now - start ).TotalSeconds ) );

          start = DateTime.Now;
          int beforeUnMergeSize = originals.Count;
          Trace.WriteLine( string.Format( "Unmerging dups..." ) );
          UnMergeDups( ref originals );
          Trace.WriteLine( string.Format( "Texts count after unmerge '{0}'->'{1}'", beforeUnMergeSize, originals.Count ) );
          Trace.WriteLine( string.Format( " done ({0} s)", ( DateTime.Now - start ).TotalSeconds ) );

          Trace.WriteLine( string.Format( "Saving file '{0}'...", resultFile ) );
          DataFolderProcessor.CreateLocalizationFile( originals, resultFile, stopOnWarnings );
          Trace.WriteLine( string.Format( " done ({0} s)", ( DateTime.Now - start ).TotalSeconds ) );
        }
      }
      catch ( Exception e )
      {
        Trace.TraceError( "{0}", e.Message );
        return 1;
      }

      return 0;
    }

    private static void Compare( List<LocalizationFile> filesOldOriginal, List<LocalizationFile> filesOldLocalized,
                                List<LocalizationFile> filesNewOriginal, string excelFile )
    {
      var sheet1_old = new List<LocalizationFile>();  // sheet 1: list of original files, that was not modified since previous iteration
      var sheet1_loc  = new List<LocalizationFile>(); // sheet 1: localization
      var sheet2_new = new List<LocalizationFile>();  // sheet 2: modified files
      var sheet2_old = new List<LocalizationFile>();  // sheet 2: old versions of modified files
      var sheet2_loc = new List<LocalizationFile>();  // sheet 2: old localization
      var sheet3 = new List<LocalizationFile>();      // sheet 3: new files

      UnMergeDups(ref filesOldOriginal);
      UnMergeDups(ref filesOldLocalized);
      UnMergeDups(ref filesNewOriginal);

      foreach ( LocalizationFile lf_new in filesNewOriginal )
      {
        if ( lf_new.Filename == @"UI\UIRoot_substitutes_2_captionText.txt" )
          Trace.TraceInformation( @"UI\UIRoot_substitutes_2_captionText.txt" );

        var lf_old = filesOldOriginal.Find( f => f.Filename == lf_new.Filename );
        if ( lf_old == null )
        {
          sheet3.Add( lf_new );
          continue;
        }

        var lf_loc = filesOldLocalized.Find( f => f.Filename == lf_new.Filename );
        if ( lf_loc == null )
          throw new InvalidOperationException( String.Format( "Invalid localization file. Not found element \"{0}\"", lf_new.Filename ) );

        if ( lf_old.ToString() == lf_new.ToString() )
        {
          sheet1_old.Add( lf_new );
          sheet1_loc.Add( lf_loc );
        }
        else
        {
          sheet2_new.Add( lf_new );
          sheet2_old.Add( lf_old );
          sheet2_loc.Add( lf_loc );
        }
      }
      if ( sheet1_old.Count != sheet1_loc.Count )
        throw new Exception( String.Format( "Something going wrong in sheet 1! {0} in original list, {1} in translated list",
                                          sheet1_old.Count, sheet1_loc.Count ) );

      if (mergedups)
      {
        MergeDups(new List<List<LocalizationFile>> { sheet1_old, sheet1_loc });
        MergeDups(new List<List<LocalizationFile>> { sheet2_new, sheet2_old, sheet2_loc });
        MergeDups(new List<List<LocalizationFile>> { sheet3 });
      }

      Trace.WriteLine( String.Format( "Found localization fragments: {0} - not modified, {1} - modified, {2} - added",
                                    sheet1_old.Count, sheet2_new.Count, sheet3.Count ) );

      // Save sheets to Excel-like xml file

      Table table1 = new Table( "not modified", 3, sheet1_old.Count, new[] { "Id", "Text", "Translated text" } );
      for ( int i = 0; i < sheet1_old.Count; i++ )
      {
        table1[0, i] = sheet1_old[i].Filename;
        table1[1, i] = sheet1_old[i].ToString();
        table1[2, i] = sheet1_loc[i].ToString();
      }

      Table table2 = new Table( "modified", 4, sheet2_new.Count, new[] { "Id", "Old Text", "New text", "Translated text" } );
      for ( int i = 0; i < sheet2_new.Count; i++ )
      {
        table2[0, i] = sheet2_new[i].Filename;
        table2[1, i] = sheet2_old[i].ToString();
        table2[2, i] = sheet2_new[i].ToString();
        table2[3, i] = sheet2_loc[i].ToString();
      }

      Table table3 = new Table( "added", 3, sheet3.Count, new[] { "Id", "Text", "Translated text" } );
      for ( int i = 0; i < sheet3.Count; i++ )
      {
        table3[0, i] = sheet3[i].Filename;
        table3[1, i] = sheet3[i].ToString();
      }

      ExcelXmlUtility.WriteFile( excelFile, new[] { table1, table2, table3 } );
      Trace.WriteLine( String.Format( "File {0} created", excelFile ) );
    }

    private static NameValueCollection Decode( string excelFile )
    {
      var tables = ExcelXmlUtility.ReadFile( excelFile );
      var rxKillAllDogs = new Regex( "@+" );
      foreach ( Table table in tables )
      {
        for ( int i = 1; i < table.Rows; i++ ) // ignoring first row [0], because it is header
          for ( int j = 0; j < table.Columns; j++ )
            if ( table[j, i] != null && table[j, i].Contains( "@" ) )
              table[j, i] = rxKillAllDogs.Replace( table[j, i], Environment.NewLine );
      }

      var result = new NameValueCollection();
      // not modified sheet
      for ( int i = 1; i < tables[0].Rows; i++ )
      {
        if ( tables[0][2, i] == null )
          Trace.TraceWarning( "Empty value in file " + tables[0][0, i] );
        result.Add( tables[0][0, i], tables[0][2, i] ?? " " );
      }
      // modified sheet
      for ( int i = 1; i < tables[1].Rows; i++ )
      {
        if ( tables[1][3, i] == null )
          Trace.TraceWarning( "Empty value in file " + tables[0][0, i] );
        result.Add( tables[1][0, i], tables[1][3, i] ?? " " );
      }
      // added sheet
      for ( int i = 1; i < tables[2].Rows; i++ )
      {
        if ( tables[2][2, i] == null )
          Trace.TraceWarning( "Empty value in file " + tables[0][0, i] );
        result.Add( tables[2][0, i], tables[2][2, i] ?? " " );
      }

      return result;
    }

    #region Support tools
    private const string TAGS_PATTERN = @"\$\((.*?)\)|<(.*?)>|\r|\n|\t";
    /// using this function to exclude tag only texts when creating translation xml file
    private static bool IsLocalizableText( string text )
    {
      return !string.IsNullOrEmpty( Regex.Replace( text, TAGS_PATTERN, string.Empty ) );
    }

    private const string SEPARATOR_CHAR = "|";
    private static void MergeDups( ref NameValueCollection originals )
    {
      ///collecting dups
      var dups = new Dictionary<string, List<string>>();

      /// [fileContent, [file1, file2, file3]]
      foreach ( var key in originals.AllKeys )
      {
        var value = originals[key];
        if ( !dups.ContainsKey( value ) )
          dups.Add( value, new List<string>() );

        dups[value].Add( key );
      }

      ///merging dups
      foreach ( var p in dups )
      {
        if ( p.Value.Count == 1 )
          continue;

        p.Value.Sort();
        var newKey = string.Empty;
        foreach ( var file in p.Value )
          originals.Remove( file );

        newKey = string.Join( SEPARATOR_CHAR, p.Value.ToArray() );

        originals.Add( newKey, p.Key );
      }
    }

    private static void UnMergeDups( ref NameValueCollection originals )
    {
      var items = new Dictionary<string, string[]>();

      var separator = new[] { SEPARATOR_CHAR };
      foreach ( var key in originals.AllKeys )
      {
        var keys = key.Split( separator, StringSplitOptions.RemoveEmptyEntries );
        if ( keys.Length == 1 )
          continue;

        items.Add( key, keys );
      }

      foreach ( var p in items )
      {
        var value = originals[p.Key];
        foreach ( var newKey in p.Value )
          originals.Add( newKey, value );

        originals.Remove( p.Key );
      }
    }

    public static void MergeDups(List<List<LocalizationFile>> files)
    {
      var dups = new Dictionary<String, List<String>>();

      var length = files.First().Count;
      if (files.Any(list => list.Count != length))
      {
        throw new InvalidOperationException("Not possible to merge lists with various lengths");
      }

      for (var i = 0; i < files[0].Count; i++)
      {
        var fileName = files[0][i].Filename;
        var fileValue = files.Aggregate("", (current, fileList) => current + fileList.Find(file => file.Filename == fileName));

        if (!dups.ContainsKey(fileValue))
        {
          dups.Add(fileValue, new List<String>());
        }
        dups[fileValue].Add(fileName);
      }

      foreach (var dup in dups.Where(dup => dup.Value.Count > 1))
      {
        foreach (var fileList in files)
        {
          var localDup = dup;
          fileList.Find(file => file.Filename == localDup.Value[0]).Filename = String.Join(SEPARATOR_CHAR, dup.Value.ToArray());
        }
        for (var i = 1; i < dup.Value.Count; i++)
        {
            foreach (var fileList in files)
            {
              var localDup = dup;
              var localI = i;
              fileList.Remove(fileList.Find(file => file.Filename == localDup.Value[localI]));
            }
        }
      }
    }

    public static void UnMergeDups(ref List<LocalizationFile> files)
    {
      var filenames = new Dictionary<String, String[]>();

      var separator = new[] { SEPARATOR_CHAR };
      foreach (var file in files)
      {
        var splittedFilenames = file.Filename.Split(separator, StringSplitOptions.RemoveEmptyEntries);
        if (splittedFilenames.Length == 1)
          continue;

        filenames.Add(file.Filename, splittedFilenames);
      }

      foreach (var filename in filenames)
      {
        var currentFilename = filename;
        var oldFile = files.Find(file => file.Filename == currentFilename.Key);
        foreach (var splittedFilename in currentFilename.Value)
        {
          var newFile = LocalizationFile.ParseXML(oldFile.ToXML());
          newFile.Filename = splittedFilename;
          files.Add(newFile);
        }
        files.Remove(oldFile);
      }
    }
    #endregion
  }
}
