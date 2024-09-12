<?php
require dirname(__FILE__).'/settings/config.php';
$workersPIDs = $aPIDsInfo = $aWorkerRunning = array();
exec("ps -ef | grep ".dirname(__FILE__)."/workers/workerRunner.php | grep -v 'grep' | awk '{print $2\":\"$11}'",$aPIDsInfo);
if($aPIDsInfo)
{
    foreach ($aPIDsInfo as $v)
    {
        $aTmp = explode(':', $v);
        $workersPIDsInfo[$aTmp[0]]=$aTmp[1];
        $workersPIDs[]=$aTmp[0];
        $aWorkerRunning[$aTmp[1]]=isset($aWorkerRunning[$aTmp[1]])?$aWorkerRunning[$aTmp[1]]+1:1;
    }
}

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

if($workersPIDs)
{
    echo "Active workers detected stop it first?\n";
    echo "Or run more?  Type 'no' to stop or 'c' to continue: ";
    $handle = fopen ("php://stdin","r");
    $line = trim(fgets($handle));
    if($line=='no' || $line!='c')
    {
        echo "by!\n";
        exit(0);
    }
    foreach ($config['workers']['workerAvailable'] as $name => $value)
    {
        if($value)
        {
            echo "Run more {$name}. Type 'no' to stop or number >=1 to continue or 0 to skip: ";
            $handle = fopen ("php://stdin","r");
            $line = trim(fgets($handle));
            if($line=='no' || intval($line,10)<0)
            {
                echo "by!\n";
                exit(0);
            }
            $config['workers'][$name]['count'] = intval($line,10);
        }else {
            echo "{$name} is off. Type 'no' to stop or 'c' to continue: ";
            $handle = fopen ("php://stdin","r");
            $line = trim(fgets($handle));
            if($line=='no' || $line!='c')
            {
                echo "by!\n";
                exit(0);
            }
        }
    }
}

foreach ($config['workers']['workerAvailable'] as $name => $value)
{
	$op = array();
    if($value && $config['workers'][$name]['count'])
    {
        $logPath = realpath($config['path']['logs']).'/';
        $aPidFiles = glob(realpath($config['path']['logs']).'/pid/*-state.txt');

        /*
        if($aPidFiles)
        {
            foreach($aPidFiles as $file)
            {
                if(is_file($file) && preg_match('/\d+\-.+/i', $file))
                {
                    $aWorkerRunning[$name]=isset($aWorkerRunning[$name])?$aWorkerRunning[$name]+1:0;
                }
            }
        }
        */

        $aWorkerRunning[$name] = isset($aWorkerRunning[$name])?$aWorkerRunning[$name]:0;
        for($i=0;$i<$config['workers'][$name]['count'];$i++)
        {
            exec('php '.dirname(__FILE__).'/workers/workerRunner.php -w '.$name.' >>'.$logPath.$name.'Worker-'.($i+$aWorkerRunning[$name]).'.out 2>&1 & echo $!',$op);
            $workersPIDs[$op[$i]] = $op[$i];
            echo "start {$name} on pid[{$op[$i]}]\n";
        }
    }
}

file_put_contents(dirname(__FILE__).'/workers.txt', serialize($workersPIDs), LOCK_EX);

echo "Now workers started: \n";
foreach ($workersPIDs as $v)
{
    echo "workers started pid[{$v}]\n";
}
