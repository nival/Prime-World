/*********************************************************************
** Copyright (C) 2003 Terabit Pty Ltd.  All rights reserved.
**
** This file is part of the POSIX-Proactor module.
**
**  
**   
**
**
**
**
**
**********************************************************************/

/* -*- C++ -*- */

//=============================================================================
/**
 *  @file    Sock_Addr.h
 *
 *  $Id:  $
 *
 *  @author Alexander Libman <libman@terabit.com.au>
 */
//=============================================================================
#ifndef TRB_SOCK_ADDR_H 
#define TRB_SOCK_ADDR_H

#include /**/ "ace/pre.h"

#include "TProactor/TPROACTOR_Export.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
#pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include "ace/INET_Addr.h"
#include "ace/UNIX_Addr.h"

ACE_BEGIN_VERSIONED_NAMESPACE_DECL

class TPROACTOR_Export TRB_Sock_Addr
{
public:
    // area to locate any supported addresses
    union Area
    {
        struct  Dummy { void *dummy_; };
        
        Dummy dummy_;
        void *any_;
        long  long_;
        
        char  any_area_  [sizeof(ACE_Addr)];
        char  inet_area_ [sizeof(ACE_INET_Addr)];

#if !defined (ACE_LACKS_UNIX_DOMAIN_SOCKETS)
        char  unix_area_ [sizeof(ACE_UNIX_Addr)];
#endif 
    };


    static bool is_addresses_compatible (int type1, int type2);

    static int copy_addr(ACE_Addr& dst, const ACE_Addr& src);
    static int copy_addr(ACE_Addr& dst, const sockaddr *src, int size);


    ~TRB_Sock_Addr ();
    TRB_Sock_Addr (int type = AF_ANY);
    TRB_Sock_Addr (const TRB_Sock_Addr & other);
    TRB_Sock_Addr (const ACE_Addr& other);
    TRB_Sock_Addr (sockaddr *addr, int size);

    TRB_Sock_Addr& operator = (const TRB_Sock_Addr & other);
    TRB_Sock_Addr& operator = (const ACE_Addr & other);

    static int to_string (const ACE_Addr& addr,
                          char  *buf, 
                          size_t len,
                          int    format=1);

    int  to_string (char   *buf, 
                    size_t  len,
                    int     format=1) const;
    

    const ACE_Addr& get_ace_addr ()const;
    ACE_Addr& get_ace_addr ();

    const ACE_Addr& operator* () const { return get_ace_addr (); }
    ACE_Addr& operator* () { return get_ace_addr (); }

    operator const ACE_Addr& () const { return  get_ace_addr (); }
    operator ACE_Addr& () { return get_ace_addr (); }
    
    int   get_type () const;
    void *get_addr () const;

    void set_type (int type);
     
    void set (const TRB_Sock_Addr & other);
    void set (const ACE_Addr& other);
    void set (sockaddr *addr, int size);

    int  getpeername (ACE_HANDLE handle);
    int  getsockname (ACE_HANDLE handle);


    void clear ();

private:
    void delete_i ();
    void set_type_i (int type);
    void set_i (const ACE_Addr& other);
    void set_i (sockaddr *addr, int size);

    ACE_Addr* ace_addr_;
    Area      area_;
};

ACE_END_VERSIONED_NAMESPACE_DECL

#include "ace/post.h"
#endif // TRB_SOCK_ADDR_H 
