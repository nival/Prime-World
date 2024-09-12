<?php
class ZzimaGameAPI extends ZZimaGameError {

    protected $app_id;
    protected $app_key;
    protected $app_secret;
    protected $sn_game_id = null;
    protected $sn_user_id = null;

    protected $response = null;
    protected $request = null;
    protected $request_dec = null;
    protected $response_type = 'json';  // default type json
    protected $response_status = 0;
    protected $is_app_user = 0;
    protected $game_data = array();
    protected $errorHandler;

    protected $dbg_secret = null;
    protected $dbg_string = null;
    
    protected $req_params = array(
        'api_key',
        'sig',
        'game_id',
        'app_user',

        'method',
    );

    protected $allowed_method = array(
        'users.getInfo'     => 'getUsersInfo',

        'friends.get'       => 'getUsersFriend',
        'friends.getapp'    => 'getUsersAppFriend',

        'notifications.send' => 'sendInvite',

        'request.invite'    => 'sendInvite',

    );


    function  __construct($request = array()) {
        define('NO_PANIC_ON_DB_ERROR', '1');
        $this->errorHandler = new ZZimaGameError();
        if(!empty($request)) {
            
            $request['method'] =  get_magic_quotes_gpc() ? stripslashes($request['method']) : $request['method'];
            $request['method'] = urldecode($request['method']);
            $request['method'] = str_replace(" ", "+", $request['method']);
            $this->request = $request;
            foreach ($this->request as $p=>$v) {
                $this->request_dec[$p] = base64_decode($v);
            }
        }
        $this->makeResponse();
    }

    protected function checkIsAppUser() {
        $user_ids = Utils::decode_id($this->sn_user_id);
        if(Games::isMember($user_ids, $this->game_data['game_id'])) {
            $this->is_app_user = 1;
        }
    }

    public function getResponse() {
        return $this->response;
    }

    protected function makeResponse() {
        if(!is_null($this->request_dec)) {
            try {
                $this->parseRequest();
                if($this->response === null) {
                    $this->preMakeResponse();
                }
            } catch (AppException $e) {
                $this->errorHandler->setError(4);
                $this->response['error'] = $this->errorHandler->getError(4);
                $this->response['request'] = $this->request_dec;
                $this->response['status'] = 0;
            }
    
        } else {
            $this->errorHandler->setError(100);
            $this->preMakeResponse();
        }
        $this->response = $this->response_type === 'xml' ? Utils::convertToXML($this->response) : json_encode($this->response);
    }

    protected function preMakeResponse($response = null) {
        $err = $this->errorHandler->getError();
        $this->response_status =  (empty($err)) ? 1 : 0;
        if($this->response_status && $response) {
            $response['result'] = $this->response_status;
            //$response['is_app_user'] = $this->is_app_user;
            $this->response['response'] = $response;
        } else {
            if(isset($err[4])) $err = array(4=>$err[4]);
            $response['error'] = $err;
            $response['request'] = $this->request_dec;
            $response['result'] = $this->response_status;
            $this->response['response'] = $response;
        }
    }

    protected function parseRequest() {

        if(!empty ($this->request['user'])) $this->sn_user_id = $this->request_dec['user'];

        if(!empty ($this->request['game'])) $this->sn_game_id = $this->request_dec['game'];
        
        if(!$this->checkAppKey()) $this->errorHandler->setError(101);

        if(strcmp($this->app_secret, $this->request['sig']) !== 0) {
            $this->errorHandler->setError(102);
            $str  = "\n".date('Y-m-d H:i:s').' ----Signature Error------ '."\n";
            $str .= 'Request signature - '.$this->request['sig']."\n";
            $str .= 'Server signature  - '.$this->app_secret."\n";
            $str .= 'Request data - '."\n".var_export($this->request_dec,1)."\n";
            $str .= 'Game Data - '."\n".var_export($this->game_data, 1)."\n";
            $str .= 'Generated string - '.$this->dbg_string."\n";
            $str .= '------------'."\n\n";
            Log::addApi($str);
        }

        $err = $this->errorHandler->getError();

        $this->checkFormat();
        $this->checkIsAppUser();
        if(empty($err)) {
            if(!empty ($this->request_dec['method'])) {
                $methodHash = explode(',',$this->request_dec['method']);
                $this->execMethod($methodHash);
            } else {
                $this->errorHandler->setError(103);
            }

            if($this->response == null) {
                $err = $this->errorHandler->getError();
                if($this->response === null && $err) $this->response['error'] = $err;
                if(!$this->response_status) $this->response['request'] = $this->request;
            }
        } 
    }

    protected function checkFormat() {
        if(!empty ($this->request_dec['format'])) {
            $format = strtolower($this->request_dec['format']);
            if($format === 'json' || $format === 'xml') {
                $this->response_type = $format;
            }
        }
    }

    protected function checkAppKey() {
        if(empty ($this->request['api_key'])) return false;
        try {
            $result = Games::getGameByAppKey($this->request_dec['api_key']);
            if(is_array($result)) {
                $this->game_data = $result;
                $this->generateSecret($result['app_secret']);
                return true;
            } else {
                $this->errorHandler->setError(101);
                return false;
            }
        } catch (AppException $e) {
            $this->errorHandler->setError(4);
        }
        
    }

    private function generateSecret($secret_code = null) {
        $request_string = '';
        foreach($this->request as $p=>$v) {
            if($p == 'sig') continue;
            $request_string .= $p . '=' . $v;
        }
        $this->dbg_secret = $secret_code;
        $this->dbg_string = $request_string;
        $this->app_secret = md5($request_string.$secret_code);
    }

    protected function execMethod($method) {
        if(isset ($method[0]) && isset($this->allowed_method[$method[0]])) {
            eval('$this->'.$this->allowed_method[$method[0]].'($method);');
        } else {
            $this->errorHandler->setError(103);
        }
    }
    
    /**
     * Return user profile information
     *
     * @param $user_id (intval)     - required
     * @param $picture (string)     - optional
     * @param $personal (string)    - optional
     *
     */

    private function getUsersInfo($params = null, $is_external = true) {
        $response   = null;
        $userId     = (int)$params[1];
        
        $picture    = (!empty ($params[2]) && (int) $params[2]) ? 1 : 0;
        $ext        = (!empty($params[3]) && (int) $params[3]) ? 1 : 0;

        try {
            $user = User::getBaseInfo($userId, $picture);
            if(!isset($user['user_id'])) {
                $this->errorHandler->setError(200);
            } else {
                $htsr = Storage::getImage($user['user_id'], $user['spam_code'], IMAGE_USERPIC, IMAGE_BIG, $user['sex']);
                $response['user_id'] = $user['user_id'];
                $response['first_name'] = $user['first_name'];
                $response['last_name'] = $user['last_name'];
                $response['nick'] = $user['nickname'];
                $response['sex'] = $user['sex'];
                $response['profile'] = WEBROOT.'player/'.$user['nickname'];
                if($picture) {
                    $response['picture_80'] = Storage::getImageSrc($htsr['src'], 80, 80, 'crop', $user['image_crop']);
                    $response['picture_50'] = Storage::getImageSrc($htsr['src'], 50, 50, 'crop', $user['image_crop']);
                }
                // extended info
                if($ext) {
                        $response['email']  = $user['email'];
                }
            }
        } catch (AppException $e) {
            $this->errorHandler->setError(4);
        }
        if($is_external) {
            $this->preMakeResponse($response);
        } else {
            return $response;
        }
    }

    /**
     * Return user friends
     * @param $user_id      (intval)        - required (user identifer)
     * @param $ext          (boolean)   - optional (extendet response 1 - full information, 0 - only id)
     *
     * @return $response    (array xor)     - if ext == 1 full user information else id hash
     */
    private function getUsersFriend($params) {
        $response = null;

        $userId = Utils::decode_id($params[1]);
        $ext = (!empty ($params[2]) && (int) $params[2]) ? 1 : 0;
        try {
            $friends = Friends::getFriendIds($userId);
            $ids = array();
            foreach ((array)$friends as $friendId) {
                if($ext) {
                    $params = array(0, Utils::code_id($friendId),1);
                    $ids[] = $this->getUsersInfo($params, false);
                } else {
                    $ids[] = Utils::code_id($friendId);
                }
            }
            $response['friends'] = $ids;
        } catch (AppException $e) {
            $this->errorHandler->setError(4);
        }
        $this->preMakeResponse($response);
    }

    /**
     * Return application friend
     * @param $user_id      (intval)        - required (user identifer)
     * @param $ext          (boolean)       - optional (extendet response 1 - full information, 0 - only id)
     *
     * @return $response    (array xor)     - if ext == 1 full user information else id hash
     */
    private function getUsersAppFriend($params) {
        $response = null;

        $userId = Utils::decode_id($params[1]);
        $ext = (!empty ($params[2]) && (int) $params[2]) ? 1 : 0;

        try {
            $appFriends = Friends::getFriendIds($userId);
            $ids = array();
            foreach ((array)$appFriends as $friendId) {
                if(Games::isMember($user_ids, $this->game_data['game_id'])) {
                    if($ext) {
                        $params = array('id'=>Utils::code_id($friendId), 'picture'=>1);
                        $ids[] = $this->getUsersInfo($params, false);
                    } else {
                        $ids[] = Utils::code_id($friendId);
                    }
                }
            }
            $response['friends'] = $ids;
        } catch (AppException $e) {
            $this->errorHandler->setError(4);
        }
        $this->preMakeResponse($response);
    }

    /**
     *  Send request to join game
     *
     * @param $userHash     (array)
     */
    private function sendInvite($params) {
        $response = null;
        $userStr = $params[1];
        $userHash = explode(':', $userStr);
        $txtBody  = $params[2];
        $line  = date('Y-m-d H:i:s').' ---- Send Invite -------'."\n";
        $line .= 'User String - '.$userStr."\n";
        $line .= 'User Hash - '.var_export($userHash, 1)."\n";
        $line .= 'Text - '.$txtBody."\n";
        
        if(is_array($userHash)) {
            try {
                $result = array();
                foreach($userHash as $userId) {
                    if(empty ($userId)) continue;
                    $intParam = array(0, $userId, 1, 1);
                    $userInfo = $this->getUsersInfo($intParam, false);
                    $data['full_name'] = $userInfo['nick'];
                    $data['email'] = $userInfo['email'];
                    $data['app_body'] = stripslashes($txtBody);
                    $line .= 'Mail Data - '.var_export($data, 1)."\n";
                    if ($threadId = Mailbox::createThread(array(SYSTEM_ACCOUNT_ID, $userId), SYSTEM_ACCOUNT_ID)) {
                        $res = Mailbox::createMessage(
                            $threadId,
                            SYSTEM_ACCOUNT_ID,
                            array(Utils::decode_id($userId)),
                            Utils::parseLine(_('[%M_GAME_INVITE_TITLE%]'), array('GAME_APP_NAME'=>$this->game_data['name'])),
                            Utils::parseLine(_('[%M_GAME_INVITE_BODY%]'),array('GAME_APP_MESSAGE'=>stripslashes($txtBody))),
                            false,
                            1,
                            Utils::decode_id($userId)
                        );
                    }
                    
//                  if(Notification::apiGameInvite($data)) {
                        $result[] = $userId;
//                  }
                    
                }
                if(empty ($result)) {
                    $this->errorHandler->setError(201);
                } else {
                    App :: sendMails();
                    $response['send_invite'] = $result;
                }
            } catch (AppException $e) {
                $this->errorHandler->setError(4);
            }
        } else {
            $this->errorHandler->setError(104);
        }
        Log::addApi($line);
        $this->preMakeResponse($response);
    }

}

class ZZimaGameError {

    protected $error = array();

    /**
     * Describe errors
     *
     * 100-199 (Reserved. Critical errors (e.g. empty request, bad app key or secret code))
     * 200-299 (Reserved. Major errors (e.q. empty/incorrect method parameters))
     * 300-499 (Reserved. Minor errors)
     *
     * @author  chulim
     * @access  protected
     * @var     array $errorHash
     * 
     */

    protected $errorsHash = array(
        4   => 'Unknown Error',
        100 => 'Bad request',
        101 => 'Application key is not exists',
        102 => 'Bad signature',
        103 => 'Function not found',
        104 => 'Incorrect method params',


        200 => 'Not found user',
        201 => 'Not found recipients',
        202 => 'Not found app friends',

    );

    public function  getError($error = null) {
        if ($error && array_key_exists($error, $this->error)) {
            return $this->errorsHash[$error];
        } else {
            return $this->error;
        }
    }

    public function  setError($value) {
        if (array_key_exists($value, $this->errorsHash)) {
            if(empty ($this->error)) {
                $this->error['code'] = $value;
                $this->error['message'] = $this->errorsHash[$value];
                if($value == 4) {
                    $e = new AppException('Db error');
                    Log::addApi(var_export(array('msg'=>$e->getMessage(),'file'=>$e->getFile(), 'line'=>$e->getLine(), 'trace'=>$e->getTrace()), 1));
                }
            } else {
                return;
            }
        }
    }
}