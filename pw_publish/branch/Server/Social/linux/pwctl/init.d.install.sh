#!/usr/bin/env bash

PATH=`pwd`
echo $PATH

for file in $PATH/etc/init.d/prepare/*; do
    /bin/rm /etc/init.d/$(/usr/bin/basename $file)
    /bin/ln -s $PATH/etc/init.d/prepare/$(/usr/bin/basename $file) /etc/init.d/$(/usr/bin/basename $file)
done

for file in $PATH/etc/default/prepare/*; do
    /bin/rm /etc/default/$(/usr/bin/basename $file)
    /bin/ln -s $PATH/etc/default/prepare/$(/usr/bin/basename $file) /etc/default/$(/usr/bin/basename $file)
done

/bin/chmod 777 ./etc/init.d/prepare/pw*
