#include "TamarinPCH.h"
#include "SoundData.h"

#include "swf_parse.h"
#include <math.h>

#include "../../../Sound/SoundScene.h"

/*
rate5512Hz = 0,
rate11025Hz = 1,
rate22050Hz = 2,
rate44100Hz = 3
*/
int SoundRate::GetRate( ERate rate )
{
  static int rates[] = {5512, 11025, 22050, 44100};

  NI_VERIFY(rate>=0 && rate<4, "wrong rate", return rates[1]);

  return rates[rate];
}

namespace flash
{
  /*//ID for this sound.
  UI16 soundId;

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

  //The sound data; varies by  format.
  vector<UI8> soundData;*/


void SoundData::Load( SwfStreamReader & streamReader, TagInfo & tagInfo )
{
//   UI32 parserPos = streamReader.GetPos();
//   streamReader.clearBitreader(true);
//   soundFormat = (SoundFormat::EFormat)streamReader.readUBits(4);
//   soundRate = (SoundRate::ERate)streamReader.readUBits(2);
//   sampleSize = streamReader.readUBits(1);
//   isStereo = streamReader.readUBits(1);
//   streamReader.clearBitreader(true);
// 
//   NI_VERIFY(soundFormat==SoundFormat::UncompressedLittleEndian, "we dont support other formats", return);
// 
//   soundSampleCount = streamReader.readUI32();
// 
//   int bytesToRead = soundSampleCount;
//   bytesToRead = isStereo? bytesToRead*2 :bytesToRead;
//   bytesToRead = sampleSize? bytesToRead*2 :bytesToRead;
// 
//   parserPos = streamReader.GetPos();
//   int descSize = parserPos - tagInfo.parserPos;
//   
//   NI_VERIFY(bytesToRead  == (tagInfo.tagLen - descSize), "Wrong data size?", bytesToRead  = (tagInfo.tagLen - descSize));
// 
//   vector<UI8> soundData(bytesToRead);
//   streamReader.readBuffer(&(soundData[0]), bytesToRead);
// 
//   //post init stuff
// 
//   sampleSize = sampleSize? 16: 8;
// 
//   simpleSound = NSoundScene::CreateSimpleSoundFromData(soundData, SoundRate::GetRate(soundRate), isStereo, sampleSize);
//   //NI_ASSERT( simpleSound, "sound was not created!")
}
}

NI_DEFINE_REFCOUNT(flash::SoundData);

