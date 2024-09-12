# coding: utf8

import signal

def set_blocking_alarm(loop, on=True):
    if on and (loop._blocking_signal_threshold is not None):
        signal.setitimer(signal.ITIMER_REAL, loop._blocking_signal_threshold, 0)
    else:
        signal.setitimer(signal.ITIMER_REAL, 0, 0)
