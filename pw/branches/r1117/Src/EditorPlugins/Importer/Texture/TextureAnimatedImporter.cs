using System.Diagnostics;
using System.Drawing;
using EditorLib;
using EditorLib.Extensions;
using EditorLib.IO;
using EditorNative;
using EditorPlugins.Importer.Texture;
using libdb.DB;
using libdb.Diagnostics;
using System.Collections.Generic;
using System.Globalization;
using libdb.IO;
using System.IO;

namespace EditorPlugins.Importer.TextureAnimated
{
	public class TextureAnimatedImporter : Importer<DBTypes.TextureAnimated>
	{

		protected override bool KnownDuration { get { return false; } }

		protected override bool Process( DBPtr<DBTypes.TextureAnimated> resource, IEditorCommonApplication application, bool fast )
		{
			DBTypes.TextureAnimated texture = resource.Get();
			if ( texture.animCount < 1 )
				texture.animCount = 1;

			// import the first texture
			FileNameCounter srcFileNames = new FileNameCounter( texture.srcFileName.FileName, texture.animCount );
			FileNameCounter dstFileNames = new FileNameCounter( texture.textureFileName, texture.animCount );

			for ( int index = srcFileNames.Min; index < srcFileNames.Max; ++index )
			{
				if ( !TextureImporter.ImportImage( TextureImporter.LoadImage( application.SourceFileSystem, srcFileNames.Format( index ) ), application.FileSystem, dstFileNames.Format( index ), texture ) )
					return false;
			}

      for ( int index = srcFileNames.Min; index < srcFileNames.Max; ++index )
      {
        EditorRender.ResetTexture( dstFileNames.Format( index ) );
      }

			return true;
		}
	}
}
