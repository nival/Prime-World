#!/usr/bin/env bash
echo -e "\ntry stop workers \n"
php ../../application/background/workers/terminateJobs.php
echo -e "\n\ntry run workers \n"
sleep 5
php ../../application/background/startWorkers.php
