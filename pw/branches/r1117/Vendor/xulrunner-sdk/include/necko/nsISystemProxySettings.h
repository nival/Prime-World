/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM e:/builds/moz2_slave/mozilla-1.9.1-win32-xulrunner/build/netwerk/base/public/nsISystemProxySettings.idl
 */

#ifndef __gen_nsISystemProxySettings_h__
#define __gen_nsISystemProxySettings_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

#ifndef __gen_nsIURI_h__
#include "nsIURI.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif

/* starting interface:    nsISystemProxySettings */
#define NS_ISYSTEMPROXYSETTINGS_IID_STR "a9f3ae38-b769-4e0b-9317-578388e326c9"

#define NS_ISYSTEMPROXYSETTINGS_IID \
  {0xa9f3ae38, 0xb769, 0x4e0b, \
    { 0x93, 0x17, 0x57, 0x83, 0x88, 0xe3, 0x26, 0xc9 }}

/** 
 * This interface allows the proxy code to use platform-specific proxy
 * settings when the proxy preference is set to "automatic discovery". This service
 * acts like a PAC parser to netwerk, but it will actually read the system settings and
 * either return the proper proxy data from the autoconfig URL specified in the system proxy,
 * or generate proxy data based on the system's manual proxy settings.
 */
class NS_NO_VTABLE NS_SCRIPTABLE nsISystemProxySettings : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(NS_ISYSTEMPROXYSETTINGS_IID)

  /**
     * If non-empty, use this PAC file. If empty, call getProxyForURI instead.
     */
  /* readonly attribute AUTF8String PACURI; */
  NS_SCRIPTABLE NS_IMETHOD GetPACURI(nsACString & aPACURI) = 0;

  /**
     * See nsIProxyAutoConfig::getProxyForURI; this function behaves exactly
     * the same way.
     */
  /* AUTF8String getProxyForURI (in nsIURI aURI); */
  NS_SCRIPTABLE NS_IMETHOD GetProxyForURI(nsIURI *aURI, nsACString & _retval NS_OUTPARAM) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(nsISystemProxySettings, NS_ISYSTEMPROXYSETTINGS_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSISYSTEMPROXYSETTINGS \
  NS_SCRIPTABLE NS_IMETHOD GetPACURI(nsACString & aPACURI); \
  NS_SCRIPTABLE NS_IMETHOD GetProxyForURI(nsIURI *aURI, nsACString & _retval NS_OUTPARAM); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSISYSTEMPROXYSETTINGS(_to) \
  NS_SCRIPTABLE NS_IMETHOD GetPACURI(nsACString & aPACURI) { return _to GetPACURI(aPACURI); } \
  NS_SCRIPTABLE NS_IMETHOD GetProxyForURI(nsIURI *aURI, nsACString & _retval NS_OUTPARAM) { return _to GetProxyForURI(aURI, _retval); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSISYSTEMPROXYSETTINGS(_to) \
  NS_SCRIPTABLE NS_IMETHOD GetPACURI(nsACString & aPACURI) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetPACURI(aPACURI); } \
  NS_SCRIPTABLE NS_IMETHOD GetProxyForURI(nsIURI *aURI, nsACString & _retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetProxyForURI(aURI, _retval); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsSystemProxySettings : public nsISystemProxySettings
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSISYSTEMPROXYSETTINGS

  nsSystemProxySettings();

private:
  ~nsSystemProxySettings();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsSystemProxySettings, nsISystemProxySettings)

nsSystemProxySettings::nsSystemProxySettings()
{
  /* member initializers and constructor code */
}

nsSystemProxySettings::~nsSystemProxySettings()
{
  /* destructor code */
}

/* readonly attribute AUTF8String PACURI; */
NS_IMETHODIMP nsSystemProxySettings::GetPACURI(nsACString & aPACURI)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* AUTF8String getProxyForURI (in nsIURI aURI); */
NS_IMETHODIMP nsSystemProxySettings::GetProxyForURI(nsIURI *aURI, nsACString & _retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsISystemProxySettings_h__ */
