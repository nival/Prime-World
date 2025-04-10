CALL BuildByteArray.bat

set menu_cmdline=-import ../source/core/builtin.abc utils/ByteArray_import.abc 

CALL _compile_file.bat net/URLRequest.as
set menu_cmdline=%menu_cmdline% -import net/URLRequest.abc

set menu_cmdline=%menu_cmdline% -import events\IEventDispatcher.as
set menu_cmdline=%menu_cmdline% -import events\Event.as
set menu_cmdline=%menu_cmdline% -import events\EventDispatcher.as

set menu_cmdline=%menu_cmdline% -import ui/ContextMenuBuiltInItems.as
set menu_cmdline=%menu_cmdline% -import ui/ContextMenuClipboardItems.as


java -ea -DAS3 -DAVMPLUS -classpath ../source/utils/asc.jar macromedia.asc.embedding.ScriptCompiler -builtin %menu_cmdline%  ui/ContextMenu.as
