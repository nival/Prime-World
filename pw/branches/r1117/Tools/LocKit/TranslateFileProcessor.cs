using System.Collections.Generic;
using System.Collections.Specialized;
using System.Xml.Linq;
using System;
using LocKit.Localization;

namespace LocKit
{
  static class TranslateFileProcessor
  {
    public static NameValueCollection CollectTexts( string filePath )
    {
      var result = new NameValueCollection();
      foreach (var lfile in CollectLocalizationFiles(filePath))
      {
        result.Add(lfile.Filename, lfile.ToString());
      }

      return result;
    }

    public static List<LocalizationFile> CollectLocalizationFiles(string filePath)
    {
      var xD = XDocument.Load(filePath, LoadOptions.PreserveWhitespace);
      if (xD.Root == null)
        throw new Exception(String.Format("File {0} have not root node", filePath));

      var result = new List<LocalizationFile>();
      foreach (var element in xD.Root.Elements())
      {
        result.Add(LocalizationFile.ParseXML(element));
      }

      return result;
    }

  }
}
