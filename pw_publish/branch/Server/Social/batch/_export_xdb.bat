REM // XML & XDB data
DEL /Q /F /S C:\Work\Tornado\tornado.src\xdb
PAUSE

XCOPY /S /Y /E C:\Work\xdb\Heroes\*.HR?B.xdb  C:\Work\Tornado\tornado.src\xdb\Heroes
XCOPY /S /Y /E C:\Work\xdb\Items\*.TALENTSET.xdb  C:\Work\Tornado\tornado.src\xdb\Items
XCOPY /S /Y /E C:\Work\xdb\Items\*.TALENT.xdb  C:\Work\Tornado\tornado.src\xdb\Items

COPY /Y C:\Work\xdb\GeneratedInfo\Talents.xml C:\Work\Tornado\tornado.src\xdb\
COPY /Y C:\Work\xdb\GeneratedInfo\Heroes.xml C:\Work\Tornado\tornado.src\xdb\

XCOPY /S /Y C:\Work\Tornado\tornado.src\xdb C:\Work\Tornado\tornado\xdb

cd \Work\Tornado\tornado
python -u xdb_data.py >xdb/xdb_gen.log

PAUSE