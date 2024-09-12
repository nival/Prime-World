#ifndef IFILESYSTEMDEBUGMONITOR_H_INCLUDED
#define IFILESYSTEMDEBUGMONITOR_H_INCLUDED

_interface IFileSystemDebugMonitor : public IObjectBase
{
  virtual void OnGetDirectories( const string & root, NHPTimer::FTime timeSpent ) = 0;
  virtual void OnGetFiles( const string & root, NHPTimer::FTime timeSpent ) = 0;
  virtual void OnGetFileInfo( const string & fileName, NHPTimer::FTime timeSpent ) = 0;
  virtual void OnOpenFile( const string & fileName, NHPTimer::FTime timeSpent, unsigned size ) = 0;
};

#endif //IFILESYSTEMDEBUGMONITOR_H_INCLUDED
