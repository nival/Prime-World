#ifndef BLOOM_ENCODING_INCLUDED
  #define BLOOM_ENCODING_INCLUDED
  
half DecodeBloomVal(half val)  { return saturate( 1 - val/(1 - BLOOM_ENCODING_THRESHOLD) ); }

half EncodeBloomVal(half alpha, half emissiveScale)
{
  half emissivePart = saturate(alpha - BLOOM_ENCODING_THRESHOLD);
  return 1 - (alpha - emissivePart*(1 - emissiveScale));
}

#endif