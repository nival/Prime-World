#pragma once

struct lua_State;
typedef int (*lua_CFunction) (lua_State *L);

namespace Lua
{
  struct LuaEntryBase 
  {
    enum ItemType{ IT_FIELD, IT_METHOD, _ITEMS_COUNT_ };
    virtual ItemType GetItemType() const = 0;
    
    virtual ~LuaEntryBase() {};
  };

  class LuaMethodEntry : public LuaEntryBase
  {
  public:
    explicit LuaMethodEntry(char const* name, lua_CFunction wrapper) 
      : name(name)
      , wrapper(wrapper)
    {
    }

    lua_CFunction Get()  const { return wrapper;}
    char const*   Name() const { return name.c_str(); }
    
    virtual ItemType GetItemType() const { return IT_METHOD; };
  private:
    lua_CFunction wrapper;
    string        name;
  };
  
  class LuaFieldEntry : public LuaEntryBase
  {
  public:
    explicit LuaFieldEntry(char const* name, lua_CFunction getter, lua_CFunction setter)
      : name(name)
      , getter(getter)
      , setter(setter)
    {
    }
    
    char const*   Name()           const { return name.c_str(); }
    lua_CFunction GetManipulator() const { return setter; }
    lua_CFunction GetAccessor()    const { return getter; }

    virtual ItemType GetItemType() const { return IT_FIELD; };
  private:
    lua_CFunction getter;
    lua_CFunction setter;
    string        name;
  };

  struct LuaEntryCmp
  {
    typedef LuaEntryBase const* arg_t;
    bool operator () (arg_t l, arg_t r) const
    {
      NI_ASSERT( l && r, "Invalid entry in Lua class metatable!");
      return (l->GetItemType() < r->GetItemType());
    }
  };
  
  class LuaTypeInfo
  {
    LuaTypeInfo const* pBase;  
    LuaEntryBase**     pEntries;
    int                count;

    int                typeOffsets[LuaEntryBase::_ITEMS_COUNT_];
    int                typeCounts[LuaEntryBase::_ITEMS_COUNT_];
    
    string             typeName;

    LuaTypeInfo(LuaTypeInfo const&);
    LuaTypeInfo& operator = (LuaTypeInfo const&);
    
    int                 GetEntriesCount(LuaEntryBase::ItemType type) const
    {
      int count = typeCounts[type]; 
      if(pBase)
        count += pBase->GetEntriesCount(type);

      return count; 
    }

    LuaEntryBase const* GetEntry(int index, LuaEntryBase::ItemType type) const
    {
      if(index < 0)
      {
        NI_ALWAYS_ASSERT("Invalid entry index!");
        return NULL;
      }

      const int base  = pBase ? pBase->GetEntriesCount(type) : 0;
      const int self  = typeCounts[type];

      if(index < base)
        return pBase->GetEntry(index, type);

      if(index < base + self)
        return pEntries[index - base + typeOffsets[type] ];

      NI_ALWAYS_ASSERT("Invalid index!");
      return NULL;
    }

  public:    
    explicit LuaTypeInfo(char const* typeName, LuaTypeInfo const* pBase, LuaEntryBase** pEntries, int count)
      : pBase(pBase)
      , pEntries(pEntries)
      , count(count)
      , typeName(typeName)
    {
      sort(pEntries, pEntries + count, LuaEntryCmp());

      for(int i = 0; i < LuaEntryBase::_ITEMS_COUNT_; ++i)
      {
        typeOffsets[i] = -1;
        typeCounts[i]  = 0;
      }

      for(int i = 0; i < count; ++i)
      {
        NI_ASSERT(pEntries[i], "Invalid entry!");
        if(NULL == pEntries[i])
          continue;
        
        const LuaEntryBase::ItemType type = pEntries[i]->GetItemType();
        if(0 == i || pEntries[i - 1]->GetItemType() != type )
        {
          NI_ASSERT(-1 == typeOffsets[type], "Invalid entry array!");
          typeOffsets[type] = i;
        }

        ++typeCounts[type];
      }
    }

    ~LuaTypeInfo()
    {
      for(int i = 0; i < count; ++i)
      {
        SAFE_DELETE(pEntries[i]);
      }
      
      pEntries = NULL;
    }

    int                   GetMethodsCount() const { return GetEntriesCount(LuaEntryBase::IT_METHOD); }
    int                   GetFieldsCount() const  { return GetEntriesCount(LuaEntryBase::IT_FIELD); }   
    
    LuaMethodEntry const* GetMethod(int index) const 
    { 
      return static_cast<LuaMethodEntry const*>(GetEntry(index, LuaEntryBase::IT_METHOD));
    }

    LuaFieldEntry const* GetField(int index) const
    {
      return static_cast<LuaFieldEntry const*>(GetEntry(index, LuaEntryBase::IT_FIELD));
    }

    char const*          GetTypeName() const { return typeName.c_str(); }
  };

} // namespace Lua