<?php
$root = dirname(__FILE__);
$root .= '/../';
require $root . 'settings/config.php';
$worker = new GearmanWorker();
$worker->addServers($config['gearman']['servers']);
$worker->addFunction('draugasRefreshInfo', 'draugasRefreshInfo');
while (1) {
    echo "Wait draugasRefreshInfo\n";
    $ret = $worker->work();
}

function draugasRefreshInfo($job)
{
    echo "Work draugasRefreshInfo\n";
    try {
        $root = dirname(__FILE__);
        $root .= '/../';
        require $root . 'settings/config.php';
        $paths = implode(PATH_SEPARATOR, array(
            $config['path']['library'],
            implode(PATH_SEPARATOR, $config['path']['models'])
        ));
        set_include_path($paths);
        require_once $root . 'application/background/Initializer.php';
        $initializer = new Initializer();
        $initializer->initialize(array('config' => $config));
        $workload = $job->workload();
        $data = unserialize($workload);
        if (isset($data['_id'])) {
            $message = false;
            $type = Sa_Log::INFO;
            $usersModel = new Users();
            $user = $usersModel->getByAuid($data['_id'], array('dlt.snuid', 'dlt.sntoken'));
            if ($user) {
                $draugasUsers = new DraugasUsers();
                if (isset($data['sntoken']) && isset($data['snuid'])) {
                    $validToken = $draugasUsers->validateToken($data['snuid'], $data['sntoken']);
                    if (!isset($validToken['error'])) {
                        if ($config['log_level'] == 'info') {
                            $message = 'DraugasRefreshInfo : validate Infî for user with auid = ' . $data['_id'];
                            //Assistant::workerLogMessage('DraugasRefreshInfo', $message, $type);
                        }
                    } else {
                        $message = 'DraugasRefreshInfo : ' . $validToken['message'] . ' snuid=' . $data['snuid'];
                        $type = Sa_Log::ERR;
                    }
                }
            } else {
                if ($config['log_level'] == 'info' || $config['log_level'] == 'error') {
                    $message = 'DraugasRefreshInfo : Draugas account for user with auid = ' . $data['_id'] . 'not found.';
                    $type = Sa_Log::ERR;
                }
            }
            if ($message) {
                Assistant::workerLogMessage('DraugasRefreshInfo', $message, $type);
            }
        }
    } catch (Exception $e) {
        $message = "DraugasRefreshInfo : Error message:" . $e->getMessage() . "\nTrace:" . $e->getTraceAsString();
        Assistant::workerLogMessage('DraugasRefreshInfo', $message, Sa_Log::CRIT);
    }
}

?>
