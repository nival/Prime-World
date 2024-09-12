#ifndef NOTIFIER_H_9B37D027_F9E6_4B4C_9A
#define NOTIFIER_H_9B37D027_F9E6_4B4C_9A

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 template<class TParam>
_interface INotifyCallback
{
  virtual void Call( const TParam& param ) = 0;
  virtual bool Equals( INotifyCallback* other ) = 0;
  virtual bool OwnerByNotifier() const = 0;
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, class TParam, bool ownerByNotifier = false>
class MethodNotifyCallback : public INotifyCallback<TParam>
{	
public:
  typedef void (T::*Handler)( const TParam& param );

  MethodNotifyCallback( T* _pThis, Handler _handler ) : pThis( _pThis ), handler( _handler ) {}

  virtual void Call( const TParam& param )
  {
    (pThis->*handler)( param );
  }
  virtual bool Equals( INotifyCallback<TParam>* other )
  {
    MethodNotifyCallback<T, TParam,ownerByNotifier>* otherFunctor = dynamic_cast<MethodNotifyCallback<T, TParam,ownerByNotifier>*>( other );
    if ( !otherFunctor )
      return false;
    return otherFunctor->pThis == pThis && otherFunctor->handler == handler;
  }
  virtual bool OwnerByNotifier() const { return ownerByNotifier; }
private:
  T* pThis;
  Handler handler;
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class TParam>
struct Notifier
{
  Notifier() {}
  ~Notifier();

  void Notify( const TParam& param );
  bool Empty() const { return functors.empty(); }

  template<class T, typename P>
  bool Subscribe( T* _pThis, P _handler )
  {
    return Subscribe_( new MethodNotifyCallback<T,TParam,true>( _pThis, _handler ) );
  }
  template<class T, typename P>
  bool Unsubscribe( T* _pThis, P _handler )
  {
    MethodNotifyCallback<T,TParam,true> f( _pThis, _handler );
    return Unsubscribe_( &f );
  }
  bool Subscribe_( INotifyCallback<TParam>* pFunctor );
  bool Unsubscribe_( INotifyCallback<TParam>* pFunctor );
private:
  typedef list<INotifyCallback<TParam>*> TFunctors;
  TFunctors functors;
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class TKey, class TParam>
struct NotifiersRegistry
{
  void Notify( const TKey& key, const TParam& param )
  {                
    typename TNotifiersMap::iterator itFunctor = notifiers.find( key );
    if ( itFunctor != notifiers.end() )
      itFunctor->second.Notify( param );
  }

  bool Subscribe_( const TKey& key, INotifyCallback<TParam>* pFunctor )
  {
    Notifier<TParam>& notifier = notifiers[ key ];
    return notifier.Subscribe_( pFunctor );
  }

  bool Unsubscribe_( const TKey& key, INotifyCallback<TParam>* pFunctor )
  {
    Notifier<TParam>& notifier = notifiers[ key ];
    bool res = notifier.Unsubscribe_( pFunctor );
    if ( notifier.Empty() )
      notifiers.erase( key );
    return res;
  }

  template<class T, typename P>
  bool Subscribe( TKey key, T* _pThis, P _handler )
  {
    Notifier<TParam>& notifier = notifiers[ key ];
    return notifier.Subscribe( _pThis, _handler );
  }

  template<class T, typename P>
  bool Unsubscribe( TKey key, T* _pThis, P _handler )
  {
    Notifier<TParam>& notifier = notifiers[ key ];
    bool res = notifier.Unsubscribe( _pThis, _handler );
    if ( notifier.Empty() )
      notifiers.erase( key );
    return res;
  }
private:
  typedef hash_map<TKey, Notifier<TParam> > TNotifiersMap;
  TNotifiersMap notifiers;
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class TParam>
Notifier<TParam>::~Notifier()
{
  for ( typename TFunctors::iterator it = functors.begin(), itEnd = functors.end(); it != itEnd; ++it )
    if( (*it)->OwnerByNotifier() )
      delete *it;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class TParam>
void Notifier<TParam>::Notify( const TParam& param )
{
  TFunctors savedFunctors( functors );

  for ( typename TFunctors::iterator it = savedFunctors.begin(), itEnd = savedFunctors.end(); it != itEnd; ++it )
  {
    (*it)->Call( param );
  }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class TParam>
bool Notifier<TParam>::Subscribe_( INotifyCallback<TParam>* pFunctor )
{
  for ( typename TFunctors::iterator it = functors.begin(), itEnd = functors.end(); it != itEnd; ++it )
  {
    NI_VERIFY( !pFunctor->Equals( *it ), "Duplicate functor found", if( pFunctor->OwnerByNotifier() ) delete pFunctor; return false);
  }

  functors.push_back( pFunctor );
  return true;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class TParam>
bool Notifier<TParam>::Unsubscribe_( INotifyCallback<TParam>* pFunctor )
{
  for ( typename TFunctors::iterator it = functors.begin(), itEnd = functors.end(); it != itEnd; ++it )
  {
    if ( pFunctor->Equals( *it ) )
    {
      if( (*it)->OwnerByNotifier() )
        delete *it;
      functors.erase( it );
      return true;
    }
  }
 // NI_ALWAYS_ASSERT( "Cannot find functor to unsubscribe" );
  return false;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif //#define NOTIFIER_H_9B37D027_F9E6_4B4C_9A
