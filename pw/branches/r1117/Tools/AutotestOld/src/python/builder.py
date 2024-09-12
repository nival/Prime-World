import consts
import errors
import logging
import os
import re
import shutil
import settingsManager
from os.path import join, exists


def isSolution(component):
  return (re.match('.*\.sln', component) != None)

def getSolution(component):
  if isSolution(component):
    return component
    
  path, file = os.path.split(component)
  name, ext = os.path.splitext(file)
  return join(path, '.auto', name + '.sln')

class BuildFailure(Exception):
  pass
  
class Builder(object):
  def __init__(self, settings):
    self.root_ = settingsManager.getRoot(settings)
    self.mainSolution_ = settings.get('build', 'solution')
    self.configurations_ = list(settings.configurations)
    self.shouldClean_ = settings.getint('build', 'shouldClean')

    self.builder_ = settings.get('build', 'builder')
    logging.debug('Builder set to: %s', self.builder_)

  # generate project & solution files for all required components
  def generateSolution(self, component):
    cwd = os.getcwd()
    path, file = os.path.split(component)
    cmd = 'cd %s && run %s && cd %s' % ( join(self.root_, path), file, cwd )
    rc = os.system(cmd)
    
    if rc != 0:
      raise BuildFailure('failed to auto-generate component %s' % component)

  def buildConfiguration(self, component, configuration, command):
    logName = join(consts.INITIAL_FOLDER, command + '.log')
    if exists(logName):
      os.remove(logName)
    
    fullSlnName = join(self.root_, getSolution(component))
    cmd = '%s %s /%s %s /out %s' % (self.builder_, fullSlnName, command, configuration, logName)
    logging.debug('%sing: %s', command, cmd)
    rc = os.system(cmd)

    shutil.copyfile(logName, join(consts.LOG_FOLDER, command + '.log'))
    
    if rc != 0:
      raise BuildFailure('failed to %s %s - %s' % (command, getSolution(component), configuration))

  def build(self, component):
    
    logging.info('Building %s' % component)
    
    if not isSolution(component):
      self.generateSolution(component)
    
    if self.shouldClean_:
        for configuration in self.configurations_:
          self.buildConfiguration(component, configuration, 'clean')

    for configuration in self.configurations_:
      self.buildConfiguration(component, configuration, 'build')
