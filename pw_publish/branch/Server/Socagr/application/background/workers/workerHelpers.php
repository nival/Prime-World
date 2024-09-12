<?php
/**
 * @name refreshInfo
 * @param GearmanWorker $job
 * @param array $context
 * @return void|unknown|string|Ambigous <>|boolean
 */
function refreshInfo($job,$context)
{
    global $config;

    $workload = $job->workload();
    if($workload=='terminate')
    {
         posix_kill( $context['pid'], SIGTERM ); // exec(sprintf('/bin/kill -s TERM %d', $context['pid']));
         return;
    }

    $path=realpath($config['path']['logs']).'/pid/'.$context['pid'] .'-state.txt';

    if(file_exists($path)
        && ($sPidFile = file_get_contents($path)) == true
    ){
        $aWorkersPID = unserialize($sPidFile);
        if(isset($aWorkersPID[$context['pid']]) && $aWorkersPID[$context['pid']]['state']=='no_more')
        {
            return;
        }
    }

    file_put_contents($path, serialize(array($context['pid']=>array('state'=>'busy','t'=>date("Y-m-d H:i:s"),'u'=>time(),'name'=>'refreshInfo'))), LOCK_EX);

    $time_start = microtime(true);
    echo strftime("[%F %T] PID:[{$context['pid']}] Work...\n", time());
    try
    {
        $message = false;
        $type = Sa_Log::INFO;

        $initializer = new Initializer();
        $initializer->initialize(array('config' => $config));
        if(is_object($job))
        {
            // array('_id','sntoken')
            $data = $workload ? unserialize($workload) : false;
        }else
        {
            $data = $job;
        }
        if(!isset($data['_id'])
            || ($auid = $data['_id'])==false
            || !isset($data['sn'])
        ){
            if($config['log_level'] == 'info')
            {
                Assistant::workerLogMessage(
                    'error',
                    'error input parametr Data:['.unserialize($data).']. Time:['. (microtime(true) - $time_start).']',
                    Sa_Log::ERR
                );
            }
            return;
        }

        $SN = $data['sn'];
        if(!isset($config['workers']['access_sn'][$SN])
            || $config['workers']['access_sn'][$SN]==false
        ){
            Assistant::workerLogMessage(
                'error',
                'SN ['.$SN.'] is off :['.serialize($workload).']. Time:['. (microtime(true) - $time_start).']',
                Sa_Log::ERR
            );
            return;
        }

        // worker for fb, vk, st, ok, ae, mru
        $usersModel = new Users();
        switch ($SN)
        {
            // no snrefresh_token
            case 'fb':
                $SNO = 'FacebookUsers';
                $WORKER_NAME='facebookRefreshInfo';
                $user = $usersModel->getByAuid($auid,array($SN.'.snuid',$SN.'.sntoken',$SN.'.sntoken_expire'));
            break;
            case 'vk':
                $SNO = 'VkontakteUsers';
                $WORKER_NAME='vkontakteRefreshInfo';
                $user = $usersModel->getByAuid($auid,array($SN.'.snuid',$SN.'.sntoken',$SN.'.sntoken_expire',$SN.'.photo'));
            break;
            case 'st':
                $SNO = 'SteamUsers';
                $WORKER_NAME='steamRefreshInfo';
                $user = $usersModel->getByAuid($auid,array($SN.'.snuid',$SN.'.sntoken',$SN.'.sntoken_expire',$SN.'.photo'));
            break;
            // snrefresh_token
            case 'ok':
                $SNO = 'OdnoklassnikiUsers';
                $WORKER_NAME='odnoklassnikiRefreshInfo';
                $user = $usersModel->getByAuid($data['_id'],array($SN.'.snuid',$SN.'.sntoken',$SN.'.snrefresh_token',$SN.'.dt_request_sntoken',$SN.'.dt_request_snrefresh_token',$SN.'.sntoken_expire',$SN.'.photo'));
            break;
            case 'ae':
                //XXX *Always* check sntoken validity, becouse we don't pass 'expires_in' from client
                //XXX and we don't know how much time have passed since token was received by client.
                //XXX But hope sometime we'll request tokens by server -- the way it should be done.
                $SNO = 'AeriaUsers';
                $WORKER_NAME='aeriaRefreshInfo';
                $user = $usersModel->getByAuid($auid,array($SN.'.snuid',$SN.'.sntoken',$SN.'.snrefresh_token',$SN.'.sntoken_expire',$SN.'.photo'));
            break;
            case 'mru':
                //XXX *Always* check sntoken validity, becouse we don't pass 'expires_in' from client
                //XXX and we don't know how much time have passed since token was received by client.
                //XXX But hope sometime we'll request tokens by server -- the way it should be done.
                $SNO = 'MailRuUsers';
                $WORKER_NAME='mailruRefreshInfo';
                $user = $usersModel->getByAuid($auid,array($SN.'.snuid',$SN.'.sntoken',$SN.'.snrefresh_token',$SN.'.sntoken_expire',$SN.'.photo'));
            break;
            case 'dlt':
                //XXX *Always* check sntoken validity, becouse we don't pass 'expires_in' from client
                //XXX and we don't know how much time have passed since token was received by client.
                //XXX But hope sometime we'll request tokens by server -- the way it should be done.
                $SNO = 'DraugasUsers';
                $WORKER_NAME='draugasRefreshInfo';
                $user = $usersModel->getByAuid($auid,array($SN.'.snuid',$SN.'.sntoken',$SN.'.snrefresh_token',$SN.'.sntoken_expire',$SN.'.photo'));
                break;
            default:
                Assistant::workerLogMessage(
                    'error',
                    'SN '.$SN.' is off :['.serialize($workload).']. Time:['. (microtime(true) - $time_start).']',
                    Sa_Log::ERR
                );
                return;
            break;
        }

        if(isset($user[$SN]['sntoken_expire']) && $user[$SN]['sntoken_expire'])
        {
            Assistant::workerLogMessage(
                'token_exp',
                $SN.' skip, token exp : user['.json_encode($user).']. data['.json_encode($data).']',
                Sa_Log::ERR
            );
            return;
        }

        if(!$user
            && ($config['log_level'] == 'info' || $config['log_level'] == 'error')
        ){
            Assistant::workerLogMessage(
                'error',
                $SNO.' account for user with auid = ['.$auid.'] not found. Time:['. (microtime(true) - $time_start).']',
                Sa_Log::ERR
            );
            return;
        }

        $oSnUsers = new $SNO();
        $sntoken_save = $user[$SN]['sntoken'];

        switch ($SN)
        {
            case 'fb':
            case 'vk':
            case 'st':

                if(isset($data['sntoken']) && $sntoken_save != $data['sntoken'])
                {
                    $validToken = $oSnUsers->validateToken(NULL, $data['sntoken']);
                    // @todo up in DB ? maybe clean ?
                    $sntoken_save = $data['sntoken'];
                }
            break;
            case 'dlt':
                /*if(isset($data['sntoken']) && $sntoken_save != $data['sntoken'])
                {*/

                    $validToken = $oSnUsers->validateToken($data['snuid'], $data['sntoken']);
                    // @todo up in DB ? maybe clean ?
                    if(isset($validToken['error'])) {
                        Assistant::workerLogMessage(
                            $WORKER_NAME,
                            $SNO . ' : snuid=' . $user[$SN]['snuid'].' validation error '.print_r($validToken, true),
                            Sa_Log::ERR
                        );
                        $usersModel->setSntokenExpire($data['_id'], $SN, 1);
                        return;
                    }
                    $sntoken_save = $data['sntoken'];
                //}
            break;
            case 'ok':
                // @todo $validToken ???
                if($data['sntoken'] == $user[$SN]['sntoken'])
                {
                    if(isset($user[$SN]['dt_request_sntoken']) && (time() - $user[$SN]['dt_request_sntoken']) > 1800)
                    {
                        if(isset($user[$SN]['dt_request_snrefresh_token']) && (time() - $user[$SN]['dt_request_snrefresh_token']) < 2592000)
                        {
                            $sntoken_up = $oSnUsers->refreshToken($user[$SN]['snrefresh_token']);
                            if(is_array($sntoken_up) && isset($sntoken_up['error']))
                            {
                                Assistant::workerLogMessage(
                                    $WORKER_NAME,
                                    $SNO. ' : '.$sntoken_up['message'].' snuid='.$user[$SN]['snuid'],
                                    Sa_Log::ERR
                                );
                                $usersModel->setSntokenExpire($data['_id'],$SN,1);
                                return;
                            }
                            else
                            {
                                $sntoken_save = $sntoken_up;
                                $data['snrefresh_token'] = $user[$SN]['snrefresh_token'];
                                $dtRequestSnRefreshToken = $user[$SN]['dt_request_snrefresh_token'];

                                if($config['log_level'] == 'info' || $config['log_level'] == 'error')
                                {
                                    Assistant::workerLogMessage(
                                        $WORKER_NAME,
                                        $SNO.' : Refresh token for ['.$data['_id'].'] used. Time:['. (microtime(true) - $time_start).']',
                                        Sa_Log::INFO
                                    );
                                }
                            }
                        }
                        else
                        {
                            Assistant::workerLogMessage(
                                $WORKER_NAME,
                                $SNO.' : Refresh token for user auid='.$data['_id'].',snuid='.$user[$SN]['snuid'].' expired.',
                                Sa_Log::ERR
                            );
                            $usersModel->setSntokenExpire($data['_id'],$SN,1);
                            return;
                        }
                    }
                    else
                    {
                        $sntoken_save = $user[$SN]['sntoken'];
                        $data['snrefresh_token'] = $user[$SN]['snrefresh_token'];
                        $dtRequestSnRefreshToken = $user[$SN]['dt_request_snrefresh_token'];
                        $dtRequestSnToken = $user[$SN]['dt_request_sntoken'];

                        Assistant::workerLogMessage(
                            $WORKER_NAME,
                            $SNO.' : Access token for ['.$data['_id'].'] used. Time:['. (microtime(true) - $time_start).']',
                            Sa_Log::INFO
                        );
                    }
                }
                else
                {
                    $validToken = $oSnUsers->validateToken(NULL, $data['sntoken']);
                    if(!isset($validToken['error']))
                    {
                        $sntoken_save = $data['sntoken'];
                    }
                }
            break;
            case 'ae':
            case 'mru':

                $validToken = $oSnUsers->validateToken($data['_id'], $data['sntoken']);
                if (isset($validToken['error']) && $validToken['error'] == 4)
                {
                    $usersModel->setSntokenExpire($data['_id'],$SN,1);
                    $refreshed = $oSnUsers->refreshToken($data['snrefresh_token']);
                    if(!isset($refreshed['error']))
                    {
                        $sntoken_save = $refreshed['access_token'];
                        $data['snrefresh_token'] = $refreshed['refresh_token'];
                        unset($validToken['error']);
                    }
                }
            break;
            default:
            break;
        }

        if(isset($validToken['error']))
        {
            Assistant::workerLogMessage(
                $WORKER_NAME,
                $SNO.' token validation error: '.$validToken['message'].' snuid='.$user[$SN]['snuid'] .' Time:['. (microtime(true) - $time_start).']',
                Sa_Log::ERR
            );
            $usersModel->setSntokenExpire($data['_id'],$SN,1);
            return;
        }

        $userFullInfo = isset($data['snrefresh_token']) && $data['snrefresh_token']
            ? $oSnUsers->requestFullUserData($user[$SN]['snuid'],$sntoken_save,$data['snrefresh_token'])
            : $oSnUsers->requestFullUserData($user[$SN]['snuid'],$sntoken_save,NULL,false);

        if(!isset($userFullInfo['error']))
        {
            $friends = isset($userFullInfo['friends'])?$userFullInfo['friends']:false;
            $snid = isset($userFullInfo['snid'])?$userFullInfo['snid']:false;
            // ok {{{
            if(isset($dtRequestSnRefreshToken))
            {
                $userFullInfo[$SN]['dt_request_snrefresh_token'] = $dtRequestSnRefreshToken;
            }
            if(isset($dtRequestSnToken))
            {
                $userFullInfo[$SN]['dt_request_sntoken'] = $dtRequestSnToken;
            }
            // ok end }}}

            unset(
                $userFullInfo['friends'],$userFullInfo['snid'],
                $userFullInfo['dt_last_login'],$userFullInfo['dt_register'],
                $user[$SN]['sntoken_expire']
            );
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
                # now compare the lists, format [fb_3468936_100004631055392]
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
                            try{
                               $friendsModel->add($auid, $friendAuid, $snid);
                            }catch(Exception $e){
                                Assistant::workerLogMessage($WORKER_NAME, json_encode($e), $type);
                            }
                        }
                    }
                    # it's safe to crash here we'll just fix `sn_friends` next time
                    if ($newFriendsData)
                    {
                        $friendsModel->addSnFriends($snid,$auid,$newFriendsData);
                    }
                }
            }
            if ($auid && $newFriendsAuids && !empty($config['ss_xcoordinator']))
            {
                Assistant::workerSendToSS(array(
                    'host'=>$config['ss_xcoordinator']['host'],
                    'port'=>$config['ss_xcoordinator']['port'],
                    'path'=>$config['ss_xcoordinator']['path'],
                    'timeout'=>isset($config['ss_xcoordinator']['timeout'])?$config['ss_xcoordinator']['timeout']:10,
                    'wait_response'=>isset($config['ss_xcoordinator']['wait_response'])?$config['ss_xcoordinator']['wait_response']:false,
                    'json'=> '{ "method" : "refresh_friends" }',
                    'get'=>array(
                        'action'=>'send_to_friends',
                        'auid'=>$auid
                    ),
                ));
            }else
            {
                $message .= 'No send to SS auid = '.$data['_id'].'  ';
            }
            if($config['log_level'] == 'info')
            {
                $message .= $SNO.'Info refresh for user with auid = '.$data['_id'].' complete. Time:['. (microtime(true) - $time_start).']';
            }

            $usersModel->setSntokenExpire($data['_id'],$SN,0);

        }
        elseif($config['log_level'] == 'info' || $config['log_level'] == 'error')
        {
            $message .= $SNO.' error: '.$userFullInfo['message'].'. Data:['.serialize($workload).']. Time:['. (microtime(true) - $time_start).']';
            $type = Sa_Log::ERR;
            $usersModel->setSntokenExpire($data['_id'],$SN,1);
        }
        if($message)
        {
            Assistant::workerLogMessage($WORKER_NAME, $message, $type);
        }
    }
    catch (Exception $e)
    {
        $message .= $WORKER_NAME." : Error message:".$e->getMessage()."\nTrace:".$e->getTraceAsString()." Time:['. (microtime(true) - $time_start).]";
        Assistant::workerLogMessage($WORKER_NAME, $message, Sa_Log::CRIT);
    }
}

/**
 * @name logBackground
 * @param GearmanWorker $job
 * @param array $context
 * @return void|unknown|string|Ambigous <>|boolean
 */
function logBackground($job,$context)
{
    global $config;

    $workload = $job->workload();
    if($workload=='terminate')
    {
        posix_kill( $context['pid'], SIGTERM ); // exec(sprintf('/bin/kill -s TERM %d', $context['pid']));
        return;
    }

    $path=realpath($config['path']['logs']).'/pid/'.$context['pid'] .'-state.txt';

    if(file_exists($path)
        && ($sPidFile = file_get_contents($path)) == true
    ){
        $aWorkersPID = unserialize($sPidFile);
        if(isset($aWorkersPID[$context['pid']]) && $aWorkersPID[$context['pid']]['state']=='no_more')
        {
            return;
        }
    }

    echo strftime("[%F %T] PID:[{$context['pid']}] Work...\n", time());

    try
    {
        $initializer = new Initializer();
        $initializer->initialize(array('config' => $config));
        if(is_object($job))
        {
            // array('_id','sntoken')
            $data = $workload ? unserialize($workload) : false;
        }else
        {
            $data = $job;
        }

        if(isset($data['message']) && isset($data['worker']) && isset($data['type']))
        {
            $date = date("Y.m.d");
            $logFileArray = glob($config['path']['logs'].$data['worker'].'-'.$config['version'].'-'.$date."-*-sa.txt", GLOB_NOSORT);
            if(count($logFileArray))
            {
                $logFile = $logFileArray[0];
            }
            else
            {
                $logFile = $config['path']['logs'].$data['worker'].'-'.$config['version'].'-'.$date.'-sa.txt';
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
        file_put_contents(realpath($config['path']['logs']).'/error.log', json_encode($e->getTraceAsString()), FILE_APPEND|LOCK_EX);
    }
}
/**
 * @name sendBackground
 * @param GearmanWorker $job
 * @param array $context
 * @return void|unknown|string|Ambigous <>|boolean
 */
function sendToSSBackground($job,$context)
{
    global $config;

    if(is_object($job))
    {
        $data = $job->workload();
        $data = $data ? unserialize($data) : false;
    }else
    {
        $data = $job;
    }

    if($data=='terminate')
    {
        posix_kill( $context['pid'], SIGTERM );
        return;
    }

    $path=realpath($config['path']['logs']).'/pid/'.$context['pid'] .'-state.txt';

    if(file_exists($path)
        && ($sPidFile = file_get_contents($path)) == true
    ){
        $aWorkersPID = unserialize($sPidFile);
        if(isset($aWorkersPID[$context['pid']]) && $aWorkersPID[$context['pid']]['state']=='no_more')
        {
            return;
        }
    }

    echo strftime("[%F %T] PID:[{$context['pid']}] Work...\n", time());

    try
    {
        $initializer = new Initializer();
        $initializer->initialize(array('config' => $config));

        if(isset($data['host']) && isset($data['port']))
        {
            $fp = @fsockopen( $data['host'], $data['port'], $errno, $errstr, $data['timeout'] );
            if (!$fp)
            {
                 Assistant::workerLogMessage( 'sendToSSBackground', $errstr.' '.$errno  , Sa_Log::ERR );
            }
            else
            {
                $content_get  = http_build_query( $data['get'] ); // $data['send_data'] array
                $out  = "POST ".$data['path'].($content_get?'?'.$content_get:'')." HTTP/1.1\r\n";
                $out .= "Host: " . $data['host'] . "\r\n";
                $out .= "Content-Type: application/json; charset=utf-8 \r\n";
                $out .= "Content-Length: " . strlen( $data['json'] ) . "\r\n";
                $out .= "Connection: close\r\n\r\n";
                $out .= $data['json'];
                fwrite( $fp, $out );
                if($data['wait_response'])
                {
                    $response='';
                    while (!feof($fp))
                    {
                        $response.=fgets($fp, 1024);
                    }
                    Assistant::workerLogMessage( 'sendToSSBackground', "sendToSSBackground response: [".json_encode($response) . "]", Sa_Log::INFO);
                }
                fclose( $fp );
            }
        }else{
            Assistant::workerLogMessage( 'sendToSSBackground', 'config error data:[' . serialize($data).']', Sa_Log::ERR);
        }
    }
    catch (Exception $e)
    {
        file_put_contents(realpath($config['path']['logs']).'/error.log', json_encode($e->getTraceAsString()), FILE_APPEND|LOCK_EX);
    }
}