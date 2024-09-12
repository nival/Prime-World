import sys
import os
import fnmatch
import shutil
import tempfile
import stat

print sys.argv

def SetAttributes(folder, attribute):
  for root, dirs, files in os.walk(folder):
    for name in files:
      os.chmod(os.path.join(root, name), attribute)        

def RemoveFolders(path, pattern):
  print 'Removing svn folders from %r' % path
  result = []
  for root, dirs, files in os.walk(path):
    if pattern in dirs:
      result.append(os.path.join(root, pattern))
  print 'Found %d folders' % len(result)
  for name in result:
    print 4*' ', 'Removing %r' % name
    SetAttributes(name, stat.S_IWRITE) 
    shutil.rmtree(name)

def RemoveSVNFolders(path):
  RemoveFolders(path, '.svn')

def IsNameMatchPattern(name, patterns):
  for pattern in patterns:
    if fnmatch.fnmatch(name, pattern):
      return True
  return False

def RemoveFiles(path, patterns):
  print 'Removing files from %r by patterns %r' % (path, patterns)
  result = []
  for root, dirs, files in os.walk(path):
    for name in files:
      if IsNameMatchPattern(name, patterns):
        result.append(os.path.join(root, name))
  print 'Found %d files' % len(result)
  for name in result:
    print 4*' ', 'Removing %r' % name
    os.remove(name)

def GetVersionFromSVN(imagePath, svnPath, revision):
  folder = tempfile.mkdtemp()
  shutil.copy(r'L:\Versions\Current\CopyFile-Testers.exe', folder)
  exeName = os.path.join(folder, 'CopyFile-Testers.exe')
  args = [
    exeName,
    revision,
    svnPath,
    imagePath
  ]
  print 'Downloading version %r from %r' % (revision, svnPath)
  os.system(' '.join(args))
   

if len(sys.argv) == 4:
  version = sys.argv[1]
  revision = sys.argv[2]
  svnPath = sys.argv[3]
  imagePath = os.path.join('Versions', version, revision) # imagePath
#  GetVersionFromSVN(imagePath, svnPath, revision)
  RemoveSVNFolders(imagePath)
  RemoveFiles(imagePath, ['*.maya*'])
  unusedFiles = [
    'server.cfg',
    'PF_Editor.config',
    'private.cfg_example',
    '*.config',
    'town_server.cfg',
    'mmaking_test.cfg',
    'mmaking.cfg',
    'gameSTOE.cfg',
    'editor.cfg',
    'debugvars.cfg',
    'audit.cfg',
    'show_mipmaps.cfg',
    'town.cfg',
  ]
  RemoveFiles(os.path.join(imagePath, 'Profiles'), unusedFiles)
  RemoveFolders(os.path.join(imagePath, 'Profiles'), 'Shipping')
  RemoveFolders(os.path.join(imagePath, 'Bin'), 'Microsoft.VC90.DebugCRT')
  RemoveFolders(os.path.join(imagePath, 'Data', 'Maps'), 'Lobby')
  RemoveFolders(os.path.join(imagePath, 'Data', 'Maps'), 'LobbyArt')
  RemoveFolders(os.path.join(imagePath, 'Data', 'Maps'), 'PvE')
  RemoveFolders(os.path.join(imagePath, 'Data', 'Maps'), 'Test')
  RemoveFolders(os.path.join(imagePath, 'Data', 'Maps', 'Multiplayer'), 'CTF')
  RemoveFiles(os.path.join(imagePath, 'Bin'), ['PF_Editor*.*'])
else:
  print 'Usage: <trunk|pbt> <revision> <svn path>'