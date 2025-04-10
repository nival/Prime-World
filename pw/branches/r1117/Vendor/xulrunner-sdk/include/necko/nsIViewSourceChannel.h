/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM e:/builds/moz2_slave/mozilla-1.9.1-win32-xulrunner/build/netwerk/protocol/viewsource/public/nsIViewSourceChannel.idl
 */

#ifndef __gen_nsIViewSourceChannel_h__
#define __gen_nsIViewSourceChannel_h__


#ifndef __gen_nsIChannel_h__
#include "nsIChannel.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif

/* starting interface:    nsIViewSourceChannel */
#define NS_IVIEWSOURCECHANNEL_IID_STR "8b77d6e2-2ae9-11d5-be57-000064657374"

#define NS_IVIEWSOURCECHANNEL_IID \
  {0x8b77d6e2, 0x2ae9, 0x11d5, \
    { 0xbe, 0x57, 0x00, 0x00, 0x64, 0x65, 0x73, 0x74 }}

class NS_NO_VTABLE nsIViewSourceChannel : public nsIChannel {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(NS_IVIEWSOURCECHANNEL_IID)

  /**
     * The actual (MIME) content type of the data.
     *
     * nsIViewSourceChannel returns a content type of
     * "application/x-view-source" if you ask it for the contentType
     * attribute.
     *
     * However, callers interested in finding out or setting the
     * actual content type can utilize this attribute.
     */
  /* attribute ACString originalContentType; */
  NS_IMETHOD GetOriginalContentType(nsACString & aOriginalContentType) = 0;
  NS_IMETHOD SetOriginalContentType(const nsACString & aOriginalContentType) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(nsIViewSourceChannel, NS_IVIEWSOURCECHANNEL_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIVIEWSOURCECHANNEL \
  NS_IMETHOD GetOriginalContentType(nsACString & aOriginalContentType); \
  NS_IMETHOD SetOriginalContentType(const nsACString & aOriginalContentType); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIVIEWSOURCECHANNEL(_to) \
  NS_IMETHOD GetOriginalContentType(nsACString & aOriginalContentType) { return _to GetOriginalContentType(aOriginalContentType); } \
  NS_IMETHOD SetOriginalContentType(const nsACString & aOriginalContentType) { return _to SetOriginalContentType(aOriginalContentType); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIVIEWSOURCECHANNEL(_to) \
  NS_IMETHOD GetOriginalContentType(nsACString & aOriginalContentType) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetOriginalContentType(aOriginalContentType); } \
  NS_IMETHOD SetOriginalContentType(const nsACString & aOriginalContentType) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetOriginalContentType(aOriginalContentType); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsViewSourceChannel : public nsIViewSourceChannel
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIVIEWSOURCECHANNEL

  nsViewSourceChannel();

private:
  ~nsViewSourceChannel();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsViewSourceChannel, nsIViewSourceChannel)

nsViewSourceChannel::nsViewSourceChannel()
{
  /* member initializers and constructor code */
}

nsViewSourceChannel::~nsViewSourceChannel()
{
  /* destructor code */
}

/* attribute ACString originalContentType; */
NS_IMETHODIMP nsViewSourceChannel::GetOriginalContentType(nsACString & aOriginalContentType)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsViewSourceChannel::SetOriginalContentType(const nsACString & aOriginalContentType)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIViewSourceChannel_h__ */
