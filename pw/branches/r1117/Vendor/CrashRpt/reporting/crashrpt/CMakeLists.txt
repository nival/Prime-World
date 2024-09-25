project(CrashRpt)

# Create the list of source files
aux_source_directory( . source_files )
file( GLOB header_files *.h )

list(APPEND source_files ./CrashRpt.rc ./CrashRpt.def)

# Enable usage of precompiled header
set(srcs_using_precomp ${source_files})
list(REMOVE_ITEM srcs_using_precomp ./CrashRpt.rc ./StdAfx.cpp ./CrashRpt.def)
add_msvc_precompiled_header(stdafx.h ./StdAfx.cpp srcs_using_precomp)

# Define _UNICODE (use wide-char encoding)
add_definitions(-D_UNICODE -D_CRT_SECURE_NO_DEPRECATE)

# Modify default compiler settings
fix_default_compiler_settings_()

# Add include dir
include_directories( ${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/thirdparty/wtl)

# Add library build target
if(CRASHRPT_BUILD_SHARED_LIBS)
	add_library(CrashRpt SHARED ${source_files} ${header_files})
else(CRASHRPT_BUILD_SHARED_LIBS)
	add_library(CrashRpt STATIC ${source_files} ${header_files})
endif(CRASHRPT_BUILD_SHARED_LIBS)

# Specify what libraries to link
target_link_libraries(CrashRpt rpcrt4.dll version.lib)

foreach (flag_var
	CMAKE_C_FLAGS_RELEASE CMAKE_CXX_FLAGS_RELEASE )
	string(REPLACE "/O2" "-Od" ${flag_var} "${${flag_var}}")	
	string(REPLACE "/Ob2" "" ${flag_var} "${${flag_var}}")	
	set(${flag_var} "${${flag_var}} /Zi /fp:except /MP") 
endforeach()    

set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /DEBUG") 

# Add compiler flags (/MP for multi-processor compilation, /fp:except to handle floating-point exceptions; /Zi, /DEBUG to generate debugging symbols)
#set_target_properties(CrashRpt PROPERTIES  LINK_FLAGS "/DEBUG")
#if(${MSVC_VERSION} GREATER 1310)
#	set_target_properties(CrashRpt PROPERTIES COMPILE_FLAGS "/MP")
#endif(${MSVC_VERSION} GREATER 1310)

if(CRASHRPT_BUILD_SHARED_LIBS)
	
else(CRASHRPT_BUILD_SHARED_LIBS)
	set_target_properties(CrashRpt PROPERTIES 
									DEBUG_POSTFIX LIB 
									RELEASE_POSTFIX LIB )
endif(CRASHRPT_BUILD_SHARED_LIBS)

