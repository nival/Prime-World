project(libogg)

# Create the list of source files
aux_source_directory( ./src source_files )

# Define _UNICODE (use wide-char encoding)
add_definitions(-D_UNICODE -D_CRT_SECURE_NO_DEPRECATE /wd4244)

# Add include dir
include_directories(        ${CMAKE_SOURCE_DIR}/thirdparty/libogg/include)

fix_default_compiler_settings_()

# Add library build target
add_library(libogg STATIC ${source_files})

set_target_properties(libogg PROPERTIES DEBUG_POSTFIX d )