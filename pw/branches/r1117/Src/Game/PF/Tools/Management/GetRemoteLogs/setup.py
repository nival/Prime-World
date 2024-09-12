# ADD pythoncom26.dll, pywintypes26.dll (or analogs) and RUN "python setup.py py2exe" to rebuild

from distutils.core import setup
import py2exe

setup(
options = {'py2exe': {'bundle_files': 1}},
console=['get_remote_logs.py'],
zipfile=None
)
