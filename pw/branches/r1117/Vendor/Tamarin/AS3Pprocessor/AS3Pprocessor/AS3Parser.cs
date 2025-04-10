using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

namespace AS3Pprocessor
{
  /// <summary>
  /// AS3 files parser
  /// </summary>
  class AS3Parser
  {
    private const string NATIVE = "native";
    private const string NATIVE_ATTRIBUTE = "[native(";
    private const string STATIC = "static ";

    /// <summary>
    /// Searches for natives functions and stores that info in FileStatistic
    /// </summary>
    /// <param name="fileName"></param>
    /// <returns></returns>
    public static FileStatistic ParseFile(String fileName)
    {
      FileStatistic statistic = new FileStatistic();
      
      foreach (String line in File.ReadAllLines(fileName))
      {
        if (!line.Contains( NATIVE ) || line.Contains( NATIVE_ATTRIBUTE ) )
          continue;

        if ( line.Contains( STATIC ) )
          statistic.StaticNativeMethodsCount++;
        else
          statistic.NativeMethodsCount++;
      }
      return statistic;
    }
  
  }
}
