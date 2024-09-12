#ifndef FSACTIVITYLOGREADER_H_INCLUDED
#define FSACTIVITYLOGREADER_H_INCLUDED

namespace fileSystem
{

class ActivityLogReader //: public BaseObjectST
{
 // NI_DECLARE_REFCOUNT_CLASS_1( ActivityLogReader, BaseObjectST );

public:
  enum ELogEntryType
  {
    eGetFileInfo,
    eOpenFile,
    eGetFiles,
    eGetDirectories
  };

  struct SLogEntry
  {
    ELogEntryType type;
    float         time;
    unsigned      size;
    string        filename;
    SLogEntry() : type( eGetFileInfo ), time( 0 ), size( 0 ) {}
  };

  ActivityLogReader() {}
  ~ActivityLogReader() {}

  bool Load( const char * filename );

  const string Filename() const { return filename; }
  const vector<SLogEntry> & Access() const { return log; }

private:
  string filename;
  vector<SLogEntry> log;
};

} //namespace fileSystem

#endif  // FSACTIVITYLOGREADER_H_INCLUDED
