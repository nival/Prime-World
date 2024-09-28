import os
import _winreg
import re
import fnmatch
import subprocess
import sys
from win32gui import SendMessageTimeout
from win32con import HWND_BROADCAST
from win32con import WM_SETTINGCHANGE
from win32con import WM_STYLECHANGING
from win32con import WM_STYLECHANGED
from win32con import GWL_EXSTYLE
import Tkinter, tkFileDialog
from optparse import OptionParser
import tempfile
import zipfile
import shutil

def copyTree(src, dst, force, processor = None):
    for root, dirs, files in os.walk(src):
        short_path = root.replace(src, '')
        if short_path and short_path[0] == '\\':
            short_path = short_path[1:]
        cur_path = os.path.join(dst, short_path)
        if not os.path.isdir(cur_path):
            os.makedirs(cur_path)
        for name in files:
            path = os.path.join(cur_path, name)
            src_path = os.path.join(root, name)
            if force or not os.path.isfile(path):
                shutil.copyfile(src_path, path)
            else:
                if processor:
                    processor.onAlreadyExists(path) 

class ZipArchive:

    def __init__(self, name):
        self.name = name

    def writeFile(self, _path, content):
        path = os.path.abspath(os.path.normpath(_path))
        root, name = os.path.split(path)
        try:
            os.makedirs(root)
        except OSError:
            pass

        open(path, 'wb').write(content)

    def extractAll(self, root, decorator=None):
        z = zipfile.ZipFile(self.name)
        for f in z.infolist():
            if f.file_size > 0:
                if not decorator or decorator.onWrite(root, f):
                    content = z.read(f.filename)
                    path = os.path.join(root, f.filename)
                    self.writeFile(path, content)

def unzip(zip_path, destination_root, root_to_skip='', force=True):
    folder = tempfile.mkdtemp()
    z = ZipArchive(zip_path)
    z.extractAll(folder)
    copyTree(
        os.path.join(folder, root_to_skip),
        destination_root,
        force)
    shutil.rmtree(folder)


class WinRegistry:

  def __init__(self, reg=_winreg.HKEY_LOCAL_MACHINE,
               key=r"System\CurrentControlSet\Control\Session Manager\Environment"):
      self.reg = _winreg.ConnectRegistry(None, reg)
      self.key = key

  def create_subkey(self, subkey):
      key = self.key + "\\" + subkey
      _winreg.CreateKey(self.reg, key)

  def delete_subkey(self, subkey):
      key = self.key + "\\" + subkey
      _winreg.DeleteKey(self.reg, key)
    
  def set_value(self, value_name="", value="", subkey=None, value_type=_winreg.REG_SZ):
      key = self.key
      if subkey:
          key += "\\" + subkey
      k = _winreg.OpenKey(self.reg, key, 0, _winreg.KEY_WRITE)
      _winreg.SetValueEx(k, value_name, 0, value_type, value)
      _winreg.CloseKey(k)

  def get_value(self, value_name="", subkey=None):
      key = self.key
      if subkey:
          key += "\\" + subkey
      k = _winreg.OpenKey(self.reg, key)
      value = _winreg.QueryValueEx(k, value_name)[0]
      _winreg.CloseKey(k)
      return value

  def delete_value(self, value_name="", subkey=None):
      key = self.key
      if subkey:
          key += "\\" + subkey
      k = _winreg.OpenKey(self.reg, key, 0, _winreg.KEY_WRITE)
      _winreg.DeleteValue(k, value_name)
      _winreg.CloseKey(k)
      
  def append_value(self, value_name, value):
      oldvalue = self.get_value( value_name )
      self.set_value( value_name, oldvalue + ';' + value, value_type = _winreg.REG_EXPAND_SZ )
 
  def insert_value(self, value_name, value):
      oldvalue = self.get_value( value_name )
      self.set_value( value_name, value+';'+oldvalue, value_type = _winreg.REG_EXPAND_SZ )


def runCommand( args ):
    a = subprocess.Popen(
        ' '.join(args),
        shell = True,
        stdin = subprocess.PIPE,
        stderr = subprocess.PIPE,
        stdout = subprocess.PIPE)
    text1 = a.stdout.read()
    text2 = a.stderr.read()
    a.wait()

    return text1, text2


def findJavaC():
    try:
        wr = WinRegistry( key=r"Software\JavaSoft\Java Development Kit" )
        value = wr.get_value( 'CurrentVersion' )
        wr2 = WinRegistry( key=r"Software\JavaSoft\Java Development Kit"+'\\'+value )
        javapath = wr2.get_value( 'JavaHome' )
        return os.path.abspath( javapath ) + '\\bin'

    except Exception, details:
        return None


def downloadFramework():
    try:
        args = [ 'svn', 'export', '-q', '--force', 'http://www.d-inter.ru:49555/svn/PF/trunk/Tools/TestFramework', './' ]
        text1, text2 = runCommand( args )
        print text1, text2
        if text1 or text2:
            raise Exception( 'svn error', text1 + text2 )
    except Exception, details:
        sys.stderr.write( 'Error download Framework' + details + '\n' )
        return
    print 'Download Framework OK'

def fixEnvironment():
    '''Add Environment varible TestFrameworkPath, fix Path varible, add javac path'''
    path = re.sub( r'\\', '/', os.path.abspath( "." ), 0 )

    try:
        varName = 'TestFrameworkPath'
        wr = WinRegistry()
        wr.set_value(varName, path)
        paths = wr.get_value('Path')
        if paths:
            tokens = [m.upper() for m in paths.split(';')]
            if '%'+varName.upper()+'%' not in tokens:
                wr.append_value("Path", '%'+varName+'%')

#        javacpath = findJavaC()
#        if javacpath:
#            wr.append_value("Path", javacpath)
#        else:
#            print 'Java not found. Feature disabled.'

    except Exception, details:
        sys.stderr.write( 'Error fix environment' + details + '\n' )
        return

    print 'Fix environment OK'

configfilename = 'unittest.cfg'

def install():
    root = Tkinter.Tk()
    root.withdraw()
    dirname = tkFileDialog.askdirectory(parent=root,initialdir=os.path.abspath('.'),title='Select directory to install TestFramework')
    if not dirname:
        exit(1)
    if not os.path.isdir( dirname ):
        os.mkdir( dirname )
    os.chdir( dirname )
    downloadFramework()

    distribs()

    fixEnvironment( )
    print 'Refresh Environment....'
    SendMessageTimeout( HWND_BROADCAST, WM_SETTINGCHANGE, 0, "Environment", 0, 1000 )
    print 'Run tests....'
    retcode = os.system( 'test.py' )
    if not retcode:
        print 'All ok'


def setVars():
    dirname = os.path.abspath('../TestFramework')
    os.chdir( dirname )
    fixEnvironment( )
    print 'Refresh Environment....'
    SendMessageTimeout( HWND_BROADCAST, WM_SETTINGCHANGE, 0, "Environment", 0, 1000 )
    print 'All ok'


def distribs():
    eclipsePath = r"Y:\Programmer\eclipse.zip"

    root = Tkinter.Tk()
    root.withdraw()
    dirname = tkFileDialog.askdirectory(parent=root,initialdir=os.path.abspath('C:/'),title='Select directory to install Eclipse')
    if not dirname:
        exit(1)
    if not os.path.isdir( dirname ):
        os.mkdir( dirname )
    print 'Install Eclipse to ' + dirname
    unzip( eclipsePath, dirname, 'eclipse', True )
    print 'Install Eclipse OK.'


    print 'Set Eclipse Environment vars...'
    try:
        wr = WinRegistry()
        value_name = 'EclipsePath'
        value = dirname
        wr.set_value( value_name, value, value_type = _winreg.REG_SZ )
    
    except Exception, details:
        sys.stderr.write( 'Error fix environment' + details + '\n' )
        return
    print 'OK.'

    print 'Install cygwin'
    os.system( r'Y:\Programmer\cygwin\setup.exe' )

    print 'Copy make file to cygwin'
    root2 = Tkinter.Tk()
    root2.withdraw()
    dirname = tkFileDialog.askdirectory(parent=root2,initialdir=os.path.abspath('C:/'),title='Select directory with cygwin')
    if not dirname:
        exit(1)
    if not os.path.isdir( dirname ):
        exit(1)
    dirname += '/bin'
    unzip( r'Y:\Programmer\make.zip', dirname, force=True )
    print 'OK.'

    print 'Refresh Environment....'
    SendMessageTimeout( HWND_BROADCAST, WM_SETTINGCHANGE, 0, "Environment", 0, 1000 )
    print 'All ok'

def parseCommandline():
    '''Analyze command line arguments'''
    parser = OptionParser("%prog [options]")
    parser.add_option( "--setvar", action="store_true", dest="setvar", help="Only set variables", default=False )
    parser.add_option( "--distribs", action="store_true", dest="distribs", help="Install distribs and set variables", default=False )

    ( options, args ) = ( options, args ) = parser.parse_args()

    fullInstall = True

    if options.distribs:
        fullInstall = False
        distribs()
    if options.setvar:
        fullInstall = False
        setVars()

    if fullInstall:
        install()

parseCommandline()