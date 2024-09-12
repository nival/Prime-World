import TestFramework.utils
import sys

def getRevisions( text ):
  result = []
  strs = text.split('\n')
  for s in strs:
    if len(s) > 0 and s[0] == 'r':
      idx = s.find(' ')
      result.append(s[1:idx])
  return result


def findTextInDiff( text ):
  result = []
  strs = text.split('\n')
  for s in strs:
    if len(s) > 0 and s[0] == '-':
      if s.find("workTime") != -1:
        print s
        return True
  return False


def doJob( dir = "../Data/Items", files = ["*.xdb"], text = 'workTime' ):
  print "Do in " + dir + " with " + files[0] + " " + text
  for f in TestFramework.utils.collectFiles("../Data/Items", ["*.xdb"], ignored = [], recursive=True, add_root=True):
    args = [ 'svn', 'log', str(f), '-q', '--stop-on-copy' ]
    textout, texterr = TestFramework.utils.runSubprocess( args )
    #print textout
    results = getRevisions( textout )
    for r in results:
      #print r
      args = [ 'svn', 'diff', str(f), '-c', r ]
      textout, texterr = TestFramework.utils.runSubprocess( args )
      #print textout
      if findTextInDiff( textout ):
        print f

if __name__ == '__main__':
  if len(sys.argv) == 1:
    doJob()
  elif len(sys.argv) == 2:
    doJob( sys.argv[1] )
  elif len(sys.argv) == 3:
    doJob( sys.argv[1], sys.argv[2] )
  elif len(sys.argv) == 4:
    doJob( sys.argv[1], sys.argv[2], sys.argv[3] )
  else:
    doJob()
