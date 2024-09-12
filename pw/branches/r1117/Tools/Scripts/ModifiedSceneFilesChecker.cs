/*
#about Проверка SVN-статуса файлов сцены
#ref EditorNative.dll
#ref EditorPlugins.dll
#ref PF_Types.DBTypes.dll
#ref PF_Editor.exe
#ref mayaexeinteraction.dll
#ref sharpsvn.dll
*/

using System.Collections;
using System.Collections.ObjectModel;
using System.IO;
using EditorLib;
using libdb.Diagnostics;
using SharpSvn;
using Tools.MayaExeInteraction;

namespace Scripts
{
	public class ModifiedSceneFilesValidator
	{
		public IEnumerable Main(IEditorCommonApplication app)
		{
			SvnClient client = new SvnClient();

			bool failed = false;
			foreach (string file in app.SourceFileSystem.GetFileNames( "/", "*.mb", SearchOption.AllDirectories ))
			{
				if ( file.Substring( 1, 4 ).ToLower() == "test" )
					continue;

				string afile = app.SourceFileSystem.GetFullFileName( file );
				Collection<SvnStatusEventArgs> st = null;
				bool notVersioned = false;
				try
				{
					client.GetStatus( afile, out st );
				}
				catch (SvnWorkingCopyException ex)
				{
					Log.TraceWarning( "Something wrong with SVN status of this file: {0}. But i'll check it. Details: {1}", afile, ex.ToString() );
					notVersioned = true;
				}
        //if ( notVersioned ||
        //     (st != null &&
        //      st.Count > 0 &&
        //      st[0].LocalContentStatus != SvnStatus.Deleted &&
        //      st[0].LocalContentStatus != SvnStatus.Ignored &&
        //      st[0].LocalContentStatus != SvnStatus.Missing &&
        //      st[0].LocalContentStatus != SvnStatus.Normal &&
        //      st[0].LocalContentStatus != SvnStatus.None) )
        //{
        //  Log.TraceMessage( "checking {0}", afile );
        //  if ( MayaOperationsUtility.LaunchSceneChecker( afile ) )
        //    continue;
        //  failed = true;
        //}
			}
			
			yield return !failed;
		}
	}
}