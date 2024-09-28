#ifndef SYSTEM_MD4_H_INCLUDED
#define SYSTEM_MD4_H_INCLUDED

extern "C"
{
#include <Vendor/MD4/global.h>
#include <Vendor/MD4/md4.h>
#include <Vendor/MD4/md5.h>
}

#include <System/DefaultTypes.h>
#include <assert.h>
#include <memory.h>
#include <System/nvector.h>
#include <System/nstring.h>

namespace math
{

struct MD4
{
    static const int DIGEST_SIZE = 4;
    static const int DIGEST_SIZE_IN_BYTES = DIGEST_SIZE*sizeof(int);
    //union
    //{
      uint code[DIGEST_SIZE];
//      byte bytes[DIGEST_SIZE_IN_BYTES];
    //};

    MD4()
    {
        Clear();
    }
    MD4(int lowPart)
    {
        Clear();
        Set(lowPart);
    }

    const byte* Get() const { return (const byte*)&code; }
    int Length() const { return DIGEST_SIZE*sizeof(int); }
    
    void Set(uint part)
    {
        code[3] = part;
    }

    void Clear()
    {
        for (int i=0;i<4;++i)
        {
            code[i] = 0;
        }
    }
    
    bool operator == (const MD4& other) const 
    {
        for (int i=0;i<4;++i)
        {
            if (code[i] != other.code[i])
                return false;
        }
        return true;
    }
    
    bool operator != (const MD4& other) const 
    {
      return !this->operator==(other);
    }

    static math::MD4 Generate(const byte* buffer, uint size);
    static math::MD4 Generate(const nstl::vector<byte>& buffer);

    nstl::string ToString() const;
};

template <typename CONTEXT, void INIT(CONTEXT*), void UPDATE(CONTEXT*, unsigned char*, unsigned int), void FINAL(unsigned char [16], CONTEXT*)>
struct MDGenerator
{
  MDGenerator()
  {
    Start();
  }

  void Start()
  {
    INIT(&context);
  }

  void Update(const byte* data, uint size)
  {
    UPDATE(&context, const_cast<byte*>(data), size);
  }

  template <typename T>
  void AddObject( const T & obj )
  {
    UPDATE(&context, const_cast<byte*>( reinterpret_cast<const byte*>( &obj ) ), sizeof( obj ) );
  }

  const MD4& Stop()
  {
    FINAL((byte*)result.code, &context);
    return Get();
  }

  inline const MD4& Get() const { return result; }
private:
  CONTEXT context;
  MD4 result;
};

typedef math::MDGenerator<MD4_CTX, MD4Init, MD4Update, MD4Final> MD4Generator;
typedef math::MDGenerator<MD5_CTX, MD5Init, MD5Update, MD5Final> MD5Generator;

math::MD4 GenerateMD5(const byte* buffer, uint size);
math::MD4 GenerateMD5(const nstl::vector<byte>& buffer);
math::MD4 GenerateMD4(const byte* buffer, uint size);
math::MD4 GenerateMD4(const nstl::vector<byte>& buffer);

}

#endif //SYSTEM_MD4_H_INCLUDED
