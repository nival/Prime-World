<?php
$root = dirname(__FILE__);
$root.= '/../';
require $root.'settings/config.php';
$worker = new GearmanWorker();
$worker->addServers($config['gearman']['servers']);
$worker->addFunction('vkontaktePost', 'vkontaktePost');
while (1)
{
    echo "Wait...\n";
    $ret= $worker->work();
}

function vkontaktePost($job)
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
            $vkontakteUsers = new VkontakteUsers();
            $response = $vkontakteUsers->post($data['access_token'],$data['postTo'],$data['data']);
            $message = false;
            $type = Sa_Log::INFO;
            if(isset($response['error']))
            {
                $message = 'VkontaktePost : Connection error.'.$response['error']."\nMessage data: "._generateMessageDataString($data['data']);
            }
            else
            {
                $post = $response['result'];
                if(isset($post->response->processing) && $post->response->processing == 1)
                {
                    if($config['log_level'] == 'info')
                    {
                        $message = 'VkontaktePost : Message with attachments processing'.". \nMessage data: "._generateMessageDataString($data['data']);
                    }
                }
                elseif(isset($post->response->post_id) && $post->response->post_id)
                {
                    if($config['log_level'] == 'info')
                    {
                        $message = 'VkontaktePost : Message posted to snuid = '.$data['postTo'].' profile message id = '.$post->response->post_id .". \nMessage data: "._generateMessageDataString($data['data']);
                    }
                }
                else
                {
                    if($config['log_level'] == 'info' || $config['log_level'] == 'error')
                    {
                        if(isset($post->error))
                        {
                            $message = 'VkontaktePost : Message not posted to snuid = '.$data['postTo'].' profile. Error: '.$post->error->error_msg.". \nMessage data: "._generateMessageDataString($data['data']);
                            $type = Sa_Log::ERR;
                        }
                        else
                        {
                            $message = 'VkontaktePost : Message not posted to snuid = '.$data['postTo'].' profile. Error: Unknown error occurred'.". \nMessage data: "._generateMessageDataString($data['data']);
                            $type = Sa_Log::ERR;
                        }
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
                    'worker' => 'VkontaktePost',
                );
                $client->doBackground('logBackground', serialize($data));
            }
        }
    }
    catch (Exception $e)
    {
        $message = "Vkontakte : Error message:".$e->getMessage()."\nTrace:".$e->getTraceAsString();
        $client= new GearmanClient();
        $client->addServers($config['gearman']['servers']);
        $data = array(
            'message' => $message,
            'type' => Sa_Log::CRIT,
            'worker' => 'VkontaktePost',
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