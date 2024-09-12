#pragma once
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace Types
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct HashCheck
{
	static bool Check()
	{
		static const char* hashFileName = "Types.md5";
		static const unsigned char hash[] = { 0x94, 0x86, 0x8D, 0x13, 0x72, 0x3D, 0x38, 0xDC, 0x5C, 0xB2, 0x2E, 0x54, 0x05, 0x09, 0xDF, 0xF5 };
		static const int hashLength = sizeof( hash ) / sizeof( hash[0] );

		CObj<Stream> pStream = RootFileSystem::OpenFile( hashFileName, FILEACCESS_READ, FILEOPEN_OPEN_EXISTING );
		NI_DATA_VERIFY( IsValid( pStream ), NStr::StrFmt( "Cannot open file \"%s\" with database descriptor", hashFileName ), return false );
		NI_DATA_VERIFY( pStream->GetSize() == hashLength, NStr::StrFmt( "Invalid size (%d, expected %d) of file \"%s\" with database descriptor", pStream->GetSize(), hashLength, hashFileName ), return false );
		
		static unsigned char buffer[hashLength];
		const int readen = pStream->Read( buffer, hashLength );
		NI_DATA_VERIFY( readen == hashLength, NStr::StrFmt( "Cannot read from file \"%s\" with database descriptor", hashFileName ), return false );

		for( int i = 0; i < hashLength; ++i )
		{
			NI_DATA_VERIFY( buffer[i] == hash[i], "Database descriptor in binary file is out of date", return false );
		}

		return true;
	}
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}; // namespace $(NameSpace)

