#!/usr/bin/env bash

#/etc/init.d/pw-coordinator restart
GGG=`netstat -tlnp | awk '/:8701 */ {split($NF,a,"/"); print a[1]}'`
echo -e "kill pid[$GGG] \n"

array=(${GGG//\n/ })

/etc/init.d/pw-xs stop
if [ -n "$GGG" ]
then
    for i in "${!array[@]}"
    do
        echo -e "$i=>${array[i]}"
        kill "${array[i]}"
    done
fi

/etc/init.d/pw-xcoordinator restart
/etc/init.d/pw-xs restart