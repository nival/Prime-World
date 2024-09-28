#include "StdAfx.h"
#include "CommandSerializer.h"
#include "GameCommand.h"
#include "WorldCommand.h"

#include "../System/ChunklessSaver.h"
#include "../System/StrProc.h"

namespace NCore
{
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const int N_ID_SIZE = 4; // == sizeof(int);
const int N_SIZE_LIMIT = 1024;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void WriteCommandToStream( CObjectBase *pPacket, Stream *pStream, IPointerHolder *pPointerHolder )
{
	NI_VERIFY( pPacket, "Invalid command", return );
	NI_VERIFY( pStream, "Invalid stream", return );

	int nID = NObjectFactory::GetObjectTypeID( pPacket );
	if ( nID != -1 )
	{
		pStream->Write( &nID, N_ID_SIZE );
		CObj<IBinSaver> pSaver = CreateChunklessSaver( pStream, pPointerHolder, false );
		pSaver->AddPolymorphicBase( 1, pPacket );
		return;
	}
	NI_ALWAYS_ASSERT( NI_STRFMT( "trying to send unregistered command %s!", pPacket->GetObjectTypeName() ) );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CObjectBase *ReadCommandFromStream( Stream *pStream, IPointerHolder *pPointerHolder )
{
	NI_VERIFY( pStream, "Invalid stream", return 0 );

	int nID = 0;
	pStream->Seek( 0, SEEKORIGIN_BEGIN );
	pStream->Read( &nID, N_ID_SIZE );
	CObjectBase *pCmd = NObjectFactory::MakeObject( nID );
	if ( pCmd )
	{
		CObj<IBinSaver> pSaver = CreateChunklessSaver( pStream, pPointerHolder, true, N_SIZE_LIMIT );
		pSaver->AddPolymorphicBase( 1, pCmd );
    if (pSaver->GetError())
      return 0;
		return pCmd;
	}
	NI_ALWAYS_ASSERT( NI_STRFMT( "Reading command with invalid ID %x!", nID ) );
	pStream->Seek( pStream->GetSize() - N_ID_SIZE, SEEKORIGIN_BEGIN ); //skip the rest
	return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//void WriteNetPacketToStream( CNetPacket *pPacket, Stream *pStream )
//{
//	WriteCommandToStream( CastToObjectBase( pPacket ), pStream, 0 );
//}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//CNetPacket *ReadNetPacketFromStream( Stream *pStream )
//{
//	CObjectBase *pObj = ReadCommandFromStream( pStream, 0 );
//	return checked_cast<CNetPacket*>( pObj );
//}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void WriteWorldCommandToStream( WorldCommand *pPacket, Stream *pStream, IPointerHolder *pPointerSerialization )
{
	WriteCommandToStream( CastToObjectBase( pPacket ), pStream, pPointerSerialization );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
WorldCommand *ReadWorldCommandFromStream( Stream *pStream, IPointerHolder *pPointerSerialization )
{
	CObjectBase *pObj = ReadCommandFromStream( pStream, pPointerSerialization );
	return checked_cast<WorldCommand*>( pObj );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}