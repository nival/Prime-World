using System.IO;
using System.Drawing;
using EditorLib.IO;
using EditorPlugins.Importer.Texture;

namespace EditorPlugins.Importer.Texture
{
	public class DdsImage
	{
		static public Bitmap Load( Stream ddsStream )
		{
			DdsFile file = new DdsFile();
			file.Load( ddsStream );
			Bitmap image = new Bitmap( file.GetWidth(), file.GetHeight() );
			byte[] rawData = file.GetPixelData();
			for ( int y = 0; y < file.GetHeight(); y++ )
			{
				for ( int x = 0; x < file.GetWidth(); x++ )
				{
					int pixelOffset = (y * file.GetWidth() * 4) + (x * 4);
					image.SetPixel(
						x,
						y,
						System.Drawing.Color.FromArgb(
							rawData[pixelOffset + 3],
							rawData[pixelOffset + 0],
							rawData[pixelOffset + 1],
							rawData[pixelOffset + 2]
						)
					);
				}
			}
			return image;
		}

		static public bool Save( RootFileSystem fileSystem, DBTypes.Texture texture, Bitmap bitmap )
		{
			if ( fileSystem.FileExists( texture.textureFileName ) )
			{
				fileSystem.DeleteFile( texture.textureFileName );
			}

			using ( var imageStream = fileSystem.CreateFile( texture.textureFileName ) )
			{
				if ( !ReferenceEquals( imageStream, null ) )
				{
					DdsFileFormat format = DdsFileFormat.DDS_FORMAT_INVALID;

					switch ( texture.pixelFormat )
					{
					//case DBTypes.EPixelFormat.Grayscale:
					//  format = DdsFileFormat.DDS_FORMAT_A8;
					//  break;
					//case DBTypes.EPixelFormat.RGB:
					//  format = DdsFileFormat.DDS_FORMAT_R8G8B8;
					//  break;
					case DBTypes.EPixelFormat.RGBA:
						format = DdsFileFormat.DDS_FORMAT_A8R8G8B8;
						break;
					case DBTypes.EPixelFormat.DXT1:
						format = DdsFileFormat.DDS_FORMAT_DXT1;
						break;
					case DBTypes.EPixelFormat.DXT5:
						format = DdsFileFormat.DDS_FORMAT_DXT5;
						break;
					}

					DdsFile dds = new DdsFile();
					dds.Save( imageStream, bitmap, format, 13 );
					return true;
				}
				else
				{
					return false;
				}
			}
		}

		static public bool Save( RootFileSystem fileSystem, string textureFileName, DdsFileFormat format, int mipLevels, Bitmap bitmap )
		{
			if ( fileSystem.FileExists( textureFileName ) )
				fileSystem.DeleteFile( textureFileName );

			Stream file = fileSystem.CreateFile( textureFileName );
			if ( file == null )
				return false;

			DdsFile dds = new DdsFile();
			dds.Save( file, bitmap, format, mipLevels );

			file.Close();
			return true;
		}
	}
}