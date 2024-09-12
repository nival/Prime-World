# -*- coding: utf-8 -*-
import socket
from functools import partial
from itertools import izip
import logging
import weakref
from collections import deque

from tornado.ioloop import IOLoop
from tornado.iostream import IOStream
from tornado import gen

from datetime import datetime
from exceptions import RequestError, ConnectionError, ResponseError


log = logging.getLogger('tornadoredis.client')


class Message(object):
    ''' Wrapper Message object.
        kind = command
       channel = channel from which the message was received
        pattern = subscription pattern
        body = message body
    '''
    def __init__(self, *args):
        if len(args) == 3:
            (self.kind, self.channel, self.body) = args
            self.pattern = self.channel
        elif len(args) == 4:
            (self.kind, self.pattern, self.channel, self.body) = args
        else:
            raise ValueError('Invalid number of arguments')


class CmdLine(object):
    def __init__(self, cmd, *args, **kwargs):
        self.cmd = cmd
        self.args = args
        self.kwargs = kwargs

    def __repr__(self):
        return self.cmd + '(' + str(self.args) + ',' + str(self.kwargs) + ')'


def string_keys_to_dict(key_string, callback):
    return dict([(key, callback) for key in key_string.split()])


def dict_merge(*dicts):
    merged = {}
    [merged.update(d) for d in dicts]
    return merged


def encode(value):
    if isinstance(value, str):
        return value
    elif isinstance(value, unicode):
        return value.encode('utf-8')
    # pray and hope
    return str(value)


def format_command(*tokens, **kwargs):
    cmds = []
    for t in tokens:
        e_t = encode(t)
        cmds.append('$%s\r\n%s\r\n' % (len(e_t), e_t))
    return '*%s\r\n%s' % (len(tokens), ''.join(cmds))


def format_pipeline_request(command_stack):
    return ''.join(format_command(c.cmd, *c.args, **c.kwargs) \
                   for c in command_stack)


class Connection(object):
    def __init__(self, host, port, event_handler,
                 stop_after=None, io_loop=None):
        self.host = host
        self.port = port
        self._event_handler = weakref.proxy(event_handler)
        self.timeout = stop_after
        self._stream = None
        self._io_loop = io_loop
        self.try_left = 2

        self.in_progress = False
        self.read_callbacks = []
        self.ready_callbacks = deque()

    def __del__(self):
        self.disconnect()

    def __enter__(self):
        return self

    def __exit__(self, *args, **kwargs):
        if self.ready_callbacks:
            # Pop a SINGLE callback from the queue and execute it.
            # The next one will be executed from the code
            # invoked by the callback
            callback = self.ready_callbacks.popleft()
            callback()

    def ready(self):
        return not self.read_callbacks and not self.ready_callbacks

    def wait_until_ready(self, callback=None):
        if callback:
            if not self.ready():
                self.ready_callbacks.append(callback)
            else:
                callback()
        return self

    def connect(self):
        if not self._stream:
            try:
                sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM, 0)
                sock.setsockopt(socket.SOL_TCP, socket.TCP_NODELAY, 1)
                sock.settimeout(self.timeout)
                sock.connect((self.host, self.port))
                self._stream = IOStream(sock, io_loop=self._io_loop)
                self._stream.set_close_callback(self.on_stream_close)
                self.connected()
            except socket.error, e:
                raise ConnectionError(str(e))
            self.fire_event('on_connect')

    def on_stream_close(self):
        if self._stream:
            self._stream = None
            callbacks = self.read_callbacks
            self.read_callbacks = []
            for callback in callbacks:
                callback(None)

    def disconnect(self):
        if self._stream:
            s = self._stream
            self._stream = None
            try:
                s.socket.shutdown(socket.SHUT_RDWR)
                s.close()
            except socket.error:
                pass

    def fire_event(self, event):
        if self._event_handler:
            try:
                getattr(self._event_handler, event)()
            except AttributeError:
                pass

    def write(self, data, try_left=None):
        if try_left is None:
            try_left = self.try_left
        if not self._stream:
            self.connect()
            if not self._stream:
                raise ConnectionError('Tried to write to '
                                      'non-existent connection')

        if try_left > 0:
            try:
                self._stream.write(data)
            except IOError:
                self.disconnect()
                self.write(data, try_left - 1)
        else:
            raise ConnectionError('Tried to write to non-existent connection')

    def read(self, length, callback=None):
        try:
            if not self._stream:
                self.disconnect()
                raise ConnectionError('Tried to read from '
                                      'non-existent connection')
            self.read_callbacks.append(callback)
            self._stream.read_bytes(length,
                                    callback=partial(self.read_callback,
                                                     callback))
        except IOError:
            self.fire_event('on_disconnect')

    def read_callback(self, callback, *args, **kwargs):
        self.read_callbacks.remove(callback)
        callback(*args, **kwargs)

    def readline(self, callback=None):
        try:
            if not self._stream:
                self.disconnect()
                raise ConnectionError('Tried to read from '
                                      'non-existent connection')
            self.read_callbacks.append(callback)
            self._stream.read_until('\r\n',
                                    callback=partial(self.read_callback,
                                                     callback))
        except IOError:
            self.fire_event('on_disconnect')

    def connected(self):
        if self._stream:
            return True
        return False


def reply_to_bool(r, *args, **kwargs):
    return bool(r)


def make_reply_assert_msg(msg):
    def reply_assert_msg(r, *args, **kwargs):
        return r == msg
    return reply_assert_msg


def reply_set(r, *args, **kwargs):
    return set(r)


def reply_dict_from_pairs(r, *args, **kwargs):
    return dict(izip(r[::2], r[1::2]))


def reply_str(r, *args, **kwargs):
    return r or ''


def reply_int(r, *args, **kwargs):
    return int(r) if r is not None else None


def reply_float(r, *args, **kwargs):
    return float(r) if r is not None else None


def reply_datetime(r, *args, **kwargs):
    return datetime.fromtimestamp(int(r))


def reply_pubsub_message(r, *args, **kwargs):
    return Message(*r)


def reply_zset(r, *args, **kwargs):
    if (not r) or (not 'WITHSCORES' in args):
        return r
    return zip(r[::2], map(float, r[1::2]))


def reply_hmget(r, key, *fields, **kwargs):
    return dict(zip(fields, r))


def reply_info(response):
    info = {}

    def get_value(value):
        if ',' not in value:
            return value
        sub_dict = {}
        for item in value.split(','):
            k, v = item.split('=')
            try:
                sub_dict[k] = int(v)
            except ValueError:
                sub_dict[k] = v
        return sub_dict
    for line in response.splitlines():
        key, value = line.split(':')
        try:
            info[key] = int(value)
        except ValueError:
            info[key] = get_value(value)
    return info


def reply_ttl(r, *args, **kwargs):
    return r != -1 and r or None


PUB_SUB_COMMANDS = set([
    'SUBSCRIBE',
    'PSUBSCRIBE',
    'UNSUBSCRIBE',
    'PUNSUBSCRIBE',
    # Not a command at all
    'LISTEN',
])


class Client(object):
    def __init__(self, host='localhost', port=6379, password=None,
            selected_db=None, io_loop=None):
        self._io_loop = io_loop or IOLoop.instance()
        self.connection = Connection(host, port, self, io_loop=self._io_loop)
        self.current_cmd_line = None
        self.subscribed = False
        self.password = password
        self.selected_db = selected_db
        self.REPLY_MAP = dict_merge(
                string_keys_to_dict('AUTH BGREWRITEAOF BGSAVE DEL EXISTS '
                                    'EXPIRE HDEL HEXISTS '
                                    'HMSET MOVE MSET MSETNX SAVE SETNX',
                                    reply_to_bool),
                string_keys_to_dict('FLUSHALL FLUSHDB SELECT SET SETEX '
                                    'SHUTDOWN RENAME RENAMENX WATCH UNWATCH',
                                    make_reply_assert_msg('OK')),
                string_keys_to_dict('SMEMBERS SINTER SUNION SDIFF',
                                    reply_set),
                string_keys_to_dict('HGETALL BRPOP BLPOP',
                                    reply_dict_from_pairs),
                string_keys_to_dict('HGET',
                                    reply_str),
                string_keys_to_dict('SUBSCRIBE UNSUBSCRIBE LISTEN '
                                    'PSUBSCRIBE UNSUBSCRIBE',
                                    reply_pubsub_message),
                string_keys_to_dict('ZRANK ZREVRANK',
                                    reply_int),
                string_keys_to_dict('ZSCORE ZINCRBY ZCOUNT ZCARD',
                                    reply_int),
                string_keys_to_dict('ZRANGE ZRANGEBYSCORE ZREVRANGE '
                                    'ZREVRANGEBYSCORE',
                                    reply_zset),
                {'HMGET': reply_hmget},
                {'PING': make_reply_assert_msg('PONG')},
                {'LASTSAVE': reply_datetime},
                {'TTL': reply_ttl},
                {'INFO': reply_info},
                {'MULTI_PART': make_reply_assert_msg('QUEUED')},
            )

        self._pipeline = None

    def __repr__(self):
        return 'Tornadoredis client (host=%s, port=%s)' \
                % (self.connection.host, self.connection.port)

    def __enter__(self):
        return self

    def __exit__(self, *args, **kwargs):
        pass

    def pipeline(self, transactional=False):
        if not self._pipeline:
            self._pipeline = Pipeline(
                selected_db=self.selected_db,
                io_loop=self._io_loop,
                transactional=transactional
            )
            self._pipeline.connection = self.connection
        return self._pipeline

    #### connection

    def connect(self):
        self.connection.connect()

    def disconnect(self):
        self.connection.disconnect()

    def on_connect(self):
        if self.password:
            self.auth(self.password)
        if self.selected_db:
            self.select(self.selected_db)

    def on_disconnect(self):
        if self.subscribed:
            self.subscribed = False
        raise ConnectionError("Socket closed on remote end")
    ####

    #### formatting
    def encode(self, value):
        if isinstance(value, str):
            return value
        elif isinstance(value, unicode):
            return value.encode('utf-8')
        # pray and hope
        return str(value)

    def format_command(self, *tokens):
        cmds = []
        for t in tokens:
            e_t = self.encode(t)
            cmds.append('$%s\r\n%s\r\n' % (len(e_t), e_t))
        return '*%s\r\n%s' % (len(tokens), ''.join(cmds))

    def format_reply(self, cmd_line, data):
        if cmd_line.cmd not in self.REPLY_MAP:
            return data
        try:
            res = self.REPLY_MAP[cmd_line.cmd](data,
                                               *cmd_line.args,
                                               **cmd_line.kwargs)
        except Exception, e:
            raise ResponseError(
                'failed to format reply to %s, raw data: %s; err message: %s'
                % (cmd_line, data, e), cmd_line
            )
        return res
    ####

    #### new AsIO
    def call_callback(self, callback, *args, **kwargs):
        for cb in callback:
            cb(*args, **kwargs)

    @gen.engine
    def execute_command(self, cmd, *args, **kwargs):
        callback = kwargs.get('callback', None)
        del kwargs['callback']
        cmd_line = CmdLine(cmd, *args, **kwargs)
        if self.subscribed and cmd not in PUB_SUB_COMMANDS:
            callback(RequestError(
                'Calling not pub/sub command during subscribed state',
                cmd_line))
            return

        if not self.connection.connected():
            self.connection.connect()

        if not self.connection.ready() and not self.subscribed:
            yield gen.Task(self.connection.wait_until_ready)

        try:
            self.connection.write(self.format_command(cmd, *args, **kwargs))
        except Exception, e:
            self.connection.disconnect()
            raise e

        if (cmd in PUB_SUB_COMMANDS) or (self.subscribed and cmd == 'PUBLISH'):
            result = True
        else:
            with self.connection as c:
                result = None
                data = yield gen.Task(c.readline)
                if not data:
                    raise ConnectionError('no data received')
                else:
                    resp = yield gen.Task(self.process_data, data, cmd_line)
                    result = self.format_reply(cmd_line, resp)
        if callback:
            callback(result)

    @gen.engine
    def process_data(self, data, cmd_line, callback=None):
        data = data[:-2]  # strip \r\n

        if data == '$-1':
            response = None
        elif data == '*0' or data == '*-1':
            response = []
        else:
            if len(data) == 0:
                raise IOError('Disconnected')
            head, tail = data[0], data[1:]

            if head == '*':
                response = yield gen.Task(self.consume_multibulk,
                                          int(tail),
                                          cmd_line)
            elif head == '$':
                # Consume bulk reply
                response = yield gen.Task(self.connection.read, int(tail) + 2)
                if isinstance(response, Exception):
                    raise response
                if not response:
                    raise ResponseError('EmptyResponse')
                else:
                    response = response[:-2]
            elif head == '+':
                response = tail
            elif head == ':':
                response = int(tail)
            elif head == '-':
                if tail.startswith('ERR'):
                    tail = tail[4:]
                response = ResponseError(tail, cmd_line)
            else:
                raise ResponseError('Unknown response type %s' % head,
                                    cmd_line)
        callback(response)

    @gen.engine
    def consume_multibulk(self, length, cmd_line, callback=None):
        tokens = []
        while len(tokens) < length:
            data = yield gen.Task(self.connection.readline)
            if not data:
                raise ResponseError(
                    'Not enough data in response to %s, accumulated tokens: %s'
                    % (cmd_line, tokens),
                    cmd_line)
            token = yield gen.Task(self.process_data, data, cmd_line)
            tokens.append(token)

        callback(tokens)

    ### MAINTENANCE
    def bgrewriteaof(self, callback=None):
        self.execute_command('BGREWRITEAOF', callback=callback)

    def dbsize(self, callback=None):
        self.execute_command('DBSIZE', callback=callback)

    def flushall(self, callback=None):
        self.execute_command('FLUSHALL', callback=callback)

    def flushdb(self, callback=None):
        self.execute_command('FLUSHDB', callback=callback)

    def ping(self, callback=None):
        self.execute_command('PING', callback=callback)

    def info(self, callback=None):
        self.execute_command('INFO', callback=callback)

    def select(self, db, callback=None):
        self.selected_db = db
        self.execute_command('SELECT', db, callback=callback)

    def shutdown(self, callback=None):
        self.execute_command('SHUTDOWN', callback=callback)

    def save(self, callback=None):
        self.execute_command('SAVE', callback=callback)

    def bgsave(self, callback=None):
        self.execute_command('BGSAVE', callback=callback)

    def lastsave(self, callback=None):
        self.execute_command('LASTSAVE', callback=callback)

    def keys(self, pattern, callback=None):
        self.execute_command('KEYS', pattern, callback=callback)

    def auth(self, password, callback=None):
        self.execute_command('AUTH', password, callback=callback)

    ### BASIC KEY COMMANDS
    def append(self, key, value, callback=None):
        self.execute_command('APPEND', key, value, callback=callback)

    def expire(self, key, ttl, callback=None):
        self.execute_command('EXPIRE', key, ttl, callback=callback)

    def ttl(self, key, callback=None):
        self.execute_command('TTL', key, callback=callback)

    def type(self, key, callback=None):
        self.execute_command('TYPE', key, callback=callback)

    def randomkey(self, callback=None):
        self.execute_command('RANDOMKEY', callback=callback)

    def rename(self, src, dst, callback=None):
        self.execute_command('RENAME', src, dst, callback=callback)

    def renamenx(self, src, dst, callback=None):
        self.execute_command('RENAMENX', src, dst, callback=callback)

    def move(self, key, db, callback=None):
        self.execute_command('MOVE', key, db, callback=callback)

    def substr(self, key, start, end, callback=None):
        self.execute_command('SUBSTR', key, start, end, callback=callback)

    def delete(self, *keys, **kwargs):
        self.execute_command('DEL', *keys, callback=kwargs.get('callback'))

    def set(self, key, value, callback=None):
        self.execute_command('SET', key, value, callback=callback)

    def setex(self, key, ttl, value, callback=None):
        self.execute_command('SETEX', key, ttl, value, callback=callback)

    def setnx(self, key, value, callback=None):
        self.execute_command('SETNX', key, value, callback=callback)

    def mset(self, mapping, callback=None):
        items = []
        [items.extend(pair) for pair in mapping.iteritems()]
        self.execute_command('MSET', *items, callback=callback)

    def msetnx(self, mapping, callback=None):
        items = []
        [items.extend(pair) for pair in mapping.iteritems()]
        self.execute_command('MSETNX', *items, callback=callback)

    def get(self, key, callback=None):
        self.execute_command('GET', key, callback=callback)

    def mget(self, keys, callback=None):
        self.execute_command('MGET', *keys, callback=callback)

    def getset(self, key, value, callback=None):
        self.execute_command('GETSET', key, value, callback=callback)

    def exists(self, key, callback=None):
        self.execute_command('EXISTS', key, callback=callback)

    def sort(self, key, start=None, num=None, by=None, get=None, desc=False,
             alpha=False, store=None, callback=None):
        if (start is not None and num is None) \
        or (num is not None and start is None):
            raise ValueError("``start`` and ``num`` must both be specified")

        tokens = [key]
        if by is not None:
            tokens.append('BY')
            tokens.append(by)
        if start is not None and num is not None:
            tokens.append('LIMIT')
            tokens.append(start)
            tokens.append(num)
        if get is not None:
            tokens.append('GET')
            tokens.append(get)
        if desc:
            tokens.append('DESC')
        if alpha:
            tokens.append('ALPHA')
        if store is not None:
            tokens.append('STORE')
            tokens.append(store)
        return self.execute_command('SORT', *tokens, callback=callback)

    def getbit(self, key, offset, callback=None):
        self.execute_command('GETBIT', key, offset, callback=callback)

    def setbit(self, key, offset, value, callback=None):
        self.execute_command('SETBIT', key, offset, value, callback=callback)

    ### COUNTERS COMMANDS
    def incr(self, key, callback=None):
        self.execute_command('INCR', key, callback=callback)

    def decr(self, key, callback=None):
        self.execute_command('DECR', key, callback=callback)

    def incrby(self, key, amount, callback=None):
        self.execute_command('INCRBY', key, amount, callback=callback)

    def decrby(self, key, amount, callback=None):
        self.execute_command('DECRBY', key, amount, callback=callback)

    ### LIST COMMANDS
    def blpop(self, keys, timeout=0, callback=None):
        tokens = list(keys)
        tokens.append(timeout)
        self.execute_command('BLPOP', *tokens, callback=callback)

    def brpop(self, keys, timeout=0, callback=None):
        tokens = list(keys)
        tokens.append(timeout)
        self.execute_command('BRPOP', *tokens, callback=callback)

    def brpoplpush(self, src, dst, timeout=1, callback=None):
        tokens = [src, dst, timeout]
        self.execute_command('BRPOPLPUSH', *tokens, callback=callback)

    def lindex(self, key, index, callback=None):
        self.execute_command('LINDEX', key, index, callback=callback)

    def llen(self, key, callback=None):
        self.execute_command('LLEN', key, callback=callback)

    def lrange(self, key, start, end, callback=None):
        self.execute_command('LRANGE', key, start, end, callback=callback)

    def lrem(self, key, value, num=0, callback=None):
        self.execute_command('LREM', key, num, value, callback=callback)

    def lset(self, key, index, value, callback=None):
        self.execute_command('LSET', key, index, value, callback=callback)

    def ltrim(self, key, start, end, callback=None):
        self.execute_command('LTRIM', key, start, end, callback=callback)

    def lpush(self, key, value, callback=None):
        self.execute_command('LPUSH', key, value, callback=callback)

    def rpush(self, key, value, callback=None):
        self.execute_command('RPUSH', key, value, callback=callback)

    def lpop(self, key, callback=None):
        self.execute_command('LPOP', key, callback=callback)

    def rpop(self, key, callback=None):
        self.execute_command('RPOP', key, callback=callback)

    def rpoplpush(self, src, dst, callback=None):
        self.execute_command('RPOPLPUSH', src, dst, callback=callback)

    ### SET COMMANDS
    def sadd(self, key, value, callback=None):
        self.execute_command('SADD', key, value, callback=callback)

    def srem(self, key, value, callback=None):
        self.execute_command('SREM', key, value, callback=callback)

    def scard(self, key, callback=None):
        self.execute_command('SCARD', key, callback=callback)

    def spop(self, key, callback=None):
        self.execute_command('SPOP', key, callback=callback)

    def smove(self, src, dst, value, callback=None):
        self.execute_command('SMOVE', src, dst, value, callback=callback)

    def sismember(self, key, value, callback=None):
        self.execute_command('SISMEMBER', key, value, callback=callback)

    def smembers(self, key, callback=None):
        self.execute_command('SMEMBERS', key, callback=callback)

    def srandmember(self, key, callback=None):
        self.execute_command('SRANDMEMBER', key, callback=callback)

    def sinter(self, keys, callback=None):
        self.execute_command('SINTER', *keys, callback=callback)

    def sdiff(self, keys, callback=None):
        self.execute_command('SDIFF', *keys, callback=callback)

    def sunion(self, keys, callback=None):
        self.execute_command('SUNION', *keys, callback=callback)

    def sinterstore(self, keys, dst, callback=None):
        self.execute_command('SINTERSTORE', dst, *keys, callback=callback)

    def sunionstore(self, keys, dst, callback=None):
        self.execute_command('SUNIONSTORE', dst, *keys, callback=callback)

    def sdiffstore(self, keys, dst, callback=None):
        self.execute_command('SDIFFSTORE', dst, *keys, callback=callback)

    ### SORTED SET COMMANDS
    def zadd(self, key, score, value, callback=None):
        self.execute_command('ZADD', key, score, value, callback=callback)

    def zcard(self, key, callback=None):
        self.execute_command('ZCARD', key, callback=callback)

    def zincrby(self, key, value, amount, callback=None):
        self.execute_command('ZINCRBY', key, amount, value, callback=callback)

    def zrank(self, key, value, callback=None):
        self.execute_command('ZRANK', key, value, callback=callback)

    def zrevrank(self, key, value, callback=None):
        self.execute_command('ZREVRANK', key, value, callback=callback)

    def zrem(self, key, value, callback=None):
        self.execute_command('ZREM', key, value, callback=callback)

    def zcount(self, key, start, end, offset=None, limit=None,
               with_scores=None, callback=None):
        tokens = [key, start, end]
        if offset is not None:
            tokens.append('LIMIT')
            tokens.append(offset)
            tokens.append(limit)
        if with_scores:
            tokens.append('WITHSCORES')
        self.execute_command('ZCOUNT', *tokens, callback=callback)

    def zscore(self, key, value, callback=None):
        self.execute_command('ZSCORE', key, value, callback=callback)

    def zrange(self, key, start, num, with_scores, callback=None):
        tokens = [key, start, num]
        if with_scores:
            tokens.append('WITHSCORES')
        self.execute_command('ZRANGE', *tokens, callback=callback)

    def zrevrange(self, key, start, num, with_scores, callback=None):
        tokens = [key, start, num]
        if with_scores:
            tokens.append('WITHSCORES')
        self.execute_command('ZREVRANGE', *tokens, callback=callback)

    def zrangebyscore(self, key, start, end, offset=None, limit=None,
                      with_scores=False, callback=None):
        tokens = [key, start, end]
        if offset is not None:
            tokens.append('LIMIT')
            tokens.append(offset)
            tokens.append(limit)
        if with_scores:
            tokens.append('WITHSCORES')
        self.execute_command('ZRANGEBYSCORE', *tokens, callback=callback)

    def zrevrangebyscore(self, key, end, start, offset=None, limit=None,
                         with_scores=False, callback=None):
        tokens = [key, end, start]
        if offset is not None:
            tokens.append('LIMIT')
            tokens.append(offset)
            tokens.append(limit)
        if with_scores:
            tokens.append('WITHSCORES')
        self.execute_command('ZREVRANGEBYSCORE', *tokens, callback=callback)

    def zremrangebyrank(self, key, start, end, callback=None):
        self.execute_command('ZREMRANGEBYRANK', key, start, end,
                             callback=callback)

    def zremrangebyscore(self, key, start, end, callback=None):
        self.execute_command('ZREMRANGEBYSCORE', key, start, end,
                             callback=callback)

    def zinterstore(self, dest, keys, aggregate=None, callback=None):
        return self._zaggregate('ZINTERSTORE', dest, keys, aggregate, callback)

    def zunionstore(self, dest, keys, aggregate=None, callback=None):
        return self._zaggregate('ZUNIONSTORE', dest, keys, aggregate, callback)

    def _zaggregate(self, command, dest, keys, aggregate, callback):
        tokens = [dest, len(keys)]
        if isinstance(keys, dict):
            items = keys.items()
            keys = [i[0] for i in items]
            weights = [i[1] for i in items]
        else:
            weights = None
        tokens.extend(keys)
        if weights:
            tokens.append('WEIGHTS')
            tokens.extend(weights)
        if aggregate:
            tokens.append('AGGREGATE')
            tokens.append(aggregate)
        return self.execute_command(command, *tokens, callback=callback)

    ### HASH COMMANDS
    def hgetall(self, key, callback=None):
        self.execute_command('HGETALL', key, callback=callback)

    def hmset(self, key, mapping, callback=None):
        items = []
        map(items.extend, mapping.iteritems())
        self.execute_command('HMSET', key, *items, callback=callback)

    def hset(self, key, field, value, callback=None):
        self.execute_command('HSET', key, field, value, callback=callback)

    def hget(self, key, field, callback=None):
        self.execute_command('HGET', key, field, callback=callback)

    def hdel(self, key, field, callback=None):
        self.execute_command('HDEL', key, field, callback=callback)

    def hlen(self, key, callback=None):
        self.execute_command('HLEN', key, callback=callback)

    def hexists(self, key, field, callback=None):
        self.execute_command('HEXISTS', key, field, callback=callback)

    def hincrby(self, key, field, amount=1, callback=None):
        self.execute_command('HINCRBY', key, field, amount, callback=callback)

    def hkeys(self, key, callback=None):
        self.execute_command('HKEYS', key, callback=callback)

    def hmget(self, key, fields, callback=None):
        self.execute_command('HMGET', key, *fields, callback=callback)

    def hvals(self, key, callback=None):
        self.execute_command('HVALS', key, callback=callback)

    ### PUBSUB
    def subscribe(self, channels, callback=None):
        self._subscribe('SUBSCRIBE', channels, callback=callback)

    def psubscribe(self, channels, callback=None):
        self._subscribe('PSUBSCRIBE', channels, callback=callback)

    def _subscribe(self, cmd, channels, callback=None):
        if isinstance(channels, basestring):
            channels = [channels]
        if not self.subscribed:
            original_callback = callback

            def _cb(*args, **kwargs):
                self.on_subscribed(*args, **kwargs)
                original_callback(*args, **kwargs)

            callback = _cb if original_callback else self.on_subscribed
        self.execute_command(cmd, *channels, callback=callback)

    def on_subscribed(self, result):
        self.subscribed = True

    def unsubscribe(self, channels, callback=None):
        self._unsubscribe('UNSUBSCRIBE', channels, callback=callback)

    def punsubscribe(self, channels, callback=None):
        self._unsubscribe('PUNSUBSCRIBE', channels, callback=callback)

    def _unsubscribe(self, cmd, channels, callback=None):
        if isinstance(channels, basestring):
            channels = [channels]
        self.execute_command(cmd, *channels, callback=callback)

    def on_unsubscribed(self, *args, **kwargs):
        self.subscribed = False

    def publish(self, channel, message, callback=None):
        self.execute_command('PUBLISH', channel, message, callback=callback)

    @gen.engine
    def listen(self, callback=None):
        if callback:
            def error_wrapper(e):
                if isinstance(e, GeneratorExit):
                    return ConnectionError('Connection lost')
                else:
                    return e

            cmd_listen = CmdLine('LISTEN')
            with self.connection as c:
                while self.subscribed:
                    data = yield gen.Task(c.readline)
                    if isinstance(data, Exception):
                        raise data

                    response = yield gen.Task(self.process_data,
                                              data,
                                              cmd_listen)
                    if isinstance(response, Exception):
                        raise response

                    result = self.format_reply(cmd_listen, response)

                    callback(result)
                    if result.kind in ['unsubscribe', 'punsubscribe'] \
                    and result.body == 0:
                        self.on_unsubscribed()

    ### CAS
    def watch(self, key, callback=None):
        self.execute_command('WATCH', key, callback=callback)

    def unwatch(self, callback=None):
        self.execute_command('UNWATCH', callback=callback)

    ### SCRIPTING COMMANDS
    def eval(self, script, keys=None, args=None, callback=None):
        if keys is None:
            keys = []
        if args is None:
            args = []
        num_keys = len(keys)
        keys.extend(args)
        self.execute_command('EVAL', script, num_keys, *keys, callback=callback)

    def evalsha(self, shahash, keys=None, args=None, callback=None):
        if keys is None:
            keys = []
        if args is None:
            args = []
        num_keys = len(keys)
        keys.extend(args)
        self.execute_command('EVALSHA', shahash, num_keys, *keys, callback=callback)

    def script_exists(self, shahashes, callback=None):
        # not yet implemented in the redis protocol
        self.execute_command('SCRIPT EXISTS', *shahashes, callback=callback)

    def script_flush(self, callback=None):
        # not yet implemented in the redis protocol
        self.execute_command('SCRIPT FLUSH', callback=callback, verbose=True)

    def script_kill(self, callback=None):
        # not yet implemented in the redis protocol
        self.execute_command('SCRIPT KILL', callback=callback)

    def script_load(self, script, callback=None):
        # not yet implemented in the redis protocol
        self.execute_command('SCRIPT LOAD', script, callback=callback)


class Pipeline(Client):
    def __init__(self, transactional, *args, **kwargs):
        super(Pipeline, self).__init__(*args, **kwargs)
        self.transactional = transactional
        self.command_stack = []

    def execute_command(self, cmd, *args, **kwargs):
        if cmd in ('AUTH', 'SELECT'):
            super(Pipeline, self).execute_command(cmd, *args, **kwargs)
        elif cmd in PUB_SUB_COMMANDS:
            raise RequestError(
                'Client is not supposed to issue command %s in pipeline' % cmd)
        self.command_stack.append(CmdLine(cmd, *args, **kwargs))

    def discard(self):
        # actually do nothing with redis-server, just flush the command_stack
        self.command_stack = []

    def format_replies(self, cmd_lines, responses):
        results = []
        for cmd_line, response in zip(cmd_lines, responses):
            try:
                results.append(self.format_reply(cmd_line, response))
            except Exception, e:
                results.append(e)
        return results

    @gen.engine
    def execute(self, callback=None):
        command_stack = self.command_stack
        self.command_stack = []

        if self.transactional:
            command_stack = [CmdLine('MULTI')] \
                          + command_stack \
                          + [CmdLine('EXEC')]

        request = format_pipeline_request(command_stack)

        if not self.connection.ready():
            yield gen.Task(self.connection.wait_until_ready)

        try:
            self.connection.write(request)
        except IOError:
            self.command_stack = []
            self.connection.disconnect()
            raise ConnectionError("Socket closed on remote end")
        except Exception, e:
            self.command_stack = []
            self.connection.disconnect()
            raise e

        responses = []
        total = len(command_stack)
        cmds = iter(command_stack)

        with self.connection:
            while len(responses) < total:
                data = yield gen.Task(self.connection.readline)
                if not data:
                    raise ResponseError('Not enough data after EXEC')
                try:
                    cmd_line = cmds.next()
                    if self.transactional and cmd_line.cmd != 'EXEC':
                        response = yield gen.Task(self.process_data, data,
                                                  CmdLine('MULTI_PART'))
                    else:
                        response = yield gen.Task(self.process_data,
                                                  data,
                                                  cmd_line)
                    responses.append(response)
                except Exception, e:
                    responses.append(e)

        if self.transactional:
            command_stack = command_stack[:-1]
            responses = responses[-1]
            results = self.format_replies(command_stack[1:], responses)
        else:
            results = self.format_replies(command_stack, responses)

        callback(results)
