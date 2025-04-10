CALL BuildByteArray.bat

set compile=java -ea -DAS3 -DAVMPLUS -classpath ../source/utils/asc.jar macromedia.asc.embedding.ScriptCompiler -builtin -import ..\source\core\builtin.abc -import utils/ByteArray_import.abc
set cmdline=%key% ../source/core/builtin.abc %key% utils/ByteArray_import.abc

if (%build_classes%)==(true) CALL _compile_file.bat net/URLRequest.as
set cmdline=%cmdline% %key% net/URLRequest.%ext%

if (%build_classes%)==(true) CALL _compile_file.bat system/ApplicationDomain.as
set cmdline=%cmdline% %key% system/ApplicationDomain.%ext%

if (%build_classes%)==(true) CALL _compile_file.bat system/SecurityDomain.as
set cmdline=%cmdline% %key% system/SecurityDomain.%ext%

CALL ContextMeny_build.bat 
set cmdline=%cmdline% %key% ui/ContextMenu.%ext%

if (%build_classes%)==(true) CALL _compile_file.bat filters\BitmapFilter.as
set cmdline=%cmdline% %key% filters\BitmapFilter.%ext%

if (%build_classes%)==(true) CALL _compile_file.bat geom.as
set cmdline=%cmdline% %key% geom.%ext%

if (%build_classes%)==(true) CALL _compile_file.bat media\SoundTransform.as
set cmdline=%cmdline% %key% media\SoundTransform.%ext%

if (%build_classes%)==(true) CALL _compile_file.bat text\TextSnapshot.as 
set cmdline=%cmdline% %key% text\TextSnapshot.%ext%

if (%build_classes%)==(true) CALL _compile_file.bat events\Event.as
set cmdline=%cmdline% %key% events\Event.%ext%

if (%build_classes%)==(true) CALL _compile_file_2args.bat events\Event.as events\IEventDispatcher.as 
set cmdline=%cmdline% %key% events\IEventDispatcher.%ext%

if (%build_classes%)==(true) %compile% -import events\Event.as -import events\IEventDispatcher.as events\EventDispatcher.as
set cmdline=%cmdline% %key% events\EventDispatcher.%ext%

if (%build_classes%)==(true) %compile% -import system/SecurityDomain.as -import system/ApplicationDomain.as system\LoaderContext.as
set cmdline=%cmdline% %key% system\LoaderContext.%ext%

if (%build_classes%)==(true) CALL _compile_file.bat ui\ContextMenuBuiltInItems.as
set cmdline=%cmdline% %key% ui\ContextMenuBuiltInItems.%ext%

if (%build_classes%)==(true) CALL _compile_file.bat ui\ContextMenuClipboardItems.as
set cmdline=%cmdline% %key% ui\ContextMenuClipboardItems.%ext%

:: display_build uses the same env variable. so store it.
set temp_line=%cmdline%
if (%build_classes%)==(true) CALL _build_env.bat display
set cmdline=%temp_line% 
set cmdline=%cmdline% %key% display.%ext%

