import urllib                        
import time
from logging import debug

first_mode = {
    'session_start_training' : 'first_session_training',
    'session_start_pvp' : 'first_session_pvp',
}

class Module:

    def __init__(self, queue, config):
        self.queue = queue
        self.config = config
        assert config.url != None, "Kontagent url not defined"

    def GetPartner(self):
        return None

    def Install(self, events):
        events.OnRegister.Bind(self.OnRegister)
        events.OnBeginInstall.Bind(self.OnBeginInstall)
        events.OnCancelInstall.Bind(self.OnCancelInstall)
        events.OnLaunchInstall.Bind(self.OnLaunchInstall)
        events.OnBeginDownload.Bind(self.OnBeginDownload)
        events.OnEndInstall.Bind(self.OnEndInstall)
        events.OnReInstall.Bind(self.OnReInstall)
        events.OnUnInstall.Bind(self.OnUnInstall)
        events.OnDownloadClientBegin.Bind(self.OnDownloadClientBegin)
        events.OnDownloadClientEnd.Bind(self.OnDownloadClientEnd)
        events.OnSelectFaction.Bind(self.OnSelectFaction)
        events.OnCastleLogin.Bind(self.OnCastleLogin)
        events.OnFirstLogin.Bind(self.OnFirstLogin)
        events.OnSessionStart.Bind(self.OnSessionStart)
        events.OnFirstSessionStart.Bind(self.OnFirstSessionStart)
        events.OnFirstSpentResource.Bind(self.OnFirstSpentResource)
        events.OnSpentResource.Bind(self.OnSpentResource)
        events.OnPayment.Bind(self.OnPayment)
        events.OnFirstCastleLogin.Bind(self.OnFirstCastleLogin)
        events.OnPageView.Bind(self.OnPageView)

    def GetUrl(self, etype, args):
        url = etype+'/'
        url += '?'+urllib.urlencode(args)
        final_url = self.config.url
        if not final_url or final_url[-1] != '/':
            final_url += '/'
        final_url += url
        return final_url

    def _PushAquisitionEvent(self, user, event, _aargs={}):            
        aargs = [ 'aquisition',  user.partner]
        if user.program != None:
            aargs.append(user.program)
        self._PushDefaultEvent(user, event, _aargs, *aargs)

    def _PushDefaultEvent(self, user, event, kargs, *aargs):            
        if not event:
            event = 'unknown'
        args = {
            's' : user.muid,
            'n': event[:32],
        }
        for index, param in enumerate(aargs):
            args['st'+str(index+1)] = param
        if kargs:
            args.update(kargs)
        self._SendEvent('evt', args)

    def _SendEvent(self, etype, args):
        url = self.GetUrl(etype, args)
        self.queue.Push(url) 

    def OnBeginInstall(self, user):
        self._PushAquisitionEvent(user, 'begin_install')

    def OnBeginDownload(self, user):
        self._PushAquisitionEvent(user, 'begin_download')

    def OnEndInstall(self, user):
        self._PushAquisitionEvent(user, 'end_install')

    def OnCancelInstall(self, user):
        self._PushAquisitionEvent(user, 'cancel_install')        

    def OnLaunchInstall(self, user):
        self._PushAquisitionEvent(user, 'launch_install') 
        
    def OnReInstall(self, user):
        self._PushAquisitionEvent(user, 'reinstall')
    
    def OnPageView(self, muid, ip=None):
        args = {
            's' : muid,
            'ts' : int(time.time()),
        }
        if ip:
            args['ip'] = ip
        self._SendEvent('pgr', args)
            
    def OnUnInstall(self, user):
        self._PushAquisitionEvent(user, 'uninstall')
        args = {
            's' : user.muid,
        }
        self._SendEvent('apr', args)

    def OnDownloadClientBegin(self, user):
        self._PushAquisitionEvent(user, 'download_client_begin')

    def OnDownloadClientEnd(self, user):
        self._PushAquisitionEvent(user, 'download_client_end')

    def OnSelectFaction(self, user):
        self._PushAquisitionEvent(user, 'faction_selected')

    def OnCastleLogin(self, user, faction, auid):
        self._PushDefaultEvent(user, 'castle_login', None, 'login', faction)

    def OnFirstCastleLogin(self, user, faction):
        self._PushAquisitionEvent(user, 'first_castle')

    def OnFirstLogin(self, user):
        args = {
            's' : user.muid,
            'su' : user.su,
        }
        self._SendEvent('apa', args)
        self._PushAquisitionEvent(user, 'first_login')
        args = {
            's' : user.muid,
        }
        self._SendEvent('cpu', args)

    def OnSessionStart(self, user, faction, session_type, hero):
        if hero:
            self._PushDefaultEvent(user, session_type, None, 'session', faction, hero)
        else:
            self._PushDefaultEvent(user, session_type, None, 'session', faction)

    def OnFirstSessionStart(self, user, faction, session_type, hero):
        self._PushAquisitionEvent(user, first_mode[session_type])

    def OnSpentResource(self, user, source, resource, change, total, _gain):
        if _gain == True:
            gain = 'income'
        else:
            gain = 'spend'
        self._PushDefaultEvent(user, source, {'v' : change}, 'resources', resource, resource+'_'+gain)
        if total >= 0:
            self._PushDefaultEvent(user, resource+'_amount', {'v' : total}, 'resources', resource)

    def OnFirstSpentResource(self, user):
        self._PushAquisitionEvent(user, 'first_spend')

    def OnPayment(self, user, cvalue, source, ovalue):
        args  = {
            's' : user.muid,
            'st1' : source,
            'v' : cvalue,
        }
        self._SendEvent('mtu', args)
        self._PushAquisitionEvent(user, 'payment_'+source, {'v' : cvalue})
        self.OnSpentResource(user, source, 'gold', ovalue, 0, True)

    def OnRegister(self, user):
        args = {
            's' : user.muid,
            'st1' : 'aquisition',
            'st2' : user.partner,
            'tu' : 'partner',
            'i' : 0,
            'su' : user.su,
        }
        if user.program != None:
            args['st3'] = user.program

        url = self.GetUrl('ucc', args)
        self.queue.Push(url)

        source = None
        if user.pdata:
            source = user.pdata.get('source', None)
        self._PushAquisitionEvent(user, source)
