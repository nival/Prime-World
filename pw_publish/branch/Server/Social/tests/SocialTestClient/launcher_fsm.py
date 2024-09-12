import fsm 

class LauncherLoginFSM(fsm.FSM):

    def __init__(self, context, args):
        super(LauncherLoginFSM, self).__init__(self.Who)
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
            return self.LLogin

    def LLogin(self):
        self.context.LLogin(self.context.who['response']['info']['auid'], [ (self.args.sn, self.args.user, self.args.password, self.args.a_password) ] )
        return self.WaitLLogin

    def WaitLLogin(self):
        if self.context.GetFailMessage():
            self.Fail('API fail')
            self.Exit()
        if self.context.llogin:
            return self.Login

    def Login(self):
        self.context.Login(self.context.who['response']['info']['auid'], self.context.who['response']['token'], 'pw' )
        return self.WaitLogin

    def WaitLogin(self):
        if self.context.GetFailMessage():
            self.Fail('API fail')
            self.Exit()
        if self.context.uid:
            self.Exit()
