using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

namespace AS3Pprocessor
{
  static class NativeClassesGenerator
  {
    private const String GENERATED_NAME = "GeneratedClasses";
    
    public static void GenerateHeaders()
    {
      //need this for error reporting
      ClassStatistics.BuildStatistics();

      String curDir = Directory.GetCurrentDirectory();
      foreach(String fileName in Directory.GetFiles(curDir, "*.as", SearchOption.AllDirectories))
      {
        String outputFile = Path.ChangeExtension( fileName, ".h" ).Replace(curDir,curDir+"\\"+GENERATED_NAME + "\\");
        Directory.CreateDirectory( Path.GetDirectoryName(outputFile));
        HeaderTemplate.CreateHeader( fileName, outputFile );
      }

      DupmDescriptionFiles();

      ClassStatistics.DumpErrors();
    }

    //TODO rewrite it. seems messy
    private static void DupmDescriptionFiles()
    {
      String curDir = Directory.GetCurrentDirectory();
      string generatedDir = curDir + "\\" + GENERATED_NAME + "\\";
      String sources = String.Empty;
      List<String> includes = new List<String>();

      foreach ( String dir in Directory.GetDirectories( generatedDir ) )
      {
        List<String> headers = new List<String>();

        String dirName = dir.Replace( generatedDir, "" );
        sources += "sources['" + dirName + "']";
        sources += " = [\n";

        foreach ( String file in Directory.GetFiles( dir, "*.h", SearchOption.AllDirectories ) )
        {
          String shortFilePath = file.Replace( generatedDir, "" );
          headers.Add( shortFilePath );
          sources += "  '" + shortFilePath + "',\n";
        }
        sources += "]\n";

        //write all included here
        String headersContent = String.Empty;
        foreach ( String header in headers )
          headersContent += "#include \"" + header + "\"\n";

        if ( String.IsNullOrEmpty( headersContent ) )
          continue;

        headersContent = "#pragma once\n" + headersContent;

        String includeFile = dir.Replace( generatedDir, "" ) + "Include.h";
        includes.Add( includeFile );
        File.WriteAllText( generatedDir + includeFile, headersContent );
      }
           
      string componentContent = global::AS3Pprocessor.Properties.Resources.HeadersComponent.Replace( "${Sources}", sources );
    
      String includeContent = String.Empty;
      foreach (String include in includes)
        includeContent += "  '" + include + "',\n";
      componentContent = componentContent.Replace( "${BuiltinsInclude}", includeContent );

      //write component here
      File.WriteAllText( generatedDir + "all.component", componentContent.Replace( "\r\n", "\n" ).Replace( "\r", "\n" ) );

      //avm includes like ScriptObject and such
      File.WriteAllText( generatedDir + "PlayerGlobalIncludes.h", global::AS3Pprocessor.Properties.Resources.requiredInclude );
    }

  }
}
