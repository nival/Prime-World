<?php
/* Import all users from anover db to current.
 * Assing new auid's to them, apply pwc_snuid changes and rebuild friend lists.
 * Prepare auid replacement list for the subsequent stages.
 * http://devjira.nivalnetwork.com/browse/PF-80368
 */

require __DIR__ . '/config.php';
require __DIR__ . '/common.php';

class Importer extends Common
{
	private $resolve = null;  // duplicates resolutions list
	private $copyList = null; // accounts to copy
	private $auidMap = array(); // USauids -> RUauids
	private $pwcAuids = array(); // new auids for pwc accounts
	private $newUsers = array(); // map new user auids to that users data
	//private $toDelete = array(); // RU users to delete: auids used as keys
	private $ruAuidSubst = array(); // maps deleted RU auids to the main acc auid
	private $usAuidSubst = array(); // maps deleted US auids to the main acc auid
	private $billingConfig = null;
	//private $addedFriends = array(); // track already created friend links to avoid dubble inserts
	private $toAddBilling = array(); // кого добавлять в биллинг

	/* public function __construct($config_array)
	{
		parent::__construct($config_array);
		// ...	
	} */
 
	public function parse_options($shortOptions, $longOptions)
	{
		$longOptions[] = "dups:";  // Requires a file name of dups resolution
		$longOptions[] = "copy:";  // Requires a file name of US account list for copy
		parent::parse_options($shortOptions, $longOptions);
		if (!isset($this->params['dups']) || !isset($this->params['copy']))
		{
			print "ERROR! --dups and --copy required!\n";
			exit(2);
		}
	}

	function prepare()
	{
		parent::prepare();
		$this->load_dup_resolve();
		$this->load_copy_list();
		$this->billingConfig = $this->isTest ? $this->config->test_billing->toArray() : $this->config->billing->toArray();
		MongoCursor::$timeout = -1; // turn off mongo timeouts
	}

	/* Load pwc_suid translation map and duplicate list.
	 * They should be prepared on PWC merge stage. */
	function load_dup_resolve()
	{
		$fname = $this->params['dups'];
		if (!file_exists($fname))
		{
			printf("ERROR: file %f does not exist!\n", $fname);
			exit(2);
		}
		$dfile = file_get_contents($fname, "r");
		$this->resolve = json_decode($dfile, true);
		print count($this->resolve) . " dupe resolutions found.\n";
	}

	function load_copy_list()
	{
		$fname = $this->params['copy'];
		if (!file_exists($fname))
		{
			printf("ERROR: file %f does not exist!\n", $fname);
			exit(2);
		}
		$cfile = file_get_contents($fname, "r");
		$this->copyList = json_decode($cfile, true);
		print count($this->copyList) . " US accounts are listed to copy.\n";
	}

	/* Copy `users` collection records, assigning new auids.
	 * Prepare auid translation map. */
	function perform()
	{
		// 0. Remove all sn_friends with 'used' != 2 -- they will be restored on the next sn info updates
		// And they aren't used here at all.
		$this->ruFriends->removeSnFriendsExceptUnfriended();
		// 1. Only users and properties. Create auid map
		$usDoneCount = $this->copyUsers();
		$usDoneCount += $this->mergeUsers();
		print $usDoneCount . " US users added to RU-SA.\n";
		// 2. Friends
		$this->mergeSnAndFriends();
		$this->clearFriends();
	}

	function copyUsers()
	{
		$count = 0;
		foreach ($this->copyList as $item) # $item is a pair of auid and fsnLogin
		{
			$this->copyUser($item[0]);
			$count++;
		}
		return $count;
	}

	function copyUser($auid)
	{
		$user = $this->usUsers->getByAuid($auid);
		$newAuid = $this->ruUsers->getUserSequence();
		$user['_id'] = $newAuid;
		unset($user['billing_status']); // turn it off to properly nandle billing registration result
		unset($user['helpdeskuid']);
		$user['fromUS'] = 1; // special mark
		$this->ruUsers->add($user);
		// fill $this->newUsers, $this->auidMap, $this->pwcAuids
		$this->auidMap[$auid] = $newAuid;
		$this->newUsers[$newAuid] = $user;
		// 
		$this->billingRegisterFill($newAuid, $user);
		print "US user $auid imported with auid $newAuid\n";
		//
		if (isset($user['pwc']['snuid'])) // we'll need to fix it's auid value in pwc SQL table
		{
			$this->pwcAuids[$user['pwc']['snuid']] = $newAuid;
			print "New auid $newAuid assigned to pwc_snuid " . $user['pwc']['snuid'] . "\n";
		}
		return $user;
	}

	function mergeUsers()
	{
		$count = 0; // for copied US users only
		foreach ($this->resolve as &$res)
		{
			if ($res['main']['location'] == 'US')
			{
				$user = $this->copyUser($res['main']['auid']);
				$res['main']['_user'] = $user;
				$mainAuid = $user['_id'];
				$count++;
			}
			else
			{
				$mainAuid = $res['main']['auid'];
				$res['main']['_user'] = $this->ruUsers->getByAuid($mainAuid);
				if (!$res['main']['_user']) {
					print "ERROR: RU user $mainAuid not found!\n";
				}
				print "RU user $mainAuid keeped as main among duplicates\n";
			}

			foreach ($res['dups'] as $dup)
			{
				if ($dup['location'] == 'RU')
				{
					//$this->toDelete[$dup['auid']] = 1; // TODO а нужен ли этот массив?
					$this->ruAuidSubst[$dup['auid']] = $mainAuid;
					print "RU user " . $dup['auid'] . " has been deleted as duplicate for " . $mainAuid . "\n";
					// remember, that friends, sn_friends and user_properties aren't deleted
				}
				else
				{
					$this->usAuidSubst[$dup['auid']] = $mainAuid;
					print "US user " . $dup['auid'] . " has been left uncopied as duplicate for " . $mainAuid . "\n";
				}
			}
		}
		return $count;
	}

	function addRuFriendChecked($auid1, $auid2, $snid)
	{
		//$pair = min($auid1, $auid2) . ':' . max($auid1, $auid2);
		//if (!array_key_exists($pair, $this->addedFriends))
		if ($auid1 == $auid2)
		{
			; // print "DEBUG: Self-friendship prevented for $auid1\n";
		}
		elseif ($this->ruFriends->getStatus($auid1, $auid2))
		{
			; // print "DEBUG: duplicate friend link insert prevented for $auid1 and $auid2\n";
		}
		else
		{
			$this->ruFriends->add($auid1, $auid2, $snid);
			//$this->addedFriends[$pair] = null;
		}
	}

	function mainAccFriendsRemap($acc)
	{
		printf("Remap friends for %s:%s\n", $acc['location'], $acc['auid']);
		$auid = $acc['_user']['_id'];
		if ($acc['location'] == 'RU')
		{
			$friends = iterator_to_array($this->ruFriends->getListByAuid($auid)); // going to make some changes so has to fetch'em all first
			foreach ($friends as $fr)
			{
				print "DEBUG friend rec " . print_r($fr, true) . "\n";
				if (isset($this->ruAuidSubst[$fr['friend_auid']]))
				{
					// If a friend's acc was substituted by another (main) acc -- relilnk friendship to main friend's acc
					$new = $this->ruAuidSubst[$fr['friend_auid']];
					print "Remove friendship " . $auid . " <-> " . $fr['friend_auid'] . "\n";
					$this->ruFriends->remove($auid, $fr['friend_auid']);
					print "Add friendship " . $auid . " <[" . $fr['snid'] . "]> " . $new . "\n";
					$this->addRuFriendChecked($auid, $new, $fr['snid']);
				}
			}
		}
		else // 'US', i.e. it was copied already, and all his friends too
		{
			foreach ($this->usFriends->getListByAuid($acc['auid']) as $fr)
			{
				$new = $this->mapUsAuid($fr['friend_auid']);
				if ($new)
					$this->addRuFriendChecked($auid, $new, $fr['snid']);
			}
			// copy only deleted sn_friends (used == 2)
			foreach($this->usFriends->getSnFriendsInfo('', $acc['auid'], array(2)) as $snFriend)
			{
				if (!$this->ruFriends->checkSnFriend($snFriend['snid'], $auid, $snFriend['snuid']))
				{				
					$this->ruFriends->addSnFriends($snFriend['snid'], $auid, array($snFriend));
				}
			}
		}
		return $auid;
	}

	function mergeSnAndFriends()
	{
		// pocess simple copies
		print "Process friends for copied single accs\n";
		foreach($this->copyList as $item)
		{
			$this->mainAccFriendsRemap(array(
				'auid' => $item[0], 
				'location' => 'US', 
				'_user' => array('_id' => $this->auidMap[$item[0]]),
			));
		}
		// process dups
		print "Process friends for copied main accs of dups\n";
		foreach($this->resolve as $res)
		{
			$usedSn = UsersExt::getSnSet($res['main']['_user']);
			$auid = $this->mainAccFriendsRemap($res['main']);

			// collect friends from deleted accs
			foreach($res['dups'] as $dup)
			{
				$loc = $dup['location'];
				$user = ($loc == 'RU') ? $this->ruUsers->getByAuid($dup['auid']) : $this->usUsers->getByAuid($dup['auid']);

				// copy new SN records
				$newSn = array();
				foreach(Assistant::$SNLIST as $snid)
				{
					if (isset($user[$snid]['snuid']) && !isset($usedSn[$snid]))
					{
						$newSn[$snid] = $user[$snid];
						$usedSn[$snid] = 1;
						if ($snid == 'pwc')
						{
							$this->pwcAuids[$user['pwc']['snuid']] = $auid;
							print "New auid $auid assigned to joined pwc_snuid " . $user['pwc']['snuid'] . "\n";
						}
					}
				}
				if ($newSn)
				{
					print "Saving newSn for $auid:\n";
					var_dump($newSn);
					$this->ruUsers->edit($auid, $newSn);
				}

				// copy new friends
				$friendsModel = ($loc == 'RU') ? $this->ruFriends : $this->usFriends;
				foreach($friendsModel->getListByAuid($dup['auid']) as $friend)
				{
					$frAuid = ($loc == 'RU') ? $friend['friend_auid'] : $this->mapUsAuid($friend['friend_auid']);
					if ($frAuid && !$this->ruFriends->getStatus($auid, $frAuid))
					{
						$this->addRuFriendChecked($auid, $frAuid, ($friend['snid'] == 'pwg')? 'pw' : $friend['snid']);
					}
				}
				/* NOTE!
 				   Do not copy sn-unfriended by other accs since we not sure that he DON'T want them as sn-friends on this acc.
				*/
				// finally drop RU dup
				if ($loc == 'RU')
				{
					$this->ruUsers->remove($dup['auid']);
				}
			}
		}
	}

	function mapUsAuid($usAuid)
	{
		if (isset($this->auidMap[$usAuid])) // was copied
		{
			return $this->auidMap[$usAuid];
		}
		else if(isset($this->usAuidSubst[$usAuid])) // is dup
		{
			return $this->usAuidSubst[$usAuid];
		}
		print "ERROR: US auid $usAuid not found neither in main nor in duplicate accounts!\n";
		return null;
	}

	function clearFriends()
	{
		foreach (array_keys($this->ruAuidSubst) as $auid)
		{
			// if still exists any friends of old accounts... (possibly, not)
			$this->ruFriends->removeByAuid($auid);
			// and remove all their sn_friends
			$this->ruFriends->removeSnFriendsAll($auid);
		}
	}

	function bilRegGetSnid($userData)
	{
		$snid = isset($userData['fsn']) ? $userData['fsn'] : '';
		if (empty($snid) || !isset($userData[$snid])) // email not found AND no fsn specified
		{
			$snid = UsersExt::getAnySn($userData);
		}
		return $snid;
	}

	function billingRegisterFill($auid, $userData)
	/* Copypasted from IndexController.php and changed slightly -- it was too hard to generalize. */
    {
        $snid = $this->bilRegGetSnid($userData);
        $email = Assistant::generateEmail($auid, $snid, $userData, $this->billingConfig);
        $password = md5(str_shuffle(substr(rand() . time(), 0, 12)));
        $user = $this->billingConfig['userName_prefix'].$auid;
		$this->toAddBilling[] = "$user,$password,$email\n";
    }   

	function finalize()
	{
		// Save $this->auidMap
		print count($this->auidMap) . " US auids mapped to RU auids\n";
		$data = json_encode(array("auids" => array('US->RU' => $this->auidMap)));
		$fname = 'new_auids.json';
		print "JSON data length " . strlen($data) . ", writting into $fname\n";
		file_put_contents($fname, $data);

		// Save $this->pwcAuids
		print count($this->pwcAuids) . " new auids for PWC accounts\n";
		$data = json_encode($this->pwcAuids);
		$fname = 'pwc_auids_update.json';
		print "JSON data length " . strlen($data) . ", writting into $fname\n";
		file_put_contents($fname, $data);

		// Save data for billing
		print count($this->toAddBilling) . " new billing users prepared\n";
		$fh = fopen('new_billing_users.txt', 'w');
		foreach ($this->toAddBilling as $line)
			fwrite($fh, $line);
		fclose($fh);

	}
}

$i = new Importer($config);
$i->run();
