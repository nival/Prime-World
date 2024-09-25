set key=-import
set ext=as
set build_classes=false

::this will set cmdline to the required state using key
CALL %1%_set_env.bat 

java -ea -DAS3 -DAVMPLUS -classpath ../source/utils/asc.jar macromedia.asc.embedding.ScriptCompiler -builtin %cmdline% %1%.as
::java -jar ../source/utils/asc.jar -log errs.txt %cmdline% %1%.as

set key=
set ext=abc
set build_classes=true
CALL %1%_set_env.bat
"../source/utils/nativegen.py" %cmdline% %1%.abc
