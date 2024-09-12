#!/bin/bash
tail -n +26778 logs/wsStatisticResend.log.N|grep 'is already sent'|perl -ne 'print "$1\n" if /Packet (\d+) is already sent/'
