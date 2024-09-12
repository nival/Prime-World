/*
#about Экспорт данных для социального клиента
#ref PF_Types.DBTypes.dll
#ref SocialTypes.DBTypes.dll
#ref PF_EditorC.exe
#ref EditorPlugins.dll
#ref EditorNative.dll
 */
using System;
using System.Collections;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Text;
using System.Text.RegularExpressions;
using System.Xml;
using EditorLib;
using EditorLib.IO;
using EditorLib.Plugin;
using libdb.DB;
using libdb.Diagnostics;
using libdb.IO;
using DBTypes;
using System.Windows.Forms;


namespace Utils
{
  public class Png2Dds
  {
    public IEnumerable Main( IEditorCommonApplication app, string[] args )
    {
        List<string> files = new List<string>();
        foreach (string f in args)
        {
            if (Directory.Exists(f))
            {
                files.AddRange(Directory.GetFiles(f));
            }
            else
                if (File.Exists(f))
                {
                    files.Add(f);
                }

        }

        foreach (var f in files)
        {
            var bitmap = new System.Drawing.Bitmap(app.FileSystem.OpenFile(f));
            var output = app.FileSystem.CreateFile(Path.ChangeExtension(f, "dds"));
            int fType = 3;
            float fParam1 = 4.0f;
            float fParam2 = 1.0f;
            float fParam3 = 3.0f;
            EditorNative.TextureImporter.TextureImporter.Import(bitmap, output, EPixelFormat.RGBA,
          false, true, 0, null, fType, fParam1, fParam2, fParam3);
        }
        yield return true;
    }
  }
}
