# -*- coding: utf-8 -*-
__author__ = 'danil.lavrentyuk'
import sys, time

if len(sys.argv) > 1:
    try:
        seconds = float(sys.argv[1])
    except Exception:
        seconds = 0
else:
    seconds = 1.0

if seconds > 0:
    print "=== WAITING %5.3f seconds..." % seconds
    time.sleep(seconds)
else:
    print "Bad argument: %s. Positive int or float number of seconds required." % sys.argv[1]


