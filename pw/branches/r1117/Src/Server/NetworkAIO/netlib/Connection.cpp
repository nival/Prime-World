#include "Connection.h"

namespace netlib
{
  Connection::Connection()
  {
  }

  Connection::~Connection()
  {
  }

  int Connection::send(char const * data, unsigned int size)
  {
    return 0;
  }

  int Connection::recv(char*& data, unsigned int& size)
  {
    return 0;
  }

  int Connection::status()
  {
    return 0;
  }

  void Connection::close()
  {
  }
}
