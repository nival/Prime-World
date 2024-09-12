#include "stdafx.h"

#include "fxresource.h"


namespace Render
{
	//bool FXResource::LoadFromFile( const nstl::string& _filename )
	//{
	//	FileStream fileStream( _filename, FILEACCESS_READ, FILEOPEN_OPEN_EXISTING );
	//	NI_VERIFY( fileStream.IsOk(), "Cannot open file with some data", return false );

	//	const int fileSize = fileStream.GetSize();
	//	pPFXData = static_cast<const PFXBinaryFileData*>(_aligned_malloc(fileSize, 16));
	//	fileStream.Read( (void*)pPFXData, fileSize );

	//	fileStream.Close();
	//	bLoaded = true;
	//	return true;
	//}
};