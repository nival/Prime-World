<?php
require_once dirname(__FILE__).'/settings/config.php';

exec("ps -ef | grep ".dirname(__FILE__)."/workers/workerRunner.php | grep -v 'grep' | awk '{print $2}'",$workersPIDs);
if(file_exists(dirname(__FILE__).'/workers.txt'))
{
    $workersPIDsSave = unserialize(file_get_contents(dirname(__FILE__).'/workers.txt'));
    sort($workersPIDsSave);
    sort($workersPIDs);
    if ($workersPIDsSave != $workersPIDs)
    {
        echo "Error in workers.txt. Continue?\n";
        echo "Type 'no'/'yes': ";
        $handle = fopen ("php://stdin","r");
        $line = trim(fgets($handle));
        if($line=='no')
        {
            echo "by!\n";
            exit(0);
        }elseif($line=='yes')
        {
            continue;
        }else{
            echo "error input: by!\n";
            exit(0);
        }
    }
}

if($workersPIDs)
{
    foreach ($workersPIDs as $key => $pid)
    {
        $aWorkersPIDs[$pid]=$pid;
        $sPidFile = realpath($config['path']['logs']).'/pid/'.$pid .'-state.txt';
        if(file_exists(realpath($config['path']['logs']).'/pid/'.$pid .'-state.txt') == false)
        {
            echo "-------------------------------------------------------- \n";
            echo "For stop workers try run [php workers/terminateJobs.php] \n";
            echo "-------------------------------------------------------- \n";
            echo "Error: No pid file [{$sPidFile}] detected. Continue? \n";
            echo "Type 'no'/'yes': ";
            $handle = fopen ("php://stdin","r");
            $line = trim(fgets($handle));
            if($line=='no')
            {
               echo "by!\n";
               exit(0);
            }elseif($line=='yes')
            {
               continue;
            }else{
               echo "error input: by!\n";
               exit(0);
           }
        }
    }
    if(!file_exists(dirname(__FILE__).'/workers.txt'))
    {
        file_put_contents(dirname(__FILE__).'/workers.txt', serialize($aWorkersPIDs),FILE_APPEND|LOCK_EX);
    }else{
        file_put_contents(dirname(__FILE__).'/workers.txt', serialize($aWorkersPIDs),LOCK_EX);
    }
}else
{
    $workersPIDs = array();
}
echo "restore state:\n";
var_dump($workersPIDs);