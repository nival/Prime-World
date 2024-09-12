#pragma once

namespace Lobby
{

struct BuyResult
{
  bool isSuccessful;
  int currentAmount;
};

struct ServiceInfo
{
  int serviceId;
  int servicePrice;
};

} // Lobby