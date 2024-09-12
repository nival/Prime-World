# -*- coding: utf-8 -*-

#!/usr/bin/env python
#
# (C) Dan Vorobiev 2011, Nival Network

import sys
sys.path.append('base')
from helpers import *

from binascii import crc32   # zlib version is not cross-platform

# ------------------------------------------------------------
# хелпер-структура для хранения атрибутов героя
class HeroTypeDict( ClassDict ):
    """ типа герой """
    def __init__(self, xml_item):
        pass
