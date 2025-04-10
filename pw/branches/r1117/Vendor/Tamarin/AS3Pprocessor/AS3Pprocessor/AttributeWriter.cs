using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;


namespace AS3Pprocessor
{
  class AttributeWriter
  {
    //Pattern
    //[native(cls="ArrayClass", instance="ArrayObject", methods="auto")]

    private const String ATTRIBUTE_SEARCH_PATTERN = "[native(";
    private const String CLASS_SEARCH_PATTERN = " class ";

    public static void WriteAttributes(FileStatistic statistic, String fileName)
    {
      //do we have natives?
      if ( statistic.StaticNativeMethodsCount + statistic.NativeMethodsCount == 0 )    return;

      List<String> lines = new List<String> (File.ReadAllLines(fileName));

      for ( int i = 0; i < lines.Count; i++ )
      {
        String line = lines[i];
        if ( line.Contains( ATTRIBUTE_SEARCH_PATTERN ) )
        {
          lines[i] = BuildAttributeString( statistic, fileName );
          break;
        }

        if ( line.Contains( CLASS_SEARCH_PATTERN ) )
        {
          lines.Insert( i, BuildAttributeString( statistic, fileName ) );
          break;
        }
      }

      File.WriteAllLines(fileName, lines.ToArray());

      Console.WriteLine( fileName + " was processed" );
    }

    private static String BuildAttributeString( FileStatistic statistic, String fileName )
    {
      //sample
      //[native(cls="ArrayClass", instance="ArrayObject", methods="auto")]

      String asClassName = Path.GetFileNameWithoutExtension( fileName );
      String attrLine = "    [native(";

      //if (statistic.StaticNativeMethodsCount>0)
      attrLine += "cls=\"" + asClassName + "Class\", ";

      //if ( statistic.NativeMethodsCount> 0 )
      attrLine += "instance=\"" + asClassName + "Object\", ";

      attrLine+= "methods=\"auto\")]";
      
      return attrLine;
    }
  }
}
