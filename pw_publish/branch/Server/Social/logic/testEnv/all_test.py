#!/usr/bin/env python
# -*- coding: utf-8 -*-
# (C) Vadim Petrov 2011, Nival

import os, sys, unittest, logging, gc
from pythonEnvironment import *
from csharpEnvironment import *
from modeldata.datamanager import PwNewModelManager
from modeldata.persistent_data import PersistentDataManager
from iserialmodel import ISyncSerialModel
from iwebserver import IWebServer
from modeldata.MultiStaticData import MultiStaticData
from config.MultiConfig import *
from ifactory import IfaceFactory
from ipersonserver import IFakePersonServer

pathForTests = "../tests"

DEFAULT_LOG_LEVEL = logging.WARNING

# - needed in reroll shop manual testing, will started this tests from - Reroll_shop_with_statistics
# - maybe debug locally, but remember - logic "Reroll_shop_with_statistics" depends on this
# - don`t start in build process this - there is work with the database and disk
locked_tests_in_build_machine = [
    "reroll_shop_with_statistics_test",
    "reroll_shop_with_statistics_subprocess_test"
]


# Каждый параметр имеет вид ИМЯ_ФАЙЛА или ИМЯ_ФАЙЛА:ИМЯ_ТЕСТА
# возвращает словарь вида:  ИМЯ_ФАЙЛА => [СПИСОК_ИМЕН_ТЕСТОВ]
# при пустом списке тестов исполняет из данного файла все тесты (все классы и функции уровня модуля, не начинающиеся с __)
# при пустом списке файлов будут испоользованы все питоновские файлы из каталога

def parseParams(params):
    tests = {}
    for param in params:
        param_array = param.split(":")
        filename = param_array[0]
        if not tests.get(filename):
            tests[filename] = []
        if len(param_array) > 1:
            tests[filename].append(param_array[1])

    return tests


# Собирает из pathForTests (путь относительно пути текущего файла) все .py-файлы
def findAllTest(files):
    path = os.path.normpath(os.path.join(os.path.dirname(os.path.realpath(__file__)), pathForTests))
    filelist = []
    for file in os.listdir(path):
        fpath = os.path.join(path, file)
        if os.path.isfile(fpath):
            fname, ext = os.path.splitext(file)
            if ext == '.py':
                if (not files) or (fname in files):
                    filelist.append(os.path.normpath(fpath))

    return sorted(filelist)


class LogicTest():
    def testLogicAtAll(self):
        logging.basicConfig(level=DEFAULT_LOG_LEVEL, format='[%(asctime)s %(levelname)8s] %(message)s')

        cfg.TOURNAMENT_SERVER = coord_cfg.COORDINATOR_TOURNAMENT_SERVER
        cfg.TOURNAMENT_SERVER_ADDR = coord_cfg.COORDINATOR_TOURNAMENT_SERVER_ADDR
        cfg.TOURNAMENT_XSERVER_ADDR = coord_cfg.COORDINATOR_TOURNAMENT_XSERVER_ADDR
        cfg.TOURNAMENT_SPECTATOR_AUIDS = coord_cfg.COORDINATOR_TOURNAMENT_SPECTATOR_AUIDS
        cfg.TOURNAMENT_APPLY_RESULTS = coord_cfg.COORDINATOR_TOURNAMENT_APPLY_RESULTS

        self.I = ClassDict()
        self.I.coord_res = {}
        self.I.coord_res["deploy_name"] = "RU"
        self.I.Config = MultiConfig()
        SD = MultiStaticData("../../xdb/ExportedSocialData.xml", self.I.Config.getMainConfig())
        self.I.SD = SD
        self.I.Config.fillStaticDataDependendValues(SD)
        self.I.WS = IWebServer(test_mode=True)  # FakeWSGuidGenerator()
        self.I.MD = PwNewModelManager(ifaceDict=self.I, load_events=False)
        self.I.PDM = PersistentDataManager(ifaceDict=self.I)
        self.I.SMODEL = ISyncSerialModel(self.I, FAKE_PWSOC_SERVER_VERSION)
        self.I.STATS = IfaceFactory.makeIStatsInterface("none", "", self.I)  # пустая болванка
        self.I.SQL = fakeSQL()
        self.I.BILL = IfaceFactory.makeBillingInterface("dummy", self.I)
        self.I.PS = IFakePersonServerForLogic()
        self.I.CHAT = IFakeChatForLogic()

        test_count = 0
        total_failed_test_count = 0
        total_failed_test = []
        filetests = parseParams(args)
        for file in findAllTest(filetests.keys()):
            envPy = PythonEnvironment(SD, self.I)

            filebase = os.path.basename(file)
            testclassname = os.path.splitext(filebase)[0]
            if testclassname == '__init__':
                continue
            testmodule = imp.load_source(testclassname, file)
            testclass = getattr(testmodule, testclassname)()

            tests = dir(testclass)

            for test in tests:
                if not "__" in test:
                    testFromArguments = test in filetests[testclassname] if testclassname in filetests else False
                    if len(filetests) == 0 or len(filetests[testclassname]) == 0 or testFromArguments:
                        if not testFromArguments and test in locked_tests_in_build_machine:
                            continue
                        s = ""
                        try:
                            s = str(testclass.__class__) + ":" + str(test)
                            warn(">>>starting: " + s)
                            envPy.runTest(getattr(testclass, test))
                        except Exception:
                            catch()
                            total_failed_test_count += 1
                            total_failed_test.append(s)
                            # эти две строки, похоже, баг или недоделка, к тому же они используют test (т.е. последний элемент предыдущей итерации)
                            # envCs = CSharpEnvironment()
                            # envCs.runTest( test )
                        test_count += 1
                        gc.collect()

        warn("total tests run: %d", test_count)
        warn("total success test count: %d", test_count - total_failed_test_count)
        warn("total failed test count: %d", total_failed_test_count)
        warn("total failed test names: \n%s", "\n".join(total_failed_test))
        return total_failed_test_count



gc.disable()
args = sys.argv[1:]
sys.argv = sys.argv[:1]
#unittest.main()

l = LogicTest()
exit(l.testLogicAtAll())
