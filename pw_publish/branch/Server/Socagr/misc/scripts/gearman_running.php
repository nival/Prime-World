<?php
/**
 * see http://devjira.nivalnetwork.com/browse/PF-80746
 * Срипт для проверки настроек gearman при нескольких SA на одном сервере.
 *  В каталоге /var/www (или в пути, заданном первым аргументом) проверяет используемые
 *  порты gearman в конфигах соцагрегаторов и наличие запущенных на тех портах гирманов.
 * Use
 *  php gearman_was_run.php
 *  watch php gearman_running.php
 *  php gearman_was_run.php /var/www
 *  watch php gearman_was_run.php /var/www
 * Примечание:
 *  путь подставляется без всякого экранирования. Пробелы в пути не допускаются.
 */
/**
 * @param object $workers
 * @return boolean|unknown
 */
function getWorkersStatus( $workers )
{
    global $config, $gearman, $server, $port;
    if (false === $sh = @fsockopen( $server, $port, $errno, $errstr, 10 ))
    {
        fwrite( STDERR, sprintf( '    Unable to connect to gearman: %s: %s', $errno, $errstr ) . "\n" );
        return false;
    }
    $aOut=array();
    fwrite( $sh, "status\n" );
    $aOut[] = sprintf("%-22s    %-12s    %10s    %-10s | \n",'Queue Name','| Worker Available','| Jobs Waiting','| Jobs Running ');
    $aOut[] = sprintf("%s\n",str_repeat('_', strlen($aOut[0])-2 ));

    while ( (!feof( $sh )) && (".\n" !== $line = fgets( $sh )) )
    {
        preg_match_all('/[^\s]+/i', $line,$aM);
        $aM=$aM[0];
        $aOut[]=sprintf("%-22s    | %-12s        | %-8s        | %-7s       | \n",$aM[0],$aM[3],$aM[1],$aM[2]);
    }
    foreach ($aOut as $v) {
        echo $v;
    }
    fclose( $sh );
    echo "\n";
    return true;
}

$base = (isset($argv[1]) && preg_match('/\//i', $argv[1]))? $argv[1] : '/var/www/';
exec( "find ".$base." -name 'config.php'", $aRez );

$aCacheServers=array();
$aCachePath=array();
echo "\n";

foreach( $aRez as $path )
{
    include $path;
    $aM=array();
    if (isset( $config['gearman']['servers'] ))
    {
        preg_match('/.+(background|frontend)/i', $path,$aM);
        $key=preg_replace('/(background|frontend)\/settings\/config.php/i', '',$path);
        $aCachePath[$key][$aM[1]]=$config['gearman']['servers'];
        if(isset($aCacheServers[$config['gearman']['servers']]))
        {
            continue;
        }
        $aCacheServers[$config['gearman']['servers']]=true;
        list( $server, $port ) = explode( ':', $config['gearman']['servers'] );
        echo 'gearman server :' . $config['gearman']['servers'] . "\n";
        try
        {
            $gearman = new GearmanClient();
            $gearman->addServer( $server, $port );
            // find running workers and ask them to terminate
            $workers = array();
            $workers = getWorkersStatus( $workers );
            if($workers)
            {
                echo '    ' . $config['gearman']['servers'] . " is running... \n\n";
            }else{
                echo '    ' . $config['gearman']['servers'] . " NOT running... \n\n";
            }
        } catch ( Exception $e )
        {
            var_dump( $e,'try error' );
        }
    }
    unset( $config );
}
echo "\n";
$aUniqueServer=array();
if($aCachePath)
{
    foreach ($aCachePath as $key=>$a) {
        $aTmp = array_values($a);
        if($aTmp[0]!=$aTmp[1])
        {
            echo "=========================\n";
            echo "Error in gearman config : {$key} !!!\n";
            var_dump($aCachePath[$key]);
            echo "=========================\n";
        }
        echo $key."\n";
        foreach ($a as $k=>$v) {
            echo '  '.$k.'    '.$v."\n";
            $aUniqueServer[$v]=isset($aUniqueServer[$v])?$aUniqueServer[$v]+1:0;
        }
    }
}
echo "\n";
if ($aUniqueServer)
{
    foreach ($aUniqueServer as $k=>$v) {
        if($v>1)
        {
            echo "=============================================================\n";
            echo "Error!!! Gearman must be running one for deployment: {$k} !!!\n";
            echo "=============================================================\n";
        }
    }
}
echo "\n";