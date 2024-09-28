#pragma once

#include "ClassFactory.h"
#include "IRemoteEntity.h"

namespace rpc
{

  class VectorAccessor
  {
  public:
    VectorAccessor():entity(0) {}

    VectorAccessor(byte memberId):
    entity(0),
    memberId(memberId)
    {}

    void Init(rpc::IRemoteEntity* _entity) { entity = _entity; }

    template <typename T>
    void Set(int index, const T& value, const T& oldValue)
    {
      ContainerOperationInfo info = { index, rpc::VectorOfScalars, rpc::voSet };
      entity->GetHandler()->SetMember(entity, memberId, info, value, oldValue);
    }

    template <typename T>
    void append(const T& value)
    {
      ContainerOperationInfo info = { -1, rpc::VectorOfScalars, rpc::voAppend };
      entity->GetHandler()->SetMember(entity, memberId, info, value, value);
    }

    template <typename T>
    void eraseByIndex(int index, const T& value) 
    {
      ContainerOperationInfo info = { index, rpc::VectorOfScalars, rpc::voEraseByIndex };
      entity->GetHandler()->EraseMember(entity, memberId, info, value);
    }
  private:
    rpc::IRemoteEntity* entity;
    byte memberId;
  };

  template <typename T>
  class vector : nstl::vector<T>
  {
  public:
    vector():accessor(0) {}

    vector(rpc::VectorAccessor* accessor):
    accessor(accessor)
    {
    }

    void insert(int index, const T& value)
    {
      nstl::vector<T>::insert(nstl::vector<T>::begin()+index, value);
    }

    void insert(int index)
    {
      nstl::vector<T>::insert(nstl::vector<T>::begin()+index);
    }

    void pop_back()
    {
      nstl::vector<T>::pop_back();
    }

    void eraseByIndex(int index, bool log=true) 
    {
      if (log)
      {
        accessor->eraseByIndex(index, operator[](index));
      }
      nstl::vector<T>::eraseByIndex(index);        
    }
    uint size() const { return nstl::vector<T>::size(); }

    void append(const T& value, bool log=true) 
    {
      push_back(value, log);
    }

    void remove(const T& value, bool log=true)
    {
      typename nstl::vector<T>::iterator it = nstl::vector<T>::find(value);
      if (it != nstl::vector<T>::end())
      {
        eraseByIndex(it-nstl::vector<T>::begin(), log);
      }
    }

    void push_back(const T& value, bool log=true) 
    {
      if (log)
      {
        accessor->append(value);
      }
      nstl::vector<T>::push_back(value);      
    }

    const T& operator [] (uint index) const
    {
      return (const nstl::vector<T>*)this->operator[](index);
    }

    T& operator [] (uint index)
    {
      return ((nstl::vector<T>*)this)->operator[](index);
    }
  private:
    rpc::VectorAccessor* accessor;
  };

  template <typename T>
  class _StringAccessor
  {
  public:
    _StringAccessor():entity(0) {}

    _StringAccessor(byte memberId):
    entity(0),
    memberId(memberId)
    {}

    void Init(rpc::IRemoteEntity* _entity) { entity = _entity; }

    void Set(const T* newValue, const T* oldValue)
    {
      ContainerOperationInfo info = { 0, rpc::String, rpc::soAssign };
      entity->GetHandler()->SetMember(entity, memberId, info, newValue, oldValue);
    }

    void Set(int index, T newValue, T oldValue)
    {
      ContainerOperationInfo info = { index, rpc::String, rpc::soSetByIndex };
      entity->GetHandler()->SetMember(entity, memberId, info, newValue, oldValue);;
    }
  private:
    byte memberId;
    rpc::IRemoteEntity* entity;
  };
  typedef _StringAccessor<char> StringAccessor;
  typedef _StringAccessor<wchar_t> WStringAccessor;


  template <typename T>
  class _string : private nstl::basic_string<T>
  {
  public:
    _string():accessor(0) {}

    _string(_StringAccessor<T>* accessor):
    accessor(accessor)
    {
    }

    void assign(const T* value, bool log=false)
    {
      if (log)
      {
        accessor->Set(value, c_str());
      }
      nstl::basic_string<T>::assign(value);
    }
    const T* c_str() const { return nstl::basic_string<T>::c_str(); }

    T& operator [] (uint index) 
    {
      return nstl::basic_string<T>::operator[](index);
    }

    const T& operator [] (uint index) const 
    {
      return nstl::basic_string<T>::operator[](index);
    }

    void clear(bool log=false)
    {
      if (log)
      {
        // TODO: support clear
      }
      nstl::basic_string<T>::clear();
    }
    bool operator == (const _string<T>& rhs)
    {
        return nstl::basic_string<T>::operator==(rhs);
    }

    bool operator == (const nstl::basic_string<T>& rhs)
    {
        return (const nstl::basic_string<T>&)*this == rhs;
    }
  private:
    rpc::_StringAccessor<T>* accessor;
  };

  typedef _string<char> rpcstring;
  typedef _string<wchar_t> rpcwstring;
} // rpc
