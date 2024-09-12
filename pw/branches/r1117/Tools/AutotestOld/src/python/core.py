import logger
import logging
import os
import processes
import shutil
import testPoints
import testRegister

from errors import *
from logger.reporters.textUtils import textRender
from os.path import join, exists

IMAGES_FOLDER = 'out'
TEST_FOLDER = '.testfolder'

def makeGoldenImages(tests):
  logging.info('Creating golden images...')

  shutil.rmtree(IMAGES_FOLDER, ignore_errors = True)
  os.mkdir(IMAGES_FOLDER)

  try:
    register = testRegister.TestRegister()

    for test in tests:
      if register.isRegistred(test):
        logging.warning('test %s is already registred, skipping', test)
        continue

      register.addTest(test)
      logging.info('processing %s...', test)

      testFolder = join(IMAGES_FOLDER, register.folder(test))
      os.mkdir(testFolder)

      # Dump key of test
      f = file(join(testFolder, 'test-key'), 'w')
      f.write(str(test))
      f.close()

      # Find out configurations to build golden images from
      testConfigs = sorted(set(test.configurations.itervalues()))

      for config in testConfigs:
        logging.info('  building golden images for %s', config)

        outputFolder = join(testFolder, config)
        os.mkdir(outputFolder)
        runTest(test, outputFolder, config)

      logging.info('passed')

    register.store(IMAGES_FOLDER)

  except TestFailed, e:
    logging.error('test failed: %s', textRender(e.report()))
    shutil.rmtree(IMAGES_FOLDER)

def runTests(tests):
  logging.info('Running tests...')

  register = testRegister.TestRegister()
  register.load(IMAGES_FOLDER)

  for test in tests:
    if test.useGoldenImages() and not register.isRegistred(test):
      # TODO: add into a log as a root element
      logging.warning('test %s is absent from golden images, skipping', test)
      continue
    
    testFolder = ''
    if test.useGoldenImages():
      testFolder = join(IMAGES_FOLDER, register.folder(test))

    logging.info('test %s', test)

    if exists(TEST_FOLDER):
      shutil.rmtree(TEST_FOLDER)
      
    os.mkdir(TEST_FOLDER)
    
    if test.execute():
      logger.log.passed(test)
    else:
      logging.error('  %s', textRender(test.lastRunException.report()))
      logger.log.failed(test, test.lastRunException.report())

    shutil.rmtree(TEST_FOLDER)
