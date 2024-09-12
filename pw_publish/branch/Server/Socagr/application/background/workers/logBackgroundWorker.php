<?php
$root = dirname(__FILE__);
$root.= '/../';
require $root.'settings/config.php';
$worker = new GearmanWorker();
$worker->addServers($config['gearman']['servers']);
$worker->addFunction('logBackground', 'logBackground');
while (1)
{
    echo "Wait...\n";
    $ret= $worker->work();
}

function logBackground($job)
{
    echo "Work...\n";
    global $config;
    try
    {
        $root = dirname(__FILE__);
        $root.= '/../';
        require $root.'settings/config.php';
        $paths = implode(PATH_SEPARATOR, array(
            $config['path']['library'],
            implode(PATH_SEPARATOR, $config['path']['models'])
        ));
        set_include_path($paths);
        require_once $root.'application/background/Initializer.php';
        $initializer = new Initializer();
        $initializer->initialize(array('config' => $config));
        $workload= $job->workload();
        $data = unserialize($workload);
        if(isset($data['message']) && isset($data['worker']) && isset($data['type']))
        {
            $version = $config['version'];
            $date = date("Y.m.d");
            $fileNamePatern = $data['worker'].'-'.$version.'-'.$date;
            $logFileArray = glob($config['path']['logs'].$fileNamePatern."-*-sa.txt", GLOB_NOSORT);
            if(count($logFileArray))
            {
                $logFile = $logFileArray[0];
            }
            else
            {
                //$logFile = $config['path']['logs'].$data['worker'].'-'.$version.'-'.date("Y.m.d-H.i.s.u").'-sa.txt';
                $logFile = $config['path']['logs'].$data['worker'].'-'.$version.'-'.$date.'-sa.txt';
            }
            $loger =  new Sa_Log();
            $stream = @fopen($logFile, 'a+', false);
            $loger->addWriter(new Zend_Log_Writer_Stream($stream));
            $loger->log($data['message'], $data['type']);
            $loger->__destruct();
        }
    }
    catch (Exception $e)
    {
        echo $e->getTraceAsString().'\n';
    }

}
?>