from os.path import split
from logger.reports import *

class TextRender(Render):
  '''
    TextRender renders reports as simple texts
  '''
  @staticmethod
  def renderTextReport(report):
    return report.text

  def renderComparisonReport(self, report):
    return '%s:\n  golden image = %s; produced = %s' % (
      report.text, self(report.goldenImage), self(report.produced)
    )

  def renderNetworkReport(self, report):
    text = ''
    
    for machine, log in report.assertLogs:
      text += 'Asserts on %s:\n %s\n' % (machine, self(log))
    
    for machine, log in report.excptLogs:
      text += 'Exceptions on %s:\n %s\n' % (machine, self(log))

    return text

  @staticmethod
  def renderImage(image): return '`' + image.url + '`'

  @staticmethod
  def renderText(text):
    return text.text

  @staticmethod
  def renderTextFile(filedesc):
    path, filename = split(filedesc.filename)
    
    text = '\n----- [ begin   %s ] -----\n' % filename
    text += filedesc.text
    text += '\n----- [ end   %s ] -----\n' % filename
    
    return text

textRender = TextRender()

def formatDetailedReport(failed, warned):
  if failed:
    yield 'Failed tests:'
    yield ''

    for test, report in failed:
      yield '  ' + str(test)
      for s in textRender(report).splitlines():
        yield '    ' + s
      yield ''

  if warned:
    yield 'Warned tests:'
    yield ''

    for test, warnings in warned:
      yield '  ' + str(test)
      for warning in warnings:
        for s in textRender(warning).splitlines():
          yield '    ' + s
        yield ''
