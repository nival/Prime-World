<?php

class UsersExt extends Users
{
    public function __construct($db)
	{
		// override Users initialization -- use already opened DB connection
        $this->_db = $db;
    }

    public function getAll()
    {
        return $this->_db->users->find();
	}

	public function getOnlyRegOrLogin($timestamp)
	{
		$nologin = iterator_to_array($this->_db->users->find(array(
			'dt_last_login' => array('$exists' => false), 
			'dt_register' => array('$lt' => $timestamp)
		)));
		$noreg = iterator_to_array($this->_db->users->find(array(
			'dt_last_login' => array('$lt' => $timestamp), 
			'dt_register' => array('$exists' => false)
		)));
		return array($nologin, $noreg);
	}
	
	public function getByRegAndLogin($timestamp, $any)
	{
		$res = iterator_to_array($this->_db->users->find(array(
			'dt_last_login' => array('$lt' => $timestamp), 
			'dt_register' => array('$lt' => $timestamp)
		)));
		if (!$any)
			return $res;

		list($nologin, $noreg) = $this->getOnlyRegOrLogin($timestamp);
		printf("DEBUG: both fields %d, nologin %d, noreg %d\n", count($res), count($nologin), count($noreg));
		return array_merge($res, $nologin, $noreg);
	}

	public function getAllBySn($snid)
	{
        return $this->_db->users->find(array($snid => array('$exists' => 1)), array($snid => 1));
	}

	static public function getAnySn($user)
	{
		foreach (Assistant::$SNLIST as $snid)
		{
			if (isset($user[$snid]['snuid']))
			{
				return $snid; // normally in should be only one sn if no fsn is set
			}
		}
		return '';
	}

	static public function getFsnLogin($user)
	{
		$sn = isset($user['fsn']) ? $user['fsn'] : UsersExt::getAnySn($user);
		return $sn . '#' . $user[$sn]['snuid'];
	}

	static public function getSnSet($user)
	{
		$list = array();
		foreach (Assistant::$SNLIST as $snid)
		{
			if (isset($user[$snid]['snuid'])) $list[$snid] = 1;
		}
		return $list;
	}

	static public function checkGhost($user)
	{
		// user, who never logged out nor has fraction counts as 'ghost', i.e. 'never seen in the game'.
		return !(isset($user['dt_last_logout']) || isset($user['fraction']));
	}

}

class FriendsExt extends Friends
{
    public function __construct($db)
	{
		// override Users initialization -- use already opened DB connection
        $this->_db = $db;
    }

}
