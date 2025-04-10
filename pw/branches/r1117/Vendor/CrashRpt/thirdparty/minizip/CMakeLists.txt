project(minizip)

# Create the list of source files
aux_source_directory( . source_files )

# Define _UNICODE (use wide-char encoding)
add_definitions(-D_UNICODE -D_CRT_SECURE_NO_DEPRECATE /wd4127 /wd4131 /wd4100 /wd4189 /wd4244)

# Add include dir
include_directories( ${CMAKE_SOURCE_DIR}/thirdparty/zlib )

fix_default_compiler_settings_()

# Add library build target
add_library(minizip STATIC ${source_files})

# Add linker input libraries
target_link_libraries(minizip zlib)

set_target_properties(minizip PROPERTIES DEBUG_POSTFIX d )