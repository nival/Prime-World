<?php
echo "WARNING: Do not use restartWorkers as a short way to do stopWorkers + startWorkers!\n";
$root = dirname(__FILE__);
$root.= '/./';
require $root.'settings/config.php';
$backgroundPath = realpath($root.'application/background/');
if(file_exists($backgroundPath.'/workers_old.txt'))
{
    unlink($backgroundPath.'/workers_old.txt');
}
$workersPath = realpath($backgroundPath.'/workers');
$workersFile = fopen($backgroundPath.'/workers_old.txt', 'a+', false);
$workersPIDs = array();
//****************facebook****************
//post update
$op = array();
$logPath = realpath($config['path']['logs']).'/';
for($i=0;$i<$config['workers']['facebook']['post'];$i++)
{
    exec('php '.$workersPath.'/facebookPostWorker.php >>'.$logPath.'facebookPostWorker-'.$i.'.out 2>&1 & echo $!',$op);
    $workersPIDs[] = $op[$i];
}
//****************vkontakte****************
//post update
$op = array();
for($i=0;$i<$config['workers']['vkontakte']['post'];$i++)
{
    exec('php '.$workersPath.'/vkontaktePostWorker.php >>'.$logPath.'vkontaktePostWorker-'.$i.'.out 2>&1 & echo $!',$op);
    $workersPIDs[] = $op[$i];
}
//****************odnoklassniki***********
//****************steam***********
//****************aeriagames***********
//****************mailru***********
//**************log********************
$op = array();
for($i=0;$i<$config['workers']['log']['count'];$i++)
{
    exec('php '.$workersPath.'/logBackgroundWorker.php >>'.$logPath.'logBackgroundWorker-'.$i.'.out 2>&1 & echo $!',$op);
    $workersPIDs[] = $op[$i];
}
$workersPIDsStr = serialize($workersPIDs);
fwrite($workersFile, $workersPIDsStr);
fclose($workersFile);
echo "All workers started.\n";
?>
