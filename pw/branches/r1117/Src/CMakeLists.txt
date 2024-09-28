# CMake compatibility issues: don't modify this, please!
CMAKE_MINIMUM_REQUIRED( VERSION 2.6 )
MARK_AS_ADVANCED(CMAKE_BACKWARDS_COMPATIBILITY)
# allow more human readable "if then else" constructs
SET( CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS TRUE )
set( CMAKE_VERBOSE_MAKEFILE off )


function( list_remove_regexp LIST_NAME PATTERN )
  set( TMP_LIST )
  
  foreach(f ${${LIST_NAME}}) 
    if( NOT ${f} MATCHES ${PATTERN} )
      list( APPEND TMP_LIST ${f} )
    endif()
  endforeach()
  
  set( ${LIST_NAME} ${TMP_LIST} PARENT_SCOPE )
endfunction()

function( print_list LIST_NAME )
  foreach(f ${${LIST_NAME}}) 
    message( ${f} )
  endforeach()
endfunction()

macro( simple_add_library )
  set ( ALL_LIBS ${ALL_LIBS} ${ARGN}${CMAKE_STATIC_LIBRARY_SUFFIX} )
endmacro()


macro( process_dyn_lib DLIB_PATH )
  #http://public.kitware.com/Bug/view.php?id=9974
  #http://www.mail-archive.com/cmake@cmake.org/msg37783.html 
  ADD_CUSTOM_COMMAND(
    TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${DLIB_PATH}${CMAKE_SHARED_LIBRARY_SUFFIX}" "${CMAKE_CURRENT_BINARY_DIR}"
  )
endmacro()

project(PrimeWorld)

# project version
SET( ${PROJECT_NAME}_MAJOR_VERSION 0 )
SET( ${PROJECT_NAME}_MINOR_VERSION 1 )
SET( ${PROJECT_NAME}_PATCH_LEVEL 0 )

set( VENDOR ${${PROJECT_NAME}_SOURCE_DIR}/../Vendor )
set( SRC_DIR ${${PROJECT_NAME}_SOURCE_DIR} )

include_directories( ${SRC_DIR} )
include_directories( ${SRC_DIR}/.. )
include_directories( ${SRC_DIR}/../.. )
include_directories( ${VENDOR} )
include_directories( ${VENDOR}/xulrunner-sdk/sdk/include )
include_directories( ${VENDOR}/CxxTest/include )
include_directories( ${VENDOR}/zlib/include )
include_directories( ${VENDOR}/DirectX/include )
include_directories( ${VENDOR}/fmod/api/inc )
include_directories( ${VENDOR}/fmod/fmoddesignerapi/api/inc )
include_directories( ${VENDOR}/ACE_wrappers )
include_directories( ${VENDOR}/WTL/Include )
include_directories( ${VENDOR}/CrashRpt/include )
include_directories( ${VENDOR}/freetype/include )
include_directories( ${VENDOR}/Tamarin/ )
include_directories( ${VENDOR}/Gl/include )
include_directories( ${VENDOR}/openSSL/include )
include_directories( ${VENDOR}/Terabit )
include_directories( ${VENDOR}/Terabit/app )
include_directories( ${VENDOR}/Tamarin/source/VMPI )
include_directories( ${VENDOR}/Tamarin/source/platform )
include_directories( ${VENDOR}/Tamarin/source/core )
include_directories( ${VENDOR}/Tamarin/source/MMgc )
include_directories( ${VENDOR}/Tamarin/source/eval )
include_directories( ${VENDOR}/Tamarin/source/pcre )
include_directories( ${VENDOR}/Tamarin/source/shell )
include_directories( ${VENDOR}/Tamarin/source/extensions )
include_directories( ${SRC_DIR}/Game/PF )
include_directories( ${SRC_DIR}/Server )
include_directories( ${SRC_DIR}/Server/NetworkAIO )

file( GLOB_RECURSE ALL_SRCS *.cpp *.c )
 
list_remove_regexp( ALL_SRCS ".+/Server\\.Old/.+" ) 
list_remove_regexp( ALL_SRCS ".+/Game/PF/Server/.+" ) 

list_remove_regexp( ALL_SRCS ".+/Server/AdminConsole/.+" )
list_remove_regexp( ALL_SRCS ".+/Server/AppFramework/.+" )
list_remove_regexp( ALL_SRCS ".+/Server/ClusterAdmin/.+" )
list_remove_regexp( ALL_SRCS ".+/Server/ClusterAdminClientApp/.+" )
list_remove_regexp( ALL_SRCS ".+/Server/Coordinator/.+" )
list_remove_regexp( ALL_SRCS ".+/Server/DebugConsole/.+" )
list_remove_regexp( ALL_SRCS ".+/Server/HttpGateway/.+" )
list_remove_regexp( ALL_SRCS ".+/Server/HttpJson/.+" )
list_remove_regexp( ALL_SRCS ".+/Server/MatchMaking/.+" )
list_remove_regexp( ALL_SRCS ".+/Server/Monitoring/.+" )
list_remove_regexp( ALL_SRCS ".+/Server/ServerAppBase/.+" )
list_remove_regexp( ALL_SRCS ".+/Server/TestClientBase/.+" )
list_remove_regexp( ALL_SRCS ".+/Server/TestEcho/.+" )
list_remove_regexp( ALL_SRCS ".+/Server/TransportTest/.+" )
list_remove_regexp( ALL_SRCS ".+/Server/UpdateService.4Delete/.+" )
list_remove_regexp( ALL_SRCS ".+/Server/ZZima/.+" )

list_remove_regexp( ALL_SRCS ".+/Server/Network/FrontLine/.+" )
list_remove_regexp( ALL_SRCS ".+/Server/Network/RelayServer2/.+" )
list_remove_regexp( ALL_SRCS ".+/Server/Network/RelayServerTest/.+" )
list_remove_regexp( ALL_SRCS ".+/Server/Network/StuntClient/.+" )

list_remove_regexp( ALL_SRCS ".+/Server/Network/LoginServer\\.cpp" )
list_remove_regexp( ALL_SRCS ".+/LoginServerAsync\\.cpp$" )
list_remove_regexp( ALL_SRCS ".+/LLoginServerAsync\\.auto\\.cpp$" )
list_remove_regexp( ALL_SRCS ".+/RelayServerRunner\\.cpp$" )
list_remove_regexp( ALL_SRCS ".+/Server/NetworkAIO/netlib/.+" )

list_remove_regexp( ALL_SRCS ".+/Server/RPC/.+/.+" )

list_remove_regexp( ALL_SRCS ".+\\.tests?\\.cpp$" )
list_remove_regexp( ALL_SRCS ".+/BrowserPlugins/.+" )  
list_remove_regexp( ALL_SRCS ".+/VisualManager\\.cpp$" )  
list_remove_regexp( ALL_SRCS ".+/ClientWorldFactory\\.cpp$" )  
list_remove_regexp( ALL_SRCS ".+/NetMessagesProcessor\\.cpp$" )  
list_remove_regexp( ALL_SRCS ".+/StateAudit\\.cpp$" )  
list_remove_regexp( ALL_SRCS ".+/StateCreatingGame\\.cpp$" )  
list_remove_regexp( ALL_SRCS ".+/StateGameRoomClient\\.cpp$" )  
list_remove_regexp( ALL_SRCS ".+/StateGameRoomHost\\.cpp$" )  
list_remove_regexp( ALL_SRCS ".+/StateGameWon\\.cpp$" )  
list_remove_regexp( ALL_SRCS ".+/StateInGameHost\\.cpp$" )  
list_remove_regexp( ALL_SRCS ".+/State.+\\.cpp$" )  
list_remove_regexp( ALL_SRCS ".+/EditorNative/.+" ) 
list_remove_regexp( ALL_SRCS ".+/FormulaBuilder/.+" ) 
list_remove_regexp( ALL_SRCS ".+/Audit/.+" ) 
list_remove_regexp( ALL_SRCS ".+/PingTester/.+" ) 
list_remove_regexp( ALL_SRCS ".+/GameTestClient/.+" ) 
list_remove_regexp( ALL_SRCS ".+/Tower/.+" ) 
list_remove_regexp( ALL_SRCS ".+/Town/.+" ) 
list_remove_regexp( ALL_SRCS ".+/HybridServer/.+" ) 
list_remove_regexp( ALL_SRCS ".+/UniServer/.+" ) 
list_remove_regexp( ALL_SRCS ".+/WorldDraw/.+" ) 
list_remove_regexp( ALL_SRCS ".+/Launcher/.+" ) 
list_remove_regexp( ALL_SRCS ".+/ReplayPlayer/.+" ) 
list_remove_regexp( ALL_SRCS ".+/MayaExtension/.+" ) 
list_remove_regexp( ALL_SRCS ".+/Tests/.+" ) 
list_remove_regexp( ALL_SRCS ".+/tests/.+" ) 
list_remove_regexp( ALL_SRCS ".+/MeshConverter/.+" ) 
list_remove_regexp( ALL_SRCS ".+/ShaderCompiler/.+" ) 
list_remove_regexp( ALL_SRCS ".+/Net/.+" ) 
list_remove_regexp( ALL_SRCS ".+/NetRun/.+" ) 
list_remove_regexp( ALL_SRCS ".+/StatusEffect\\.cpp$" )  
list_remove_regexp( ALL_SRCS ".+/PF_EditorNative/.+" )
list_remove_regexp( ALL_SRCS ".+/Cursors\\.cpp$" )
list_remove_regexp( ALL_SRCS ".+/DBUIRoot\\.cpp$" ) 
list_remove_regexp( ALL_SRCS ".+/FinalScreen\\.cpp$" ) 
list_remove_regexp( ALL_SRCS ".+/FinalScreenLogic\\.cpp$" ) 
list_remove_regexp( ALL_SRCS ".+/HeroSceneObject\\.cpp$" ) 
list_remove_regexp( ALL_SRCS ".+/PFBaseUnit\\.Fake\\.cpp$" ) 
list_remove_regexp( ALL_SRCS ".+/PFWorldTree\\.cpp$" ) 
list_remove_regexp( ALL_SRCS ".+/LuxPlatformTrajectory\\.cpp$" ) 
list_remove_regexp( ALL_SRCS ".+/PF_ServerCmds\\.Old/.+" )
list_remove_regexp( ALL_SRCS ".+/DebugMaterial\\.cpp$" ) 
list_remove_regexp( ALL_SRCS ".+/facefxsystem\\.cpp$" ) 
list_remove_regexp( ALL_SRCS ".+/GrassMaterial\\.cpp$" ) 
list_remove_regexp( ALL_SRCS ".+/MaterialResourceInterface\\.cpp$" ) 
list_remove_regexp( ALL_SRCS ".+/mesh\\.cpp$" ) 
list_remove_regexp( ALL_SRCS ".+/shaderconstantsbinder\\.cpp$" ) 
list_remove_regexp( ALL_SRCS ".+/Samples/.+" ) 
list_remove_regexp( ALL_SRCS ".+/ModelLoader\\.cpp$" ) 
list_remove_regexp( ALL_SRCS ".+/TimeCtrlSceneComponent\\.cpp$" ) 
list_remove_regexp( ALL_SRCS ".+/SoundFX\\.cpp$" ) 
list_remove_regexp( ALL_SRCS ".+/.+_linux\\.cpp$" ) 
list_remove_regexp( ALL_SRCS ".+/InlineProfiler3TestApp\\.cpp$" ) 
list_remove_regexp( ALL_SRCS ".+/Main\\.cpp$" ) 
list_remove_regexp( ALL_SRCS ".+/MD\\.cpp$" ) 
list_remove_regexp( ALL_SRCS ".+/ObjectFactoryDebug\\.cpp$" ) 
list_remove_regexp( ALL_SRCS ".+/TestAssertDumper\\.cpp$" ) 
list_remove_regexp( ALL_SRCS ".+/UpdaterTest\\.cpp$" ) 
list_remove_regexp( ALL_SRCS ".+/UberElement\\.cpp$" ) 
list_remove_regexp( ALL_SRCS ".+/ActionContext\\.cpp$" ) 

list_remove_regexp( ALL_SRCS ".+/builtins/accessibility\\.cpp$" )
list_remove_regexp( ALL_SRCS ".+/builtins/ByteArray_builtin\\.cpp$" )
list_remove_regexp( ALL_SRCS ".+/builtins/display\\.cpp$" )
list_remove_regexp( ALL_SRCS ".+/builtins/events\\.cpp$" )
list_remove_regexp( ALL_SRCS ".+/builtins/filters\\.cpp$" )
list_remove_regexp( ALL_SRCS ".+/builtins/geom\\.cpp$" )
list_remove_regexp( ALL_SRCS ".+/builtins/net\\.cpp$" )
list_remove_regexp( ALL_SRCS ".+/builtins/sound\\.cpp$" )
list_remove_regexp( ALL_SRCS ".+/builtins/system\\.cpp$" )
list_remove_regexp( ALL_SRCS ".+/builtins/testing\\.cpp$" )
list_remove_regexp( ALL_SRCS ".+/builtins/text\\.cpp$" )
list_remove_regexp( ALL_SRCS ".+/builtins/ui\\.cpp$" )
list_remove_regexp( ALL_SRCS ".+/builtins/utils\\.cpp$" )
list_remove_regexp( ALL_SRCS ".+/builtins/xml\\.cpp$" )
list_remove_regexp( ALL_SRCS ".+/display/Styles\\.cpp$" )

list_remove_regexp( ALL_SRCS ".+/SwfChecker\\.cpp$" )
list_remove_regexp( ALL_SRCS ".+/Dummy\\.cpp$" )
list_remove_regexp( ALL_SRCS ".+/PFResourcesCollection\\.cpp$" )
list_remove_regexp( ALL_SRCS ".+/DummySound\\.cpp$" )
list_remove_regexp( ALL_SRCS ".+/FullScreenTest\\.cpp$" )
list_remove_regexp( ALL_SRCS ".+/FileStream\\.cpp$" )
list_remove_regexp( ALL_SRCS ".+/FilePileCompilerApp\\.cpp$" )


set( ALL_SRCS ${ALL_SRCS} ${SRC_DIR}/Game/PF/HybridServer/PeeredTypes.cpp )
set( ALL_SRCS ${ALL_SRCS} ${SRC_DIR}/Game/PF/HybridServer/LPeered.auto.cpp )

set( ALL_SRCS ${ALL_SRCS} ${SRC_DIR}/Game/PF/Server/Lobby/CommonTypes.cpp )
set( ALL_SRCS ${ALL_SRCS} ${SRC_DIR}/Game/PF/Server/Statistic/StatisticTypes.cpp )
set( ALL_SRCS ${ALL_SRCS} ${SRC_DIR}/Game/PF/Server/Accounting/RLobbyAccounting.auto.cpp )
set( ALL_SRCS ${ALL_SRCS} ${SRC_DIR}/Game/PF/Server/Lobby/RLobbyIEntrance.auto.cpp )
set( ALL_SRCS ${ALL_SRCS} ${SRC_DIR}/Server/Monitoring/PerfCounterProvider/PerfCounterProvider.cpp )
set( ALL_SRCS ${ALL_SRCS} ${SRC_DIR}/Server/Monitoring/PerfCounterProvider/LPerfCounterProviderIntf.auto.cpp )


set( ALL_SRCS ${ALL_SRCS} ${SRC_DIR}/../Tools/GMTools/StatisticService/RPC/RStatisticWriter.auto.cpp )
set( ALL_SRCS ${ALL_SRCS} ${SRC_DIR}/../Tools/GMTools/StatisticClient/Data.cpp )



#print_list( ALL_SRCS )


simple_add_library( comsuppw )
simple_add_library( winmm )
simple_add_library( Rpcrt4 )
simple_add_library( quartz )
simple_add_library( DbgHelp )
simple_add_library( version )
simple_add_library( Psapi )
simple_add_library( ${VENDOR}/zlib/lib/zdll )
simple_add_library( optimized ${VENDOR}/CxxTest/lib/CxxTest )
simple_add_library( debug ${VENDOR}/CxxTest/lib/CxxTestD )
simple_add_library( ${VENDOR}/jpeglib/lib/jpeglib )
simple_add_library( optimized ${VENDOR}/freetype/lib/freetype244MT )
simple_add_library( debug ${VENDOR}/freetype/lib/freetype244MT_D )
simple_add_library( ${VENDOR}/Gl/lib/GlU32 )
simple_add_library( optimized ${VENDOR}/Tamarin/lib/Release/Tamarin )
simple_add_library( debug ${VENDOR}/Tamarin/lib/Debug/Tamarin )
simple_add_library( ${VENDOR}/DirectX/Lib/x86/dxguid )
simple_add_library( ${VENDOR}/DirectX/Lib/x86/dinput8 )
simple_add_library( ${VENDOR}/DirectX/Lib/x86/d3d9 )
simple_add_library( ${VENDOR}/DirectX/Lib/x86/d3dx9 )
simple_add_library( ${VENDOR}/DirectX/Lib/x86/dxerr9 )
simple_add_library( ${VENDOR}/DirectX/Lib/x86/dxerr )
simple_add_library( ${VENDOR}/DirectShow/Lib/gtrtst32 )
simple_add_library( ${VENDOR}/DirectShow/Lib/strmbase )
simple_add_library( ${VENDOR}/DirectShow/Lib/strmiids )
simple_add_library( ${VENDOR}/fmod/api/lib/fmodex_vc )
simple_add_library( ${VENDOR}/fmod/fmoddesignerapi/api/lib/fmod_event )
simple_add_library( ${VENDOR}/fmod/fmoddesignerapi/api/lib/fmod_event_net )
simple_add_library( ${VENDOR}/CrashRpt/lib/CrashRpt )
simple_add_library( optimized ${VENDOR}/ACE_wrappers/lib/ACE )
simple_add_library( debug ${VENDOR}/ACE_wrappers/lib/ACEd )
simple_add_library( optimized ${VENDOR}/Terabit/lib/IOTerabit )
simple_add_library( debug ${VENDOR}/Terabit/lib/IOTerabitd )
simple_add_library( optimized ${VENDOR}/Terabit/lib/TProactor )
simple_add_library( debug ${VENDOR}/Terabit/lib/TProactord )
simple_add_library( optimized ${VENDOR}/OpenSSL/lib/ssleay32MT )
simple_add_library( debug ${VENDOR}/OpenSSL/lib/ssleay32MTd )
simple_add_library( optimized ${VENDOR}/OpenSSL/lib/libeay32MT )
simple_add_library( debug ${VENDOR}/OpenSSL/lib/libeay32MTd )

#ws2_32.lib
#detours.lib
#detoured.lib
#shlwapi.lib

add_definitions( -DDO_NOT_USE_DLLMAIN )
add_definitions( -D_SCL_SECURE_NO_WARNINGS -D_SECURE_SCL=0 -D_CRT_NONSTDC_NO_WARNINGS -D_CRT_SECURE_NO_WARNINGS )

add_executable(${PROJECT_NAME} WIN32 ${ALL_SRCS})

IF(MSVC)
    SET(VS_IGNORE_LIBRARY_FLAGS_BASE
       "/NODEFAULTLIB:libc.lib
       /NODEFAULTLIB:libcmt.lib
       /NODEFAULTLIB:libcd.lib   
       /NODEFAULTLIB:libcmtd.lib
       /LTCG"
    )

     SET_TARGET_PROPERTIES( ${PROJECT_NAME} PROPERTIES
        LINK_FLAGS_DEBUG
        "${VS_IGNORE_LIBRARY_FLAGS_BASE}\n/NODEFAULTLIB:msvcrt.lib")    
        
     SET_TARGET_PROPERTIES( ${PROJECT_NAME} PROPERTIES
        LINK_FLAGS_RELEASE
        "${VS_IGNORE_LIBRARY_FLAGS_BASE}\n/NODEFAULTLIB:msvcrtd.lib")
        
    SET_TARGET_PROPERTIES( ${PROJECT_NAME} PROPERTIES
        COMPILE_FLAGS
        "/MP")
ENDIF()

target_link_libraries(${PROJECT_NAME} ${ALL_LIBS})

process_dyn_lib( ${VENDOR}/zlib/zlib1 )
process_dyn_lib( ${VENDOR}/fmod/fmod_event )
process_dyn_lib( ${VENDOR}/fmod/fmodex )
process_dyn_lib( ${VENDOR}/fmod/fmod_event_net )
process_dyn_lib( ${VENDOR}/ACE_wrappers/lib/ACE )
process_dyn_lib( ${VENDOR}/ACE_wrappers/lib/ACEd )
process_dyn_lib( ${VENDOR}/Terabit/lib/IOTerabit )
process_dyn_lib( ${VENDOR}/Terabit/lib/IOTerabitd )
process_dyn_lib( ${VENDOR}/Terabit/lib/TProactor )
process_dyn_lib( ${VENDOR}/Terabit/lib/TProactord )
process_dyn_lib( ${VENDOR}/OpenSSL/ssleay32 )
process_dyn_lib( ${VENDOR}/OpenSSL/libeay32 )