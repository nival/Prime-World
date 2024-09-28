using libdb.Diagnostics;
using System.Drawing;
using EditorLib;
using EditorLib.IO;
using EditorLib.Extensions;
using libdb.DB;
using EditorPlugins.Importer.Texture;
using System.Collections;

namespace EditorPlugins.Importer.UITexture
{
	public class UITextureImporter : Importer<DBTypes.UITexture>
	{
		protected override bool KnownDuration { get { return false; } }

		//protected override string CommandCaption() { return "Import UI Texture"; }

		protected override bool Process( DBPtr<DBTypes.UITexture> resource, IEditorCommonApplication application, bool fast )
		{
			DBTypes.UITexture texture = resource.Get();

			// import texture
			if ( !texture.importOnlyShape )
			{
				TextureImporter textureImporter = new TextureImporter();
				textureImporter.Initialize( resource.DBId, application, false );
				if ( !textureImporter.Import( Context ) )
					return false;
			}

				// import shape
			if ( texture.shapeAlphaThreshold > 0 )
			{
				Log.TraceMessage( "Performing alpha-channel-based texture shape export from {0} to {1}", texture.srcFileName, texture.shapeFileName );

				if ( !application.SourceFileSystem.IsFileExists( texture.srcFileName.FileName ) )
				{
					Log.TraceError( "Cannot open source texture \"{0}\" for resource {1}.", texture.srcFileName, texture.DBId.Name );
					return false;
				}

				Bitmap bitmap = LoadBitmapTexture( application.SourceFileSystem, texture.srcFileName.FileName );

				if ( bitmap == null )
					return false;

				if ( application.FileSystem.FileExists( texture.shapeFileName ) )
					application.FileSystem.DeleteFile( texture.shapeFileName );

				using ( var imageStream = application.FileSystem.CreateFile( texture.shapeFileName ) )
				{
					if ( ReferenceEquals( imageStream, null ) )
						return false;

					MakeAnsSaveShp( imageStream, bitmap, texture.shapeAlphaThreshold );
				}
			}
			Log.TraceMessage( "UITexture imported successfully." );
      
      if( !DataBase.UndoRedoManager.IsCommandStarted )
        DataBase.ChangeCallback( texture.DBId );
			return true;
		}

		private static bool MakeAnsSaveShp( System.IO.Stream output, Bitmap bitmap, int threshold )
		{
			if ( bitmap.Width <= 0 || bitmap.Height <= 0 )
				return false;

			if ( bitmap.Width > 65534 ) // prevent row length overflow and reach marker 0xFFFF
				return false;
			if ( bitmap.Height > 32760 ) // prevent overflow: 4+4+2*h
				return false;

			ushort w = (ushort)bitmap.Width;
			ushort h = (ushort)bitmap.Height;

			ArrayList data = new ArrayList();

				// add sizes
			data.Add( w );
			data.Add( h );

				// write "no info" value as offset for each row
			for ( ushort y = 0; y < h; ++y )
				data.Add( (ushort)0xFFFF );

				// process each row for RLE enconding
			ushort offset = (ushort)(4 + 4 + 2 * h);
			for ( ushort y = 0; y < h; ++y )
			{
				ushort rowOffset = offset;
				
				bool opaque = false;
				ushort len = 0;
				
				int count = 0;

				for ( ushort x = 0; x < w; ++x )
				{
					Color color = bitmap.GetPixel( x, y );
					bool q = ( color.A >= threshold );
					if ( q != opaque )
					{
						data.Add( len );
						++count;
						if ( offset >= 65534 )
						{
							Log.TraceError( "Shape total size overflow!" );
							return false;
						}
						offset += 2;
						opaque = q;
						len = 1;
					}
					else
					{
						if ( len >= 65534 )
						{
							Log.TraceError( "Shape length override (too long rows)!" );
							return false;
						}
						++len;
					}
				}

					// if have added at least one length, add end-marker and write offset to table
				if ( count > 0 )
				{
					data.Add( (ushort)0xFFFF );
					if ( offset >= 65534 )
					{
						Log.TraceError( "Shape total size overflow!" );
						return false;
					}
					offset += 2;
					data[ 2 + y ] = rowOffset;
				}
			}

			Utility.WriteUInt32( output, 0x20504853 ); // 'SHP '
			foreach ( var element in data )
			{
				if ( element.GetType() != typeof( ushort ) )
				{
					Log.TraceError( "Data type error!" );
					return false;
				}
				Utility.WriteUInt16( output, (ushort)element );
			}

			return true;
		}

		private static Bitmap LoadBitmapTexture( SourceFileSystem sourceFileSystem, string sourceFileRelativePath )
		{
			using ( var srcStream = sourceFileSystem.OpenFile( sourceFileRelativePath ) )
			{
				return TgaReader.LoadImage( srcStream );
			}
		}
	}
}
