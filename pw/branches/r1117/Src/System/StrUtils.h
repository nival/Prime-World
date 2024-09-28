#ifndef STRUTILS_H__
#define STRUTILS_H__

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NStr
{

  void  Copy          (char *dest, const char *src, size_t  sizeOut);
  void  CopyN         (char *dest, const char *src, size_t  sizeOut, size_t numBytes);
  void  Cat           (char *dest, const char *src, size_t  sizeOut);
  int   Printf        (char *dest, size_t sizeOut,  const char *sFormat, ...);
  int   VPrintf       (char *sOut, size_t sizeOut,  const char *sFormat, va_list vlArgs);
  int   Cmp           (const char *sStr1, const char *sStr2, unsigned int numCharsToCompare = 0);
  int   NCmp          (const char *sStr1, const char *sStr2, unsigned int numCharsToCompare);
  int   ICmp          (const char *sStr1, const char *sStr2, unsigned int numCharsToCompare = 0);
  void  GenerateUUID  (char *dest, size_t sizeOut);
  void  SysLog        (const char *logString);
  
  void  ItoA          (int i, char *buf, size_t buf_len);
  
  char *FindFirst     (const char *sStr, const char *sSubStr);
  char *FindFirstI    (const char *sStr, const char *sSubStr);
  wchar_t *FindFirst  (const wchar_t *sStr, const wchar_t *sSubStr);
  wchar_t *FindFirstI (const wchar_t *sStr, const wchar_t *sSubStr);

  char *FindFirstChar (const char *sStr, char ch);
  char *FindLastChar  (const char *sStr, char ch);
  int   Len           (const char *src);
  void  ToUppercase   (char *sStr);
  void  ToLowercase   (char *sStr);
  void  ExtractFileName(const char *sFullFileName, char *sFileName, unsigned int sizeFileName);
  void  ExtractFileNameAndExt(const char *sFullFileName, char *sFileName, unsigned int sizeFileName);
  void  ExtractDrive(const char *sFullFileName, char *sDrive, unsigned int sizePath);
  bool  IsAbsPath(const char *sPath);
  void  ExtractPath(const char *sFullFileName, char *sPath, unsigned int sizePath);
  void  GetRelPath(const char *sAbsPath1, const char *sAbsPath2, char *sRelPath2, unsigned int sizeRelPath2);
  void  GetRelPathDiff(const char *sAbsPathResult, const char *sRelPath, char *sAbsPath, unsigned int sizeAbsPath);
  void  GetAbsPath(const char *sAbsPath1, const char *sRelPath2, char *sAbsPath2, unsigned int sizeAbsPath2);
  void  MakeAbsPathRelative2Exe(char const *sShortFileName, char *sFullFileName, unsigned int sizeFullFileName);
  void  MakeAbsPathRelative2CurrDir(char const *sRelPath, char *sAbsPath, unsigned int sizeAbsPath);
  void  GetRelPathFromCurrDir(char const *sAbsPath, char *sRelPath, unsigned int sizeRelPath);
  void  GetRelPathFromExe(char const *sAbsPath, char *sRelPath, unsigned int sizeRelPath);
  void  TryProduceUniqueName(char const *sCurrName, char *sNewName, unsigned int sizeNewName);
  
  int   WCopy           (const wchar_t *src, wchar_t *dest, int destMax);
  int   WCmp            (const wchar_t *str1, const wchar_t *str2);
  int   WNCmp           (const wchar_t *str1, const wchar_t *str2, int maxCount);
  int   ConvertToWString(const char *src, wchar_t *dest, int DestMax);
  int   SWPrintf        (wchar_t *dest, size_t destMaxlen, const wchar_t *format, ...);
  void  WVPrintf        (wchar_t *sOut, size_t sizeOut, const wchar_t *sFormat, va_list vlArgs);



};  // namespace
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif //STRUTILS_H__
