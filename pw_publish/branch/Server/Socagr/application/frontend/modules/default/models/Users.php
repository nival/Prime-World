<?php
class Users
{
    protected $_db;

    public function __construct()
    {
         $this->_db = Mongosa::getInstance();
    }

    public function getUserSequence()
    {
        $result = $this->_db->command(array("findandmodify" => "seq",
            'query' => array('_id' => 'users'),
            'update' => array('$inc' => array('seq' => 1)),
            'new' => TRUE));
        if($result['ok'] == 1)
        {
            return $result['value']['seq'];
        }
        throw new Exception('mongo error: '.$result['errmsg']);
    }

    public function add($data)
    {
        /*
         * Old
         *   Throw a MongoCursorException if the "safe" option is set and the insert fails.
         * New
         *   Changed second parameter to be an array of options.
         *   The options parameter no longer accepts a boolean to signify an acknowledged write.
         *   Instead, this now has to be done with array('w' => 1) (the default behaviour of MongoClient).
         *   public bool|array MongoCollection::insert ( array|object $document [, array $options = array() ] )
         * read http://php.net/manual/ru/mongocollection.insert.php for more information
         *
         */
        $result = $this->_db->users->insert($data); //- array('w' => 1) is default.  For newer mongo version
        if($result['ok'] == 1)
        {
            return $data['_id'];
        }
        throw new Exception('mongo error: '.$result['errmsg']);
    }

    public function remove($auid)
    {
        $result = $this->_db->users->remove(array('_id' => (int)$auid));
        if($result === true || $result['ok'] == 1)
        {
            return true;
        }
        throw new Exception($result['err']);
    }

    public function edit($auid,$data,$options = array())
    {
        return $this->_db->users->update(array('_id' => (int)$auid), array('$set' => $data),$options);
    }

    public function getByAuid($auid,$fields = array())
    {
        return $this->_db->users->findOne(array('_id' => (int)$auid),$fields);
    }

    public function getMultiByAuids($auids,$fields = array())
    {
        return $this->_db->users->find(array('_id' => array('$in' => $auids)),$fields);
    }

    public function getSnUser($snId,$snUid,$fields = array())
    {
        return $this->_db->users->findOne(array($snId.'.snuid' => $snUid),$fields);
    }

    /**
     * use
     *  $aParams = array($snId.'.passportid' => $passportId)
     * @param array $aParams
     * @param array $fields
     */
    public function getUserInfo($aParams,$fields = array())
    {
        return $this->_db->users->findOne($aParams, $fields);
    }

    public function getSnUsers($snId,$snUids,$fields = array())
    {
        return $this->_db->users->find(array($snId.'.snuid' => array('$in' => $snUids)),$fields);
    }

    public function getUsersCount()
    {
        return $this->_db->users->count();
    }

    // db.users.update({"_id":1}, { $set: { "$SN.sntoken_expire": 1 } } )
    public function setSntokenExpire($_id,$SN,$sntoken_expire)
    {
        return $this->_db->users->update(array("_id" => $_id), array( '$set' => array($SN.".sntoken_expire" => $sntoken_expire)));
    }

    public function mergeAccounts($user,$secondUser)
    {
        $friendsModel = new Friends();
        $propertiesModel = new Properties();
        $userEdgePropertiesArray = array();
        // edge properties
        // collect all user's properties, removing props from user to secondUser
        $userEdgeProperties = $propertiesModel->getUserEdgeProperties($user['_id']);
        $res = array();
        foreach ($userEdgeProperties as $userEdgeProperty)
        {
            $edgeAuid = $userEdgeProperty['auid'];
            if($edgeAuid == $user['_id'])
            {
                $edgeAuid = $userEdgeProperty['e_auid'];
            }
            if($edgeAuid == $secondUser['_id'])
            {
                $propertiesModel->removeUsersProperty($user['_id'],$secondUser['_id'],$userEdgeProperty['name']);
            }
            else
            {
                $userEdgePropertiesArray[$userEdgeProperty['name']][$edgeAuid] = $userEdgeProperty['value'];
            }
        }
        // add to user all additional secondUser's props (not overrinding existing ones)
        $secondUserEdgeProperties = $propertiesModel->getUserEdgeProperties($secondUser['_id']);
        foreach ($secondUserEdgeProperties as $secondUserEdgeProperty)
        {
            $edgeAuid = $secondUserEdgeProperty['auid'];
            if($edgeAuid == $secondUser['_id'])
            {
                $edgeAuid = $secondUserEdgeProperty['e_auid'];
            }
            if($edgeAuid != $user['_id'])
            {
                if(!isset($userEdgePropertiesArray[$secondUserEdgeProperty['name']][$edgeAuid]))
                {
                    $propertiesModel->add($user['_id'],$edgeAuid,$secondUserEdgeProperty['name'],$secondUserEdgeProperty['value']);
                }
                $propertiesModel->removeUsersProperty($secondUser['_id'],$edgeAuid,$secondUserEdgeProperty['name']);
            }
        }

        //friends
        $userFriendIds = $friendsModel->getAuidListByAuid($user['_id']);
        $secondUserFriendIds = $friendsModel->getAuidListByAuid($secondUser['_id']);
        $friendsToAdd = array_diff($secondUserFriendIds,$userFriendIds,array($user['_id']));

        foreach ($secondUserFriendIds as $secondUserFriendId)
        {
            $friendsModel->remove($secondUser['_id'],$secondUserFriendId);
        }
        # XXX: this code doesn't care about friendsModel's snid value!
        foreach ($friendsToAdd as $friendToAdd)
        {
           $friendsModel->add($user['_id'],$friendToAdd,'pw');
        }
        //sn friends and sn data
        // remove from secondUser's sn_friends all user's sn_friends
        foreach (array('fb', 'vk', 'ok', 'st', 'ae', 'mru', 'msv','zzma', 'dlt') as $sn)
        {
                if(isset($user[$sn]) && isset($secondUser[$sn]))
                {
                    $friendsModel->removeSnFriends($sn,$secondUser['_id']);
                }
        }
        // ... and add all other secondUser's sn_friend to user's sn_friends
        if(!isset($user['vk']) && isset($secondUser['vk']))
        {
            $friendsData = array();
            $snFriends = $friendsModel->getSnFriendsInfo('vk',$secondUser['_id'],array(0,1,2));
            foreach ($snFriends as $snFriend)
            {
                $friendsData[] = array(
                    'snuid' => $snFriend['snuid'],
                    'name' => $snFriend['name'],
                    'photo' => $snFriend['photo'],
                    'used' => $snFriend['used'],
                );
            }
            if(count($friendsData) > 0)
            {
                $friendsModel->removeSnFriends('vk',$secondUser['_id']);
                $friendsModel->addSnFriends('vk',$user['_id'],$friendsData);
            }
            $this->edit($user['_id'],array('vk' => $secondUser['vk']));
        }
        if(!isset($user['fb']) && isset($secondUser['fb']))
        {
            $friendsData = array();
            $snFriends = $friendsModel->getSnFriendsInfo('fb',$secondUser['_id'],array(0,1,2));
            foreach ($snFriends as $snFriend)
            {
                $friendsData[] = array(
                    'snuid' => $snFriend['snuid'],
                    'name' => $snFriend['name'],
                    'used' => $snFriend['used'],
                );
            }
            if(count($friendsData) > 0)
            {
                $friendsModel->removeSnFriends('fb',$secondUser['_id']);
                $friendsModel->addSnFriends('fb',$user['_id'],$friendsData);
            }
            $this->edit($user['_id'],array('fb' => $secondUser['fb']));
        }
        if(!isset($user['ok']) && isset($secondUser['ok']))
        {
            $friendsData = array();
            $snFriends = $friendsModel->getSnFriendsInfo('ok',$secondUser['_id'],array(0,1,2));
            foreach ($snFriends as $snFriend)
            {
                $friendsData[] = array(
                    'snuid' => $snFriend['snuid'],
                    'name' => $snFriend['name'],
                    'photo' => $snFriend['photo'],
                    'used' => $snFriend['used'],
                );
            }
            if(count($friendsData) > 0)
            {
                $friendsModel->removeSnFriends('ok',$secondUser['_id']);
                $friendsModel->addSnFriends('ok',$user['_id'],$friendsData);
            }
            $this->edit($user['_id'],array('ok' => $secondUser['ok']));
        }
        if(isset($secondUser['pwc']))
        {

            if(!isset($user['pwc']))
            {
                $this->edit($user['_id'],array('pwc' => $secondUser['pwc']));
                $res['pwc_snuid'] = $secondUser['pwc']['snuid'];
            }
            else
            {
                $res['pwc_unused'] = $secondUser['pwc']['snuid'];
            }
        }
        if(!isset($user['st']) && isset($secondUser['st']))
        {
            $friendsData = array();
            $snFriends = $friendsModel->getSnFriendsInfo('st',$secondUser['_id'],array(0,1,2));
            foreach ($snFriends as $snFriend)
            {
                $friendsData[] = array(
                    'snuid' => $snFriend['snuid'],
                    'name' => isset($snFriend['name']) ? $snFriend['name'] : "",
                    'used' => $snFriend['used'],
                );
            }
            if(count($friendsData) > 0)
            {
                $friendsModel->removeSnFriends('st',$secondUser['_id']);
                $friendsModel->addSnFriends('st',$user['_id'],$friendsData);
            }
            $this->edit($user['_id'],array('st' => $secondUser['st']));
        }
        if(!isset($user['ae']) && isset($secondUser['ae']))
        {
            $friendsData = array();
            $snFriends = $friendsModel->getSnFriendsInfo('ae',$secondUser['_id'],array(0,1,2));
            foreach ($snFriends as $snFriend)
            {
                $friendsData[] = array(
                    'snuid' => $snFriend['snuid'],
                    'name' => $snFriend['name'],
                    'used' => $snFriend['used'],
                );
            }
            if(count($friendsData) > 0)
            {
                $friendsModel->removeSnFriends('ae',$secondUser['_id']);
                $friendsModel->addSnFriends('ae',$user['_id'],$friendsData);
            }
            $this->edit($user['_id'],array('ae' => $secondUser['ae']));
        }
        if(!isset($user['msv']) && isset($secondUser['msv']))
        {
            $this->edit($user['_id'],array('msv' => $secondUser['msv']));
        }
        if(!isset($user['mru']) && isset($secondUser['mru']))
        {
            $friendsData = array();
            $snFriends = $friendsModel->getSnFriendsInfo('mru',$secondUser['_id'],array(0,1,2));
            foreach ($snFriends as $snFriend)
            {
                $friendsData[] = array(
                    'snuid' => $snFriend['snuid'],
                    'name' => $snFriend['name'],
                    'used' => $snFriend['used'],
                );
            }
            if(count($friendsData) > 0)
            {
                $friendsModel->removeSnFriends('mru',$secondUser['_id']);
                $friendsModel->addSnFriends('mru',$user['_id'],$friendsData);
            }
            $this->edit($user['_id'],array('mru' => $secondUser['mru']));
        }
        if(!isset($user['zzma']) && isset($secondUser['zzma']))
        {
            $friendsData = array();
            $snFriends = $friendsModel->getSnFriendsInfo('zzma',$secondUser['_id'],array(0,1,2));
            if($snFriends)
            {
                foreach ($snFriends as $snFriend)
                {
                    $friendsData[] = array(
                        'snuid' => $snFriend['snuid'],
                        'name' => $snFriend['name'],
                        'used' => $snFriend['used'],
                    );
                }
                if(count($friendsData) > 0)
                {
                    $friendsModel->removeSnFriends('zzma',$secondUser['_id']);
                    $friendsModel->addSnFriends('zzma',$user['_id'],$friendsData);
                }
            }
            $this->edit($user['_id'],array('zzma' => $secondUser['zzma']));
        }
        if(!isset($user['dlt']) && isset($secondUser['dlt']))
        {
            $friendsData = array();
            $snFriends = $friendsModel->getSnFriendsInfo('dlt',$secondUser['_id'],array(0,1,2));
            foreach ($snFriends as $snFriend)
            {
                $friendsData[] = array(
                    'snuid' => $snFriend['snuid'],
                    'name' => $snFriend['name'],
                    'used' => $snFriend['used'],
                );
            }
            if(count($friendsData) > 0)
            {
                $friendsModel->removeSnFriends('dlt',$secondUser['_id']);
                $friendsModel->addSnFriends('dlt',$user['_id'],$friendsData);
            }
            $this->edit($user['_id'],array('dlt' => $secondUser['dlt']));
        }

        $this->remove($secondUser['_id']);
        return $res;
    }

    public function disconnectAccount($auid,$snid)
    {
        $friendsModel = new Friends();
        $friendsModel->removeSnFriends($snid,$auid);
        return $this->_db->users->update(
            array('_id' => (int)$auid),
            array('$unset' => array($snid => 1))
        );
    }
    
    public function deleteAccount($auid)
    {
        $friendsModel = new Friends();
        $friendsModel->removeSnFriendsAll($auid);
        $this->remove($auid);
    }

    public function setGender($auid, $snid, $gender)
    {
        return $this->_db->users->update(
            array('_id' => (int)$auid),
            array('$set' => array($snid.'.gender' => $gender))
        );
    }
    public function getByRuid($ruid,$fields = array())
    {
        $res = array();
        $users = $this->_db->users->find(array('ruid' => $ruid),$fields);

        foreach ($users as $user)
        {
            $res[] = array('auid'=>$user["_id"],
                //'nick'=> array_key_exists('nick', $user) ? $user["nick"] : "",
                '//fsn'=> array_key_exists('fsn', $user) ? $user["fsn"] : "",
                );

        }
        return $res;
    }


}
?>
