project(libpng)

# Create the list of source files
aux_source_directory( . source_files )

# Define _UNICODE (use wide-char encoding)
add_definitions(-D_UNICODE -D_CRT_SECURE_NO_DEPRECATE /wd4244 /wd4267)

# Add include dir
include_directories( ${CMAKE_SOURCE_DIR}/thirdparty/zlib )

fix_default_compiler_settings_()

# Add library build target
add_library(libpng STATIC ${source_files})

# Add linker input libraries
target_link_libraries(libpng zlib)

set_target_properties(libpng PROPERTIES DEBUG_POSTFIX d )