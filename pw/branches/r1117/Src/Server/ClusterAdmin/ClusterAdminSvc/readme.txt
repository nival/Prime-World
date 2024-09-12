+ clusteradmin'у не сообщается о нем как о started, только pending получаем
  сервис не включался в нотификацию ServiceStarted, - в runner'е сервисов надо делать coordClient->MakeFullServiceName.
  архитектура требующая переработки
+ уменьшить кол-во разных статусов у сервисов

+ разобраться в frontend интерфейсом - несколько relay'ев

thrift iface
+ сообщать pid
- сообщать machine
- сообщать uptime