import time, copy, gc
import random
import mdutils

N = 100000

gc.disable()

class _Talent(object):
    #~ def __init__(self):
        #~ pass
        
    def init(self):
        dct = self.__dict__
        
        #print "_Talent.__init__ called"
        #~ dct["index"] = index
        #~ dct["index2"] = index2
        #~ dct["index3"] = index3
        
        #~ dct.update( _Talent._defaults ) 
        dct["attr1"] = True
        dct["attr2"] = 2
        dct["attr3"] = "3"
        dct["attr4"] = 4
    
    #~ def __init__(self, index, index2, index3):
        #~ self.index = index
        #~ self.index2 = index2
        #~ self.index3 = index3
        
    def __getattr__(self, name):
        print "_Talent.__getattr__ called"
        return object.__getattr__(self, name)

    def __setattr__(self, name, value):
        return object.__setattr__(self, name, value)

    def test(self):
        print "_Talent.test()"


def speed_test():
    t0 = time.time()
    array = [ None ] * N
    for n in xrange(N):
        x = _Talent()
        x.init()
        array[n] = x
        
    t1 = time.time()

    print "--- PY create(%d) time: %.3f" % (N, t1-t0)
    print "t[0]=%s, t[1]=%s" % (array[0], array[1])
    print "t[0].__dict__=%s" % (array[0].__dict__)

#~ def speed_test_one_by_one_C():
    #~ t0 = time.time()
    #~ array = [ None ] * N
    #~ for n in xrange(N):
        #~ x = mdutils.clone( _Talent, 1 )
        #~ array[n] = x
        #~ #print "new t[%s]=%s, __dict__=%s" % (n, x, x.__dict__)
        
    #~ t1 = time.time()

    #~ print "--- PY clone(%d) time: %.3f" % (N, t1-t0)
    #~ print "t[0]=%s, t[1]=%s" % (array[0], array[1])
    #~ print "t[0].__dict__=%s" % (array[0].__dict__)

# ----------------------------------------------------
def clone_test_C():
    t0 = time.time() #-----

    cloned_list = mdutils.clone( _Talent, N )

    t1 = time.time() #-----
    print "clone() result len: %s" % len(cloned_list)
    print "--- C clone(%d) time: %.3f" % (N, t1-t0)
    print "cloned[0] dict: %s" % (cloned_list[0].__dict__)

    #~ cloned_list[0].attr2 = 1234
    #~ cloned_list[0].attr4 = 12
    #~ print "cloned[0] dict: %s" % (cloned_list[0].__dict__)
    #~ print "cloned[1] dict: %s" % (cloned_list[1].__dict__)
    #~ print "cloned[-1] dict: %s" % (cloned_list[-1].__dict__)
    #~ # ----------------------------------------------------

    cloned_list = []

# ----------------------------------------------------

# ----------------------------------------------------

#~ cloned_list = mdutils.clone( _Talent, 2 )
#~ print "---- cloned_list(2) done -----"
#~ bad, good = cloned_list

#~ print "dir(good): %s" % dir(good)
#~ print "bad: %s" % bad
#~ #print "dir(bad): %s" % dir(bad)

#~ #print "bad __dict__: %s" % bad.__dict__

#~ good_dir = dir(good)
#~ good_dir.remove( '__delattr__' )
#~ good_dir.remove( '__dict__' )
#~ good_dir.remove( '__doc__' )
#~ good_dir.remove( '__format__' )
#~ for name in good_dir:
    #~ print "trying attr bad.%s..." % ( name )
    #~ try:
        #~ print "attr bad.%s = %s" % ( name, getattr(bad, name, None) )
    #~ except:
        #~ pass

#~ x2 = mdutils.clone( _Talent, -1 )

#~ #------------------------------------------------------------
#~ print "gc.collect result: %s" % gc.collect()

#~ print "x1 dict: %s" % x1.__dict__
#~ print "x2 dict: %s" % x2.__dict__

#~ print "x1.attr2 == x2.attr2: %s" % (x1.attr2 == x2.attr2)
#~ print "x1.attr2 is x2.attr2: %s" % (x1.attr2 is x2.attr2)

#~ speed_test()
#~ speed_test_C()


def convert_int_keys_Py(dct):
    new_dct = {}
    for key,val in dct.iteritems():
        try:
            new_key = int(key)
            if new_key:
                new_dct[new_key] = val
                continue
        except:
            pass
        break
    return new_dct
    
#~ def convert_int_keys_Py(dct):
    #~ for key in dct.keys():
        #~ try:
            #~ new_key = int(key)
            #~ if new_key:
                #~ val = dct.pop(key)
                #~ dct[new_key] = val
                #~ continue
        #~ except:
            #~ pass
        #~ break
    #~ return dct


def test_dict_conversion():
    N = 100000

    dct1 = {}
    dct2 = {}

    for i in xrange(1000,1000+N):
        key = random.randint(1,1000000)
        dct1[ str(key) ] = key
        dct2[ str(key) ] = key
    print "original dict: len %s" % len(dct1)
    
    KEYS = len(dct1)

    t0 = time.time()
    new_dct = mdutils.convert_int_keys( dct1 )
    t1 = time.time()

    print "C (after) original dict: len %s" % len(dct1)
    print "C new dict: %s" % (str(new_dct)[:256])
    print "C new dict: len %s, \n--- C time(%d): %.3f" % (len(new_dct), KEYS, t1-t0)

    t0 = time.time()
    new_dct = convert_int_keys_Py( dct2 )
    t1 = time.time()

    print "PY (after) original dict: len %s" % len(dct2)
    print "PY new dict: %s, \n" % (str(new_dct)[:256])
    print "PY new dict: len %s, \n--- PY time(%d): %.3f" % (len(new_dct), KEYS, t1-t0)

# --------------------------------------------------------------------------------
# --------------------------------------------------------------------------------
# --------------------------------------------------------------------------------


speed_test()
clone_test_C()

print "gc.collect result: %s" % gc.collect()

# --------------------------------------------------------------------------------

test_dict_conversion()

print "gc.collect result: %s" % gc.collect()

