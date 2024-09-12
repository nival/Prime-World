# -*- coding: utf-8 -*-
import sys
from subaction import *
from party_action import *
from logic.requests.PartyFlagRequest import *

class Party_flag( Party_action , PartyFlagRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "party_flag"
  
  @model_callback
  @parse
  def onStart(self):
    """стартовый метод для обработки action"""
    self.log()

    if not self.checkParams():
      info("Party_flag (auid=%s): failed param check" % self.acc.auid)
      return
    self.addArguments( person_id=self.acc.db.auid )

    return Party_action.onStart(self)