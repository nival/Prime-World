import sys
import json
import datetime
import random
import time

if len(sys.argv) < 4:
    print 'Usage: main.py <US mm logs> <RU mm logs> <FINAL mm logs>'
    sys.exit(1)
us = sys.argv[1]
ru = sys.argv[2]
usru = sys.argv[3]

print 'Merging %r+%r=%r' % (us, ru, usru)

fus = open(us, 'rb')
fru = open(ru, 'rb')

class ShiftData:

    def __init__(self, shift, location):
        self.shift = shift
        self.location = location

    def ProcessPings(self, member):
        if self.location == 'us':
            member['pings'].append( {u'ru0' : random.randint(100, 300)} )
        elif self.location == 'ru':                 
            member['pings'].append( {u'us0' : random.randint(100, 300)} )

    def __call__(self, row):
        rtype = row.keys()[0]
        if rtype == 'PushingGame':
            for member in row.values()[0]['members']:
                member['reqId'] += self.shift
                member['userId'] += self.shift
                self.ProcessPings(member)
        else:
            row.values()[0]['id'] += self.shift
            if rtype == 'RequestQueued':
                row.values()[0]['rev'] = 55555
                for member in row.values()[0]['members']:
                    member['mmId'] += self.shift
                    self.ProcessPings(member)

def ParseData(f, func):
    print 'Loading data for %r' % func.location
    errors = 0
    rows = []
    for _line in f.readlines():
        try:
            if _line[0].find('{') >= 0:
                rows.append(_line)
            else:
                raise ValueError()
#            if len(rows) == 100:
#                break
        except ValueError, details:
            errors += 1
    print 'Data parsed for %r (rows=%d skipped=%d)' % (func.location, len(rows), errors)        
    data = []
    for i, row in enumerate(rows):
        rdata = json.loads(row)
        dt = rdata.values()[0]['time']
        d = datetime.datetime(year=2013, month=dt['mon'], day=dt['day'], hour=dt['hour'], minute=dt['min'], second=dt['sec'])
        secs = time.mktime(d.timetuple())
        if func:
            func(rdata)
            row = json.dumps(rdata)
        data.append((row, func.location, secs, dt['scalar']))
    return data

def Compare(row0, row1):
    line0, location0, dt0, scalar0 = row0
    line1, location1, dt1, scalar1 = row1
    if location0 != location1:
        if dt0 < dt1:
            return -1
        elif dt0 > dt1:
            return 1
        return 0 
    else:
        if scalar0 < scalar1:
            return -1
        elif scalar0 > scalar1:
            return 1
        return 0

data_us = ParseData(fus, ShiftData(10000000, 'us'))
data_ru = ParseData(fru, ShiftData(0, 'ru'))

print 'Sorting data'
data_us.extend(data_ru)
data_ru = None
data_us.sort(Compare)

print 'Writing final data'
fall = open(usru, 'wb')
fall.write('Local time: +0:00 UTC\n')
fall.write('ProcessId: 555\n')

for row in data_us:
    line, location, dt, scalar = row
    s = line+'\n'
    fall.write(s)
