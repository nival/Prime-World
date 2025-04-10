using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;


namespace AS3Pprocessor
{
  class Program
  {
    static void Main( string[] args )
    {
      NativeClassesGenerator.GenerateHeaders();

      //foreach(String fileName in Directory.GetFiles(Directory.GetCurrentDirectory(), "*.as", SearchOption.AllDirectories))
      //{
      //  AttributeWriter.WriteAttributes( AS3Parser.ParseFile( fileName ), fileName );
      //}
    }
  }
}
