using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

namespace AS3Pprocessor
{
  /// <summary>
  /// represents header template
  /// </summary>
  static class HeaderTemplate
  {
    /// <summary>
    /// fills header file
    /// </summary>
    /// <param name="fileName"></param>
    static public void CreateHeader(String inputFile, String outputFile)
    {
      String fileContent = File.ReadAllText( inputFile );
      String template = global::AS3Pprocessor.Properties.Resources.hTemplate;

      ClassTemplate classTemplate = new ClassTemplate( fileContent );
            
      String classBody = classTemplate.GetClassBody();
      String objectClassBody = classTemplate.GetObjecClasstBody();
    
      if ( String.IsNullOrEmpty( classBody ) && String.IsNullOrEmpty( objectClassBody ) )
        return;

      template = template.Replace( "${ClassBody}", classBody );
      template = template.Replace( "${ObjectClassBody}", objectClassBody );

      IEnumerable<String> forwardClasses = ClassStatistics.GetDependenciesForClass( classTemplate.ClassName );
      forwardClasses = forwardClasses.Union( ClassStatistics.GetDependenciesForClass( classTemplate.ObjectClassName ) ).Distinct();

      String forwardDeclaration = String.Empty;
      foreach ( String classToForward in forwardClasses )
        forwardDeclaration += "class " + classToForward + ";\n";

      template = template.Replace( "${ForwardDeclaration}", forwardDeclaration );

      String includes = String.Empty;

      foreach ( String requiredHeader in classTemplate.RequiredHeaders )
      {
        includes += "#include \"" + requiredHeader + "\"\n";
      }

      template = template.Replace( "&{Includes}", includes );

      File.WriteAllText( outputFile, template.Replace("\r\n", "\n").Replace("\r", "\n"));
    }
  }
}
