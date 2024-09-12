#include <System/stdafx.h>
#include <Server/ZZima/ZZimaService.h>

int main (int argc, char *argv[]) 
{
  ZZima::InvokerOld invoker("http://zzapi.SITE.com/zzimaApi", "api_key", "api_secret");
  ZZima::UserInfo info;
  if (ZZima::GetUserInfo(invoker, "user_id", info) == ZZima::E_OK)
  {
  }
  return 0;
}
//http://SITE:35090

