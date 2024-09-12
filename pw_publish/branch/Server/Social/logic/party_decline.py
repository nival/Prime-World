#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from party_action import *
from logic.requests.PartyDeclineRequest import PartyDeclineRequest

class Party_decline( Party_action, PartyDeclineRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "party_decline"