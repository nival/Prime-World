import consts
import settingsManager

from os.path import join

# Standard configurations suffices
CONFIGURATION_OBJ_DIRS = {
  'Debug'  : '_Debug',
  'Release': '_Release',
}

class StdTestApplication(object):
  '''
    Base class for standard test applications

    Inherited classes should define PROJECT_NAME variable. Sources
    for standard test applications should be placed in
    sv2/source/tools/autotest/src/c++/<PROJECT_NAME> folder. Name of
    .vcproj and project should be PROJECT_NAME as well.

    Exe files should be placed into exe subfolder of project folder and
    should follow standard naming conventions.
  '''

  @classmethod
  def configure(cls, settings):
    '''
      Configures test application

      settings - settings to configure by

      This methods sets following common settings:

        sv2 - path to sv2 folder
        PROJECT_PATH - path to project folder
        expectedMspf - expected MSPF (MilliSeconds Per Frame) for test application
    '''
    cls.root = settingsManager.getRoot(settings)
    cls.PROJECT_PATH = ''

  @classmethod
  def project(cls):
    '''
      Returns path and filename of the VC++ project
    '''
    return 'all', cls.PROJECT_NAME

  @classmethod
  def objDir(cls, configuration):
    return CONFIGURATION_OBJ_DIRS[configuration]

  @classmethod
  def application(cls, configuration):
    '''
      Returns filename of test application for the given configuration

      configuration - configuration to get test application for
    '''
    app = join(join(cls.PROJECT_PATH, cls.objDir(configuration)), cls.PROJECT_NAME + '.exe')
    return join(cls.root, app)

  @classmethod
  def workingDir(cls, configuration):
    '''
      Returns path to the directory test application should be run from
      for the given configuration.

      configuration - configuration to get test application for
    '''
    d = join(cls.PROJECT_PATH, cls.objDir(configuration))
    return join(cls.root, d)
