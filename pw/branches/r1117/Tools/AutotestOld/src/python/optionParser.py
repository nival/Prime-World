import logging
import optparse
import consts
import sys

def parseOptions():
  parser = optparse.OptionParser(version = consts.VERSION)

  parser.add_option(
    '-s', '--settings',
    action = 'store', type = 'string', dest = 'settings',
    default = consts.PROJECT_SETTINGS_FILE,
    help = 'settings file to use; defaults to %s' % consts.PROJECT_SETTINGS_FILE
  )

  parser.add_option(
    '-t', '--testsuite',
    action = 'store', type = 'string', dest = 'testsuite',
    default = consts.SUITE_FILE,
    help = 'testsuite file to use; defaults to %s' % consts.SUITE_FILE
  )

  parser.add_option(
    '-q', '--quiet',
    action = 'store_const', const = logging.WARNING, dest = 'loggingLevel',
    help = 'switches on quiet mode that would print error messages only'
  )

  parser.add_option(
    '-v', '--verbose',
    action = 'store_const', const = logging.DEBUG, dest = 'loggingLevel',
    help = 'switches on verbose mode that would print debug information as well'
  )

  parser.add_option(
    '-m', '--makeimages',
    action = 'store_true', dest = 'makeImages',
    default = False,
    help = 'make golden images instead of testing'
  )

  parser.add_option(
    '-e', '--export',
    action = 'store_true', dest = 'shouldExport',
    default = True,
    help = 'auto-export data from MAX files before testing'
  )

  parser.add_option(
    '-U', '--no-update',
    action = 'store_false', dest = 'shouldUpdate',
    default = True,
    help = 'bypass sources update'
  )

  parser.add_option(
    '-B', '--no-build',
    action = 'store_false', dest = 'shouldBuild',
    default = True,
    help = 'bypass sources building'
  )

  parser.add_option(
    '-T', '--no-test',
    action = 'store_false', dest = 'shouldTest',
    default = True,
    help = 'bypass testing'
  )

  parser.add_option(
    '-E', '--no-export',
    action = 'store_false', dest = 'shouldExport',
    default = True,
    help = 'bypass auto-export'
  )

  parser.add_option(
    '-r', '--regular',
    action = 'store', type = 'int', dest = 'interval',
    default = 0,
    help = 'time interval for regular autotest run'
  )
  
  #~ TODO
  #~ parser.add_option(
    #~ '-i', '--images',
    #~ action = 'store', type = 'string', dest = 'images',
    #~ default = 'images',
    #~ help = 'folder to store golden images into; defaults to images'
  #~ )

  #~ parser.add_option(
    #~ '-o', '--testoutput',
    #~ action = 'store', dest = 'testOutput',
    #~ default = 'out',
    #~ help = 'folder for outputs of test run; defaults to out'
  #~ )

  #~ parser.add_option(
    #~ '-l', '--logoutput',
    #~ action = 'store', dest = 'logOutput',
    #~ default = 'log',
    #~ help = 'folder for logging; defaults to log'
  #~ )

  parser.set_defaults(loggingLevel = logging.INFO)

  return parser.parse_args()[0]
