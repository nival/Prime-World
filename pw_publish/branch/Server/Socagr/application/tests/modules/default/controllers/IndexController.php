<?php
class IndexController extends Zend_Controller_Action
{
    public function indexAction()
    {
        $this->_perform('Fuctional tests started:', '_testUserCount', '_performTest');
    }

    public function pwgtestAction()
    {
		# The standalone test suit for guild friends case. 
        $this->_perform('PWG fuctional tests started:', '_testUserCount', '_performPwgTest');
    }

    private function _perform($title, $testUserCountFunc, $test_func)
    {
        $this->_initTest();
        echo '<h2>' . $title . "</h2>\n";
        self::_subtitle('Request facebook test users');
    	$response = $this->_getFacebookTestUsers($this->$testUserCountFunc());
        echo '<br>';
     	if(isset($response['test_users']))
     	{
            if (count($response['test_users']) == 0)
            {
                echo '<p><b>No test users configured!</b></p>';
            }
            else
            {
                $this->$test_func($response['test_users'], $this->config);
            }
        }
        else
     	{
     		echo $response['error'];
     		echo '<br>'; 
     	}
        $this->_doneTest();
    }

    private function _performTest($testUsers, $config)
    {
        $mode = $this->verbose == 1 ? 'verbose' : 'regular';
        $this->_registerUsers($testUsers);
		list($auids, $snauids) = $this->_login($testUsers);
		#####
        self::_subtitle('Find user method test(action=find_user)');
        $locations = array();
        foreach ($testUsers as $testUser)
        {
            $locations[$testUser->id] = $this->_actionURL('find_user').'&snid=fb&snuid='.$testUser->id;
        }
        $users = Assistant::multiCurl($locations);
        foreach ($users as $userId => $user)
        {
            $result = self::_jsonResult($user);
            if ($result)
            {
                echo 'Find user with snuid='.$userId.'. auid= '.$result->auid;
                if($this->verbose == 1)
                {
                    echo '<br>';
                    $serializer = new Sa_View_Serializer(false);
                    echo $serializer->Serialize($result);
                }
            }
            echo '<br>';
        }
        //join
        $this->_joinTest($auids,$mode);
        #####
        self::_subtitle('Post method test(action=post)');
        $locations = array();
        $loginUrlsWithSnuid = array();
        $loginUrlsWithAuid = array();
        foreach ($testUsers as $testUser)
        {
            $auid = $snauids[$testUser->id];
            if($auid)
            {
                $loginUrlsWithAuid[$auid] = $testUser->login_url;
                $loginUrlsWithSnuid[$testUser->id] = $testUser->login_url;
                $locations[$testUser->id] = $this->_actionURL('post').'&message=test'.rand().'&snid=fb&auid='.$auid;
            }
        }
        $users = Assistant::multiCurl($locations);
        foreach ($users as $userId => $user)
        {
            $result = self::_jsonResult($user);
            if ($result)
            {
                echo 'View post at snuid='.$userId.' <a href="http://www.facebook.com/profile.php?id='.$userId.'&sk=wall">profile<a>. Use <a href="'.$loginUrlsWithSnuid[$userId].'">'.$loginUrlsWithSnuid[$userId].'<a> for login.';
                if($this->verbose == 1)
                {
                    echo '<br>';
                    $serializer = new Sa_View_Serializer(false);
                    echo $serializer->Serialize($result);
                }
            }
            echo '<br>';
        }
        #####
        self::_subtitle('Users count method test(action=get_users_count)');
        $locations = array();
        for($i=0;$i < 10;$i++)
        {
            $locations[] = $this->_actionURL('get_users_count');
        }
        $users = Assistant::multiCurl($locations);
        foreach ($users as $user)
        {
            $result = self::_jsonResult($user);
            if ($result)
            {
                echo 'Users count:  '.$result->users_count;
                if($this->verbose == 1)
                {
                    echo '<br>';
                    $serializer = new Sa_View_Serializer(false);
                    echo $serializer->Serialize($result);
                }
                echo '<br>';
            }
        }
        #####
        //set property
        $this->_setPropertyTest($auids,'test',1,$mode);
        //set property
        $this->_getPropertyTest($auids,'test',$mode);
        //get all properties
        $this->_getAllPropertiesTest($auids,$mode);
        #####
        self::_subtitle('Get sa test users info(action=get_info)');
        $locations = array();
        foreach ($auids as $auid)
        {
            $locations[$auid] = $this->_actionURL('get_info').'&auid='.$auid;
        }
        $userInfos = Assistant::multiCurl($locations);
        foreach ($userInfos as $auid => $info)
        {
            $result = self::_jsonResult($info);
            if ($result)
            {
                echo 'Get info for user with auid = '.$auid;
                if($this->verbose == 1)
                {
                    echo '<br>';
                    $serializer = new Sa_View_Serializer(false);
                    echo $serializer->Serialize(Zend_Json::decode($info));
                }
            }
            echo '<br>';
        }
		#####
        self::_subtitle('Get sa test users info with secure data(action=get_info and include_secure_data=1)');
        $locations = array();
        foreach ($auids as $auid)
        {
            $locations[$auid] = $this->_actionURL('get_info').'&auid='.$auid.'&include_secure_data=1';
        }
        $userInfos = Assistant::multiCurl($locations);
        foreach ($userInfos as $auid => $info)
        {
            $result = self::_jsonResult($info);
            if ($result)
            {
                echo 'Get info for user with auid = '.$auid;
                if($this->verbose == 1)
                {
                    echo '<br>';
                    $serializer = new Sa_View_Serializer(false);
                    echo $serializer->Serialize(Zend_Json::decode($info));
                }
            }
            echo '<br>';
        }
		#####
        self::_subtitle('Get info for test users(action=get_infos)');
        $ch = curl_init();
        curl_setopt($ch, CURLOPT_URL, $this->_actionURL('get_infos').'&auids='.(implode(',',$auids)));
        curl_setopt($ch, CURLOPT_HEADER, 0);
        curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
        curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, FALSE);
        $info = curl_exec($ch);
        $result = self::_jsonResult($info);
        if ($result)
        {
            echo 'Get info for users with auids = '.implode(',',$auids);
            if($this->verbose == 1)
            {
                echo '<br>';
                $serializer = new Sa_View_Serializer(false);
                echo $serializer->Serialize(Zend_Json::decode($info));
            }
        }
		#####
        self::_subtitle('Get info for test users with secure data(action=get_infos and include_secure_data=1)');
        $ch = curl_init();
        curl_setopt($ch, CURLOPT_URL, $this->_actionURL('get_infos').'&include_secure_data=1&auids='.(implode(',',$auids)));
        curl_setopt($ch, CURLOPT_HEADER, 0);
        curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
        curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, FALSE);
        $info = curl_exec($ch);
        $result = self::_jsonResult($info);
        if ($result)
        {
            echo 'Get info for users with auids = '.implode(',',$auids);
            if($this->verbose == 1)
            {
                echo '<br>';
                $serializer = new Sa_View_Serializer(false);
                echo $serializer->Serialize(Zend_Json::decode($info));
            }
        }
		#####
        self::_subtitle('Add friend method test(action=add_friend)');
        $usedAuids = array();
        sort($auids);
        $friendAuids = $auids;
        foreach ($auids as $auid)
        {
            $usedAuids[] = $auid;
            $addFriendLocations = array();
            foreach ($friendAuids as $friendAuid)
            {
                if(!in_array($friendAuid,$usedAuids))
                {
                    $addFriendLocations[$friendAuid] = $this->_actionURL('add_friend').'&auid='.$auid.'&friend_auid='.$friendAuid;
                    $deleteFriendLocations[$auid][$friendAuid] = $this->_actionURL('delete_friend').'&auid='.$auid.'&friend_auid='.$friendAuid;
                    $getEdgeStatusLocations[$auid][$friendAuid] = $this->_actionURL('get_edge_status').'&auid1='.$auid.'&auid2='.$friendAuid;
                    $setEdgePropertyLocations[$auid][$friendAuid] = $this->_actionURL('set_edge_property').'&auid1='.$auid.'&auid2='.$friendAuid.'&property_name=test&property_value=1';
                    $getEdgePropertyLocations[$auid][$friendAuid] = $this->_actionURL('get_edge_property').'&auid1='.$auid.'&auid2='.$friendAuid.'&property_name=test';
                }
            }
            $answer = Assistant::multiCurl($addFriendLocations);
            foreach ($answer as $friendAuid => $response)
            {
        		$result = self::_jsonResult($response);
                if ($result)
                {
                    echo 'Create friendship: auid = '.$auid.' friend_auid = '.$friendAuid;
                    if($this->verbose == 1)
                    {
                        echo '<br>';
                        $serializer = new Sa_View_Serializer(false);
                        echo $serializer->Serialize($result);
                    }
                }
                echo '<br>';		
            }
        }
		#####
        self::_subtitle('Get Friends method test(action=get_friends)');
        foreach ($auids as $auid)
        {
            $locations[$auid] = $this->_actionURL('get_friends').'&auid='.$auid;
        }
        $answer = Assistant::multiCurl($locations);
        foreach ($answer as $auid => $response)
        {
        	$result = self::_jsonResult($response);
            if ($result)
            {
                echo 'Get friends: auid = '.$auid;
                if($this->verbose == 1)
                {
                    echo '<br>';
                    $serializer = new Sa_View_Serializer(false);
                    echo $serializer->Serialize($result);
                }
            }
            echo '<br>';		
        }
		#####
        self::_subtitle('Get Edge Status method test(action=get_edge_status)');
        $usersCount = count($auids);
        foreach ($auids as $auid)
        {
            if($auid != $auids[$usersCount-1])
            {
                $answer = Assistant::multiCurl($getEdgeStatusLocations[$auid]);
                foreach ($answer as $friendAuid => $response)
                {
        			$result = self::_jsonResult($response);
                    if($result)
                    {
                        echo 'Edge status = '.$result->Get_edge_status.' for auid = '.$auid.' friend_auid = '.$friendAuid;
                        if($this->verbose == 1)
                        {
                            echo '<br>';
                            $serializer = new Sa_View_Serializer(false);
                            echo $serializer->Serialize($result);
                        }
                    }
                    echo '<br>';		
                }
            }
        }
		#####
        self::_subtitle('Get friends info method test(action=get_friends_info_all)');
        foreach ($auids as $auid)
        {
            $locations[$auid] = $this->_actionURL('get_friends_info_all').'&auid='.$auid;
        }
        $answer = Assistant::multiCurl($locations);
        foreach ($answer as $auid => $response)
        {
   			$result = self::_jsonResult($response);
            if($result)
            {
                echo 'Get friends info for user with auid = '.$auid;
                if($this->verbose == 1)
                {
                    echo '<br>';
                    $serializer = new Sa_View_Serializer(false);
                    echo $serializer->Serialize(Zend_Json::decode($response));
                }
            }
            echo '<br>';		
        }
		#####
        self::_subtitle('Delete friend method test(action=delete_friend)');
        $usersCount = count($auids);
        foreach ($auids as $auid)
        {
            if($auid != $auids[$usersCount-1])
            {
                $answer = Assistant::multiCurl($deleteFriendLocations[$auid]);
                foreach ($answer as $friendAuid => $response)
                {
   					$result = self::_jsonResult($response);
                    if($result)
                    {
                        echo 'Destroy friendship: auid = '.$auid.' friend_auid = '.$friendAuid;
                        if($this->verbose == 1)
                        {
                            echo '<br>';
                            $serializer = new Sa_View_Serializer(false);
                            echo $serializer->Serialize($result);
                        }
                    }
                    echo '<br>';		
                }
            }
        }
		#####
        self::_subtitle('Get_candidates_info_all method test(action=get_candidates_info_all)');
        foreach ($auids as $auid)
        {
            $locations[$auid] = $this->_actionURL('get_candidates_info_all').'&auid='.$auid;
        }
        $answer = Assistant::multiCurl($locations);
        $friendsForPosting = array();
        foreach ($answer as $auid => $response)
        {
			$result = self::_jsonResult($response);
            if($result)
            {
                if(isset($result->get_candidates_info_all->fb))
                {
                    foreach ($result->get_candidates_info_all->fb as $friendId=>$friend)
                    {
                        $friendsForPosting[$auid][] = $friendId;
                    }	
                }
                echo 'Get candidates info for user with auid = '.$auid;
                if($this->verbose == 1)
                {
                    echo '<br>';
                    $serializer = new Sa_View_Serializer(false);
                    echo $serializer->Serialize(Zend_Json::decode($response));
                }
            }
            echo '<br>';		
        }
        if(count($friendsForPosting) > 0)
        {
            self::_subtitle('Post to friends method test(action=post)');
            foreach ($friendsForPosting as $auid=>$friends)
            {
                if(isset($loginUrlsWithAuid[$auid]))
                {
                    $locations = array();
                    foreach ($friends as $friend)
                    {
                        $locations[$friend] = $this->_actionURL('post_to_friend').'&message=test'.rand().'&friend_snid=fb&from_auid='.$auid.'&friend_snuid='.$friend;	
                    }
                    $users = Assistant::multiCurl($locations);
                    foreach ($users as $userId => $user)
                    {
                        $result = json_decode($user);
                        if($result->error)
                        {
                            echo 'Error: code '.$result->error.' message "'.$result->message.'"';
                        }
                        else 
                        {
                            echo 'View post at snuid='.$userId.' <a href="http://www.facebook.com/profile.php?id='.$userId.'&sk=wall">profile<a>. Use <a href="'.$loginUrlsWithAuid[$auid].'">'.$loginUrlsWithAuid[$auid].'<a> for login.';
                            if($this->verbose == 1)
                            {
                                echo '<br>';
                                $serializer = new Sa_View_Serializer(false);
                                echo $serializer->Serialize($result);
                            }
                        }
                        echo '<br>';
                    }
                }
            }
                
        }

        self::_subtitle('Set_edge_property method test(action=set_edge_property)');
        $usersCount = count($auids);
        foreach ($auids as $auid)
        {
            if($auid != $auids[$usersCount-1])
            {
                $answer = Assistant::multiCurl($setEdgePropertyLocations[$auid]);
                foreach ($answer as $friendAuid => $response)
                {
                    $result = json_decode($response);
                    if($result->error)
                    {
                        echo 'Error: code '.$result->error.' message "'.$result->message.'"';
                    }
                    else 
                    {
                        echo 'Set edge property test for auid1 = '.$auid.' auid2 = '.$friendAuid;
                        if($this->verbose == 1)
                        {
                            echo '<br>';
                            $serializer = new Sa_View_Serializer(false);
                            echo $serializer->Serialize($result);
                        }
                    }
                    echo '<br>';		
                }
            }
        }

        self::_subtitle('Get_edge_property method test(action=get_edge_property)');
        $usersCount = count($auids);
        foreach ($auids as $auid)
        {
            if($auid != $auids[$usersCount-1])
            {
                $answer = Assistant::multiCurl($getEdgePropertyLocations[$auid]);
                foreach ($answer as $friendAuid => $response)
                {
                    $result = json_decode($response);
                    if($result->error)
                    {
                        echo 'Error: code '.$result->error.' message "'.$result->message.'"';
                    }
                    else 
                    {
                        echo 'Get edge property test for auid1 = '.$auid.' auid2 = '.$friendAuid;
                        if($this->verbose == 1)
                        {
                            echo '<br>';
                            $serializer = new Sa_View_Serializer(false);
                            echo $serializer->Serialize(Zend_Json::decode($response));
                        }
                    }
                    echo '<br>';		
                }
            }
        }
        //get billing status
        $this->_getBillingStatus($auids,$mode);
        //retry billing registration
        $this->_retryBillingRegistrationTest($auids,$mode);
		//add/delete guild friends
		$this->_guildFriendsTests($auids);
        //logout
        $this->_logout($auids,$mode);
        //merge
        $this->_mergeTest($auids,$mode);
		//
        $this->_clearInfo($auids,array('test'));
    }

	// ----------------- pwgtest -------------

	private function _performPwgTest($testUsers, $config)
    {
        $mode = $this->verbose == 1 ? 'verbose' : 'regular';
        $this->_registerUsers($testUsers);
		list($auids, $snauids) = $this->_login($testUsers);
		#
		$this->_guildFriendsTests($auids);
		#
        $this->_logout($auids,$mode);
        $this->_clearInfo($auids,array());
    }

	// ----------------- loadtest ---------------

    public function loadtestAction()
    {
        $this->_initTest();
     	$config = $this->config;
     	$response = $this->_getFacebookTestUsers($config->load_test->register);
		$locations = array();
     	if(isset($response['test_users']))
     	{
     		$testUsers = $response['test_users'];
     		self::_subtitle('Register action');
	    	foreach ($testUsers as $testUser)
	    	{
	    		$locations[$testUser->id] = $this->_actionURL('register').'&snid=fb&snuid='.$testUser->id.'&sntoken='.$testUser->access_token.'&test=1';
	    	}
	    	$users = Assistant::multiCurl($locations);
	    	$errors = 0;
     		$responseTime = 0;
     		$errorServerAnswer = 0;
	    	foreach ($users as $user)
	    	{
	    		$result = json_decode($user);
	    		if(isset($result->error))
		    	{
			    	if($result->error)
			    	{
			    		$errors++;
			    	}
			    	else 
			    	{
			    		$auids[] = $result->auid;
			    		$responseTime = $responseTime + (int)$result->tm;
			    	}
		    	}
		    	else 
		    	{
		    		$errorServerAnswer++;	
		    	}
	    	}
	    	$this->_formatResponse($locations,$responseTime,$errors,$errorServerAnswer);
	 	    	
	    	self::_subtitle('Login action');
	    	$locations = array();
	    	foreach ($testUsers as $testUser)
	    	{
	    		$locations[] = $this->_actionURL('login').'&snid=fb&snuid='.$testUser->id.'&sntoken='.$testUser->access_token.'&test=1';
	    	}
 			$locations = $this->_exact_locations_number($locations, $this->config->load_test->login);
	    	$users = Assistant::multiCurl($locations);
	    	$errors = 0;
     		$responseTime = 0;
     		$errorServerAnswer = 0;
	    	foreach ($users as $user)
	    	{
	    		$result = json_decode($user);
	    		if(isset($result->error))
		    	{
			    	if($result->error)
			    	{
			    		$errors++;
			    	}
			    	else 
			    	{
			    		$responseTime = $responseTime + (int)$result->tm;
			    	}
		    	}
		    	else 
		    	{
		    		$errorServerAnswer++;	
		    	}
	    	}
	    	$this->_formatResponse($locations,$responseTime,$errors,$errorServerAnswer);
	    	
	    	//join
		   	$this->_joinTest($auids,'load');
	    	
	    	self::_subtitle('Get info action');
	    	$locations = array();
	    	foreach ($auids as $auid)
	    	{
	    		$locations[] = $this->_actionURL('get_info').'&auid='.$auid;
	    	}
 			$locations = $this->_exact_locations_number($locations, $this->config->load_test->get_info);
	    	$users = Assistant::multiCurl($locations);
	    	$errors = 0;
     		$responseTime = 0;
     		$errorServerAnswer = 0;
	    	foreach ($users as $user)
	    	{
	    		$result = json_decode($user);
	    		if(isset($result->error))
		    	{
			    	if($result->error)
			    	{
			    		$errors++;
			    	}
			    	else 
			    	{
			    		$responseTime = $responseTime + (int)$result->tm;
			    	}
		    	}
		    	else 
		    	{
		    		$errorServerAnswer++;	
		    	}
	    	}
	    	$this->_formatResponse($locations,$responseTime,$errors,$errorServerAnswer);
	    	
	    	self::_subtitle('Get infos action');
	    	$locations = array();
	    	$auidsForStr = $auids;
	    	for($i=0;$i < $this->config->load_test->get_infos;$i++)
	    	{
	    		shuffle($auidsForStr);
	    		$locations[] = $this->_actionURL('get_infos').'&auids='.(implode(',',array_slice($auidsForStr,0,10)));
	    	}
	    	$users = Assistant::multiCurl($locations);
	    	$errors = 0;
     		$responseTime = 0;
     		$errorServerAnswer = 0;
	    	foreach ($users as $user)
	    	{
	    		$result = json_decode($user);
	    		if(isset($result->error))
		    	{
			    	if($result->error)
			    	{
			    		$errors++;
			    	}
			    	else 
			    	{
			    		$responseTime = $responseTime + (int)$result->tm;
			    	}
		    	}
		    	else 
		    	{
		    		$errorServerAnswer++;	
		    	}
	    	}
	    	$this->_formatResponse($locations,$responseTime,$errors,$errorServerAnswer);
	    	
	    	self::_subtitle('Add friend action');
    		$usedAuids = array();
    		sort($auids);
    		$friendAuids = $auids;
    		$addFriendLocations = array();
    		$deleteFriendLocations = array();
    		$getEdgeStatusLocations = array();
    		$setEdgePropertyLocations = array();
	    	foreach ($auids as $auid)
	   		{
	   			$usedAuids[] = $auid;
	   			foreach ($friendAuids as $friendAuid)
	   			{
	   				if(!in_array($friendAuid,$usedAuids))
	   				{
	   					$addFriendLocations[] = $this->_actionURL('add_friend').'&auid='.$auid.'&friend_auid='.$friendAuid;
	   					$deleteFriendLocations[] = $this->_actionURL('delete_friend').'&auid='.$auid.'&friend_auid='.$friendAuid;
	   					$getEdgeStatusLocations[] = $this->_actionURL('get_edge_status').'&auid1='.$auid.'&auid2='.$friendAuid;
	   					$setEdgePropertyLocations[] = $this->_actionURL('set_edge_property').'&auid1='.$auid.'&auid2='.$friendAuid.'&property_name=test&property_value=1';
	   				}
	   			}
	   		}
	   		$locationsNativeCount = count($addFriendLocations);
     		if ($locationsNativeCount > $config->load_test->add_friend)
	    	{
	    		$addFriendLocations = array_slice($addFriendLocations,0,$config->load_test->add_friend);	
	    	}
	   		$users = Assistant::multiCurl($addFriendLocations);
	    	$errors = 0;
     		$responseTime = 0;
     		$errorServerAnswer = 0;
	    	foreach ($users as $user)
	    	{
	    		$result = json_decode($user);
	    		if(isset($result->error))
		    	{
			    	if($result->error)
			    	{
			    		$errors++;
			    	}
			    	else 
			    	{
			    		$responseTime = $responseTime + (int)$result->tm;
			    	}
		    	}
		    	else 
		    	{
		    		$errorServerAnswer++;	
		    	}
	    	}
	    	$this->_formatResponse($addFriendLocations,$responseTime,$errors,$errorServerAnswer);
	    		    	
	    	self::_subtitle('Get edge status action');
 			$locations = $this->_exact_locations_number($locations, $config->load_test->get_edge_status);
	    	$users = Assistant::multiCurl($getEdgeStatusLocations);
	    	$errors = 0;
     		$responseTime = 0;
     		$errorServerAnswer = 0;
	    	foreach ($users as $user)
	    	{
	    		$result = json_decode($user);
	    		if(isset($result->error))
		    	{
			    	if($result->error)
			    	{
			    		$errors++;
			    	}
			    	else 
			    	{
			    		$responseTime = $responseTime + (int)$result->tm;
			    	}
		    	}
		    	else 
		    	{
		    		$errorServerAnswer++;	
		    	}
	    	}
	    	$this->_formatResponse($getEdgeStatusLocations,$responseTime,$errors,$errorServerAnswer);
	    	    	
	    	self::_subtitle('Get friends action');
    		$locations = array();
	    	foreach ($auids as $auid)
	    	{
	    		$locations[] = $this->_actionURL('get_friends').'&auid='.$auid;
	    	}
 			$locations = $this->_exact_locations_number($locations, $config->load_test->get_friends);
	    	$users = Assistant::multiCurl($locations);
	    	$errors = 0;
     		$responseTime = 0;
     		$errorServerAnswer = 0;
	    	foreach ($users as $user)
	    	{
	    		$result = json_decode($user);
	    		if(isset($result->error))
		    	{
			    	if($result->error)
			    	{
			    		$errors++;
			    	}
			    	else 
			    	{
			    		$responseTime = $responseTime + (int)$result->tm;
			    	}
		    	}
		    	else 
		    	{
		    		$errorServerAnswer++;	
		    	}
	    	}
	    	$this->_formatResponse($locations,$responseTime,$errors,$errorServerAnswer);
	    	
	    	self::_subtitle('Get friends info action');
    		$locations = array();
	    	foreach ($auids as $auid)
	    	{
	    		$locations[] = $this->_actionURL('get_friends_info_all').'&auid='.$auid;
	    	}
 			$locations = $this->_exact_locations_number($locations, $config->load_test->get_friends_info_all);
	    	$users = Assistant::multiCurl($locations);
	    	$errors = 0;
     		$responseTime = 0;
     		$errorServerAnswer = 0;
	    	foreach ($users as $user)
	    	{
	    		$result = json_decode($user);
	    		if(isset($result->error))
		    	{
			    	if($result->error)
			    	{
			    		$errors++;
			    	}
			    	else 
			    	{
			    		$responseTime = $responseTime + (int)$result->tm;
			    	}
		    	}
		    	else 
		    	{
		    		$errorServerAnswer++;	
		    	}
	    	}
	    	$this->_formatResponse($locations,$responseTime,$errors,$errorServerAnswer);
	    	
	    	self::_subtitle('Delete friend action');
    		$locationsNativeCount = count($deleteFriendLocations);
     		if ($locationsNativeCount > $config->load_test->delete_friend)
	    	{
	    		$deleteFriendLocations = array_slice($deleteFriendLocations,0,$config->load_test->delete_friend);	
	    	}
	   		$users = Assistant::multiCurl($deleteFriendLocations);
	    	$errors = 0;
     		$responseTime = 0;
     		$errorServerAnswer = 0;
	    	foreach ($users as $user)
	    	{
	    		$result = json_decode($user);
	    		if(isset($result->error))
		    	{
			    	if($result->error)
			    	{
			    		$errors++;
			    	}
			    	else 
			    	{
			    		$responseTime = $responseTime + (int)$result->tm;
			    	}
		    	}
		    	else 
		    	{
		    		$errorServerAnswer++;	
		    	}
	    	}
	    	$this->_formatResponse($deleteFriendLocations,$responseTime,$errors,$errorServerAnswer);
	    	
	    	self::_subtitle('Candidates info all action');
     		$locations = array();
	    	foreach ($auids as $auid)
	    	{
	    		$locations[] = $this->_actionURL('get_candidates_info_all').'&auid='.$auid;
	    	}
 			$locations = $this->_exact_locations_number($locations, $config->load_test->get_candidates_info_all);
	    	$users = Assistant::multiCurl($locations);
	    	$errors = 0;
     		$responseTime = 0;
     		$errorServerAnswer = 0;
	    	foreach ($users as $user)
	    	{
	    		$result = json_decode($user);
	    		if(isset($result->error))
		    	{
			    	if($result->error)
			    	{
			    		$errors++;
			    	}
			    	else 
			    	{
			    		$responseTime = $responseTime + (int)$result->tm;
			    	}
		    	}
		    	else 
		    	{
		    		$errorServerAnswer++;	
		    	}
	    	}
	    	$this->_formatResponse($locations,$responseTime,$errors,$errorServerAnswer);
	    	
	    	self::_subtitle('Set edge property action');
    		$locationsNativeCount = count($setEdgePropertyLocations);
    		$propertyNames = array('test');
     		if($locationsNativeCount < $config->load_test->set_edge_property)
	    	{
	    		$cyclesCount = ceil((($config->load_test->set_edge_property - $locationsNativeCount)/$locationsNativeCount));
	    		for($i=1;$i <= $cyclesCount;$i++)
	    		{
	    			$propertyNames[] = 'test'.$i;
		    		for($y = 0;$y < $locationsNativeCount;$y++)
		    		{
		    			$setEdgePropertyLocations[] =  str_replace('&property_name=test','&property_name=test'.$i,$setEdgePropertyLocations[$y]); 	
		    		}
	    				 
	    		}
	    	}
     		if(count($setEdgePropertyLocations) > $config->load_test->set_edge_property)
	    	{
	    		$setEdgePropertyLocations = array_slice($setEdgePropertyLocations,0,$config->load_test->set_edge_property);	
	    	}
	   		$users = Assistant::multiCurl($setEdgePropertyLocations);
	    	$errors = 0;
     		$responseTime = 0;
     		$errorServerAnswer = 0;
	    	foreach ($users as $user)
	    	{
	    		$result = json_decode($user);
	    		if(isset($result->error))
		    	{
			    	if($result->error)
			    	{
			    		$errors++;
			    	}
			    	else 
			    	{
			    		$responseTime = $responseTime + (int)$result->tm;
			    	}
		    	}
		    	else 
		    	{
		    		$errorServerAnswer++;	
		    	}
	    	}
	    	$this->_formatResponse($setEdgePropertyLocations,$responseTime,$errors,$errorServerAnswer);
	    	
	    	self::_subtitle('Get edge property action');
     		$locations = array();
	    	foreach ($setEdgePropertyLocations as $setEdgePropertyLocation)
	    	{
	    		$templocation = str_replace('?action=set_edge_property','?action=get_edge_property',$setEdgePropertyLocation);
	    		$locations[] = str_replace('&property_value=1','',$templocation);
	    	}
 			$locations = $this->_exact_locations_number($locations, $config->load_test->get_edge_property);
    		$users = Assistant::multiCurl($locations);
	    	$errors = 0;
     		$responseTime = 0;
     		$errorServerAnswer = 0;
	    	foreach ($users as $user)
	    	{
	    		$result = json_decode($user);
	    		if(isset($result->error))
		    	{
			    	if($result->error)
			    	{
			    		$errors++;
			    	}
			    	else 
			    	{
			    		$responseTime = $responseTime + (int)$result->tm;
			    	}
		    	}
		    	else 
		    	{
		    		$errorServerAnswer++;	
		    	}
	    	}
	    	$this->_formatResponse($locations,$responseTime,$errors,$errorServerAnswer);
	    	
	    	self::_subtitle('Find user action');
	    	$locations = array();
	    	foreach ($testUsers as $testUser)
	    	{
	    		$locations[] = $this->_actionURL('find_user').'&snid=fb&snuid='.$testUser->id;
	    	}
 			$locations = $this->_exact_locations_number($locations, $config->load_test->find_user);
	    	$users = Assistant::multiCurl($locations);
	    	$errors = 0;
     		$responseTime = 0;
     		$errorServerAnswer = 0;
	    	foreach ($users as $user)
	    	{
	    		$result = json_decode($user);
	    		if(isset($result->error))
		    	{
			    	if($result->error)
			    	{
			    		$errors++;
			    	}
			    	else 
			    	{
			    		$responseTime = $responseTime + (int)$result->tm;
			    	}
		    	}
		    	else 
		    	{
		    		$errorServerAnswer++;	
		    	}
	    	}
	    	$this->_formatResponse($locations,$responseTime,$errors,$errorServerAnswer);
	    	
	    	self::_subtitle('Users count action');
	    	$locations = array();
	    	for($i=0;$i < $config->load_test->get_users_count;$i++)
	    	{
	    		$locations[] = $this->_actionURL('get_users_count');
	    	}
	    	$users = Assistant::multiCurl($locations);
	    	$errors = 0;
     		$responseTime = 0;
     		$errorServerAnswer = 0;
	    	foreach ($users as $user)
	    	{
	    		$result = json_decode($user);
	    		if(isset($result->error))
		    	{
			    	if($result->error)
			    	{
			    		$errors++;
			    	}
			    	else 
			    	{
			    		$responseTime = $responseTime + (int)$result->tm;
			    	}
		    	}
		    	else 
		    	{
		    		$errorServerAnswer++;	
		    	}
	    	}
	    	$this->_formatResponse($locations,$responseTime,$errors,$errorServerAnswer);
	    	
	    	//set property
	    	$this->_setPropertyTest($auids,'test',1,'load');
	    	
	    	//get property
	    	$this->_getPropertyTest($auids,'test','load');
	    	
	    	//get all properties
	    	$this->_getAllPropertiesTest($auids,'load');
	    	
	    	//get billing status
	    	$this->_getBillingStatus($auids,'load');
	    	
	    	//retry billing registration
	    	$this->_retryBillingRegistrationTest($auids,'load');
	    	
	    	//logout
   			$this->_logout($auids,'load');
   			
	    	//merge
	    	$this->_mergeTest($auids,'load');
	    	
			$this->_clearInfo($auids,$propertyNames);
     	}
     	else 
     	{
     		echo $response['error'];
     		return false; 
     	}	 
        $this->_doneTest();
    }

    private function _getFacebookTestUsers($testUsersCount)
    {
    	$responce = array();
   		$ch = curl_init();
    	curl_setopt($ch, CURLOPT_URL, 'https://graph.facebook.com/'.$this->config->facebook->applicationId.'/accounts/test-users?access_token='.$this->config->facebook->accessToken);
    	curl_setopt($ch, CURLOPT_TIMEOUT, 60);
    	curl_setopt($ch, CURLOPT_HEADER, 0);
    	curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
    	curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, FALSE);
    	curl_setopt($ch, CURLOPT_SSL_VERIFYHOST, FALSE);
    	$result = curl_exec($ch); 
    	if($result === false)
		{
		    $responce['error'] = 'Connection error: ' . curl_error($ch);
		}
		else 
		{
			$result = json_decode(curl_exec($ch));
			if(isset($result->error))
	    	{
	    		$responce['error'] = 'Facebook error: '.$result->error->message;
	    	}
	    	else 
	    	{
	    		if(isset($result->data))
	    		{
		    		$testUsers = array();
		    		$testUsers = (array)$result->data;
	    			shuffle($testUsers);
	    			$testUsers = array_slice($testUsers,0,(int)$testUsersCount);
			    	foreach($testUsers as $testUser)
					{
						if(isset($testUser->id) && isset($testUser->access_token) && isset($testUser->login_url))
						{
							$responce['test_users'][] = $testUser;		
						}    			    
					}
	    		}
	    		else 
	    		{
	    			$responce['error'] = 'Facebook error: Unknown error.';	
	    		}
	    	}
		}
		return $responce;	
    }
    
    private function _registerUsers($users)
    {
        self::_subtitle('Register sa test users(action=register)');
        $locations = array();
        foreach ($users as $testUser)
        {
            $locations[$testUser->id] = $this->_actionURL('register').'&snid=fb&snuid='.$testUser->id.'&sntoken='.$testUser->access_token.'&test=1';
        }
        $users = Assistant::multiCurl($locations);
        foreach ($users as $userId => $user)
        {
            $result = self::_jsonResult($user);
            if ($result)
            {
                echo 'Register user with snuid = '.$userId.'. auid = '.$result->auid;
                if($this->verbose == 1)
                {
                    echo '<br>';
                    $serializer = new Sa_View_Serializer(false);
                    echo $serializer->Serialize($result);
                }
            }
            echo '<br>';
        }
    }

	private function _login($users)
	{
        $auids = array();
		$snauids = array();
        self::_subtitle('Login sa test users(action=login)');
        $locations = array();
        foreach ($users as $testUser)
        {
            $locations[$testUser->id] = $this->_actionURL('login').'&snid=fb&snuid='.$testUser->id.'&sntoken='.$testUser->access_token.'&test=1';
        }
        $users = Assistant::multiCurl($locations);
        foreach ($users as $userId => $user)
        {
            $result = self::_jsonResult($user);
            if ($result)
            {
                echo 'Login user with snuid='.$userId.'. auid= '.$result->auid;
                $auids[] = $result->auid;
                $snauids[$userId] = $result->auid;
                if($this->verbose == 1)
                {
                    echo '<br>';
                    $serializer = new Sa_View_Serializer(false);
                    echo $serializer->Serialize($result);
                }
            }
            echo '<br>';
        }
		return array($auids, $snauids);
	}

    private function _formatResponse($locations,$responseTime,$errors,$errorServerAnswer)
    {
    	echo 'Requests: '.count($locations).';';
    	echo '<br>';
    	echo 'Average response time: '.round($responseTime/count($locations),2).';';
    	echo '<br>';
    	echo 'Errors: '.$errors.';';
    	echo '<br>';
    	if($errorServerAnswer > 0)
    	{
    		echo '<span style="color: #FF0000;">500 server errors: '.$errorServerAnswer.';</span>';	
    	}
    	else 
    	{
    		echo '<span style="color: #008000;">500 server errors: '.$errorServerAnswer.';</span>';
    	}
    	echo '<br>';	
    }
    
    private function _clearInfo($auids,$propertyNames)
    {
        self::_subtitle('Remove sa test users');
    	$usersModel = new Users();
   		$propertiesModel = new Properties();
   		$friendsModel = new Friends();
   		foreach ($auids as $auid)
   		{
            if (count($propertyNames) > 0)
            {
                foreach ($auids as $auid2)
                {
                    if($auid != $auid2)
                    {
                        foreach ($propertyNames as $propertyName)
                        {
                            $propertiesModel->removeUsersProperty($auid,$auid2,$propertyName);
                        }
                    }	
                }
            }
   			$friendsModel->removeSnFriends('fb',$auid);
   			$friendsModel->removeSnFriends('vk',$auid);
   			foreach ($friendsModel->getAuidListByAuid($auid) as $friend)
   			{
   				$friendsModel->remove($auid,$friend);
   			}
			$usersModel->remove($auid);
   		}	
    }
    
    private function _guildFriendsTests($auids)
    {
		# A test for guild friends functionality.
		# Guild friends are implemented via pseudo social network 'pwg' and some
		# special treatment for this SN in SS.
		# XXX The test suit is incomplete yet.
		#
		# Split all test users list for groups.
		$guilds = self::_prepareGuilds($auids);
		# TODO: Add some personal friendship.
		# Mark members of each group as 'guild friend' to each other (inside a group).
		$this->_addGuildFriendTest($guilds);
		# TODO: test friendship status.
		# TODO: Add some more personal friendship.
		# TODO: test friendship status.
		# TODO: Remove some friendship.
		# TODO: test friendship status.
		# Remove giuld friendship.
		$this->_delGuildFriends($auids);
		# TODO: test friendship status.
    }

	private static function _prepareGuilds($auids)
	{
		$guilds = array();
		$med = intval(count($auids)/2);
		$guilds[] = array_slice($auids, 0, $med);
		$guilds[] = array_slice($auids, $med);
		return $guilds;
	}

	private function _addGuildFriendTest($guilds)
	{
        self::_subtitle('Add guild friends');
		for ($g = 0; $g < count($guilds); $g++)
		{
			$guild = $guilds[$g];
			echo 'Guild ' . ($g+1) . ":<br>\n";
			for ($i = 1; $i < count($guild); $i++)
			{
				$locations = array();
				for ($j = 0; $j < $i; $j++)
				{
					$locations[$guild[$j]] = $this->_actionURL('add_friend').'&snid=pwg&auid='.$guild[$i].'&friend_auid='.$guild[$j];
				}
        		$answer = Assistant::multiCurl($locations);
            	foreach ($answer as $friendAuid => $response)
				{
					$result = self::_jsonResult($response);
					if ($result)
					{
						echo 'Create guild friendship: auid = '.$guild[$i].' friend_auid = '.$friendAuid;
						if($this->verbose == 1)
						{
							echo '<br>';
							$serializer = new Sa_View_Serializer(false);
							echo $serializer->Serialize($result);
						}
					}
					echo '<br>';		
				}
			}
		}
	}

#	private function _delGuildFriends($auids)
#	{
#        echo '<br>'itle('Delete guild friends');
#		foreach ($auids as $auid)
#		{
#    		$locations = array();
#			$locations[] = $this->_actionURL('delete_friend').'&snid=pwg&auid='.$auid;
#       		$answer = Assistant::multiCurl($locations);
#            foreach ($answer as $response)
#            {
#                $result = self::_jsonResult($response);
#                if($result)
#                {
#                    echo 'Destroy guild friendship for auid = '.$auid;
#                    if($this->verbose == 1)
#                    {
#                        echo '<br>';
#                        $serializer = new Sa_View_Serializer(false);
#                        echo $serializer->Serialize($result);
#                    }
#                }
#                echo '<br>';		
#            }
#		}
#	}

	private function _delGuildFriends($auids)
	{
        self::_subtitle('Delete guild friends');
		$locations = array();
		foreach ($auids as $auid)
		{
			$locations[$auid] = $this->_actionURL('delete_friend').'&snid=pwg&auid='.$auid;
		}
   		$answer = Assistant::multiCurl($locations);
		foreach ($answer as $auid => $response)
		{
			$result = self::_jsonResult($response);
			if($result)
			{
				echo 'Destroy guild friendship for auid = '.$auid;
				if($this->verbose == 1)
				{
					echo '<br>';
					$serializer = new Sa_View_Serializer(false);
					echo $serializer->Serialize($result);
				}
			}
			echo '<br>';		
		}
	}

	private function _setPropertyTest($auids,$propertyName,$propertyValue,$mode)
    {
		self::_subtitle('Set_property method test(action=set_property)');
  		$locations = array();
   		foreach ($auids as $auid)
   		{
			$locations[$auid] = $this->_actionURL('set_property').'&auid='.$auid.'&property_name='.$propertyName.'&property_value='.$propertyValue;
   		}
   		if($mode == 'load')
 		{
 			$locations = $this->_exact_locations_number($locations, $this->config->load_test->set_property);
 		}
 		$answer = Assistant::multiCurl($locations);
 		if($mode == 'load')
 		{
 			$errors = 0;
     		$responseTime = 0;
     		$errorServerAnswer = 0;
 		}
		foreach ($answer as $auid => $response)
		{
			$result = json_decode($response);
			if(isset($result->error))
	    	{
		    	if($result->error)
	    		{
	    			if($mode == 'load')
	 				{
	 					$errors++;	
	 				}
	 				else 
	 				{
	    				echo 'Error: code '.$result->error.' message "'.$result->message.'"';
	    				echo '<br>';
	 				}
	    		}
		    	else 
		    	{
		    		if($mode == 'load')
	 				{
	 					$responseTime = $responseTime + (int)$result->tm;
	 				}
	 				else 
	 				{
			    		echo 'Set property for user with auid = '.$auid;
			    		if($mode == 'verbose')
			    		{
			    			echo '<br>';
			    			$serializer = new Sa_View_Serializer(false);
			    			echo $serializer->Serialize(Zend_Json::decode($response));
			    		}
			    		echo '<br>';	
	 				}
		    	}
	    	}
	    	else 
	    	{
	    		if($mode == 'load')
	 			{
	    			$errorServerAnswer++;
	 			}
	 			else 
	 			{
	 				echo '<br><b>500 server error.</b><br>'."\n";
	 			}
	    	}
		}
    	if($mode == 'load')
		{
  			$this->_formatResponse($locations,$responseTime,$errors,$errorServerAnswer);
		}	
    }
    
	private function _getPropertyTest($auids,$propertyName,$mode)
    {
		self::_subtitle('Get_property method test(action=get_property)');
  		$locations = array();
   		foreach ($auids as $auid)
   		{
			$locations[$auid] = $this->_actionURL('get_property').'&auid='.$auid.'&property_name='.$propertyName;
   		}
   		if($mode == 'load')
 		{
 			$locations = $this->_exact_locations_number($locations, $this->config->load_test->get_property);
 		}
 		$answer = Assistant::multiCurl($locations);
 		if($mode == 'load')
 		{
 			$errors = 0;
     		$responseTime = 0;
     		$errorServerAnswer = 0;
 		}
		foreach ($answer as $auid => $response)
		{
			$result = json_decode($response);
			if(isset($result->error))
	    	{
		    	if($result->error)
	    		{
	    			if($mode == 'load')
	 				{
	 					$errors++;	
	 				}
	 				else 
	 				{
	    				echo 'Error: code '.$result->error.' message "'.$result->message.'"';
	    				echo '<br>';
	 				}
	    		}
		    	else 
		    	{
		    		if($mode == 'load')
	 				{
	 					$responseTime = $responseTime + (int)$result->tm;
	 				}
	 				else 
	 				{
			    		echo 'Get property '.$propertyName.' for user with auid = '.$auid;
			    		if($mode == 'verbose')
			    		{
			    			echo '<br>';
			    			$serializer = new Sa_View_Serializer(false);
			    			echo $serializer->Serialize(Zend_Json::decode($response));
			    		}
			    		echo '<br>';	
	 				}
		    	}
	    	}
	    	else 
	    	{
	    		if($mode == 'load')
	 			{
	    			$errorServerAnswer++;
	 			}
	 			else 
	 			{
	 				echo '<br><b>500 server error.</b><br>'."\n";
	 			}
	    	}
		}
    	if($mode == 'load')
		{
  			$this->_formatResponse($locations,$responseTime,$errors,$errorServerAnswer);
		}	
    }
    
	private function _getBillingStatus($auids,$mode)
    {
		self::_subtitle('Get_billing_status method test(action=get_billing_status)');
  		$locations = array();
   		foreach ($auids as $auid)
   		{
			$locations[$auid] = $this->_actionURL('get_billing_status').'&auid='.$auid;
   		}
   		if($mode == 'load')
 		{
 			$locations = $this->_exact_locations_number($locations, $this->config->load_test->get_billing_status);
 		}
 		$answer = Assistant::multiCurl($locations);
 		if($mode == 'load')
 		{
 			$errors = 0;
     		$responseTime = 0;
     		$errorServerAnswer = 0;
 		}
		foreach ($answer as $auid => $response)
		{
			$result = json_decode($response);
			if(isset($result->error))
	    	{
		    	if($result->error)
	    		{
	    			if($mode == 'load')
	 				{
	 					$errors++;	
	 				}
	 				else 
	 				{
	    				echo 'Error: code '.$result->error.' message "'.$result->message.'"';
	    				echo '<br>';
	 				}
	    		}
		    	else 
		    	{
		    		if($mode == 'load')
	 				{
	 					$responseTime = $responseTime + (int)$result->tm;
	 				}
	 				else 
	 				{
			    		echo 'Get billing status for user with auid = '.$auid;
			    		if($mode == 'verbose')
			    		{
			    			echo '<br>';
			    			$serializer = new Sa_View_Serializer(false);
			    			echo $serializer->Serialize(Zend_Json::decode($response));
			    		}
			    		echo '<br>';	
	 				}
		    	}
	    	}
	    	else 
	    	{
	    		if($mode == 'load')
	 			{
	    			$errorServerAnswer++;
	 			}
	 			else 
	 			{
	 				echo '<br><b>500 server error.</b><br>'."\n";
	 			}
	    	}
		}
    	if($mode == 'load')
		{
  			$this->_formatResponse($locations,$responseTime,$errors,$errorServerAnswer);
		}	
    }
    
	private function _getAllPropertiesTest($auids,$mode)
    {
		self::_subtitle('Get_all_properties method test(action=get_all_properties)');
  		$locations = array();
   		foreach ($auids as $auid)
   		{
			$locations[$auid] = $this->_actionURL('get_all_properties').'&auid='.$auid;
   		}
   		if($mode == 'load')
 		{
 			$locations = $this->_exact_locations_number($locations, $this->config->load_test->get_all_properties);
 		}
 		$answer = Assistant::multiCurl($locations);
 		if($mode == 'load')
 		{
 			$errors = 0;
     		$responseTime = 0;
     		$errorServerAnswer = 0;
 		}
		foreach ($answer as $auid => $response)
		{
			$result = json_decode($response);
			if(isset($result->error))
	    	{
		    	if($result->error)
	    		{
	    			if($mode == 'load')
	 				{
	 					$errors++;	
	 				}
	 				else 
	 				{
	    				echo 'Error: code '.$result->error.' message "'.$result->message.'"';
	    				echo '<br>';
	 				}
	    		}
		    	else 
		    	{
		    		if($mode == 'load')
	 				{
	 					$responseTime = $responseTime + (int)$result->tm;
	 				}
	 				else 
	 				{
			    		echo 'Get all properties for user with auid = '.$auid;
			    		if($mode == 'verbose')
			    		{
			    			echo '<br>';
			    			$serializer = new Sa_View_Serializer(false);
			    			echo $serializer->Serialize(Zend_Json::decode($response));
			    		}
			    		echo '<br>';	
	 				}
		    	}
	    	}
	    	else 
	    	{
	    		if($mode == 'load')
	 			{
	    			$errorServerAnswer++;
	 			}
	 			else 
	 			{
	 				echo '<br><b>500 server error.</b><br>'."\n";
	 			}
	    	}
		}
    	if($mode == 'load')
		{
  			$this->_formatResponse($locations,$responseTime,$errors,$errorServerAnswer);
		}	
    }
    
	private function _retryBillingRegistrationTest($auids,$mode)
    {
		self::_subtitle('Retry_billing_registration method test(action=retry_billing_registration)');
  		$locations = array();
   		foreach ($auids as $auid)
   		{
			$locations[$auid] = $this->_actionURL('retry_billing_registration').'&auid='.$auid.'&test=1';
   		}
   		if($mode == 'load')
 		{
 			$locations = $this->_exact_locations_number($locations, $this->config->load_test->retry_billing_registration);
 		}
 		$answer = Assistant::multiCurl($locations);
 		if($mode == 'load')
 		{
 			$errors = 0;
     		$responseTime = 0;
     		$errorServerAnswer = 0;
 		}
		foreach ($answer as $auid => $response)
		{
			$result = json_decode($response);
			if(isset($result->error))
	    	{
		    	if($result->error)
	    		{
	    			if($mode == 'load')
	 				{
	 					$errors++;	
	 				}
	 				else 
	 				{
	    				echo 'Error: code '.$result->error.' message "'.$result->message.'"';
	    				echo '<br>';
	 				}
	    		}
		    	else 
		    	{
		    		if($mode == 'load')
	 				{
	 					$responseTime = $responseTime + (int)$result->tm;
	 				}
	 				else 
	 				{
			    		echo 'Retry billing registration for user with auid = '.$auid;
			    		if($mode == 'verbose')
			    		{
			    			echo '<br>';
			    			$serializer = new Sa_View_Serializer(false);
			    			echo $serializer->Serialize(Zend_Json::decode($response));
			    		}
			    		echo '<br>';	
	 				}
		    	}
	    	}
	    	else 
	    	{
	    		if($mode == 'load')
	 			{
	    			$errorServerAnswer++;
	 			}
	 			else 
	 			{
	 				echo '<br><b>500 server error.</b><br>'."\n";
	 			}
	    	}
		}
    	if($mode == 'load')
		{
  			$this->_formatResponse($locations,$responseTime,$errors,$errorServerAnswer);
		}	
    }
    
	private function _joinTest($auids,$mode)
    {
		self::_subtitle('Join method test(action=join)');
	   	$odnoklassnikiUsers = new OdnoklassnikiUsers();
	   	$vkontakteTestUsers = $this->config->vkontakte_test_users->toArray();
	   	$odnoklassnikiTestUsersTemp = $this->config->odnoklassniki_test_users->toArray();
	   	$odnoklassnikiTestUsers = array();
	   	foreach ($odnoklassnikiTestUsersTemp as $userId => $snRefreshToken)
	   	{
	   		$accessToken = $odnoklassnikiUsers->refreshToken($snRefreshToken);
   			if(!is_array($accessToken))
   			{
   				$odnoklassnikiTestUsers[$userId] = array(
   					'sntoken' => $accessToken,
   					'snrefresh_token' => $snRefreshToken,
   				);		
   			}
	   	}
  		$locations = array();
  		$auidCounter = 0;
   		foreach ($vkontakteTestUsers as $snuid=>$sntoken)
   		{
			if(isset($auids[$auidCounter]))
			{
   				$auid = $auids[$auidCounter];
   				$auidCounter ++;
			}
			else 
			{
				$auid = $auids[0];
				$auidCounter = 1;	
			}
   			$locations[] = $this->_actionURL('join').'&auid='.$auid.'&snid=vk&snuid='.$snuid.'&sntoken='.$sntoken;
   		}
   		$auidCounter = 0;
    	foreach ($odnoklassnikiTestUsers as $snuid=>$testUserData)
   		{
			if(isset($auids[$auidCounter]))
			{
   				$auid = $auids[$auidCounter];
   				$auidCounter ++;
			}
			else 
			{
				$auid = $auids[0];
				$auidCounter = 1;	
			}
   			$locations[] = $$this->_actionURL('join').'&auid='.$auid.'&snid=ok&snuid='.$snuid.'&sntoken='.$testUserData['sntoken'].'&snrefresh_token='.$testUserData['snrefresh_token'];
   		}
   		if($mode == 'load')
 		{
 			$locations = $this->_exact_locations_number($locations, $this->config->load_test->join);
 		}
 		$answer = Assistant::multiCurl($locations);
 		if($mode == 'load')
 		{
 			$errors = 0;
     		$responseTime = 0;
     		$errorServerAnswer = 0;
 		}
		foreach ($answer as $response)
		{
			$result = json_decode($response);
			if(isset($result->error))
	    	{
		    	if($result->error)
	    		{
	    			if($mode == 'load')
	 				{
	 					$errors++;	
	 				}
	 				else 
	 				{
	    				echo 'Error: code '.$result->error.' message "'.$result->message.'"';
	    				echo '<br>';
	 				}
	    		}
		    	else 
		    	{
		    		if($mode == 'load')
	 				{
	 					$responseTime = $responseTime + (int)$result->tm;
	 				}
	 				else 
	 				{
			    		echo 'Add new network for user with auid = '.$result->auid;
			    		if($mode == 'verbose')
			    		{
			    			echo '<br>';
			    			$serializer = new Sa_View_Serializer(false);
			    			echo $serializer->Serialize(Zend_Json::decode($response));
			    		}
			    		echo '<br>';	
	 				}
		    	}
	    	}
	    	else 
	    	{
	    		if($mode == 'load')
	 			{
	    			$errorServerAnswer++;
	 			}
	 			else 
	 			{
	 				echo '<br><b>500 server error.</b><br>'."\n";
	 			}
	    	}
		}
    	if($mode == 'load')
		{
  			$this->_formatResponse($locations,$responseTime,$errors,$errorServerAnswer);
		}	
    }
    
	private function _mergeTest($auids,$mode)
    {
    	if(count($auids) > 1)
    	{
			self::_subtitle('Merge method test(action=merge)');
		   	$mainAuid = $auids[1];
		   	unset($auids[1]);
	  		$locations = array();
	   		foreach ($auids as $auid)
	   		{
				$locations[$auid] = $this->_actionURL('merge').'&auid1='.$mainAuid.'&auid2='.$auid;
	   		}
	   		if($mode == 'load')
	 		{
	 			$locations = $this->_exact_locations_number($locations, $this->config->load_test->merge);
	 		}
	 		$answer = Assistant::multiCurl($locations);
	 		if($mode == 'load')
	 		{
	 			$errors = 0;
	     		$responseTime = 0;
	     		$errorServerAnswer = 0;
	 		}
			foreach ($answer as $auid => $response)
			{
				$result = json_decode($response);
				if(isset($result->error))
		    	{
			    	if($result->error)
		    		{
		    			if($mode == 'load')
		 				{
		 					$errors++;	
		 				}
		 				else 
		 				{
		    				echo 'Error: code '.$result->error.' message "'.$result->message.'"';
		    				echo '<br>';
		 				}
		    		}
			    	else 
			    	{
			    		if($mode == 'load')
		 				{
		 					$responseTime = $responseTime + (int)$result->tm;
		 				}
		 				else 
		 				{
				    		echo 'Merge for user with auid1 = '.$mainAuid.' and auid2 = '.$auid;
				    		if($mode == 'verbose')
				    		{
				    			echo '<br>';
				    			$serializer = new Sa_View_Serializer(false);
				    			echo $serializer->Serialize(Zend_Json::decode($response));
				    		}
				    		echo '<br>';	
		 				}
			    	}
		    	}
		    	else 
		    	{
		    		if($mode == 'load')
		 			{
		    			$errorServerAnswer++;
		 			}
		 			else 
		 			{
	 					echo '<br><b>500 server error.</b><br>'."\n";
		 			}
		    	}
			}
	    	if($mode == 'load')
			{
	  			$this->_formatResponse($locations,$responseTime,$errors,$errorServerAnswer);
			}
    	}	
    }
   
	private function _logout($auids,$mode)
    {
		self::_subtitle('Logout method test(action=logout)');
  		$locations = array();
   		foreach ($auids as $auid)
   		{
			$locations[$auid] = $this->_actionURL('logout').'&auid='.$auid;
   		}
   		if($mode == 'load')
 		{
			$locations = $this->_exact_locations_number($locations, $this->config->load_test->logout);
 		}
 		$answer = Assistant::multiCurl($locations);
 		if($mode == 'load')
 		{
 			$errors = 0;
     		$responseTime = 0;
     		$errorServerAnswer = 0;
 		}
		foreach ($answer as $auid => $response)
		{
			$result = json_decode($response);
			if(isset($result->error))
	    	{
		    	if($result->error)
	    		{
	    			if($mode == 'load')
	 				{
	 					$errors++;	
	 				}
	 				else 
	 				{
	    				echo 'Error: code '.$result->error.' message "'.$result->message.'"';
	    				echo '<br>';
	 				}
	    		}
		    	else 
		    	{
		    		if($mode == 'load')
	 				{
	 					$responseTime = $responseTime + (int)$result->tm;
	 				}
	 				else 
	 				{
			    		echo 'Logout user with auid = '.$auid;
			    		if($mode == 'verbose')
			    		{
			    			echo '<br>';
			    			$serializer = new Sa_View_Serializer(false);
			    			echo $serializer->Serialize(Zend_Json::decode($response));
			    		}
			    		echo '<br>';	
	 				}
		    	}
	    	}
	    	else 
	    	{
	    		if($mode == 'load')
	 			{
	    			$errorServerAnswer++;
	 			}
	 			else 
	 			{
	 				echo '<br><b>500 server error.</b><br>'."\n";
	 			}
	    	}
		}
    	if($mode == 'load')
		{
  			$this->_formatResponse($locations,$responseTime,$errors,$errorServerAnswer);
		}	
    }

    private function _initTest()
    {
    	ini_set('max_execution_time', '1000800');   //  3 hours
		ini_set('max_input_time', '1000800');       //  3 hours
		ini_set('error_reporting', E_ALL);
		ini_set('display_errors', 1);
		list($msec,$sec)=explode(chr(32),microtime());
		$this->HeadTime=$sec+$msec;
    	$this->_helper->viewRenderer->setNoRender(true);
    	$this->verbose = $this->_request->getQuery('verbose');
    	$this->baseDir = 'http://' . $_SERVER['SERVER_NAME'] . ($_SERVER['SERVER_PORT'] != '80' ? (':' . $_SERVER['SERVER_PORT'] . '/'):'/');
     	$this->config = Zend_Registry::get('config');
		$this->version = $this->config->version;
     	$this->_response->setHeader('Content-type','text/html;charset='.$this->config->common->charset.';');
     	echo '<html><head>
	    		<link href="'.$this->baseDir.'css/default.css" type="text/css" rel="stylesheet">
	    	<head>
	    	<body>';
    }

    private function _doneTest()
    {
    	list($msec,$sec)=explode(chr(32),microtime());
   		echo 'Total time spent: '.round(($sec+$msec)-$this->HeadTime,4)." seconds.";
   		echo '</body></html>';
    }

	private function _actionURL($action)
	{
		return $this->baseDir.'?action='.$action.'&version='.$this->version;
	}
    
    private function _testUserCount()
    {
        return $this->config->facebook->test_users_count;
    }

	private function _exact_locations_number($locations, $number)
	{
		$locationsCount = count($locations);
		if ($locationsCount > $number)
		{
			return array_slice($locations,0,$number);	
		}
		for($i = $locationsCount;$i < $number;$i++)
		{
			$locations[] =  $locations[array_rand($locations, 1)]; 	
		}
		return $locations;
	}

	private static function _jsonResult($data)
	{
		$result = json_decode($data);
		$err = '';
		if (!$result)
		{
#		    $trace=debug_backtrace();
#    		$caller = $trace[1];
			echo "Error: empty json_decode() result for:<pre>" . $data . "</pre><br>\n";
#			    '...in function ' . $caller['function'] . ', line ' . $caller['line'] . ' of file ' . $caller['file'] . "\n";
		}
		elseif ($result->error)
		{
			echo 'Error: code ' . $result->error . ' message "' . $result->message . "\"\n";
		}
		else
		{
			return $result;
		}
		return null;
	}

	private static function _subtitle($str)
	{
		echo '<h3>' . $str . "</h3>\n";
	}

}
?>
