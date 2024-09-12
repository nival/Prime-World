import consts
import settingsManager
import sys
import time

from Cheetah.Template import Template
from logger.reports import *
from os.path import join, normpath, abspath
from xml.sax.saxutils import escape

class XhtmlRender(Render):
  def __init__(self, comparisonRender, imageWidth):
    self.imageWidth = imageWidth
    self.comparisonRender = comparisonRender

  @staticmethod
  def renderTextReport(report): return '<p>' + escape(report.text) + '</p>'

  def renderComparisonReport(self, report):
    return self.comparisonRender(escape(report.text), self(report.goldenImage), self(report.produced))

  def renderNetworkReport(self, report):
    text = ''
    
    for machine, log in report.assertLogs:
      text += 'Asserts on %s:\n %s\n' % (machine, self(log))
    
    for machine, log in report.excptLogs:
      text += 'Exceptions on %s:\n %s\n' % (machine, self(log))

    return text

  def renderImage(self, image): return '<img src = "%s" width = "%d"/>' % (image.url, self.imageWidth)

  @staticmethod
  def renderText(text): return escape(text.text)

  def renderTextFile(self, filedesc): return '<p class = "embeddedText">%s</p>' % filedesc.text

class XhtmlReporter(object):
  '''
    XHTML reporter
  '''
  @classmethod
  def configure(cls, settings):
    FOLDER = 'xhtml'

    def get(option): return settingsManager.getRelativeToSettings(settings, FOLDER, option)

    # Add path to Cheetah templates into sys.path
    sys.path.append(normpath(abspath(join(settingsManager.getSettingsPath(settings), FOLDER))))

    cls.SUCCESS_TEMPLATE = get('successTemplate')
    cls.TEST_FAILURE_TEMPLATE = get('testFailureTemplate')
    cls.FATAL_FAILURE_TEMPLATE = get('fatalFailureTemplate')

    cls.CSS_FILE = get('cssFile')

    cls.IMAGE_WIDTH = settings.getint('xhtml', 'imageWidth')

    cls.TIME_FORMAT_STRING = settings.get('notification', 'timeFormatString')

  @classmethod
  def generateReport(cls, templateFile, args, setup = None):
    tmpl = Template(file = templateFile)

    tmpl.CSS_FILE = cls.CSS_FILE
    tmpl.TIME_STAMP = time.strftime(cls.TIME_FORMAT_STRING)

    for name, value in args.iteritems():
      setattr(tmpl, name, value)

    if setup:
      setup(tmpl)

    file(join(consts.LOG_FOLDER, 'report.html'), 'w').write(str(tmpl))

  def report(self, succeed, shortReport, detailedReport):
    def kind(warned, failed):
      if failed: return "failed"
      elif warned: return "warned"
      else: return "passed"

    adaptedShortReport = [(kind(w, f), c, p, w, f) for c, p, w, f in shortReport]

    if succeed:
      self.generateReport(self.SUCCESS_TEMPLATE, dict(SHORT_REPORT = adaptedShortReport))
    else:
      def setup(tmpl):
        tmpl.RENDER = XhtmlRender(tmpl.renderComparison, self.IMAGE_WIDTH)

      self.generateReport(
        self.TEST_FAILURE_TEMPLATE,
        dict(SHORT_REPORT = adaptedShortReport, DETAILED_REPORT = detailedReport),
        setup
      )

  def fatalFailure(self, info):
    self.generateReport(self.FATAL_FAILURE_TEMPLATE, dict(INFO = escape(str(info))))
