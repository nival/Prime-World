#!/usr/bin/python
# -*- coding: utf-8 -*-
import sys, re, time, traceback

#fnames = [
#'statistic.log-20150124.1425',
#]

#outname = 'colleted-stats'
json_fn = 'collected-json'
unsent_fn = 'collected-unsent'
noresp_fn = 'collected-no-response'

json_file = open(json_fn, "wt")
unsent_file = open(unsent_fn, "wt")
noresp_file = open(noresp_fn, "wt")

sent = {} # dict to track sent/unsent packets
unsent = [] # list of packets failed to send

line_re = re.compile(r'\[(\S+\s\S+),(\d+)\s+(\w+)\] (.+)')
to_add_re = re.compile(r'key (\S+), args (\{.+\})')
to_add_head = 'to add: '
to_add_off = len(to_add_head)
thrift_re = re.compile(r"key='(\w+)', data=(\[.+\]), packet_id=(\d+)")
thrift_head = 'sendThrift LIST: '
thrift_off = len(thrift_head)
resp_re = re.compile(r"key='(\w+)', packet_id=(\d+), response=HTTPResponse\(code=(\d+),")
resp_head = 'onSendThriftHttpResponse: '
resp_off = len(resp_head)

sleep_cnt = 1

def process(ts, ms, level, text):
    if level == 'INFO':
        if text.startswith(to_add_head):
            # "key u'HeroRankChange', args {...}"
            m = to_add_re.match(text[to_add_off:])
            if m:
                print >>json_file, "key=%s, args=%s" % (m.group(1), m.group(2))
            else:
                print "WARN: strange 'to add' line: %s" % text
        elif text.startswith(thrift_head):
            # "key='HeroRankChange', data=[...], packet_id=NNN"
            m = thrift_re.match(text[thrift_off:])
            if m:
                key, data, packet_id = m.group(1,2,3)
                if packet_id in sent:
                    print "WARN: duplicate packet id %s" % packet_id
                else:
                    tm = time.mktime(time.strptime('2015-01-23 15:47:58', '%Y-%m-%d %H:%M:%S')) + (int(ms)/1000.0)
                    sent[packet_id] = (key, data, tm)
            else:
                print "WARN: strange sendThrift line: %s" % text
        elif text.startswith(resp_head):
            #"key='LoginUsers', packet_id=862, response=HTTPResponse(code=200, ..., error=None)"
            #"key='MoveHeroToBath', packet_id=451523, response=HTTPResponse(code=599, ..., error=HTTPError('HTTP 599: Timeout',)"
            m = resp_re.match(text[resp_off:])
            if m:
                key, packet_id, code = m.group(1,2,3)
                if packet_id in sent:
                    if code == '200':
                        #print "DEBUG: packet %s - ok" % packet_id
                        pass
                    else:
                        if code != '599':
                            print "WARN: coed %s for packet id %s" % (code, packet_id)
                        pkey, pdata, tm = sent[packet_id]
                        if pkey != key:
                            print "WARN: packet id %s keys mismatch: %s vs %s" % (packet_id, pkey, key)
                        print >>unsent_file, "%s: %s: %s" % (packet_id, key, pdata)
                        #unsent.append((pkey, pdata, tm))
                    del sent[packet_id]
                else:
                    print "WARN: skipping unknown packet_id %s in pesponse line: %s" % (packet_id, text)
            else:
                print "WARN: strange onSendThriftHttpResponse line: %s" % text
    elif level == 'WARNING':
        pass
    else:
        pass

in_trace = False

try:
#    for fname in fnames:
#        with open(fname) as infile:
    for line in iter(sys.stdin):
        if line.startswith('Processing file'):
            print "***", line,
            continue
        if line.startswith('Traceback (most recent call last):'):
            in_trace = True
            continue
        if (sleep_cnt % 10000) == 0:
            print "[%s] len(sent) = %s" % (sleep_cnt, len(sent))
            time.sleep(0.01)
        sleep_cnt += 1
        m = line_re.match(line)
        if m: # and len(m.groups()) == 3:
            in_trace = False
            #print m.groups()
            process(*m.group(1,2,3,4))
        else:
            if not in_trace:
                print "WARN: strange line: %s" % line
except:
    print traceback.print_exc()

for packet_id, (key, data, tm) in sent.iteritems():
    print >>noresp_file, "[%.3f] %s: %s: %s" % (tm, packet_id, key, data)

json_file.close()
unsent_file.close()
noresp_file.close()

