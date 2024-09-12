using System.Diagnostics;
using EditorLib;
using EditorLib.Extensions;
using EditorNative;
using libdb.DB;
using libdb.Diagnostics;

namespace EditorPlugins.Importer.Texture
{
	public class CubeMapImporter : Importer<DBTypes.CubeMap>
	{
		private DBTypes.CubeMap cubeMap;
		private string tempFileName;
		private IEditorCommonApplication application;

		protected override bool KnownDuration { get { return false; } }

		protected override bool Process(DBPtr<DBTypes.CubeMap> resource, IEditorCommonApplication application, bool fast)
		{
			cubeMap = resource.Get();
			this.application = application;
			if ( !application.SourceFileSystem.IsFileExists( cubeMap.srcFileName_0.FileName ) )
			{
				Log.TraceError( "Cannot open source_0 texture \"{0}\" for resource {1}.", cubeMap.srcFileName_0, cubeMap.DBId.Name );
				return false;
			}
			if ( !application.SourceFileSystem.IsFileExists( cubeMap.srcFileName_1.FileName ) )
			{
				Log.TraceError( "Cannot open source_1 texture \"{0}\" for resource {1}.", cubeMap.srcFileName_1, cubeMap.DBId.Name );
				return false;
			}
			if ( !application.SourceFileSystem.IsFileExists( cubeMap.srcFileName_2.FileName ) )
			{
				Log.TraceError( "Cannot open source_2 texture \"{0}\" for resource {1}.", cubeMap.srcFileName_2, cubeMap.DBId.Name );
				return false;
			}
			if ( !application.SourceFileSystem.IsFileExists( cubeMap.srcFileName_3.FileName ) )
			{
				Log.TraceError( "Cannot open source_3 texture \"{0}\" for resource {1}.", cubeMap.srcFileName_3, cubeMap.DBId.Name );
				return false;
			}
			if ( !application.SourceFileSystem.IsFileExists( cubeMap.srcFileName_4.FileName ) )
			{
				Log.TraceError( "Cannot open source_4 texture \"{0}\" for resource {1}.", cubeMap.srcFileName_4, cubeMap.DBId.Name );
				return false;
			}
			if ( !application.SourceFileSystem.IsFileExists( cubeMap.srcFileName_5.FileName ) )
			{
				Log.TraceError( "Cannot open source_5 texture \"{0}\" for resource {1}.", cubeMap.srcFileName_5, cubeMap.DBId.Name );
				return false;
			}

			string size = string.Format("{0}", cubeMap.size).Replace( "_", "" );
			string src_0 = application.SourceFileSystem.GetFullFileName( cubeMap.srcFileName_0.FileName );
			string src_1 = application.SourceFileSystem.GetFullFileName( cubeMap.srcFileName_1.FileName );
			string src_2 = application.SourceFileSystem.GetFullFileName( cubeMap.srcFileName_2.FileName );
			string src_3 = application.SourceFileSystem.GetFullFileName( cubeMap.srcFileName_3.FileName );
			string src_4 = application.SourceFileSystem.GetFullFileName( cubeMap.srcFileName_4.FileName );
			string src_5 = application.SourceFileSystem.GetFullFileName( cubeMap.srcFileName_5.FileName );
			string format = "DXT1";
			switch (cubeMap.pixelFormat)
			{
				case DBTypes.EPixelFormat.RGBA: format = "A8R8G8B8";
				break;
				case DBTypes.EPixelFormat.DXT5: format = "DXT5";
				break;
				default: break;
			};

			tempFileName = System.IO.Path.GetTempFileName();
			string args = string.Format("-importFaceXPos:{0} -importFaceXNeg:{1} -importFaceYPos:{2} -importFaceYNeg:{3} -importFaceZPos:{4} -importFaceZNeg:{5} -exit -exportMipChain -exportCubeDDS  -perLevelMipFilterScale:3.0 -exportFilename:\"{6}\" -exportSize:{7} -exportPixelFormat:{8}", src_0, src_1, src_2, src_3, src_4, src_5, tempFileName, size, format);

			ProcessStartInfo atiStartInfo = new ProcessStartInfo("CubeMapGen.exe", args);
			atiStartInfo.CreateNoWindow = false;
			atiStartInfo.UseShellExecute = false;
			atiStartInfo.RedirectStandardOutput = false;
			atiStartInfo.RedirectStandardError = false;


			atiStartInfo.WorkingDirectory = System.Environment.CurrentDirectory;
			Process atiProcess = new Process();
			atiProcess.StartInfo = atiStartInfo;
			atiProcess.EnableRaisingEvents = true;

			atiProcess.Start();
			atiProcess.WaitForExit();
			if ( atiProcess.ExitCode != 0 )
			{
				Log.TraceError( string.Format( "ATI CubeMap generator failed with arguments: {0}", args ));
				return false;
			}

			if ( application.FileSystem.FileExists( cubeMap.textureFileName ) )
			{
				application.FileSystem.DeleteFile( cubeMap.textureFileName );
			}

			libdb.IO.FileUtils.CopyRealFile( tempFileName, application.FileSystem, cubeMap.textureFileName );

			if ( System.IO.File.Exists( tempFileName ) )
			{
				System.IO.File.Delete( tempFileName );
			}

			application.SourceFileSystem.UpdateChecksum( cubeMap.srcFileName_0 );
			application.SourceFileSystem.UpdateChecksum( cubeMap.srcFileName_1 );
			application.SourceFileSystem.UpdateChecksum( cubeMap.srcFileName_2 );
			application.SourceFileSystem.UpdateChecksum( cubeMap.srcFileName_3 );
			application.SourceFileSystem.UpdateChecksum( cubeMap.srcFileName_4 );
			application.SourceFileSystem.UpdateChecksum( cubeMap.srcFileName_5 );
			EditorRender.ResetTexture(cubeMap.textureFileName);
      
      if(!DataBase.UndoRedoManager.IsCommandStarted)
			  DataBase.ChangeCallback(cubeMap.DBId);

			return true;
		}
	}
}
