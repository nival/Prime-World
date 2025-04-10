project(Tests)

# Create the list of source files
aux_source_directory( . source_files )
file( GLOB header_files *.h )

list(APPEND source_files ${CMAKE_SOURCE_DIR}/reporting/CrashRpt/Utility.cpp)

# Enable usage of precompiled header
set(srcs_using_precomp ${source_files})
list(REMOVE_ITEM srcs_using_precomp ./stdafx.cpp )
add_msvc_precompiled_header(stdafx.h ./stdafx.cpp srcs_using_precomp )

# Define _UNICODE (use wide-char encoding)
add_definitions(-D_UNICODE )

if(NOT CRASHRPT_BUILD_SHARED_LIBS)
	add_definitions(-DCRASHRPT_LIB )
endif(NOT CRASHRPT_BUILD_SHARED_LIBS)

fix_default_compiler_settings_()

foreach (flag_var
	CMAKE_C_FLAGS_RELEASE CMAKE_CXX_FLAGS_RELEASE )
	string(REPLACE "/O2" "-Od" ${flag_var} "${${flag_var}}")
	string(REPLACE "/Ob2" "" ${flag_var} "${${flag_var}}")	
	set(${flag_var} "${${flag_var}} /Zi /fp:except /MP") 
endforeach()    

set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /DEBUG") 

# Add include dir
include_directories( ${CMAKE_SOURCE_DIR}/include 
                     ${CMAKE_SOURCE_DIR}/reporting/CrashRpt
					 ${CMAKE_SOURCE_DIR}/thirdparty/wtl )

# Add executable build target
add_executable(Tests ${source_files} ${header_files})

# Add input link libraries
target_link_libraries(Tests CrashRpt CrashRptProbe)

set_target_properties(Tests PROPERTIES DEBUG_POSTFIX d )
#set_target_properties(Tests PROPERTIES COMPILE_FLAGS "/Zi" LINK_FLAGS "/DEBUG")
