#!/usr/bin/env bash
echo -e "\ntry restore state \n"
php ../../application/background/restoreState.php
echo -e "\ntry stop workers \n"
php ../../application/background/stopWorkers.php
echo -e "\n\ntry run workers \n"
sleep 10
php ../../application/background/startWorkers.php
