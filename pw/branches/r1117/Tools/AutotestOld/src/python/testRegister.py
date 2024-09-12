import os.path

class TestRegister(object):
  def __init__(self):
    self.map_ = {}

  def addTest(self, test):
    self.map_[test.key()] = len(self.map_)

  def folder(self, test):
    return '%08d' % self.map_[test.key()]

  def isRegistred(self, test):
    return test.key() in self.map_

  def store(self, folder):
    import pickle
    pickle.dump(self.map_, file('%s/register' % folder, 'w'))

  def load(self, folder):
    import pickle
    
    name = '%s/register' % folder
    if os.path.exists(name):
      self.map_ = pickle.load(file(name, 'r'))
