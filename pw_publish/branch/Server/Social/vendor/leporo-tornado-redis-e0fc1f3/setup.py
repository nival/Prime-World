#!/usr/bin/env python

try:
    from setuptools import setup
except ImportError:
    from distutils.core import setup

VERSION = '0.0.7'

setup(name='tornado-redis',
      version=VERSION,
      description='Asynchronous Redis client for the Tornado Web Server.',
      author='Vlad Glushchuk',
      author_email='high.slopes@gmail.com',
      license="http://www.apache.org/licenses/LICENSE-2.0",
      url='http://github.com/leporo/tornado-redis',
      keywords=['Redis', 'Tornado'],
      packages=['tornadoredis'],)
