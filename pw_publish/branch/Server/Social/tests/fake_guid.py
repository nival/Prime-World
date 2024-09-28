# -*- coding: utf-8 -*-
#!/usr/bin/env python
#
# (C) Dan Vorobiev 2011, Nival Network

class FakeWSGuidGenerator:
    """ притворяемся web server-ным guid генератором """
    def __init__( self, start_value=0 ):
        self.inc = start_value
        
    def nextInt64GUID( self, key ):
        self.inc += 1
        return self.inc
