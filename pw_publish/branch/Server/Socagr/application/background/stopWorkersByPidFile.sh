#!/usr/bin/env bash
echo -e "\ntry restore state \n"
php ../../application/background/restoreState.php
echo -e "\ntry stop workers \n"
php ../../application/background/stopWorkers.php