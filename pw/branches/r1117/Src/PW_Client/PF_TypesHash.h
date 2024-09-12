#pragma once
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace PF_Types
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct HashCheck
{
	static bool Check()
	{
		static const char* hashFileName = "PF_Types.md5";
		static const unsigned char hash[] = { 0xBD, 0xE3, 0xD7, 0xA0, 0xC8, 0xAD, 0xB2, 0x07, 0xC3, 0x1C, 0x6E, 0xB6, 0x9B, 0x13, 0x20, 0x3C };
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

