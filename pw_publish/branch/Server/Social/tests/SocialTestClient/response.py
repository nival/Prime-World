from logging import debug, info

MAX_LOG_DATA_LENGTH = 1024

class Response:

    def __init__(self, callback):
        self.callback = callback

    def __call__(self, requestId, data):
        str_data = str(data)
        if len(str_data) <= MAX_LOG_DATA_LENGTH:
            debug( "Response data: %s" % str_data )
        else:
            debug( "Response data START: %s\n...\n%s" % ( str_data[:MAX_LOG_DATA_LENGTH], str_data[-MAX_LOG_DATA_LENGTH/2:] ) )
            
        if data:
            if data['response']['ok'] == 1:
                self.callback(data)
            else:
                self.callback.__self__.Fail(data['response']['error'])
        else:
            self.callback.__self__.Fail('%s error' % self.callback.__name__)
