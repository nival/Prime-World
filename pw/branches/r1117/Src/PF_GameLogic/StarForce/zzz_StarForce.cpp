#include "stdafx.h"

// NOTE: имя файла и функции специально выбраны таким образом, чтобы компоновщик (linker) обрабатывал их в последнюю очередь.
// это workaround ошибки в софте StarForce: защититься не получится, если в секции с защищаемым кодом нет незащищенных функций.
// по рекомендации StarForce

#ifdef STARFORCE_PROTECTED

#include <System/StarForce/StarForce.h>

#pragma code_seg(push, "~")
STARFORCE_EXPORT void zzz()
{
  /* placeholder */
}
#pragma code_seg(pop)

#endif
