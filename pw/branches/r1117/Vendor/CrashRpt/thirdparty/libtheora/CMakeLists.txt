project(libtheora)

# Create the list of source files
aux_source_directory( ./lib source_files )
aux_source_directory( ./lib/x86_vc x86_source_files )

# Define _UNICODE (use wide-char encoding)
add_definitions(-D_UNICODE -D_CRT_SECURE_NO_DEPRECATE /wd4244 /wd4700 /wd4214 /wd4554 /wd4018 /wd4100 /wd4132 /wd4389 /wd4127 /wd4701 /wd4245 /wd4267 /wd4334)

# Add include dir
include_directories(        ${CMAKE_SOURCE_DIR}/thirdparty/libogg/include
							${CMAKE_SOURCE_DIR}/thirdparty/libtheora/include)

fix_default_compiler_settings_()

foreach (flag_var	CMAKE_C_FLAGS_DEBUG CMAKE_CXX_FLAGS_DEBUG )
	string(REPLACE "/RTC1" "-RTCs" ${flag_var} "${${flag_var}}")			  
endforeach()

# Add library build target
add_library(libtheora STATIC ${source_files} ${x86_source_files})

set_target_properties(libtheora PROPERTIES DEBUG_POSTFIX d )
