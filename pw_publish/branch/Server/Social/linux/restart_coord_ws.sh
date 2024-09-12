#!/usr/bin/env bash

/etc/init.d/pw-coordinator stop
/etc/init.d/pw-coordinator start
/etc/init.d/pw-ws restart
