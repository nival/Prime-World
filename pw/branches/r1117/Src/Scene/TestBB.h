#pragma once

#ifndef _SHIPPING
  #define DO_BB_TEST
#endif // _SHIPPING

#ifdef DO_BB_TEST
  static hash_set<string> namesTested;

  #define TEST_BB_UNIQUE(condition) \
    if( namesTested.find(GetDBID().GetFileName()) == namesTested.end() ) { \
      NI_ASSERT( condition, NStr::StrFmt("AABB should be valid %s", FormatDescription()) ); \
      namesTested.insert( GetDBID().GetFileName() ); }
#else
  #define TEST_BB_UNIQUE(condition)
#endif // DO_BB_TEST
