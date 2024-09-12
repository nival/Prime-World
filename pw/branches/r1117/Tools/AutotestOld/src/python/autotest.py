import sys
import string
import time
import smtplib
from email.MIMEText import MIMEText
import core
import builder
import errors
import logger
import logging
from logger.reporters.mail import MailReporter
import optionParser
import settingsManager
import sourceManager
import testApplications
import testPoints
import tests
import os
import consts
import re
import testCaseDB
import logger

from os.path import join, normpath, abspath

LAST_RUN_INFO = 'last.run.info'

RESULT_OK = 'OK'
RESULT_BUILD_FAILED = 'BuildFailed'
RESULT_TEST_FAILED = 'TestFailed'

class FatalFailure(Exception):
  def __init__(self, excpt, suspects = []):
    self.excpt = excpt
    self.suspects = suspects

class UserManager(object):
  @classmethod
  def configure(cls, settings):
    cls.mailNames = {}

    usersFile = settingsManager.getRelativeToSettings(settings, 'email', 'users')
    f = open(usersFile)
    if f:
      for line in f:
        name, mail = re.match('(\S+)\s*:\s*(\S+)', line).groups()
        cls.mailNames[name] = mail

  @classmethod
  def getMailByName(cls, name):
    if cls.mailNames.has_key(name):
      return cls.mailNames[name]

class MailHelper(object):
  def __init__(self, settings):
    self.host = settings.get('email', 'host')
    self.fromAddr = settings.get('email', 'fromAddress')
    self.toAddr = settings.get('email', 'notifyAddress','')

  def sendMail(self, subj, body):
    if self.toAddr == '':
      return

    msg = MIMEText(body)

    msg['Subject'] = subj
    msg['From'] = self.fromAddr
    msg['To'] = self.toAddr
    msg['X-Priority'] = '2' # high

    server = smtplib.SMTP(self.host)
    server.sendmail(self.fromAddr, self.toAddr, msg.as_string())
    server.quit()

  def buildBroken(self):
    body = 'Autotest failed to build & run game on revision %d. Possibly the build is broken. Consider deferring your update until the problem is fixed.' % sourceManager.singleton.version
    self.sendMail('pf: autotest: Build broken', body)

  def buildFixed(self):
    body = 'Problem with the build has been fixed. It is safe to update to revision %d.' % sourceManager.singleton.version
    self.sendMail('pf: autotest: Build fixed', body)

class LastRunInfo(object):
  def __init__(self, time, result):
    self.time = time
    self.result = result

  def store(self, fileName):
    import pickle
    f = file(fileName, 'w')
    pickle.dump(self, f)

  @staticmethod
  def load(fileName):
    import pickle
    if os.path.exists(fileName):
      f = file(fileName, 'r')
      return pickle.load(f)
    return None

def userList2MailList(users):
  mails = []
  for name in users:
    mail = UserManager.getMailByName(name)
    if mail:
      mails.append(mail)
    else:
      logging.warning("Couldn't find e-mail for user: %s", name)

  return mails

def gatherComponents(tests):
  components = []
  for t in tests:
    components += t.getRequiredComponents()

  unique = []
  for c in components:
    nc = normpath(c)
    if nc not in unique:
      unique.append(nc)

  return unique

def run(settings, options):
  launchTime = time.localtime()
  logging.info('****************************************************************')
  logging.info('* AUTOTEST started ' + time.strftime('%a, %d %b %Y %H:%M:%S', launchTime))
  logging.info('****************************************************************')

  sourceManager.singleton = sourceManager.SourceManager(settings)

  result = RESULT_OK

  # load test case DB
  tcDB = testCaseDB.TestCaseDB()
  tcDB.load()

  try:

    if options.shouldUpdate and not options.makeImages:
      try:
        lastUpdTime = sourceManager.singleton.getLastUpdateTime()
        sourceManager.singleton.update()

      except errors.FatalFailure, e:
        raise FatalFailure(e)

    if sourceManager.singleton.version == -1:
      raise FatalFailure('Invalid source version')

    logging.info('Gathering tests from %s...', options.testsuite)
    testSuite = tests.gatherTests(options.testsuite)
    logging.info('%d tests gathered', len(testSuite))

    if options.shouldBuild:
      try:
        logging.info('Building...')

        components = gatherComponents(testSuite)
        bldr = builder.Builder(settings)

        buildResults = {}
        for c in components:
          buildResults[c] = True

          try:
            bldr.build(c)
          except builder.BuildFailure, e:
            logging.info('Build error: %s', e.args[0])
            buildResults[c] = False

        # register successfull build
        tcDB.lastGoodBuildDate = sourceManager.singleton.getLastUpdateTime()

      except errors.FatalFailure, e:
        result = RESULT_BUILD_FAILED
        raise FatalFailure(e, sourceManager.singleton.gatherCommitAuthors(tcDB.lastGoodBuildDate, sourceManager.singleton.getLastUpdateTime()))

      # remove tests for which we don't have all required components
      readyToTest = []
      for t in testSuite:
        components = t.getRequiredComponents()

        nc = 0
        for c in components:
          if buildResults[normpath(c)]:
            nc += 1

        if nc == len(components):
          readyToTest.append(t)
        else:
          logger.log.failed(t, errors.TestFailed('Failed to build some required components').report())

      testSuite = readyToTest

    if options.shouldTest:
      result = RESULT_TEST_FAILED # set default value in case some exception is raised

      # use persistent data from DB for known tests
      for t in testSuite:
        if t.key() in tcDB.tests:
          t.pd = tcDB.tests[ t.key() ]

      try:
        if not options.makeImages:
          core.runTests(testSuite)

          broken = [t for t in testSuite if hasattr(t.pd, 'lastGoodRunDate') and t.lastRunException != None]
          if broken != []:
            lastOKDate = min( [ t.pd.lastGoodRunDate for t in broken ] )
            suspects = sourceManager.singleton.gatherCommitAuthors(lastOKDate, sourceManager.singleton.getLastUpdateTime())
            logging.info('Suspects: '+ ' '.join(suspects) )
            MailReporter.setAuxMailList(userList2MailList(suspects))
          else:
            result = RESULT_OK

          logger.log.report()
          logger.log.backup()
        else:
          core.makeGoldenImages(testSuite)

      except errors.FatalFailure, e:
        lastOKDate = min( [t.pd.lastGoodRunDate for t in testSuite] )
        raise FatalFailure(e, sourceManager.singleton.gatherCommitAuthors(lastOKDate, sourceManager.singleton.getLastUpdateTime()))

      # update DB with test results
      tcDB.tests.update( dict( [[t.key(), t.pd] for t in testSuite] ) )

  except FatalFailure, e:
    logging.error('Autotest fatal failure: %s', e.excpt)
    if not options.makeImages:
      logging.info('Suspects: '+ ' '.join(e.suspects) )
      MailReporter.setAuxMailList(userList2MailList(e.suspects))
      logger.log.fatalFailure(e.excpt)
      logger.log.backup()


  # save test case DB
  tcDB.store()

  # send notification mail
  lri = LastRunInfo.load(LAST_RUN_INFO)
  mailer = MailHelper(settings)
  if ((result == RESULT_BUILD_FAILED or result == RESULT_TEST_FAILED) and
      lri != None and lri.result == RESULT_OK):
    mailer.buildBroken()
  if result == RESULT_OK and lri != None and lri.result != RESULT_OK:
    mailer.buildFixed()

  # store info about this run
  lri = LastRunInfo(launchTime, result)
  lri.store(LAST_RUN_INFO)

  logging.info('****************************************************************')
  logging.info('* AUTOTEST finished ' + time.strftime('%a, %d %b %Y %H:%M:%S'))
  logging.info('****************************************************************')

def main():
  consts.INITIAL_FOLDER = os.getcwd()

  options = optionParser.parseOptions()

  logging.basicConfig(stream = sys.stdout, level = options.loggingLevel, format = '%(levelname)s: %(message)s')

  settings = settingsManager.readSettings(options.settings)
  logger.init(settings)

  UserManager.configure(settings)
  testApplications.configureApplications(settings)
  tests.configureTests(settings)
  testPoints.configureTestpoints(settings)

  logger.reset()
  run(settings, options)

  logging.shutdown()

if __name__ == '__main__':
  main()
