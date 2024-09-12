<?php
require_once dirname(__FILE__).'/../settings/config.php';

/**
 * cleanLog
 */
function cleanLog()
{
    global $config;
    $files = glob(realpath($config['path']['logs']).'/pid/*.txt');
    foreach($files as $file)
    {
        if(is_file($file))
        {
            unlink($file);
        }
    }
    if(file_exists(dirname(__FILE__).'/../workers.txt'))
    {
        unlink(dirname(__FILE__).'/../workers.txt');
    }
}
/**
 * @param string $workers
 * @return string
 */
function getWorkersStatus($workers)
{
    global $config,$gearman,$server,$port;

    if (false === $sh = fsockopen( $server, $port, $errno, $errstr, 10 ))
    {
        fwrite( STDERR, sprintf( 'Unable to connect to gearman: %s: %s', $errno, $errstr ) . "\n" );
        exit( 1 );
    }
    fwrite( $sh, "status\n" );
    while ( (!feof( $sh )) && (".\n" !== $line = fgets( $sh )) )
    {
        if (preg_match( '/^('.(implode('|', array_keys($config['workers']['workerAvailable']))) .')\s+\d+\s+\d+\s+(\d+)/i', $line, $match )
                && isset($match[2]) && $match[2]>0
        ){
            fwrite( STDOUT, sprintf( '[%s] UP %s', date( 'H:i:s' ), $match[1] ) . "\n" );
            for($i=0;$i<$match[2];$i++){
                //$workers[$match[1]] = $gearman->doHighBackground( $match[1], 'terminate',$match[1] ); //, $match[1]
                $workers[] = $gearman->doHighBackground( $match[1], 'terminate',$match[1].'_'.$i ); //, $match[1]
            }
        }elseif(isset($match[2]) && $match[2]==0)
        {
            //unset($workers[$match[1]]);
            $x=array_shift($workers);
            if($x)
            {
                echo "{$x} is DOWN\n";
            }
        }
    }
    fclose( $sh );
    return $workers;
}

// get status of gearman server
list($server,$port) = explode(':', $config['gearman']['servers']);
$workers = array();
$gearman = new GearmanClient();
$gearman->addServer($server,$port);

// find running workers and ask them to terminate
$workers = array();
$workers = getWorkersStatus($workers);

if(!$workers)
{
    echo "Nothing to stop\n";
    cleanLog();
    exit(0);
}else
{
    foreach ($workers as $v)
    {
        fwrite( STDOUT, sprintf( '[%s] info %s', date( 'H:i:s' ), $v ) . "\n" );
    }
}
// callback to update the list of who is still down
$gearman->setStatusCallback( function ( GearmanTask $task, $context ) use( &$workers )
{
    if (!$task->isKnown())
    {
        unset( $workers[$context] );
        fwrite( STDOUT, sprintf( '[%s] DOWN %s', date( 'H:i:s' ), $context ) . "\n" );
    }
} );

$loop = 0;
// poll gearman about the termination jobs
do
{
    foreach ( $workers as $worker => $handle )
    {
        $gearman->addTaskStatus( $handle, $worker );
    }
    $gearman->runTasks();
    if ((0 == ++$loop % 20) && ($workers))
    {
        // remind who is still down every 10 seconds
        fwrite( STDOUT, sprintf( '[%s] waiting for: %s', date( 'H:i:s' ), implode( ' ', array_keys( $workers ) ) ) . "\n" );
    }
    usleep( 500000 );
} while ( $workers );

cleanLog();