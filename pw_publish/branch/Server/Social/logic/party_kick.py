#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from party_action import *
from logic.requests.PartyKickRequest import PartyKickRequest

class Party_kick( Party_action, PartyKickRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "party_kick"