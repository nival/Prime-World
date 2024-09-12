class TextReport(object):
  '''
    Class that describes one phrase information on
    test failure
  '''

  def __init__(self, text):
    self.text = str(text)

class ComparisonReport(object):
  '''
    Class that describes information on test
    failure that compares golden image and produced
    results
  '''
  def __init__(self, text, goldenImage, produced):
    self.text = text
    self.goldenImage = goldenImage
    self.produced = produced

class NetworkReport(object):
  '''
    Class that describes information on network test failure
  '''
  def __init__(self, assertLogs, excptLogs):
    self.assertLogs = assertLogs
    self.excptLogs = excptLogs

class Image(object):
  '''
    Class that references an image
  '''
  def __init__(self, url):
    self.url = url

class Text(object):
  '''
    Class that references a text
  '''
  def __init__(self, text):
    self.text = str(text)

class TextFile(object):
  '''
    Class that references a text file
  '''
  def __init__(self, filename):
    self.filename = filename

    f = file(filename)
    self.text = f.read()
    f.close()

REPORTS = [TextReport, ComparisonReport, NetworkReport, Image, Text, TextFile]

class Render(object):
  '''
    Base class for renders dispatched on report class
  '''

  mappings = dict((cls, 'render' + cls.__name__) for cls in REPORTS)

  def __call__(self, report):
    if self.mappings.has_key(type(report)):
      return getattr(self, self.mappings[type(report)])(report)
    else:
      print 'Unknown report type: ', type(report)
      return ''
