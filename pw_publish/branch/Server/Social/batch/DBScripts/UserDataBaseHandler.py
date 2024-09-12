#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys
import gc
import pymongo
import imp
from operator import attrgetter
import multiprocessing

sys.path.append('../..')
sys.path.append('..')
sys.path.append('../cfg')

from modeldata.persistent_data import PersistentDataManager
from modeldata.ModelData import *
from modeldata.StaticData import StaticData
from config.MultiConfig import MultiConfig
from modeldata.datamanager import ScriptInfo
from pwaccount import UserAccount

from ifactory import IfaceFactory

FOREACH_SLEEP_MSEC_PER_USER = 100
FOREACH_USERS_PER_GC_COLLECT = 100
STATISTICSTIMEOUT = 10

class UserDataBaseHandler():
    def __init__(self, mongo_db, keysToProcess, totalAccs, processId, logFileName, handlerFunctionName,
                 rewriteData, outputData, **kwargs):
        self.mongo_db = mongo_db
        self.keysToProcess = keysToProcess
        self.totalAccs = totalAccs
        self.processId = processId
        self.logFile = open(logFileName + str(processId) + ".log", "w")
        self.handlerFunction = getattr(self, handlerFunctionName)
        self.kwargs = kwargs
        self.rewriteData = rewriteData
        self.outputData = outputData
        self.name = "Worker %d: " % processId

        # Создаём фейковые интерфейсы для некоторых скриптов
        self.I = ClassDict()
        self.I.BILL = IfaceFactory.makeBillingInterface("dummy", self.I)
        self.I.Config = MultiConfig()
        self.I.SD = StaticData("../xdb/ExportedSocialData.xml", self.I.Config.getMainConfig(), applyOverrides=True)

        self.I.STATS = IfaceFactory.makeIStatsInterface("none", "", self.I)  # пустая болванка

    def _loadAccount(self, userKey):
        obj = self.mongo_db.pers.find_one({"key": userKey})
        if not obj:
            return None, None, False

        # 1) Вытащим сырые данные пользователя
        ####################################################
        if not obj.get("data", None) or not obj.get("key", None):
            sys.stdout.write(self.name + "Data for account %r was not found\n" % str(obj))
            return None, None, False
        data_json = obj["data"]

        self.curIdx += 1


        if self.curIdx % FOREACH_USERS_PER_GC_COLLECT == 0:
            gc.collect()

        key_coll = userKey.split("_")
        if len(key_coll) == 2:
            prefix = key_coll[0]
            uid = long(key_coll[1])
        else:
            sys.stdout.write(self.name + "ERROR bad key %r\n" % userKey)
            return None, None, False
        ####################################################

        # 2) Загрузим acc
        ####################################################
        try:
            acc = UserAccount(PersistentDataManager.newSimpleDataAcc(data_json))
            acc.SD = self.I.SD
            acc.Config = self.I.Config
            MD = ModelData()
            MD.load(acc.model)
            MD.init(changeWriter=None)
        except Exception:
            catch()
            sys.stdout.write(self.name + "ERROR bad data for key %r\n" % userKey)
            return None, None, False
        ####################################################

        return acc, MD, True

    def _saveData(self, acc, md, pers_key):
        # 1) Завернем acc в json zip'?
        ####################################################
        acc.model = md.generateJsonDict()
        new_data_json = PersistentDataManager.saveData(acc, True)
        ####################################################

        # 2) Сохраним изменённые данные
        ####################################################
        updateFunc = getattr(mongo_db.pers, "update")
        mongo_reply = updateFunc({"key": pers_key}, {"$set": {"data": new_data_json}}, upsert=True, safe=True)
        if not mongo_reply.get("ok", None):
            sys.stdout.write(self.name + "ERROR save to mongo: %r\n" % mongo_reply)
        ####################################################

    def processAccount(self):
        self.curIdx = 0
        l = len(self.keysToProcess)
        i = 1
        t = time.time()
        for userKey in self.keysToProcess:
            acc, MD, result = self._loadAccount(userKey)
            if not result:
                continue

            # Обработка modeldata
            ####################################################
            self.handlerFunction(MD, acc, acc.model, userKey, self.kwargs)
            if time.time() > t and i < l:
                #time.sleep(FOREACH_SLEEP_MSEC_PER_USER / 1000.0)  # ??? ? ???? ?? ?????? ?????
                t += STATISTICSTIMEOUT
                sys.stdout.write(self.name + "{0:.2f}% was processed \n".format((float(i)/l)*100))
            i += 1
        json.dump(self.outputData, self.logFile)
        self.logFile.close()
        sys.stdout.write(self.name + "100% was processed \n")
        sys.stdout.write(self.name + "finished \n")

    def findUsersWithBadPremiumAcc(self, md, acc, mdDict, persKey, kwargs):
        secs = toint(kwargs.get("secs"))
        #if md.IsPremiumAccount():
        diff = md.LordInfo.PremiumAccountEnd - md.LordInfo.PremiumAccountStart
        if diff >= secs:
            print self.name + ": auid =", acc.db.auid, "-> PremiumAccount = ", diff, "sec"
            kwargs["accountsToProcess"].append(persKey)
            self.outputData.append(acc.db.auid)

    def findUsersWithLesserVersion(self, md, acc, mdDict, persKey, kwargs):
        version = toint(kwargs.get("version"))
        if (md.version.revision < version):
            self.outputData[md.version.revision] += 1
            kwargs["accountsToProcess"].append(persKey)



    def fixUsersWithLesserVersion(self, md, acc, mdDict, persKey, kwargs):
        scripts = kwargs.get("scripts", None)
        scriptInfos = []
        if scripts:
            try:
                if scripts:
                    for i, scriptInfo in enumerate(scripts):
                        if scriptInfo.revision > md.version.revision or (scriptInfo.revision == md.version.revision and scriptInfo.patch > md.version.patch):
                            # поскольку скрипты в self.scripts[] должны лежать строго по порядку ревизий, просто отрезаем часть списка начиная с данного scriptInfo
                            scriptInfos = scripts[i:]
                            scriptInfos = self._sortScriptList(scriptInfos)
                            break
            except Exception:
                catch()
                return

            for scriptInfo in scriptInfos:
                try:
                    scclass = getattr(scriptInfo.scmodule, scriptInfo.scclassname)()
                    md, acc.db = scclass.convertModelData(self, acc, md, mdDict)
                except Exception:
                    err(self.name + "Fail run script: " + scriptInfo.script_name)
                    catch()
                    return

                md.version.revision = scriptInfo.revision
                md.version.patch = scriptInfo.patch
        else:
            print(self.name + "Scripts not found!")

        self._saveData(acc, md, persKey)

    def findBrokenTutorialAccounts(self, md, acc, mdDict, persKey, kwargs):
        version = toint(kwargs.get("version"))
        if md.version.revision <= version and len(md.LordInfo.MapsByType) <= 1:
            if md.version.revision in self.outputData:
                self.outputData[md.version.revision] += 1
                kwargs["accountsToProcess"].append(persKey)

    @staticmethod
    def _sortScriptList(scripts):
        priorityScripts = []

        for i, scriptInfo in enumerate(scripts):

            if scriptInfo.priority != 0:
                priorityScripts.append(scriptInfo)
                del scripts[i]
        priorityScripts = sorted(priorityScripts, key=attrgetter('priority'))

        scripts = priorityScripts + scripts

        return scripts

def loadConversionScripts():
    scripts = []
    path = os.path.dirname(os.path.realpath(__file__))
    versionfile = os.path.normpath(os.path.join(path, "../../modeldata/Scripts/version.txt"))
    file = open(versionfile, "r")
    lines = file.readlines()
    file.close()
    for line in lines:
        if line[0] == '#': # a comment (or disabled string)
            continue
        startIdx = 0
        endIdx = line.find( " ", startIdx )
        if endIdx == -1:
            err( "Bad format line, skip: %r" % line )
            continue
        revision = int(line[startIdx:endIdx])
        startIdx = endIdx+1
        endIdx = line.find( " ", startIdx )
        if endIdx == -1:
            err( "Bad format line, skip: %r" % line )
            continue
        patch = int(line[startIdx:endIdx])
        startIdx = endIdx+1
        endIdx = line.find( " ", startIdx )
        if endIdx == -1:
            err( "Bad format line, skip: %r" % line )
            continue
        priority = int(line[startIdx:endIdx])

        filename = line[endIdx+1:].strip()
        if filename[-3:] == ".py":
            scriptspath = os.path.normpath( os.path.join( path, "../../modeldata/Scripts" ) )
            filename = os.path.normpath( os.path.join( scriptspath, filename ) )
            if os.path.isfile( filename ):
                scclassname = os.path.splitext( os.path.basename( filename ) )[0]
                info( "LoadScript: scclassname %r, script_name %r" % (scclassname, filename) )
                scmodule = imp.load_source( scclassname, filename )
                scriptInfo = ScriptInfo( revision, patch, priority, filename, scmodule, scclassname )
                scripts.append( scriptInfo )
                info( "Add script: file %r, ver %s %s" % (filename, revision, patch) )
            else:
                err( "File %r not exist" % filename )
        else:
            err( "Bad filename in script list: %r, skipping whole line: %r" % (filename, line) )
    return scripts

def main(shard, total, keysFileName, processId, logFileName, handlerFunctionName, rewriteData, kwargs ):
    outputData = []
    try:
        keysFile = open(keysFileName, "r")
        keysToProcess = json_loads(keysFile.read())
        keysFile.close()
    except Exception:
        catch()
        exit(1)

    opt = ClassDict(shard)
    mongo_db = getattr(pymongo.Connection(opt.mongo_addr, opt.mongo_port), opt.mongo_base, None)
    #mongo_db = getattr(pymongo.Connection(opt.mongo_addr, opt.mongo_port, slave_okay=True), opt.mongo_base, None)
    if mongo_db:
        if handlerFunctionName in ("findUsersWithLesserVersion", ):
            version = toint(kwargs.get("version", 0))
            kwargs["accountsToProcess"] = []
            outputData = {}
            for i in xrange(0, version):
                outputData[i] = 0

        elif handlerFunctionName == "fixUsersWithLesserVersion":
            scripts = loadConversionScripts()
            kwargs["scripts"] = scripts

        elif handlerFunctionName == "findUsersWithBadPremiumAcc":
            kwargs["accountsToProcess"] = []
            outputData = []

        elif handlerFunctionName in ("findBrokenTutorialAccounts",):
            version = toint(kwargs.get("version", 0))
            kwargs["accountsToProcess"] = []
            outputData = {}
            for i in xrange(100, version):
                outputData[i] = 0

        print "Total accs for process %d: %d" % (processId, total)
        dbHandler = UserDataBaseHandler(mongo_db, keysToProcess, total, processId, logFileName, handlerFunctionName,
                                      rewriteData, outputData, **kwargs)
        dbHandler.processAccount()

        if handlerFunctionName in ("findUsersWithLesserVersion", "findUsersWithBadPremiumAcc", "findBrokenTutorialAccounts"):
            #print "accountsToProcess =", kwargs["accountsToProcess"]
            keysFile = open(keysFileName, "w")
            json.dump(kwargs["accountsToProcess"], keysFile)
            keysFile.close()


if __name__ == "__main__":
    curIdx = 0
    print "Args = ", sys.argv

    if len(sys.argv) > 8:
        try:
            shard = json_loads(sys.argv[1])
            total = toint(sys.argv[2])
            keysFileName = sys.argv[3]
            processId = toint(sys.argv[4])
            logFileName = sys.argv[5]
            handlerFunctionName = sys.argv[6]
            rewriteData = str2bool(sys.argv[7])
            kwargs = json_loads(sys.argv[8])
        except Exception:
            catch()
            exit(1)
    else:
        exit(1)

    main(shard, total, keysFileName, processId, logFileName, handlerFunctionName, rewriteData, kwargs)
