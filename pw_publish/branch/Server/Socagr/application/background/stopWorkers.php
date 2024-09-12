<?php
require_once dirname(__FILE__).'/settings/config.php';

function stopWorkers($workersPIDs,$path)
{
    static $counter=array();
    if($workersPIDs)
    {
        foreach ($workersPIDs as $k=>$PID)
        {
            $sPidFile = $path.$PID .'-state.txt';
            $status = file_exists($sPidFile)
                ? unserialize(file_get_contents($sPidFile))
                : false;
            if(!$status)
            {
                echo "For stop try run [php workers/terminateJobs.php] \n";
                echo "Error: No pid file [{$sPidFile}] detected. Continue? \n";
                echo "Type 'no'/'yes': ";
                $handle = fopen ("php://stdin","r");
                $line = trim(fgets($handle));
                if($line=='no' )
                {
                    echo "by!\n";
                    exit(0);
                }
            }
            elseif(( isset($status[$PID]) && ($status[$PID]['state']=='wait') ))
            {
                killProcess($PID);
                echo "{$PID} stop\n";
                unset($workersPIDs[$k]);
                if(file_exists($sPidFile))
                {
                    unlink($sPidFile);
                }else{
                    return;
                }
            }else{
                $counter[$PID]=isset($counter[$PID])?$counter[$PID]+1:1;
                echo "{$PID}:{$counter[$PID]} is busy...,try shutdown".str_repeat('.', $counter[$PID])."\n";

                file_put_contents($sPidFile, serialize(array($PID=>array('state'=>'no_more','t'=>date("Y-m-d H:i:s"),'u'=>time(),'name'=>$status['name']))), LOCK_EX);

                if($counter[$PID]>2)
                {
                   sleep($counter[$PID]);
                }
            }
            if($workersPIDs)
            {
                shuffle($workersPIDs);
                return stopWorkers($workersPIDs,$path);
            }
        }
    }
    return;
}
function killProcess($pid)
{
    exec('kill '.$pid);
    //exec('kill -9 '.$pid);
}

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
        if($line=='no' )
        {
            echo "by!\n";
            exit(0);
        }
    }
}

$path=realpath($config['path']['logs']).'/pid/';
stopWorkers($workersPIDs,$path);

if(file_exists(dirname(__FILE__).'/workers.txt'))
{
    unlink(dirname(__FILE__).'/workers.txt');
}
echo "All workers stoped.\n";