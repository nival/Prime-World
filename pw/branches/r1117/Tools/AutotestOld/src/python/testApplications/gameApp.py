from stdTestApplication import StdTestApplication
from os.path import join, normpath, abspath, splitext

class GameApp(StdTestApplication):
  '''
    mapToolTest test application class
  '''

  PROJECT_NAME = 'PF_Game'

  @classmethod
  def configure(cls, settings):
    super(GameApp, cls).configure(settings)

    cls.PROJECT_PATH = 'Src'

  @staticmethod
  def args():
    return 'single'

  @classmethod
  def timeout(cls):
    '''
      Returns no-response timeout (in milliseconds)
    '''
    return 10000

  @classmethod
  def workingDir(cls, configuration):
    '''
      Returns path to the directory test application should be run from
      for the given configuration.

      configuration - configuration to get test application for
    '''
    return join(cls.root, 'Bin')
