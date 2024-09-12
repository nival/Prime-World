#pragma once

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// a) chunk structure
// b) ptr/ref storage
// system is able to store ref/ptr only for objectbase ancestors
// final save file structure
// -header section list of object types with pointers
// -object data separated in chunks one chunk per object
// c) can replace MemoryStream with specialized objects to increase perfomance

// chunk with index 0 is used for system and should not be used in user code

_interface IProgressHook;

IBinSaver *CreateReadBinSaver( Stream *pStream, IProgressHook *pProgress );
IBinSaver *CreateWriteBinSaver( Stream *pStream, const int version, const bool compress );
