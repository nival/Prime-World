//!Component('System/Streams')
//!Component('System/Minizip')
#include "cxxtest/TestSuite.h"
#include "stdafx.h"

#include <System/FileSystem/ZipFileSystem.h>


class Test_ZipFileSystem :  public CxxTest::TestSuite
{
public:
 void test_Simple()
 {
   /*ZipFileSystem fs("test_Simple.zip");
   {
     CObj<Stream> f = fs.OpenFile("test.txt", FILEACCESS_WRITE, FILEOPEN_CREATE_NEW);
     f->Write("0123456789", 10);
   }
   {
     CObj<Stream> f = fs.OpenFile("test.txt", FILEACCESS_READ, FILEOPEN_OPEN_EXISTING);
     byte buffer[64];
     int readBytes = f->Read(buffer, 10);
     TS_ASSERT_EQUALS(10, readBytes);
     TS_ASSERT_SAME_DATA("0123456789", buffer, 10);
   } */
 }

 void test_Compressing()
 {
   {
     const byte zip[] = { 80, 75, 3, 4, 20, 0, 0, 0, 8, 0, 165, 90, 54, 60, 241, 143, 133, 124, 21, 0, 0, 0, 232, 3, 0, 0, 8, 0, 0, 0, 116, 101, 115, 116, 46, 116, 120, 116, 51, 48, 52, 50, 54, 49, 53, 51, 183, 176, 52, 24, 101, 141, 178, 70, 89, 195, 148, 5, 0, 80, 75, 1, 2, 20, 0, 20, 0, 0, 0, 8, 0, 165, 90, 54, 60, 241, 143, 133, 124, 21, 0, 0, 0, 232, 3, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 1, 0, 32, 0, 0, 0, 0, 0, 0, 0, 116, 101, 115, 116, 46, 116, 120, 116, 80, 75, 5, 6, 0, 0, 0, 0, 1, 0, 1, 0, 54, 0, 0, 0, 59, 0, 0, 0, 0, 0};
     FileStream s("test.zip", FILEACCESS_WRITE, FILEOPEN_CREATE_NEW);
     s.Write(zip, sizeof(zip));
   }
   /*{
     ZipFileSystem fs("test_Compressing.zip");
     {
       CObj<Stream> f = fs.OpenFile("test.txt", FILEACCESS_WRITE, FILEOPEN_CREATE_NEW);
       for (int i=0;i<100;++i)
       {
         f->Write("0123456789", 10);
       }
     }
   }
   FileStream s("test_Compressing.zip", FILEACCESS_READ, FILEOPEN_OPEN_EXISTING);
   TS_ASSERT_EQUALS(true, s.IsOk());
   TS_ASSERT_LESS_THAN(s.GetSize(), 10*100);
   TS_ASSERT(s.GetSize() > 0);*/
   {
     ZipFileSystem fs("test.zip");
     CObj<Stream> f = fs.OpenFile("test.txt", FILEACCESS_READ, FILEOPEN_OPEN_EXISTING);
     byte buffer[64];
     for (int i=0;i<100;++i)
     {
       int readBytes = f->Read(buffer, 10);
       TS_ASSERT_SAME_DATA("0123456789", buffer, readBytes);
     }
   }
   {
     ZipFileSystem fs("test.zip");
     nstl::vector<nstl::string> files;
     fs.GetFiles( &files, "", "*.*", true, 0 );
     TS_ASSERT_EQUALS( 1, files.size() );
   }
 }

 void test_TwoFiles()
 {
   {
     const byte zip[] = { 0x50, 0x4b, 0x3, 0x4, 0x14, 0x0, 0x0, 0x0, 0x8, 0x0, 0xa5, 0x5a, 0x36, 0x3c, 0xf1, 0x8f, 0x85, 0x7c, 0x15, 0x0, 0x0, 0x0, 0xe8, 0x3, 0x0, 0x0, 0x9, 0x0, 0x0, 0x0, 0x74, 0x65, 0x73, 0x74, 0x32, 0x2e, 0x74, 0x78, 0x74, 0x33, 0x30, 0x34, 0x32, 0x36, 0x31, 0x35, 0x33, 0xb7, 0xb0, 0x34, 0x18, 0x65, 0x8d, 0xb2, 0x46, 0x59, 0xc3, 0x94, 0x5, 0x0, 0x50, 0x4b, 0x3, 0x4, 0x14, 0x0, 0x0, 0x0, 0x8, 0x0, 0xa5, 0x5a, 0x36, 0x3c, 0xf1, 0x8f, 0x85, 0x7c, 0x15, 0x0, 0x0, 0x0, 0xe8, 0x3, 0x0, 0x0, 0x8, 0x0, 0x0, 0x0, 0x74, 0x65, 0x73, 0x74, 0x2e, 0x74, 0x78, 0x74, 0x33, 0x30, 0x34, 0x32, 0x36, 0x31, 0x35, 0x33, 0xb7, 0xb0, 0x34, 0x18, 0x65, 0x8d, 0xb2, 0x46, 0x59, 0xc3, 0x94, 0x5, 0x0, 0x50, 0x4b, 0x1, 0x2, 0x14, 0x0, 0x14, 0x0, 0x0, 0x0, 0x8, 0x0, 0xa5, 0x5a, 0x36, 0x3c, 0xf1, 0x8f, 0x85, 0x7c, 0x15, 0x0, 0x0, 0x0, 0xe8, 0x3, 0x0, 0x0, 0x9, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1, 0x0, 0x20, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x74, 0x65, 0x73, 0x74, 0x32, 0x2e, 0x74, 0x78, 0x74, 0x50, 0x4b, 0x1, 0x2, 0x14, 0x0, 0x14, 0x0, 0x0, 0x0, 0x8, 0x0, 0xa5, 0x5a, 0x36, 0x3c, 0xf1, 0x8f, 0x85, 0x7c, 0x15, 0x0, 0x0, 0x0, 0xe8, 0x3, 0x0, 0x0, 0x8, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1, 0x0, 0x20, 0x0, 0x0, 0x0, 0x3c, 0x0, 0x0, 0x0, 0x74, 0x65, 0x73, 0x74, 0x2e, 0x74, 0x78, 0x74, 0x50, 0x4b, 0x5, 0x6, 0x0, 0x0, 0x0, 0x0, 0x2, 0x0, 0x2, 0x0, 0x6d, 0x0, 0x0, 0x0, 0x77, 0x0, 0x0, 0x0, 0x0, 0x0};
     FileStream s("test.zip", FILEACCESS_WRITE, FILEOPEN_CREATE_NEW);
     s.Write(zip, sizeof(zip));
   }
   /*{
   ZipFileSystem fs("test_Compressing.zip");
   {
   CObj<Stream> f = fs.OpenFile("test.txt", FILEACCESS_WRITE, FILEOPEN_CREATE_NEW);
   for (int i=0;i<100;++i)
   {
   f->Write("0123456789", 10);
   /}
   }
   }
   FileStream s("test_Compressing.zip", FILEACCESS_READ, FILEOPEN_OPEN_EXISTING);
   TS_ASSERT_EQUALS(true, s.IsOk());
   TS_ASSERT_LESS_THAN(s.GetSize(), 10*100);
   TS_ASSERT(s.GetSize() > 0);*/
   {
     ZipFileSystem fs("test.zip");
     nstl::vector<nstl::string> files;
     fs.GetFiles( &files, "", "*.*", true, 0 );
     TS_ASSERT_EQUALS( 2, files.size() );
   }
   {
     ZipFileSystem fs("test.zip");
     {
       CObj<Stream> f = fs.OpenFile("test.txt", FILEACCESS_READ, FILEOPEN_OPEN_EXISTING);
       byte buffer[64];
       for (int i=0;i<100;++i)
       {
         int readBytes = f->Read(buffer, 10);
         TS_ASSERT_SAME_DATA("0123456789", buffer, readBytes);
       }
     }
     {
       CObj<Stream> f = fs.OpenFile("test2.txt", FILEACCESS_READ, FILEOPEN_OPEN_EXISTING);
       byte buffer[64];
       for (int i=0;i<100;++i)
       {
         int readBytes = f->Read(buffer, 10);
         TS_ASSERT_SAME_DATA("0123456789", buffer, readBytes);
       }
     }
   }
 }

};