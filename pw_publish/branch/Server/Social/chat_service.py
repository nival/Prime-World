#!/usr/bin/env python
# -*- coding: utf-8 -*-

#
# Chat Proxy web-server
# (C) Eugene Ivanov 2011, Nival Network

from base.helpers import *
import base64
import datetime
import errno
import re
import heapq

addModPath('cfg')

from iwebserver import *
from tornado.options import options
import tornado.httpclient


from handlers import * # JsonHandler, IfaceFactory
from subaction import SubAction

from iuserdata import IDataManager
import chat_cfg

from ifactory import IfaceFactory
import coord_cfg

from EC import *

## ---------------------------------------------------------------------------------------------
CONNECTING = 1
CONNECTED = 2
DISCONNECTED = 3

import Queue

MUTE_PERM = -1

ADMIN_MUTE = ''

RECONNECT_PAUSE = 2.0
NEXT_RECONNECT_PAUSE = 5

##---------------------------------------------------------------------------------------------------
## ERROR CODES
OK = 0
##---------------------------------------------------------------------------------------------------
import select


def needFloodConrol(nick):
    for rx in chat_cfg.no_flood_control_nicks:
        if rx.search(nick):
            return False # means 'no flood control'
    return True

extractChannelRx = re.compile(r'^\w+\s+(#?\w+)')
def extractChannel(msgHeader):
    match = extractChannelRx.search(msgHeader)
    if match:
        return match.group(1)
    return None

def getChannelGroup(channel):
    for group in chat_cfg.flood_control_groups:
        if group['channel_rx'].search(channel):
            return group['name']
    return None

class Poller(object):
    def __init__(self, address):
        self.address = address
        self.s2c = {}
        self.c2s = {}

    def Send(self, callback, data):
        s = self.c2s.get(callback, None)
        if not s:
            error('Socket not found')
            return 0
        try:
            sentBytes = s.send(data)
            #debug('sent (fileno=%d): %d' % (s.fileno(), sentBytes) )
            return sentBytes
        except socket.error, e:
            if e.errno != errno.EWOULDBLOCK:
                #debug('sent failed (fileno=%d)' % s.fileno())
                self._Disconnect(callback, s)
                callback.OnDisconnect(True)
        return 0

    def Register(self, callback):
        if callback in self.c2s:
            error('Callback already registered (id=%r)', callback.GetId())
            return
        s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        try:
            debug('connecting (fileno=%d cid=%d) to %s', s.fileno(), id(callback), self.address)
            s.connect(self.address)
            s.setblocking(0)
            self._Register(s)
            self.s2c[s.fileno()] = callback
            self.c2s[callback] = s
            callback.OnConnect()
        except socket.error, e:
            error('socket error, disconnected (fileno=%d)', s.fileno())
            callback.OnDisconnect(True)

    def Update(self):
        disconnected = []

        self._Update(disconnected)

        for callback, s in disconnected:
            debug('disconnected (fileno=%d cid=%d)', s.fileno(), id(callback))
            self._Disconnect(callback, s)
            callback.OnDisconnect(True)

    def _Disconnect(self, callback, s):
        fileno = s.fileno()
        self._DisconnectSocket(s)
        s.close()
        del self.s2c[fileno]
        del self.c2s[callback]

    def Unregister(self, callback):
        s = self.c2s.get(callback, None)
        if not s:
            error('Socket not found')
            return
        debug('disconnecting intentionally (fileno=%d)', s.fileno())
        self._Disconnect(callback, s)
        callback.OnDisconnect(False)

    def _Register(self, s):
        raise NotImplementedError()

    def _Update(self, disconnected):
        raise NotImplementedError()

    def _DisconnectSocket(self, s):
        raise NotImplementedError()


class EPollPoller(Poller):
    def __init__(self, address):
        super(EPollPoller, self).__init__(address)
        self.epoll = select.epoll()

    def __del__(self):
        for fileno, callback in self.s2c.items():
            self.epoll.unregister(fileno)
        self.epoll.close()

    def GetStatus(self):
        return {
            'type': 'epoll',
            's2c': len(self.s2c),
            'c2s': len(self.c2s),
        }

    def _Register(self, s):
        self.epoll.register(s.fileno(), select.EPOLLIN | select.EPOLLPRI | select.EPOLLHUP | select.EPOLLERR)

    def _Update(self, disconnected):
        events = self.epoll.poll(0.01)
        for fileno, event in events:
            callback = self.s2c.get(fileno, None)
            if not callback:
                continue
            s = self.c2s[callback]
            if event & select.EPOLLIN or event & select.EPOLLPRI:
                data = s.recv(4 * 1024)
                if len(data) > 0:
                    callback.OnData(data)
                else:
                    disconnected.append((callback, s))
            elif event & select.EPOLLHUP or event & select.EPOLLERR:
                disconnected.append((callback, s))

    def _DisconnectSocket(self, s):
        self.epoll.unregister(s.fileno())


class SimpleSocketPoller(Poller):
    #def __init__(self, address):
    #    super(SimpleSocketPoller, self).__init__(address)

    def GetStatus(self):
        return {
            'type': 'simple',
            's2c': len(self.s2c),
            'c2s': len(self.c2s),
        }

    def _Register(self, s):
        pass

    def _Update(self, disconnected):
        for callback, s in self.c2s.items():
            try:
                data = s.recv(4 * 1024)
                if len(data) == 0:
                    disconnected.append((callback, s))
                else:
                    callback.OnData(data)
            except socket.error, e:
                if e.errno != errno.EWOULDBLOCK:
                    disconnected.append((callback, s))

    def _DisconnectSocket(self, s):
        pass


class FloodControl(object):
    "Performs flood control for the context and hold flood control values foor it."

    # -----------------------------------------
    def __init__(self, options):
        self.options = options
        self.floodLevel = 0
        self.lastMessageTime = 0   # time.time() of the last message
        self.muteBeginTime = 0
        self.muteEndTime = 0   # when the last mute period ends and the amnesty period begins
        self.isFlooder = False
        self.messageWeight = chat_cfg.flood_message_weight
        self.unweightRate = options['unweight_rate']
        self.lastMute = options['mute_time']    # mute length of the last flood mute (to increase if too often)
        #self.lastAmnesty = options['amnesty_time']

    # -----------------------------------------
    def updateFloodLevel(self, context, text):
        # Also control amnesty period and 'message when muted' penalty,
        # return True if already muted
        tm = time.time()
        if self.isFlooder:
            if tm  < self.muteEndTime:
                if chat_cfg.flood_penalty > 0:
                    penalty = self.lastMute * chat_cfg.flood_penalty
                    self.lastMute += penalty
                    self.muteEndTime += penalty
                    context.mute(self.muteEndTime, self.options['name'])
                    #debug("[FloodControl] updateFloodLevel: a message during mute, mute time increased by %s", penalty)
                return True
            elif tm - self.muteEndTime >= self.options['amnesty_time']: # this time counts after a mute ends
                # was marked as a flooder, but the amnesty period has passed
                self.messageWeight = chat_cfg.flood_message_weight
                self.unweightRate = self.options['unweight_rate']
                self.lastMute = self.options['mute_time']
                #self.lastAmnesty = self.options['amnesty_time']
                self.isFlooder = False
        weight = self.messageWeight
        if len(text) > chat_cfg.flood_max_length:
            weight *= float(len(text)) / chat_cfg.flood_max_length
        #debug("[FloodControl] updateFloodLevel: message len %s, weight %s", len(text), weight)
        self.floodLevel = max(0, (self.floodLevel - (tm - self.lastMessageTime) * self.unweightRate)) + weight
        self.lastMessageTime = tm
        return False

    # -----------------------------------------
    def checkFlood(self, context, text):
        if self.updateFloodLevel(context, text):
            return True
        #debug("[FloodControl] checkFoold: user %s, flood level [%s] = %s", context.nickname, self.options['name'], self.floodLevel)
        # here self.lastMessageTime holds the current time.time() value
        if self.floodLevel >= self.options['weight_limit']:
            if self.isFlooder:
                self.lastMute *= self.options['mute_increase']
                #self.lastAmnesty *= self.flood_mute_increase
                self.messageWeight *= chat_cfg.flood_weight_increase
                self.unweightRate /= chat_cfg.flood_unweight_slower
            self.lastFloodEventTime = self.lastMessageTime
            self.isFlooder = True
            self.muteEndTime = self.lastMessageTime + self.lastMute
            context.mute(self.muteEndTime, self.options['name'])
            self.floodLevel = 0
            #debug("[ChatContext] checkFoold: mute %s until %s", context.nickname, time.strftime("%Y.%m.%d %X", time.localtime(self.muteEndTime)))
            context.wasMuted = True
        return False



class ChatContext(object):
    def __init__(self, poller, nickname, key, realName, registerContext=None, globalChannels=None):
        self.globalChannels = globalChannels if globalChannels else []
        self.poller = poller
        self.nickname = nickname
        self.key = key
        self.realName = realName
        self.cache = ''
        self.readbuffer = ''
        self.mode = DISCONNECTED
        self.request = None
        self.registerContext = registerContext
        self.registerCommands = []
        self.postJoinCommands = []
        self.nextConnectTime = 0
        self.mutetime = [] # heapq of pairs [mutetime, channel], not containing permanents (mutetime == 0)
        self.muted = {}
        self.wasMuted = False # indicates that FloodSontrol has set a new mute
        #self.isMuted = False
        self.isNull = False
        self.isAdmin = False
        self.cmds = Queue.Queue()
        self.commands = ''
        self.lastPingTime = self.getTime()
        self.locale = ''

        # здесь будут timestamp-ы последних исполненных команд
        # - для работы с группами // self.timestamps.get(groupname)
        # - или статусами // self.timestamps.get("mute")
        # если новая приходящая команда имеет более древний timestamp, чем уже исполненная -- игнорируем ее
        # (чтобы подпереть перепутывание порядка HTTP-пакетов типа PART/JOIN, MUTE/UNMUTE)
        self.timestamps = {}
        #self.queue = queue # never used!
        self.groups = []
        # --- flood control attributes
        if needFloodConrol(nickname):
            self.floodControls = dict ((opt['name'], FloodControl(opt)) for opt in chat_cfg.flood_control_groups)
            self.muteGroups = dict((name, set()) for name in self.floodControls.iterkeys())
        else:
            self.floodControls = None
            self.muteGroups = {}
        self.muteGroups[ADMIN_MUTE] = set()
        #debug("ChatContext: nick %s, mute groups %r", self.nickname, self.muteGroups)

    # -----------------------------------------
    def GetId(self):
        return self.nickname

    # -----------------------------------------
    def Nullify(self):
        self.isNull = True

    # -----------------------------------------
    def checkTimestamp(self, cmdkey, timestamp):
        return timestamp > self.timestamps.get(cmdkey, 0)

    # -----------------------------------------
    def setTimestamp(self, cmdkey, timestamp):
        self.timestamps[cmdkey] = timestamp

    # -----------------------------------------
    def disconnect(self):
        if self.mode != DISCONNECTED:
            self.poller.Unregister(self)

    # -----------------------------------------
    def OnDisconnect(self, connectionLost):
        self.mode = DISCONNECTED
        if connectionLost:
            self.nextConnectTime = self.getTime() + RECONNECT_PAUSE
        else:
            self.cache = ''

    # -----------------------------------------
    def doGroupAction(self, group, timestamp, isRemove):
        if self.registerContext:
            self.setTimestamp(group, timestamp)
            if isRemove:
                if group in self.groups:
                    self.groups.remove(group)
                    self._muteGroupsRemove('#'+group)
            else:
                if group not in self.groups:
                    self.groups.append(group)
                    self._muteGroupsAdd('#'+group)
            if self.mode == CONNECTED:
                action = 'SAPART' if isRemove else 'SAJOIN'
                #debug("doGroupAction: %s %s #%s", action, self.nickname, group)
                self.registerContext.enqueue('%s %s #%s' % (action, self.nickname, group), True)
                if not isRemove:
                    self.registerContext.enqueue('SAMODE #%s +u' % (group,), True)
            return True
        return False

    def doGlobalGroupsAction(self, auid, timestamp, isRemove):
        if not self.registerContext:
            return ('admin context not found', CHAT_ADMIN_CONTEXT_NOT_FOUND)
        for channelName in self.globalChannels:
            if self.checkTimestamp(channelName, timestamp):
                info("timestamp check ok for nick=%s, group name=%s, timestamp=%5.4f" % (self.nickname, channelName, timestamp))
                self.setTimestamp(channelName, timestamp)
                #FIXME no check if such group is joined or parted now!
                self.registerContext.enqueue(('SAPART %s %s' if isRemove else 'SAJOIN %s %s') % (self.nickname, channelName))
                if isRemove:
                    self._muteGroupsRemove(channelName)
                else:
                    self._muteGroupsAdd(channelName)
            else:
                return ("timestamp check failed for auid=%s, group name=%s, timestamp=%5.4f" % (auid, channelName, timestamp),
                        CHAT_TIMESTAMP_CHECK_FAILED)
        return None

    # -----------------------------------------
    def _muteGroupsAdd(self, channel):
        if self.floodControls:
            group = getChannelGroup(channel)
            if group is not None:
                try:
                    self.muteGroups[group].add(channel)
                except KeyError as e:
                    error("[_muteGroupsAdd] unknown mute control group '%s'", group)
        if any(r.search(channel) for r in chat_cfg.admin_mute_channels):
            self.muteGroups[ADMIN_MUTE].add(channel)


    def _muteGroupsRemove(self, channel):
        if self.floodControls:
            group = getChannelGroup(channel)
            if group is not None:
                try:
                    self.muteGroups[group].discard(channel)
                except KeyError as e:
                    error("[_muteGroupsAdd] unknown mute control group '%s'", group)
        self.muteGroups[ADMIN_MUTE].discard(channel)

    # -----------------------------------------
    def reconnect(self):
        if self.mode != DISCONNECTED:
            self.disconnect()
            self.nextConnectTime = self.getTime() + RECONNECT_PAUSE

    # -----------------------------------------
    def isActive(self):
        return self.mode != DISCONNECTED

    # -----------------------------------------
    def isConnecting(self):
        return self.mode == CONNECTING

    # -----------------------------------------
    def mute(self, mutetime, channel):
        # mutetime here is the end time of mute or 0 for permanent,
        # so substitute 0 to MUTE_PERM
        if mutetime == 0:
            mutetime = MUTE_PERM
        if channel == ADMIN_MUTE:
            info("mute(%s, ADMIN_MUTE) for %s", mutetime, self.nickname)
        old = self.muted.get(channel, None)
        # PF-98200 replace (0 < old < mutetime) <-> (mutetime > 0)
        if old is None or (mutetime == MUTE_PERM) or (mutetime > 0):
            self.muted[channel] = mutetime
            if old: # should be pretty rare occasion: changing time of already existed mute
                # if we set permanent mute, it should override all other timed mutes
                if mutetime == MUTE_PERM:
                    while self.mutetime:
                        heapq.heappop(self.mutetime)
                else:
                    self.setNewMuteTime(channel, mutetime)
                # if self.mutetime <= 0, it's heapq item will be removed on the next _updateMutes()
            else: # None or 0
                if mutetime > 0:
                    heapq.heappush(self.mutetime, [mutetime, channel])
        if channel == ADMIN_MUTE and chat_cfg.long_polling_enabled and self.request:
            self.Ping(self.request, chat_cfg.long_polling_enabled)

    # -----------------------------------------
    def unmute(self, channel):
        mtime = None
        if channel == ADMIN_MUTE:
            if ADMIN_MUTE in self.muted:
                mtime = self.muted[ADMIN_MUTE]
                self.muted[ADMIN_MUTE] = 0
        else:
            mtime = self.muted.pop(channel, 0)
        if mtime:
            self.setNewMuteTime(channel, 0)
            # set 0 to self.mutetime's record only, to make it cleared on the next _updateMutes()
        if channel == ADMIN_MUTE and chat_cfg.long_polling_enabled and self.request:
            self.Ping(self.request, chat_cfg.long_polling_enabled)

    # -----------------------------------------
    def setNewMuteTime(self, channel, mtime):
        debug("setNewMuteTime: '%s', %s", channel, mtime)
        try:
            next(m for m in self.mutetime if m[1] == channel)[0] = mtime
            heapq.heapify(self.mutetime)
        except StopIteration:
            pass

    # -----------------------------------------
    def _updateMutes(self):
        #debug("[_updateMutes] for %s", self.nickname)
        now = time.time() + 1e-3
        while self.mutetime and self.mutetime[0][0] < now:
            item = heapq.heappop(self.mutetime)
            if item[1] == ADMIN_MUTE and self.muted[ADMIN_MUTE] != MUTE_PERM:
                self.muted[ADMIN_MUTE] = 0
            else:
                self.muted.pop(item[1], None) # existence isn't guaranteed, see mute() and unmute()
            #debug("Unmuted %r for %s", item, self.nickname)

    # -----------------------------------------
    def connect(self, registerCommands=None):
        if not registerCommands:
            registerCommands = []
        if self.isActive():
            self.disconnect()
        self.registerCommands = registerCommands
        self.nextConnectTime = self.getTime()
        self.lastPingTime = self.getTime()

    # -----------------------------------------
    def _connect(self):
        self.poller.Register(self)

    # -----------------------------------------
    def OnConnect(self):
        self.mode = CONNECTING
        self.enqueue("NICK %s" % self.nickname)
        self.enqueue("USER %s 0 * :%s" % (self.nickname, self.realName))

    # -----------------------------------------
    def getTime(self):
        t = datetime.datetime.now()
        return time.mktime(t.timetuple())

    # -----------------------------------------
    def OnData(self, data):
        debug('data recieved (nick=%s null=%d data=%s)', self.nickname, self.isNull, data)
        self.readbuffer += data
        index = self.readbuffer.rfind('\n')
        if index >= 0:
            newLines = self.readbuffer[:index + 1]
            self.readbuffer = self.readbuffer[index + 1:]
            self.cache += newLines

            lines = string.split(newLines, "\n")
            for line in lines:
                line = string.rstrip(line)
                if line:
                    if self.mode == CONNECTING and 'are supported by this server' in line:
                        self.mode = CONNECTED
                        self._register()
                    #elif self.mode == CONNECTED and self.isAdmin and line.startswith(':AdminMsg'):
                    #    m = re.match(r'\:(AdminMsg\d+)\!\S+\sJOIN \:(\#\w+)', line)
                    #    if m:
                    #        nick = m.group(1)
                    #        channel = m.group(2)
                    #        if nick != self.nickname:
                    #            debug("%s OnData: %s joins %s", self.nickname, nick, channel)
                    #            self.registerContext.enqueue('SAMODE %s +o %s' % (channel, nick))
                    else:
                        tokens = string.split(line)
                        if "PING" == tokens[0]:
                            self.enqueue("PONG %s" % tokens[1], False, False)
                            # ? don't we need to remove this line from newLines ?
        if self.isNull:
            self.cache = ''
        if chat_cfg.long_polling_enabled and len(self.cache) > 0 and self.request:
            debug('pushing data to lp request (nick=%s data=%r)' % (self.nickname, self.cache))
            self.Ping(self.request, chat_cfg.long_polling_enabled)

    # -----------------------------------------
    def update(self):
        ts = self.getTime()

        if self.mode == DISCONNECTED:
            if ts >= self.nextConnectTime:
                self._connect()
                self.nextConnectTime = ts + NEXT_RECONNECT_PAUSE
            return False
        elif not self.isNull and ts - self.lastPingTime > 120.0:
            self.disconnect()
            self.nextConnectTime = ts + 3600 * 24 * 30
            return False

        if self.mutetime:
            self._updateMutes()
        if not self.cmds.empty():
            self._push()
        return True

        # -----------------------------------------

    def _register(self):
        #debug("_register %s:", self.nickname)
        context = self.registerContext
        if not context:
            context = self
        for cmd in self.registerCommands:
            context.enqueue(cmd)
        for globalChannelName in self.globalChannels:
            context.enqueue('SAJOIN %s %s' % (self.nickname, globalChannelName))
            context.enqueue('SAMODE %s +u' % (globalChannelName,))
            self._muteGroupsAdd(globalChannelName)
        for group in self.groups:
            group = '#' + group
            context.enqueue('SAJOIN %s %s' % (self.nickname, group))
            context.enqueue('SAMODE %s +u' % (group,))
            self._muteGroupsAdd(group)
        for cmd in self.postJoinCommands:
            context.enqueue(cmd)

    # -----------------------------------------
    def matchKey(self, key):
        return self.key == key

    # -----------------------------------------
    def Send(self, auid, commands):
        if commands:
            info('recieved from user (auid=%s commands=%r)' % (auid, commands))
        if commands.startswith('PRIVMSG') or commands.startswith('WHOIS') or commands.startswith('WHOWAS'):
            if commands.find('\r') >= 0 or commands.find('\n') >= 0:
                commands = None
        else:
            commands = None
        if commands:
            self.enqueue(commands, True)
        return commands is not None

    # -----------------------------------------
    def OnConnectionClose(self):
        if chat_cfg.long_polling_enabled:
            self.request = None # forget old request

    # -----------------------------------------
    def Ping(self, request, isLongPolled):
        if isLongPolled:
            self.request = request # forget old request
        self.lastPingTime = self.getTime()
        haveContent = (len(self.cache) > 0)
        clearContent = False
        if haveContent:
            request.response['chat'] = base64.b64encode(self.cache)
            request.response['ok'] = 1
        #debug("respond for Ping: self.muted = %r", self.muted)
        if haveContent or self.muted or (not isLongPolled):
            if self.muted:
                self.muteResponse(request)
                request.response['ok'] = 1
            try:
                debug("Response: %r", request.response)
                request.fin()
                clearContent = True
            except Exception, e:
                if isLongPolled:
                    self.request = None # request was reset
        if clearContent:
            self.cache = ''
            self.request = None #? arilou: Is it OK ?

            # -----------------------------------------

    def enqueue(self, command, forcePush=False, logSending=True):
        self.cmds.put((command, logSending))
        if forcePush:
            self._push()

    # -----------------------------------------
    def _push(self):
        if self.mode == CONNECTED or self.mode == CONNECTING:
            while not self.cmds.empty():
                cmd, logSending = self.cmds.get()
                if logSending:
                    info('send to irc (commands=%r)' % cmd)
                self.commands += cmd
                if self.commands[-1] != '\n':
                    self.commands += '\r\n'
            if len(self.commands) > 0:
                sentBytes = self.poller.Send(self, self.commands)
                if sentBytes < len(self.commands):
                    self.commands = self.commands[sentBytes:]
                else:
                    self.commands = ''

    # -----------------------------------------
    def checkMute(self, msgHeader, text):
        channel = extractChannel(msgHeader)
        if channel is None:
            error("[ChatContext] checkMute: no channel/user name found in comand '%s', #global used as default", msgHeader)
            channel = '#global'
        am = self.muted.get(ADMIN_MUTE, None)
        if am is not None and channel in self.muteGroups[ADMIN_MUTE] and (am == MUTE_PERM or am > time.time()):
            return True
        if not self.floodControls:
            return False
        group = getChannelGroup(channel)
        if not group:
            return False
        return self.floodControls[group].checkFlood(self, text)

    # -----------------------------------------
    def muteResponse(self, request):
        self._updateMutes()
        now = time.time()
        if ADMIN_MUTE in self.muted:
            # amute - a list of moderator muted channels
            request.response['amute'] = tuple(c for c in self.muteGroups[ADMIN_MUTE])
            mtime = self.muted[ADMIN_MUTE]
            # amtime - a remaining mute length or -1 for permanent
            request.response['amtime'] = max(0, mtime - now) if mtime >= 0 else MUTE_PERM
            if mtime == 0:
                del self.muted[ADMIN_MUTE]
        request.response['mutes'] = dict(
            (channel[1:], (MUTE_PERM if mtime == MUTE_PERM else max(0, mtime - now)))
            for group, mtime in self.muted.iteritems() if group != ADMIN_MUTE and (mtime == 0 or mtime > now)
            for channel in self.muteGroups[group])
        #debug("[muteResponse] res: %r", request.response)


##---------------------------------------------------------------------------------------------------
class PingAction(SubAction):
    action = "ping"

    # -----------------------------------------
    def onStart(self):
        auid = self.getParam("auid")
        if chat_cfg.long_polling_enabled:
            return self.fail('ping action disabled, use lping protocol (auid=%s)' % auid, CHAT_DEPRECATED_PROTOCOL)

        self.response['ec'] = OK
        key = self.getParam("key")
        _commands = self.getParam("chat")
        context = self.I.WS.getContext(auid)
        if context:
            if not context.isActive():
                if not context.isConnecting():
                    context.connect()
                return self.fail('not connected (auid=%s)' % auid, CHAT_NOT_CONNECTED)
            elif context.matchKey(key):
                unpacked = base64.b64decode(_commands)
                context.Send(auid, unpacked)
                context.Ping(self, chat_cfg.long_polling_enabled)
                return
            else:
                return self.fail('mismatched key (auid=%s key=%s)' % (auid, key), CHAT_MISMATCHED_KEY)
        else:
            return self.fail('no context found (auid=%s)' % auid, CHAT_CONTEXT_NOT_FOUND)

##---------------------------------------------------------------------------------------------------
class LongPingAction(SubAction):
    action = "lping"

    # -----------------------------------------
    def onStart(self):
        auid = self.getParam("auid")
        if not chat_cfg.long_polling_enabled:
            return self.fail('lping action disabled, use ping protocol (auid=%s)' % auid, CHAT_DEPRECATED_PROTOCOL)
        self.response['ec'] = OK
        key = self.getParam("key")
        context = self.I.WS.getContext(auid)
        self.context = context
        if context:
            if not context.isActive():
                if not context.isConnecting():
                    context.connect()
                return self.fail('not connected (auid=%s)' % auid, CHAT_NOT_CONNECTED)
            elif context.matchKey(key):
                context.Ping(self, chat_cfg.long_polling_enabled)
                return
            else:
                return self.fail('mismatched key (auid=%s key=%s)' % (auid, key), CHAT_MISMATCHED_KEY)
        else:
            return self.fail('no context found (auid=%s)' % auid, CHAT_CONTEXT_NOT_FOUND)

    def onConnectionClose(self):
        if self.context:
            self.context.OnConnectionClose()
            self.context = None

## ---------------------------------------------------------------------------------------------
class ReconnectAction(SubAction):
    action = "reconnect"

    # -----------------------------------------
    def onStart(self):
        self.response['ec'] = OK
        auid = self.getParam("auid")
        key = self.getParam("key")
        commands = self.getParam("chat")
        context = self.I.WS.getContext(auid)
        if context:
            if context.matchKey(key):
                context.reconnect()
                self.response['chat'] = ''
                self.response['ok'] = 1
            else:
                return self.fail('mismatched key (auid=%s key=%s)' % (auid, key), CHAT_MISMATCHED_KEY)
        else:
            return self.fail('no context found (auid=%s)' % auid, CHAT_CONTEXT_NOT_FOUND)
        self.fin()

## ---------------------------------------------------------------------------------------------
class SendAction(SubAction):
    action = "send"

    # -----------------------------------------
    def onStart(self):
        auid = self.getParam("auid")
        if not chat_cfg.long_polling_enabled:
            return self.fail('ping action disabled, use lping protocol (auid=%s)' % auid, CHAT_DEPRECATED_PROTOCOL)

        self.response['ec'] = OK
        key = self.getParam("key")
        _commands = self.getParam("chat")
        context = self.I.WS.getContext(auid)
        if context:
            if not context.isActive():
                if not context.isConnecting():
                    context.connect()
                return self.fail('not connected (auid=%s)' % auid, CHAT_NOT_CONNECTED)
            elif context.matchKey(key):
                if _commands:
                    unpacked = base64.b64decode(_commands)
                    if unpacked.startswith('PRIVMSG'): # PRIVMSG text is a subject of flood-checking
                        msgStart = unpacked.find(':')
                        if msgStart >= 0: #-- PF-86843: no CleanSpeak more, but floodfilter is still in use
                            header = unpacked[:(msgStart + 1)]
                            text = unpacked[(msgStart + 1):].decode('utf8')
                            #-- PF-86843
                            #-- if '\t' in text: # \t is used in onFilter as filtered and unfiltered parts delimiter
                                #-- text = text.replace('\t',' ')
                            if context.checkMute(header, text):
                                context.muteResponse(self)
                                return self.fin()
                            if context.wasMuted: # was auto-muted by checkMute() call
                                context.muteResponse(self)
                                # and go ahead - let the message be sent

                            #-- NO MORE CleanSpeak calls!  PF-86843
                            #-- _callback = functools.partial(self.onFilter, context=context, header=header, orig=text, auid=auid)
                            #-- info("to filter: %r" % text)
                            #-- filter_locales = self.I.WS.getFilterLocales( context.locale )
                            #-- return self.I.FILTER.filterText(text, filter_locales, _callback)
                    #else:
                        # прочие команды фильтровать не надо
                        #return self.onFilter(unpacked, context=context, auid=auid)
                    if context.Send(auid, unpacked):
                        self.response["ftext"] = _commands
                        return self.fin()
                    else:
                        return self.fail('send failed (auid=%s)' % auid, CHAT_SEND_FAILED)
                else:
                    return self.fail('bad commands (auid=%s commands=%s)' % (auid, _commands), CHAT_EMPTY_MESSAGE)
            else:
                return self.fail('mismatched key (auid=%s key=%s)' % (auid, key), CHAT_MISMATCHED_KEY)
        else:
            return self.fail('no context found (auid=%s)' % auid, CHAT_CONTEXT_NOT_FOUND)

    # -----------------------------------------
    def onFilter(self, filtered_text, context=None, header="", orig=None, auid=0):
        commands = header + utf8convert(filtered_text)
        if orig is not None and orig != filtered_text:
            commands += '\t' + utf8convert(orig)
        if context.Send(auid, commands):
            self.response["ftext"] = base64.b64encode(commands)
            return self.fin()
        else:
            return self.fail('send failed (auid=%s)' % auid, CHAT_SEND_FAILED)


## ---------------------------------------------------------------------------------------------
class CheckAction(SubAction):
    action = "check"

    # -----------------------------------------
    def onStart(self):
        auid = self.getParam("auid")
        if not chat_cfg.long_polling_enabled:
            return self.fail('lping action disabled, use ping protocol (auid=%s)' % auid, CHAT_DEPRECATED_PROTOCOL)
        self.response['ec'] = OK
        key = self.getParam("key")
        context = self.I.WS.getContext(auid)
        if context:
            if context.matchKey(key):
                self.response['ok'] = 1
                if context.muted:
                    context.muteResponse(self)
            else:
                return self.fail('mismatched key (auid=%s key=%s)' % (auid, key), CHAT_MISMATCHED_KEY)
        else:
            return self.fail('no context found (auid=%s)' % auid, CHAT_CONTEXT_NOT_FOUND)
        self.fin()

## ---------------------------------------------------------------------------------------------
class ExternalChatHandler(JsonHandler):
    internalActionMap = {
        'ping': PingAction,
        'reconnect': ReconnectAction,
        'lping': LongPingAction,
        'check': CheckAction,
        'send': SendAction,
    }


def getIrcNickname(auid):
    return 'U' + auid


fractions = ['0', '1']
locales = getattr(chat_cfg, "chat_locales", ["RU"])


def getPublicChannelName(name, fraction, locale, useFraction=True, useLocales=True):
    if useFraction and useLocales:
        #assert fraction in fractions
        return '#'+ name + str(locale) + str(fraction)
    elif useFraction and useLocales==False:
        #assert fraction in fractions
        return '#'+ name + str(fraction)
    elif useFraction==False and useLocales==True:
        return '#'+ name + str(locale)
    #useFraction=False,useLocales=False
    else:
        return '#'+name

def getGlobalChannelName(fraction, locale, useFraction=True, useLocales=True):
    return getPublicChannelName('global', fraction, locale, useFraction, useLocales)

def isFactionsSeparated():
    return getattr(chat_cfg, 'separate_factions', False)

def isLocalesSeparated():
    return getattr(chat_cfg, 'separate_locales', False)

class InternalChatHandler(JsonHandler):
    internalActionMap = {
        'broadcast': 'onBroadcast',
        'msg': 'onMsg',
        'add_user': 'onAddUser',
        'add_user_group': 'onAddUserToGroup',
        'remove_user_group': 'onRemoveUserFromGroup',
        'add_user_global': 'onAddUserGlobal', # add user to all global chats available for him
        'remove_user_global': 'onRemoveUserGlobal', # remove user from all global chats
        'check_alive': 'onCheckWebServerAlive', # base JsonHandler: проверяем, жив ли сервер
        'remove_user': 'onRemoveUser',
        'mute_user': 'onMuteUser',
        'unmute_user': 'onUnmuteUser',
        'getstatus': 'onGetStatus',
    }

    def onGetStatus(self):
        self.response['status'] = self.I.WS.getStatus()
        self.response['ok'] = 1
        self.fin()

    # -----------------------------------------
    def onAddUser(self):
        auid = self.getParam("auid")
        if auid is None:
            return self.fail('param not defined (name=auid)', BAD_PARAM)
        realName = self.getParam("nickname")
        if realName is None:
            return self.fail('param not defined (name=nickname)', BAD_PARAM)
        fraction = self.getParam("fraction")
        if fraction not in fractions:
            return self.fail('fraction wrong value (value=%s)' % fraction, BAD_PARAM)
        locale = self.getParam("locale")
        if locale not in locales:
            return self.fail('locale wrong value (value=%s)' % locale, BAD_PARAM)
        key = self.getParam("key")
        muted = self.getIntParam("muted")
        mutetime = self.getFloatParam("mutetime")
        #debug("onAddUser: auid %s, key %s, nick %s, faction %s, locale %s, MUTED %s, time %s",
        #      auid, key, realName, fraction, locale, muted, mutetime)
        if key != None:
            info('connecting user (auid=%s key=%s nickname=%r fraction=%s muted=%d mutetime=%f)' % (
                auid, key, realName, fraction, muted, mutetime))
            context = self.I.WS.getContext(auid)
            if not context:
                globalChannelName = getGlobalChannelName(fraction, locale, isFactionsSeparated(), isLocalesSeparated())
                lfgChannelName = getPublicChannelName('lfg', fraction, locale, isFactionsSeparated(), isLocalesSeparated())
                context = self.I.WS.createContext(auid, key, realName, [globalChannelName, lfgChannelName])
            if context:
                context.locale = locale
                if muted:
                    context.mute(mutetime, ADMIN_MUTE)
                context.connect()
                self.response['ok'] = 1
                self.response['host'] = options.server_name
                self.response['key'] = key
            else:
                return self.fail('context creation failed', CHAT_CONTEXT_CREATION_FAILED)
        else:
            return self.fail('param not defined (name=key)', BAD_PARAM)
        self.fin()

    # -----------------------------------------
    def onBroadcast(self):
        context = self.I.WS.getBroadcastContext()
        if context:
            message = self.getParam("message")
            dstLocale = self.getParam("locale", None)
            if message:
                sentCount = 0
                for locale in locales:
                    if not isLocalesSeparated():
                        locale=dstLocale=""
                    if dstLocale is None or locale == dstLocale:
                        if not isFactionsSeparated():
                            context.enqueue('PRIVMSG %s :' % getGlobalChannelName(None, locale, False, isLocalesSeparated()) + message, True)
                            sentCount += 1
                            if not locale: # send 1 for all
                                break
                        else:
                            for fraction in fractions:
                                context.enqueue('PRIVMSG %s :' % getGlobalChannelName(fraction, locale, True, isLocalesSeparated()) + message, True)
                                sentCount += 1
                if sentCount > 0:
                    self.response['ok'] = 1
                else:
                    return self.fail('unknown locale %r, message skipped' % dstLocale, CHAT_SEND_FAILED)
            else:
                return self.fail('empty message', CHAT_EMPTY_MESSAGE)
        else:
            return self.fail('admin context not found', CHAT_ADMIN_CONTEXT_NOT_FOUND)
        self.fin()

    # -----------------------------------------
    def onMsg(self):
        context = self.I.WS.getBroadcastContext()
        if context:
            title = self.getParam("title")
            text = self.getParam("text")
            auid = self.getParam("auid")
            if auid != None and title != None and text != None:
                # context.enqueue('PRIVMSG %s :' % getIrcNickname(auid) + base64.urlsafe_b64decode(title) + ': '+base64.urlsafe_b64decode(text), True)
                context.enqueue('PRIVMSG %s :' % getIrcNickname(auid) + ' ' + base64.urlsafe_b64decode(text),
                                True) # не нужно title, PF-40779
            self.response['ok'] = 1
        else:
            return self.fail('admin context not found', CHAT_ADMIN_CONTEXT_NOT_FOUND)
        self.fin()

    # -----------------------------------------
    def doGroupAction(self, isRemove):
        auid = self.getParam("auid")
        group = self.getParam("group")
        timestamp = self.getFloatParam("timestamp")
        if auid is None:
            return self.fail('param not defined (name=auid)', BAD_PARAM)
        if group is None:
            return self.fail('param not defined (name=group)', BAD_PARAM)
        usercontext = self.I.WS.getContext(auid)
        if not usercontext:
            return self.fail('user context not found', CHAT_CONTEXT_NOT_FOUND)

        if usercontext.checkTimestamp(group, timestamp):
            info("timestamp check ok for auid=%s, group name=%s, timestamp=%5.4f" % (auid, group, timestamp))
            if usercontext.doGroupAction(group, timestamp, isRemove):
                self.response['ok'] = 1
            else:
                return self.fail('admin context not found', CHAT_ADMIN_CONTEXT_NOT_FOUND)
        else:
            return self.fail("timestamp check failed for auid=%s, group name=%s, timestamp=%5.4f" % (auid, group, timestamp),
                             CHAT_TIMESTAMP_CHECK_FAILED)
        self.fin()

    # -----------------------------------------
    def doGlobalGroupsAction(self, isRemove):
        auid = self.getParam("auid")
        if auid is None:
            return self.fail('param not defined (name=auid)', BAD_PARAM)
        timestamp = self.getFloatParam("timestamp")
        usercontext = self.I.WS.getContext(auid)
        if not usercontext:
            return self.fail('user context not found', CHAT_CONTEXT_NOT_FOUND)

        res = usercontext.doGlobalGroupsAction(auid, timestamp, isRemove)
        if res:
            return self.fail(*res)
        self.response['ok'] = 1
        self.fin()

    # -----------------------------------------
    def onRemoveUserFromGroup(self):
        self.doGroupAction(True)

    # -----------------------------------------
    def onAddUserToGroup(self):
        self.doGroupAction(False)

    # -----------------------------------------
    def onAddUserGlobal(self):
        self.doGlobalGroupsAction(False)

    # -----------------------------------------
    def onRemoveUserGlobal(self):
        self.doGlobalGroupsAction(True)

    # -----------------------------------------
    def onRemoveUser(self):
        auid = self.getParam("auid")
        if auid != None:
            if self.I.WS.removeContext(auid):
                self.response['ok'] = 1
            else:
                return self.fail('context not found (auid=%s)' % auid, CHAT_CONTEXT_NOT_FOUND)
        else:
            return self.fail('context not specified', CHAT_CONTEXT_NOT_SPECIFIED)
        self.fin()

    # -----------------------------------------
    def onMuteUser(self):
        auid = self.getParam("auid")
        mutetime = self.getFloatParam("mutetime")
        muted = self.getIntParam("muted")
        #debug("onMuteUser: auid %s, mutetime %s, muted %s", auid, mutetime, muted)
        if auid != None:
            context = self.I.WS.getContext(auid)
            if context:
                context.mute(mutetime, ADMIN_MUTE)
                self.response['ok'] = 1
            else:
                return self.fail('context not found (auid=%s)' % auid, CHAT_CONTEXT_NOT_FOUND)
        else:
            return self.fail('context not specified', CHAT_CONTEXT_NOT_SPECIFIED)
        self.fin()

    # -----------------------------------------
    def onUnmuteUser(self):
        auid = self.getParam("auid")
        #debug("onUnmuteUser: auid %s", auid )
        if auid != None:
            context = self.I.WS.getContext(auid)
            if context:
                context.unmute(ADMIN_MUTE)
                self.response['ok'] = 1
            else:
                return self.fail('context not found (auid=%s)' % auid, CHAT_CONTEXT_NOT_FOUND)
        else:
            return self.fail('context not specified', CHAT_CONTEXT_NOT_SPECIFIED)
        self.fin()

##---------------------------------------------------------------------------------------------------
class ChatService(ITornadoServer):
    def __init__(self, **kwargs):
        super(ChatService, self).__init__(**kwargs)
        irc_poll_connect = getattr(chat_cfg, "irc_poll_connect", [])
        if options.server_id and len(irc_poll_connect) > 1:
            chat_cfg.irc_host, chat_cfg.irc_port = irc_poll_connect[options.server_id % 2]
        self.address = (chat_cfg.irc_host, chat_cfg.irc_port)

        info('Using irc_poll_connect irc_host[%r] irc_port=[%r] irc_poll_connect[%r])' % (chat_cfg.irc_host, chat_cfg.irc_port, irc_poll_connect))

        pollFreq = getattr(chat_cfg, "poll_freq", 1)
        self.TICK_PERIOD = float(pollFreq)
        pollType = getattr(chat_cfg, "poll", 'simple')

        self.poller = None
        if pollType not in ['epoll', 'simple']:
            error('Unexpected poll type (name=%r)' % pollType)
        else:
            if pollType == 'epoll':
                try:
                    self.poller = EPollPoller(self.address)
                except:
                    error('Poll type "epoll" not supported, reverting to "simple"')
                    pollType = 'simple'
            if pollType == 'simple':
                self.poller = SimpleSocketPoller(self.address)
        if self.poller:
            info('Using poll type (name=%r freq=%f)' % (pollType, pollFreq))

        #self.contextsQueue = [] # never used!

        self.filter_locales = getattr( chat_cfg, "filter_locales", {} )

        self.adminContext = ChatContext(self.poller, 'Admin' + str(id(self)), 'BAADF00D', "Administrator")
        operName = getattr(chat_cfg, "oper_name", None)
        operPassword = getattr(chat_cfg, "oper_password", None)
        if operName != None and operPassword != None:
            self.adminContext.connect(['OPER %s %s' % (operName, operPassword)])
        else:
            error('Oper credentials are not defined, chat administration disabled')
        broadcastNick = 'AdminMsg%s' % str(id(self))
        globalChannels = []
        for locale in locales:
            if not isLocalesSeparated():
                locale=""
            if not isFactionsSeparated():
                globalChannels.append(getGlobalChannelName(None, locale, False, isLocalesSeparated()))
            else:
                for fraction in fractions:
                    globalChannels.append(getGlobalChannelName(fraction, locale, True,isLocalesSeparated()))
            if not locale:
                break

        self.broadcastContext = ChatContext(
            self.poller, broadcastNick, 'BAADBEEF', "Administrator", self.adminContext, globalChannels)
        self.broadcastContext.isAdmin = True
        for channel in globalChannels:
            self.broadcastContext.postJoinCommands.append('SAMODE %s +w o:AdminMsg*!AdminMsg*@*' % channel)
        #    self.broadcastContext.postJoinCommands.append('SAMODE %s +m' % channel)

        self.adminContext.Nullify()
        self.broadcastContext.Nullify()

        self.broadcastContext.connect()
        self.contexts = {'admin': self.adminContext, 'adminMsg': self.broadcastContext} # [auid] -> ChatContext

    # -----------------------------------------------
    def createContext(self, auid, key, nickname, globalChannels):
        info('create context for user (auid=%s key=%s nickname=%r channels=%r)' % (auid, key, nickname, globalChannels))
        ircNickname = getIrcNickname(auid)
        context = ChatContext(self.poller, ircNickname, key, nickname, self.adminContext, globalChannels)
        if auid in self.contexts:
            error('duplicate auid found (auid=%s)' % auid)
            # drop the old one, but keep it's flood control data
            context.floodControls = self.contexts[auid].floodControls
        self.contexts[auid] = context
        return context

    # -----------------------------------------------
    def removeContext(self, auid):
        context = self.contexts.get(auid, None)
        if context:
            info('disconnecting user (auid=%s)' % auid)
            context.disconnect()
            del self.contexts[auid]
            return True
        else:
            return False

    def getStatus(self):
        return {
            'ctxs': len(self.contexts),
            'poll': self.poller.GetStatus(),
        }

    # -----------------------------------------------
    def getContext(self, auid):
        return self.contexts.get(auid, None)

    # -----------------------------------------------
    def getAdminContext(self):
        return self.adminContext

    # -----------------------------------------------
    def getBroadcastContext(self):
        return self.broadcastContext

    # -----------------------------------------------
    def getFilterLocales(self, locale):
        default_filter_locales = [ str(locale).lower() ]
        return self.filter_locales.get(locale, default_filter_locales)

    # -----------------------------------------------
    def tick(self):
        self.poller.Update()
        for context in self.contexts.values(): #TODO checl for inner deletes and, if no, use itervalues() here!
            context.update()

    # -----------------------------------------------
    def initHandlers(self, application):
        application.add_handlers(r"(.*)", [
            ( r"/x", InternalChatHandler, dict(SUBADDR=SUBADDR_INTERNAL, I=self.I) ),
            ( r"/%s" % options.server_name, ExternalChatHandler, dict(SUBADDR=SUBADDR_INTERNAL, I=self.I) ),
        ])

    # return True if startup enviroment is bad
    @staticmethod
    def checkStartupFail():
        # проверяем, не слушает ли на нашем порту кто-то еще (защита от повторного запуска координатора)
        self_addr = "127.0.0.1:" + str(options.port)
        res = httpClientRequest(addr=self_addr, server="x", params="action=check_alive&name=_chat_server_")
        if res and res.get("ok") != None:
            fatal("DUPLICATE CHAT SERVICE: already listening on " + self_addr + "\n(reply was %s)" % str(res))
            return True # обламываемся, уже запущена копия веб-сервера на этом порту
        print( "check startup environment: ok, port free (" + self_addr + ")" )

    # -----------------------------------------------
    @staticmethod
    def initOptions():
        #tornado 3.4 fix
        if options.__class__.__name__ == "OptionParser":
            options.server_class = "chat"
        else:
            options["server_class"].set("chat")


    # -----------------------------------------------
    @staticmethod
    def initInterfaces( classOf=None ):
        iDict = ClassDict()
        iDict.MD = IDataManager()
        iDict.HTTP = tornado.httpclient.AsyncHTTPClient(max_clients=coord_cfg.COORDINATOR_HTTP_CURL_WORKERS)
        #iDict.FILTER = IfaceFactory.makeChatFilterInterface(options.filter,
        #                                                    coord_cfg.COORDINATOR_CLEANSPEAK_FILTER_ADDRESS, iDict.HTTP)
        return iDict

## ---------------------------------------------------------------------------------------------
## ---------------------------------------------------------------------------------------------

def main():
    ITornadoServer.main(ChatService)


if __name__ == "__main__":
    main()


### Problems found:
# 1. mutetime: in different places it's compared with time.time() or with ChatContext.getTime() (which is localtime, not gmtime).
# It should be fixed, but the resolution depends on what time (local or gm) is used in AddUser and MuteUser commands.
# Если верить коду в logic/mute_account.py: Mute_account.onStart() - используется именно time.time()
