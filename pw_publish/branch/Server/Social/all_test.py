#!/usr/bin/env python
# -*- coding: utf-8 -*-
import os, sys, unittest, time
import subprocess

# Каждый из этих тестов запускается как отдельный процесс.
# Текущим каталогом назначается каталог, где находится файл теста.
# Тесты запускаются последовательно.
tests = [
    "logic/testEnv/all_test.py",
    "modeldata/Accounts/convertmd.test.py",
    "testdata/forClient.test.py",
    "friendsdata/friends.test.py",
    "modeldata/json.test.py",
    "modeldata/modeldata.test.py",
    "modeldata/StaticData_test.py",
    "modeldata/MultiStaticData_test.py",
    "testdata/multidata.test.py",
    "party/party.test.py",
    #"tests/party.test.py",    # !
    "testdata/ref.test.py",
    "testdata/serialization.test.py",
    "testdata/simplelist.test.py",
    #"tests/unit.test.py",   # !
    "tests/ibilling.test.py",
    "tests/staticdata.test.py",
    "tests/modeldata.test.py",
    "config/configdata.test.py",
    "tests/steam.test.py",
    "tests/arcgames.test.py",
    "tests/stats_agent.test.py",
    "tests/model_change_apply.test.py",
    "tests/change_applicator.test.py",
    #"tests/guards.test.py", # !
    "modeldata/Accounts/new_custom_events.test.py",
]

realpath = os.path.dirname( os.path.realpath(__file__) )
for test in tests:
    print ">>>RUNNING " + test
    sys.stdout.flush()
    os.chdir(realpath)
    filepath = os.path.dirname( os.path.realpath(test) )
    filename = os.path.basename( os.path.realpath(test) )
    os.chdir(filepath)
    if os.name != 'posix':
        retcode = subprocess.call(("python ", os.path.join(filepath, filename)), stdout=sys.stdout)
    else:
        retcode = subprocess.call(("python", os.path.join(filepath, filename)),shell=False, stdout=sys.stdout,stderr=sys.stdout)
    if retcode != 0:
        print "ERROR!"
        exit(1)

print "ALL OK!"
exit(0)
