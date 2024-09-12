#!/usr/bin/env sh

apt-get -y python2.7
apt-get -y install libmysqlclient-dev  python-dev
apt-get -y install libcurl4-gnutls-dev librtmp-dev
apt-get -y install inspircd

# apt-cache search
# apt-get install curl libghc-curl-dev libmysqld-dev

# https://archive.apache.org/dist/thrift/0.8.0/
# thrift-0.8.0.tar.gz
# http://thrift.apache.org/docs/BuildingFromSource
# https://thrift-tutorial.readthedocs.org/en/latest/installation.html
apt-get -y install libboost-dev libboost-test-dev libboost-program-options-dev libevent-dev automake libtool flex bison pkg-config g++ libssl-dev git
# ./configure --without-java --without-php

#Install mono
apt-key adv --keyserver keyserver.ubuntu.com --recv-keys 3FA7E0328081BFF6A14DA29AA6A19B38D3D831EF
echo "deb http://download.mono-project.com/repo/debian wheezy main" | tee /etc/apt/sources.list.d/mono-xamarin.list
apt-get -y update
apt-get -y install mono-gmcs

#Install additional packages for mono
apt-get -y install git autoconf libtool automake build-essential mono-devel gettext

cd ..
virtualenv venv
. venv/bin/activate

cd vendor/linux

pip install MySQL-python-1.2.3.tar.gz
#pip install MySQL-python-1.2.3.patch.tar.gz
pip install pycurl-7.19.0.tar.gz
pip install pymongo-1.9.tar.gz
pip install python-suds-0.4.tar.gz
pip install py.thrift-0.8.0.tar.gz


#pip install PIL
pip install PIL --allow-unverified --allow-all-external

#python leporo-tornado-redis-e0fc1f3/setup.py install
#python pymongo-src-1.10/setup.py install

pip freeze
