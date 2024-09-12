#ifndef SIMPLECRYPT_HPP_B7BE6C43_E065_41
#define SIMPLECRYPT_HPP_B7BE6C43_E065_41


class SimpleCrypt
{
public:
  typedef unsigned char TByte;

  SimpleCrypt()
  {
    Reset();
  }

  void Reset()
  {
    state = 0;
  }
  
  void EncryptDecrypt( TByte *pData, size_t size )
  {
    //»спользуем дл€ шифровани€ очень простой алгоритм: дл€ каждого символа 
    //вычисл€ем XOR с некоторым числом state и измен€ем state прибавл€€ 
    //к нему простое число baseNum. “олько простое число baseNum позвол€ет, 
    //не повтор€€сь, перебрать все возможные значени€ state 
    TByte * const pEnd = pData + size;
    
    while( pData != pEnd )
    {
      state = (state + baseNum) & 0xFF; // & 0xFF For calm Run-Time Error Checks
      *(pData++) ^= state;
    }
  }
      
  template<class T>
  void EncryptDecrypt( T *pData, size_t size = 1 )
  {
    EncryptDecrypt( static_cast<void *>(pData), size * sizeof(T) );
  };  
  
  void EncryptDecrypt( void *pData, size_t size )
  {
    EncryptDecrypt( static_cast<TByte *>(pData), size );  
  }

private:
  TByte state;
  static const TByte baseNum = 83;
};


#endif //#define SIMPLECRYPT_HPP_B7BE6C43_E065_41