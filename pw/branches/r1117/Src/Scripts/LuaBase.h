#pragma once

// собственно сами врапперы и стуктуры для метаданных: сюда смотреть не надо
#include "LuaMetaData.h"
#include "LuaWrappers.h"

// lua-трансфер встроенных типов данных: смотреть как референс
#include "LuaValues.h"
// lua-трансфер пользовательских типов данных: можно и нужно смотреть, и дополнять
#include "LuaComplexTypes.h"

// Сервисные методы: сюда смотреть не надо
#include "LuaCommon.h"


// Обеспечить lua-трансфер значений enum`а EnumType
// Трансфер осуществляется с помощью значений типа int, контроль корректности значений на чтении не осуществляется
// Можно помещать в .h - если enum используется несколькими классами, так и в .cpp - если только одним.
#define LUA_ENUM_TRANSFER(EnumType)                                                                                      \
  template<> struct Lua::lua_values<EnumType>                                                                                 \
  {                                                                                                                      \
  static EnumType get(lua_State* L, int idx) { return static_cast<EnumType>(lua_values<int>::get(L, idx)); }           \
  static int      put(lua_State* L, EnumType value) { return lua_values<int>::put(L, static_cast<int>(value)); }       \
  };

// Данный макрос декларирует служенбные методы и данные, необходимые для коммуникации класса Class с LUA
// Необходимо поместить в public раздел класса
#define DECLARE_LUA_TYPEINFO(Class)                                                            \
  static  Lua::LuaTypeInfo const* GetLuaTypeInfo();                                            \
  virtual Lua::LuaTypeInfo const* QueryLuaTypeInfo() const { return Class::GetLuaTypeInfo(); } \
  virtual void*                   QueryNativeLuaObject() const { return (void*)this; }         \
          void                    Lua_DestructorImplementation() { delete this; }

// Данный макрос объявляет акцессор/манипулятор для свойства Name типа Type.
// Нужно поместить в public часть объявления класса
#define DEFINE_LUA_PROPERTY(Name, Type, Expr)                              \
  Type Lua_Property_##Name##_Get() const { return Expr;}                   \
  void Lua_Property_##Name##_Set(Type value) { Expr = value;} 

// Данный макрос объявляет акцессор для свойства Name типа Type.
// Нужно поместить в public часть объявления класса
#define DEFINE_LUA_READONLY_PROPERTY(Name, Type, Expr)                     \
  Type Lua_Property_##Name##_Get() const { return Expr;}

// Данный макрос объявляет манипулятор для свойства Name типа Type.
// Нужно поместить в public часть объявления класса
#define DEFINE_LUA_WRITEONLY_PROPERTY(Name, Type, Expr)                    \
  void Lua_Property_##Name##_Set(Type value) { Expr = value;}

// Объявить таблицу методов и свойств, видимых из LUA для класса Class с базовым классом Base, который 
// также может взаимодейстовать с LUA
// Ограничение: не поддерживается множественное наследование классов, взаимодействующих с LUA: 
// такой предок обязательно должен быть один
// 
#define BEGIN_LUA_TYPEINFO(Class, Base)                                                    \
struct LuaTypeInfoWrapperFor##Class                                                        \
  {                                                                                        \
  typedef Class TheClass;                                                                  \
  typedef Base  TheBase;                                                                   \
  static Lua::LuaTypeInfo const* pBase;                                                    \
  static Lua::LuaEntryBase* entries[];                                                     \
  static Lua::LuaTypeInfo typeInfo;                                                        \
  };                                                                                       \
  Lua::LuaTypeInfo const* LuaTypeInfoWrapperFor##Class::pBase = TheBase::GetLuaTypeInfo(); \
  Lua::LuaEntryBase* LuaTypeInfoWrapperFor##Class::entries[] = {

// Объявить таблицу методов и свойств, видимых из LUA для класса Class, который 
// не имеет базового класса, который может взаимодейстовать с LUA. Если один из предков данного 
// класса всё-таки может взаимодейстовать с LUA, то нужно использовать BEGIN_LUA_TYPEINFO
#define BEGIN_LUA_TYPEINFO_NOBASE(Class)                                   \
struct LuaTypeInfoWrapperFor##Class                                        \
  {                                                                        \
  typedef Class TheClass;                                                  \
  static Lua::LuaTypeInfo const* pBase;                                    \
  static Lua::LuaEntryBase* entries[];                                     \
  static Lua::LuaTypeInfo typeInfo;                                        \
  };                                                                       \
  Lua::LuaTypeInfo const* LuaTypeInfoWrapperFor##Class::pBase = NULL;      \
  Lua::LuaEntryBase* LuaTypeInfoWrapperFor##Class::entries[] = {

//////////////////////////////////////////////////////////////////////////
// Все следующие макросы ДОЛЖНЫ использоваться ТОЛЬКО между 
// BEGIN_LUA_TYPEINFO/BEGIN_LUA_TYPEINFO_NOBASE и END_LUA_TYPEINFO
//////////////////////////////////////////////////////////////////////////

// Уничтожать объект данного класса как только он перестаёт использоваться в LUA коде.
// Данный макрос можно использовать только в следующих ситуациях:
// 1. Объект создаётся по new
// 2. Время жизни объекта больше никем не контролируется
// Использовать ОЧЕНЬ осторожно. Пример использования - lua-трансфер СТехt`ов (LuaComplexTypes.h)
#define LUA_DESTRUCTOR() \
  new Lua::LuaMethodEntry(LUA_DESTRUCTOR_NAME, &Lua::make_member_wrapper(&TheClass::Lua_DestructorImplementation).Func<&TheClass::Lua_DestructorImplementation, TheClass*(*)(lua_State* L), &Lua::TypedObjectPtrFromMeta< TheClass > >),

// Сделать доступным в LUA метод Method данного класса под именем Method.
// Ограничения: 
// 1. метод должен быть public
// 2. lua-трансфер типов возвращаемого значения и аргументов должен быть определён
// 3. не поддерживаются перегруженные функции, т.е. int Foo(int arg); int Foo(char const* arg);
#define LUA_METHOD(Method)                                                 \
  new Lua::LuaMethodEntry(#Method, &Lua::make_member_wrapper(&TheClass::Method).Func<&TheClass::Method, TheClass*(*)(lua_State* L), &Lua::TypedObjectPtrFromMeta< TheClass > >),

// Сделать доступным в LUA метод Method данного класса под именем Name.
// Ограничения: см. LUA_METHOD
#define LUA_METHOD_EX(Name, Method)                                                 \
  new Lua::LuaMethodEntry(Name, &Lua::make_member_wrapper(&TheClass::Method).Func<&TheClass::Method, TheClass*(*)(lua_State* L), &Lua::TypedObjectPtrFromMeta< TheClass > >),

// Сделать доступным в LUA свойство Name. 
// Для доступа/модификации значения используются методы Getter/Setter
// Ограничения: 
// 1. методы Getter/Setter должны быть public
// 2. lua-трансфер типа свойства должен быть определён
#define LUA_PROPERTY_EX(Name, Getter, Setter)                                                                                                  \
  new Lua::LuaFieldEntry(#Name,                                                                                                                \
  &Lua::make_member_wrapper(&TheClass::Getter).Func<&TheClass::Getter, TheClass*(*)(lua_State* L), &Lua::TypedObjectPtrFromMeta< TheClass > >, \
  &Lua::make_member_wrapper(&TheClass::Setter).Func<&TheClass::Setter, TheClass*(*)(lua_State* L), &Lua::TypedObjectPtrFromMeta< TheClass > > ),

// Сделать доступным в LUA свойство только для чтения Name. 
// Для доступа к значению используется мето Getter
// Ограничения: 
// 1. метод Getter должен быть public
// 2. lua-трансфер типа свойства должен быть определён
#define LUA_READONLY_PROPERTY_EX(Name, Getter)                                                                                                 \
  new Lua::LuaFieldEntry(#Name,                                                                                                                \
  &Lua::make_member_wrapper(&TheClass::Getter).Func<&TheClass::Getter, TheClass*(*)(lua_State* L), &Lua::TypedObjectPtrFromMeta< TheClass > >, \
  NULL),

// Сделать доступным в LUA свойство только для записи Name. 
// Для доступа к значению используется мето Setter
// Ограничения: 
// 1. метод Setter должен быть public
// 2. lua-трансфер типа свойства должен быть определён
#define LUA_WRITEONLY_PROPERTY_EX(Name, Setter)                                                                                                 \
  new Lua::LuaFieldEntry(#Name,                                                                                                                 \
  NULL,                                                                                                                                         \
  &Lua::make_member_wrapper(&TheClass::Setter).Func<&TheClass::Getter, TheClass*(*)(lua_State* L), &Lua::TypedObjectPtrFromMeta< TheClass > >),

// Сделать доступным в LUA свойство Name. 
#define LUA_PROPERTY(Name) \
  LUA_PROPERTY_EX(Name, Lua_Property_##Name##_Get, Lua_Property_##Name##_Set)

// Сделать доступным в LUA свойство только для чтения Name. 
#define LUA_READONLY_PROPERTY(Name) \
  LUA_READONLY_PROPERTY_EX(Name, Lua_Property_##Name##_Get)

// Сделать доступным в LUA свойство только для записи Name. 
#define LUA_WRITEONLY_PROPERTY(Name) \
  LUA_WRITEONLY_PROPERTY_EX(Name, Lua_Property_##Name##_Set)

// Закончить таблицу методов и свойств, видимых из LUA для данного класса 
#define END_LUA_TYPEINFO(Class)                                                                                                         \
  NULL                                                                                                                                  \
  } ;                                                                                                                                   \
  Lua::LuaTypeInfo LuaTypeInfoWrapperFor##Class::typeInfo("Native_"###Class, pBase, entries, sizeof(entries) / sizeof(entries[0]) - 1); \
  Lua::LuaTypeInfo const* Class::GetLuaTypeInfo() { return &LuaTypeInfoWrapperFor##Class::typeInfo; }

// служебный макрос для вывода сообщения об ошибке в LUA_METHOD_IMPL/LUA_METHOD_IMPL_RV
#define LUA_IMPL_ERROR_NOTIFY(NAME) \
  {systemLog( NLogg::LEVEL_DEBUG ) << "Failed to call handler <" << NAME << ">" << endl; }

// следующая группа макросов используется для определения функции, имплементация которй находится в lua
// LUA_METHOD_IMPL, LUA_METHOD_IMPL_1 ... - функции, который не возвращают значений
// аргументы - имя функции, аргументы (если есть) 
#define LUA_METHOD_IMPL(NAME)                                          \
  if(!CallHandler(#NAME))                                              \
  {                                                                    \
    LUA_IMPL_ERROR_NOTIFY(#NAME)                                       \
  }                                                                    \
  else {}

#define LUA_METHOD_IMPL_1(NAME, ARG1)                                  \
  if(!CallHandler(#NAME, ARG1))                                        \
  {                                                                    \
    LUA_IMPL_ERROR_NOTIFY(#NAME)                                       \
  }                                                                    \
  else {}

#define LUA_METHOD_IMPL_2(NAME, ARG1, ARG2)                            \
  if(!CallHandler(#NAME, ARG1, ARG2))                                  \
  {                                                                    \
    LUA_IMPL_ERROR_NOTIFY(#NAME)                                       \
  }                                                                    \
  else {}

#define LUA_METHOD_IMPL_3(NAME, ARG1, ARG2, ARG3)                      \
  if(!CallHandler(#NAME, ARG1, ARG2, ARG3))                            \
  {                                                                    \
    LUA_IMPL_ERROR_NOTIFY(#NAME)                                       \
  }                                                                    \
  else {}

#define LUA_METHOD_IMPL_4(NAME, ARG1, ARG2, ARG3, ARG4)                \
  if(!CallHandler(#NAME, ARG1, ARG2, ARG3, ARG4))                      \
  {                                                                    \
    LUA_IMPL_ERROR_NOTIFY(#NAME)                                       \
  }                                                                    \
  else {}

#define LUA_METHOD_IMPL_5(NAME, ARG1, ARG2, ARG3, ARG4, ARG5)          \
  if(!CallHandler(#NAME, ARG1, ARG2, ARG3, ARG4, ARG5))                \
  {                                                                    \
    LUA_IMPL_ERROR_NOTIFY(#NAME)                                       \
  }                                                                    \
  else {}

// LUA_METHOD_IMPL, LUA_METHOD_IMPL_1 ... - функции, которые возвращают значение
// аргументы - тип возвращаемого значения, имя функции, аргументы (если есть) 
#define LUA_METHOD_IMPL_RV(TYPE, NAME)                                 \
  TYPE result = TYPE();                                                \
  if(!CallMethod(#NAME, result))                                       \
  {                                                                    \
    LUA_IMPL_ERROR_NOTIFY(#NAME)                                       \
  }                                                                    \
  else {}                                                              \
  return result;

#define LUA_METHOD_IMPL_RV_1(TYPE, NAME, ARG1)                         \
  TYPE result = TYPE();                                                \
  if(!CallMethod(#NAME, result, ARG1))                                 \
  {                                                                    \
    LUA_IMPL_ERROR_NOTIFY(#NAME)                                       \
  }                                                                    \
  else {}                                                              \
  return result;

#define LUA_METHOD_IMPL_RV_2(TYPE, NAME, ARG1, ARG2)                   \
  TYPE result = TYPE();                                                \
  if(!CallMethod(#NAME, result, ARG1, ARG2))                           \
  {                                                                    \
    LUA_IMPL_ERROR_NOTIFY(#NAME)                                       \
  }                                                                    \
  else {}                                                              \
  return result;

#define LUA_METHOD_IMPL_RV_3(TYPE, NAME, ARG1, ARG2, ARG3)             \
  TYPE result = TYPE();                                                \
  if(!CallMethod(#NAME, result, ARG1, ARG2, ARG3))                     \
  {                                                                    \
    LUA_IMPL_ERROR_NOTIFY(#NAME)                                       \
  }                                                                    \
  else {}                                                              \
  return result;

#define LUA_METHOD_IMPL_RV_4(TYPE, NAME, ARG1, ARG2, ARG3, ARG4)       \
  TYPE result = TYPE();                                                \
  if(!CallMethod(#NAME, result, ARG1, ARG2, ARG3, ARG4))               \
  {                                                                    \
    LUA_IMPL_ERROR_NOTIFY(#NAME)                                       \
  }                                                                    \
  else {}                                                              \
  return result;

#define LUA_METHOD_IMPL_RV_5(TYPE, NAME, ARG1, ARG2, ARG3, ARG4, ARG5) \
  TYPE result = TYPE();                                                \
  if(!CallMethod(#NAME, result, ARG1, ARG2, ARG3, ARG4, ARG5))         \
  {                                                                    \
    LUA_IMPL_ERROR_NOTIFY(#NAME)                                       \
  }                                                                    \
  else {}                                                              \
  return result;
                                                                                   