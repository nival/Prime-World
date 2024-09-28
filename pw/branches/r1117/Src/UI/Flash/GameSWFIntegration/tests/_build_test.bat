@ECHO OFF
cd  build_utilities
REM java -ea -DAS3 -DAVMPLUS -classpath asc.jar macromedia.asc.embedding.ScriptCompiler -builtin -import builtin.abc -import playerglobal.abc -import testing.abc ../%1 
java -jar asc.jar -builtin -import builtin.abc -import playerglobal.abc -import testing.abc ../%1 
cd ..
