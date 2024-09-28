<?php
class Assistant
{
    static public $default_http_timeout = 300;
    static public $default_http_connect_timeout = 30;
    static public $SNLIST = array('fb', 'vk', 'ok', 'st', 'ae', 'pwc', 'mru', 'msv','arc','zzma','gmg', 'dlt');
    static public $standartProperties = array('_id','dt_last_login','dt_last_logout','dt_register','billing_status','fb', 'vk', 'ok', 'st', 'ae', 'pwc', 'mru', 'msv','arc','zzma','gmg', 'dlt');

    public static function prepare_request($req, $options, $headers=array())
    {
        $url = (is_array($req) && !empty($req['url'])) ? $req['url'] : $req;
        $ch = curl_init($url);
        curl_setopt($ch, CURLOPT_HEADER,         0);
        curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
        curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, FALSE);
        if (!empty($headers))
            curl_setopt($ch, CURLOPT_HTTPHEADER, $headers);
        $config = Zend_Registry::get('config');
        curl_setopt($ch, CURLOPT_CONNECTTIMEOUT, $config->get('http_connect_timeout', Assistant::$default_http_connect_timeout));
        curl_setopt($ch, CURLOPT_TIMEOUT, $config->get('http_timeout', Assistant::$default_http_timeout));
        if (is_array($req) && !empty($req['post']))
        {
            curl_setopt($ch, CURLOPT_POST,       1);
            curl_setopt($ch, CURLOPT_POSTFIELDS, $req['post']);
        }
        if (count($options)>0) curl_setopt_array($ch, $options);
        return $ch;
    }

    public static function singleCurl($req, $options = array(),$bToJson=true, $headers=array())
    {
        $ch = Assistant::prepare_request($req, $options,$headers);
        $response = $bToJson ? json_decode(curl_exec($ch)) : curl_exec($ch);
        curl_close($ch);
        return $response;
    }

    public static function singleCurlCheckError($req, $options = array(),$headers=array())
    {
        $ch = Assistant::prepare_request($req, $options, $headers);
        $response['result'] = json_decode(curl_exec($ch));
        if(empty($response['result']))
        {
            $response['error'] = curl_error($ch);
            if(!$response['error'])
            {
                $code = curl_getinfo($ch, CURLINFO_HTTP_CODE);
                if ($code != 200)
                {
                    $response['error'] = 'HTTP result code: ' . $code;
                }
                else
                {
                    $response['error'] = 'Unknown connection error occurred';
                }
            }
        }
        curl_close($ch);
        return $response;
    }

    public static function multiCurl($data, $options = array(),$debug=false,$headers=array())
    {
        $curls = array();
        $result = array();
        $bInitOnce=false;
        foreach ($data as $id => $d)
        {
            if($debug)
            {
                 echo '   multiCurl request: '.$d."\n";
            }
            $curls[$id] = Assistant::prepare_request($d, $options, $headers);
            if(!$bInitOnce)
            {
                $mh = curl_multi_init();
                $bInitOnce=true;
            }
            curl_multi_add_handle($mh, $curls[$id]);
        }
        $running = null;
        do { curl_multi_exec($mh, $running); } while($running > 0);
        foreach($curls as $id => $c)
        {
            $result[$id] = curl_multi_getcontent($c);
            curl_multi_remove_handle($mh, $c);
            if($debug)
            {
                echo '   multiCurl response: '.$id.' ---- '.$d."\n";
                var_dump($result[$id]);
                echo "\n";
            }
        }
        curl_multi_close($mh);
        return $result;
    }

    /**
     * @param string $date
     * return int
     */
    public static function getAgeByBirthday($date)
    {
        $date = date("Y-m-d",strtotime($date));
        $birthday = explode("-", $date);
        if ($birthday[0] == '0000')
        {
            return '';
        }
        $fix = 1;
        if (date('m') > $birthday[1])
            $fix = 0;
        elseif (date('m') == $birthday[1])
        {
            if (date('d') > $birthday[2])
            $fix = 0;
        }
        $age = date('Y') - $birthday[0] -  $fix;
        return $age;
    }

    /* generateUserData() and it's private methods */

    private static function _fbUserArray($userFb, $includeSecureData)
    {
        $ua = array(
            'name' => $userFb['name'],
            'gender' => isset($userFb['gender']) && $userFb['gender']!=0 ? $userFb['gender'] : 1,
            'photo' => 'https://graph.facebook.com/'.$userFb['snuid'].'/picture?type=square&width=64&height=64',
            'age' => Assistant::getAgeByBirthday($userFb['dt_birthday']),
        );
        if($includeSecureData == 1)
        {
            $ua['email'] = $userFb['email'];
            $ua['sntoken'] = $userFb['sntoken'];
            $ua['snuid'] = $userFb['snuid'];
        }
        return $ua;
    }

    private static function _pwcUserArray($userPwc, $includeSecureData)
    {
        $ua = array(
            'gender' => isset($userPwc['gender']) && $userPwc['gender']!=0 ? $userPwc['gender'] : 1,
            'age' => Assistant::getAgeByBirthday($userPwc['birthday']),
        );
        if($includeSecureData == 1)
        {
            $ua['email'] = $userPwc['email'];
            $ua['sntoken'] = $userPwc['sntoken'];
            $ua['snuid'] = $userPwc['snuid'];
        }
        return $ua;
    }

    private static function _stUserArray($userSt, $includeSecureData)
    {
        $ua = array(
            'name' => $userSt['name'],
            'photo' => $userSt['photo'],
            'gender' => isset($userSt['gender']) && $userSt['gender']!=0 ? $userSt['gender'] : 1,
        );
        if($includeSecureData == 1)
        {
            $ua['snuid'] = $userSt['snuid'];
        }
        return $ua;
    }

    private static function _aeUserArray($userAe, $includeSecureData)
    {
        $ua = array(
            'name' => $userAe['name'],
            'photo' => $userAe['photo'],
            'gender' => isset($userAe['gender']) && $userAe['gender']!=0 ? $userAe['gender'] : 1,
        );
        if (isset($userAe['dt_birthday']))
        {
            $ua['age'] = Assistant::getAgeByBirthday($userAe['dt_birthday']);
        }
        if($includeSecureData == 1)
        {
            $ua['snuid'] = $userAe['snuid'];
            $ua['sntoken'] = $userAe['sntoken'];
            $ua['snrefresh_token'] = $userAe['snrefresh_token'];
        }
        return $ua;
    }

    private static function _vkUserArray($userVk, $includeSecureData)
    {
        $ua = array(
            'name' => $userVk['name'],
            'gender' => isset($userVk['gender']) && $userVk['gender']!=0 ? $userVk['gender'] : 1,
            'photo' => $userVk['photo'],
        );
        if(isset($userVk['dt_birthday']))
        {
            $ua['age'] = Assistant::getAgeByBirthday($userVk['dt_birthday']);
        }
        if($includeSecureData == 1)
        {
            $ua['sntoken'] = $userVk['sntoken'];
            $ua['snuid'] = $userVk['snuid'];
        }
        return $ua;
    }

    private static function _okUserArray($userOk, $includeSecureData)
    {
        $ua = array(
            'name' => $userOk['name'],
            'gender' => isset($userOk['gender']) && $userOk['gender']!=0 ? $userOk['gender'] : 1,
            'photo' => $userOk['photo'],
        );
        if(isset($userOk['dt_birthday']))
        {
            $ua['age'] = Assistant::getAgeByBirthday($userOk['dt_birthday']);
        }
        if($includeSecureData == 1)
        {
            $ua['sntoken'] = $userOk['sntoken'];
            $ua['snrefresh_token'] = $userOk['snrefresh_token'];
            $ua['snuid'] = $userOk['snuid'];
        }
        return $ua;
    }

    private static function _mruUserArray($userMru, $includeSecureData)
    {
        $ua = array(
            'name' => $userMru['name'],
            'gender' => isset($userMru['gender']) && $userMru['gender']!=0 ? $userMru['gender'] : 1,
            'photo' => $userMru['photo'],
        );
        if(isset($userMru['dt_birthday']))
        {
            $ua['age'] = Assistant::getAgeByBirthday($userMru['dt_birthday']);
        }
        if($includeSecureData == 1)
        {
            $ua['sntoken'] = $userMru['sntoken'];
            $ua['snrefresh_token'] = isset($userMru['snrefresh_token'])?$userMru['snrefresh_token']:false;
            $ua['snuid'] = $userMru['snuid'];
        }
        return $ua;
    }

    private static function _msvUserArray($userMsv, $includeSecureData)
    {
        $ua = array(
            'name' => $userMsv['name'],
            'gender' => isset($userMsv['gender']) && $userMsv['gender']!=0 ? $userMsv['gender'] : 1,
        );
        if($includeSecureData == 1)
        {
            $ua['sntoken'] = $userMsv['sntoken'];
            $ua['snuid'] = $userMsv['snuid'];
        }
        return $ua;
    }
    private static function _arcUserArray($userArc, $includeSecureData)
    {
        $ua = array(
            'name' => $userArc['name'],
            'gender' => 1, // isset($userArc['gender'])?$userArc['gender']
            'passportid' => isset($userArc['passportid'])?$userArc['passportid']:'',
        );
        if($includeSecureData == 1)
        {
            $ua['sntoken'] = $userArc['sntoken'];
            $ua['snuid'] = $userArc['snuid'];
        }
        return $ua;
    }
    private static function _zzmaUserArray($userArc, $includeSecureData)
    {
        $ua = array(
            'name' => $userArc['name'],
            'userName' => $userArc['userName'],
            'gender' => 1,
        );
        if($includeSecureData == 1)
        {
            $ua['sntoken'] = $userArc['sntoken'];
            $ua['snuid'] = $userArc['snuid'];
        }
        return $ua;
    }
    private static function _gmgUserArray($userGmg, $includeSecureData)
    {
        $ua = array();
        if(isset($userGmg['name']))
        {
            $ua['name'] = $userGmg['name'];
        }
        $ua = $ua + array(
            'gender' => 1,
            'passportid' => $userGmg['passportid'],
        );
        if($includeSecureData == 1)
        {
            $ua['sntoken'] = $userGmg['sntoken'];
            $ua['snuid'] = $userGmg['snuid'];
        }
        return $ua;
    }

    private static function _dltUserArray($userDlt, $includeSecureData)
    {
        $ua = array();
        if(isset($userDlt['name']))
        {
            $ua['name'] = $userDlt['name'];
        }
        $ua = $ua + array(
                'gender' => $userDlt["gender"],
            );

        if (isset($userDlt['photo']))
            $ua['photo'] = $userDlt['photo'];

        if($includeSecureData == 1)
        {
            $ua['sntoken'] = $userDlt['sntoken'];
            $ua['snuid'] = $userDlt['snuid'];
        }
        return $ua;
    }

    private static function _selectSnUserArray($snid, $user, $includeSecureData)
    {
        switch ($snid)
        {
            case 'fb':
                return Assistant::_fbUserArray($user['fb'], $includeSecureData);
            case 'pwc':
                return Assistant::_pwcUserArray($user['pwc'], $includeSecureData);
            case 'st':
                return Assistant::_stUserArray($user['st'], $includeSecureData);
            case 'ae':
                return Assistant::_aeUserArray($user['ae'], $includeSecureData);
            case 'vk':
                return Assistant::_vkUserArray($user['vk'], $includeSecureData);
            case 'ok':
                return Assistant::_okUserArray($user['ok'], $includeSecureData);
            case 'mru':
                return Assistant::_mruUserArray($user['mru'], $includeSecureData);
            case 'msv':
                return Assistant::_msvUserArray($user['msv'], $includeSecureData);
            case 'arc':
                return Assistant::_arcUserArray($user['arc'], $includeSecureData);
            case 'zzma':
                return Assistant::_zzmaUserArray($user['zzma'], $includeSecureData);
            case 'gmg':
                return Assistant::_gmgUserArray($user['gmg'], $includeSecureData);
            case 'dlt':
                return Assistant::_dltUserArray($user['dlt'], $includeSecureData);
            default:
                return NULL;
        }
    }

    public static function generateUserData($user,$snid,$includeSecureData)
    {
        if($snid && !isset($user[$snid]))
        {
            return false;
        }
        $userArray = array('dt_register' => $user['dt_register'], 'dt_login' => $user['dt_last_login']);
        $userArray['dt_logout'] =  isset($user['dt_last_logout']) ? $user['dt_last_logout'] : $user['dt_register'];

        foreach ($user as $propertyName => $propertyValue)
        {
            if(!in_array($propertyName,self::$standartProperties))
            {
                $userArray['props'][$propertyName] = $propertyValue;
            }
        }
        $ua = Assistant::_selectSnUserArray($snid, $user, $includeSecureData);
        if (isset($ua))
        {
            $userArray[$snid] = $ua;
        }
        else
        {
            foreach (self::$SNLIST as $sn)
            {
                if (isset($user[$sn]))
                {
                    $userArray[$sn] = Assistant::_selectSnUserArray($sn, $user, $includeSecureData);
                }
            }
        }
        return $userArray;
    }

    public static function mkParamString($params)
    {
        $result = '';
        foreach($params as $key=>$value)
        {
            $result .= $key.'='.$value.'&';
        }
        return rtrim($result,'&');
    }

    private static function _sub_cmp($old, $new)
    {
        return (is_array($old) && is_array($new)) ? array_diff_assoc($new, $old) : ($new != $old);
    }

    public static function diffUsers($userOld, $userNew)
    {
        return array_udiff_assoc($userNew, $userOld, "Assistant::_sub_cmp");
    }

    public static function workerLogMessage($worker, $message, $type)
    {
        $config = Zend_Registry::get('config');
        $client= new GearmanClient();
        $client->addServers($config->gearman->servers);
        $client->doBackground('logBackground', serialize(array('message' => $message, 'type' => $type, 'worker' => $worker)));
    }

    public static function workerSendToSS($data)
    {
        $config = Zend_Registry::get('config');
        $client= new GearmanClient();
        $client->addServers($config->gearman->servers);
        $client->doBackground('sendToSSBackground', serialize($data));
    }

    public static function extractFriendAuid($f)
    {
        return $f['friend_auid'];
    }

    public static function generateBillingCRC($params)
    {
        return md5(join('',$params));
    }

    public static function generateEmail($auid, $snid, $userData, $billingConfig)
    {
        $config = Zend_Registry::get('config');
        $email = '';

        $patternStr = $billingConfig['email_pattern'];
        $patternArray = explode('@',$patternStr);
        if(isset($patternArray[1]))
        {
            if (strpos($patternArray[0], 'auid') !== false)
            {
                $email = str_replace("auid", $auid, $patternArray[0]).'@'.$patternArray[1];
            }
            else
            {
                foreach ($userData[$snid] as $key => $value)
                {
                    if($key == $patternArray[0])
                    {
                        $email = $value.'@'.$patternArray[1];
                    }
                }
            }
        }
        if(empty($email))
        {
            $email = $auid.'@playpw.com';
        }
        return $email;
    }

    public static function logger($str,$_messageType = Sa_Log::INFO,$_serverIdent = 'web')
    {
        static $_logFile = false;
        static $_date = false;
        static $loger = false;
        if ( !isset($_logFile[$_serverIdent]) )
        {
            $_date = date("Y.m.d");
            $config = Zend_Registry::get('config');
            $version = $config->version;
            $fileNamePatern = $_serverIdent.'-'.$version.'-'.$_date;
            $logFileArray = glob($config->path->logs.$fileNamePatern."-*-sa.txt", GLOB_NOSORT);
            $_logFile[$_serverIdent] = isset($logFileArray[0])
                ? $logFileArray[0]
                : $config->path->logs.$_serverIdent.'-'.$version.'-'.$_date.'-sa.txt';
            $loger =  new Sa_Log();
        }
        $message = $_serverIdent.': ' .
            (isset($_SERVER['QUERY_STRING']) ? 'Query string: '.$_SERVER['QUERY_STRING']:'').
            "\nLOG: " . $str;
        $stream = @fopen($_logFile[$_serverIdent], 'a', false);
        if($stream){
            $loger->addWriter(new Zend_Log_Writer_Stream($stream));
            $loger->log($message, $_messageType);
        }
    }

}
