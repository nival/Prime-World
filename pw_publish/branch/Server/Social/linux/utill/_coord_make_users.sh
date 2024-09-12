#!/usr/bin/env bash

cd ..
# for fresh MYSQL installations:
python -u coordinator.py --port=8700 --log_file_prefix=logs/wsCoord.log --_make_test_logins=1000