#ifndef HIDDENVARS_H_9451F229_6804_4A7F
#define HIDDENVARS_H_9451F229_6804_4A7F

#include "System/Geom.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Модуль позволяет зашифровать переменные в памяти, что затрудняет их анализ такими средствами, как
// ArtMoney и CheatEngine. Каждая переменная хранится в памяти в зашифрованном виде и в момент 
// использования расшифровывается, а после использования новое значение снова зашифровывается и 
// записывается в память для хранения. Кроме того, периодически, значения переменных перешифровываются
// таким образом, что расшифрованное значения совпадают, но значения хранящиеся в памяти отличаются.
// Такой подход позволяет защититься от двух распространённых паттернов работы с читерскими 
// программами:
//    1. Поиск адреса переменной по её значению отображающемуся на экране. Решение: значение 
//       защищенной переменной и её представление в памяти полностью различаются
//    2. Поиск переменных с неизвестным значением, по моменту их изменения. Например, мы не знаем 
//       значение жизни героя, но зато знаем момент после которого это значение изменилось. 
//       Тогда, мы находим все переменные изменившееся за данный промежуток времени и постепенно,
//       отбрасывая лишнее, находим искомый адрес. Решение: представление в памяти защищенной 
//       переменной постоянно изменяется за счёт перешифрования (явный вызов функции Recrypt) 
//       вне зависимости от того изменилось значение переменной или нет.
//
// StarForce поддерживает шифрование переменных, но скорость работы таких переменных в 5000 
// медленнее, чем обычных и поэтому от использования механизма StarForce отказались.
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if defined( STARFORCE_PROTECTED )
  #define HIDDEN_VARS_ENABLED
#endif

_interface IBinSaver;

namespace Protection
{
namespace Detail
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Простые числа, используемые в шифровании переменных. Сгенерированы при помощи 
// следующего кода на Maple. Подробнее см. описание процесса шифрования ниже.
// 
// restart;
// calcBase := proc( base, baseDiv )
//    local f, rez, cur, i;
//    f := x -> if isprime(x) then x else prevprime(x) end if;
//    rez := f(floor(base / baseDiv));
//    printf( "LCM: %d\n", lcm(rez, base) ); 
// 
//    cur := rez;
//    printf( "\n" );
//    for i from 1 to prevprime(20) do
//        printf( "template<> struct UniqNum2BaseValue< unsigned int, %2d>  { static const unsigned int Value = %d; };\n", i-1, cur );
//       cur := nextprime(floor(cur*1.005));
//    end do:
// 
//    cur := rez:
//    for i from 1 to 300 do
//        printf( "%d, ", cur );
//        cur := (cur + rez) mod base;
//    end do:
// 
//    return rez;
// end proc:              
// calcBase( 2^32, 4.7);
// calcBase(  2^8, 3 );
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template< class T, int > struct UniqNum2BaseValue;
template< class T > struct CountUniqNum2BaseValue;

template<> struct UniqNum2BaseValue< unsigned int,  0>  { static const unsigned int Value = 913822823; };
template<> struct UniqNum2BaseValue< unsigned int,  1>  { static const unsigned int Value = 918391949; };
template<> struct UniqNum2BaseValue< unsigned int,  2>  { static const unsigned int Value = 922983911; };
template<> struct UniqNum2BaseValue< unsigned int,  3>  { static const unsigned int Value = 927598849; };
template<> struct UniqNum2BaseValue< unsigned int,  4>  { static const unsigned int Value = 932236847; };
template<> struct UniqNum2BaseValue< unsigned int,  5>  { static const unsigned int Value = 936898057; };
template<> struct UniqNum2BaseValue< unsigned int,  6>  { static const unsigned int Value = 941582569; };
template<> struct UniqNum2BaseValue< unsigned int,  7>  { static const unsigned int Value = 946290491; };
template<> struct UniqNum2BaseValue< unsigned int,  8>  { static const unsigned int Value = 951021947; };
template<> struct UniqNum2BaseValue< unsigned int,  9>  { static const unsigned int Value = 955777063; };
template<> struct UniqNum2BaseValue< unsigned int, 10>  { static const unsigned int Value = 960555949; };
template<> struct UniqNum2BaseValue< unsigned int, 11>  { static const unsigned int Value = 965358743; };
template<> struct UniqNum2BaseValue< unsigned int, 12>  { static const unsigned int Value = 970185551; };
template<> struct UniqNum2BaseValue< unsigned int, 13>  { static const unsigned int Value = 975036487; };
template<> struct UniqNum2BaseValue< unsigned int, 14>  { static const unsigned int Value = 979911679; };
template<> struct UniqNum2BaseValue< unsigned int, 15>  { static const unsigned int Value = 984811253; };
template<> struct UniqNum2BaseValue< unsigned int, 16>  { static const unsigned int Value = 989735317; };
template<> struct UniqNum2BaseValue< unsigned int, 17>  { static const unsigned int Value = 994683997; };
template<> struct UniqNum2BaseValue< unsigned int, 18>  { static const unsigned int Value = 999657427; };

template<> struct CountUniqNum2BaseValue< unsigned int > { static const int Count = 19; };

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Определение операторов для зашифрованных классов
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template< class DerivedT, class OriginT >
class BaseOperators
{ 
public:
   typedef OriginT TOrigin;

private:
  DerivedT &Der()
  { 
    return static_cast<DerivedT &>(*this);
  }
  
  const DerivedT &Der() const
  { 
    return static_cast<const DerivedT &>(*this);
  }
  
  void Encrypt( OriginT val )
  {
    Der() = val;   
  }
  
  OriginT Decrypt() const
  {
    return GetValue( Der() );
  }
    
public:
  operator const OriginT() const 
  {
    return Decrypt();
  }

  DerivedT & operator++( void ) 
  { 
    Encrypt( Decrypt() + 1 ); 
    return Der(); 
  } 
  
  DerivedT & operator--( void ) 
  { 
    Encrypt( Decrypt() - 1 ); 
    return *this; 
  } 
     
  DerivedT operator++( int ) 
  { 
    const DerivedT prev( Der() );
    ++( Der() ); 
    return prev; 
  }
  
  DerivedT operator--( int ) 
  { 
    const DerivedT prev( Der() );
    --( Der() ); 
    return prev; 
  }
  
  DerivedT &operator+=( OriginT val ) 
  { 
    Encrypt( Decrypt() + val ); 
    return Der(); 
  }
  
  DerivedT &operator-=( OriginT val ) 
  { 
    Encrypt( Decrypt() - val ); 
    return Der(); 
  }
  
  DerivedT &operator*=( OriginT val ) 
  { 
    Encrypt( Decrypt() * val ); 
    return Der(); 
  }
  
  DerivedT &operator/=( OriginT val ) 
  { 
    Encrypt( Decrypt() / val ); 
    return Der(); 
  }
  
  friend Meta::Type2Type<OriginT> GetRealType( Meta::Type2Type<DerivedT> )
  {
    return Meta::Type2Type<OriginT>();
  }
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Шаблонный тип защищенной переменной. Поддерживает прозрачное по отношению к синтаксису
// шифрование переменной при помощи операторов неявного преобразования в оригинальный тип 
// переменной и обратно.
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<
  //Тип оригинальной переменной
  class OriginT, 
  
  //Беззнаковый целый тип размерности sizeof(OriginT)
  class StorageT, 
  
  //Порядковый номер базового значения для шифрования. Алгоритм шифрования использует 
  //константу, значение которой желательно как можно реже повторять в программе.
  //Поэтому, желательно, при объявлении защищенной переменной последовательно увеличивать 
  //значения этого параметра от нуля и выше
  int UniqNum
>
class HiddenVarImpl: public BaseOperators< HiddenVarImpl<OriginT, StorageT, UniqNum>, OriginT >
{
  static const StorageT BaseValue = UniqNum2BaseValue<
                  StorageT, 
                  UniqNum % CountUniqNum2BaseValue<StorageT>::Count
                >::Value; 
                                    
  
public:
  HiddenVarImpl(): 
    /* no data init*/ key()  
 {}
  
  HiddenVarImpl( OriginT val ): 
    key() 
  { 
    Encrypt( val ); 
  } 
  
  HiddenVarImpl &operator=( OriginT val ) 
  { 
    Encrypt( val ); 
    return *this; 
  }
  
  friend OriginT GetValue( const HiddenVarImpl &v )
  {
    return v.Decrypt();  
  }
  
  //Важно периодически вызывать данную функцию, вне зависимости от того 
  //изменилось значение переменной или нет  
  friend void Recrypt( HiddenVarImpl &val )
  {
    //Для того чтобы изменить представление в памяти достаточно 
    //расшифровать и снова зашифровать переменную
    val.Encrypt( val.Decrypt() );
  }
    
private:

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // Описание алгоритма.
  // Используется очень простой и быстрый алгоритм. Данные сохраняются в двух переменных key и data.
  // Изначально значение key равно BaseValue. BaseValue - это произвольное, достаточно большое простое
  // число. Перед каждым шифрованием значение key увеличивается на BaseValue и в data записывается сумма
  // исходного значения и key. Для расшифрования из data вычитается key.
  // Таким образом, алгоритм при каждом шифровании генерирует новое значение гаммы, продолжительность 
  // которой, благодаря использованию простых чисел для BaseValue, равна диапазону значений типа key и 
  // эта гамма накладывается на данные для шифрования. Сложение и вычитание используются, вместо 
  // привычного XOR, только для того, чтобы вызывать меньше подозрения в коде, основная задача
  // которого это производить арифметические действия.
  // 
  // Алгоритм, безусловно, не является хоть сколько криптографически стойким, но в ситуации, когда 
  // у хакера есть доступ к ключу любой алгоритм со временем сдастся, стоит только хакеру обратить 
  // внимание на данную переменную. Поэтому я не вижу причин усложнять алгоритм и терять в
  // производительности. Главное задача алгоритма - это сделать так чтобы данная защищенная переменная 
  // не обратила на себя внимание. 
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template< class T1, class T2 >
  static T1 Convert( T2 value )
  {
    NI_STATIC_ASSERT( sizeof(T1) == sizeof(T2), sizeof_mismatch );
    //NI_STATIC_ASSERT( alignof(T1) == alignof(T2), alignof_mismatch );  
    return *reinterpret_cast<const T1 *>(&value);
  }
  
  void Encrypt( OriginT value )
  {
    key += BaseValue;
    data = Convert<StorageT>(value) + key;  
  }
  
  OriginT Decrypt() const
  {
    return Convert<OriginT>(data - key);
  }
  
private:
  //Лучше когда data расположена перед key, тогда "странная" константа BaseValue
  //в ассемблерном коде находится дальше от инструкции изменения
  StorageT data; 
  StorageT key;
  
public: //Не должен сериализоваться как POD
  int operator&( IBinSaver &f ); 
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Защищенный класс CVec2
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<int UniqNum>
class Vec2: public BaseOperators< Vec2<UniqNum>, CVec2 >
{
  typedef CVec2 OriginVec2;
  
public:
  Vec2() {}
  Vec2( const OriginVec2 &val ): x(val.x), y(val.y) {}
    
  Vec2 &operator=( const OriginVec2 &val )
  {
    x = val.x;
    y = val.y;
    return *this;
  } 
  
  friend OriginVec2 GetValue( const Vec2 &v )
  {
    return OriginVec2( v.x, v.y );
  }
  
  friend void Recrypt( Vec2 &val )
  {
     Recrypt( val.x );
     Recrypt( val.y );
  }
  
  friend inline bool Normalize( Vec2 *pVec ) 
  { 
    CVec2 tmp(*pVec);
    const bool result = Normalize(&tmp);
    *pVec = tmp; 
    
    return result; 
  }

private:
  typedef CountUniqNum2BaseValue<unsigned int> TCount;
  HiddenVarImpl<float, unsigned int, UniqNum > x;
  HiddenVarImpl<float, unsigned int, UniqNum + TCount::Count / 2>  y;
  
public: //Не должен сериализоваться как POD
  int operator&( IBinSaver &f );  
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Защищенный класс CVec3
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<int UniqNum>
class Vec3: public BaseOperators< Vec3<UniqNum>, CVec3 >
{
  typedef CVec3 OriginVec3;
  
public:
  Vec3() {}
  Vec3( const OriginVec3 &val ): x(val.x), y(val.y), z(val.z) {}
    
  Vec3 &operator=( const OriginVec3 &val )
  {
    x = val.x;
    y = val.y;
    z = val.z;
    return *this;
  } 
  
  friend OriginVec3 GetValue( const Vec3 &v ) 
  {
    return OriginVec3( v.x, v.y, v.z );
  }
  
  friend void Recrypt( Vec3 &val )
  {
     Recrypt( val.x );
     Recrypt( val.y );
     Recrypt( val.z );
  }
  
  const CVec2 AsVec2D() const
  {
    return CVec2( x, y );
  } 
  
  float X() const { return x; }
  float Y() const { return y; }
  float Z() const { return z; }
  
private:
  typedef CountUniqNum2BaseValue<unsigned int> TCount;
  HiddenVarImpl<float, unsigned int, UniqNum >     x;
  HiddenVarImpl<float, unsigned int, UniqNum + TCount::Count * 1 / 3>  y;
  HiddenVarImpl<float, unsigned int, UniqNum + TCount::Count * 2 / 3>  z;
  
public: //Не должен сериализоваться как POD
  int operator&( IBinSaver &f ); 
};

} //namespace Detail


template< class T, int UniqNum = 1>
struct HiddenVar;

template<int UniqNum>
struct HiddenVar<float, UniqNum> 
{ 
#ifdef HIDDEN_VARS_ENABLED
  typedef typename Detail::HiddenVarImpl<float, unsigned int, UniqNum - 1> T;
  typedef const float TConstRef; 
#else 
  typedef float T;
  typedef const float &TConstRef;
#endif
};

template<int UniqNum>
struct HiddenVar<int, UniqNum> 
{ 
#ifdef HIDDEN_VARS_ENABLED
  typedef typename Detail::HiddenVarImpl<int, unsigned int, UniqNum - 1> T;
  typedef const int TConstRef; 
#else 
  typedef int T;
  typedef const int &TConstRef;
#endif
};

template<int UniqNum>
struct HiddenVar<bool, UniqNum> 
{ 
#ifdef HIDDEN_VARS_ENABLED
  typedef typename Detail::HiddenVarImpl<int, unsigned int, UniqNum - 1> T;
  typedef const int TConstRef; 
#else 
  typedef int T;
  typedef const int &TConstRef;
#endif
};

template<int UniqNum>
struct HiddenVar<CVec2, UniqNum> 
{ 
#ifdef HIDDEN_VARS_ENABLED
  typedef typename Detail::Vec2<UniqNum - 1> T; 
  typedef const CVec2 TConstRef;
#else 
  typedef CVec2 T;
  typedef const CVec2 &TConstRef;
#endif
};

template<int UniqNum>
struct HiddenVar<CVec3, UniqNum> 
{ 
#ifdef HIDDEN_VARS_ENABLED
  typedef typename Detail::Vec3<UniqNum - 1> T;
  typedef const CVec3 TConstRef; 
#else 
  typedef CVec3 T;
  typedef const CVec3 &TConstRef;
#endif
};

} //namespace Protection


//Вместо этих функций будет выбираться перегрузки из Detail даже когда макрос 
//HIDDEN_VARS_ENABLED определен, но на всякий случай будем открывать их только 
//тогда, когда они действительно нужны
#ifndef HIDDEN_VARS_ENABLED
  //Ничего не делающая версия Recrypt для обычных переменных
  template<class T>
  inline void Recrypt( T & ) 
  {
    //Nothing
  }

  template<class T>
  inline void Recrypt( const T & ) 
  {
    //Если не перегружать данную функцию, то при случайной передачи константной переменной
    //будет выбрана глобальная перегрузка Recrypt, которая ничего не делает
    T::MustBeenNonConst(); 
  }

  //Просто возвращающая аргумент функция GetValue для обычных переменных
  template<class T>
  inline const T &GetValue( const T &v )
  {
    return v;
  } 
#endif

#endif //#define HIDDENVARS_H_9451F229_6804_4A7F