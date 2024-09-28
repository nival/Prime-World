from thread import start_new_thread
from win32con import WAIT_TIMEOUT
from win32event import WaitForSingleObject
from win32process import CreateProcess, TerminateProcess, STARTUPINFO, GetExitCodeProcess
import pywintypes
import logging

def waitForTermination(hProcess, timeout):
  if WaitForSingleObject(hProcess, timeout) == WAIT_TIMEOUT:
    try:
      TerminateProcess(hProcess, -1)
    except pywintypes.error:
      pass
    return (True, None, None)
  else:
    return (False, GetExitCodeProcess(hProcess), None)

def launchApp(appName, args, outputFolder, timeout = 0, bAsynchronous = False):
  logging.debug('run: %s %s', appName, args)
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
    return (False, None, hProcess)

  if bAsynchronous:
    t = Thread(target = waitForTermination, args = (hProcess, timeout))
    t.start()
    return (False, None, hProcess)
  else:
    return waitForTermination(hProcess, timeout)
