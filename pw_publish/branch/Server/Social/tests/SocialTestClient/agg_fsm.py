import fsm 
import transport
import time


class CallResult:

    def __init__(self):
        self.data = None
        self.isCalled = False
        self.reqId = -1

    def __call__(self, reqId, data):
        self.reqId = reqId
        self.data = data
        self.isCalled = True

class AggregatorLoginFSM(fsm.FSM):

    def __init__(self, channel, args):
        super(AggregatorLoginFSM, self).__init__(self.Login)
        self.args = args
        self.channel = channel
        self.loginCalled = False
        self.loginData = None
        self.infoCalled = False
        self.infoData = None
        self.friendsData = None
        self.friendsCalled = False
        self.friendsAllData = None
        self.friendsAllCalled = True
        self.get_billing_status = CallResult()
        self.retry_billing_registration = CallResult()
        self.index = 0

    def GetFailMessage(self):
        return self.failMessage
    
    def Login(self):
        self.channel.send(None, {'action' : 'login', 'version' : '0.3.93', 'snid' : 'fb', 'snuid' : self.args.user, 'sntoken' : self.args.password }, self.OnLogin)
        return self.Wait

    def Wait(self):
        if self.loginCalled:
            if int(self.loginData['error']) == 0:
                self.channel.send(None, {'action' : 'get_info', 'version' : '0.3.93', 'auid' : self.loginData['auid'], 'include_secure_data' : 1}, self.OnInfo)
                return self.WaitInfo
            else:
                self.Fail('login error')
                self.Exit()

    def WaitInfo(self):
        if self.infoCalled:
            if int(self.infoData['error']) == 0:
                print 'Registration date:',time.ctime(int(self.infoData['get_info']['dt_register']))
                self.channel.send(None, {'action' : 'get_friends', 'version' : '0.3.93', 'auid' : self.loginData['auid'], 'include_secure_data' : 1}, self.OnFriends)
                return self.WaitFriends
            else:
                self.Fail('get_info error')
            self.Exit()

    def WaitFriends(self):
        if self.friendsCalled:
            if int(self.friendsData['error']) == 0:
                self.friends = self.friendsData['get_friends'] 
                print 'Found %d friends' % len(self.friends)
                self.retrieveCalled = True
                self.retrieveData = {'error' : 0}
                return self.Retrieve
            else:
                self.Fail('get_friends error')
                self.Exit()

    def Retrieve(self):
        if self.retrieveCalled:
            if self.retrieveData and int(self.retrieveData['error']) == 0:
                if self.index < len(self.friends):
                    auid = self.friends[self.index]
                    self.index += 1
                    self.retrieveData = None
                    self.retrieveCalled = False
                    self.channel.send(None, {'action' : 'get_info', 'version' : '0.3.93', 'auid' : auid, 'include_secure_data' : 1}, self.OnRetrieve)
                else:
                    self.channel.send(None, {'action' : 'get_friends_info_all', 'version' : '0.3.93', 'auid' : self.loginData['auid'], 'include_secure_data' : 1}, self.OnAllFriends)
                    return self.WaitAllFriends
            else:
                self.Fail('get_info failed')
                self.Exit()

    def WaitAllFriends(self):
        if self.friendsAllCalled:
            if int(self.friendsAllData['error']) == 0:
                print 'Found %d all friends' % len(self.friendsAllData['get_friends_info_all'])
                self.Pass()
                self.channel.send(None, {'action' : 'get_billing_status', 'version' : '0.3.93', 'auid' : self.loginData['auid'] }, self.get_billing_status)
                return self.WaitBilling
            else:
                self.Fail('get_friends_info_all error')
            self.Exit()

    def WaitBilling(self):
        if self.get_billing_status.isCalled:
            if self.get_billing_status.data['get_billing_status'] == 0:
                self.channel.send(None, {'action' : 'retry_billing_registration', 'version' : '0.3.93', 'auid' : self.loginData['auid'] }, self.retry_billing_registration)
                return self.WaitBillingRegistration
            else:
                self.Pass()
                self.Exit()

    def WaitBillingRegistration(self):
        if self.retry_billing_registration.isCalled:
            print self.retry_billing_registration.data
            self.Pass()
            self.Exit()

    def OnRetrieve(self, reqId, data):
        self.retrieveData = data
        self.retrieveCalled = True

    def OnLogin(self, reqId, data):
        self.loginData = data
        self.loginCalled = True

    def OnInfo(self, reqId, data):
        self.infoData = data
        self.infoCalled = True

    def OnFriends(self, reqId, data):
        self.friendsData = data
        self.friendsCalled = True

    def OnAllFriends(self, reqId, data):
        self.friendsAllData = data
        self.friendsAllCalled = True

