CALL BuildByteArray.bat 
java -ea -DAS3 -DAVMPLUS -classpath ../source/utils/asc.jar macromedia.asc.embedding.ScriptCompiler -builtin -import ..\source\core\builtin.abc -import utils/ByteArray_import.abc  -import %1 %2
::java -jar ../source/utils/asc.jar -log errs.txt -import ..\source\core\builtin.abc -import ..\source\shell\ByteArray.abc  -import %1 %2