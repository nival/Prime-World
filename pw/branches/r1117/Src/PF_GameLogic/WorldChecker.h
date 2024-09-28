#pragma once


#include "../System/MemoryStream.h"
#include "../System/ChunklessSaver.h"
#include "System/JobThread.h"


namespace PF_Core
{
class WorldObjectBase;
}


namespace NWorld
{
class PFWorld;
class PointersHolder;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class WorldChecker
{
  PFWorld* world;
  CObj<PointersHolder> pd;
  mutable StrongMT<threading::JobThread> saveCompressThread;

  void SaveWorldObject( int id, PF_Core::WorldObjectBase* object, IBinSaver * _saver ) const;
  CObjectBase* LoadWorldObject( int id, Stream & st );
  void SaveWorld( Stream & st ) const;
  void LoadWorld( Stream & st );
  void SaveIds( Stream & st ) const;
  void LoadIds( Stream & st );
  void SaveObjects( Stream & st ) const;

  void SaveToFile( Stream & st ) const;
  void LoadFromFile( Stream & st );

public:
  WorldChecker(PFWorld* _world)
  {
    NI_ASSERT(_world, "Invalid world!");
    world = _world;
  }

  void Save() const;
  void Save( Stream & worldData ) const;
  void SaveWithoutCompression( Stream & worldData ) const;
  void Load();
  void Load( Stream & worldData );

  void Compress( Stream & stDst, const Stream & stSrc ) const;
  void Uncompress( Stream & stDst, const Stream & stSrc ) const;
};


class SaveCompressThreadJob : public threading::IThreadJob, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( SaveCompressThreadJob, threading::IThreadJob, BaseObjectMT );
public:
  explicit SaveCompressThreadJob( bool _saveToFile );

  virtual void Work( volatile bool & isRunning );

  Stream * GetSourceStream() { return sourceStream; }
  Stream * GetDestStream() { return destStream; }

private:

  CObj<Stream> sourceStream;
  CObj<Stream> destStream;
  bool saveToFile;
};

} // namespace NWorld
