#pragma once

#include "TypeInfo.hpp"

#include <boost/type_traits.hpp>

#include <boost/mpl/list.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/same_as.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/find_if.hpp>
#include <boost/mpl/end.hpp>

namespace DI
{
  namespace Detail
  {
    class Provider
      : public NonCopyable
    {
    public:
      virtual void* GetInstance() const = 0;
    protected:
      Provider() {}
      virtual ~Provider() {}
    };

    typedef Provider& ProviderRef;
    typedef Provider* ProviderPtr;
  }

  namespace Private
  {
    using Detail::Provider;
    using Detail::ProviderRef;
    using Detail::ProviderPtr;
    using Detail::TypeInfo;

    class ProviderManager : public NonCopyable
    {
    public:
      void Register(const TypeInfo& tag, const ProviderPtr provider);
      void Unregister(const TypeInfo& tag, const ProviderPtr provider);

      ProviderPtr Get(const TypeInfo& tag) const;

      static ProviderManager& Instance();
    private:
      typedef map<TypeInfo, ProviderPtr> ProviderMap;

      ProviderManager();
      ~ProviderManager();

      ProviderMap providers;
    };
  }

  namespace Detail
  {
    template <class T>
    struct CheckDependencyType
      : boost::true_type
    {
    };

    template <class T>
    struct CheckDependencyType<T*>
      : boost::false_type
    {
    };

    template <class T>
    struct CheckDependencyType<T&>
      : boost::false_type
    {
    };

    template <class T>
    struct CheckDependencyType<T[]>
      : boost::false_type
    {
    };

    template <class T, int N>
    struct CheckDependencyType<T[N]>
      : boost::false_type
    {
    };
  }

  template <class T, const bool = Detail::CheckDependencyType<T>::value>
  struct SelfProvider
  {
    BOOST_STATIC_ASSERT_MSG(false, "Invalid provider definition!");
  };

  template <class T>
  struct SelfProvider<T, true>
  {
  private:
    typedef typename boost::remove_cv<T>::type TagType;

    class Impl
      : public Detail::Provider
    {
    public:
      Impl()
        : self(NULL)
      {
        const Detail::TypeInfo tag(Detail::TypeInfo::Make<TagType>());

        Private::ProviderManager::Instance().Register(tag, this);
      }

      ~Impl()
      {
        const Detail::TypeInfo tag(Detail::TypeInfo::Make<TagType>());

        Private::ProviderManager::Instance().Unregister(tag, this);
      }

      void SetInstance(T* const p)
      {
        self = p;
      }

      virtual void* GetInstance() const
      {
        return self;
      }
    private:
      T* self;
    };

    Impl _provider;
  protected:
    SelfProvider()
    {
      _provider.SetInstance(static_cast<T*>(this));
    }
    
    virtual ~SelfProvider()
    {
      _provider.SetInstance(NULL);
    }
  };

  namespace InjectorPolicy
  {
    struct Strong {};
    struct Weak {};
    struct Raw {};
  }

  namespace Detail
  {
    namespace mpl = boost::mpl;

    template <class T, class Base, class Policy>
    struct PointerTypeSelector;

    template <class T> struct PointerTypeSelector<T, IObjectBase, InjectorPolicy::Strong>       { typedef CObj<T>     Type; };
    template <class T> struct PointerTypeSelector<T, IObjectBase, InjectorPolicy::Weak>         { typedef CPtr<T>     Type; };
    template <class T> struct PointerTypeSelector<T, IBaseInterfaceST, InjectorPolicy::Strong>  { typedef Strong<T>   Type; };
    template <class T> struct PointerTypeSelector<T, IBaseInterfaceST, InjectorPolicy::Weak>    { typedef Weak<T>     Type; };
    template <class T> struct PointerTypeSelector<T, IBaseInterfaceMT, InjectorPolicy::Strong>  { typedef StrongMT<T> Type; };
    template <class T> struct PointerTypeSelector<T, IBaseInterfaceMT, InjectorPolicy::Weak>    { typedef WeakMT<T>   Type; };

    template <class T, class Base> struct PointerTypeSelector<T, Base, InjectorPolicy::Strong>  { typedef T*          Type; };
    template <class T, class Base> struct PointerTypeSelector<T, Base, InjectorPolicy::Weak>    { typedef T*          Type; };
    template <class T, class Base> struct PointerTypeSelector<T, Base, InjectorPolicy::Raw>     { typedef T*          Type; };

    template <class T>
    struct HierarchyRootSelector
    {
      struct NoRoot {};

      // список базовых классов иерархий, к которым применимы умные указатели
      typedef mpl::list3<IObjectBase, IBaseInterfaceST, IBaseInterfaceMT> Roots;
      // итератор конца списка базовых классов
      typedef typename mpl::end<Roots>::type RootsEnd;
      // предикат поиска: проверяет, является ли член списка базовым классом для T
      typedef boost::is_base_of<mpl::_1, T> Predicate;
      // итератор результата поиска
      typedef typename mpl::find_if<Roots, Predicate>::type Root;

      // результат. вернуть NoRoot если соотвествующий базовый класс не найден, иначе вернуть базовый класс
      typedef typename mpl::if_c<boost::is_same<Root, RootsEnd>::value, NoRoot, typename mpl::deref<Root>::type>::type Type;
    };

    template <class T, class Policy>
    struct InjectorStorageSelector
    {
      typedef typename PointerTypeSelector<T, typename HierarchyRootSelector<T>::Type, Policy>::Type Type;
    };
  }

  template <class T, class Policy = InjectorPolicy::Weak, const bool = Detail::CheckDependencyType<T>::value>
  struct Injector
  {
    BOOST_STATIC_ASSERT_MSG(false, "Invalid injector definition!");
  };

  namespace
  {
    struct UnspecifiedBool
    {
      typedef void (*ResultType)();

      static void True()
      {
        /* dummy */
      }
    };

    typedef UnspecifiedBool::ResultType UnspecifiedBoolType;

    template <typename T>
    static UnspecifiedBoolType GetUnspecifiedBool(T condition)
    {
      return !!condition ? &UnspecifiedBool::True : NULL;
    }
  }

  template <class T, class Policy>
  struct Injector<T, Policy, true>
    : public NonCopyable
  {
    typedef typename boost::remove_cv<T>::type TagType;

    typedef T& InstanceRef;
    typedef T* InstancePtr;

    typedef typename Detail::InjectorStorageSelector<T, Policy>::Type StorageType;

    inline const StorageType& GetInstance() const
    {
      if (IsValid(holder))
        return holder;

      const Detail::TypeInfo tag(Detail::TypeInfo::Make<TagType>());
      const Detail::ProviderPtr provider(Private::ProviderManager::Instance().Get(tag));

      if (provider)
      {
        InstancePtr const instance = static_cast<InstancePtr>(provider->GetInstance());

        holder = instance;
      }
      else
      {
        holder = NULL;
      }

      return holder;
    }

    inline InstanceRef operator*() const
    {
      const StorageType& instance = GetInstance();
      NI_ASSERT(IsValid(instance), "Invalid instance!");
      return *instance;
    }

    inline InstancePtr operator->() const
    {
      return GetInstance();
    }

    inline operator UnspecifiedBoolType() const
    {
      return GetUnspecifiedBool(GetInstance());
    }

    inline bool operator!() const
    {
      return !IsValid(GetInstance());
    }

    inline operator const StorageType&() const
    {
      return holder;
    }
  private:
    mutable StorageType holder;
  };
}

template <class T, class Policy>
inline bool IsValid(const ::DI::Injector<T, Policy, true>& injector)
{
  return IsValid(injector.GetInstance());
}

template <class T, class Policy>
inline bool IsValid(const ::DI::Injector<T, Policy, false>& injector)
{
  return false;
}

#define DI_STRONG(_)    const ::DI::Injector< _ , ::DI::InjectorPolicy::Strong>
#define DI_WEAK(_)      const ::DI::Injector< _ , ::DI::InjectorPolicy::Weak>
#define DI_RAW(_)       const ::DI::Injector< _ , ::DI::InjectorPolicy::Raw>
