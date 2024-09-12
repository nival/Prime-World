cmake_minimum_required( VERSION 2.8 )

project( thread-new-test )

set( BOOST_ROOT ../../../../../Vendor/boost )
set( BOOST_LIBRARYDIR ../../../../../Vendor/boost/stage/lib )

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)

find_package( Boost COMPONENTS thread REQUIRED )

include_directories( ${Boost_INCLUDE_DIR} )
#link_directories( ${Boost_LIBRARY_DIR} )

find_library( CPPUNIT_LIBRARY NAMES cppunitd PATHS ../../../../../Vendor/cppunit/lib )
#find_library( CPPUNIT_LIBRARY NAMES cppunit )

include_directories( ../../../.. )
include_directories( ../../../../../Vendor/cppunit/include )

set( SOURCE_FILES ${SOURCE_FILES} thread-new-test.cpp )
set( SOURCE_FILES ${SOURCE_FILES} ../../thread.cpp )

add_executable( thread-new-test ${SOURCE_FILES} )

target_link_libraries( thread-new-test ${Boost_LIBRARIES} )
target_link_libraries( thread-new-test ${CPPUNIT_LIBRARY} )
#target_link_libraries( thread-new-test rt )
