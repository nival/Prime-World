import os, sys

os.system( "taskkill /pid " + sys.argv[1] + " /F /T" )
