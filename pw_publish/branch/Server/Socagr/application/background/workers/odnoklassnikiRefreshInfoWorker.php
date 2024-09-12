<?php
$root = dirname(__FILE__);
$root.= '/../';
require $root.'settings/config.php';
$worker = new GearmanWorker();
$worker->addServers($config['gearman']['servers']);
$worker->addFunction('odnoklassnikiRefreshInfo', 'odnoklassnikiRefreshInfo');
while (1)
{
    echo "Wait...\n";
    $ret= $worker->work();
}

function odnoklassnikiRefreshInfo($job)
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
        if(isset($data['_id']))
        {
            $message = false;
            $type = Sa_Log::INFO;
            $usersModel = new Users();
            $user = $usersModel->getByAuid($data['_id'],array('ok.snuid','ok.sntoken','ok.snrefresh_token','ok.dt_request_sntoken','ok.dt_request_snrefresh_token'));
            if($user)
            {
                $odnoklassnikiUsers = new OdnoklassnikiUsers();
                $sntoken = false;
                $snRefreshToken = false;
                $dtRequestSnToken = $dtRequestSnRefreshToken = time();

                if($data['sntoken'] == $user['ok']['sntoken'])
                {
                    if(isset($user['ok']['dt_request_sntoken']) && (time() - $user['ok']['dt_request_sntoken']) > 1800)
                    {
                        if(isset($user['ok']['dt_request_snrefresh_token']) && (time() - $user['ok']['dt_request_snrefresh_token']) < 2592000)
                        {
                            $accessToken = $odnoklassnikiUsers->refreshToken($user['ok']['snrefresh_token']);
                            if(is_array($accessToken) && isset($accessToken['error']))
                            {
                                $message = 'OdnoklassnikiRefreshInfo : '.$accessToken['message'].' snuid='.$user['ok']['snuid'];
                                $type = Sa_Log::ERR;
                            }
                            else
                            {
                                $sntoken =$accessToken;
                                $snRefreshToken = $user['ok']['snrefresh_token'];
                                $dtRequestSnRefreshToken = $user['ok']['dt_request_snrefresh_token'];
                                echo 'Refresh token used.';
                            }
                        }
                        else
                        {
                            $message = 'OdnoklassnikiRefreshInfo : Refresh token for user auid='.$data['_id'].',snuid='.$user['ok']['snuid'].' expired.';
                            $type = Sa_Log::ERR;
                        }
                    }
                    else
                    {
                        $sntoken = $user['ok']['sntoken'];
                        $snRefreshToken = $user['ok']['snrefresh_token'];
                        $dtRequestSnRefreshToken = $user['ok']['dt_request_snrefresh_token'];
                        $dtRequestSnToken = $user['ok']['dt_request_sntoken'];
                        echo 'Access token used.';
                    }
                }
                else
                {
                    $validToken = $odnoklassnikiUsers->validateToken(NULL, $data['sntoken']);
                    if(!isset($validToken['error']))
                    {
                        $sntoken = $data['sntoken'];
                        $snRefreshToken = $data['snrefresh_token'];
                    }
                    else
                    {
                        $message = 'OdnoklassnikiRefreshInfo : '.$validToken['message'].' snuid='.$user['ok']['snuid'];
                        $type = Sa_Log::ERR;
                    }
                    echo 'Validate new token.';
                }
                if($sntoken && $snRefreshToken)
                {
                    $userFullInfo = $odnoklassnikiUsers->requestFullUserData($user['ok']['snuid'],$sntoken,$snRefreshToken);
                    if(!isset($userFullInfo['error']))
                    {
                        $friends = $userFullInfo['friends'];
                        $snid = $userFullInfo['snid'];
                        unset($userFullInfo['friends']);
                        unset($userFullInfo['snid']);
                        unset($userFullInfo['dt_last_login']);
                        unset($userFullInfo['dt_register']);
                        $userFullInfo['ok']['dt_request_snrefresh_token'] = $dtRequestSnRefreshToken;
                        $userFullInfo['ok']['dt_request_sntoken'] = $dtRequestSnToken;
                        $deletedSnuids = array();
                        $deletedAuids = array();

                        if($usersModel->edit($data['_id'],$userFullInfo))
                        {
                            $friendsModel = new Friends();
                            $deletedSnFriends = $friendsModel->getSnFriendsInfo($snid,$data['_id'],array(2));
                            foreach ($deletedSnFriends as $deletedSnFriend)
                            {
                                $deletedUser = $usersModel->getSnUser($snid,$deletedSnFriend['snuid'],array('_id'));
                                if($deletedUser)
                                {
                                    $deletedSnuids[] = $deletedSnFriend['snuid'];
                                    $deletedAuids[] = $deletedUser['_id'];
                                }
                            }
                            if($friendsModel->removeSnFriends($snid,$data['_id']))
                            {
                                if(isset($friends['friends_data']) && count($friends['friends_data']) > 0)
                                {
                                    if($friendsModel->addSnFriends($snid,$data['_id'],$friends['friends_data']))
                                    {
                                        # Add new OK friends as friends in game.
                                        if(isset($friends['auids']) && count($friends['auids']) > 0)
                                        {
                                            $currentFriendsAuids = $friendsModel->getAuidListByAuid($data['_id']);
                                            $friendsToAdd = array_diff($friends['auids'],$currentFriendsAuids,$deletedAuids);
                                            foreach ($friendsToAdd as $friendAuid)
                                            {
                                                $friendsModel->add($data['_id'],$friendAuid,$snid);
                                            }
                                            # override 'pwg' friends who are in $friends['auids'] too
                                            $friendsModel->overridePwgSn($data['_id'], $friends['auids'], $snid);
                                        }
                                        # Mark me as used=1 for all my mutual friends from Facebook
                                        # (Who had used=2 will be reseted later.)
                                        if(isset($friends['friend_records_ids']) && count($friends['friend_records_ids']) > 0)
                                        {
                                            $friendsModel->markUsed($friends['friend_records_ids'],1);
                                        }
                                            # Restore used=2 flags for sn_friends.
                                        if(count($deletedSnuids) > 0)
                                        {
                                            $deletedRecords = array();
                                            foreach ($deletedAuids as $deletedAuid)
                                            {
                                                $deletedRecords[] = $snid.'_'.$deletedAuid.'_'.$user['ok']['snuid'];
                                            }
                                            foreach ($deletedSnuids as $deletedSnuid)
                                            {
                                                $deletedRecords[] = $snid.'_'.$user['_id'].'_'.$deletedSnuid;
                                            }
                                            if(count($deletedRecords) > 0)
                                            {
                                                $friendsModel->markUsed($deletedRecords,2);
                                            }
                                        }
                                    }
                                }
                            }
                        }
                                $ch = curl_init();
                            curl_setopt($ch, CURLOPT_URL, $config['refresh_notify_url'].'?action=refresh&auid='.$data['_id']);
                            curl_setopt($ch, CURLOPT_HEADER, 0);
                            curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
                            curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, FALSE);
                            curl_exec($ch);
                            curl_close($ch);
                                if($config['log_level'] == 'info')
                            {
                                $message = 'OdnoklassnikiRefreshInfo : Info refresh for user with auid = '.$data['_id'].' complete.';
                            }
                        }
                        else
                        {
                            if($config['log_level'] == 'info' || $config['log_level'] == 'error')
                        {
                            $message = 'OdnoklassnikiRefreshInfo : odnoklassniki error: '.$userFullInfo['message'];
                            $type = Sa_Log::ERR;
                        }
                    }
                }
            }
            else
            {
                if($config['log_level'] == 'info' || $config['log_level'] == 'error')
                {
                    $message = 'OdnoklassnikiRefreshInfo : Odnoklassniki account for user with auid = '.$data['_id'].'not found.';
                    $type = Sa_Log::ERR;
                }
            }
            if($message)
            {
                $client= new GearmanClient();
                $client->addServers($config['gearman']['servers']);
                $data = array(
                    'message' => $message,
                    'type' => $type,
                    'worker' => 'OdnoklassnikiRefreshInfo',
                );
                $client->doBackground('logBackground', serialize($data));
            }
        }
    }
    catch (Exception $e)
    {
        $message = "OdnoklassnikiRefreshInfo : Error message:".$e->getMessage()."\nTrace:".$e->getTraceAsString();
        $client= new GearmanClient();
        $client->addServers($config['gearman']['servers']);
        $data = array(
            'message' => $message,
            'type' => Sa_Log::CRIT,
            'worker' => 'OdnoklassnikiRefreshInfo',
        );
        $client->doBackground('logBackground', serialize($data));
    }
}
?>
