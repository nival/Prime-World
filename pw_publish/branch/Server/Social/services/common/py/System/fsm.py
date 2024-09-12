import time

class FSM:

    def __init__(self, transitions, state):
        self.transitions = transitions
        self.state = state
        self.Refresh()

    def Refresh(self):
        self.startTime = time.time()

    def GetStateTime(self):
        return time.time()-self.startTime

    def Reset(self, target):
        self.state = target
        self.Refresh()

    def Move(self, target, data=None):
        if self.state == target:
            return
        for transition in self.transitions:
            if len(transition) == 2:
                start, end = transition
                callback = None
            else:
                start, end, callback = transition
            if start == self.state and target == end:
                self.state = target
                if callback:
                    callback(data)
                self.Refresh()
                return
        raise Exception('No transition found (source=%d target=%d)' % (self.state, target))                