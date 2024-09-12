import os.path

TEST_CASE_DB = 'testcase.dat'

class TestCaseDB(object):
  def __init__(self):
    self.tests = {}
    self.lastGoodBuildDate = 0

  def store(self):
    import pickle
    f = file(TEST_CASE_DB, 'w')
    pickle.dump(self.lastGoodBuildDate, f)
    pickle.dump(self.tests, f)

  def load(self):
    import pickle
    if os.path.exists(TEST_CASE_DB):
      f = file(TEST_CASE_DB, 'r')
      self.lastGoodBuildDate = pickle.load(f)
      self.tests = pickle.load(f)
