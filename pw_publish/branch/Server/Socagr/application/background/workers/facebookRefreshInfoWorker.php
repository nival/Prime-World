<?php
$root = dirname(__FILE__);
$root.= '/../';
require $root.'settings/config.php';
$worker = new GearmanWorker();
$worker->addServers($config['gearman']['servers']);
$worker->addFunction('facebookRefreshInfo', 'facebookRefreshInfo');
while (1)
{
    echo "Wait...\n";
    $ret= $worker->work();
}

function facebookRefreshInfo($job)
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
			$user = $usersModel->getByAuid($data['_id'],array('fb.snuid','fb.sntoken'));
			if($user)
			{
				$facebookUsers = new FacebookUsers();
				$sntoken = $user['fb']['sntoken'];
				if(isset($data['sntoken']) && $user['fb']['sntoken'] != $data['sntoken'])
				{
					$validToken = $facebookUsers->validateToken(NULL, $data['sntoken']);
	    			if(!isset($validToken['error']))
	    			{
	    				$sntoken = 	$data['sntoken'];
	    			}
	    			else 
	    			{
	    				$message = 'FacebookRefreshInfo : '.$validToken['message'].' snuid='.$user['fb']['snuid']; 
						$type = Sa_Log::ERR;	
	    			}	
				}
                # FIXME do we use $sntoken even if it's not valid?
				$userFullInfo = $facebookUsers->requestFullUserData($user['fb']['snuid'],$sntoken);
				if(!isset($userFullInfo['error']))
   				{
   					$friends = $userFullInfo['friends'];
     				$snid = $userFullInfo['snid'];
     				unset($userFullInfo['friends']);
     				unset($userFullInfo['snid']);
     				unset($userFullInfo['dt_last_login']);
     				unset($userFullInfo['dt_register']);
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
                                    # Add new Facebook friends as friends in game.
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
				     						$deletedRecords[] = $snid.'_'.$deletedAuid.'_'.$user['fb']['snuid'];		
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
	    			curl_setopt($ch, CURLOPT_SSL_CIPHER_LIST, 'TLSv1');
	    			curl_exec($ch);
	    			curl_close($ch);
   					if($config['log_level'] == 'info')
					{
						$message = 'FacebookRefreshInfo : Info refresh for user with auid = '.$data['_id'].' complete.';	
					}	 	 	
   				}
   				else 
   				{
   					if($config['log_level'] == 'info' || $config['log_level'] == 'error')
					{
                        # FIXME could $message be set already by failed token update?
						$message = 'FacebookRefreshInfo : facebook error: '.$userFullInfo['message'];
						$type = Sa_Log::ERR;		
					}	
   				}
			}
			else 
			{
				if($config['log_level'] == 'info' || $config['log_level'] == 'error')
				{
					$message = 'FacebookRefreshInfo : Facebook account for user with auid = '.$data['_id'].'not found.'; 
					$type = Sa_Log::ERR;		
				}	
			}
			if($message)
			{
				Assistant::workerLogMessage('FacebookRefreshInfo', $message, $type);
			}
		}
	}
    catch (Exception $e)
    {
        $message = "FacebookRefreshInfo : Error message:".$e->getMessage()."\nTrace:".$e->getTraceAsString();
        Assistant::workerLogMessage('FacebookRefreshInfo', $message, Sa_Log::CRIT);
    }
}

?>
