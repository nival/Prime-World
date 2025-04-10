/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM e:/builds/moz2_slave/mozilla-1.9.1-win32-xulrunner/build/netwerk/socket/base/nsITransportSecurityInfo.idl
 */

#ifndef __gen_nsITransportSecurityInfo_h__
#define __gen_nsITransportSecurityInfo_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif

/* starting interface:    nsITransportSecurityInfo */
#define NS_ITRANSPORTSECURITYINFO_IID_STR "0d0a6b62-d4a9-402e-a197-6bc6e358fec9"

#define NS_ITRANSPORTSECURITYINFO_IID \
  {0x0d0a6b62, 0xd4a9, 0x402e, \
    { 0xa1, 0x97, 0x6b, 0xc6, 0xe3, 0x58, 0xfe, 0xc9 }}

class NS_NO_VTABLE NS_SCRIPTABLE nsITransportSecurityInfo : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(NS_ITRANSPORTSECURITYINFO_IID)

  /* readonly attribute unsigned long securityState; */
  NS_SCRIPTABLE NS_IMETHOD GetSecurityState(PRUint32 *aSecurityState) = 0;

  /* readonly attribute wstring shortSecurityDescription; */
  NS_SCRIPTABLE NS_IMETHOD GetShortSecurityDescription(PRUnichar * *aShortSecurityDescription) = 0;

  /* readonly attribute wstring errorMessage; */
  NS_SCRIPTABLE NS_IMETHOD GetErrorMessage(PRUnichar * *aErrorMessage) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(nsITransportSecurityInfo, NS_ITRANSPORTSECURITYINFO_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSITRANSPORTSECURITYINFO \
  NS_SCRIPTABLE NS_IMETHOD GetSecurityState(PRUint32 *aSecurityState); \
  NS_SCRIPTABLE NS_IMETHOD GetShortSecurityDescription(PRUnichar * *aShortSecurityDescription); \
  NS_SCRIPTABLE NS_IMETHOD GetErrorMessage(PRUnichar * *aErrorMessage); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSITRANSPORTSECURITYINFO(_to) \
  NS_SCRIPTABLE NS_IMETHOD GetSecurityState(PRUint32 *aSecurityState) { return _to GetSecurityState(aSecurityState); } \
  NS_SCRIPTABLE NS_IMETHOD GetShortSecurityDescription(PRUnichar * *aShortSecurityDescription) { return _to GetShortSecurityDescription(aShortSecurityDescription); } \
  NS_SCRIPTABLE NS_IMETHOD GetErrorMessage(PRUnichar * *aErrorMessage) { return _to GetErrorMessage(aErrorMessage); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSITRANSPORTSECURITYINFO(_to) \
  NS_SCRIPTABLE NS_IMETHOD GetSecurityState(PRUint32 *aSecurityState) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetSecurityState(aSecurityState); } \
  NS_SCRIPTABLE NS_IMETHOD GetShortSecurityDescription(PRUnichar * *aShortSecurityDescription) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetShortSecurityDescription(aShortSecurityDescription); } \
  NS_SCRIPTABLE NS_IMETHOD GetErrorMessage(PRUnichar * *aErrorMessage) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetErrorMessage(aErrorMessage); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsTransportSecurityInfo : public nsITransportSecurityInfo
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSITRANSPORTSECURITYINFO

  nsTransportSecurityInfo();

private:
  ~nsTransportSecurityInfo();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsTransportSecurityInfo, nsITransportSecurityInfo)

nsTransportSecurityInfo::nsTransportSecurityInfo()
{
  /* member initializers and constructor code */
}

nsTransportSecurityInfo::~nsTransportSecurityInfo()
{
  /* destructor code */
}

/* readonly attribute unsigned long securityState; */
NS_IMETHODIMP nsTransportSecurityInfo::GetSecurityState(PRUint32 *aSecurityState)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute wstring shortSecurityDescription; */
NS_IMETHODIMP nsTransportSecurityInfo::GetShortSecurityDescription(PRUnichar * *aShortSecurityDescription)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* readonly attribute wstring errorMessage; */
NS_IMETHODIMP nsTransportSecurityInfo::GetErrorMessage(PRUnichar * *aErrorMessage)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsITransportSecurityInfo_h__ */
