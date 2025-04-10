// Sock_Addr.cpp

#include "TProactor/Sock_Addr.h"
#include "ace/Log_Msg.h"
#include "ace/OS_NS_sys_socket.h"

ACE_BEGIN_VERSIONED_NAMESPACE_DECL


// ***********************************************************************
//  static address helper functions
// ***********************************************************************
bool
TRB_Sock_Addr::is_addresses_compatible (int type1, int type2)
{
    if (type1 == type2)
    {
        return true;
    }

#if defined (ACE_HAS_IPV6)
    if (type1 == AF_INET || type2 == AF_INET6)
    {
        return true;
    }

    if (type1 == AF_INET6 || type2 == AF_INET)
    {
        return true;
    }
#endif

    return false;
}

int
TRB_Sock_Addr::copy_addr (ACE_Addr& dst, const ACE_Addr& src)
{
    // TODO : add checking types
    int dst_type = dst.get_type ();
    int src_type = src.get_type ();

    if (is_addresses_compatible (src_type, dst_type))
    {
        void *from = src.get_addr ();
        int   len  = src.get_size ();
        if (from != 0 && len > 0)
        {
            dst.set_type (src_type);
            dst.set_addr (from, len);
            return 0;
        }
    }

    return -1;
}

int
TRB_Sock_Addr::copy_addr (ACE_Addr & dst, const sockaddr *src, int size)
{
    int  src_type = src->sa_family;
    int  dst_type = dst.get_type ();

    if (is_addresses_compatible (src_type, dst_type))
    {
        dst.set_type (src_type);
        dst.set_addr ((void*)src, size);
        return 0;
    }

    return -1;
}

// ***********************************************************************
//  TRB_Sock_Addr
// ***********************************************************************
TRB_Sock_Addr::~TRB_Sock_Addr ()
{
    this->delete_i ();
}

TRB_Sock_Addr::TRB_Sock_Addr (const TRB_Sock_Addr & other)
: ace_addr_ (0)
{
    this->set_i (other.get_ace_addr ());
}

TRB_Sock_Addr::TRB_Sock_Addr (const ACE_Addr& other)
: ace_addr_ (0)
{
    this->set_i (other);
}

TRB_Sock_Addr::TRB_Sock_Addr (sockaddr *addr, int size)
: ace_addr_ (0)
{
    this->set_i (addr, size);
}

TRB_Sock_Addr::TRB_Sock_Addr (int type)
: ace_addr_ (0)
{
    this->set_type_i (type);
}

TRB_Sock_Addr& 
TRB_Sock_Addr::operator = (const TRB_Sock_Addr & other)
{
    this->set (other);
    return *this;
}

TRB_Sock_Addr&
TRB_Sock_Addr::operator = (const ACE_Addr & other)
{
    this->set (other);
    return *this;
}

int
TRB_Sock_Addr::to_string (const ACE_Addr& addr,
                          char           *buf, 
                          size_t          len, 
                          int             ip_format)
{
    int rc = -1;
    if (buf == 0 ||len == 0)
    {
        return rc;
    }

    switch (addr.get_type ())
    {
    case AF_INET:
    case AF_INET6:
        {
           const ACE_INET_Addr & inet_addr = 
               static_cast<const ACE_INET_Addr&> (addr);

           rc = inet_addr.addr_to_string (buf, len, ip_format);
        }
        break;

#if !defined (ACE_LACKS_UNIX_DOMAIN_SOCKETS)
    case AF_UNIX:
        {
           const ACE_UNIX_Addr & unix_addr =
               static_cast<const ACE_UNIX_Addr&> (addr);

           rc = unix_addr.addr_to_string (buf, len);
        }
        break;

#endif

    default:
        *buf = '\0';
        break;
    }

    buf[len-1] = '\0';
    return rc;
}

int 
TRB_Sock_Addr::to_string (char *buf, size_t len, int ip_format) const 
{
    return TRB_Sock_Addr::to_string (get_ace_addr(), buf, len, ip_format);
}

void  *
TRB_Sock_Addr::get_addr () const
{
    return get_ace_addr ().get_addr ();
}

int
TRB_Sock_Addr::get_type () const
{
    return get_ace_addr ().get_type ();
}


ACE_Addr&
TRB_Sock_Addr::get_ace_addr ()
{
    ACE_ASSERT (this->ace_addr_ != 0);
    return *this->ace_addr_;
}

const ACE_Addr& 
TRB_Sock_Addr::get_ace_addr ()const
{
    ACE_ASSERT (this->ace_addr_ != 0);
    return *this->ace_addr_;
}

int 
TRB_Sock_Addr::getsockname (ACE_HANDLE h)
{
    union
    {
        sockaddr       addr_;
        sockaddr_in    in4_addr_;

#if defined (ACE_HAS_IPV6)
        sockaddr_in6   in6_addr_;
#endif 

#if !defined (ACE_LACKS_UNIX_DOMAIN_SOCKETS)
        sockaddr_un    unix_addr_;
#endif

    } addr;

    int len = sizeof (addr);
    if (ACE_OS::getsockname (h, &addr.addr_, &len) == 0)
    {
       this->set (&addr.addr_, len);
       return 0;
    } 

    ACE_ERROR ((LM_ERROR,
        ACE_TEXT ("(%t) TRB_Sock_Addr::getsockname %p\n"),
        ACE_TEXT ("failed")));
    return -1;
}

int 
TRB_Sock_Addr::getpeername (ACE_HANDLE h)
{
    union
    {
        sockaddr       addr_;
        sockaddr_in    in4_addr_;

#if defined (ACE_HAS_IPV6)
        sockaddr_in6   in6_addr_;
#endif 

#if !defined (ACE_LACKS_UNIX_DOMAIN_SOCKETS)
        sockaddr_un    unix_addr_;
#endif

    } addr;

    int len = sizeof (addr);
    if (ACE_OS::getpeername (h, &addr.addr_, &len) == 0)
    {
       this->set (&addr.addr_, len);
       return 0;
    } 

    ACE_ERROR ((LM_ERROR,
        ACE_TEXT ("(%t) TRB_Sock_Addr::getpeername %p\n"),
        ACE_TEXT ("failed")));
    return -1;
}

void 
TRB_Sock_Addr::clear ()
{
    this->delete_i ();
    this->set_type_i (AF_ANY);
}

void
TRB_Sock_Addr::set (const TRB_Sock_Addr & other)
{
    if (&other == this)
    {
        return;
    }
    return this->set (other.get_ace_addr ());
}

void
TRB_Sock_Addr::set (const ACE_Addr& other)
{
    if (&other == this->ace_addr_)
    {
        return;
    }

    this->delete_i ();
    this->set_i (other);
}

void
TRB_Sock_Addr::set (sockaddr *addr, int size)
{
    this->delete_i ();
    this->set_i (addr, size);
}

void
TRB_Sock_Addr::set_type (int type)
{
    if (this->get_type () != type)
    {
        this->delete_i ();
        this->set_type_i (type);
    }
}

// *******************************************************
//  private methods
// *******************************************************
void 
TRB_Sock_Addr::delete_i ()
{
    if (this->ace_addr_ != 0)
    {
        this->ace_addr_->~ACE_Addr();
        this->ace_addr_ = 0;
    }
}

void
TRB_Sock_Addr::set_i (const ACE_Addr & other)
{
    switch (other.get_type ())
    {
    case AF_INET:
    case AF_INET6:
        this->ace_addr_ =
            new (reinterpret_cast<ACE_INET_Addr *> (area_.inet_area_))
            ACE_INET_Addr (static_cast<const ACE_INET_Addr&> (other));
        break;

#if !defined (ACE_LACKS_UNIX_DOMAIN_SOCKETS)
    case AF_UNIX:
        this->ace_addr_ =
            new (reinterpret_cast<ACE_UNIX_Addr *> (area_.unix_area_))
            ACE_UNIX_Addr (static_cast<const ACE_UNIX_Addr&> (other));
        break;
#endif

    default:
        this->ace_addr_ =
            new (reinterpret_cast<ACE_Addr *> (area_.any_area_))
            ACE_Addr (AF_ANY, -1);
        break;
    }
}

void
TRB_Sock_Addr::set_i (sockaddr *addr, int size)
{
    switch (addr->sa_family)
    {
    case AF_INET:
    case AF_INET6:
        this->ace_addr_ =
            new (reinterpret_cast<ACE_INET_Addr *> (area_.inet_area_))
            ACE_INET_Addr ((sockaddr_in *) addr, size);
        break;

#if !defined (ACE_LACKS_UNIX_DOMAIN_SOCKETS)
    case AF_UNIX:
        this->ace_addr_ =
            new (reinterpret_cast<ACE_UNIX_Addr *> (area_.unix_area_))
            ACE_UNIX_Addr ();
            
        // to avoid ACE error
        this->copy_addr (*this->ace_addr_, addr, size);
        break;
#endif

    default:
        this->ace_addr_ =
            new (reinterpret_cast<ACE_Addr *> (area_.any_area_))
            ACE_Addr (AF_ANY, -1);
        break;
    }
}

void
TRB_Sock_Addr::set_type_i (int type)
{
    switch (type)
    {
    case AF_INET:
    case AF_INET6:
        this->ace_addr_ =
            new (reinterpret_cast<ACE_INET_Addr *> (area_.inet_area_))
            ACE_INET_Addr ();
        break;

#if !defined (ACE_LACKS_UNIX_DOMAIN_SOCKETS)
    case AF_UNIX:
        this->ace_addr_ =
            new (reinterpret_cast<ACE_UNIX_Addr *> (area_.unix_area_))
            ACE_UNIX_Addr ();
        break;
#endif

    default:
        this->ace_addr_ =
            new (reinterpret_cast<ACE_Addr *> (area_.any_area_))
            ACE_Addr (AF_ANY, -1);
        break;
    }
}

ACE_END_VERSIONED_NAMESPACE_DECL
