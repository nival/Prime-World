# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.SrvDebugRequest import *

class Srv_debug( SubAction, SrvDebugRequest ):
    action = "srv_debug"
    debug = True
  
    @model_callback
    @parse
    def onStart(self):
        self.log()
        if not self.checkParams():
          return

        #ACTION LOGIC
        command = self.arguments.command
        if command == 'ping':
            self.__ping()
        elif command == 'events':
            self.__events()

        self.response["ok"] = 1
        self.fin()

    def __ping(self):
        self.response['dbg'] = 'pong'

    def __events(self):
        result_list = []
        operator_events = self.I.WS.operatorEvents
        for event_id in operator_events['pendingEvents']:
            result_list.append('pending:' + str(event_id))
        for event_id in operator_events['activeEvents']:
            result_list.append('active:' + str(event_id))
        for event_id in operator_events['finishedEvents']:
            result_list.append('finished:' + str(event_id))
        for event_id in operator_events['disabledEvents']:
            result_list.append('disabled:' + str(event_id))
        self.response['dbg'] = ';'.join(result_list)
