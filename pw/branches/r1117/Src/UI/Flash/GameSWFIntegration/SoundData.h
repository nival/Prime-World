#pragma once

#include "SwfTypes.h"


namespace NSoundScene
{
  _interface ISimpleSound;
}



namespace SWFParser
{
  struct TagInfo;
};

namespace SoundFormat
{
  enum EFormat
  {
    UncompressedNativeEndian = 0, //native-endian 0
    ADPCM = 1, 
    MP3 = 2, 
    UncompressedLittleEndian = 3,// little-endian 3 
    Nellymoser16 = 4, //16 kHz 
    Nellymoser8 = 5, //8 kHz 
    Nellymoser = 6, 
    Speex = 11 
  };
}

namespace SoundRate
{
  enum ERate
  {
    rate5512Hz = 0,
    rate11025Hz = 1,
    rate22050Hz = 2,
    rate44100Hz = 3
  };

  int GetRate(ERate rate);
}

namespace flash
{

  class SwfStreamReader;


  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  class SoundData: public BaseObjectST
  {
    NI_DECLARE_REFCOUNT_CLASS_1( SoundData, BaseObjectST );
  
    //ID for this sound.
    //UI16 soundId; already parsed

    // UB[4] Format of SoundData.
    SoundFormat::EFormat soundFormat;  
    
    //UB[2] The sampling rate. This is      ignored for Nellymoser and Speex codecs.     5.5kHz is not allowed for MP3.
    SoundRate::ERate soundRate;  

    //UB[1] Size of each sample. This parameter only pertains to uncompressed formats.  0 = snd8Bit   1 = snd16Bit
    int sampleSize; 

    // UB[1] Mono or stereo sound  This is ignored for Nellymoser and Speex. 0 = sndMono 1 = sndStereo
    bool isStereo; 
    
    //Number of samples. Not  ffected by mono/stereo setting;
    //for stereo sounds this is the number of sample pairs.
    UI32 soundSampleCount; 

    CObj<NSoundScene::ISimpleSound> simpleSound;
    //The sound data; varies by  format.
    //vector<UI8> soundData;
  
    public:
    SoundData(){}
    void Load( SwfStreamReader & streamReader, TagInfo & tagInfo);
    NSoundScene::ISimpleSound * GetSimpleSound() {return simpleSound;}
  };

}