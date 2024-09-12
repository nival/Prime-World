using libdb.Diagnostics;
using System.IO;
using EditorLib;
using EditorLib.Extensions;
using libdb.DB;
using libdb.IO;
using DBTypes;

namespace EditorPlugins.Importer.Mesh
{
	public sealed class FaceFXImporter : StructImporter<DBTypes.Skeleton, DBTypes.FaceFX>
	{
		protected override bool KnownDuration { get { return false; } }
		//protected override string CommandCaption() { return "Import Face FX"; }

		protected override bool Process( FaceFX importStruct, DBPtr<Skeleton> resource, IEditorCommonApplication application, bool fast )
		{
			Progress( string.Format( "Import Face FX animation from \"{0}\"", resource.DBId.Name ) );

			var faceFx = importStruct;

			if ( string.IsNullOrEmpty( faceFx.srcFileName.FileName ) )
			{
				Log.TraceError( "Face FX srcFileName not specified in resource \"{0}\"", resource.DBId.Name );
				return false;
			}

			string srcFileName = FileUtils.FixFileName( application.SourceFileSystem.GetFullFileName( faceFx.srcFileName.FileName ) );
			if ( !File.Exists( srcFileName ) )
			{
				Log.TraceError( "Source file \"{0}\" is not exist.", srcFileName );
				return false;
			}

			application.FileSystem.AddFile( srcFileName, faceFx.fxaFileName );

			Log.TraceMessage( "Export successful." );
			return true;
		}
	}

	public sealed class FaceFXDBAnimatedSceneComponentImporter : StructImporter<DBTypes.DBAnimatedSceneComponent, DBTypes.FaceFX>
	{
		protected override bool KnownDuration { get { return false; } }
		//protected override string CommandCaption() { return "Import Face FX"; }

		protected override bool Process(FaceFX importStruct, DBPtr<DBAnimatedSceneComponent> resource, IEditorCommonApplication application, bool fast)
		{
			Progress(string.Format("Import Face FX animation from \"{0}\"", resource.DBId.Name));

			var faceFx = importStruct;

			if ( string.IsNullOrEmpty( faceFx.srcFileName.FileName ) )
			{
				Log.TraceError("Face FX srcFileName not specified in resource \"{0}\"", resource.DBId.Name);
				return false;
			}

			string srcFileName = FileUtils.FixFileName( application.SourceFileSystem.GetFullFileName( faceFx.srcFileName.FileName ) );
			if (!File.Exists(srcFileName))
			{
				Log.TraceError("Source file \"{0}\" is not exist.", srcFileName);
				return false;
			}

			application.FileSystem.AddFile(srcFileName, faceFx.fxaFileName);

			Log.TraceMessage("Export successful.");
			return true;
		}
	}
}
