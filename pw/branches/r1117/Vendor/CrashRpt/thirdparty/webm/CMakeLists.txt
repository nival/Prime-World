project(vpx)

include_directories(./include ./src ./build)

# Create the list of source files
aux_source_directory(./build build_source_files)
aux_source_directory(./src/vpx/src vpx_source_files)
aux_source_directory(./src/vp8 vp8_source_files)
aux_source_directory(./src/vp8/common vp8_common_source_files)
aux_source_directory(./src/vp8/common/generic vp8_common_generic_source_files)
aux_source_directory(./src/vp8/encoder vp8_encoder_source_files)
aux_source_directory(./src/libmkv mkv_source_files)
aux_source_directory(./src/vpx_mem vpx_mem_source_files)
aux_source_directory(./src/vpx_scale/generic vpx_scale_source_files)

# Define _UNICODE (use wide-char encoding)
add_definitions(-D_UNICODE -D_CRT_SECURE_NO_DEPRECATE /wd4244 /wd4706 /wd4018)

fix_default_compiler_settings_()

# Add library build target
add_library(vpx STATIC ${build_source_files} 
					   ${vpx_source_files} 
                       ${mkv_source_files} 
					   ${vp8_source_files}
					   ${vp8_common_source_files}
					   ${vp8_common_generic_source_files}
					   ${vp8_encoder_source_files}
					   ${vpx_mem_source_files}
					   ${vpx_scale_source_files})

set_target_properties(vpx PROPERTIES DEBUG_POSTFIX d )