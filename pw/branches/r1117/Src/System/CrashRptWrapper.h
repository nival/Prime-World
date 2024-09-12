#ifndef CRASHRPTWRAPPER_H_INCLUDED
#define CRASHRPTWRAPPER_H_INCLUDED

namespace CrashRptWrapper
{

void InstallForProcess( const char * uploadUrl, bool useBinaryEncoding, bool noGui, const char * productTitleOverride = 0, const char * privacyPolicyUrl = 0, bool enableLogging = false, bool sendQueuedReports = true );
void UninstallFromProcess();

#ifndef NI_DISABLE_CRASHRPT

//We cover per-thread functions only to reduce copy-paste
void InstallToCurrentThread();
void UninstallFromCurrentThread();

#else //NI_DISABLE_CRASHRPT

inline void InstallToCurrentThread() {}
inline void UninstallFromCurrentThread() {}

#endif //NI_DISABLE_CRASHRPT


void AddFileToReport( const char * filename, const char * description );

void AddTagToReport( const char * name, const char * value );

} //namespace CrashRptWrapper

#endif //CRASHRPTWRAPPER_H_INCLUDED
