# -*- coding: cp1251 -*- 
# скрипт генерит csv с колонками: auid, nick, fb email, fb friends, ok friends, pw friends, vk friends, fraction, dt_last_login
# предварительно экспортировать входные данные из mongodb:
# mongoexport.exe --csv -d sa -c friends -f auid,friend_auid,snid > friends.csv
# mongoexport.exe --csv -d sa -c users -f _id,nick,fraction,dt_last_login,fb.email > users.csv
import sys
import re
import datetime
P = re.compile('(.+),"(.+)",("(?:.+)")?')

A = dict()
for line in open("users.csv").readlines()[1:]:
    try:
        auid, nick, fraction, dt_last_login, fb_email = line.split(",")
        fb_email = fb_email.strip()
        dt_last_login = datetime.datetime.fromtimestamp(float(dt_last_login)).strftime("%d.%m.%Y %H:%M:%S")
        try:
            nick = unicode(nick, 'utf-8').encode('cp1251')
        except Exception:
            pass
        auid = str(int(float(auid)))
    except ValueError:
        print "Parse error: %s" % line
        sys.exit(1)
    if not auid in A:
        A[auid] = {"friends" : {'"fb"' : [], '"ok"' : [], '"pw"' : [], '"vk"' : []},
                   "fraction" : '',
                   "nick" : '',
                   "dt_last_login" : '',
                   "fb_email" : ''
        }
    A[auid]['fraction'] = fraction
    A[auid]['nick'] = nick
    A[auid]['dt_last_login'] = dt_last_login
    A[auid]['fb_email'] = fb_email

for line in open("friends.csv").readlines()[1:]:
    try:
        auid, friend_auid, snid = line.split(",")
        snid = snid.strip()
    except ValueError:
        print "Parse error: %s" % line
        sys.exit(1)
    if not auid in A:
        print "Unknown auid %s" % auid
        sys.exit(1)
    A[auid]['friends'][snid].append(friend_auid)

headers = ['auid','nick','fb_email', 'fb friends', 'ok friends', 'pw friends', 'vk friends', 'fraction', 'dt_last_login']
print ';'.join(headers)
for auid, info in A.items():
    csv_fraction = ''
    if info['fraction']:
        csv_fraction = "=%s" % info['fraction']
    stats = [auid,
             info['nick'],
             info['fb_email'],
             len(info['friends']['"fb"']),
             len(info['friends']['"ok"']),
             len(info['friends']['"pw"']),
             len(info['friends']['"vk"']),
             csv_fraction,
             info['dt_last_login']]
    stats = [str(el) for el in stats]
    print ';'.join(stats)