#ifndef CLIENTACCOUNTINGGADGET_H_INCLUDED
#define CLIENTACCOUNTINGGADGET_H_INCLUDED

#include "Server/Accounting/RLobbyAccounting.auto.h"


namespace lobby
{

//Вообще эту конструкцию надо бы прибить, но сейчас нет времени. Уж больно она проросла в миниигре...
class AccountingGadget : public NonCopyable
{
public:
  AccountingGadget(int _userId) : userId(_userId) {}

  template <typename T>
  void BlockMoney( int serviceId, T* object, void (T::*func)(int result) )
  {
    if (api)
    {
      api->BlockMoney(userId, serviceId, object, func);
    } else
    {
      (object->*func)(-1);
    }
  }

  void UnblockMoney( int blockId )
  {
    if (api)
    {
      api->UnblockMoney(userId, blockId);
    } 
  }

  template <typename T>
  void GetServicePrice( int serviceId, T* object, void (T::*func)(int result) )
  {
    if (api)
    {
      api->GetServicePrice(serviceId, object, func);
    } else
    {
      (object->*func)(0);
    }
  }

  template <typename T>
  void BuyBlockedService( int blockId, int serviceId, T* object, void (T::*func)(bool result) )
  {
    if (api)
    {
      api->BuyBlockedService(userId, blockId, serviceId, object, func);
    } else
    {
      (object->*func)(false);
    }
  }


  template <typename T>
  void GetMoney(T* object, void (T::*func)(int result) )
  {
    if (api)
    {
      api->GetMoney(userId, object, func);
    } else
    {
      (object->*func)(0);
    }
  }

  template <typename T>
  void BuyService( int nService, T* object, void (T::*func)(Lobby::BuyResult result) )
  {
    if (api)
    {
      api->BuyService(userId, nService, object, func);
    } else
    {
      Lobby::BuyResult result;
      result.currentAmount = 0;
      result.isSuccessful = false;
      (object->*func)(result);
    }
  }
  template <typename T>
  void TransferService( int nDstUSerID, int nService, T* object, void (T::*func)(bool result) )
  {
    if (api)
    {
      api->GiveMoneyToUser(userId, nDstUSerID ,nService, object, func);
    } else
    {
      (object->*func)(false);
    }
  }
  void SetAccountingApi(Lobby::RLobbyAccounting* _api) { api = _api; }
  inline int GetId() const { return userId; }
private:
  AccountingGadget() {}
  int userId;
  StrongMT<Lobby::RLobbyAccounting> api;
};

} //namespace lobby

#endif //CLIENTACCOUNTINGGADGET_H_INCLUDED
