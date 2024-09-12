<?php
require_once dirname(__FILE__).'/../settings/config.php';
$paths = implode(PATH_SEPARATOR, array(
    $config['path']['library'],
    implode(PATH_SEPARATOR, $config['path']['models'])
));
set_include_path($paths);
require_once dirname(__FILE__).'/../Initializer.php';
require_once dirname(__FILE__).'/../../../library/Sa/Log.php';


/**
 * @param GearmanWorker $job
 * @return void|unknown|string|Ambigous <>|boolean
 */
function vkontakteRefreshInfo($job)
{
    global $config,$WORKER_NAME,$SNO;

    if($config['log_level'] == 'info')
    {
        $time_start = microtime(true);
    }

    echo strftime("[%F %T] Work...\n", time());
    try
    {
        $message = false;
        $type = Sa_Log::INFO;

        $initializer = new Initializer();
        $initializer->initialize(array('config' => $config));
        $workload= $job->workload();
        // array('_id','sntoken',)
        $data = $workload ? unserialize($workload) : false;
        if(!isset($data['_id'])
            || ($auid = $data['_id'])==false
        ){
            return;
        }

        $usersModel = new Users();
        $user = $usersModel->getByAuid($auid);
        if(!$user
            && ($config['log_level'] == 'info' || $config['log_level'] == 'error')
        ){
            Assistant::workerLogMessage(
                $WORKER_NAME,
                $SNO.' account for user with auid = '.$auid.'not found.',
                Sa_Log::ERR
            );
            return;
        }

        $oSnUsers = new $SNO();
        $sntoken = $user['vk']['sntoken'];
        if(isset($data['sntoken']) && $sntoken != $data['sntoken'])
        {
            $validToken = $oSnUsers->validateToken(NULL, $data['sntoken']);
            if(isset($validToken['error']))
            {
                Assistant::workerLogMessage($WORKER_NAME,
                    $SNO.' token validation error: '.$validToken['message'].' snuid='.$user['vk']['snuid'],
                    Sa_Log::ERR
                );
                return;
            }
            $sntoken = $data['sntoken'];
        }

        $userFullInfo = $oSnUsers->requestFullUserData($user['vk']['snuid'],$sntoken,NULL,false);
        if(!isset($userFullInfo['error']))
        {
            $friends = isset($userFullInfo['friends'])?$userFullInfo['friends']:false;
            $snid = isset($userFullInfo['snid'])?$userFullInfo['snid']:false;
            unset($userFullInfo['friends'],$userFullInfo['snid']);
            $udiff = Assistant::diffUsers($user,$userFullInfo);

            if(!($udiff) || $usersModel->edit($auid, $udiff))
            {
                $friendsModel = new Friends();
                #####
                # The first - collect all friends changes
                $snFriends = iterator_to_array($friendsModel->getSnFriends($snid, $auid));
                $oldSnFriendsRecordIds = array_map(
                    function($f){return $f['_id'];},
                    $snFriends
                );
                $newSnFriendsRecordIds = array_map(
                    function($f) use ($snid, $auid) {return $snid.'_'.$auid.'_'.$f['snuid'];},
                    $friends['friends_data']
                );
                # now compare the lists
                # select all of `sn_friends` which already aren't our friends by the SN - and remove 'em
                $toRemove = array_diff($oldSnFriendsRecordIds, $newSnFriendsRecordIds);
                # select all friends from SN which aren't listed in `sn_friends` - and add 'em
                $toAdd = array_diff($newSnFriendsRecordIds, $oldSnFriendsRecordIds);
                $hasPwgFriends = $newFriendsAuids = $newFriendsData = false;

                if ($toAdd)
                {
                    # take snuid parts from `sn_friends` record _ids
                    $snuids = array_map(
                        function($id){$a=explode('_', $id); return $a[2];},
                        $toAdd
                    );
                    # filter from friend_data all records correponding to $toAdd list
                    $newFriendsData = array_filter(
                        $friends['friends_data'],
                        function($d) use ($snuids) {return in_array($d['snuid'],$snuids);}
                    );
                    # take friends selected into $toAdd and add 'em to `friends` (if they aren't there) - have to find their auids for it
                    $auids = array_map(
                        function ($f){return $f['_id'];},
                        iterator_to_array($usersModel->getSnUsers($snid, $snuids, array('_id')))
                    );
                    # 'pwg' friends who also become friends by some real SN should have snid to be overriden
                    $hasPwgFriends = $friendsModel->hasPwgFriends($auid);
                    # also in could simplify the next question: whom to add to `friends`
                    $currentFriendsAuids = $hasPwgFriends
                        ? $friendsModel->getNoguildListByAuid($auid)
                        : $friendsModel->getAuidListByAuid($auid);
                    $newFriendsAuids = array_diff($auids, $currentFriendsAuids);
                }
                #####
                # The second - write 'em in safer order
                if ($toRemove)
                {
                    $friendsModel->removeSnFriendsList($toRemove); # NOTE: removes only one direction: from $auid to it's friends!
                }
                # it's safe to crash here - additions will be done on the next update
                if ($toAdd)
                {
                    # override 'pwg' friends who are in $friends['auids'] too
                    if ($hasPwgFriends)
                    {
                        $friendsModel->overridePwgSn($auid, $auids, $snid);
                    }
                    # it's safe to crach here, we'll just add all other friends next time
                    # since the aren't added to `sn_friends` yet
                    if ($newFriendsAuids)
                    {
                        foreach ($newFriendsAuids as $friendAuid)
                        {
                            $friendsModel->add($auid, $friendAuid, $snid);
                        }
                    }
                    # it's safe to crash here we'll just fix `sn_friends` next time
                    if ($newFriendsData)
                    {
                        $friendsModel->addSnFriends($snid,$auid,$newFriendsData);
                    }
                }
            }
            if (!empty($config['refresh_notify_url']))
            {
                $ch = Assistant::prepare_request($config['refresh_notify_url'].'?action=refresh&auid='.$data['_id'], array());
                curl_exec($ch);
                curl_close($ch);
            }
            if($config['log_level'] == 'info')
            {
                $message .= 'Info refresh for user with auid = '.$data['_id'].' complete. Time:['. (microtime(true) - $time_start)."]\n";
            }
        }
        elseif($config['log_level'] == 'info' || $config['log_level'] == 'error')
        {
            $message .= $SNO.' error: '.$userFullInfo['message']."\n";
            $type = Sa_Log::ERR;
        }
        if($message)
        {
            Assistant::workerLogMessage($WORKER_NAME, $message, $type);
        }
    }
    catch (Exception $e)
    {
        $message .= $WORKER_NAME." : Error message:".$e->getMessage()."\nTrace:".$e->getTraceAsString()."\n";
        Assistant::workerLogMessage($WORKER_NAME, $message, Sa_Log::CRIT);
    }
}

$SNO = 'VkontakteUsers';
$WORKER_NAME = 'vkontakteRefreshInfo';

$worker = new GearmanWorker();
$worker->addServers($config['gearman']['servers']);
$worker->addFunction($WORKER_NAME, $WORKER_NAME);

while (1)
{
    echo "Wait...\n";
    $ret= $worker->work();
}