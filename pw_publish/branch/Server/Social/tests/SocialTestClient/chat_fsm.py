import fsm 
import transport
import response
import time
import base64

class SimpleMessageFSM(fsm.FSM):

    def __init__(self, context, args):
        super(SimpleMessageFSM, self).__init__(self.Login)
        self.context = context
        self.args = args
        self.data = None
        self.counter = 0
        self.login = 0

    def GetFailMessage(self):
        return self.context.GetFailMessage() or self.failMessage
    
    def Shutdown(self):
        if len(chatChannels) > 0:
            for channel in chatChannels:
                channel.Shutdown()

    def Login(self):
        if not self.context.chat.host:
            self.Fail('Chat host not defined')
        else:
            self.channel = transport.JsonChannel(transport.AsyncHTTPChannel(self.args.login+'/'+self.context.chat.host, self.args.verbose, self.args.threads))
            self.channel.start()
            return self.WaitLogin

    def send(self, args, callback, data):
        self.channel.send(data, args, response.Response(callback))
    
    def WaitLogin(self):
        if self.login < 3:
            time.sleep(0.1)
            self.login += 1        
            return self.WaitLogin
        else:
            return self.Send

    def Send(self):
        args = {
            'action' : 'ping',
            'key' : self.context.chat.key,
            'auid' : str(self.context.auid),
            'chat' : base64.urlsafe_b64encode('PRIVMSG #global0 : Hello %d!' % self.counter),
        } 
        self.send(args, self.OnReply, None)
        return self.Wait

    def OnReply(self, data):
        self.data = data['response']

    def Wait(self):
        if self.data:
            if self.data['ec'] == 0:
                if 'chat' in self.data:
                    self.text = base64.b64decode(self.data['chat'])
                    if self.text:
                        print self.text
                    if self.counter < 5:
                        self.counter += 1 
                        return self.Send
                    else:
                        self.channel.shutdown()
                        self.Pass()
                        self.Exit()
            else:
                return self.Send
