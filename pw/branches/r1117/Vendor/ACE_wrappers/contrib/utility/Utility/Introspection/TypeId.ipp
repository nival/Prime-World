// file      : Utility/Introspection/TypeId.ipp
// author    : Boris Kolpackov <boris@kolpackov.net>
// copyright : Copyright (c) 2002-2003 Boris Kolpackov
// license   : http://kolpackov.net/license.html
// cvs-id    : $Id: TypeId.ipp 80826 2008-03-04 14:51:23Z wotte $

namespace Utility
{
  namespace Introspection
  {
    inline TypeId::
    TypeId (std::type_info const& tid)
        : tid_ (&tid)
    {
    }


    inline bool TypeId::
    operator == (TypeId const& other) const
    {
      return *tid_ == *other.tid_;
    }

    inline bool TypeId::
    operator != (TypeId const& other) const
    {
      return *tid_ != *other.tid_;
    }

    inline bool TypeId::
    operator < (TypeId const& other) const
    {
      return tid_->before (*other.tid_);
    }
  }
}
//$Id: TypeId.ipp 80826 2008-03-04 14:51:23Z wotte $
