#ifndef ICENSORCLIENT_H_INCLUDED
#define ICENSORCLIENT_H_INCLUDED

#include "System/EnumToString.h"
#include "System/Pointers/Pointers.h"

namespace censorship
{

typedef long long TRequestId;
typedef long long TAuxId;



namespace ECheckResult
{
  enum Enum
  {
    Clean,      //Нарушений правопорядка не обнаружено
    Dirty,      //В тексте были найдены недопустимые слова
    SvcFailure  //Отказ сервиса (Скорее всего, недоступен web-service)
  };

  NI_ENUM_DECL_STD;
}


// Через этот колбэк доставляется результат проверки
// Колбэк вызывается только из основного потока
// Поле "_filteredText" всегда содержит правильный текст, даже если _result=ECheckResult::Clean
class ICensorClientCallback : public IBaseInterfaceMT
{
  NI_DECLARE_CLASS_1( ICensorClientCallback, IBaseInterfaceMT );

public:
  virtual void TextCheckResult( TRequestId _reqId, TAuxId _auxId, ECheckResult::Enum _result, const wstring & _filteredText ) = 0;
};



class ICensorClient : public IBaseInterfaceMT
{
  NI_DECLARE_CLASS_1( ICensorClientCallback, IBaseInterfaceMT );

public:
  // Разместить запрос на проверку текста
  // Возвращает id запроса.
  // Если метод вернул 0, то сервис недоступен (скорее всего, перегружен). В таком случае колбэк не будет вызван.
  // Ограничение на длину очереди можно отключить, выставив в 0 параметр "censor_queue_limit"
  // Колбэк хранится по слабой ссылке
  // Вместе с запросом можно передать один 64битный пользовательский параметр
  virtual TRequestId Check( TAuxId _auxId, ICensorClientCallback * _callback, const wstring & _text ) = 0;

  // Стандартный полл сервиса. Именно из него будут вызываться все колбэки.
  // WARNING: Если между вызовами Poll будет обработано очень много запросов, то часть запросов будет отброшена без вызова колбеков.
  // Ограничение на длину очереди можно отключить, выставив в 0 параметр "censor_out_queue_limit"
  virtual void Poll() = 0;
};


ICensorClient * CreateClient();

} //namespace censorship

#endif //ICENSORCLIENT_H_INCLUDED
