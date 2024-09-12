<?php
$backgroundPath = dirname(__FILE__);
if(!file_exists($backgroundPath.'/workers_old.txt'))
{
    echo "No active workers detected.\n";
}
else
{
    $workersFileContents = file_get_contents($backgroundPath.'/workers_old.txt');
    $workersPIDs = unserialize($workersFileContents);
    foreach ($workersPIDs as $pid)
    {
        $err = killProcess($pid);
        if($err)
        {
            echo "Error!!!\n";
            exit(1);
        }
    }
    unlink($backgroundPath.'/workers_old.txt');
    echo "All workers stoped.\n";
}

function killProcess($pid)
{
    exec('kill -9 '.$pid,$op,$err);
    return $err;
}