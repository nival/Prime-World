<?php
require_once dirname(__FILE__).'/../settings/config.php';
$paths = implode(PATH_SEPARATOR, array(
	$config['path']['library'],
	implode(PATH_SEPARATOR, $config['path']['models'])
));
set_include_path($paths);
require_once dirname(__FILE__).'/../Initializer.php';
require_once dirname(__FILE__).'/../../../library/Sa/Log.php';
require_once dirname(__FILE__).'/workerHelpers.php';

// ought to be unique within the server's workforce
$context = array(
	'id' => 'refreshInfo',
	'pid' => getmypid(),
	'terminate' => false
);
pcntl_signal( SIGTERM, function () use( &$context )
{
	fwrite( STDOUT, sprintf( '[%s] SIGTERM %s', date( 'H:i:s' ), $context['id'] ) . "\n" );
	$context['terminate'] = true;
} );
pcntl_signal( SIGHUP, function () use( &$context )
{
	fwrite( STDOUT, sprintf( '[%s] SIGHUP %s', date( 'H:i:s' ), $context['id'] ) . "\n" );
	$context['terminate'] = true;
} );
pcntl_signal( SIGUSR1, function () use( &$context )
{
	fwrite( STDOUT, sprintf( '[%s] SIGUSR1 %s', date( 'H:i:s' ), $context['id'] ) . "\n" );
	$context['terminate'] = true;
} );

$worker = new GearmanWorker();
$worker->addOptions( GEARMAN_WORKER_NON_BLOCKING );
// maximum time that gearman will block from userspace code

$sFunctionWorker = 'refreshInfo';
$worker->setTimeout( 2500 );
$worker->addServers($config['gearman']['servers']);
$worker->addFunction($sFunctionWorker, $sFunctionWorker, $context);

$path=realpath($config['path']['logs']).'/pid/'.$context['pid'] .'-state.txt';
file_put_contents($path, serialize(array($context['pid']=>array('state'=>'wait','t'=>date("Y-m-d H:i:s"),'u'=>time(),'name'=>$sFunctionWorker))), LOCK_EX);

fwrite( STDOUT, sprintf( '[%s] READY %s (%d)', date( 'H:i:s' ), $context['id'], $context['pid'] ) . "\n" );

$iCountSleep=1;
while ( (!$context['terminate'])
	&& (@$worker->work() # GearmanWorker::work(): (null)
		|| (GEARMAN_IO_WAIT == $worker->returnCode())
		|| (GEARMAN_NO_JOBS == $worker->returnCode())
		|| (GEARMAN_TIMEOUT == $worker->returnCode())
	)
){
	// (PHP 5 >= 5.3.0) declare(ticks = 1); -> pcntl_signal_dispatch(). If you are running PHP as CLI and as a "daemon" (i.e. in a loop), this function
	// must be called in each loop  to check if new signals are waiting dispatching.
	pcntl_signal_dispatch();

	if (GEARMAN_SUCCESS == $worker->returnCode())
	{
		// reset count
		$iCountSleep=1;
		$aWorkersPID = unserialize(file_get_contents($path));
		file_put_contents($path, serialize(array($context['pid']=>array('state'=>'wait','t'=>date("Y-m-d H:i:s"),'u'=>time(),'name'=>$sFunctionWorker))), LOCK_EX);
		if(isset($aWorkersPID[$context['pid']]) && $aWorkersPID[$context['pid']]=="no_more")
		{
			sleep(100000000000);
		}
		continue;
	}
	echo "[ " . date("Y-m-d H:i:s") . " ] Waiting for next job...\n";
	if (!@$worker->wait())
	{
		$iCountSleep++;
		$iCountSleep = $iCountSleep > 60 ? 1 : $iCountSleep;
		if ($worker->returnCode() == GEARMAN_NO_ACTIVE_FDS)
		{
			# We are not connected to any servers, so wait a bit before trying to reconnect.
			echo "Not connected to any servers. Retrying ".str_repeat('.', $iCountSleep)." \n";
			sleep($iCountSleep);
			continue;
		}
		elseif ($worker->returnCode() == GEARMAN_TIMEOUT)
		{
			echo "Timeout. Retrying \n";
			sleep($iCountSleep);
			continue;
		}
		break;
	}
	echo "return code " . $worker->returnCode() . "\n";
}

// $worker->unregisterAll();
echo 'unregister worker:[' . $context['id']."]\n";
$worker->unregister($context['id']);
fwrite( STDOUT, sprintf( '[%s] EXIT %s:pid[%s]', date( 'H:i:s' ), $context['id'], $context['pid'] ) . "\n" );