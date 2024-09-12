import sys, os, time
import getopt

SHUTDOWN_TIMEOUT = 60

FILEMASK = "ws"

def files_exist():
  curDir = os.getcwd() + "/logs"
  file_list = os.listdir( curDir ) 
  for filename in file_list[:]:
    if filename.find("%s.running." % FILEMASK) >= 0:
      return True
  return False


arglist = sys.argv[1:]
#print "arglist: ", arglist
opts, args = getopt.getopt( arglist, "", ["filemask="] )
for opt, arg in opts:
  if opt == "--filemask":
    FILEMASK = arg or FILEMASK

os.chdir("..")
print "wait for %s shutdown..." % FILEMASK
startTime = time.time()
exist = files_exist()
while exist:
  time.sleep( 1.0 )
  elapsed = time.time() - startTime
  print "(%d)" % int(elapsed)
  if elapsed > SHUTDOWN_TIMEOUT:
    print "%s SHUTDOWN TIMEOUT (%s seconds elapsed)" % (FILEMASK.upper(), SHUTDOWN_TIMEOUT)
    exit(-1)
  exist = files_exist()
print "%s shutdown ok" % FILEMASK
