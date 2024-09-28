import sys
from binascii import crc32

if len(sys.argv) > 1:
  persistentIds = sys.argv[1:]
  talentNames = {}
 
  for tid in persistentIds:
  
    for i in range(0,10):
      talName = "G00"+str(i)
      if crc32(talName) == int(tid):
        talentNames.update( {tid : talName} )
        break

    for i in range(10,100):
      talName = "G0"+str(i)
      if crc32(talName) == int(tid):
        talentNames.update( {tid : talName} )
        break

    for i in range(100,1000):
      talName = "G"+str(i)
      if crc32(talName) == int(tid):
        talentNames.update( {tid : talName} )
        break

  print talentNames  

else:
  print "Usage: TalentPersistentIdToName.py 843935346 -101218247 -1281530690"