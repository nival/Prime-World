#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.ItemRemoveNewStatusRequest import ItemRemoveNewStatusRequest

class Item_remove_new_status( SubAction, ItemRemoveNewStatusRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "item_remove_new_status"
  
  # клиент просит добавить индекс вещи в ActionBar
  @model_callback # АВТОМАТИЧЕСКИ АПДЕЙТИМ ИЗМЕНЕНИЯ В MODEL DATA
  @parse
  @action_timing
  def onStart(self):
    """стартовый метод для обработки action"""
    self.log()
    if not self.checkParams():
      return
    
    # 1) достанем src вещь из keeper-a
    item = self.arguments.talent
    if item:
      #======================================================================================================
      # ОК, снимаем статус "новой вещи"
      item.IsNew = False
      self.response["ok"] = 1 # success
      #======================================================================================================
      # (TODO:AUTO-GENERATE?) отлупы 
    else:
      self.errorResponse( "bad source path or item_id" )
      return
    self.fin()
