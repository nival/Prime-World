CALL BuildByteArray.bat
set compile=java -ea -DAS3 -DAVMPLUS -classpath ../source/utils/asc.jar macromedia.asc.embedding.ScriptCompiler -builtin -import ..\source\core\builtin.abc -import utils/ByteArray_import.abc
set cmdline=%key% ../source/core/builtin.abc %key% utils/ByteArray_import.abc

if (%build_classes%)==(true) CALL _compile_file.bat events\Event.as
set cmdline=%cmdline% %key% events\Event.%ext%

if (%build_classes%)==(true) CALL _compile_file_2args.bat events\Event.as events\IEventDispatcher.as 
set cmdline=%cmdline% %key% events\IEventDispatcher.%ext%

if (%build_classes%)==(true) %compile% -import events\Event.as -import events\IEventDispatcher.as events\EventDispatcher.as
set cmdline=%cmdline% %key% events\EventDispatcher.%ext%

