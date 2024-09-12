#pragma once

_interface IPointerHolder;

namespace NCore
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class WorldCommand;
_interface IObjectsHolder;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PackedWorldCommand : public CObjectBase
{
  OBJECT_METHODS( 0x1474B2C0, PackedWorldCommand );
public:
  PackedWorldCommand() {}
  PackedWorldCommand( WorldCommand *pCmd, IPointerHolder *pPtr, int cid, DWORD time );

  WorldCommand *GetWorldCommand( IPointerHolder *pPtr );
  
  DWORD GetCommandId();
  int GetCommandSize() const;

  Stream* GetStream() { return &serializedCmd; }

  int ClientId() const { return clientId; }
  DWORD TimeSent() const { return timeSent; }

private:
  ZDATA
  ZNOPARENT( CObjectBase )
  int clientId;
  DWORD timeSent;
  MemoryStream serializedCmd;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&clientId); f.Add(3,&timeSent); f.Add(4,&serializedCmd); return 0; }
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}; // namespace NCore
