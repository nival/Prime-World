#ifdef _WIN32
#if !defined (WSDLPULL_EXPORT_H)
#define WSDLPULL_EXPORT_H

#ifndef WSDLPULL_EXPORT
  #if (defined _MSC_VER) && (defined _MT)
    /*
    * For Windows builds
    * Note: all Microsoft compilers define the _MSC_VER macro.
    *       The _MT macro is defined for multithreaded builds.
    */ 
    #if defined(DLLEXPORT)
      // DLLEXPORT is used when creating a LIB or DLL
      #define WSDLPULL_EXPORT __declspec (dllexport)
    #else
      // DLLIMPORT is used by consumers of LIBs and DLLs.
      // Set this as the default
      #define WSDLPULL_EXPORT __declspec (dllimport)
    #endif
  #else
    /*
     * For Linux or other non-Windows builds	
     */
    #define WSDLPULL_EXPORT /**/
  #endif
#endif 

#endif // WSDLPULL_EXPORT_H
#else
   #define WSDLPULL_EXPORT /**/
#endif
//temp hack
#define WSDLPULL_EXPORT /**/
