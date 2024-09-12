# -*- coding: utf-8 -*-
# Скрипт для выдергивания нужных ModelData для разных AP

import os,sys

def findAllFiles():
  filepath = os.path.dirname( os.path.realpath(__file__) )
  path = filepath
  filelist = []
  for file in os.listdir( path ):
    if os.path.isfile( os.path.join( path, file ) ):
      if os.path.splitext( file )[1]:
        filelist.append( os.path.normpath( os.path.join( path, file ) ) )
  return reversed(sorted(filelist))

def findLine( f ):
  file = open( f, "r" )
  lines = file.readlines()
  file.close()
  for line in lines:
    if not line.find("create_version") == -1:
      return line
  return None

allfiles = findAllFiles()
res_dict = {}
for f in allfiles:
  line = findLine( f )
  if line and len(line) < 1024:
    res_dict[line] = f

result = open( "result.txt", "w" )
for r in res_dict:
  result.write( r + " in file " + res_dict[r] + "\n" )
result.close()

