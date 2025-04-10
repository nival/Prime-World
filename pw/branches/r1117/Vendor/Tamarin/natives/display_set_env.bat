CALL BuildByteArray.bat
set compile=java -ea -DAS3 -DAVMPLUS -classpath ../source/utils/asc.jar macromedia.asc.embedding.ScriptCompiler -builtin -import ..\source\core\builtin.abc -import utils/ByteArray_import.abc

set cmdline=%key% ../source/core/builtin.abc %key% utils/ByteArray_import.abc

if (%build_classes%)==(true) CALL _compile_file.bat net/URLRequest.as
set cmdline=%cmdline% %key% net/URLRequest.%ext%

if (%build_classes%)==(true) CALL _compile_file.bat system/ApplicationDomain.as
set cmdline=%cmdline% %key% system/ApplicationDomain.%ext%

if (%build_classes%)==(true) CALL _compile_file.bat system/SecurityDomain.as
set cmdline=%cmdline% %key% system/SecurityDomain.%ext%

if (%build_classes%)==(true) CALL _compile_file.bat accessibility/AccessibilityImplementation.as 
set cmdline=%cmdline% %key% accessibility/AccessibilityImplementation.%ext%

CALL ContextMeny_build.bat 
set cmdline=%cmdline% %key% ui/ContextMenu.%ext%

if (%build_classes%)==(true) CALL _compile_file.bat filters\BitmapFilter.as
set cmdline=%cmdline% %key% filters\BitmapFilter.%ext%

if (%build_classes%)==(true) CALL _compile_file.bat accessibility\AccessibilityProperties.as
set cmdline=%cmdline% %key% accessibility\AccessibilityProperties.%ext% 

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

