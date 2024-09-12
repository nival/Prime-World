<?php
/**
 * run as daemon
 */
require dirname(__FILE__).'/settings/config.php';

$aPid=array();
$aPidFiles = glob(realpath($config['path']['logs']).'/pid/*-state.txt');
while (1)
{
	if($aPidFiles)
	{
		foreach ($aPidFiles as $path)
		{
			$aTmp =  unserialize(file_get_contents($path));
			$sKey = key($aTmp);
			if(isset($aPid[$sKey]))
			{
				echo ($aPid[$sKey]['u']-$aTmp[$sKey]['u'])."\n"; // - это хорошо / + плохо
				echo (time()-$aTmp[$sKey]['u'])."\n"; // - это хорошо / + плохо
			}
			$aPid[$sKey]=$aTmp[$sKey];
		}
	}
	var_dump($aPid);
	sleep(10);
}