from win32con import WAIT_TIMEOUT
from win32event import WaitForSingleObject
from win32process import CreateProcess, TerminateProcess, STARTUPINFO, GetExitCodeProcess
from os.path import join
from os import getcwd, chdir
from sys import argv
import pywintypes
import time
import logging

def getLocalPath(path):
  cwd = getcwd()
  chdir(path)
  localPath = getcwd()
  chdir(cwd)
  return localPath

def launchApp(appName, args, outputFolder, timeout):
  print 'run: %s %s %s (timeout = %d)' % (outputFolder, appName, args, timeout)
  hProcess, _, _, _ = CreateProcess(
    appName,
    '"' + appName + '" ' + args,
    None,
    None,
    0,
    0,
    None,
    outputFolder,
    STARTUPINFO()
  )

  if (timeout == 0):
    return (False, None)

  if WaitForSingleObject(hProcess, timeout) == WAIT_TIMEOUT:
    try:
      TerminateProcess(hProcess, -1)
    except pywintypes.error:
      pass
    return (True, None)
  else:
    return (False, GetExitCodeProcess(hProcess))


GAME_APP = 'PF_Game.exe'
REMOTE_SCRIPT_LOG = 'autotest.remote.log'
TIME_FORMAT = '%Y.%m.%d-%H.%M.%S'

rootdir = getLocalPath(argv[1])
configuration = argv[2]

log = open(join(rootdir,REMOTE_SCRIPT_LOG), 'w+')
log.write( 'Launch time: ' + time.strftime(TIME_FORMAT, time.localtime()) )
log.close()

hanged, exitCode = launchApp(join(rootdir, configuration, GAME_APP), 'exec ../$$$.remote.cfg', join(rootdir, 'Bin'), int(argv[3]))

if hanged:
  print 'Hanged'
else:
  print 'Exited with code: %d' % exitCode