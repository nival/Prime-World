using System;
using System.Collections.Generic;
using System.Text;

namespace EditorLib.Wizards
{
  public class ImportWizardAttribute : Attribute
  {
    public readonly string extension = string.Empty;

    public ImportWizardAttribute( string ext )
    {
      extension = ext;
    }
  }
}
