project(WTLDemo)

# Create the list of source files
aux_source_directory( . source_files )
file( GLOB header_files *.h )

# Enable usage of precompiled header
set(srcs_using_precomp ${source_files})
list(REMOVE_ITEM srcs_using_precomp ./stdafx.cpp)
add_msvc_precompiled_header(stdafx.h ./stdafx.cpp srcs_using_precomp)

# Include resource file
list(APPEND source_files ./WTLDemo.rc )

# Define _UNICODE (use wide-char encoding)
add_definitions(-D_UNICODE )

fix_default_compiler_settings_()

# Add include dir
include_directories(${CMAKE_SOURCE_DIR}/include
					${CMAKE_SOURCE_DIR}/thirdparty/wtl)

# Add executable build target
add_executable(WTLDemo WIN32 ${source_files} ${header_files})

# Add input link libraries
target_link_libraries(WTLDemo CrashRpt)

# Add "d" postfix to output file name in Debug
set_target_properties(WTLDemo PROPERTIES DEBUG_POSTFIX d )
set_target_properties(WTLDemo PROPERTIES COMPILE_FLAGS "/Od /Zi /fp:except" LINK_FLAGS "/DEBUG")

# Add post-build event
if(CMAKE_CL_64)
ADD_CUSTOM_COMMAND(
    TARGET WTLDemo
    POST_BUILD
    COMMAND copy ARGS "\"${CMAKE_SOURCE_DIR}/thirdparty/dbghelp/bin\\dbghelp.dll\" \"${CMAKE_BINARY_DIR}/bin\\x64\""
    COMMAND copy ARGS "\"${CMAKE_SOURCE_DIR}/demos/WTLDemo\\dummy.ini\" \"${CMAKE_BINARY_DIR}/bin\\x64\""
    COMMAND copy ARGS "\"${CMAKE_SOURCE_DIR}/demos/WTLDemo\\dummy.log\" \"${CMAKE_BINARY_DIR}/bin\\x64\""
    COMMAND copy ARGS "\"${CMAKE_SOURCE_DIR}/lang_files\\crashrpt_lang_EN.ini\" \"${CMAKE_BINARY_DIR}/bin\\x64\\crashrpt_lang.ini\""
)
else(CMAKE_CL_64)
ADD_CUSTOM_COMMAND(
    TARGET WTLDemo
    POST_BUILD
    COMMAND copy ARGS "\"${CMAKE_SOURCE_DIR}/thirdparty/dbghelp/bin\\dbghelp.dll\" \"${CMAKE_BINARY_DIR}/bin\""
    COMMAND copy ARGS "\"${CMAKE_SOURCE_DIR}/demos/WTLDemo\\dummy.ini\" \"${CMAKE_BINARY_DIR}/bin\""
    COMMAND copy ARGS "\"${CMAKE_SOURCE_DIR}/demos/WTLDemo\\dummy.log\" \"${CMAKE_BINARY_DIR}/bin\""
    COMMAND copy ARGS "\"${CMAKE_SOURCE_DIR}/lang_files\\crashrpt_lang_EN.ini\" \"${CMAKE_BINARY_DIR}/bin\\crashrpt_lang.ini\""
)
endif(CMAKE_CL_64)