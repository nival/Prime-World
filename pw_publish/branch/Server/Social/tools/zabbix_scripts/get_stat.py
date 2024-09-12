#!/usr/bin/env python
# -"- coding: utf8 -"- 
# (C) Dmitry Kolb 2014, Nival Network 
__author__ = 'dmitry.kolb'

import argparse
import urllib2
import sys
import logging
import os
import base_stat

base_stat.buildPath()
from base.helpers import *

info = logging.info
warn = logging.warning
debug = logging.debug
error = logging.error

def get_stat(chost,cport, byname, bytype):
    params = ""
    if byname:
        params += "&byname=%s" % byname
    elif bytype:
        params += "&bytype=%s" % bytype
    else:
        params = ""
    try:
        req = urllib2.Request('http://{0}:{1}/x?action=get_stat{2}'.format(chost, cport, params))
        f = urllib2.urlopen(req)
        data = f.read()
        ddata = ClassDict(json_loads(data))
        response = ddata.response
        if response.get("ok"):
            del response["ec"]
            del response["ok"]
            del response["server"]
            return response
        else:
            warn("bad response:", response)

    except Exception:
        catch()

def main():
    parser = argparse.ArgumentParser(description='Scripts for getting of coordinator stats.')
    parser.add_argument('--coord_host', metavar='-ch', type=str, help='host of service')
    parser.add_argument('--coord_port', metavar='-cp', type=str, help='port of service')
    parser.add_argument('--bytype', metavar='-t', default="", type=str, help='type of services')
    parser.add_argument('--byname', metavar='-n', default="", type=str, help='name of services')
    parser.add_argument('--key',   metavar='-k', default="", type=str, help='key from reponse')
    logging.basicConfig(filename='get_stat.log', level=logging.INFO, format='[%(asctime)s %(levelname)8s] %(message)s' )

    args = parser.parse_args()
    info("Host is http://{0}:{1}".format(args.coord_host, args.coord_port))
    resp = get_stat(args.coord_host, args.coord_port, args.byname, args.bytype)
    if resp and args.key:
        base_stat.parse_response(resp, args.key, args.byname, args.bytype)


if __name__ == "__main__":
    main()

