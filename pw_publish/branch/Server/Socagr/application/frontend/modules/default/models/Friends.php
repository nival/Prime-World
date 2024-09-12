<?php
class Friends
{
	protected $_db;

	public function __construct()
    {
        $this->_db = Mongosa::getInstance();
    }

	## -------- `friends` collection ---------
	# Fields:
	# _id      (in form $auid.'_'.$friendAuid)
	# auid
	# friend_auid
	# snid     soc.network id where friend comes from
	#          spec. values:
	#          'pw'  - individually friended in game
	#          'pwg' - friend by guild

	public function add($auid,$friendAuid,$snid)
	{
		$collection = $this->_db->friends;
		$friends = array(
			1 => array(
				'_id' => $auid.'_'.$friendAuid,
				'auid' => (int)$auid,
				'friend_auid' => (int)$friendAuid,
				'snid' => $snid,
			),
			2 => array(
				'_id' => $friendAuid.'_'.$auid,
				'auid' => (int)$friendAuid,
				'friend_auid' => (int)$auid,
				'snid' => $snid,
			)
		);
		$result = $collection->batchInsert($friends);
		if($result['ok'] == 1)
		{
			return true;
		}
		throw new Exception($result['err']);
	}

	public function getStatus($auid,$friendAuid)
	{
		return $this->_db->friends->findOne(array('auid' => (int)$auid,'friend_auid' => (int)$friendAuid),array()) ? true : false;
	}

	public function getStatusSn($auid, $friendAuid)
	{
        return $this->_db->friends->findOne(array('auid' => (int)$auid,'friend_auid' => (int)$friendAuid), array('snid'));
	}

	public function remove($auid,$friendAuid)
	{
		$result = $this->_db->friends->remove(
			array('_id' => array('$in' => array($auid.'_'.$friendAuid, $friendAuid.'_'.$auid))),
			array()
		);
		if($result)
			return true;
		throw new Exception($result['err']);
	}

    public function removeByAuid($auid)
    {
        $result = $this->_db->friends->remove(
            array('$or' => array(array('auid' => $auid), array('friend_auid' => $auid))),
            array()
        );
        if($result)
            return true;
        throw new Exception($result['err']);
    }

	# Remove all friend by specified $snid
	public function removeBySn($auid, $snid)
	{
		$collection = $this->_db->friends;
		$friends = $collection->find(
			array('snid' => $snid,
				'$or' => array(array('auid' => (int)$auid), array('friend_auid' => (int)$auid))),
			array('_id', 'auid', 'friend_auid'));
		if ($friends->count() == 0)
		{
			return array(); # Nothing to do.
		}
		$ids = array();
		$pairs = array();
		foreach ($friends as $friend)
		{
			$ids[] = $friend['_id'];
			$pairs[] = array($friend['auid'], $friend['friend_auid']);
		}
		$result = $this->_db->friends->remove(array('_id' => array('$in' => $ids)));
		if($result)
		{
			return $pairs;
		}
		throw new Exception($result['err']);
	}

	public function setSn($auid, $friendAuid, $snid)
	{
		$result = $this->_db->friends->update(
			array('_id' => array('$in' => array($auid.'_'.$friendAuid, $friendAuid.'_'.$auid))),
			array('$set' => array('snid' => $snid)),
			array('multiple' => true)
		);
		if($result['ok'] == 1)
		{
			return true;
		}
		throw new Exception($result['err']);
	}

	public function hasPwgFriends($auid)
	{
		return $this->_db->friends->findOne(array('auid' => (int)$auid, 'snid' => 'pwg')) ? true : false;
	}

	public function overridePwgSn($auid, $friendAuids, $snid)
	{
		# PF-74372:
		# perform 2 updates because a single update with OR'ed condition becomes too slow in production
		# (and .hint() doesn't help)
		$result = $this->_db->friends->update(
			array('$and' => array(
				array('snid' => 'pwg'),
				array('auid' => $auid),
				array('friend_auid' => array('$in' => $friendAuids)))),
			array('$set' => array('snid' => $snid)),
			array('multiple' => true));
		if(!$result['ok'])
		{
			throw new Exception($result['err']);
		}
		$result = $this->_db->friends->update(
			array('$and' => array(
				array('snid' => 'pwg'),
				array('friend_auid' => $auid),
				array('auid' => array('$in' => $friendAuids)))),
			array('$set' => array('snid' => $snid)),
			array('multiple' => true));
		if(!$result['ok'])
		{
			throw new Exception($result['err']);
		}
		return true;
	}

	public function getListByAuid($auid,$fields = array())
	{
		return $this->_db->friends->find(array('auid' => (int)$auid),$fields);
	}

	public function getAuidListByAuid($auid)
	{
		return array_map( 'Assistant::extractFriendAuid',
			iterator_to_array($this->getListByAuid($auid, array('friend_auid'))));
	}

	# Select all 'pwg' friends.
	public function getGuildListByAuid($auid)
	{
		return array_map( 'Assistant::extractFriendAuid',
			iterator_to_array($this->_db->friends->find(array('auid' => (int)$auid, 'snid' => 'pwg'), array('friend_auid'))));
	}

	# Select all friends except 'pwg' ones.
	public function getNoguildListByAuid($auid)
	{
		return array_map( 'Assistant::extractFriendAuid',
			iterator_to_array($this->_db->friends->find(
                array('auid' => (int)$auid, 'snid' => array('$ne' => 'pwg')),
                array('friend_auid'))));
	}

	## -------- `sn_friends` collection ---------
	# Used to remember if a friend from soc.network was unfriended in game
	# (Not sure yet if it is used for something else.)
	# Fields:
	#   _id    in form $snid.'_'.$auid.'_'.$friendSnuid
	#   auid
	#   snid
	#   used   flag, values:
	#          0 - sn-friend is not a pw-player
	#          1 - current friend,
	#          2 - manually unfriended, do not autofriend on soc.network data update

	public function getNativeSnFriends($snid,$snuid, $fields = array())
	{
		return $this->_db->sn_friends->find(array('snuid' => $snuid,'snid' => $snid),$fields);
	}

	public function addSnFriends($snid,$auid,$data)
	{
		$friends = array();
		foreach ($data as $friend)
		{
			$friendItem = &$friends[];
			$friendItem = $friend;
			$friendItem['_id'] = $snid.'_'.$auid.'_'.$friend['snuid'];
			$friendItem['auid'] = (int)$auid;
			$friendItem['snid'] = $snid;
		}
		$result = $this->_db->sn_friends->batchInsert($friends);
		if($result['ok'] == 1)
		{
			return true;
		}
		throw new Exception($result['err']);
	}

	public function removeSnFriends($snid,$auid)
	{
		$result = $this->_db->sn_friends->remove(array('auid' => (int)$auid, 'snid' => $snid));
		if($result)
		{
			return true;
		}
		throw new Exception($result['err']);
	}

	public function removeSnFriendsAll($auid)
	{
		$result = $this->_db->sn_friends->remove(array('auid' => (int)$auid));
		if($result)
		{
			return true;
		}
		throw new Exception($result['err']);
	}

	public function removeSnFriendsList($idList)
	{
		if (!$idList)
		{
			return true; # empty list remove - always success
		}
		$result = $this->_db->sn_friends->remove(array('_id' => array('$in' => $idList)));
		if($result)
		{
			return true;
		}
		throw new Exception($result['err']);
	}

	public function markUsed($recordIds,$used = 1)
	{
		return $this->_db->sn_friends->update(
			array('_id' => array('$in' => $recordIds)),
			array('$set' => array('used' => $used)),
			array('multiple' => true));
		# `used` field possible values:
		# 0 - snfriend is not known by SA (i.e. not playing pw)
		# 1 - fiend in pw too
		# 2 - removed from friends in pw
	}

	public function getSnFriends($snid,$auid)
	{
		$criteria = array('auid' => (int)$auid);
		if(!empty($snid))
		{
			$criteria['snid'] = $snid;
		}
		return $this->_db->sn_friends->find($criteria,array());
	}

	public function getSnFriendsInfo($snid,$auid,$used = array(0,2))
	{
		$criteria = array(
			'auid' => (int)$auid,
			'used' => array('$in' => $used)
		);
		if(!empty($snid))
		{
			$criteria['snid'] = $snid;
		}
		return $this->_db->sn_friends->find($criteria,array());
	}

    public function checkSnFriend($snid, $auid, $friendSnuid)
    {
        return $this->_db->sn_friends->findOne(array('_id' => $snid.'_'.$auid.'_'.$friendSnuid), array('used'));
    }

    public function removeSnFriendsExceptUnfriended()
    {
		$result = $this->_db->sn_friends->remove(array('used' => array('$in' => array(0,1))));
		if($result)
			return true;
		throw new Exception($result['err']);
    }

    public function markUnusedBySnuid($snid, $snuid)
    {
		return $this->_db->sn_friends->update(
			array('snid' => $snid, 'snuid' => $snuid, 'used' => 1),
			array('$set' => array('used' => 0)),
			array('multiple' => true));
    }

}
?>
