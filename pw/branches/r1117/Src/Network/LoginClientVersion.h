#pragma once

namespace Login
{
  struct ClientVersion
  {
    ClientVersion()
      :major_(0),
      minor_(0),
      patch_(0),
      revision_(0)
    {
    }

    ClientVersion(unsigned short major, 
            unsigned short minor,
            unsigned int   patch,
            unsigned int   revision)
      :major_(major),
      minor_(minor),
      patch_(patch),
      revision_(revision)
    {
    }

    bool isEmpty() const
    {
      return (0 == major_ && 0 == minor_ && 0 == patch_ && 0 == revision_);
    }

    int checkCompatibility(ClientVersion const & clientVer) const
    {
      if (clientVer.major_ < major_)
        return -1;
      else if (clientVer.major_ > major_)
        return 1;

      if (clientVer.minor_ < minor_)
        return -1;
      else if (clientVer.minor_ > minor_)
        return 1;

      return 0;
    }

    int compare(ClientVersion const & clientVer) const
    {
      int res = checkCompatibility(clientVer);
      if (res)
        return res;

      // compare patch & revision
      if (clientVer.patch_ < patch_)
        return -1;
      else if (clientVer.patch_ > patch_)
        return 1;

      if (clientVer.revision_ < revision_)
        return -1;
      else if (clientVer.revision_ > revision_)
        return 1;

      return 0;
    }

    bool operator == (const ClientVersion & other) const
    {
      return compare( other ) == 0;
    }

    bool operator != (const ClientVersion & other) const
    {
      return compare( other ) != 0;
    }

    ZDATA
    unsigned short major_;
    unsigned short minor_;
    unsigned int   patch_;
    unsigned int   revision_;
    ZEND int operator&( IBinSaver &f ) { f.Add(2,&major_); f.Add(3,&minor_); f.Add(4,&patch_); f.Add(5,&revision_); return 0; }
  };
}
