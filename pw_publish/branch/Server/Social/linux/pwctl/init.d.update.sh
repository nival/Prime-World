#!/usr/bin/env bash

PATH=`pwd`
echo $PATH

for file in $PATH/etc/init.d/prepare/*; do
    if [[ -L "$file" ]]; then
        echo "$file is a symlink";
    else
        echo del /etc/init.d/$(/usr/bin/basename $file)
        /bin/rm /etc/init.d/$(/usr/bin/basename $file)
        /bin/ln -s $PATH/etc/init.d/prepare/$(/usr/bin/basename $file) /etc/init.d/$(/usr/bin/basename $file)
    fi
done

for file in $PATH/etc/default/prepare/*; do
    if [[ -L "$file" ]]; then
        echo "$file is a symlink";
    else
        echo del /etc/default/$(/usr/bin/basename $file)
        /bin/rm /etc/default/$(/usr/bin/basename $file)
        /bin/ln -s $PATH/etc/default/prepare/$(/usr/bin/basename $file) /etc/default/$(/usr/bin/basename $file)
    fi
done

/bin/chmod 777 ./etc/init.d/prepare/pw*