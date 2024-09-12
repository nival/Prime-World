#!/usr/bin/env bash

red='\e[0;31m'
green='\e[0;32m'
yellow='\e[1;33m'
NC='\e[0m' # No Color
echo -e "${green}\nstop...${NC}\n"

cd ..

if [ -f venv/bin/activate ];
then
   echo "Use venv"
   . venv/bin/activate
else
   echo "Not use venv"
fi

#echo -e "${red}\nstop sysyem service...${NC}\n"
#/etc/init.d/mongodb stop
#/etc/init.d/mysql stop
#/etc/init.d/redis-server stop
if [ -n "$1" ] && [ $1 == 'n' ]
then
  echo "stop nginx..."
  #nginx -c pw.conf
  ./linux/ngstop.sh
else
  echo 'skip stop nginx'
fi

echo -e "${red}\nstop PW service...${NC}\n"
# медленно стопаются
/etc/init.d/pw-coordinator stop

/etc/init.d/pw-friends stop & /etc/init.d/pw-party stop &\
 /etc/init.d/pw-thrift stop & /etc/init.d/pw-statistic stop &\
 /etc/init.d/pw-xcoordinator stop & /etc/init.d/pw-connect stop

# медленно стопаются
/etc/init.d/pw-ws stop

/etc/init.d/inspircd stop & /etc/init.d/pw-chat stop & /etc/init.d/pw-cf stop &\
 /etc/init.d/pw-ms stop & /etc/init.d/pw-xs stop & \
 /etc/init.d/pw-guild stop & /etc/init.d/pw-mirror stop &\
 /etc/init.d/pw-login stop & /etc/init.d/pw-es stop &\
 /etc/init.d/pw-siege stop & /etc/init.d/pw-dummyps stop &\
 /etc/init.d/pw-status stop

#ISSETLOGS = find . -type f -name "*.log" | wc -l
if [ -f logs/pw-coordinator.log.run ]
then
	PATHTMP="logs_history/stop_at_`date +'%m-%d-%y-%T'`"
	echo -e "${green}move log $(pwd)/logs to $PATHTMP ${NC}\n"
	mkdir -p $PATHTMP
	find logs/ -maxdepth 1 -type f -exec mv {} $PATHTMP \;
else
   echo "logs empty..."
fi
