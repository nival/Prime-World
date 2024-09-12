#ifndef APPINSTANCESLIMIT_H_INCLUDED
#define APPINSTANCESLIMIT_H_INCLUDED

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class AppInstancesLimit
{
public:
  AppInstancesLimit( const char * appKeyName );
  ~AppInstancesLimit();

  bool Lock( int limit );

  int Index() const { return index; }

private:
  string key;
  HANDLE winMutex;
  int index;
};

#endif //APPINSTANCESLIMIT_H_INCLUDED
