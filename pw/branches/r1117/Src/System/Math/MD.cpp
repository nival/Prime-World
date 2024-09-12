#include "stdafx.h"
#include "MD4.h"




namespace math
{

nstl::string MD4::ToString() const
{
  char buf[64] = "";
  for ( int i = 0; i < DIGEST_SIZE_IN_BYTES; ++i )
  {
    char tmp[16] = "";
    sprintf( tmp, "%02x", 0xff & ((byte*)code)[i] );

    strcat( buf, tmp );
  }
  return buf;
}


MD4 GenerateMD5(const byte* buffer, uint size)
{
  MD5Generator m;
  m.Start();
  m.Update(buffer, size);
  m.Stop();
  return m.Get();
}

MD4 GenerateMD5(const nstl::vector<byte>& buffer)
{
  return GenerateMD5(&buffer[0], buffer.size());
}

MD4 GenerateMD4(const byte* buffer, uint size)
{
  MD4Generator m;
  m.Start();
  m.Update(buffer, size);
  m.Stop();
  return m.Get();
}

math::MD4 GenerateMD4(const nstl::vector<byte>& buffer)
{
  return GenerateMD4(&buffer[0], buffer.size());
}


MD4 MD4::Generate(const byte* buffer, uint size)
{
  return GenerateMD4(buffer, size);
}

MD4 MD4::Generate(const nstl::vector<byte>& buffer)
{
  return GenerateMD4(buffer);
}

}