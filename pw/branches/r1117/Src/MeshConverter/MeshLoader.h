#pragma once



//bool ConvertGeometry( const nstl::string& mayaFileName, const nstl::string& h6fileName )
//{
//	FileStream mayaFileStream( mayaFileName, FILEACCESS_READ, FILEOPEN_OPEN_EXISTING );
//	NI_VERIFY( mayaFileStream.IsOk(), "Cannot open file for reading: " + mayaFileName, return false );
//	const unsigned char* pMayaBuffer = reinterpret_cast<const unsigned char*>( mayaFileStream.GetBuffer() );
//	//////////////////////////////////////////////////////////////////////////
//	FileStream h6FileStream( h6fileName, FILEACCESS_WRITE, FILEOPEN_CREATE_NEW );
//	NI_VERIFY( h6FileStream.IsOk(), "Cannot create file for writing: " + h6fileName, return false );
//	//////////////////////////////////////////////////////////////////////////
//	const MayaStaticMeshFileHeader* pMayaHeader = reinterpret_cast<const MayaStaticMeshFileHeader*>(pMayaBuffer);
//	const MayaVertexStride* pVertex = reinterpret_cast<const MayaVertexStride*>(pMayaBuffer + sizeof(MayaStaticMeshFileHeader) );
//	DummyAllocator allocator(1024*1024);
//	H6GeometryFileHeader* pH6GeometryFileHeader = new(&allocator) H6GeometryFileHeader();
//	unsigned int fragmentCount = 0;
//	pH6GeometryFileHeader->fragments.resize(fragmentCount, &allocator);
//	//////////////////////////////////////////////////////////////////////////
//	h6FileStream.Close();
//	mayaFileStream.Close();
//	return true;
//}
