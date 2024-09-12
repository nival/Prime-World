# coding: utf8

import sys
import functools
import time

from base.helpers import ClassDict, info, tryexcept, log, debug, info, warn, err, error
from handlers import users
import imirror

sys.path.append('tornado')
import tornado.options
from tornado.options import define, options
from base.wstools import AddLoopCallback
from modeldata.persistent_data import PersistentDataManager

from base.helpers import info, tryexcept, log, debug, info, warn, err, error, errStack
from pwaccount import ACC_STATUS_PROCESS_SAVE

class UserAccountDataManager(object):
    def __init__(self, acc):
        self.acc = acc

    @staticmethod
    @tryexcept
    def save_callback(data_reply, server_instance, try_count=1, callback=None):
        t0 = time.time()
        uid = data_reply.get("p")
        reply = data_reply.get("r")
        acc = users.get(uid)

        if acc:
            acc.tsSaveData = 0
            if acc.pend_data_save > 0:
                acc.pend_data_save -= 1
            else:
                warn("Trying to save data, but acc.pend_data_save will be < 0 for uid=%d", uid)
            info("onUserDataSaved: uid=%s, data_reply!=None: %s, pend_data_save=%s", uid, data_reply is not None, acc.pend_data_save)
        else:
            info("onUserDataSaved: uid=%s, data_reply!=None: %s", uid, data_reply is not None)

        if reply:
            if acc and acc.acc_status == ACC_STATUS_PROCESS_SAVE:
                acc.setAccStatusDataSaved()
            server_instance.I.MIRROR.addRequest(imirror.MirrorDataType.MODEL_DATA, uid)

        elif acc:  
            if (not acc.finalize_tm) or (acc.finalize_tm + server_instance.MAX_USER_SAVE_TIME > t0):
                timeout = server_instance.SAVE_USER_DATA_RETRY_TIMEOUT *  try_count
                info( "bad onUserDataSaved reply (uid=%s), scheduling retry in %.3f seconds..." % (uid, timeout)) 
                _callback = functools.partial(UserAccountDataManager.save_by_uid, uid=uid, save_data=1, try_count=try_count + 1,  server_instance=server_instance)
                AddLoopCallback(_callback, timeout)
            else:
                # столько времени пробуем, но не смогли сохранить в mongo? ок, признаем поражение, дампим persistent-данные в файл
                if not acc.finalize_data:
                    err("CANT SAVE acc[%d], dumping to file" % (uid))
                    acc.save(save_data=0, dump_to_file=1)
                # и все же разрешаем удалить акк
                acc.setAccStatusDataSaved()

        t1 = time.time()

        info("onUserDataSaved timing: %.3f", t1 - t0)
        if callback:
            callback()

    @staticmethod
    @tryexcept
    def save_by_uid(uid=-1, *args, **kwargs):
        acc = users.get(uid)

        if not acc:
            warn("bad saveUserData acc (uid=%d)" % uid)
            return
        if (not args) and ('server_instance' not in kwargs):
            err(errStack("UserAccountDataManager.save_by_uid: no server_instance parameter for save() provided!"))
            return
        return UserAccountDataManager(acc).save(*args, **kwargs)


    @tryexcept
    def save(self, server_instance, final=False, save_data=1, dump_to_file=0, retry_if_in_progress=1, pending=0, try_count=1, callback=None):

        if self.acc.guest or self.acc.failed or self.acc.locked:
            if self.acc.failed or self.acc.locked:
                warn("tried to save acc (uid=%s auid=%s) while not loaded: locked=%s, failed=%s", self.acc.uid, self.acc.auid, self.acc.locked, self.acc.failed)

            if final:
                debug("save acc (uid=%s auid=%s guest=%s)", self.acc.uid, self.acc.auid, self.acc.guest)
                self.acc.setAccStatusDataSaved() #TODO посмотреть как было
                if callback:
                    callback()
            return

        if pending: 
            self.acc.pendingSaveData = None

        now = time.time()

        if not save_data or not getattr(self.acc, 'tsSaveData', None):

            db_json = PersistentDataManager.saveData(self.acc)

            info("persist data for user[%d] auid=%s: persist len %d, pers_cas %s (data:%d, file:%d), save_counter %s", self.acc.uid, self.acc.auid, len(db_json), self.acc.pers_cas, save_data, dump_to_file, self.acc.db.save_counter)

            if final:
                self.acc.finalize_data = 0

            if save_data:
                self.acc.tsSaveData = now
                self.acc.pend_data_save += 1
                _callback = functools.partial(UserAccountDataManager.save_callback, try_count=try_count, server_instance=server_instance, callback=callback)

                if self.acc.do_not_save_mongo:
                    _callback({"p": self.acc.uid, "r": "ok"})
                else:
                    info("PERSIST DATA FOR USER")
                    server_instance.I.DATA.saveData(self.acc.login, self.acc.pers_key, options.server_id, db_json, _callback, params=self.acc.uid)

            if dump_to_file:
                encoded_userdata = db_json.encode("latin1")

                dump_filename = "logs/dump_uid_%s_time_%d.json.data" % ( self.acc.uid, time.time())
                dump_file = open(dump_filename, "w")
                dump_file.write(encoded_userdata)
                dump_file.close()

            return
        else:
            warn("Account uid=%d auid=%s already saving data (ts %d, now %d), pendingSaveData func: %s", self.acc.uid, self.acc.auid, self.acc.tsSaveData, now, self.acc.pendingSaveData)

        if retry_if_in_progress:
            if not self.acc.pendingSaveData:
                timeout = server_instance.PENDING_SAVE_RETRY_TIMEOUT * try_count
                info( "Account uid=%d auid=%s add pendingSaveData func, timeout %.3f seconds", self.acc.uid, self.acc.auid, timeout )
                _callback = functools.partial( UserAccountDataManager.save_by_uid, server_instance=server_instance, uid=self.acc.uid, final=final, save_data=save_data, retry_if_in_progress=1, pending=1, try_count=try_count + 1)
                self.acc.pendingSaveData = _callback
                AddLoopCallback(_callback, timeout)


    @tryexcept
    def load(self):
        pass




