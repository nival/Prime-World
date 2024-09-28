# -*- coding: utf-8 -*-
import sys
from subaction import *
from party_action import *
from logic.requests.PartyInventoryIsFullRequest import *

class Party_inventory_is_full( Party_action, PartyInventoryIsFullRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "party_inventory_is_full"
  
  @model_callback
  @parse
  def onStart(self):
    """стартовый метод для обработки action"""
    self.log()
    if not self.checkParams():
      return

    self.addArguments( person_id=self.acc.db.auid )

    return Party_action.onStart(self)