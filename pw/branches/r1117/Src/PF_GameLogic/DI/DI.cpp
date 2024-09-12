#include "stdafx.h"
#include "DI.hpp"

// NOTE: предполагается, что ProviderManager живет в основном потоке.
// на практике так и получается. если что-то изменится, необходимо будет переработать.

namespace
{
  namespace EProviderManagerState
  {
    enum Enum
    {
      Uninitialized,
      Operational,
      Finished,
    };
  }

  // глобальное состояние необходимо из-за специфики работы CObjectBase, а именно того факта, что уничтоженные объекты тут же создаются вновь
  // таким образом, может получиться, что конструктор/деструктор какого-то DI-класса будет вызван после уничтожения ProviderManager
  static EProviderManagerState::Enum g_state = EProviderManagerState::Uninitialized;
}

namespace DI
{
  namespace Private
  {

    ProviderManager::ProviderManager()
      : providers()
    {
      NI_ASSERT(g_state == EProviderManagerState::Uninitialized, "Invariant");

      g_state = EProviderManagerState::Operational;
    }

    ProviderManager::~ProviderManager()
    {
      NI_ASSERT(g_state == EProviderManagerState::Operational, "Invariant");

      g_state = EProviderManagerState::Finished;
    }

    void ProviderManager::Register(const TypeInfo& tag, const ProviderPtr provider)
    {
      if (g_state != EProviderManagerState::Operational)
        return;

      DevTrace("DI: registering '%s'...", tag.Get().name());

      if (!provider)
      {
        Unregister(tag, NULL);
        return;
      }

      ProviderMap::const_iterator it = providers.find(tag);

      if (it != providers.end())
      {
        NI_ASSERT(it->second == provider, "DI: provider with that tag is already registered!");
        return;
      }

      providers[tag] = provider;

      DevTrace("DI: registered '%s'", tag.Get().name());
    }

    void ProviderManager::Unregister(const TypeInfo& tag, const ProviderPtr provider)
    {
      if (g_state != EProviderManagerState::Operational)
        return;

      DevTrace("DI: unregistering '%s'...", tag.Get().name());

      ProviderMap::iterator it = providers.find(tag);

      if (it == providers.end())
        return;

      if (provider)
      {
        NI_VERIFY(it->second == provider, "DI: trying to unregister foreign provider!", return);
      }

      providers.erase(it);

      DevTrace("DI: unregistered '%s'", tag.Get().name());
    }

    ProviderPtr ProviderManager::Get(const TypeInfo& tag) const
    {
      if (g_state != EProviderManagerState::Operational)
        return NULL;

      ProviderMap::const_iterator it = providers.find(tag);

      if (it == providers.end())
        return NULL;

      return it->second;
    }

    ProviderManager& ProviderManager::Instance()
    {
      static ProviderManager instance;

      return instance;
    }

  }
}
