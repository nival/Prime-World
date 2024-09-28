CALL BuildByteArray.bat 
java -ea -DAS3 -DAVMPLUS -classpath ../source/utils/asc.jar macromedia.asc.embedding.ScriptCompiler -builtin -import ..\source\core\builtin.abc -import utils/ByteArray_import.abc  %1 
