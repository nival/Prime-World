# -*- coding: utf-8 -*-
#!/usr/bin/env python
import time

class LordInfo_base:

  # дополнительные (server-side) сериализуемые поля
  def generateBaseDict(self):
    if not hasattr( self, "lastFameUpdateTime_" ):
      self.lastFameUpdateTime_ = time.time()
    if not hasattr( self, "lastDodgesUpdateTime_" ):
      self.lastDodgesUpdateTime_ = time.time()
    return dict(
      lastFameUpdateTime_ = self.lastFameUpdateTime_,
      lastDodgesUpdateTime_ = self.lastDodgesUpdateTime_
    )
