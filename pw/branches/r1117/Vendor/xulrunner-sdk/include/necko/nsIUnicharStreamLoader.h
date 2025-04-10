/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM e:/builds/moz2_slave/mozilla-1.9.1-win32-xulrunner/build/netwerk/base/public/nsIUnicharStreamLoader.idl
 */

#ifndef __gen_nsIUnicharStreamLoader_h__
#define __gen_nsIUnicharStreamLoader_h__


#ifndef __gen_nsIStreamListener_h__
#include "nsIStreamListener.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif
class nsIUnicharInputStream; /* forward declaration */

class nsIUnicharStreamLoader; /* forward declaration */

class nsIChannel; /* forward declaration */


/* starting interface:    nsIUnicharStreamLoaderObserver */
#define NS_IUNICHARSTREAMLOADEROBSERVER_IID_STR "6bb3e55b-69c0-4fc9-87e5-bed780d997ce"

#define NS_IUNICHARSTREAMLOADEROBSERVER_IID \
  {0x6bb3e55b, 0x69c0, 0x4fc9, \
    { 0x87, 0xe5, 0xbe, 0xd7, 0x80, 0xd9, 0x97, 0xce }}

class NS_NO_VTABLE NS_SCRIPTABLE nsIUnicharStreamLoaderObserver : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(NS_IUNICHARSTREAMLOADEROBSERVER_IID)

  /**
   * Called when the first full segment of data if available.
   *
   * @param aLoader the unichar stream loader
   * @param aContext the context parameter of the underlying channel
   * @param aFirstSegment the raw bytes of the first full data segment
   * @param aLength the length of aFirstSegment
   *
   * @return charset corresponding to this stream
   *
   * @note this method will only be called if the stream loader receives an
   *       OnDataAvailable call.
   */
  /* ACString onDetermineCharset (in nsIUnicharStreamLoader aLoader, in nsISupports aContext, [size_is (aLength)] in string aFirstSegment, in unsigned long aLength); */
  NS_SCRIPTABLE NS_IMETHOD OnDetermineCharset(nsIUnicharStreamLoader *aLoader, nsISupports *aContext, const char *aFirstSegment, PRUint32 aLength, nsACString & _retval NS_OUTPARAM) = 0;

  /**
   * Called when the entire stream has been loaded.
   *
   * @param aLoader the unichar stream loader
   * @param aContext the context parameter of the underlying channel
   * @param aStatus the status of the underlying channel
   * @param aUnicharData the unichar input stream containing the data.  This
   *        can be null in some failure conditions.
   *
   * This method will always be called asynchronously by the
   * nsUnicharIStreamLoader involved, on the thread that called the
   * loader's init() method.
   *
   * @note If the stream loader does not receive an OnDataAvailable call,
   *       aUnicharData will be null, and aStatus will be a success value.
   */
  /* void onStreamComplete (in nsIUnicharStreamLoader aLoader, in nsISupports aContext, in nsresult aStatus, in nsIUnicharInputStream aUnicharData); */
  NS_SCRIPTABLE NS_IMETHOD OnStreamComplete(nsIUnicharStreamLoader *aLoader, nsISupports *aContext, nsresult aStatus, nsIUnicharInputStream *aUnicharData) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(nsIUnicharStreamLoaderObserver, NS_IUNICHARSTREAMLOADEROBSERVER_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIUNICHARSTREAMLOADEROBSERVER \
  NS_SCRIPTABLE NS_IMETHOD OnDetermineCharset(nsIUnicharStreamLoader *aLoader, nsISupports *aContext, const char *aFirstSegment, PRUint32 aLength, nsACString & _retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD OnStreamComplete(nsIUnicharStreamLoader *aLoader, nsISupports *aContext, nsresult aStatus, nsIUnicharInputStream *aUnicharData); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIUNICHARSTREAMLOADEROBSERVER(_to) \
  NS_SCRIPTABLE NS_IMETHOD OnDetermineCharset(nsIUnicharStreamLoader *aLoader, nsISupports *aContext, const char *aFirstSegment, PRUint32 aLength, nsACString & _retval NS_OUTPARAM) { return _to OnDetermineCharset(aLoader, aContext, aFirstSegment, aLength, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD OnStreamComplete(nsIUnicharStreamLoader *aLoader, nsISupports *aContext, nsresult aStatus, nsIUnicharInputStream *aUnicharData) { return _to OnStreamComplete(aLoader, aContext, aStatus, aUnicharData); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIUNICHARSTREAMLOADEROBSERVER(_to) \
  NS_SCRIPTABLE NS_IMETHOD OnDetermineCharset(nsIUnicharStreamLoader *aLoader, nsISupports *aContext, const char *aFirstSegment, PRUint32 aLength, nsACString & _retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->OnDetermineCharset(aLoader, aContext, aFirstSegment, aLength, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD OnStreamComplete(nsIUnicharStreamLoader *aLoader, nsISupports *aContext, nsresult aStatus, nsIUnicharInputStream *aUnicharData) { return !_to ? NS_ERROR_NULL_POINTER : _to->OnStreamComplete(aLoader, aContext, aStatus, aUnicharData); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsUnicharStreamLoaderObserver : public nsIUnicharStreamLoaderObserver
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIUNICHARSTREAMLOADEROBSERVER

  nsUnicharStreamLoaderObserver();

private:
  ~nsUnicharStreamLoaderObserver();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsUnicharStreamLoaderObserver, nsIUnicharStreamLoaderObserver)

nsUnicharStreamLoaderObserver::nsUnicharStreamLoaderObserver()
{
  /* member initializers and constructor code */
}

nsUnicharStreamLoaderObserver::~nsUnicharStreamLoaderObserver()
{
  /* destructor code */
}

/* ACString onDetermineCharset (in nsIUnicharStreamLoader aLoader, in nsISupports aContext, [size_is (aLength)] in string aFirstSegment, in unsigned long aLength); */
NS_IMETHODIMP nsUnicharStreamLoaderObserver::OnDetermineCharset(nsIUnicharStreamLoader *aLoader, nsISupports *aContext, const char *aFirstSegment, PRUint32 aLength, nsACString & _retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void onStreamComplete (in nsIUnicharStreamLoader aLoader, in nsISupports aContext, in nsresult aStatus, in nsIUnicharInputStream aUnicharData); */
NS_IMETHODIMP nsUnicharStreamLoaderObserver::OnStreamComplete(nsIUnicharStreamLoader *aLoader, nsISupports *aContext, nsresult aStatus, nsIUnicharInputStream *aUnicharData)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


/* starting interface:    nsIUnicharStreamLoader */
#define NS_IUNICHARSTREAMLOADER_IID_STR "9037f476-7c08-4729-b690-3e425269802b"

#define NS_IUNICHARSTREAMLOADER_IID \
  {0x9037f476, 0x7c08, 0x4729, \
    { 0xb6, 0x90, 0x3e, 0x42, 0x52, 0x69, 0x80, 0x2b }}

class NS_NO_VTABLE NS_SCRIPTABLE nsIUnicharStreamLoader : public nsIStreamListener {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(NS_IUNICHARSTREAMLOADER_IID)

  /**
 * Asynchronously load a channel, converting the data to UTF-16.
 *
 * To use this interface, first call init() with a
 * nsIUnicharStreamLoaderObserver that will be notified when the data has been
 * loaded. Then call asyncOpen() on the channel with the nsIUnicharStreamLoader
 * as the listener. The context argument in the asyncOpen() call will be
 * passed to the onStreamComplete() callback.
 */
  enum { DEFAULT_SEGMENT_SIZE = 4096U };

  /**
   * Initializes the unichar stream loader
   *
   * @param aObserver the observer to notify when a charset is needed and when
   *        the load is complete
   * @param aSegmentSize the size of the segments to use for the data, in bytes
   */
  /* void init (in nsIUnicharStreamLoaderObserver aObserver, in unsigned long aSegmentSize); */
  NS_SCRIPTABLE NS_IMETHOD Init(nsIUnicharStreamLoaderObserver *aObserver, PRUint32 aSegmentSize) = 0;

  /**
   * The channel attribute is only valid inside the onDetermineCharset
   * and onStreamComplete callbacks.  Otherwise it will be null.
   */
  /* readonly attribute nsIChannel channel; */
  NS_SCRIPTABLE NS_IMETHOD GetChannel(nsIChannel * *aChannel) = 0;

  /**
   * The charset that onDetermineCharset returned, if that's been
   * called.
   */
  /* readonly attribute ACString charset; */
  NS_SCRIPTABLE NS_IMETHOD GetCharset(nsACString & aCharset) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(nsIUnicharStreamLoader, NS_IUNICHARSTREAMLOADER_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIUNICHARSTREAMLOADER \
  NS_SCRIPTABLE NS_IMETHOD Init(nsIUnicharStreamLoaderObserver *aObserver, PRUint32 aSegmentSize); \
  NS_SCRIPTABLE NS_IMETHOD GetChannel(nsIChannel * *aChannel); \
  NS_SCRIPTABLE NS_IMETHOD GetCharset(nsACString & aCharset); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIUNICHARSTREAMLOADER(_to) \
  NS_SCRIPTABLE NS_IMETHOD Init(nsIUnicharStreamLoaderObserver *aObserver, PRUint32 aSegmentSize) { return _to Init(aObserver, aSegmentSize); } \
  NS_SCRIPTABLE NS_IMETHOD GetChannel(nsIChannel * *aChannel) { return _to GetChannel(aChannel); } \
  NS_SCRIPTABLE NS_IMETHOD GetCharset(nsACString & aCharset) { return _to GetCharset(aCharset); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIUNICHARSTREAMLOADER(_to) \
  NS_SCRIPTABLE NS_IMETHOD Init(nsIUnicharStreamLoaderObserver *aObserver, PRUint32 aSegmentSize) { return !_to ? NS_ERROR_NULL_POINTER : _to->Init(aObserver, aSegmentSize); } \
  NS_SCRIPTABLE NS_IMETHOD GetChannel(nsIChannel * *aChannel) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetChannel(aChannel); } \
  NS_SCRIPTABLE NS_IMETHOD GetCharset(nsACString & aCharset) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetCharset(aCharset); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsUnicharStreamLoader : public nsIUnicharStreamLoader
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIUNICHARSTREAMLOADER

  nsUnicharStreamLoader();

private:
  ~nsUnicharStreamLoader();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsUnicharStreamLoader, nsIUnicharStreamLoader)

nsUnicharStreamLoader::nsUnicharStreamLoader()
{
  /* member initializers and constructor code */
}

nsUnicharStreamLoader::~nsUnicharStreamLoader()
{
  /* destructor code */
}

/* void init (in nsIUnicharStreamLoaderObserver aObserver, in unsigned long aSegmentSize); */
NS_IMETHODIMP nsUnicharStreamLoader::Init(nsIUnicharStreamLoaderObserver *aObserver, PRUint32 aSegmentSize)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute nsIChannel channel; */
NS_IMETHODIMP nsUnicharStreamLoader::GetChannel(nsIChannel * *aChannel)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute ACString charset; */
NS_IMETHODIMP nsUnicharStreamLoader::GetCharset(nsACString & aCharset)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIUnicharStreamLoader_h__ */
