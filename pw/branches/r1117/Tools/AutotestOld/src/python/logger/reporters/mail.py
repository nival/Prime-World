import settingsManager
import smtplib
import time
import logging

from email.MIMEText import MIMEText
from email.MIMEMultipart import MIMEMultipart
from logger.reporters.textUtils import formatDetailedReport

HIGHEST_PRIORITY = '1'
HIGH_PRIORITY = '2'
NORMAL_PRIORITY = '3'

def sendMessage(host, fromAddress, sendTo, msg):
  '''
    Send a message
  '''
  try:
    server = smtplib.SMTP(host, timeout = 60)
    server.sendmail(fromAddress, sendTo, msg.as_string())
    server.quit()
  except smtplib.SMTPRecipientsRefused:
    logging.debug('Mail reporter: Some recipients were refused')

def stdMessageText(headlineTemplate, text):
  '''
    Returns standard message text formed from headlineTemplate and text

    headlineTemplate - template for headline of the message
    text - body text of the message
  '''
  headline = time.strftime(headlineTemplate)
  return '\n'.join([headline, ''] + ['  ' + s for s in text.splitlines()])

class MessageGenerator(object):
  def __init__(self, fromAddress, sendTo, successParams, testFailureParams, fatalFailureParams):
    self.FROM = fromAddress
    self.TO = ', '.join(sendTo)

    self.successParams = successParams
    self.testFailureParams = testFailureParams
    self.fatalFailureParams = fatalFailureParams

  def createMessage_(self, subject, priority, ctor, *params):
    '''
      Form standard parts of message header

      Returns created message

      subject - subject of the message
      priority - priority of the message
      ctor - ctor of the message
      params - parameters for ctor
    '''
    msg = ctor(*params)

    msg['Subject'] = subject
    msg['From'] = self.FROM
    msg['To'] = self.TO
    msg['X-Priority'] = priority

    return msg

  def textMessage_(self, (headline, subject, priority), text):
    '''
      Returns MIMEText message for the given headline, text, subject and priority
    '''
    return self.createMessage_(subject, priority, MIMEText, stdMessageText(headline, text))

  def successMessage(self, report):
    '''
      Returns success message
    '''
    return self.textMessage_(self.successParams, report)

  def testFailureMessage(self, short, detailed):
    '''
      Returns test failure message
    '''
    headline, subject, priority = self.testFailureParams

    msg = self.createMessage_(subject, priority, MIMEMultipart)
    msg.preambule = 'preambule'
    msg.epilogue = ''

    def attach(name, text):
      m = MIMEText(text)
      m.add_header('Content-Disposition', 'attachment', filename = name)
      msg.attach(m)

    attach('short report', stdMessageText(headline, short))
    attach('detailed report', detailed)

    return msg

  def fatalFailureMessage(self, info):
    '''
      Returns fatal failure report message
    '''
    return self.textMessage_(self.fatalFailureParams, str(info))

class MailReporter(object):
  '''
    Mail reporter class

    This class generates and sends e-mail about test run results
  '''

  @classmethod
  def configure(cls, settings):
    '''
      Configure MailReporter

      settings - settings to configure by
    '''
    cls.host = settings.get('email', 'host')
    cls.fromAddress = settings.get('email', 'fromAddress')
    cls.sendTo = settingsManager.getStringList(settings, 'notification', 'sendTo')

    timeFormatString = settings.get('notification', 'timeFormatString')
    def params(headline, option, priority):
      return headline % timeFormatString, settings.get('notification', option), priority

    cls.messageGenerator = MessageGenerator(
      cls.fromAddress,
      cls.sendTo,
      params('Autotest run on %s succeed:', 'successSubject', NORMAL_PRIORITY),
      params('Autotest run on %s failed:', 'testFailureSubject', HIGH_PRIORITY),
      params('Autotest run on %s fatally failed:', 'fatalFailureSubject', HIGHEST_PRIORITY)
    )

  @classmethod
  def sendMessage_(cls, msg):
    '''
      Send a message

      msg - message to send
    '''
    if hasattr(cls, 'auxMailList'):
      ml = cls.sendTo + cls.auxMailList
    else:
      ml = cls.sendTo

    logging.debug('Mail report sent to: ' + ' '.join(ml))

    sendMessage(cls.host, cls.fromAddress, ml, msg)

  @classmethod
  def setAuxMailList(cls, mailList):
    cls.auxMailList = mailList

  def makeMessage_(self, succeed, shortReport, detailedReport):
    '''
      Returns report of test run

      This method is called if no fatal failure occurs

      results - test run results
    '''
    def listTests(list, header):
      text = []
      if len(list) > 0:
        text.append(header + '\n')
        for t in list:
          text.append('   ' + t + '\n')
      return '\n'.join(text)

    passed, warned, failed = shortReport
    short = '\n'.join([listTests(failed, 'FAILED TESTS'),
                            listTests(warned, 'WARNED TESTS'),
                            listTests(passed, 'PASSED TESTS')])

    if succeed:
      return self.messageGenerator.successMessage(short)
    else:
      warned, failed = detailedReport

      return self.messageGenerator.testFailureMessage(
        short, '\n'.join(formatDetailedReport(failed, warned))
      )

  def report(self, succeed, shortReport, detailedReport):
    '''
      Report test run results

      results - results to report
    '''
    self.sendMessage_(self.makeMessage_(succeed, shortReport, detailedReport))

  def fatalFailure(self, info):
    '''
      Report fatal failure

      info - fatal failure information
    '''
    self.sendMessage_(self.messageGenerator.fatalFailureMessage(info))
