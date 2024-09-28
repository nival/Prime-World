#pragma once

#ifndef _SHIPPING
  //#define LOG_PFX
#endif // _SHIPPING

#ifdef LOG_PFX

class PFXLogger
{
  hash_set<nstl::string> loggedNames;

  void LogPFX(const nstl::string& filename, const NewPFXBinaryFile* _pData)
  {
    static NLogg::CChannelLogger _logger( "PFX" );
    static NLogg::CTextFileDumper dumper( &_logger, "PFXStats" );
    dumper.SetFileSuffix(  );

    #define logger( level ) localLog( &_logger, level )

    loggedNames.insert(filename);

    int numNames = loggedNames.size();
    numNames;

    logger( NLogg::LEVEL_DEBUG ) << filename << ':' << endl;

    const int numParticles = _pData->GetParticleCount();
    int numPosKeys = 0, numUVKeys = 0, numAngleKeys = 0, numColorKeys = 0;
    for(int i = 0; i < numParticles; ++i)
    {
      const TParticleTracks& track = _pData->particlesTracks[i];
      numUVKeys  += track.uvTrack.size();
      numPosKeys += track.positionTrack.size();
      numAngleKeys += track.rotationAndScaleTrack.size();
      numColorKeys += track.colorTrack.size();
    }
    logger( NLogg::LEVEL_DEBUG ) << "duration: " << _pData->header.duration << '\t'
             << "numParticles: " << numParticles << '\t'
             << "numPosKeys: "   << numPosKeys   << '\t'
             << "numAngleKeys: " << numAngleKeys << '\t'
             << "numColorKeys: " << numColorKeys << '\t'
             << "numUVKeys: " << numUVKeys << endl;
    
    #undef logger
  }

  PFXLogger(void)
  {
  }

public:

  ~PFXLogger(void)
  {
  }

  void Reset()
  {
    loggedNames.clear();
  }

  void Log(const nstl::string& filename, const NewPFXBinaryFile* _pData)
  {
    if( loggedNames.end() == loggedNames.find(filename) )
      LogPFX(filename, _pData);
  }

  static PFXLogger& Get()
  {
    static PFXLogger instance;

    return instance;
  }
};

#define PFX_LOG(_name_, _data_) PFXLogger::Get().Log(_name_, _data_)
#define PFX_LOGGER_RESET        PFXLogger::Get().Reset()

#else
  #define PFX_LOG(_name_, _data_)
  #define PFX_LOGGER_RESET
#endif