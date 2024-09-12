#include "stdafx.h"

#include "sampler.h"
#include "smartrenderer.h"
#include "renderresourcemanager.h"
#include "GlobalMasks.h"
#include "texture.h"
// #include "../System/Crc32Checksum.h"


namespace Render
{
  void Sampler::GetSignificantPart(SignificantPart *_res) const
  {
    _res->samplerState = samplerState;
    _res->pTexture = pTexture ? ::Get( pTexture->GetDXTexture() ) : 0;
    _res->multiplier = HasModifiers() ? multiplier : HDRColor::WHITE();
    _res->add = HasModifiers() ? add : HDRColor();
  }

	///
	void Sampler::Bind(int samplerIndex) const
	{
    if( Enabled() )
    {
      // Sorry for profiling code [11/17/2009 smirnov]
      //     Crc32Checksum crc;
      //     crc.Add(samplerStateConverted);
      //     crc.Add(pTexture);
      //     crc.Add(multiplier);
      //     crc.Add(add);
      //     SmartRenderer::_DebugSamplerBind(samplerIndex, crc.Get());

      GetStatesManager()->SetSampler(samplerIndex, samplerState, pTexture);
      if( HasModifiers() )
      {
        Render::GetRenderer()->SetPixelShaderConstantsHDRColor(SAMPLER_CONSTANTS_BEGIN+samplerIndex*2, multiplier);
        Render::GetRenderer()->SetPixelShaderConstantsHDRColor(SAMPLER_CONSTANTS_BEGIN+samplerIndex*2+1, add);
      }
    }
    //else if( SamplerState2::ForceDisable == samplerState.EnableMode() )
    //  SmartRenderer::BindTexture(samplerIndex, 0);

	}
} // namespace Render