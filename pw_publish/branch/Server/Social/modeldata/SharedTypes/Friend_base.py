#!/usr/bin/env python
import math, time
from party_const import *

class Friend_base:
  def checkForFraction( self, fraction ):
    if self.fraction != PARTY_STRING_2_PARTY_FRACTION.get( fraction, PARTY_FRACTION.NONE ):
      return False
    return True

  def checkForNoneFraction( self ):
    if self.fraction == PARTY_STRING_2_PARTY_FRACTION.get("N"):
      return True
    return False
  
