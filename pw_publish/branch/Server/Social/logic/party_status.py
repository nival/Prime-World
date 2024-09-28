#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from party_action import *
from logic.requests.PartyStatusRequest import PartyStatusRequest


class Party_status( Party_action, PartyStatusRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "party_status"