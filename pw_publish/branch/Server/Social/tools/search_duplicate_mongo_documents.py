import zlib, bz2
from pymongo import Connection as MongoClient
import os


HOST = "localhost"
PORT = 27017
DB = "pw2"
COLLECTION = "pers"
DUP_KEY = "key"
OUT = "DUMPS" #you need to create dumps folder before running this script

def decompress_data(data_dict, out):
    persistent_str = data_dict["data"]
    str_head = persistent_str[:4]
    if str_head in ["ZLIB", "BZIP"]:
        encoded_persistent = persistent_str[4:].encode('latin1')
        if persistent_str[:4] == "ZLIB":
            persistent_str = zlib.decompress( encoded_persistent )
        elif persistent_str[:4] == "BZIP":
            persistent_str = bz2.decompress( encoded_persistent )
        f = open(os.path.join(OUT, out),"w")
        f.write(persistent_str)
        f.close()

def main(collect):
    res = collect.aggregate([
            { "$group":
                {"_id":
                     "$%s" % DUP_KEY,
                      "count":
                             { "$sum": 1 }
                }
            },
            { "$match":
                {"count":
                    { "$gt": 1 }
                 }
            },
            { "$project":
                  {DUP_KEY: "$%s" % DUP_KEY, "name": "$%s" % DUP_KEY, "count": 1}
            }
    ])
    print res
    for i, x in enumerate(res["result"]):
        print x
        r = collect.find({DUP_KEY: x["_id"]})
        print r.count()
        j = 0
        for d in r:
            j += 1
            # Need to add something for the unification of the procedure of processing bad mongo-documents
            decompress_data(d, str(x["_id"])+ "_" + str(j) +".json" )
        #collect.remove({"key": x["_id"]})


if __name__=="__main__":
    client = MongoClient(HOST, PORT)
    db = client[DB]
    main(db[COLLECTION])