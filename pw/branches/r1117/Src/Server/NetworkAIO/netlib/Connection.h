#pragma once

namespace netlib
{
  class IConnection : public IObjectBase
  {
  public:
    virtual int send(char const * data, unsigned int size) = 0;
    virtual int recv(char*& data, unsigned int& size) = 0;
    virtual int status() = 0;
    virtual void close() = 0;
  };

  class Connection : public IConnection, public CObjectBase
  {
    OBJECT_BASIC_METHODS(Connection);

  public:
    Connection();
    ~Connection();

  public:
    int send(char const * data, unsigned int size);
    int recv(char*& data, unsigned int& size);
    int status();
    void close();
  };
}
