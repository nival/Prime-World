#ifndef FILESYSTEMCHANGESPROCESSOR_H_9A2
#define FILESYSTEMCHANGESPROCESSOR_H_9A2

_interface IFileWatcher;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
_interface IFileWatchFunctor
{
  virtual void Call( const string& fileName ) = 0;
  virtual bool Equals( IFileWatchFunctor* other ) = 0;
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class FileWatchFunctor : public IFileWatchFunctor
{	
public:
  typedef void (*Handler)( const string& fileName );

  FileWatchFunctor( Handler _handler ) : handler( _handler ) {}

  virtual void Call( const string& fileName )
  {
    handler( fileName );
  }
  virtual bool Equals( IFileWatchFunctor* other )
  {
    FileWatchFunctor* otherFunctor = dynamic_cast<FileWatchFunctor*>( other );
    if ( !otherFunctor )
      return false;
    return otherFunctor->handler == handler;
  }

private:
  Handler handler;
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T>
class FileWatchMethodFunctor : public IFileWatchFunctor
{	
public:
  typedef void (T::*Handler)( const string& fileName );

  FileWatchMethodFunctor( T* _pThis, Handler _handler ) : pThis( _pThis ), handler( _handler ) {}

  virtual void Call( const string& fileName )
  {
    (pThis->*handler)( fileName );
  }
  virtual bool Equals( IFileWatchFunctor* other )
  {
    FileWatchMethodFunctor<T>* otherFunctor = dynamic_cast<FileWatchMethodFunctor<T>*>( other );
    if ( !otherFunctor )
      return false;
    return otherFunctor->pThis == pThis && otherFunctor->handler == handler;
  }

private:
  T* pThis;
  Handler handler;
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class FileSystemChangesProcessor
{
public:
  FileSystemChangesProcessor();
  ~FileSystemChangesProcessor();

  void SetFileWatcher( IFileWatcher* fileWatcher );

  /**
  @brief Gets changed files and calls aporpriate functors
  */
  void ProcessFileWatchers();

  /**
  @brief Registers functor to observe all files with scpecified extension

  @param fileExt extension to watch for (contains initial dot, e.g. ".xdb", ".mayaStat")
  @param pFunctor functor to call on file change. FileSystemChangesProcessor takes 
  ownership on this object, so do not reference or delete this object.

  @return  false if pair (fileExt, function or method in pFunctor) already registered, true otherwise
  */
  bool RegisterFileWatchByExtension( const string& fileExt, IFileWatchFunctor* pFunctor );

  /**
  @brief Unregisters functor registered with RegisterFileWatchByExtension

  @param fileExt extension to watch for (contains initial dot, e.g. ".xdb", ".mayaStat")
  @param pFunctor fuctor to unregister. Functors are compared using its Equals method, not as pointers, 
  so you can pass temporary functor. See test for correct usage.

  @return  false if pair (fileExt, function or method in pFunctor) does not registered, true otherwise
  */
  bool UnregisterFileWatchByExtension( const string& fileExt, IFileWatchFunctor* pFunctor );

  /**
  @brief Registers functor to observe specific file

  @param fileName file to watch for (e.g. "UI/UIRoot.xdb")
  @param pFunctor functor to call on file change. FileSystemChangesProcessor takes 
  ownership on this object, so do not reference or delete this object.

  @return  false if pair (fileName, function or method in pFunctor) already registered, true otherwise
  */
  bool RegisterFileWatchByName( const string& fileName, IFileWatchFunctor* pFunctor );

  /**
  @brief Unregisters functor registered with RegisterFileWatchByName

  @param fileName file to watch for (e.g. "UI/UIRoot.xdb")
  @param pFunctor fuctor to unregister. Functors are compared using its Equals method, not as pointers, 
  so you can pass temporary functor. See test for correct usage.

  @return  false if pair (fileExt, function or method in pFunctor) does not registered, true otherwise
  */
  bool UnregisterFileWatchByName( const string& fileName, IFileWatchFunctor* pFunctor );
private:
  typedef hash_map<string, list<IFileWatchFunctor*> > TFunctorsMap;

  void CallFunctors( TFunctorsMap::iterator& itFunctor, const string& fileName );


  CObj<IFileWatcher> fileWatcher;
  TFunctorsMap functorsByExt;
  TFunctorsMap functorsByName;
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif //#define FILESYSTEMCHANGESPROCESSOR_H_9A2
