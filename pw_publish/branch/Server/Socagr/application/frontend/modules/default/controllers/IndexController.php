<?php
class IndexController extends Zend_Controller_Action
{
    private static function _getSnUserModel($snid)
    {
        switch($snid)
        {
        case 'fb':
            return new FacebookUsers();
        case 'pwc':
            return new PWConnectUsers();
        case 'st':
            return new SteamUsers();
        case 'vk':
            return new VkontakteUsers();
        case 'ok':
            return new OdnoklassnikiUsers();
        case 'ae':
            return new AeriaUsers();
        case 'msv':
            return new MassiveUsers();
        case 'mru':
            return new MailRuUsers();
        case 'arc':
            return new ArcgamesUsers();
        case 'zzma':
            return new ZzimaUsers();
        case 'gmg':
            return new GamigoUsers();
        case 'dlt':
            return new DraugasUsers();

        }
        return NULL;
    }

    private static function _getUserSnid($user)
    {
        if (isset($user['fb']) && isset($user['fb']['email']))
        {
            return 'fb';
        }
        foreach (array('vk','ok','st','ae','pwc','msv', 'mru','arc','zzma','gmg', 'dlt') as $snid)
        {
            if (isset($user[$snid]))
            {
                return $snid;
            }
        }
        return false;
    }

    private function _validateSnToken($model, $snuid, $sntoken,$sn=false)
    {
        $validToken = $model->validateToken($snuid, $sntoken);
        if(isset($validToken['error']))
        {
            Assistant::logger(
                ' [ Validate Sn['.$sn.':'.$snuid.'] Token ERROR: '.$validToken['error'] .' ] '.
                (isset($validToken['ext_error']) ? ' Response: ['. $validToken['ext_error'].' ]' :''),
                Sa_Log::ERR
            );
            return $this->_setError($validToken['error'], $validToken['message']);
        }
        return true;
    }

    private function _checkSnToken($model, $snuid, $sntoken)
    {
        $checkedToken = $model->checkToken($snuid,$sntoken);
        if(isset($checkedToken['error']))
        {
            Assistant::logger(
                 ' [ check SN token ERROR: '.$checkedToken['error'] .' ] '.
                 (isset($checkedToken['ext_error']) ? ' Response: ['. $checkedToken['ext_error'].' ]' :''),
                 Sa_Log::ERR
            );
            return $this->_setError($checkedToken['error'], $checkedToken['message']);
        }
        return true;
    }

    private function _billingRegister($auid, $test, $email, $referral)
    {
        $config = Zend_Registry::get('config');
        $billingConfig = ($test == 1) ? $config->test_billing->toArray() : $config->billing->toArray();

        $password = md5(str_shuffle(substr(rand() . time(), 0, 12)),true);
        $user = $billingConfig['userName_prefix'].$auid;
        $params = array(
            'fromServiceName' => $billingConfig['fromServiceName'],
            'userEmail' => $email,
            'userName' => $user,
            'userPassword' => $password,
            'userReferal' => $referral,
        );
        //Assistant::logger(("_billingRegister params: " . print_r($params, true));
        $params['crc'] = Assistant::generateBillingCRC($params);
        try
        {
            $soapClient = new SoapClient($billingConfig['url']);
            $response = $soapClient->RegisterUser(array('req' => $params));
            //Assistant::logger(("_billingRegister: soap response: " . print_r($response, true));
        }
        catch (Exception $e)
        {
            $this->view->warning = 'SOAP error: '.$e->getMessage();
            return false;
        }
        $this->view->email = $email;
        if ($response->RegisterUserResult->code < 0)
        {
            if ($response->RegisterUserResult->code == -1003 && isset($billingConfig['reuse_account']) && $billingConfig['reuse_account'] == 1)
            { # PF-75574: User exists and config says to reuse it
                return true;
            }
            $message = 'Billing error. Code = '.$response->RegisterUserResult->code.'.';
            if(isset($response->RegisterUserResult->message) && !empty($response->RegisterUserResult->message))
            {
                $message .= ' Message = '.$response->RegisterUserResult->message;
            }
            $this->view->warning = $message;
            $this->view->user = $user;
            return false;
        }
        return true;
    }

    private function _billingRegisterTry($auid, $snid, $userData, $test, $usersModel)
    {
        $config = Zend_Registry::get('config');
        $email = '';
        $generated = 0;
        $billingConfig = ($test == 1) ? $config->test_billing->toArray() : $config->billing->toArray();
        switch ($snid)
        {
            case 'pwc':
            case 'fb':
                $email = $userData[$snid]['email'];
                break;
        }
        if(empty($email))
        {
            $email = Assistant::generateEmail($auid, $snid, $userData, $billingConfig);
            $generated = 1;
        }
        if($this->_billingRegister($auid, $test, $email, $userData['referral']))
        {
            $usersModel->edit($auid,array('billing_status' => 1));
            return true;
        }
        else
        {
            if ($generated == 0)
            {
                $email = Assistant::generateEmail($auid, $snid, $userData, $billingConfig);
                if($this->_billingRegister($auid, $test, $email, $userData['referral']))
                {
                    $usersModel->edit($auid,array('billing_status' => 1));
                    return true;
                }
            }
        }
        return false;
    }

    private function _addUser($userData)
    {
        //Assistant::logger("Adding user " . print_r($userData, true));
        $useBilling = $this->_request->getQuery('use_billing');
        $test = $this->_request->getQuery('test'); // FIXME: What does it for?
        $usersModel = new Users();
        $sequence = $usersModel->getUserSequence();
        if($sequence)
        {
            $userData['_id'] = $sequence;
            $friends = $userData['friends'];
            $snid = $userData['snid'];
            unset(
                 $userData['friends'],
                 $userData['snid']
            );
            $auid = $usersModel->add($userData);
            if($auid)
            {
                if(isset($friends['friends_data']) && count($friends['friends_data']) > 0)
                {
                    $friendsModel = new Friends();
                    if($friendsModel->addSnFriends($snid,$auid,$friends['friends_data']))
                    {
                        if(isset($friends['auids']) && count($friends['auids']) > 0)
                        {
                            foreach ($friends['auids'] as $friendAuid)
                            {
                             $friendsModel->add($auid, $friendAuid, $snid);
                            }
                        }
                        if(isset($friends['friend_records_ids']) && count($friends['friend_records_ids']) > 0)
                        {
                            $friendsModel->markUsed($friends['friend_records_ids'],1);
                        }
                    }
                }
                if($useBilling == 1)
                {
                    if($this->_billingRegisterTry($auid, $snid, $userData, $test, $usersModel))
                    {
                    }
                }
                $this->view->auid = $auid;
            }
        }
    }

    private function _addNewNetwork($userData,$auid)
    {
        $usersModel = new Users();
        $friends = $userData['friends'];
        $snid = $userData['snid'];
        unset($userData['friends']);
        unset($userData['snid']);
        unset($userData['dt_last_login']);
        unset($userData['dt_register']);
        $result = $usersModel->edit($auid,$userData,array('fsync' => true));
        if($result)
        {
            if(isset($friends['friends_data']) && count($friends['friends_data']) > 0)
            {
                $friendsModel = new Friends();
                if($friendsModel->addSnFriends($snid,$auid,$friends['friends_data']))
                {
                    if(isset($friends['auids']) && count($friends['auids']) > 0)
                    {
                        $currentFriendsAuids = $friendsModel->getAuidListByAuid($auid);
                        $friendsToAdd = array_diff($friends['auids'],$currentFriendsAuids);
                        foreach ($friendsToAdd as $friendAuid)
                        {
                        $friendsModel->add($auid, $friendAuid, $snid);
                        }
                        # override 'pwg' friends who are in $friends['auids'] too
                        $friendsModel->overridePwgSn($auid, $friends['auids'], $snid);
                    }
                    if(isset($friends['friend_records_ids']) && count($friends['friend_records_ids']) > 0)
                    {
                        $friendsModel->markUsed($friends['friend_records_ids'],1);
                    }
                }
            }
            $this->view->auid = (int)$auid;
        }
    }

    private function _registerUser($snid,$snuid,$sntoken,$snRefreshToken,$verify,$is_zul,$aExtParams=array(), $ruid)
    {
        $referral = $this->_request->getQuery('referral', '');
        Assistant::logger('Registering user at '.$snid.' with uid '.$snuid.'. Referral \''.$referral.'\'');
        $usersModel = new Users();
        $user = $usersModel->getSnUser($snid,$snuid,array('_id'));
        if($user)
        {
            return $this->_setError(9, 'User already exists in database.');
        }
        $snUserModel = IndexController::_getSnUserModel($snid);
        if(!isset($snUserModel))
        {
            return $this->_setError(21, 'Social network with snid = '.$snid.' not found.');
        }
        if(empty($sntoken) && $snUserModel->snTokenRequired())
        {
            return $this->_setError(3, 'Invalid list of action parameters: sntoken required for this network.');
        }
        if ($is_zul) // PF-91646 and I HATE IT!
        {
            $snUserModel->setZul(true);
        }

        if($verify && !$this->_validateSnToken($snUserModel, $snuid, $sntoken,$snid))
        {
            return false;
        }

        // PF-95069
        if ($snid!='gmg')
        {
            $snUserData = $snUserModel->requestFullUserData($snuid, $sntoken, $snRefreshToken);

        }else{
            if(!$aExtParams || !isset($aExtParams['gmguid']) || !$aExtParams['gmguid'])
            {
                return $this->_setError(3, 'Invalid list of action parameters: no gmguid');
            }
            $snUserData = $snUserModel->requestFullUserData($snuid, $sntoken, $snRefreshToken, False, $aExtParams);
        }

        if(isset($snUserData['error']))
        {
            return $this->_setError($snUserData['error'], $snUserData['message']);
        }

        // don`t remove.Double check because we wait 1-4 seconds for response
        $user = $usersModel->getSnUser($snid,$snuid,array('_id'));
        if($user)
        {
            return $this->_setError(9, 'User already exists in database.');
        }
        if (!$user && $snid == 'gmg')
        {
            $user = $usersModel->getUserInfo(array($snid.'.passportid' => $aExtParams['gmguid']),array('_id'));
            if($user)
            {
                return $this->_setError(32, 'User with gmguid ['.$aExtParams['gmguid'].'] already exists in database.');
            }
        }
        $snUserData['referral'] = $referral;
        $snUserData['ruid'] = $ruid;

        $this->_addUser($snUserData);
    }

    public function markloginAction()
    {
        $auid = $this->_request->getQuery('auid');
        if(!$auid)
        {
            return $this->_setError(3, 'Invalid list of action parameters: no auid.');
        }
        $usersModel = new Users();
        $usersModel->edit($auid, array('dt_last_login' => time()));
    }

    public function loginAction()
    {
        $snid = $this->_request->getQuery('snid');
        $snuid = $this->_request->getQuery('snuid');
        $sntoken = $this->_request->getQuery('sntoken');
        $snRefreshToken = $this->_request->getQuery('snrefresh_token');
        $autoRegister = $this->_request->getQuery('auto');
        $verify = $this->_request->getQuery('verify', true);
        $autoRegister = is_null($autoRegister) || !is_numeric($autoRegister) || (int)$autoRegister > 0 ? 1 : 0;
        $is_zul = ($snid == 'zzma') && $this->_request->getQuery('zul', false); // PF-91646

        if(!$snid)
        {
            return $this->_setError(3, 'Invalid list of action parameters: no snid.');
        }
        if(empty($snuid))
        {
            return $this->_setError(3, 'Invalid list of action parameters: empty snuid.');
        }
        if(empty($sntoken) && $verify)
        {
            return $this->_setError(3, 'Invalid list of action parameters: empty sntoken (and verify is on).');
        }
        if(($snid == 'ok' || $snid == 'mru' || ($snid == 'ae' && $verify)) && !$snRefreshToken)
        {
            return $this->_setError(3, 'Invalid list of action parameters: no refresh_token for snid='.$snid.'.');
        }
        if(!in_array($snid,Assistant::$SNLIST ))
        {
            return $this->_setError(21, 'Social network with snid = '.$snid.' not found.');
        }

        $usersModel = new Users();
        $user = $usersModel->getSnUser($snid,$snuid);
        if($user)
        {
            $fieldsForEdit = array();
            $snUserModel = IndexController::_getSnUserModel($snid);
            // PF-95069 [SS] sntoken === password
            if($snid=='gmg')
            {
                if( !$this->_validateSnToken($snUserModel, strtolower($snuid), $sntoken,$snid) )
                {
                    return false;
                }
            }
            elseif(!isset($user[$snid]['sntoken']) || $user[$snid]['sntoken'] != $sntoken)
            {
                if ($is_zul) // PF-91646 and I HATE IT!
                {
                    $snUserModel->setZul(true);
                }
                if($verify && !$this->_validateSnToken($snUserModel, $snuid, $sntoken,$snid))
                {
                    return false;
                }
                switch($snid)
                {
                    case 'gmg':
                        break;
                    case 'arc':
                    case 'zzma':
                        $fieldsForEdit[$snid] = $user[$snid];
                        if (!empty($sntoken))
                        {
                            $fieldsForEdit[$snid]['sntoken'] = $sntoken;
                        }
                        break;
                    case 'st':
                    case 'fb':
                    case 'pwc':
                    case 'msv':
                    case 'dlt':
                        if($verify && !$this->_checkSnToken($snUserModel,$snuid,$sntoken))
                        {
                            return false;
                        }
                        $fieldsForEdit[$snid] = $user[$snid];
                        if (!empty($sntoken))
                        {
                            $fieldsForEdit[$snid]['sntoken'] = $sntoken;
                        }
                        break;
                    case 'vk':
                        /**
                         * @todo check token if vkontakte add methods
                         */
                        /*
                        if($verify && !$this->_checkSnToken($snUserModel,$snuid,$sntoken))
                        {
                            return false;
                        }
                        */
                        $fieldsForEdit['vk'] = $user['vk'];
                        if (!empty($sntoken))
                        {
                            $fieldsForEdit[$snid]['sntoken'] = $sntoken;
                        }
                        break;
                    case 'ok':
                        $fieldsForEdit[$snid] = $user[$snid];
                        if (!empty($sntoken))
                        {
                            $fieldsForEdit[$snid]['sntoken'] = $sntoken;
                            $fieldsForEdit[$snid]['dt_request_sntoken'] = time();
                        }
                        $fieldsForEdit[$snid]['snrefresh_token'] = $snRefreshToken;
                        $fieldsForEdit[$snid]['dt_request_snrefresh_token'] = time();
                        break;
                    case 'ae':
                        $fieldsForEdit[$snid] = $user[$snid];
                        if (!empty($sntoken))
                        {
                            $fieldsForEdit[$snid]['sntoken'] = $sntoken;
                            $fieldsForEdit[$snid]['dt_request_sntoken'] = time();
                            #TODO: тут ещё надо сохранять срок жизни токена
                        }
                        $fieldsForEdit[$snid]['snrefresh_token'] = $snRefreshToken;
                        $fieldsForEdit[$snid]['dt_request_snrefresh_token'] = time();
                        break;
                    case 'mru':
                        $fieldsForEdit[$snid] = $user[$snid];
                        if (!empty($sntoken))
                        {
                            $fieldsForEdit[$snid]['sntoken'] = $sntoken;
                            $fieldsForEdit[$snid]['dt_request_sntoken'] = time();
                            #TODO: тут ещё надо сохранять срок жизни токена
                        }
                        $fieldsForEdit[$snid]['snrefresh_token'] = $snRefreshToken;
                        $fieldsForEdit[$snid]['dt_request_snrefresh_token'] = time();
                        break;
                }
                if (!empty($fieldsForEdit))
                {
                    $usersModel->edit($user['_id'],$fieldsForEdit);
                }
            }

            $usersModel->setSntokenExpire($user['_id'], $snid, 0);
            $config = Zend_Registry::get('config');
            if(!empty($sntoken) && ((int)(time() - $user['dt_last_login']) > $config->user_info_refresh_period))
            # perform refresh only for login action with sntoken!
            {
                $gearmanConfig = $config->gearman->toArray();
                $client= new GearmanClient();
                $client->addServers($gearmanConfig['servers']);
                if(isset($user['fb']['snuid']) && isset($user['fb']['sntoken']))
                {
                    $client->doBackground('refreshInfo', serialize(array(
                        '_id' => $user['_id'],
                        'sntoken' => $snid == 'fb' ? $sntoken : $user['fb']['sntoken'],
                        'sn'=> 'fb'
                    )));
                }
                if(isset($user['vk']['snuid']) && isset($user['vk']['sntoken']))
                {
                    $client->doBackground('refreshInfo', serialize(array(
                        '_id' => $user['_id'],
                        'sntoken' => $snid == 'vk' ? $sntoken : $user['vk']['sntoken'],
                        'sn'=> 'vk'
                    )));
                }
                if(isset($user['st']['snuid']))
                {
                    $client->doBackground('refreshInfo', serialize(array(
                        '_id' => $user['_id'],
                        'sn'=> 'st',
                    )));
                }
                if(isset($user['ok']['snuid']) && isset($user['ok']['sntoken']))
                {
                    $client->doBackground('refreshInfo', serialize(array(
                        '_id' => $user['_id'],
                        'sntoken' => $snid == 'ok' ? $sntoken : $user['ok']['sntoken'],
                        'snrefresh_token'=> $snid == 'ok' ? $snRefreshToken : $user['ok']['snrefresh_token'],
                        'sn'=> 'ok',
                    )));
                }
                if(isset($user['ae']['snuid']) && isset($user['ae']['sntoken']))
                {
                    #TODO add expiration here!
                    $client->doBackground('refreshInfo', serialize(array(
                        '_id' => $user['_id'],
                        'sntoken' => $snid == 'ae' ? $sntoken : $user['ae']['sntoken'],
                        'snrefresh_token'=> $snid == 'ae' ? $snRefreshToken : $user['ae']['snrefresh_token'],
                        'sn'=> 'ae',
                    )));
                }
                if(isset($user['mru']['snuid']) && isset($user['mru']['sntoken']))
                {
                    #TODO add expiration here!
                    $client->doBackground('refreshInfo', serialize(array(
                         '_id' => $user['_id'],
                         'sntoken' => $snid == 'mru' ? $sntoken : $user['mru']['sntoken'],
                         'snrefresh_token'=> $snid == 'mru' ? $snRefreshToken : $user['mru']['snrefresh_token'],
                         'sn'=> 'mru',
                    )));
                }
                if(isset($user['dlt']['snuid']) && isset($user['dlt']['sntoken']))
                {
                    #TODO add expiration here!
                    $client->doBackground('refreshInfo', serialize(array(
                        '_id' => $user['_id'],
                        'sntoken' => $snid == 'dlt' ? $sntoken : $user['dlt']['sntoken'],
                        'snuid' => $snid == 'dlt' ? $snuid : $user['dlt']['snuid'],
                        'sn'=> 'dlt'
                    )));
                }

            }
            $this->view->auid = $user['_id'];
        }
        else
        {
            $config = Zend_Registry::get('config');
            if($autoRegister != 0)
            {
                $this->_registerUser($snid,$snuid,$sntoken,$snRefreshToken,$verify,$is_zul);
            }
            else
            {
                return $this->_setError(8, 'User with snuid = '.$snuid.' not found.');
            }
        }
    }


    public function registerAction()
    {
        $snid = $this->_request->getQuery('snid');
        $snuid = $this->_request->getQuery('snuid');
        $sntoken = $this->_request->getQuery('sntoken');
        $snRefreshToken = $this->_request->getQuery('snrefresh_token');
        $verify = $this->_request->getQuery('verify', true);
        $is_zul = ($snid == 'zzma') && $this->_request->getQuery('zul', false); // PF-91646
        $ruid = $this->_request->getQuery('ruid','');

        $aExtParams = array(
            'gmguid' => $this->_request->getQuery('gmguid', false)
        );

        if(!$snid)
        {
            return $this->_setError(3, 'Invalid list of action parameters: no snid.');
        }
        if(empty($snuid))
        {
            return $this->_setError(3, 'Invalid list of action parameters: empty snuid.');
        }
        if(empty($sntoken) && $verify)
        {
            return $this->_setError(3, 'Invalid list of action parameters: empty sntoken (and verify is on).');
        }
        if(($snid == 'ok' || $snid == 'mru' || ($snid == 'ae' && $verify)) && !$snRefreshToken)
        {
            return $this->_setError(3, 'Invalid list of action parameters: no refresh_token for snid='.$snid.'.');
        }
        if(!in_array($snid,Assistant::$SNLIST))
        {
            return $this->_setError(21, 'Social network with snid = '.$snid.' not found.');
        }

        $this->_registerUser($snid,$snuid,$sntoken,$snRefreshToken,$verify,$is_zul,$aExtParams,$ruid);
    }


    public function getinfoAction()
    {
        $snid = $this->_request->getQuery('snid');
        $auid = $this->_request->getQuery('auid');
        $includeSecureData = $this->_request->getQuery('include_secure_data');

        if(empty($auid))
        {
            return $this->_setError(3, 'Invalid list of action parameters.');
        }
        if($snid && !in_array($snid,Assistant::$SNLIST))
        {
            return $this->_setError(21, 'Social network with snid = '.$snid.' not found.');
        }
        $usersModel = new Users();
        $user = $usersModel->getByAuid($auid);

        if(!$user)
        {
            return $this->_setError(10, 'User with auid = '.$auid.' not found.');
        }
        $info = Assistant::generateUserData($user,$snid,$includeSecureData);
        if(!$info)
        {
            return $this->_setError(16, 'Service with snid = '.$snid.' not connected by user with auid = '.$auid);
        }
        $this->view->get_info = $info;
    }


    public function getinfosAction()
    {
        $snid = $this->_request->getQuery('snid');
        $auids = $this->_request->getQuery('auids');
        $includeSecureData = $this->_request->getQuery('include_secure_data');

        if(empty($auids))
        {
            return $this->_setError(3, 'Invalid list of action parameters.');
        }
        if($snid && !in_array($snid,Assistant::$SNLIST))
        {
            return $this->_setError(21, 'Social network with snid = '.$snid.' not found.');
        }
        $auids = explode(',',$auids);
        asort($auids);
        $usersModel = new Users();
        $auidsArray = array();
        foreach ($auids as $auid)
        {
            $auidsArray[] = (int)$auid;
        }
        $usersArray = array();
        $users = $usersModel->getMultiByAuids($auidsArray);
        $realAuids = array();
        foreach ($users as $user)
        {
            $info = Assistant::generateUserData($user,$snid,$includeSecureData);
            if($info)
            {
                $usersArray[$user['_id']] = $info;
            }
            $realAuids[] = $user['_id'];
        }
        if($realAuids != $auidsArray)
        {
            $nonExistentAuids = array_diff($auids,$realAuids);
            $nonExistentAuidsStr = implode(',',$nonExistentAuids);
            return $this->_setError(11, 'Users with auids = '.$nonExistentAuidsStr.' not found.');
        }
        $this->view->get_infos = $usersArray;
    }


    public function addfriendAction($auid=false, $friend_auid=false, $snid=false,$quiet=false)
    {
        $auid = $auid ? $auid : $this->_request->getQuery('auid');
        $friendAuid = $friend_auid ? $friend_auid : $this->_request->getQuery('friend_auid');
        $snid = $snid ? $snid : $this->_request->getQuery('snid', 'pw');

        if(empty($auid) || empty($friendAuid))
        {
            return $this->_setError(3, 'Invalid list of action parameters.');
        }
        $usersModel = new Users();
        $user = $usersModel->getByAuid($auid,array('_id','fb.snuid','vk.snuid','ok.snuid','pwc.snuid','st.snuid','ae.snuid','mru.snuid','msv.snuid', 'dlt.snuid'));
        if(!$user)
        {
            return $this->_setError(10, 'User with auid = '.$auid.' not found.');
        }

        $friend = $usersModel->getByAuid($friendAuid,array('_id','fb.snuid','vk.snuid','ok.snuid','pwc.snuid','st.snuid','ae.snuid','mru.snuid','msv.snuid', 'dlt.snuid'));
        if(!$friend)
        {
            return $this->_setError(10, 'User with auid = '.$friendAuid.' not found.');
        }
        $friendsModel = new Friends();
        $edgeStatus = $friendsModel->getStatusSn($auid,$friendAuid);
        $result = false;
        if($edgeStatus)
        {
            if ($snid == 'pwg' || $edgeStatus['snid'] != 'pwg')
            {
                return $this->_setError(12, 'Friend relationship already exist.');
            }
            $result = $friendsModel->overridePwgSn($auid, array($friendAuid), $snid);
        }
        else
        {

            try
            {
                $result = $friendsModel->add($auid,$friendAuid,$snid);
            }
            catch (MongoCursorException $e)
            {
                Assistant::logger('addfriendAction '.$e->getMessage().'\n: '.$e->getTraceAsString());
                if ($e->getCode() == 11000)
                {
                    return $this->_setError(12, 'Friend relationship already exist.');
                }
                else
                    return $this->_setError(1, 'Application error.');
            }

        }
        if($result && $snid != 'pwg')
        {
            $friendRecords = array();
            //  'pwc', 'msv','arc' - not friend
            foreach (array('fb', 'vk', 'ok', 'st', 'ae','mru', 'dlt') as $sn)
            {
                if(isset($friend[$sn]['snuid']) && isset($user[$sn]['snuid']))
                {
                    $friendRecords[] = $sn.'_'.$auid.'_'.$friend[$sn]['snuid'];
                    $friendRecords[] = $sn.'_'.$friendAuid.'_'.$user[$sn]['snuid'];
                }
            }
            if(count($friendRecords) > 0)
            {
                $friendsModel->markUsed($friendRecords,1);
            }
        }
    }

    /**
     * curl -i --data "friends_auid[]=1&friends_auid[]=2" "http://217.174.109.183:89/?action=add_friends&version=0.3.93&auid=1&friends_auid\[\]=3"
     * curl -i "http://217.174.109.183:89/?action=add_friends&version=0.3.93&auid=1000002&friends_auid\[\]=1000004&friends_auid\[\]=1000005"
     * @return boolean
     */
    public function addfriendsAction()
    {
        $auid = $this->_request->getQuery('auid');
        $friendsAuid = $this->_request->getQuery('friends_auid');
        $snid = $this->_request->getQuery('snid', 'pw');
        $bEroor=false;
        if($friendsAuid)
        {
            foreach ($friendsAuid as $friendAuid)
            {
                try
                {
                    $this->addfriendAction($auid,$friendAuid,$snid);
                    if($this->view->error)
                    {
                        $error[$friendAuid]=array(
                            'error'=> $this->view->error,
                            'message'=> $this->view->message,
                        );
                        $bEroor=true;
                    }
                }catch (Exception $e)
                {
                    Assistant::logger(
	                    ' [ addfriends Error ['.json_encode($e).']' ,
        	            Sa_Log::ERR
                    );
                }
            }
            if($bEroor)
            {
                $this->_setError(13, $error);
            }
        }
    }


    public function getedgestatusAction()
    {
        $auid = $this->_request->getQuery('auid1');
        $friendAuid = $this->_request->getQuery('auid2');

        if(empty($auid) || empty($friendAuid))
        {
            return $this->_setError(3, 'Invalid list of action parameters.');
        }
        $usersModel = new Users();
        $user = $usersModel->getByAuid($auid,array('_id'));
        if(!$user)
        {
            return $this->_setError(10, 'User with auid = '.$auid.' not found.');
        }

        $friend = $usersModel->getByAuid($friendAuid,array('_id'));
        if(!$friend)
        {
            return $this->_setError(10, 'User with auid = '.$friendAuid.' not found.');
        }
        $friendsModel = new Friends();
        $this->view->Get_edge_status = $friendsModel->getStatus($auid,$friendAuid);
    }


    public function getfriendsAction()
    {
        $auid = $this->_request->getQuery('auid');

        if(empty($auid))
        {
            return $this->_setError(3, 'Invalid list of action parameters.');
        }
        $usersModel = new Users();
        $user = $usersModel->getByAuid($auid,array('_id'));
        if(!$user)
        {
            return $this->_setError(10, 'User with auid = '.$auid.' not found.');
        }
        $friendsModel = new Friends();
        $this->view->get_friends = $friendsModel->getAuidListByAuid($auid);
    }


    public function deletefriendAction()
    {
        $auid = $this->_request->getQuery('auid');
        $friendAuid = $this->_request->getQuery('friend_auid');
        $snid = $this->_request->getQuery('snid');
        # if `friend_auid` is specified - delete this single friend;
        # if `snid` specified - delete all friends with that snid,
        # also in the `snid` case no $friendsModel->markUsed($friendRecords,2) called,
        # because these friends aren't manually unfriended

        #Assistant::logger('deletefriendAction: auid = ' . $auid .
        #    (empty($friendAuid) ? (', snid = ' . $snid) : (', friendAuid = ' . $friendAuid)));

        if(empty($auid) || (empty($friendAuid) && empty($snid)))
        {
            return $this->_setError(3, 'Invalid list of action parameters.');
        }
        $usersModel = new Users();
        $user = $usersModel->getByAuid($auid,array('_id','fb.snuid','vk.snuid','ok.snuid','pwc.snuid','st.snuid','ae.snuid','mru.snuid','msv.snuid', 'dlt.snuid'));
        if(!$user)
        {
            return $this->_setError(10, 'User with auid = '.$auid.' not found.');
        }

        $friendsModel = new Friends();
        if (empty($friendAuid))
        {
            #Assistant::logger('Deleting friends by SN');
            $this->view->pairs = $friendsModel->removeBySn($auid, $snid);
            #Assistant::logger($this->view->pairs ? (count($this->view->pairs) . ' friend records found.') : 'No friends found!');
            return;
        }

        ## --- single friend delete action, $snid ignored even if non-empty

        $friend = $usersModel->getByAuid($friendAuid,array('_id','fb.snuid','vk.snuid','ok.snuid','pwc.snuid','st.snuid','ae.snuid','mru.snuid','msv.snuid', 'dlt.snuid'));
        if(!$friend)
        {
            return $this->_setError(10, 'User with auid = '.$friendAuid.' not found.');
        }
        if(!$friendsModel->getStatus($auid,$friendAuid))
        {
            return $this->_setError(13, 'Friend relationship does not exist.');
        }
        if($friendsModel->remove($auid,$friendAuid))
        {
            $friendRecords = array();
            foreach (array('fb', 'vk', 'ok', 'st', 'ae','mru', 'dlt') as $sn)
            {
                if(isset($friend[$sn]['snuid']) && isset($user[$sn]['snuid']))
                {
                    $friendRecords[] = $sn.'_'.$auid.'_'.$friend[$sn]['snuid'];
                    $friendRecords[] = $sn.'_'.$friendAuid.'_'.$user[$sn]['snuid'];
                }
            }
            if(count($friendRecords) > 0)
            {
                $friendsModel->markUsed($friendRecords,2);
            }
        }
    }


    public function getfriendsinfoallAction()
    {
        $snid = $this->_request->getQuery('snid');
        $auid = $this->_request->getQuery('auid');
        $includeSecureData = $this->_request->getQuery('include_secure_data');
        $skip = $this->_request->getQuery('skip', 0);
        $limit = $this->_request->getQuery('limit', 0);
        if(empty($auid))
        {
            return $this->_setError(3, 'Invalid list of action parameters.');
        }
        if($snid && !in_array($snid,Assistant::$SNLIST))
        {
            return $this->_setError(21, 'Social network with snid = '.$snid.' not found.');
        }

        $usersModel = new Users();
        $user = $usersModel->getByAuid($auid,array('_id'));
        if(!$user)
        {
            return $this->_setError(10, 'User with auid = '.$auid.' not found.');
        }
        $friendsModel = new Friends();
        $friends = $friendsModel->getAuidListByAuid($auid,$skip, $limit);
        $friendsInfo = array();
        if(count($friends) > 0)
        {
            $users = $usersModel->getMultiByAuids($friends);
            foreach ($users as $user)
            {
                $info = Assistant::generateUserData($user,$snid,$includeSecureData);
                if($info)
                {
                    $friendsInfo[$user['_id']] = $info;
                }
            }
        }
        $this->view->get_friends_info_all = $friendsInfo;
    }


    public function getcandidatesinfoallAction()
    {
        $snid = $this->_request->getQuery('snid');
        $auid = $this->_request->getQuery('auid');

        if(empty($auid))
        {
            return $this->_setError(3, 'Invalid list of action parameters.');
        }
        if($snid && !in_array($snid,Assistant::$SNLIST))
        {
            return $this->_setError(21, 'Social network with snid = '.$snid.' not found.');
        }

        $usersModel = new Users();
        switch ($snid)
        {
            case 'fb':
            case 'vk':
            case 'ok':
            case 'pwc':
            case 'st':
            case 'ae':
            case 'msv':
            case 'mru':
            case 'dlt':
                $fields = array('_id',$snid.'.snuid');
                break;
            default:
                $fields = array('_id','fb.snuid','vk.snuid','ok.snuid','pwc.snuid','st.snuid','ae.snuid','mru.snuid','msv.snuid', 'dlt.snuid');
                break;
        }
        $user = $usersModel->getByAuid($auid,$fields);
        if(!$user)
        {
            return $this->_setError(10, 'User with auid = '.$auid.' not found.');
        }
        if(!empty($snid) && !isset($user[$snid]['snuid']))
        {
            return $this->_setError(16, 'Service with snid = '.$snid.' not connected by user with auid = '.$auid);
        }
        $friendsModel = new Friends();
        $candidatesInfo = array();
        $candidatesInfo = $friendsModel->getSnFriendsInfo($snid,$auid);
        $friendsInfo = array();
        foreach ($candidatesInfo as $candidate)
        {
            switch ($candidate['snid'])
            {
                case 'fb':
                        $friendsInfo[$candidate['snid']][$candidate['snuid']] =     array(
                            'name' => $candidate['name'],
                            'photo' => 'https://graph.facebook.com/'.$candidate['snuid'].'/picture?type=square&width=64&height=64',
                        );
                    break;
                case 'vk':
                case 'ok':
                case 'st':
                case 'ae':
                case 'mru':
                case 'dlt':
                        $friendsInfo[$candidate['snid']][$candidate['snuid']] =     array(
                            'name' => $candidate['name'],
                            'photo' => $candidate['photo'],
                        );
                    break;
            }
        }
        $this->view->get_candidates_info_all = $friendsInfo;
    }

    public function setedgepropertyAction()
    {
        $auid = $this->_request->getQuery('auid1');
        $secondAuid = $this->_request->getQuery('auid2');
        $propertyName = strtolower($this->_request->getQuery('property_name'));
        $propertyValue = $this->_request->getQuery('property_value');

        if(empty($auid) || empty($secondAuid) || empty($propertyName) || (empty($propertyValue) && !is_numeric($propertyValue)))
        {
            return $this->_setError(3, 'Invalid list of action parameters.');
        }

        if(!preg_match("/^[a-z]*$/",$propertyName))
        {
            return $this->_setError(14, 'Property name does not match [a-z] pattern.');
        }

        $usersModel = new Users();
        $user = $usersModel->getByAuid($auid,array('_id'));
        if(!$user)
        {
            return $this->_setError(10, 'User with auid = '.$auid.' not found.');
        }

        $secondUser = $usersModel->getByAuid($secondAuid,array('_id'));
        if(!$secondUser)
        {
            return $this->_setError(10, 'User with auid = '.$secondAuid.' not found.');
        }

        $propertiesModel = new Properties();
        $propertiesModel->add($auid,$secondAuid,$propertyName,$propertyValue);
    }


    public function getedgepropertyAction()
    {
        $auid = $this->_request->getQuery('auid1');
        $secondAuid = $this->_request->getQuery('auid2');
        $propertyName = strtolower($this->_request->getQuery('property_name'));

        if(empty($auid) || empty($secondAuid) || empty($propertyName))
        {
            return $this->_setError(3, 'Invalid list of action parameters.');
        }

        if(!preg_match("/^[a-z]*$/",$propertyName))
        {
            return $this->_setError(14, 'Property name does not match [a-z] pattern.');
        }

        $usersModel = new Users();
        $user = $usersModel->getByAuid($auid,array('_id'));
        if(!$user)
        {
            return $this->_setError(10, 'User with auid = '.$auid.' not found.');
        }

        $secondUser = $usersModel->getByAuid($secondAuid,array('_id'));
        if(!$secondUser)
        {
            return $this->_setError(10, 'User with auid = '.$secondAuid.' not found.');
        }

        $propertiesModel = new Properties();
        $property = $propertiesModel->getProperty($propertyName);
        if(!$property)
        {
            return $this->_setError(15, 'Property '.$propertyName.' not found.');
        }
        $propertyArray = array();
        $userProperty = $propertiesModel->getUsersProperty($auid,$secondAuid,$propertyName);
        if(isset($userProperty['value']))
        {
            $propertyArray[$propertyName] = $userProperty['value'];
        }
        $this->view->get_edge_property = $propertyArray;
    }


    public function getuserscountAction()
    {
        $usersModel = new Users();
        $this->view->users_count = $usersModel->getUsersCount();
    }


    public function finduserAction()
    {
        $snid = $this->_request->getQuery('snid');
        $snuid = $this->_request->getQuery('snuid');
        $passportid = $this->_request->getQuery('passportid',false);

        if(empty($snid) || empty($snuid))
        {
            return $this->_setError(3, 'Invalid list of action parameters.');
        }
        if($snid && !in_array($snid, Assistant::$SNLIST))
        {
            return $this->_setError(21, 'Social network with snid = '.$snid.' not found.');
        }

        $usersModel = new Users();
        $user = false;
        switch ($snid)
        {
            case 'arc':
            case 'gmg':
                if($passportid)
                {
                    $user = $usersModel->getUserInfo(array($snid.'.passportid' => $passportid),array('_id'));
                    $user['find_by']='passportid'; // reference
                }else
                {
                    $user = $usersModel->getSnUser($snid,strtolower($snuid),array('_id'));
                    $user['find_by']='account';
                }
            break;

            default:
                $user = $usersModel->getSnUser($snid,$snuid,array('_id'));
            break;
        }

        if(!$user || !isset($user['_id']))
        {
            return $this->_setError(8, 'User with snuid = '.$snuid.' not found.');
        }
        $this->view->auid = $user['_id'];
        if(isset($user['find_by']))
        {
            $this->view->find_by = $user['find_by'];
        }
    }

    public function getusersnlistAction()
    {
        $snid = $this->_request->getQuery('snid');
        $snuid = $this->_request->getQuery('snuid');

        if(empty($snid) || empty($snuid))
        {
            return $this->_setError(3, 'Invalid list of action parameters.');
        }
        if($snid && !in_array($snid, Assistant::$SNLIST))
        {
            return $this->_setError(21, 'Social network with snid = '.$snid.' not found.');
        }

        $usersModel = new Users();
        $user = $usersModel->getSnUser($snid,$snuid,Assistant::$SNLIST);
        if(!$user)
        {
            return $this->_setError(8, 'User with snuid = '.$snuid.' not found.');
        }
        $snlist = array();
        foreach (Assistant::$SNLIST as $snid)
        {
            if (isset($user[$snid]['snuid']))
                $snlist[] = $snid;
        }
        $this->view->auid = $user['_id'];
        $this->view->snlist = $snlist;
    }

    /**
     * @deprecated
     * @return boolean
     */
    public function postAction()
    {
        Assistant::logger(
            ' [ postAction: Method is deprecated and no longer supported. ] '.
            (isset($this->_request) ? ' Request: ['. json_encode($this->_request).' ]' :''),
            Sa_Log::ERR
        );
        return $this->_setError(30, 'Method is deprecated and no longer supported.');

        $snid = $this->_request->getQuery('snid');

        $auid = $this->_request->getQuery('auid');

        $message = $this->_request->getQuery('message');

        $link = $this->_request->getQuery('link');

        $picture = $this->_request->getQuery('picture');

        $caption = $this->_request->getQuery('caption');

        $description = $this->_request->getQuery('description');

        $source = $this->_request->getQuery('source');

        if(empty($auid) || empty($message))
        {
            return $this->_setError(3, 'Invalid list of action parameters.');
        }
        if($snid && !in_array($snid,array('fb','vk')))
        {
            return $this->_setError(21, 'Social network with snid = '.$snid.' not found.');
        }

        $data = array('message' => $message);

        if(!empty($link))
        {
            $data['link'] = $link;
        }

        if(!empty($picture))
        {
            $data['picture'] = $picture;
        }

        if(!empty($caption))
        {
            $data['caption'] = $caption;
        }

        if(!empty($description))
        {
            $data['description'] = $description;
        }
        if(!empty($source))
        {
            $data['source'] = $source;
        }

        $usersModel = new Users();
        $user = $usersModel->getByAuid($auid,array('_id','fb.sntoken','fb.snuid','vk.sntoken','vk.snuid','pwc.snuid','st.snuid','ae.snuid','mru.snuid','msv.snuid', 'dlt.snuid'));
        if(!$user)
        {
            return $this->_setError(10, 'User with auid = '.$auid.' not found.');
        }
        if(!empty($snid) && !isset($user[$snid]['snuid']))
        {
            return $this->_setError(16, 'Service with snid = '.$snid.' not connected by user with auid = '.$auid);
        }
        $config = Zend_Registry::get('config');
        $gearmanConfig = $config->gearman->toArray();
        $client= new GearmanClient();
        $client->addServers($gearmanConfig['servers']);
        switch ($snid)
        {
            case 'fb':
                $data = array(
                    'access_token' => $user['fb']['sntoken'],
                    'postTo' => $user['fb']['snuid'],
                    'data' => $data,
                );
                $client->doBackground('facebookPost', serialize($data));
                break;
            case 'vk':
                $data = array(
                    'access_token' => $user['vk']['sntoken'],
                    'postTo' => $user['vk']['snuid'],
                    'data' => $data,
                );
                $client->doBackground('vkontaktePost', serialize($data));
                break;
            default:
                if(isset($user['fb']['snuid']) && isset($user['fb']['sntoken']))
                {
                    $data = array(
                        'access_token' => $user['fb']['sntoken'],
                        'postTo' => $user['fb']['snuid'],
                        'data' => $data,
                    );
                    $client->doBackground('facebookPost', serialize($data));
                }
                if(isset($user['vk']['snuid']) && isset($user['vk']['sntoken']))
                {
                    $data = array(
                        'access_token' => $user['vk']['sntoken'],
                        'postTo' => $user['vk']['snuid'],
                        'data' => $data,
                    );
                    $client->doBackground('vkontaktePost', serialize($data));
                }
                break;
        }
    }


    /**
     * @deprecated
     * @return boolean
     */
    public function posttofriendAction()
    {
        Assistant::logger(
            ' [ posttofriendAction: Method is deprecated and no longer supported. ] '.
            (isset($this->_request) ? ' Request: ['. json_encode($this->_request).' ]' :''),
            Sa_Log::ERR
        );
        return $this->_setError(30, 'Method is deprecated and no longer supported.');

        $friendSnid = $this->_request->getQuery('friend_snid');

        $friendSnuid = $this->_request->getQuery('friend_snuid');

        $fromAuid = $this->_request->getQuery('from_auid');

        $message = $this->_request->getQuery('message');

        $link = $this->_request->getQuery('link');

        $picture = $this->_request->getQuery('picture');

        $caption = $this->_request->getQuery('caption');

        $description = $this->_request->getQuery('description');

        $source = $this->_request->getQuery('source');

        if(empty($fromAuid) || empty($message) || empty($friendSnid) || empty($friendSnuid))
        {
            return $this->_setError(3, 'Invalid list of action parameters.');
        }
        if(!in_array($friendSnid,array('fb','vk')))
        {
            return $this->_setError(21, 'Social network with snid = '.$friendSnid.' not found.');
        }

        $data = array('message' => $message);

        if(!empty($link))
        {
            $data['link'] = $link;
        }

        if(!empty($picture))
        {
            $data['picture'] = $picture;
        }

        if(!empty($caption))
        {
            $data['caption'] = $caption;
        }

        if(!empty($description))
        {
            $data['description'] = $description;
        }
        if(!empty($source))
        {
            $data['source'] = $source;
        }

        $usersModel = new Users();
        $user = $usersModel->getByAuid($fromAuid,array('_id','fb.sntoken','fb.snuid','vk.snuid','vk.sntoken'));
        if(!$user)
        {
            return $this->_setError(10, 'User with auid = '.$fromAuid.' not found.');
        }
        if(!isset($user[$friendSnid]['snuid']))
        {
            return $this->_setError(16, 'Service with snid = '.$friendSnid.' not connected by user with auid = '.$fromAuid);
        }
        $friendsSnuids = array();
        $friendsModel = new Friends();
        $friendsInfo = $friendsModel->getSnFriendsInfo($friendSnid,$fromAuid,array(0,1));
        foreach ($friendsInfo as $friend)
        {
            $friendsSnuids[] = $friend['snuid'];
        }
        if(!in_array($friendSnuid,$friendsSnuids))
        {
            return $this->_setError(17, 'Friend relationship does not exist for service with snid = '.$friendSnid);
        }
        switch ($friendSnid)
        {
            case 'fb':
                $config = Zend_Registry::get('config');
                $gearmanConfig = $config->gearman->toArray();
                $client= new GearmanClient();
                $client->addServers($gearmanConfig['servers']);
                $data = array(
                    'access_token' => $user['fb']['sntoken'],
                    'postTo' => $friendSnuid,
                    'data' => $data,
                );
                $client->doBackground('facebookPost', serialize($data));
                break;
            case 'vk':
                $config = Zend_Registry::get('config');
                $gearmanConfig = $config->gearman->toArray();
                $client= new GearmanClient();
                $client->addServers($gearmanConfig['servers']);
                $data = array(
                    'access_token' => $user['vk']['sntoken'],
                    'postTo' => $friendSnuid,
                    'data' => $data,
                );
                $client->doBackground('vkontaktePost', serialize($data));
                break;
        }
    }


    public function setpropertyAction()
    {
        $propertyName = $this->_request->getQuery('property_name');
        $propertyValue = $this->_request->getQuery('property_value');

        $auid = $this->_request->getQuery('auid');

        if(empty($auid) || empty($propertyName) || (empty($propertyValue) && !is_numeric($propertyValue)))
        {
            return $this->_setError(3, 'Invalid list of action parameters.');
        }

        if(!preg_match("/^[a-z]*$/",$propertyName))
        {
            return $this->_setError(14, 'Property name does not match [a-z] pattern.');
        }
        $usersModel = new Users();
        $user = $usersModel->getByAuid($auid,array('_id'));
        if(!$user)
        {
            return $this->_setError(10, 'User with auid = '.$auid.' not found.');
        }
        $usersModel->edit($auid,array($propertyName => $propertyValue));
    }


    public function getpropertyAction()
    {
        $propertyName = $this->_request->getQuery('property_name');

        $auid = $this->_request->getQuery('auid');

        if(empty($auid) || empty($propertyName))
        {
            return $this->_setError(3, 'Invalid list of action parameters.');
        }

        if(!preg_match("/^[a-z]*$/",$propertyName))
        {
            return $this->_setError(14, 'Property name does not match [a-z] pattern.');
        }
        $usersModel = new Users();
        $user = $usersModel->getByAuid($auid,array($propertyName));
        if(!$user)
        {
            return $this->_setError(10, 'User with auid = '.$auid.' not found.');
        }
        $propertyArray = array();
        if(isset($user[$propertyName]))
        {
            $propertyArray[$propertyName] = $user[$propertyName];
        }
        $this->view->get_property = $propertyArray;
    }


    public function getallpropertiesAction()
    {
        $auid = $this->_request->getQuery('auid');

        if(empty($auid))
        {
            return $this->_setError(3, 'Invalid list of action parameters.');
        }
        $usersModel = new Users();
        $user = $usersModel->getByAuid($auid);
        if(!$user)
        {
            return $this->_setError(10, 'User with auid = '.$auid.' not found.');
        }
        $propertiesArray = array();
        foreach ($user as $propertyName => $propertyValue)
        {
            if(!in_array($propertyName,Assistant::$standartProperties))
            {
                $propertiesArray[$propertyName] = $propertyValue;
            }
        }
        $this->view->get_all_properties = $propertiesArray;
    }


    public function getbillingstatusAction()
    {
        $auid = $this->_request->getQuery('auid');

        if(empty($auid))
        {
            return $this->_setError(3, 'Invalid list of action parameters.');
        }
        $usersModel = new Users();
        $user = $usersModel->getByAuid($auid);
        if(!$user)
        {
            return $this->_setError(10, 'User with auid = '.$auid.' not found.');
        }
        $billingStatus = 0;
        if(isset($user['billing_status']) && $user['billing_status'] == 1)
        {
            $billingStatus = 1;
        }
        $this->view->get_billing_status = $billingStatus;
    }


    public function retrybillingregistrationAction()
    {
        $auid = $this->_request->getQuery('auid');
        $test = $this->_request->getQuery('test');
        if(empty($auid))
        {
            return $this->_setError(3, 'Invalid list of action parameters.');
        }
        $usersModel = new Users();
        $user = $usersModel->getByAuid($auid);
        if(!$user)
        {
            return $this->_setError(10, 'User with auid = '.$auid.' not found.');
        }
        if(isset($user['billing_status']) && $user['billing_status'] == 1)
        {
            return $this->_setError(18, 'User already exists in billing.');
        }
        $snid = IndexController::_getUserSnid($user);
        if($snid)
        {
            if (!array_key_exists('referral', $user)) $user['referral'] = '';
            if($this->_billingRegisterTry($auid, $snid, $user, $test, $usersModel))
            {
                return true;
            }
            else
            {
                $error = $this->view->warning;
                unset($this->view->warning);
                return $this->_setError(19, $error);
            }
        }
    }


    public function joinAction()
    {
        $snid = $this->_request->getQuery('snid');
        $snuid = $this->_request->getQuery('snuid');
        $sntoken = $this->_request->getQuery('sntoken');
        $auid = $this->_request->getQuery('auid');
        $snRefreshToken = $this->_request->getQuery('snrefresh_token');

        if(!$snid)
        {
            return $this->_setError(3, 'Invalid list of action parameters: no snid.');
        }
        if(empty($snuid))
        {
            return $this->_setError(3, 'Invalid list of action parameters: empty snuid.');
        }
        if(empty($sntoken))
        {
            return $this->_setError(3, 'Invalid list of action parameters: empty sntoken.');
        }
        if(($snid == 'ok' || $snid == 'mru' || ($snid == 'ae' && $verify)) && !$snRefreshToken)
        {
            return $this->_setError(3, 'Invalid list of action parameters: no refresh_token for snid='.$snid.'.');
        }
        if(!in_array($snid,Assistant::$SNLIST))
        {
            return $this->_setError(21, 'Social network with snid = '.$snid.' not found.');
        }
        $usersModel = new Users();
        $user = $usersModel->getByAuid($auid);
        if(!$user)
        {
            return $this->_setError(10, 'User with auid = '.$auid.' not found.');
        }
        if(isset($user[$snid]))
        {
            return $this->_setError(22, 'Service with snid = '.$snid.' already connected by user with auid = '.$auid);
        }
        $user = $usersModel->getSnUser($snid,$snuid,array('_id'));
        if($user)
        {
            return $this->_setError(9, 'User already exists in database.');
        }
        $snUserModel = IndexController::_getSnUserModel($snid);
        if(!$this->_validateSnToken($snUserModel, $snuid, $sntoken))
        {
            return false;
        }
        $snUserData = $snUserModel->requestFullUserData($snuid, $sntoken, $snRefreshToken);
        if(isset($snUserData['error']))
        {
            return $this->_setError($snUserData['error'], $snUserData['message']);
        }
        /**
         * don`t remove.Double check because we wait 1-4 seconds for response
         */
        $user = $usersModel->getSnUser($snid,$snuid,array('_id'));
        if($user)
        {
            return $this->_setError(9, 'User already exists in database.');
        }
        $this->_addNewNetwork($snUserData,$auid);
    }


    public function mergeAction()
    {
        $auid = $this->_request->getQuery('auid1');
        $secondAuid = $this->_request->getQuery('auid2');

        if(empty($auid) || empty($secondAuid))
        {
            return $this->_setError(3, 'Invalid list of action parameters.');
        }
        $usersModel = new Users();
        $user = $usersModel->getByAuid($auid);
        if(!$user)
        {
            return $this->_setError(10, 'User with auid = '.$auid.' not found.');
        }

        $secondUser = $usersModel->getByAuid($secondAuid);
        if(!$secondUser)
        {
            return $this->_setError(10, 'User with auid = '.$secondAuid.' not found.');
        }
        foreach (array( 'pwc', 'fb', 'vk', 'ok', 'st', 'ae', 'mru', 'msv','zzma', 'dlt') as $sn)
        {
            if(isset($user[$sn]) && $secondUser["fsn"]===$sn)
            {
                return $this->_setError(33, 'User with auid = '.$secondAuid.' can\'t be merged to auid ='.$auid.'Main account has already included this type of sn');
            }
        }

        $res = $usersModel->mergeAccounts($user,$secondUser);
        if (isset($res['pwc_snuid']))
        {
            $this->view->pwc_snuid = $res['pwc_snuid'];
        }
        elseif (isset($res['pwc_unused']))
        {
            $this->view->pwc_unused = $res['pwc_unused'];
        }
    }


    public function logoutAction()
    {
        $auid = $this->_request->getQuery('auid');

        if(empty($auid))
        {
            return $this->_setError(3, 'Invalid list of action parameters.');
        }

        $usersModel = new Users();
        $user = $usersModel->getByAuid($auid,array('_id'));
        if(!$user)
        {
            return $this->_setError(10, 'User with auid = '.$auid.' not found.');
        }
        $usersModel->edit($user['_id'],array('dt_last_logout' => time()));
    }


    public function deletesocialnetworkAction()
    {
        $snid = $this->_request->getQuery('snid');
        $auid = $this->_request->getQuery('auid');

        if(empty($auid) || empty($snid))
        {
            return $this->_setError(3, 'Invalid list of action parameters.');
        }
        if(!in_array($snid, Assistant::$SNLIST))
        {
            return $this->_setError(21, 'Social network with snid = '.$snid.' not found.');
        }
        $usersModel = new Users();
        $user = $usersModel->getByAuid($auid,array('_id','fb.snuid','vk.snuid','ok.snuid', 'pwc.snuid','st.snuid','ae.snuid','mru.snuid','msv.snuid','zzma.snuid','dlt.snuid','fsn'));
        if(isset($user['fsn']) && ($snid == $user['fsn']))
        {
            return $this->_setError(29, "Service with snid = $snid is fsn-service for user $auid and CAN\'T be disconnected.");
        }
        if(!$user)
        {
            return $this->_setError(10, 'User with auid = '.$auid.' not found.');
        }
        if(!isset($user[$snid]['snuid']))
        {
            return $this->_setError(16, 'Service with snid = '.$snid.' not connected by user with auid = '.$auid);
        }
        if(count($user) < 3)
        {
            return $this->_setError(24, 'Only one service connected by user with auid = '.$auid);
        }
        $this->view->snuid = $user[$snid]['snuid'];
        $usersModel->disconnectAccount($auid,$snid);

    }
    
    
    public function deleteaccountAction()
    {
        $auid = $this->_request->getQuery('auid');
        if (empty($auid))
        {
            return $this->_setError(3, 'Invalid list of action parameters.');
        }
        
        $usersModel = new Users();
        $user = $usersModel->getByAuid($auid, array('_id'));
        if (!$user) {
            return $this->_setError(10, 'User with auid = '.$auid.' not found.');
        }
        
        $this->view->auid = $auid;
        $usersModel->deleteAccount($auid);
    }


    public function setgenderAction()
    {
        $snid = $this->_request->getQuery('snid');
        $auid = $this->_request->getQuery('auid');
        $gender = $this->_request->getQuery('gender');
        $force = $this->_request->getQuery('force', false);

        if(!$snid || empty($auid) || (empty($gender) && $gender != '0'))
        {
            return $this->_setError(3, 'Invalid list of action parameters.');
        }
        if(!in_array($snid,Assistant::$SNLIST))
        {
            return $this->_setError(21, 'Social network with snid = '.$snid.' not found.');
        }
        $gender_int = is_numeric($gender) ? $gender + 0 : -1;
        if(!in_array($gender_int, array(0, 1, 2)))
        {
            return $this->_setError(25, 'Invalid gender parameter value: ' . strval($gender));
        }
        $usersModel = new Users();
        $user = $usersModel->getByAuid($auid,array('_id',$snid));
        if(!$user)
        {
            return $this->_setError(10, 'User with auid = '.$auid.' not found.');
        }
        if(!isset($user[$snid]))
        {
            return $this->_setError(16, 'Service with snid = '.$snid.' not connected by user with auid = '.$auid);
        }
        if(!empty($user[$snid]['gender']) && $user[$snid]['gender'] != 0 && !$force)
        {
            return $this->_setError(26, 'User ' . $auid . ' has got gender value already. Use force=1 to override.');
        }
        $usersModel->setGender($auid, $snid, $gender);
    }

    public function getaeriatokenAction()
    {
        $auid = $this->_request->getQuery('auid');
        if(empty($auid))
        {
            return $this->_setError(3, 'Invalid list of action parameters.');
        }
        $usersModel = new Users();
        $user = $usersModel->getByAuid($auid,array('_id','ae'));
        if(!$user)
        {
            return $this->_setError(10, 'User with auid = '.$auid.' not found.');
        }
        if(!isset($user['ae']))
        {
            return $this->_setError(16, 'AeiaGames (\'ae\') service not connected by user with auid = '.$auid);
        }
        $this->view->sntoken = $user['ae']['sntoken'];
    }

    public function refreshaeriatokenAction()
    {
        $auid = $this->_request->getQuery('auid');
        if(empty($auid))
        {
            return $this->_setError(3, 'Invalid list of action parameters.');
        }
        $usersModel = new Users();
        $user = $usersModel->getByAuid($auid,array('_id','ae'));
        if(!$user)
        {
            return $this->_setError(10, 'User with auid = '.$auid.' not found.');
        }
        if(!isset($user['ae']))
        {
            return $this->_setError(16, 'AeiaGames (\'ae\') service not connected by user with auid = '.$auid);
        }
        $aeriaUsers = IndexController::_getSnUserModel('ae');
        $refreshed = $aeriaUsers->refreshToken($user['ae']['snrefresh_token']);
        if (isset($refreshed['error']))
        {
            return $this->_setError($refreshed['error'], $refreshed['message']);
        }
        $update = array(
            'ae.sntoken' => $refreshed['access_token'],
            'ae.snrefresh_token' => $refreshed['refresh_token'],
        );
        if (!$usersModel->edit($auid, $update))
        {
            Assistant::logger('Error storing updated Aeria tokens for user '.$auid);
        }
        $this->view->sntoken = $refreshed['access_token'];
    }

    /* To return to GM-tool the list of SN-lists. */
    public function listsnAction()
    {
        $this->view->snlist = Assistant::$SNLIST;
    }

    public function getusersbyruidAction()
    {
        $ruid = $this->_request->getQuery('ruid');
        if(empty($ruid))
        {
            return $this->_setError(3, 'Invalid list of action parameters.');
        }
        $usersModel = new Users();
        $users = $usersModel->getByRuid($ruid);
        if(empty($users))
        {
            return $this->_setError(10, "Users with ruid = ".$ruid." weren't found.");
        }
        $this->view->users = $users;

    }

    private function _setError($code, $message)
    {
        $this->view->error = $code;
        $this->view->message = $message;
        return false;
    }
}
?>
