/*************************************************************************
 *                         INTEL CONFIDENTIAL
 *
 * Copyright 2004-2009 Intel Corporation All Rights Reserved.
 *
 * The source code contained or described herein and all documents related
 * to the source code ("Material") are owned by Intel Corporation or its
 * suppliers or licensors.  Title to the Material remains with Intel
 * Corporation or its suppliers and licensors.  The Material contains
 * trade secrets and proprietary and confidential information of Intel
 * or its suppliers and licensors.  The Material is protected by worldwide
 * copyright and trade secret laws and treaty provisions.  No part of the
 * Material may be used, copied, reproduced, modified, published, uploaded,
 * posted, transmitted, distributed, or disclosed in any way without
 * Intel's prior express wrtten permission.
 *
 * No license under any patent, copyright, trade secret or other
 * intellectual property right is granted to or conferred upon you by
 * disclosure or delivery of the Materials, either expressly, by
 * implication, inducement, estoppel or otherwise.  Any license under such
 * intellectual property rights must be express and approved by Intel in
 * writing.
 ************************************************************************/

#if !defined(__TBRW_H__)
#define __TBRW_H__


#include "tbrw_types.h"

//TBRW error codes - these map to internal error code defined in vt_errors.h
#define 	TBRW_SUCCESS						0
#define 	TBRW_INVALID_STREAM					80
#define  	TBRW_BIND_MODULES_NOT_SORTED		142
#define 	TBRW_STREAM_NOT_BOUND				129
#define  	TBRW_TB5_IS_NOT_BOUND				113
#define  	TBRW_UNEXPECTED_NULL_PTR			36
#define  	TBRW_INVALID_ACCESS_PERMS			111
#define  	TBRW_FILE_OPEN_FAILED				44
#define  	TBRW_SECTION_ALREADY_IN_USE			77
#define  	TBRW_SECTION_NOT_EXIST				78
#define  	TBRW_UNKNOWN_SECTION_NUMBER			25
#define  	TBRW_STREAM_NOT_EXIST				79
#define  	TBRW_INVALID_STREAM					80
#define  	TBRW_STREAM_ALREADY_IN_USE			81
#define 	TBRW_INVALID_ERROR_CODE				83
#define  	TBRW_SECTION_NOT_READABLE			124
#define  	TBRW_BUFFER_TOO_SMALL				103
#define  	TBRW_INVALID_STRING					97
#define  	TBRW_NO_DATA_TO_WRITE				145
#define  	TBRW_SECTION_NOT_WRITEABLE			125
#define  	TBRW_INVALID_READ_START				86
#define  	TBRW_SAM_ERROR						22
#define  	TBRW_NOT_IMPLEMENTED				73
#define  	TBRW_INCOMPATIBLE_VERSION			84
#define  	TBRW_UNEXPECTED_VALUE				72
#define  	TBRW_UNSUPPORTED_DATA_SIZE			98
#define  	TBRW_UNEXPECTED_NUM_CPUIDS			143
#define  	TBRW_UNSUPPORTED_ARCH_TYPE			144
#define  	TBRW_FILE_OPEN_FAILED				44
#define  	TBRW_SAMPLE_FILE_MAPPING_ERROR		34
#define  	TBRW_GLOBAL_SECTION_NOT_CLOSED		126
#define  	TBRW_STREAM_SECTION_NOT_CLOSED		127
#define 	TBRW_STREAM_NOT_CLOSED            	128
#define  	TBRW_UNEXPECTED_NULL_PTR			36
#define  	TBRW_ENTRY_NOT_FOUND				39
#define  	TBRW_BUFFER_OVERFLOW				29
#define  	TBRW_NO_MEMORY						26
#define  	TBRW_NOT_ALL_SECTIONS_CLOSED		131
#define  	TBRW_BAD_PARAMETER					63
//End TBRW error codes


/******************************
ASSUMPTIONS
1) Does not handle legacy tb3 files
2) Does not handle legacy tb5 files not containing VTSA_SYS_INFO structure
3) Does not handle symbols
******************************/

#ifdef __cplusplus
extern "C" {
#endif   // __cplusplus


/* --------------------------------------------------------- */
/*!
 *
 *  General purpose routines
 *
 */


//
// Called once per process. For every open (or fork or dup),
// must call close. The driver_ptr is an opaque type used by the
// library. Allows for multiple opens in the future...
//
/* ------------------------------------------------------------------------- */
/*!
 * @fn          TBRW_U32 TBRW_open(OUT TBRW_PTR **tbrw_ptr, IN const char *filename, IN TBRW_U32 access_mode)
 * @brief       Opens a TBRW file and returns a handle to it.
 *
 * @param       filename IN - tbrw file name.
 * @param       tbrw_ptr  OUT - opaque ptr to tbrw library.
 * @param       access_mode IN - file access mode.
 *
 * @return      returns 0 if successful or returns an error code on failure.
 *
 * @special
 *
 * @todo
 *
 */
TBRW_API
TBRW_U32 TBRW_APICALL TBRW_open(OUT TBRW_PTR *tbrw_ptr, IN const TBRW_CHAR *filename, IN TBRW_U32 access_mode);

/* ------------------------------------------------------------------------- */
/*!
 * @fn          TBRW_U32 TBRW_close(IN TBRW_PTR tbrw_ptr)
 * @brief       Closes a TBRW file.
 *
 * @param       tbrw_ptr IN - opaquetbrw library ptr.
 *
 * @return      returns 0 if successful or returns an error code on failure.
 *
 * @special
 *
 * @todo
 *
 */
TBRW_API
TBRW_U32 TBRW_APICALL TBRW_close(INOUT TBRW_PTR tbrw_ptr);


/* ------------------------------------------------------------------------- */
/*!
 * @fn          TBRW_U32 TBRW_get_version(OUT TBRW_U32 *major, OUT TBRW_U32 *minor)
 * @brief       Returns TBRW api version number.
 *
 * @param       major  OUT - major version.
 * @param       minor OUT  - minor version
 *
 * @return      returns 0 if successful or returns an error code on failure.
 *
 * @todo
 *
 */
TBRW_API
TBRW_U32 TBRW_APICALL TBRW_get_version(OUT TBRW_U32 *major, OUT TBRW_U32 *minor);



/* ------------------------------------------------------------------------- */
/*!
 * @fn          TBRW_U32 TBRW_error_string(IN TBRW_U32 error_code,
                             OUT const char **error_string)
 * @brief       Translates an error code into human readable string.
 *
 * @param       error_code IN - the error code.
 * @param       error_string OUT - translated string
 *
 * @return      returns 0 if successful or returns an error code on failure.
 *
 * @special
 *
 * The caller cannot modify the string (it is a const).
 * If there is a need to modify the string, make a copy and modify the copy.
 *
 * @todo
 *
 */
TBRW_API
TBRW_U32 TBRW_APICALL TBRW_error_string(IN TBRW_U32 error_code,
                             OUT const TBRW_CHAR **error_string);

/* ------------------------------------------------------------------------- */
/*!
 * @fn          TBRW_U32 TBRW_verify(IN TBRW_PTR tbrw_ptr)
 * @brief       Verify that the currently opened file is a valid VTune file.
 *
 * @param       tbrw_ptr IN - opaque tbrw library pointer.
 *
 * @return      returns 0 if successful or returns an error code on failure.
 *
 * @special
 *
 * @todo
 *
 */
TBRW_API
TBRW_U32 TBRW_APICALL TBRW_verify (IN TBRW_PTR tbrw_ptr);



/* ------------------------------------------------------------------------- */
/*!
 * @fn          TBRW_U32 TBRW_reading_section(IN TBRW_PTR tbrw_ptr, IN TBRW_SECTION_IDENTIFIER section)
 * @brief       Tells the TBRW API you are going to be using a section for reading.
 *
 * @param       tbrw_ptr IN - tbrw file handle.
 * @param       section IN - section that you intend to read
 *
 * @return      returns 0 if successful or returns an error code on failure.
 *
 * @special
 *
 * @todo
 *
 */
TBRW_API
TBRW_U32 TBRW_APICALL TBRW_reading_section(IN TBRW_PTR tbrw_ptr, IN TBRW_SECTION_IDENTIFIER section);

/* ------------------------------------------------------------------------- */
/*!
 * @fn          TBRW_writing_section(IN TBRW_PTR tbrw_ptr, IN TBRW_SECTION_IDENTIFIER section)
 * @brief       Tells the TBRW API you are going to be using a section for reading.
 *
 * @param       tbrw_ptr IN - tbrw file handle.
 * @param       section IN - section that you intend to write
 *
 * @return      returns 0 if successful or returns an error code on failure.
 *
 * @special     If the section already exists, this call results in an error.
 *
 * @todo
 *
 */
TBRW_API
TBRW_U32 TBRW_APICALL TBRW_writing_section(IN TBRW_PTR tbrw_ptr, IN TBRW_SECTION_IDENTIFIER section);


/* ------------------------------------------------------------------------- */
/*!
 * @fn          TBRW_get_number_data_streams(IN TBRW_PTR tbrw_ptr, OUT TBRW_U32 *numStreams)
 * @brief       Returns the number of data streams in a tbrw file.
 *
 * @param       tbrw_ptr IN - tbrw file handle.
 * @param       numStreams OUT - Number of sections in the tbrw file.
 *
 * @return      returns 0 if successful or returns an error code on failure.
 *
 * @special     Initial implementation allows for only one data stream.
 *
 * @todo
 *
 */
TBRW_API
TBRW_U32 TBRW_APICALL TBRW_get_number_data_streams(IN TBRW_PTR tbrw_ptr, OUT TBRW_U32 *numStreams);



/* ------------------------------------------------------------------------- */
/*!
 * @fn          TBRW_done_section(IN TBRW_PTR tbrw_ptr, IN TBRW_SECTION_IDENTIFIER section)
 * @brief       Tells the API you are done using section
 *
 * @param       tbrw_ptr IN - tbrw file handle.
 * @param       section IN - section that you are done using.
 *
 * @return      returns 0 if successful or returns an error code on failure.
 *
 * @special
 *
 * @todo
 *
 */
TBRW_API
TBRW_U32 TBRW_APICALL TBRW_done_section(IN TBRW_PTR tbrw_ptr, IN TBRW_SECTION_IDENTIFIER section);

/* ------------------------------------------------------------------------- */
/*!
 * @fn          TBRW_reading_stream(IN TBRW_PTR tbrw_ptr, IN TBRW_U32 stream)
 * @brief       Tells the API you are going to be using the data stream for reading.
 *
 * @param       tbrw_ptr IN - tbrw file handle.
 * @param       stream IN - stream number being read, index begins at 0.
 *
 * @return      returns 0 if successful or returns an error code on failure.
 *
 * @special
 *
 * @todo
 *
 */
TBRW_API
TBRW_U32 TBRW_APICALL TBRW_reading_stream(IN TBRW_PTR tbrw_ptr, IN TBRW_U32 stream);

/* ------------------------------------------------------------------------- */
/*!
 * @fn          TBRW_writing_stream(IN TBRW_PTR tbrw_ptr, IN TBRW_U32 stream)
 * @brief       Tells the API you are going to be using the data stream for writing.
 *
 * @param       tbrw_ptr IN - tbrw file handle.
 * @param       stream IN - stream number being read, index begins at 0.
 *
 * @return      returns 0 if successful or returns an error code on failure.
 *
 * @special
 *
 * @todo
 *
 */
TBRW_API
TBRW_U32 TBRW_APICALL TBRW_writing_stream(IN TBRW_PTR tbrw_ptr, IN TBRW_U32 stream);

/* ------------------------------------------------------------------------- */
/*!
 * @fn          TBRW_done_stream(IN TBRW_PTR tbrw_ptr, IN TBRW_U32 stream)
 * @brief       Tells the API you are done using the data stream.
 *
 * @param       tbrw_ptr IN - tbrw file handle.
 * @param       stream IN - stream number, index begins at 0.
 *
 * @return      returns 0 if successful or returns an error code on failure.
 *
 * @special
 *
 * @todo
 *
 */
TBRW_API
TBRW_U32 TBRW_APICALL TBRW_done_stream(IN TBRW_PTR tbrw_ptr, IN TBRW_U32 stream);

/* ------------------------------------------------------------------------- */
/*!
 * @fn          TBRW_reading_stream_section(IN TBRW_PTR tbrw_ptr, IN TBRW_U32 stream, TBRW_STREAM_SECTION_IDENTIFIER section)
 * @brief       Tells the API you are going to be using a specified section stream for reading.
 *
 * @param       tbrw_ptr IN - tbrw file handle.
 * @param       stream IN - stream number, index begins at 0.
 * @param       section IN - section identifier.
 *
 * @return      returns 0 if successful or returns an error code on failure.
 *
 * @special
 *
 * @todo
 *
 */
TBRW_API
TBRW_U32 TBRW_APICALL TBRW_reading_stream_section(IN TBRW_PTR tbrw_ptr, IN TBRW_U32 stream, TBRW_STREAM_SECTION_IDENTIFIER section);

/* ------------------------------------------------------------------------- */
/*!
 * @fn          TBRW_writing_stream_section(IN TBRW_PTR tbrw_ptr, IN TBRW_U32 stream, TBRW_STREAM_SECTION_IDENTIFIER section)
 * @brief       Tells the API you are going to be using a specified section stream for writing.
 *
 * @param       tbrw_ptr IN - tbrw file handle.
 * @param       stream IN - stream number, index begins at 0.
 * @param       section IN - section identifier.
 *
 * @return      returns 0 if successful or returns an error code on failure.
 *
 * @special
 *
 * @todo
 *
 */
TBRW_API
TBRW_U32 TBRW_APICALL TBRW_writing_stream_section(IN TBRW_PTR tbrw_ptr,
                                       IN TBRW_U32 stream,
                                       TBRW_STREAM_SECTION_IDENTIFIER section);

/* ------------------------------------------------------------------------- */
/*!
 * @fn          TBRW_done_stream_section(IN TBRW_PTR tbrw_ptr, IN TBRW_U32 stream, TBRW_STREAM_SECTION_IDENTIFIER section)
 * @brief       Tells the API you are done using a section stream.
 *
 * @param       tbrw_ptr IN - tbrw file handle.
 * @param       stream IN - stream number, index begins at 0.
 * @param       section IN - section identifier.
 *
 * @return      returns 0 if successful or returns an error code on failure.
 *
 * @special
 *
 * @todo
 *
 */
TBRW_API
TBRW_U32 TBRW_APICALL TBRW_done_stream_section(IN TBRW_PTR tbrw_ptr,
                                    IN TBRW_U32 stream,
                                    TBRW_STREAM_SECTION_IDENTIFIER section);

/* ------------------------------------------------------------------------- */
/*!
 * @fn          TBRW_get_system(IN TBRW_PTR tbrw_ptr,IN TBRW_U32 size_of_buffer,IN void *buf_ptr,OPTIONAL OUT TBRW_U32 *size_buffer_used)
 * @brief       Read information about the entire system.
 *
 * @param       tbrw_ptr IN - tbrw file handle.
 * @param       size_of_buffer IN - size (in bytes) of buffer area pointed by buf_ptr.
 * @param       buf_ptr INOUT - buffer area in which system information is copied
 * @param       size_buffer_used OUT - The desired buffer size is returned thru this if size_of_buffer is not sufficient.
 *                                     This param is optional.
 *
 *
 * @return      returns 0 if successful or returns an error code on failure.
 *
 * @special
 *
 * @todo
 *
 */
TBRW_API
TBRW_U32 TBRW_APICALL TBRW_get_system(IN TBRW_PTR tbrw_ptr,
                           IN TBRW_U32 size_of_buffer,
                           INOUT TBRW_SYSTEM *buf_ptr,
                           OPTIONAL OUT TBRW_U32 *size_buffer_used);



/* ------------------------------------------------------------------------- */
/*!
 * @fn          TBRW_get_host(IN TBRW_PTR tbrw_ptr,IN TBRW_U32 size_of_buffer,IN void *buf_ptr,OPTIONAL OUT TBRW_U32 *size_buffer_used)
 * @brief       Read information about the entire system.
 *
 * @param       tbrw_ptr IN - tbrw file handle.
 * @param       size_of_buffer IN - size (in bytes) of buffer area pointed by buf_ptr.
 * @param       buf_ptr INOUT - buffer area in which host information is copied
 * @param       size_buffer_used OUT - The desired buffer size is returned thru this if size_of_buffer is not sufficient.
 *                                     This param is optional.
 *
 *
 * @return      returns 0 if successful or returns an error code on failure.
 *
 * @special
 *
 * @todo
 *
 */
TBRW_API
TBRW_U32 TBRW_APICALL TBRW_get_host(IN TBRW_PTR tbrw_ptr,
                         IN TBRW_U32 size_of_buffer,
                         INOUT TBRW_HOST *buf_ptr,
                         OPTIONAL OUT TBRW_U32 *size_buffer_used);



/* ------------------------------------------------------------------------- */
/*!
 * @fn          TBRW_U32 TBRW_convert_uniqueid_to_string(IN TBRW_PTR tbrw_ptr,
 *                                          IN TBRW_U32 size_of_buffer,
 *                                          IN TBRW_STRING_OR_ID *string_id,
 *                                          INOUT TBRW_CHAR *buffer,
 *                                          OPTIONAL OUT TBRW_U32 *size_buffer_needed);
 * @brief       Convert a unique id to a human-readable string.
 *
 * @param       tbrw_ptr IN - tbrw file handle.
 * @param       size_of_buffer IN -size of buffer allocated by caller to hold the string translation
 * @param       string_id IN - unique id.
 * @param       buffer INOUT - buffer allocated by the caller to hold string translation
 * @param       size_buffer_needed OPTIONAL OUT - size of buffer in number of bytes
 *
 * @return      returns 0 if successful or returns an error code on failure.
 *
 * @special
 *
 * @todo
 *
 */
TBRW_API
TBRW_U32 TBRW_APICALL TBRW_convert_uniqueid_to_string(IN TBRW_PTR tbrw_ptr,
                                           IN TBRW_U32 size_of_buffer,
                                           IN const TBRW_STRING_OR_ID *string_id,
                                           OUT TBRW_CHAR *buffer,
                                           OPTIONAL OUT TBRW_U32 *size_buffer_needed);



/* ------------------------------------------------------------------------- */
/*!
 * @fn          TBRW_get_os(IN TBRW_PTR tbrw_ptr,IN TBRW_U32 size_of_buffer,IN void *buf_ptr,OPTIONAL OUT TBRW_U32 *size_buffer_used)
 * @brief       Get information about the OS from the software section
 *
 * @param       tbrw_ptr IN - tbrw file handle.
 * @param       size_of_buffer IN - size (in bytes) of buffer area pointed by buf_ptr.
 * @param       buf_ptr INOUT - buffer area in which OS information is copied
 * @param       size_buffer_used OUT - The desired buffer size is returned thru this if size_of_buffer is not sufficient.
 *                                     This param is optional.
 *
 *
 * @return      returns 0 if successful or returns an error code on failure.
 *
 * @special
 *
 * @todo
 *
 */
TBRW_API
TBRW_U32 TBRW_APICALL TBRW_get_os(IN TBRW_PTR tbrw_ptr,
                       IN TBRW_U32 size_of_buffer,
                       INOUT TBRW_OS *buf_ptr,
                       OPTIONAL OUT TBRW_U32 *size_buffer_used);

/* ------------------------------------------------------------------------- */
/*!
 * @fn          TBRW_get_application(IN TBRW_PTR tbrw_ptr,IN TBRW_U32 size_of_buffer,IN void *buf_ptr,OPTIONAL OUT TBRW_U32 *size_buffer_used)
 * @brief       Get information about the application from the software section
 *
 * @param       tbrw_ptr IN - tbrw file handle.
 * @param       size_of_buffer IN - size (in bytes) of buffer area pointed by buf_ptr.
 * @param       buf_ptr INOUT - buffer area in which application information is copied
 * @param       size_buffer_used OUT - The desired buffer size is returned thru this if size_of_buffer is not sufficient.
 *                                     This param is optional.
 *
 *
 * @return      returns 0 if successful or returns an error code on failure.
 *
 * @special
 *
 * @todo
 *
 */
TBRW_API
TBRW_U32 TBRW_APICALL TBRW_get_application(IN TBRW_PTR tbrw_ptr,
                                IN TBRW_U32 size_of_buffer,
                                INOUT TBRW_APPLICATION *buf_ptr,
                                OPTIONAL OUT TBRW_U32 *size_buffer_used);

/* ------------------------------------------------------------------------- */
/*!
 * @fn          TBRW_enumerate_processes(IN TBRW_PTR tbrw_ptr, IN PID_CALLBACK *my_callback_func, IN void *user_ptr)
 * @brief       Get information about the processes from the process/thread section
 *
 * @param       tbrw_ptr IN - tbrw file handle.
 * @param       callback_func IN - The callback function that is called for every process in PID/TID section.
 * @param       user_ptr IN - The user supplied ptr that is passed to callback function.
 * @param       start_index IN - The index to start enumerating from (index starts at 0)
 *
 * @return      returns 0 if successful or returns an error code on failure.
 *
 * @special
 *
 * @todo
 *
 */
TBRW_API
TBRW_U32 TBRW_APICALL TBRW_enumerate_processes(IN TBRW_PTR tbrw_ptr,
                                    IN TBRW_PID_CALLBACK *callback_func,
                                    IN void *user_ptr,
                                    IN TBRW_U64 start_index);

/* ------------------------------------------------------------------------- */
/*!
 * @fn          TBRW_enumerate_threads(IN TBRW_PTR tbrw_ptr, TID_CALLBACK *callback_func, void *user_ptr)
 * @brief       Get information about the threads from the process/thread section.
 *
 * @param       tbrw_ptr IN - tbrw file handle.
 * @param       callback_func IN - The callback function that is called for every thread in PID/TID section.
 * @param       user_ptr IN - The user supplied ptr that is passed to callback function.
 * @param       start_index IN - The index to start enumerating from (index starts at 0)
 *
 * @return      returns 0 if successful or returns an error code on failure.
 *
 * @special
 *
 * @todo
 *
 */
TBRW_API
TBRW_U32 TBRW_APICALL TBRW_enumerate_threads(IN TBRW_PTR tbrw_ptr,
                                  IN TBRW_TID_CALLBACK *callback_func,
                                  IN void *user_ptr,
                                  IN TBRW_U64 start_index);

/* ------------------------------------------------------------------------- */
/*!
 * @fn          TBRW_enumerate_modules(IN TBRW_PTR tbrw_ptr, TBRW_MODULE_CALLBACK *callback_func, void *user_ptr)
 * @brief       Get information about the modules from the module section.
 *
 * @param       tbrw_ptr IN - tbrw file handle.
 * @param       callback_func IN - The callback function that is called for every module in module section.
 * @param       user_ptr IN - The user supplied ptr that is passed to callback function.
 * @param       start_index IN - The index to start enumerating from (index starts at 0)
 *
 * @return      returns 0 if successful or returns an error code on failure.
 *
 * @special
 *
 * @todo
 *
 */
TBRW_API
TBRW_U32 TBRW_APICALL TBRW_enumerate_modules(IN TBRW_PTR tbrw_ptr,
                                  IN TBRW_MODULE_CALLBACK *callback_func,
                                  IN void *user_ptr,
                                  IN TBRW_U64 start_index);

/* ------------------------------------------------------------------------- */
/*!
 * @fn          TBRW_get_user_defined_global(IN TBRW_PTR tbrw_ptr,IN TBRW_U32 size_of_buffer,IN void *buf_ptr,OPTIONAL OUT TBRW_U32 *size_buffer_used)
 * @brief       Read user-defined global data.
 *
 * @param       tbrw_ptr IN - tbrw file handle.
 * @param       size_of_buffer IN - size (in bytes) of buffer area pointed by buf_ptr.
 * @param       buf_ptr IN - buffer area in which global data is copied
 * @param       size_buffer_used OUT - The desired buffer size is returned thru this if size_of_buffer is not sufficient.
 *                                     This param is optional.
 *
 *
 * @return      returns 0 if successful or returns an error code on failure.
 *
 * @special
 *
 * @todo
 *
 */
TBRW_API
TBRW_U32 TBRW_APICALL TBRW_get_user_defined_global(IN TBRW_PTR tbrw_ptr,
                                        IN TBRW_U32 size_of_buffer,
                                        IN void *buf_ptr,
                                        OPTIONAL OUT TBRW_U32 *size_buffer_used);

/* ------------------------------------------------------------------------- */
/*!
 * @fn          TBRW_set_user_defined_global(IN TBRW_PTR tbrw_ptr, IN TBRW_U32 size_of_data, IN void *data_ptr)
 * @brief       Write user-defined global data.
 *
 * @param       tbrw_ptr IN - tbrw file handle.
 * @param       size_of_data IN - size of global data.
 * @param       data_ptr IN - pointer to global data.
 *
 * @return      returns 0 if successful or returns an error code on failure.
 *
 * @special
 *
 * @todo
 *
 */
TBRW_API
TBRW_U32 TBRW_APICALL TBRW_set_user_defined_global(IN TBRW_PTR tbrw_ptr,
                                        IN TBRW_U32 size_of_data,
                                        IN void *data_ptr);

/* ------------------------------------------------------------------------- */
/*!
 * @fn          TBRW_set_application(IN TBRW_PTR tbrw_ptr, IN TBRW_APPLICATION *os)
 * @brief       Set information about the application in the software section.
 *
 * @param       tbrw_ptr IN - tbrw file handle.
 * @param       os IN - pointer to application information.
 *
 * @return      returns 0 if successful or returns an error code on failure.
 *
 * @special
 *
 * @todo
 *
 */
TBRW_API
TBRW_U32 TBRW_APICALL TBRW_set_application(IN TBRW_PTR tbrw_ptr, IN TBRW_APPLICATION *application);



/* ------------------------------------------------------------------------- */
/*!
 * @fn          TBRW_set_system(IN TBRW_PTR tbrw_ptr, IN TBRW_SYSTEM *system)
 * @brief       Write information about the entire system.
 *
 * @param       tbrw_ptr IN - tbrw file handle.
 * @param       system IN - pointer to systeminformation.
 *
 * @return      returns 0 if successful or returns an error code on failure.
 *
 * @special
 *
 * @todo
 *
 */
TBRW_API
TBRW_U32 TBRW_APICALL TBRW_set_system(IN TBRW_PTR tbrw_ptr, IN TBRW_SYSTEM *system);



/* ------------------------------------------------------------------------- */
/*!
 * @fn          TBRW_set_host(IN TBRW_PTR tbrw_ptr, IN TBRW_HOST *host)
 * @brief       Set information about the host in the software section
 *
 * @param       tbrw_ptr IN - tbrw file handle.
 * @param       host IN - pointer to host information.
 *
 * @return      returns 0 if successful or returns an error code on failure.
 *
 * @special
 *
 * @todo
 *
 */
TBRW_API
TBRW_U32 TBRW_APICALL TBRW_set_host(IN TBRW_PTR tbrw_ptr,IN TBRW_HOST *host);

/* ------------------------------------------------------------------------- */
/*!
 * @fn          TBRW_set_os(IN TBRW_PTR tbrw_ptr, IN TBRW_OS *os)
 * @brief       Set information about the OS in the software section
 *
 * @param       tbrw_ptr IN - tbrw file handle.
 * @param       os IN - pointer to os information.
 *
 * @return      returns 0 if successful or returns an error code on failure.
 *
 * @special
 *
 * @todo
 *
 */
TBRW_API
TBRW_U32 TBRW_APICALL TBRW_set_os(IN TBRW_PTR tbrw_ptr, IN TBRW_OS *os);

/* ------------------------------------------------------------------------- */
/*!
 * @fn          TBRW_add_process(IN TBRW_PTR tbrw_ptr, IN TBRW_PID *process)
 * @brief       Add information about a process to the process/thread section
 *
 * @param       tbrw_ptr IN - tbrw file handle.
 * @param       process IN - pointer to PID information.
 *
 * @return      returns 0 if successful or returns an error code on failure.
 *
 * @special
 *
 * @todo
 *
 */
TBRW_API
TBRW_U32 TBRW_APICALL TBRW_add_process(IN TBRW_PTR tbrw_ptr, IN TBRW_PID *process);

/* ------------------------------------------------------------------------- */
/*!
 * @fn          TBRW_add_thread(IN TBRW_PTR tbrw_ptr, IN TBRW_TID *thread)
 * @brief       Add information about a thread to the process/thread section.
 *
 * @param       tbrw_ptr IN - tbrw file handle.
 * @param       thread IN - pointer to TID information.
 *
 * @return      returns 0 if successful or returns an error code on failure.
 *
 * @special
 *
 * @todo
 *
 */
TBRW_API
TBRW_U32 TBRW_APICALL TBRW_add_thread(IN TBRW_PTR tbrw_ptr, IN TBRW_TID *thread);

/* ------------------------------------------------------------------------- */
/*!
 * @fn          TBRW_add_module(IN TBRW_PTR tbrw_ptr, IN TBRW_MODULE *module)
 * @brief       Add information about a module to the module section.
 *
 * @param       tbrw_ptr IN - tbrw file handle.
 * @param       thread IN - pointer to module information.
 *
 * @return      returns 0 if successful or returns an error code on failure.
 *
 * @special
 *
 * @todo
 *
 */
TBRW_API
TBRW_U32 TBRW_APICALL TBRW_add_module(IN TBRW_PTR tbrw_ptr, IN TBRW_MODULE *module);


/* ------------------------------------------------------------------------- */
/*!
 * @fn          TBRW_set_user_defined_stream(IN TBRW_PTR tbrw_ptr, IN TBRW_U32 stream, TBRW_DATA_CALLBACK *my_callback_func, void *user_ptr)
 * @brief       Write user-defined data to be stored with a stream.
 *
 * @param       tbrw_ptr IN - tbrw file handle.
 * @param       stream IN - stream number, index begins at 0.
 * @param       size_of_data IN - number of bytes in the user defined stream
 * @param       data_ptr IN - pointer to the user defined stream
 *
 *
 * @return      returns 0 if successful or returns an error code on failure.
 *
 * @special
 *
 * @todo
 *
 */
TBRW_API
TBRW_U32 TBRW_APICALL TBRW_set_user_defined_stream(IN TBRW_PTR tbrw_ptr,
                                        IN TBRW_U32 stream,
                                        IN TBRW_U32 size_of_data,
                                        IN void *data_ptr);

/* ------------------------------------------------------------------------- */
/*!
 * @fn          TBRW_get_user_defined_stream(IN TBRW_PTR ptr,IN TBRW_U32 stream,IN TBRW_U32 size_of_buffer,IN BUFFER *buf_ptr, OPTIONAL OUT TBRW_U32 *size_buffer_used)
 * @brief       Read user-defined data stored with a stream.
 *
 * @param       tbrw_ptr IN - tbrw file handle.
 * @param       stream IN - stream number.
 * @param       size_of_buffer IN - number of bytes of the user defined stream
 * @param       buf_ptr IN - pointer to space allocated by the user
 * @param       size_buffer_used IN - set to number of bytes to allocate
 *
 *
 * @return      returns 0 if successful or returns an error code on failure.
 *
 * @special     if size_of_buffer == 0 and buf_ptr == NULL, then size_buffer_used is set to
 *              the number of bytes needed to be allocated by the caller
 *
 * @todo
 *
 */
TBRW_API
TBRW_U32 TBRW_APICALL TBRW_get_user_defined_stream(IN TBRW_PTR tbrw_ptr,
                                        IN TBRW_U32 stream,
                                        IN TBRW_U32 size_of_buffer,
                                        IN void *buf_ptr,
                                        OPTIONAL OUT TBRW_U32 *size_buffer_used);



/* ------------------------------------------------------------------------- */
/*!
 * @fn          TBRW_enumerate_events(IN TBRW_PTR tbrw_ptr, IN TBRW_U32 stream, TBRW_DATA_CALLBACK *my_callback_func, void *user_ptr)
 * @brief       Enumerates the event descriptor entries in the event descriptor.
 *
 * @param       tbrw_ptr IN - tbrw file handle.
 * @param       stream IN - stream number, stream index starts at 0.
 * @param       callback_func IN - The callback function that is called for every event in events section.
 * @param       user_ptr IN - The user supplied ptr that is passed to callback function.
 * @param       start_index IN - The index to start enumerating from (index starts at 0)
 *
 *
 * @return      returns 0 if successful or returns an error code on failure.
 *
 * @special
 *
 * @todo
 *
 */
TBRW_API
TBRW_U32 TBRW_APICALL TBRW_enumerate_events(IN TBRW_PTR tbrw_ptr,
                                 IN TBRW_U32 stream,
                                 IN TBRW_EVENT_CALLBACK *callback_func,
                                 IN void *user_ptr,
                                 IN TBRW_U64 start_index);


/* ------------------------------------------------------------------------- */
/*!
 * @fn          TBRW_add_event(IN TBRW_PTR tbrw_ptr,IN TBRW_U32 stream,IN TBRW_EVENT *event_descriptor_entry)
 * @brief       Append a new event descriptor entry to the event descriptor section.
 *
 * @param       tbrw_ptr IN - tbrw file handle.
 * @param       stream IN - stream number, stream index starts at 0.
 * @param       event_descriptor_entry IN - the event descriptor
 *
 *
 * @return      returns 0 if successful or returns an error code on failure.
 *
 * @special
 *
 * @todo
 *
 */
TBRW_API
TBRW_U32 TBRW_APICALL TBRW_add_event(IN TBRW_PTR tbrw_ptr,
                          IN TBRW_U32 stream,
                          IN TBRW_EVENT *event_descriptor_entry);


/* ------------------------------------------------------------------------- */
/*!
 * @fn          TBRW_add_events_from_file(IN TBRW_PTR tbrw_ptr, IN TBRW_U32 stream,  TBRW_CHAR *file)
 * @brief       Appends event info in a binary file to the events section. The event entries should be in the format described by the event section.
 *
 * @param       tbrw_ptr IN - tbrw file handle.
 * @param       stream IN - stream number, stream index starts at 0.
 * @param       file IN - name of file to be appended.
 * @param       numEvents IN - number of events being added.
 *
 *
 * @return      returns 0 if successful or returns an error code on failure.
 *
 * @special
 *
 * @todo
 *
 */
TBRW_API
TBRW_U32 TBRW_APICALL TBRW_add_events_from_file(IN TBRW_PTR tbrw_ptr, IN TBRW_U32 stream, TBRW_CHAR *filename, IN TBRW_U32 numEvents);


/* ------------------------------------------------------------------------- */
/*!
 * @fn          TBRW_add_data_descriptor_entry(IN TBRW_PTR tbrw_ptr, IN TBRW_U32 stream, IN TBRW_SAMPREC_DESC_ENTRY *data_descriptor_entry)
 * @brief       Appends a new data descriptor entry to the data descriptor.
 *
 * @param       tbrw_ptr IN - tbrw file handle.
 * @param       stream IN - stream number, stream index starts at 0.
 * @param       data_descriptor_entry IN -
 *
 *
 * @return      returns 0 if successful or returns an error code on failure.
 *
 * @special
 *
 * @todo
 *
 */
TBRW_API
TBRW_U32 TBRW_APICALL TBRW_add_data_descriptor_entry(IN TBRW_PTR tbrw_ptr,
                                          IN TBRW_U32 stream,
                                          IN TBRW_SAMPREC_DESC_ENTRY *data_descriptor_entry);

/* ------------------------------------------------------------------------- */
/*!
 * @fn          TBRW_enumerate_data_descriptor_entries(IN TBRW_PTR tbrw_ptr, IN TBRW_U32 stream, TBRW_DATA_CALLBACK *my_callback_func, void *user_ptr)
 * @brief       Enumerates the data descriptor entries in the data descriptor.
 *
 * @param       tbrw_ptr IN - tbrw file handle.
 * @param       stream IN - stream number, stream index starts at 0.
 * @param       callback_func IN - The callback function that is called for every event in events section.
 * @param       user_ptr IN - The user supplied ptr that is passed to callback function.
 *
 *
 * @return      returns 0 if successful or returns an error code on failure.
 *
 * @special     Note that the desc_name string field in SAMPREC_DESC_ENTY is of type UTF 8 (ascii) and not TBRW_CHAR
 *
 * @todo
 *
 */
TBRW_API
TBRW_U32 TBRW_APICALL TBRW_enumerate_data_descriptor_entries(IN TBRW_PTR tbrw_ptr,
                                                  IN TBRW_U32 stream,
                                                  IN TBRW_DATA_DESC_CALLBACK *callback_func,
                                                  IN void *user_ptr);

/* ------------------------------------------------------------------------- */
/*!
 * @fn          TBRW_add_data(IN TBRW_PTR tbrw_ptr, IN TBRW_U32 stream, IN TBRW_U32 size_of_data_entry, IN void *data_entry)
 * @brief       Appends a data entry to the data section. The data entry should be in the format described by the data description section.
 *
 * @param       tbrw_ptr IN - tbrw file handle.
 * @param       stream IN - stream number, stream index starts at 0.
 * @param       size_of_data_entry IN - data entry size
 * @param       data_entry IN -
 *
 *
 * @return      returns 0 if successful or returns an error code on failure.
 *
 * @special     Note that the desc_name string field in SAMPREC_DESC_ENTY is of type UTF 8 (ascii) and not TBRW_CHAR
 *
 * @todo
 *
 */
TBRW_API
TBRW_U32 TBRW_APICALL TBRW_add_data(IN TBRW_PTR tbrw_ptr,
                         IN TBRW_U32 stream,
                         IN TBRW_U32 size_of_data_entry,
                         IN void *data_entry);

/* ------------------------------------------------------------------------- */
/*!
 * @fn          TBRW_add_data_from_file(IN TBRW_PTR tbrw_ptr, IN TBRW_U32 stream,  TBRW_CHAR *file)
 * @brief       Appends data entries in a binary file to the data section. The data entries should be in the format described by the data description section.
 *
 * @param       tbrw_ptr IN - tbrw file handle.
 * @param       stream IN - stream number, stream index starts at 0.
 * @param       file IN - name of file to be appended.
 *
 *
 * @return      returns 0 if successful or returns an error code on failure.
 *
 * @special
 *
 * @todo
 *
 */
TBRW_API
TBRW_U32 TBRW_APICALL TBRW_add_data_from_file(IN TBRW_PTR tbrw_ptr, IN TBRW_U32 stream, TBRW_CHAR *filename);


/* ------------------------------------------------------------------------- */
/*!
 * @fn          TBRW_enumerate_data(IN TBRW_PTR tbrw_ptr, IN TBRW_U32 stream, TBRW_DATA_CALLBACK *my_callback_func, void *user_ptr)
 * @brief       Gets data entries from the data section. The data returned will be in the format described by the data description section.
 *
 * @param       tbrw_ptr IN - tbrw file handle.
 * @param       stream IN - stream number, stream index starts at 0.
 * @param       callback_func IN - The callback function that is called for every data entry.
 * @param       user_ptr IN - The user supplied ptr that is passed to callback function.
 * @param       start_index IN - The index to start enumerating from (index starts at 0)
 *
 *
 * @return      returns 0 if successful or returns an error code on failure.
 *
 * @special
 *
 * @todo
 *
 */
TBRW_API
TBRW_U32 TBRW_APICALL TBRW_enumerate_data(IN TBRW_PTR tbrw_ptr,
                               IN TBRW_U32 stream,
                               IN TBRW_DATA_CALLBACK *callback_func,
                               IN void *user_ptr,
                               IN TBRW_U64 start_index);


/* ------------------------------------------------------------------------- */
/*!
 * @fn          TBRW_set_version_info(IN TBRW_PTR tbrw_ptr,
 *                               IN TBRW_VERSION_INFO *version_info)
 * @brief       Set the TBRW_VERSION_INFO structure
 *
 * @param       tbrw_ptr IN - tbrw file handle.
 * @param       version_info IN - The structure to set.
 *
 * @return      returns 0 if successful or returns an error code on failure.
 *
 * @special
 *
 * @todo
 *
 */
TBRW_API
TBRW_U32 TBRW_APICALL TBRW_set_version_info(IN TBRW_PTR tbrw_ptr,
                                 IN TBRW_VERSION_INFO *version_info);

/* ------------------------------------------------------------------------- */
/*!
 * @fn          TBRW_get_version_info(IN TBRW_PTR tbrw_ptr,
 *                               IN TBRW_U32 size_of_buffer,
 *                               IN void *buf_ptr,
 *                               OPTIONAL OUT TBRW_U32 *size_buffer_used)
 * @brief       Get the version info (found in the TBRW_VERSION_INFO structure)
 *
 * @param       tbrw_ptr IN - tbrw file handle.
 * @param       size_of_buffer IN - size of the buffer to allocate.
 * @param       buf_ptr INOUT - pointer to the buffer.
 * @param       size_buffer_used OPTIONAL OUT - how many bytes to allocate/use
 *
 * @return      returns 0 if successful or returns an error code on failure.
 *
 * @special     if buf_ptr == NULL and size_of_buffer == 0, then
 *              size_buffer_used returned will be the size of the buffer that
 *              needs to be allocated by the caller.
 *
 * @todo
 *
 */
TBRW_API
TBRW_U32 TBRW_APICALL TBRW_get_version_info(IN TBRW_PTR tbrw_ptr,
                                 IN TBRW_U32 size_of_buffer,
                                 INOUT TBRW_VERSION_INFO *buf_ptr,
                                 OPTIONAL OUT TBRW_U32 *size_buffer_used);

/* ------------------------------------------------------------------------- */
/*!
 * @fn          TBRW_set_stream_info(IN TBRW_PTR tbrw_ptr,
                                IN TBRW_U32 stream,
                                IN TBRW_STREAM_INFO *version_info)
 * @brief       Set the TBRW_STREAM_INFO structure
 *
 * @param       tbrw_ptr IN - tbrw file handle.
 * @param       stream IN - the stream index of interest, index begins at 0
 * @param       stream_info IN - The structure to set.
 *
 * @return      returns 0 if successful or returns an error code on failure.
 *
 * @special
 *
 * @todo
 *
 */
TBRW_API
TBRW_U32 TBRW_APICALL TBRW_set_stream_info(IN TBRW_PTR tbrw_ptr,
                                IN TBRW_U32 stream,
                                IN TBRW_STREAM_INFO *stream_info);

/* ------------------------------------------------------------------------- */
/*!
 * @fn          BRW_get_stream_info(IN TBRW_PTR tbrw_ptr,
                                IN TBRW_U32 stream,
                                IN TBRW_U32 size_of_buffer,
                                IN void *buf_ptr,
                                OPTIONAL OUT TBRW_U32 *size_buffer_used)
 * @brief       Get the stream info (found in the TBRW_STREAM_INFO structure)
 *
 * @param       tbrw_ptr IN - tbrw file handle.
 * @param       stream IN - the stream index of interest, index begins at 0
 * @param       size_of_buffer IN - size of the buffer to allocate.
 * @param       buf_ptr INOUT - pointer to the buffer.
 * @param       size_buffer_used OPTIONAL OUT - how many bytes to allocate/use
 *
 * @return      returns 0 if successful or returns an error code on failure.
 *
 * @special     if buf_ptr == NULL and size_of_buffer == 0, then
 *              size_buffer_used returned will be the size of the buffer that
 *              needs to be allocated by the caller.
 *
 * @todo
 *
 */
TBRW_API
TBRW_U32 TBRW_APICALL TBRW_get_stream_info(IN TBRW_PTR tbrw_ptr,
                                IN TBRW_U32 stream,
                                IN TBRW_U32 size_of_buffer,
                                INOUT TBRW_STREAM_INFO *buf_ptr,
                                OPTIONAL OUT TBRW_U32 *size_buffer_used);


/* ------------------------------------------------------------------------- */
/*!
 * @fn          TBRW_abort_cleanup_and_close(IN TBRW_PTR tbrw_ptr)
 * @brief       aborts reading/writing of the final file and cleanups any temp files
 *
 * @param       tbrw_ptr IN - tbrw file handle.
 *
 * @return      returns 0 if successful or returns an error code on failure.
 *
 * @special
 *
 * @todo
 *
 */
TBRW_API
TBRW_U32 TBRW_APICALL TBRW_abort_cleanup_and_close(IN TBRW_PTR tbrw_ptr);


/* ------------------------------------------------------------------------- */
/*!
 * @fn          TBRW_is_bound(IN TBRW_PTR ptr, IN TBRW_U32 data_stream, OUT TBRW_U32 *is_bound)
 * @brief       indicates if the data stream is bound or not
 *
 * @param       tbrw_ptr IN - tbrw file handle.
 * @param       data_stream IN - the data stream of interest
 * @param       is_bound OUT - TRUE if bound, FALSE if not bound
 *
 * @return      returns 0 if successful or returns an error code on failure.
 *
 * @special
 *
 * @todo
 *
 */
TBRW_API
TBRW_U32 TBRW_APICALL TBRW_is_bound(IN TBRW_PTR ptr, IN TBRW_U32 data_stream, OUT TBRW_U32 *is_bound);

/* ------------------------------------------------------------------------- */
/*!
 * @fn          TBRW_dobind(IN TBRW_PTR ptr, IN TBRW_U32 data_stream)
 * @brief       binds the data stream
 *
 * @param       tbrw_ptr IN - tbrw file handle.
 * @param       data_stream IN - the data stream of interest
 *
 * @return      returns 0 if successful or returns an error code on failure.
 *
 * @special
 *
 * @todo
 *
 */
TBRW_API
TBRW_U32 TBRW_APICALL TBRW_dobind(IN TBRW_PTR ptr, IN TBRW_U32 data_stream);

/* ------------------------------------------------------------------------- */
/*!
 * @fn          TBRW_unbind(IN TBRW_PTR ptr, IN TBRW_U32 data_stream)
 * @brief       unbinds the data stream
 *
 * @param       tbrw_ptr IN - tbrw file handle.
 * @param       data_stream IN - the data stream of interest
 *
 * @return      returns 0 if successful or returns an error code on failure.
 *
 * @special
 *
 * @todo        this function is currently not implemented
 *
 */
TBRW_API
TBRW_U32 TBRW_APICALL TBRW_unbind(IN TBRW_PTR ptr, IN TBRW_U32 data_stream);

/* ------------------------------------------------------------------------- */
/*!
 * @fn          TBRW_get_size_of_data_bind_entry(IN TBRW_PTR ptr, IN TBRW_U32 data_stream, OUT TBRW_U32 *sizeof_data_bind_entry)
 * @brief       returns the size of each entry in the data bind structure
 *
 * @param       tbrw_ptr IN - tbrw file handle.
 * @param       data_stream IN - the data stream of interest
 * @param       sizeof_data_bind_entry OUT - size in bytes of an entry in the data bind structure. You need to know the
 *                                           size of each entry in order to iterate through the data bind buffer
 *
 * @return      returns 0 if successful or returns an error code on failure.
 *
 * @special
 *
 * @todo
 *
 */
TBRW_API
TBRW_U32 TBRW_APICALL TBRW_get_size_of_data_bind_entry(IN TBRW_PTR ptr, IN TBRW_U32 data_stream, OUT TBRW_U32 *sizeof_data_bind_entry);

/* ------------------------------------------------------------------------- */
/*!
 * @fn          TBRW_get_size_of_module_bind_entry(IN TBRW_PTR ptr, IN TBRW_U32 data_stream, OUT TBRW_U32 *sizeof_module_bind_entry)
 * @brief       returns the size of each entry in the module bind structure
 *
 * @param       tbrw_ptr IN - tbrw file handle.
 * @param       data_stream IN - the data stream of interest
 * @param       sizeof_module_bind_entry OUT - size in bytes of an entry in the module bind structure. You need to know the
 *                                           size of each entry in order to iterate through the module bind buffer
 *
 * @return      returns 0 if successful or returns an error code on failure.
 *
 * @special
 *
 * @todo
 *
 */
TBRW_API
TBRW_U32 TBRW_APICALL TBRW_get_size_of_module_bind_entry(IN TBRW_PTR ptr, IN TBRW_U32 data_stream, OUT TBRW_U32 *sizeof_module_bind_entry);

/* ------------------------------------------------------------------------- */
/*!
 * @fn          TBRW_get_size_of_tid_bind_entry(IN TBRW_PTR ptr, IN TBRW_U32 data_stream, OUT TBRW_U32 *sizeof_tid_bind_entry)
 * @brief       returns the size of each entry in the thread bind structure
 *
 * @param       tbrw_ptr IN - tbrw file handle.
 * @param       data_stream IN - the data stream of interest
 * @param       sizeof_tid_bind_entry OUT - size in bytes of an entry in the thread bind structure. You need to know the
 *                                           size of each entry in order to iterate through the thread bind buffer
 *
 * @return      returns 0 if successful or returns an error code on failure.
 *
 * @special
 *
 * @todo
 *
 */
TBRW_API
TBRW_U32 TBRW_APICALL TBRW_get_size_of_tid_bind_entry(IN TBRW_PTR ptr, IN TBRW_U32 data_stream, OUT TBRW_U32 *sizeof_tid_bind_entry);

/* ------------------------------------------------------------------------- */
/*!
 * @fn          TBRW_bind_enumerate_data(IN TBRW_PTR ptr, IN TBRW_U32 data_stream, IN BIND_DATA_CALLBACK *callback_func, IN void *user_ptr, IN TBRW_U64 start_index)
 * @brief       enumerates the bind information for data samples
 *
 * @param       tbrw_ptr IN - tbrw file handle.
 * @param       data_stream IN - the data stream of interest
 * @param       callback_func IN - the user defined callback function
 * @param       user_ptr IN - user supplied pointer that is passed to the callback function untouched (index starts at 0)
 * @param       start_index IN - the index into the data stream to start enumerating from
 *
 * @return      returns 0 if successful or returns an error code on failure.
 *
 * @special
 *
 * @todo
 *
 */
TBRW_API
TBRW_U32 TBRW_APICALL TBRW_bind_enumerate_data(IN TBRW_PTR ptr, IN TBRW_U32 data_stream, IN BIND_DATA_CALLBACK *callback_func, IN void *user_ptr, IN TBRW_U64 start_index);

/* ------------------------------------------------------------------------- */
/*!
 * @fn          TBRW_bind_enumerate_modules(IN TBRW_PTR ptr, IN BIND_MODULE_CALLBACK *callback_func, IN void *user_ptr, IN TBRW_U64 start_index)
 * @brief       enumerates the bind information for modules
 *
 * @param       tbrw_ptr IN - tbrw file handle.
 * @param       callback_func IN - the user defined callback function
 * @param       user_ptr IN - user supplied pointer that is passed to the callback function untouched (index starts at 0)
 * @param       start_index IN - the index into the module section to start enumerating from
 *
 * @return      returns 0 if successful or returns an error code on failure.
 *
 * @special
 *
 * @todo
 *
 */
TBRW_API
TBRW_U32 TBRW_APICALL TBRW_bind_enumerate_modules(IN TBRW_PTR ptr, IN BIND_MODULE_CALLBACK *callback_func, IN void *user_ptr, IN TBRW_U64 start_index);

/* ------------------------------------------------------------------------- */
/*!
 * @fn          TBRW_bind_enumerate_tids(IN TBRW_PTR ptr, IN BIND_TID_CALLBACK *callback_func, IN void *user_ptr, IN TBRW_U64 start_index)
 * @brief       enumerates the bind information for modules
 *
 * @param       tbrw_ptr IN - tbrw file handle.
 * @param       callback_func IN - the user defined callback function
 * @param       user_ptr IN - user supplied pointer that is passed to the callback function untouched (index starts at 0)
 * @param       start_index IN - the index into the thread section to start enumerating from
 *
 * @return      returns 0 if successful or returns an error code on failure.
 *
 * @special
 *
 * @todo
 *
 */
TBRW_API
TBRW_U32 TBRW_APICALL TBRW_bind_enumerate_tids(IN TBRW_PTR ptr, IN BIND_TID_CALLBACK *callback_func, IN void *user_ptr, IN TBRW_U64 start_index);

/* ------------------------------------------------------------------------- */
/*!
 * @fn          TBRW_get_one_module(IN TBRW_PTR ptr, IN TBRW_U64 module_index, OUT const TBRW_MODULE **p_module)
 * @brief       returns one module based on index
 *
 * @param       tbrw_ptr IN - tbrw file handle.
 * @param       module_index IN - the index of the module to be returned
 * @param       p_module OUT - pointer to the module located at index module_index. This pointer is valid until the next
 *                             time this function is called.
 *
 * @return      returns 0 if successful or returns an error code on failure.
 *
 * @special
 *
 * @todo
 *
 */
TBRW_API
TBRW_U32 TBRW_APICALL TBRW_get_one_module(IN TBRW_PTR ptr, IN TBRW_U64 module_index, OUT const TBRW_MODULE **p_module);

/* ------------------------------------------------------------------------- */
/*!
 * @fn          TBRW_get_one_pid(IN TBRW_PTR ptr, IN TBRW_U64 pid_index, OUT const TBRW_PID **p_pid)
 * @brief       returns one process based on index
 *
 * @param       tbrw_ptr IN - tbrw file handle.
 * @param       pid_index IN - the index of the process to be returned
 * @param       p_pid OUT - pointer to the process located at index pid_index. This pointer is valid until the next
 *                             time this function is called.
 *
 * @return      returns 0 if successful or returns an error code on failure.
 *
 * @special
 *
 * @todo
 *
 */
TBRW_API
TBRW_U32 TBRW_APICALL TBRW_get_one_pid(IN TBRW_PTR ptr, IN TBRW_U64 pid_index, OUT const TBRW_PID **p_pid);

/* ------------------------------------------------------------------------- */
/*!
 * @fn          TBRW_get_one_tid(IN TBRW_PTR ptr, IN TBRW_U64 tid_index, OUT const TBRW_TID **p_tid)
 * @brief       returns one thread based on index
 *
 * @param       tbrw_ptr IN - tbrw file handle.
 * @param       tid_index IN - the index of the thread to be returned
 * @param       p_tid OUT - pointer to the thread located at index pid_index. This pointer is valid until the next
 *                             time this function is called.
 *
 * @return      returns 0 if successful or returns an error code on failure.
 *
 * @special
 *
 * @todo
 *
 */
TBRW_API
TBRW_U32 TBRW_APICALL TBRW_get_one_tid(IN TBRW_PTR ptr, IN TBRW_U64 tid_index, OUT const TBRW_TID **p_tid);


/* ------------------------------------------------------------------------- */
/*!
 * @brief Convert a UTF-8-encoded string into a native wchar_t string.
 * @param[in] utf8 The input string, encoded in UTF-8.
 * @param[out] wcs A buffer for the output string of native wchar_t's.
 * @param[in,out] wcs_size The number of characters in the output buffer, wcs.
 *  It will be set to the number of characters used, or the number needed if
 *  the return value is TBRW_BUFFER_TOO_SMALL.
 * @return An error status indicator.
 * @note A common usage is to call this function with *wcs_size = 0.  This
 *  basically acts as a query, and wcs can be NULL.  As long the conversion
 *  still succeeds internally, the return value will be TBRW_BUFFER_TOO_SMALL,
 *  and *wcs_size will be set to the number of characters needed in the output
 *  buffer.  You can then allocate your buffer accordingly and call this again.
 */
TBRW_API TBRW_U32 TBRW_APICALL
TBRW_convert_utf8_to_wcs (
        IN const char *utf8,
        OUT wchar_t *wcs,
        INOUT TBRW_U32 *wcs_size
        );

/* ------------------------------------------------------------------------- */
/*!
 * @brief Convert a UTF-8-encoded string into a native wchar_t string.
 * @param[in] utf8 The input string, encoded in UTF-8.
 * @param[out] wcs The output string of native wchar_t's; NULL on error.
 * @return An error status indicator.
 * @note This serves as a wrapper for utf8_to_wcs_malloced that also allocates the
 *  destination string with malloc.  If 0 is returned, then wcs will
 *  be non-NULL, and the memory should eventually be released with free().
 */
TBRW_API TBRW_U32 TBRW_APICALL
TBRW_convert_utf8_to_wcs_malloced (
        IN const char *utf8,
        OUT wchar_t **wcs
        );

/* ------------------------------------------------------------------------- */
/*!
 * @brief Convert a native wchar_t string into a UTF-8-encoded string.
 * @param[in] wcs The input string, as native wchar_t's.
 * @param[out] utf8 A buffer for the output string encoded in UTF-8.
 * @param[in,out] utf8_size The number of characters in the output buffer,
 *  utf8.  It will be set to the number of characters used, or the number
 *  needed if the return value is TBRW_BUFFER_TOO_SMALL.
 * @return An error status indicator.
 * @note A common usage is to call this function with *utf8_size = 0.  This
 *  basically acts as a query, and utf8 can be NULL.  As long the conversion
 *  still succeeds internally, the return value will be TBRW_BUFFER_TOO_SMALL,
 *  and *utf8_size will be set to the number of characters needed in the output
 *  buffer.  You can then allocate your buffer accordingly and call this again.
 */
TBRW_API TBRW_U32 TBRW_APICALL
TBRW_convert_wcs_to_utf8(
        IN const wchar_t *wcs,
        OUT char *utf8,
        INOUT TBRW_U32 *utf8_size
        );

/* ------------------------------------------------------------------------- */
/*!
 * @brief Convert a native wchar_t string into a UTF-8-encoded string.
 * @param[in] wcs The input string, as native wchar_t's.
 * @param[out] utf8 The output string encoded in UTF-8; NULL on error.
 * @return An error status indicator.
 * @note This serves as a wrapper for wcs_to_utf8_malloced that also allocates the
 *  destination string with malloc.  If 0 is returned, then utf8 will
 *  be non-NULL, and the memory should eventually be released with free().
 */
TBRW_API TBRW_U32 TBRW_APICALL
TBRW_convert_wcs_to_utf8_malloced(
        IN const wchar_t *wcs,
        OUT char **utf8
        );



#ifdef __cplusplus
}
#endif   // __cplusplus

#endif //__TBRW_PUBLIC_H__
