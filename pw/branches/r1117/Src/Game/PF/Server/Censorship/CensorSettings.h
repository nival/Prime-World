#ifndef CENSORSETTINGS_H_INCLUDED
#define CENSORSETTINGS_H_INCLUDED

namespace censorship
{


struct SettingsStruct
{
  string        cleanSpeakUrl;
  string        cleanSpeakRequest;
  int           queueLimit;
  float         queueTimelimit;
  int           outQueueLimit;
  int           workers;

  SettingsStruct();
};



class Settings : public BaseObjectMT, public SettingsStruct
{
  NI_DECLARE_REFCOUNT_CLASS_1( Settings, BaseObjectMT );

public:
  Settings( const SettingsStruct & structSett );
};



StrongMT<Settings> CreateSettingsFromConfig();

} //namespace censorship

#endif //CENSORSETTINGS_H_INCLUDED
