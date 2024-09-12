from distutils.core import setup
from distutils.extension import Extension
setup(name='mdutils',
      version='1.0',
      ext_modules=[Extension('mdutils', ['mdutilsmodule.c'])],
      )