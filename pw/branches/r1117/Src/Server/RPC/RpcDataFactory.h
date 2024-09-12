#ifndef RPCDATAFACTORY_H_INCLUDED
#define RPCDATAFACTORY_H_INCLUDED

#include "Server/RPC/ClassNameHash.h"

#define SERIALIZE_ID()                                                       \
  static int ID;                                                               \
public:                                                                      \
  static int NI_SERIALIZE_ID(); \
  virtual rpc::TypeInfo GetTypeInfo() const { rpc::TypeInfo info = { ID, sizeof(*this) }; return info; }

#define SERIALIZE_FACTORY( className)                                        \
class Factory##className                                                     \
{                                                                            \
public:                                                                      \
  Factory##className() {                                                   \
    className::ID = rpc::get_class_name_hash(#className);                   \
    rpc::GetGlobalDataFactory()->RegisterInFactory(className::NI_SERIALIZE_ID(), Create, sizeof(className));   \
  }                                                                            \
  static rpc::Data* Create(int type, void* memory)                                   \
  {                                                                            \
    return new (memory) className;                                         \
  }                                                                            \
  int dummy() const { return 0; }                                              \
};                                                                           \
  int className::ID;                                                           \
  int className::NI_SERIALIZE_ID() { return ID; } \
  static Factory##className factory##className;                                 \
  int dummy##className = factory##className.dummy();


#define DEFINE_RE_FACTORY( namesp, className )                                                 \
static rpc::SimpleRemoteEntityFactory< namesp::className > factory_##namesp##_##className;     \
namespace namesp {                                                                             \
int dummy##className = factory_##namesp##_##className.dummy();                                 \
}

#define FORCE_INIT_FACTORY( className )                                      \
extern int dummy##className;                                                 \
static int init##className = dummy##className;

  
namespace rpc
{

struct TypeInfo
{
  int id;
  int size;
};



struct Data
{
  virtual ~Data() {}
  virtual int operator&( IBinSaver &f ) = 0;
  virtual TypeInfo GetTypeInfo() const = 0;
  typedef Data* (*CreateFun)(int type, void* memory);

  template <typename T>
  const T* Query() const
  {
    return (T*)_Query(T::ID);
  }

  inline const void* _Query(uint id) const
  {
    return (id == (uint)GetTypeInfo().id)?this:0;
  }
};



class DataFactory
{
  hash_map<int, Data::CreateFun> messagesMap;
  hash_map<int, int> realSizeMap;
public:
  DataFactory() {}
  void Clear()
  {
    messagesMap.clear();
  }

  void RegisterInFactory( int type, Data::CreateFun fun, int realSize );
  int GetRealSize( int type );
  Data* Create( int type, void* memory );
};

DataFactory* GetGlobalDataFactory();

} //namespace rpc

#endif //RPCDATAFACTORY_H_INCLUDED
