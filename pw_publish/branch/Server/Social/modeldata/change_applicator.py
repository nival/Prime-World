# -*- coding: utf-8 -*-

#
# (C) Vadim Petrov 2011
#
# change generator for modeldata
import copy

from baseclasses import *
from base.helpers import *
from base.exceptions import *
import numbers
from modeldata import collects
from modeldata.changes import CHANGE_OP_CODES

# -----------------------------------------------------------------------------------------------------

class ModelChangeApplicator(object):
    # воссоздаем ModelData по приходящим model changes (!пока понимаем только init и upd!)

    @staticmethod
    def addNewObject( model, path, value = -1 ):
        obj = None
        # нету такого объекта; пробуем завести новый
        keeper_path, obj_id = pathParentChild(path)
        keeper = pathFind( model, keeper_path )
        #info( "keeper_path=%r, obj_id=%r, keeper type=%s" % (keeper_path, obj_id, type(keeper)) )
        # если id похож на число, преобразуем к инту
        try:
            obj_id = int(obj_id)
        except:
            pass

        if isinstance(keeper, collects.Keeper):
            # текущий добавляемый id в keeper не должен быть меньше текущего значения
            saved_uid = -1
            if model.next_uid_ > obj_id:
                saved_uid = model.next_uid_
            # следующий выдаваемый guid должен совпадать с заданным
            # для этого уменьшаем значение guid
            model.next_uid_ = obj_id - 1
            #model.nextGUID = ModelChangeApplicator.nextGUID
            #ModelChangeApplicator.setNextGUID( obj_id ) # следующий выдаваемый guid должен совпадать с заданным

            keeperClassName = keeper.keeperTypeName
            #~ ############FIXME: злая подпорка :) пытаемся догадаться, какое имя класса хранится в данном keeper; убрать, когда сделают keeper.obj_name по PF-37800
            #~ keeperClassName = keeper_path[:-len("Keeper")]
            #~ if keeperClassName[-1] == "s":
            #~ keeperClassName = keeperClassName[:-1]
            #~ if keeperClassName == "Heroe": # исключение
            #~ keeperClassName = "Hero"
            #~ ############

            # у ModelData для каждого <XXX>Keeper должен быть метод new<XXX>()
            newClass = getattr( model, "new%s"%keeperClassName )
            if newClass:
                obj, new_obj_id = newClass()
                if new_obj_id != obj_id:
                    raise ModelChangeApplicatorError("%s obj_id generation failure: %s (new_obj_id) != %s (obj_id) for keeper %s",
                                                     newClass, new_obj_id, obj_id, keeper_path)
                if saved_uid != -1:
                    model.next_uid_ = saved_uid
                    #info("keeper class name=%r, newClass() type=%s, new obj type=%s" % (keeperClassName, type(newClass), type(obj)) )

            return obj

        elif isinstance(keeper, collects.Set):
            keeper.add( obj_id )

            #объект существует в keeper'е?
            obj = keeper.get( obj_id )
            if not obj:
                raise ModelChangeApplicatorError("Failed do add value %s into Set for path %s", obj_id, keeper_path)

            return obj

        elif isinstance(keeper, collects.Collection):
            #при добавлении в коллекцию нужно знать пару ключ/значение

            if value != -1:
                keeper.add( obj_id, value )

                #объект существует в keeper'е?
                obj = keeper.get( obj_id )
                if not obj:
                    raise ModelChangeApplicatorError("Failed do add value %s=>%s into Collection for path %s", obj_id, value, keeper_path)

            return obj

        elif isinstance(keeper, collects.SimpleList):

            keeper.append( obj_id )

            return obj_id

        elif isinstance(keeper, collects.SimpleDict):
            #при добавлении в коллекцию нужно знать пару ключ/значение

            if value != -1:
                keeper.add( obj_id, value )

            return obj_id


    @staticmethod
    def applyInits( acc, modelname, modelclass, model_changes ):
        if (acc is not None) and model_changes:
            for event in model_changes:
                if not _checkEvent(event):
                    continue
                for comment,change_list in event.iteritems():
                    checker = _CangesChecker(comment, change_list)
                    if checker.fail: continue
                    for change_line in change_list:
                        if not checker.checkLine(change_line): continue
                        path, op, values = change_line

                        model = acc.get(modelname)
                        if op == 'init':
                            if not values:
                                model = modelclass()
                                model.init( None ) # обязательно, чтобы во все keeper прописались keeperTypeName (напр. "Friend" для FriendsKeeper)
                                return

                            if not values and isinstance(values, dict):
                                err_trace("ModelChangeApplicator: wrong init values in change_line (%r) in the change_list %s. Nonempty dict required.",
                                          change_line, comment)
                            else:
                                try:
                                    t0 = time.time()
                                    model = modelclass()
                                    model.init( None ) # обязательно, чтобы во все keeper прописались keeperTypeName (напр. "Friend" для FriendsKeeper)
                                    values_copy = copy.deepcopy( values )
                                    model.load( values_copy )
                                    model.init( None )#после load'a нужен init
                                    setattr(acc, modelname, model)
                                    t1 = time.time()
                                    info("MCA: md creation time=%.3f" % (t1-t0) )
                                except Exception:
                                    catch()



    @staticmethod
    def applyUpds(acc, modelname, modelclass, model_changes):
        if (acc is not None) and model_changes:
            model = acc.get(modelname, None)
            if model is None:
                err("applyUpds modelname=%r is None",modelname)
                return

            for event in model_changes:
                if not _checkEvent(event): continue
                for comment, change_list in event.iteritems():
                    checker = _CangesChecker(comment, change_list)
                    if checker.fail: continue
                    for change_line in change_list:
                        if not checker.checkLine(change_line): continue
                        path, op, values = change_line

                        if op != 'init' and model:
                            if op == 'add':
                                if not checker.checkAddValues(): continue
                                for key, value in values.iteritems():
                                    add_path = path + "/" + str(key)
                                    obj = ModelChangeApplicator.addNewObject( model, add_path, value )

                            elif op == 'upd':
                                if not checker.checkUpdValues(): continue
                                obj = pathFind( model, path )
                                if obj is None:
                                    obj = ModelChangeApplicator.addNewObject( model, path )

                                if obj is not None:
                                    for key,val in values.iteritems():
                                        if  isinstance(key, numbers.Integral ):
                                            obj[key] = val
                                        else:
                                            setattr( obj, key, val )
                                else:
                                    warn( "MCA: upd obj NOT added: path=%s" % path )

                            elif op == "del":
                                if not checker.checkDelValues(): continue
                                obj_id = values
                                coll = pathFind( model, path )
                                # если id похож на число, преобразуем к инту
                                try:
                                    obj_id = long(obj_id)
                                except:
                                    pass

                                remove = getattr( coll, "remove", None )
                                if remove:
                                    try:
                                        remove( obj_id )
                                    except:
                                        warn("MCA: del failed, 'remove' method failed on path=%r and value=%r", path, obj_id)
                                else:
                                    warn("MCA: del failed, no 'remove' method on path=%r", path)

                            elif op == "swap":
                                if not checker.checkSwapValues(): continue
                                err( "MCA: swap operation NOT SUPPORTED" )

                            elif op == "push":
                                if not checker.checkPushValues(): continue
                                add_path = path + "/" + str(values)
                                obj = ModelChangeApplicator.addNewObject( model, add_path, values )

                            else:
                                err( "MCA: operation(%r) %r NOT SUPPORTED", modelname, op )


    @staticmethod
    def apply( acc, modelname, modelclass, model_changes ):
        #first init
        ModelChangeApplicator.applyInits( acc, modelname, modelclass, model_changes )
        #then update
        ModelChangeApplicator.applyUpds( acc, modelname, modelclass, model_changes )


    # ------------------------------------------------------------
    # подделываем механизм выдачи GUID-ов
    @staticmethod
    def setNextGUID( id ):
        ModelChangeApplicator.next_guid = id

    @staticmethod
    def nextGUID( ):
        info("=== nextGUID called [ ModelChangeApplicator.next_guid=%r ]" % ModelChangeApplicator.next_guid )
        return ModelChangeApplicator.next_guid


def _checkEvent(event):
    if not event:
        err_trace("ModelChangeApplicator: Empty event: %r", event)
        return False
    if isinstance(event, dict):
        return True
    err_trace("ModelChangeApplicator: Event isn't a dict: %r", event)
    return False


class _CangesChecker(object):

    def __init__(self, comment, change_list):
        if not comment:
            err_trace("ModelChangeApplicator: Empty comment: %r (for change_list %s)", comment, change_list)
            self.fail = True
        elif not isinstance(comment, basestring):
            err_trace("ModelChangeApplicator: Comment isn't a string: %r (for change_list %s)", comment, change_list)
            self.fail = True
        elif not isinstance(change_list, list):
            err_trace("ModelChangeApplicator: change_list (for comment %s) isn't a list: %r", comment, change_list)
            self.fail = True
        else:
            self.comment = comment
            self.fail = not change_list

    def checkLine(self, line):
        if not (line and isinstance(line, list) and len(line) == 3):
            err_trace("ModelChangeApplicator: wrong change_line (%r) in the change_list %s", line, self.comment)
            return False
        path, op, values = line
        if path is None or not isinstance(path, basestring):
            err_trace("ModelChangeApplicator: wrong path in the change_line (%s) in the change_list %s", line, self.comment)
            return False
        if not (op and isinstance(op, basestring) and (op in CHANGE_OP_CODES)):
            err_trace("ModelChangeApplicator: wrong op in the change_line (%s) in the change_list %s", line, self.comment)
            return False
        self.change_line = line
        self.values = line[2]
        return True


    def checkAddValues(self):
        if self.values and isinstance(self.values, dict):
            return True
        err_trace("ModelChangeApplicator: wrong add values in change_line (%r) in the change_list %s. Nonempty dict required.",
                  self.change_line, self.comment)
        return False


    def checkUpdValues(self):
        if self.values and isinstance(self.values, dict):
            return True
        err_trace("ModelChangeApplicator: wrong upd values in change_line (%r) in the change_list %s. Nonempty dict required.",
                  self.change_line, self.comment)
        return False


    def checkDelValues(self):
        if (self.values or self.values == 0) and isinstance(self.values, (numbers.Integral, basestring)):
            if self.values == 0: #TODO remove it later?
                debug("ModelChangeApplicator: 0 del value in change_line (%r) in the change_list %s.",
                      self.change_line, self.comment)
            return True
        err_trace("ModelChangeApplicator: wrong del values in change_line (%r) in the change_list %s.",
                  self.change_line, self.comment)
        return False


    def checkSwapValues(self):
        if self.values and isinstance(self.values, list) and len(self.values) == 2:
            return True
        err_trace("ModelChangeApplicator: wrong swap values in change_line (%r) in the change_list %s. List of 2 values required.",
                  self.change_line, self.comment)
        return False

    def checkPushValues(self):
        if (self.values or self.values == 0) and isinstance(self.values, (numbers.Integral, basestring)):
            if self.values == 0: #TODO remove it later?
                debug("ModelChangeApplicator: 0 push value in change_line (%r) in the change_list %s.",
                      self.change_line, self.comment)
            return True
        err_trace("ModelChangeApplicator: wrong push values in change_line (%r) in the change_list %s.",
                  self.change_line, self.comment)
        return False
