#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from party_action import *
from logic.requests.PartyDisbandRequest import PartyDisbandRequest

class Party_disband( Party_action, PartyDisbandRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "party_disband"