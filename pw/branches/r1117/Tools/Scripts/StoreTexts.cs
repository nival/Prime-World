/*
#ref EditorNative.dll
*/
using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Reflection;
using EditorLib;
using EditorLib.IO;
using EditorLib.Plugin;
using EditorNative;
using libdb.DB;
using libdb.Diagnostics;
using libdb.IO;

namespace Scripts
{
	public class StoreTexts
	{
    public IEnumerable Main( IEditorCommonApplication application, string[] parameters )
    {
      EditorUIScene.StoreTextsCache( parameters[0] );

      yield return true;
    }
	}
}
