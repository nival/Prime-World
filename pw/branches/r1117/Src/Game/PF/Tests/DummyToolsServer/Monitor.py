from Monitoring import Monitoring
from Monitoring.ttypes import *
import Monitoring.ttypes

class Handler:

    def __init__(self):
        pass

def GetParams():
    handler = Handler()
    processor = Monitoring.Monitoring.Processor(handler)
    return { 'processor' : processor, 'types' : Monitoring.ttypes }
