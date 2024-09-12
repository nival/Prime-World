import fsm 

class LauncherJoinFSM(fsm.FSM):

    def __init__(self, context, args):
        super(LauncherJoinFSM, self).__init__(self.Who)
        self.context = context
        self.args = args

    def GetFailMessage(self):
        return self.context.GetFailMessage() or self.failMessage
    
    def Who(self):
        self.context.Who(self.args.sn, self.args.user, self.args.password, self.args.a_password)
        return self.WaitWho

    def WaitWho(self):
        if self.context.GetFailMessage():
            self.Fail('API fail')
            self.Exit()
        if self.context.who:
            return self.LJoin

    def LJoin(self):
        self.context.LJoin(self.context.who['response']['info']['auid'], self.args.sn, self.args.user, self.args.password, self.args.a_password) 
        return self.WaitLJoin

    def WaitLJoin(self):
        if self.context.GetFailMessage():
            self.Fail('API fail')
            self.Exit()
        if self.context.ljoin:
            self.Exit()

class LauncherMergeFSM(fsm.FSM):

    def __init__(self, context0, context1, args):
        super(LauncherMergeFSM, self).__init__(self.Who)
        self.context0 = context0
        self.context1 = context1
        self.args = args

    def GetFailMessage(self):
        return self.context0.GetFailMessage() or self.failMessage or self.context1.GetFailMessage()
    
    def Who(self):
        self.context0.Who(self.args.sn, self.args.user, self.args.password, self.args.a_password)
        return self.WaitWho

    def WaitWho(self):
        if self.context0.GetFailMessage():
            self.Fail('API fail')
            self.Exit()
        if self.context0.who:
            return self.Who2

    def Who2(self):
        self.context1.Who(self.args.sn2, self.args.user2, self.args.password2, self.args.a_password2)
        return self.WaitWho2

    def WaitWho2(self):
        if self.context1.GetFailMessage():
            self.Fail('API fail')
            self.Exit()
        if self.context1.who:
            return self.LMerge

    def LMerge(self):
        self.context0.LMerge(self.context0.who['response']['info']['auid'], self.context0.who['response']['token'], self.context1.who['response']['info']['auid'], self.context1.who['response']['token']) 
        return self.WaitLMerge

    def WaitLMerge(self):
        if self.context0.GetFailMessage():
            self.Fail('API fail')
            self.Exit()
        if self.context0.lmerge:
            self.Pass()
            self.Exit()
