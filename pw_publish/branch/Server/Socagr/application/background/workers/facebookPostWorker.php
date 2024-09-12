<?php
$root = dirname(__FILE__);
$root.= '/../';
require $root.'settings/config.php';
$worker = new GearmanWorker();
$worker->addServers($config['gearman']['servers']);
$worker->addFunction('facebookPost', 'facebookPost');
while (1)
{
    echo "Wait...\n";
    $ret= $worker->work();
}

function facebookPost($job)
{
    echo "Work...\n";
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
        if(isset($data['access_token']) && isset($data['postTo']) && isset($data['data']))
        {
            $facebookUsers = new FacebookUsers();
            $post = $facebookUsers->post($data['access_token'],$data['postTo'],$data['data']);
            $message = false;
            $type = Sa_Log::INFO;
            if(isset($post->id))
            {
                if($config['log_level'] == 'info')
                {
                    $message = 'FacebookPost : Message posted to snuid = '.$data['postTo'].' profile message id = '.$post->id .". \nMessage data: "._generateMessageDataString($data['data']);
                }
            }
            else
            {
                if($config['log_level'] == 'info' || $config['log_level'] == 'error')
                {
                    if(isset($post->error))
                    {
                        $message = 'FacebookPost : Message not posted to snuid = '.$data['postTo'].' profile. Error: '.$post->error->message.". \nMessage data: "._generateMessageDataString($data['data']);
                        $type = Sa_Log::ERR;
                    }
                }
            }
            if($message)
            {
                $client= new GearmanClient();
                $client->addServers($config['gearman']['servers']);
                $data = array(
                    'message' => $message,
                    'type' => $type,
                    'worker' => 'FacebookPost',
                );
                $client->doBackground('logBackground', serialize($data));
            }
        }
    }
    catch (Exception $e)
    {
        $message = "FacebookPost : Error message:".$e->getMessage()."\nTrace:".$e->getTraceAsString();
        $client= new GearmanClient();
        $client->addServers($config['gearman']['servers']);
        $data = array(
            'message' => $message,
            'type' => Sa_Log::CRIT,
            'worker' => 'FacebookPost',
        );
        $client->doBackground('logBackground', serialize($data));
    }
}

function _generateMessageDataString($data)
{
    $dataStr = '';
    foreach ($data as $paramName => $paramValue)
    {
        $dataStr .= $paramName.'='.$paramValue.'&';
    }
    $dataStr = rtrim($dataStr,'&');
    return $dataStr;
}
?>