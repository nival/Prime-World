#!/bin/bash

echo "\nInstall python module: \n\n"

#MySQLdb-python-1.2.3c1.tar.gz  MySQL-python-1.2.3.patch.tar.gz
pip install setuptools

pip install MySQL-python-1.2.3.tar.gz
pip install pycurl-7.19.0.tar.gz
pip install pymongo-1.9.tar.gz
pip install python-suds-0.4.tar.gz
pip install py.thrift-0.8.0.tar.gz
