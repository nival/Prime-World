#ifndef SIMPLEFILELIST_H_INCLUDED
#define SIMPLEFILELIST_H_INCLUDED

namespace fileSystem
{

class SimpleFileList : public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_1( SimpleFileList, BaseObjectST );

public:
  SimpleFileList() {}
  ~SimpleFileList() {}

  bool Load( const char * filename );

  const string Filename() const { return filename; }
  const vector<string> & Access() const { return log; }

private:
  string filename;
  vector<string> log;
};

} //namespace fileSystem


#endif //SIMPLEFILELIST_H_INCLUDED
