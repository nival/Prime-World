# -*- coding: utf-8 -*-

from base.helpers import *

class AddIsRegularMMAllowedFlag:
  def convertModelData( self, env, acc, md, dict ):
    if not acc.db.has_key("isRegularMMAllowed"):
      acc.db.isRegularMMAllowed = True
    return md, acc.db
