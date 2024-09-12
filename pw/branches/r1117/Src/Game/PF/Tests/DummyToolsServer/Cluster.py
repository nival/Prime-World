import tornado.ioloop
import time

from ClusterManagementAPI import ClusterManagement
from ClusterManagementAPI.ttypes import *
import ClusterManagementAPI

SERVICES = [
    {'sid': 'ru/1',
     'stype': 'type1',
     'machine': 'machine1',
     'status': ServiceStatus.STOPPED,
     'pid': 4444,
     'uptime': 180,
     'parameters': [],
    },
    {'sid': 'ru/2',
     'stype': 'type2',
     'machine': 'machine1',
     'status': ServiceStatus.STOPPED,
     'pid': 5454,
     'uptime': 290,
     'parameters': [ServiceParameter(name='param', value='val', changeable=False, needrestart=False), ],
    },
    {'sid': 'ru/3',
     'stype': 'type2',
     'machine': 'machine2',
     'status': ServiceStatus.STOPPED,
     'pid': 3544,
     'uptime': 400,
     'parameters': []
    },
    {'sid': 'ru/4',
     'stype': 'type3',
     'machine': 'machine2',
     'status': ServiceStatus.STOPPED,
     'pid': 2254,
     'uptime': 230,
     'parameters': [],
    },
    {'sid': 'ru/5',
     'stype': 'type1',
     'machine': 'machine3',
     'status': ServiceStatus.STOPPED,
     'pid': 6454,
     'uptime': 160,
     'parameters': [],
    },
]

delay = 3

class ClusterManagementHandler:
    def __init__(self, services):
        self.services = [ServiceInfo(**s) for s in services]

    def GetServices(self, ):
        return self.services

    def GetServicesByMachine(self, machine):
        return [s for s in self.services if s.machine==machine]

    def GetServicesByType(self, stype):
        return [s for s in self.services if s.stype==stype]

    def GetServiceById(self, serviceid):
        try:
            return [s for s in self.services if s.sid==serviceid][0]
        except IndexError:
            return None

    def __change_status(self, serviceid, new_status):
        service = self.GetServiceById(serviceid)
        service.status = new_status
    def __start(self, serviceid, arguments):
        service = self.GetServiceById(serviceid)
        if service.status == ServiceStatus.STOPPED:
            self.__change_status(serviceid, ServiceStatus.START_PENDING)
            tornado.ioloop.IOLoop.instance().add_timeout(time.time() + delay, 
                            lambda: self.__change_status(serviceid, ServiceStatus.RUNNING))
            return 0
        else:
            return -2
    def __stop(self, serviceid, arguments):
        service = self.GetServiceById(serviceid)
        if service.status == ServiceStatus.RUNNING:
            self.__change_status(serviceid, ServiceStatus.STOP_PENDING)
            tornado.ioloop.IOLoop.instance().add_timeout(time.time() + delay,
                            lambda: self.__change_status(serviceid, ServiceStatus.WAITING_FOR_STOP))
            tornado.ioloop.IOLoop.instance().add_timeout(time.time() + delay*2, 
                            lambda: self.__change_status(serviceid, ServiceStatus.STOPPED))
            return 0
        else:
            return -2
    def __restart(self, serviceid, arguments):
        service = self.GetServiceById(serviceid)
        if service.status == ServiceStatus.RUNNING:
            self.__change_status(serviceid, ServiceStatus.STOP_PENDING)
            tornado.ioloop.IOLoop.instance().add_timeout(time.time() + delay, 
                            lambda: self.__change_status(serviceid, ServiceStatus.STOPPED))
            tornado.ioloop.IOLoop.instance().add_timeout(time.time() + delay*2, 
                            lambda: self.__change_status(serviceid, ServiceStatus.START_PENDING))
            tornado.ioloop.IOLoop.instance().add_timeout(time.time() + delay*3, 
                            lambda: self.__change_status(serviceid, ServiceStatus.RUNNING))
            return 0
        else:
            return -2
    def __soft_stop(self, serviceid, arguments):
        service = self.GetServiceById(serviceid)
        if service.status == ServiceStatus.RUNNING:
            self.__change_status(serviceid, ServiceStatus.WAITING_FOR_STOP)
            tornado.ioloop.IOLoop.instance().add_timeout(time.time() + delay,
                            lambda: self.__change_status(serviceid, ServiceStatus.STOP_PENDING))
            tornado.ioloop.IOLoop.instance().add_timeout(time.time() + delay*2, 
                            lambda: self.__change_status(serviceid, ServiceStatus.STOPPED))
            return 0
        else:
            return -2
    def __soft_restart(self, serviceid, arguments):
        service = self.GetServiceById(serviceid)
        if service.status == ServiceStatus.RUNNING:
            self.__change_status(serviceid, ServiceStatus.WAITING_FOR_RESTART)
            tornado.ioloop.IOLoop.instance().add_timeout(time.time() + delay, 
                            lambda: self.__change_status(serviceid, ServiceStatus.STOP_PENDING))
            tornado.ioloop.IOLoop.instance().add_timeout(time.time() + delay*2, 
                            lambda: self.__change_status(serviceid, ServiceStatus.STOPPED))
            tornado.ioloop.IOLoop.instance().add_timeout(time.time() + delay*3, 
                            lambda: self.__change_status(serviceid, ServiceStatus.START_PENDING))
            tornado.ioloop.IOLoop.instance().add_timeout(time.time() + delay*4, 
                            lambda: self.__change_status(serviceid, ServiceStatus.RUNNING))
            return 0
        else:
            return -2

    def ExecuteCommand(self, serviceid, command, arguments):
        commands = {ServiceCommand.START: self.__start,
                    ServiceCommand.STOP: self.__stop,
                    ServiceCommand.RESTART: self.__restart,
                    ServiceCommand.SOFT_STOP: self.__soft_stop,
                    ServiceCommand.SOFT_RESTART: self.__soft_restart, }
        service = self.GetServiceById(serviceid)
        if service!=None:
            return commands[command](serviceid, arguments)
        else:
            return -1

    def ChangeParameters(self, serviceid, parameters, saveinconfig):
        service = self.GetServiceById(serviceid)
        if service!=None:
            for serviceparam in service.parameters:
                for newparam in parameters:
                    if serviceparam.name == newparam.name:
                        serviceparam.value = newparam.value
                        serviceparam.changeable = newparam.changeable
                        serviceparam.needrestart = newparam.needrestart
                        parameters.remove(newparam)
            service.parameters = service.parameters + parameters
            return 0
        else:
            return -1

def GetParams():
    handler = ClusterManagementHandler(SERVICES)
    processor = ClusterManagement.Processor(handler)
    return { 'processor' : processor, 'types' : ClusterManagementAPI.ttypes }
