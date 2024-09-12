#ifndef SYSTEM_POINTERS_H_INCLUDED
#define SYSTEM_POINTERS_H_INCLUDED

#include "BaseInterface.h"
#include "BaseObjectST.h"
#include "BaseObjectMT.h"
#include "Strong.h"
#include "Weak.h"
#include "WeakMT.h"


//TODO: remove this
//Функции нужны только для улучшения совместимости со старым кодом

template<class T>
inline bool IsValid( const Strong<T> & p ) { return p.Valid(); }

template<class T>
inline bool IsValid( const StrongMT<T> & p ) { return p.Valid(); }

template<class T>
inline bool IsValid( const Weak<T> & p ) { return p.Valid(); }

inline bool IsValid( IBaseInterfaceST * p ) { return p ? true : false; }
inline bool IsValid( BaseObjectST * p ) { return p ? true : false; }


#endif //SYSTEM_POINTERS_H_INCLUDED
