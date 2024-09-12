import errors
import logging
import os
import settingsManager
import time
import string
import re
import consts
import shutil

from os.path import normpath, abspath, isfile, join, getmtime, exists
from settingsManager import getRelativeToSettings, getRoot

COMMIT_LOG = 'commit.log'

def removeDuplicate(list):
  if len(list) == 0:
    return []
    
  list.sort()

  newlist = [list[0]]
  for i in range(1, len(list)):
    if list[i] != list[i-1]:
      newlist.append(list[i])
      
  return newlist

UPDATE_LOG = 'update.log'

class SourceManager(object):
  def __init__(self, settings):
    self.root_ = abspath(normpath(settingsManager.getRoot(settings)))
    self.updater_ = getRelativeToSettings(settings, 'update', 'updater')
    self.updateLog = join(consts.INITIAL_FOLDER, UPDATE_LOG)
    self.updateSrcVersion()

  def updateSrcVersion(self):
    self.version = -1 # means "unknown"
    
    if not exists(self.updateLog):
      return
        
    # read update log
    f = open(self.updateLog, 'r')
    if f == None:
      return
    text = f.read()
    f.close()
    
    m = re.search('Updated to revision (\d+)', text)
    if m == None:
      m = re.search('At revision (\d+)', text)

    if m == None:
      return
    
    self.version = int(m.group(1))

  def update(self):
    logging.info('Updating the sources...')

    cmd = 'cd %s && svn revert . --recursive > %s 2>&1 && svn update >> %s 2>&1' % (self.root_, self.updateLog, self.updateLog)
    
    logging.debug('update command: %s', cmd)

    rc = os.system(cmd)
    if rc != 0:
      raise errors.FatalFailure('failed to update sources')

    shutil.copyfile(self.updateLog, join(consts.LOG_FOLDER, UPDATE_LOG))
    self.updateSrcVersion()

  def gatherAuthors(self, filename, fromTime):
    rlogfile = join(consts.INITIAL_FOLDER, 'rlog.$$$')
    cmd = 'cd %s && %s rlog -d ">= %s GMT" "sv5/%s" > "%s" && cd %s' % (self.root_, self.updater_, time.strftime('%Y/%m/%d  %H:%M:%S', time.gmtime(fromTime)), filename, rlogfile, os.getcwd())
    
    if os.system(cmd) != 0:
      raise errors.FatalFailure('failed to update sources')
      
    f = file(rlogfile, 'r')
    rlog = f.read()
    f.close()
    
    os.remove(rlogfile)
    return re.findall('author: ([^;]*);', rlog)

  def gatherCommitAuthors(self, fromTime, toTime = time.gmtime()):
    logName = abspath(COMMIT_LOG)
    cmd = 'cd %s && svn log -q -r {%s}:{%s} > %s && cd %s' % (self.root_, time.strftime('%Y-%m-%dT%H:%M:%SZ', time.gmtime(fromTime)), time.strftime('%Y-%m-%dT%H:%M:%SZ', time.gmtime(toTime)), logName, os.getcwd())
    
    logging.debug('svn log command: ' + cmd)
    
    if os.system(cmd) != 0:
      raise errors.FatalFailure('failed to retrieve SVN log')
    
    log = file(logName, 'r').read()
    
    authors = re.findall('r\d+ \| ([^ ]+) \|', log)
    
    # first commit in the list is the last one happened before specified time
    del authors[0]

    return set(authors)

  def gatherCheckinsCVS(self, fromTime):
    if not isfile(self.updateLog):
      return []
      
    cvslog = file(self.updateLog, 'r')
    
    checkins = []
    for line in cvslog.readlines():
      files = re.findall('U (.*)', line)
      
      if len(files) > 0:
        authors = self.gatherAuthors(files[0], fromTime)
        checkins = checkins + authors
        
    return removeDuplicate(checkins)
    
  def getLastUpdateTime(self):
    if isfile(self.updateLog):
      return getmtime(self.updateLog)
    else:
      return time.time()
  