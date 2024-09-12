#!/usr/bin/env bash

PATH=`pwd`
echo $PATH, `pwd`

/usr/bin/python prepare_etc_templates.py

echo "set ENV\n\n"
echo "  create user [pwcastle]\n"

/bin/cat /etc/passwd | /bin/grep pwcastle > /dev/null && USERISSET=1
if [[ $USERISSET == '' ]]
then
    echo -e "add user pwcastle\n"
    /usr/sbin/useradd -p \`openssl -p dmfge985674jgdsk\` pwcastle
fi

echo "  install init.d and default\n"
/bin/bash ./init.d.install.sh

/bin/chmod 777 $PATH/usr/local/bin/pwctl
/bin/chmod 777 $PATH/opt/pwctl/fabric/fabfile.py

/bin/ln -s $PATH/opt/pwctl/fabric/fabfile.py /usr/bin/fab
/bin/ln -s $PATH/usr/local/bin/pwctl /usr/local/bin/pwctl

/bin/chmod 777 ./../../logs/
/bin/chmod 777 ./../../services/common
/bin/chmod 777 ./../../services/dummy_ps
/bin/chmod 777 ./../../services/dummy_pwc
/bin/chmod 777 ./../../services/dummy_se
/bin/chmod 777 ./../../services/events
/bin/chmod 777 ./../../services/login
/bin/chmod 777 ./../../services/marketing
/bin/chmod 777 ./../../services/pwc_frontend
/bin/chmod 777 ./../../services/status
/bin/chmod 777 ./../../linux/all_byservic_*

