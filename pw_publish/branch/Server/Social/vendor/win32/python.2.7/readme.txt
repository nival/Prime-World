Дока на конфе
  https://confluence.nivalnetwork.com/pages/viewpage.action?pageId=167938082

Шаги установки
ставим
  python-2.7.3.msi
ставим pip
  python get-pip.py
ставим все, что ставится через pip (pip от 2.7 версии!!! pip2.7/pip-2.7/pip)
  pip install -r requirements.2.7.3.txt
не ставится через pip
  MySQL-python==1.2.3
  pycurl==7.19.0
  ujson==1.33
их ставим вручную
  MySQL-python-1.2.3.win32-py2.7.exe
  pycurl-7.19.5.win32-py2.7.exe
  ujson==1.33
проверяем, что все стало как надо
pip2.7 freeze
  tornado-redis==0.0.7
  Pygments==1.5
  pymongo==2.2.1
  suds==0.4
  thrift==0.8.0
  SOAPpy==0.12.1
  MySQL-python==1.2.3
  pycurl==7.19.0

перед запуском чистим *.pyc, если есть:
  del /S  *.pyc
удаляем старые версии БД маркетинг сервиса. При старте создадутся новые пустые совместимые с новым форматом.
win
  del /S services\marketing\*.bak
  del /S services\marketing\*.dat
  del /S services\marketing\*.dir
linux
  rm -r services/marketing/*.bak
  rm -r services/marketing/*.dat
  rm -r services/marketing/*.dir