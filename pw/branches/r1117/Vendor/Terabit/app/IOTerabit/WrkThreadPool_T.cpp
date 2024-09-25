/*********************************************************************
** Copyright (C) 2003 Terabit Pty Ltd.  All rights reserved.
**
** This file is part of the POSIX-Proactor module.
**
**  
**   @file WrkThreadPool.cpp 
**  
**  
**   @author Alexander Libman <libman@terabit.com.au>
**
**
**********************************************************************/

#include "IOTerabit/WrkThreadPool_T.h"


namespace Terabit {

class X 
{
public:
    void cancel () {}
    void set (X &x) {}
    void execute () {}
    void reset () {}
};

typedef WrkThreadPool_T<X> XPool;

void foo()
{
    XPool z("ZZZ");
    z.start(1);
}


}  //namespace Terabit 


