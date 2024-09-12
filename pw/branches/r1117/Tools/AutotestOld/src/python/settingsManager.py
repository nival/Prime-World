import ConfigParser
import logging
import consts

from os.path import join, abspath, normpath

def fetch(parsers, methodName, section, option,default=None):
  for p in parsers[:-1]:
    try:
      method = getattr(p, methodName)
      return method(section, option)
    except (ConfigParser.NoSectionError, ConfigParser.NoOptionError), _:
      pass

  if default == None:
    method = getattr(parsers[-1], methodName)
    return method(section, option)
  else:
    try:
      method = getattr(p, methodName)
      return method(section, option)
    except (ConfigParser.NoSectionError, ConfigParser.NoOptionError), _:
      return default
  
class Settings(object):
  def __init__(self, *parsers):
    self.parsers_ = parsers

    # Find out configurations
    testConfigs = set()
    configurations = {}

    for group in self.get('general', 'configurations').split(';'):
      configs = [s.strip() for s in group.split(',')]
      main = configs[0]

      assert main not in testConfigs, 'configuration %s leads two groups!' % main
      testConfigs.add(main)

      for config in configs:
        assert config not in configurations, 'configuration %s mapped to both %s and %s' % (config, configurations[config], main)
        configurations[config] = main

    self.configurations = configurations

  def get(self, section, option,default=None):
    return fetch(self.parsers_, 'get', section, option,default)

  def getint(self, section, option):
    return fetch(self.parsers_, 'getint', section, option)

  def getfloat(self, section, option):
    return fetch(self.parsers_, 'getfloat', section, option)

def readSettings(projectSettingsFile):
  def read(filename, name):
    logging.info('Reading %s settings from %s...', name, abspath(filename))
    s = ConfigParser.SafeConfigParser()
    s.read(filename)
    return s

  projectSettings = read(projectSettingsFile, 'project')

  root = getRoot(projectSettings)
  autotest = join(root, consts.AUTOTEST_PATH)
  siteSettings = read(join(autotest, consts.SITE_SETTINGS_FILE), 'site')

  return Settings(projectSettings, siteSettings)

def getRoot(settings):
  return abspath(normpath(settings.get('general', 'root')))

def getSettingsPath(settings):
  autotestPath = join(getRoot(settings), consts.AUTOTEST_PATH)
  settingsPath = join(autotestPath, consts.SITE_SETTINGS_FOLDER)
  return settingsPath

def getRelativeToSettings(settings, section, option):
  autotestPath = join(getRoot(settings), consts.AUTOTEST_PATH)
  settingsPath = join(autotestPath, consts.SITE_SETTINGS_FOLDER)
  return normpath(abspath(join(settingsPath, settings.get(section, option))))

def getStringList(settings, section, option):
  return [e.strip() for e in settings.get(section, option).split(',')]
