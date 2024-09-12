<?php
$router = new Zend_Controller_Router_Rewrite();
$router->removeDefaultRoutes();

$router->addRoute('error',
    new Zend_Controller_Router_Route('*', array('controller'=>'error', 'action'=>'error', 'module'=>'default')));

$router->addRoute('login',
    new Sa_Controller_Router_Route_Params('',
    array('controller' => 'index', 'action' => 'login', 'module'=>'default'), array('action' => 'login')));

$router->addRoute('register',
    new Sa_Controller_Router_Route_Params('',
    array('controller' => 'index', 'action' => 'register', 'module'=>'default'), array('action' => 'register')));

$router->addRoute('get_info',
    new Sa_Controller_Router_Route_Params('',
    array('controller' => 'index', 'action' => 'getinfo', 'module'=>'default'), array('action' => 'get_info')));

$router->addRoute('get_infos',
    new Sa_Controller_Router_Route_Params('',
    array('controller' => 'index', 'action' => 'getinfos', 'module'=>'default'), array('action' => 'get_infos')));

$router->addRoute('add_friend',
    new Sa_Controller_Router_Route_Params('',
    array('controller' => 'index', 'action' => 'addfriend', 'module'=>'default'), array('action' => 'add_friend')));

$router->addRoute('add_friends',
    new Sa_Controller_Router_Route_Params('',
    array('controller' => 'index', 'action' => 'addfriends', 'module'=>'default'), array('action' => 'add_friends')));

$router->addRoute('get_edge_status',
    new Sa_Controller_Router_Route_Params('',
    array('controller' => 'index', 'action' => 'get_edge_status', 'module'=>'default'), array('action' => 'get_edge_status')));

$router->addRoute('get_friends',
    new Sa_Controller_Router_Route_Params('',
    array('controller' => 'index', 'action' => 'get_friends', 'module'=>'default'), array('action' => 'get_friends')));

$router->addRoute('delete_friend',
    new Sa_Controller_Router_Route_Params('',
    array('controller' => 'index', 'action' => 'deletefriend', 'module'=>'default'), array('action' => 'delete_friend')));

$router->addRoute('get_friends_info_all',
    new Sa_Controller_Router_Route_Params('',
    array('controller' => 'index', 'action' => 'getfriendsinfoall', 'module'=>'default'), array('action' => 'get_friends_info_all')));

$router->addRoute('get_candidates_info_all',
    new Sa_Controller_Router_Route_Params('',
    array('controller' => 'index', 'action' => 'getcandidatesinfoall', 'module'=>'default'), array('action' => 'get_candidates_info_all')));

$router->addRoute('set_edge_property',
    new Sa_Controller_Router_Route_Params('',
    array('controller' => 'index', 'action' => 'setedgeproperty', 'module'=>'default'), array('action' => 'set_edge_property')));

$router->addRoute('get_edge_property',
    new Sa_Controller_Router_Route_Params('',
    array('controller' => 'index', 'action' => 'getedgeproperty', 'module'=>'default'), array('action' => 'get_edge_property')));

$router->addRoute('get_users_count',
    new Sa_Controller_Router_Route_Params('',
    array('controller' => 'index', 'action' => 'getuserscount', 'module'=>'default'), array('action' => 'get_users_count')));

$router->addRoute('find_user',
    new Sa_Controller_Router_Route_Params('',
    array('controller' => 'index', 'action' => 'finduser', 'module'=>'default'), array('action' => 'find_user')));

$router->addRoute('post',
    new Sa_Controller_Router_Route_Params('',
    array('controller' => 'index', 'action' => 'post', 'module'=>'default'), array('action' => 'post')));

$router->addRoute('post_to_friend',
    new Sa_Controller_Router_Route_Params('',
    array('controller' => 'index', 'action' => 'posttofriend', 'module'=>'default'), array('action' => 'post_to_friend')));

$router->addRoute('set_property',
    new Sa_Controller_Router_Route_Params('',
    array('controller' => 'index', 'action' => 'setproperty', 'module'=>'default'), array('action' => 'set_property')));

$router->addRoute('get_property',
    new Sa_Controller_Router_Route_Params('',
    array('controller' => 'index', 'action' => 'get_property', 'module'=>'default'), array('action' => 'get_property')));

$router->addRoute('get_all_properties',
    new Sa_Controller_Router_Route_Params('',
    array('controller' => 'index', 'action' => 'getallproperties', 'module'=>'default'), array('action' => 'get_all_properties')));

$router->addRoute('get_billing_status',
    new Sa_Controller_Router_Route_Params('',
    array('controller' => 'index', 'action' => 'getbillingstatus', 'module'=>'default'), array('action' => 'get_billing_status')));

$router->addRoute('retry_billing_registration',
    new Sa_Controller_Router_Route_Params('',
    array('controller' => 'index', 'action' => 'retrybillingregistration', 'module'=>'default'), array('action' => 'retry_billing_registration')));

$router->addRoute('join',
    new Sa_Controller_Router_Route_Params('',
    array('controller' => 'index', 'action' => 'join', 'module'=>'default'), array('action' => 'join')));

$router->addRoute('merge',
    new Sa_Controller_Router_Route_Params('',
    array('controller' => 'index', 'action' => 'merge', 'module'=>'default'), array('action' => 'merge')));

$router->addRoute('logout',
    new Sa_Controller_Router_Route_Params('',
    array('controller' => 'index', 'action' => 'logout', 'module'=>'default'), array('action' => 'logout')));

$router->addRoute('delete_sn',
    new Sa_Controller_Router_Route_Params('',
    array('controller' => 'index', 'action' => 'deletesocialnetwork', 'module'=>'default'), array('action' => 'delete_sn')));

$router->addRoute('delete_account',
    new Sa_Controller_Router_Route_Params('',
    array('controller' => 'index', 'action' => 'deleteaccount', 'module'=>'default'), array('action' => 'delete_account')));

$router->addRoute('set_gender',
    new Sa_Controller_Router_Route_Params('',
    array('controller' => 'index', 'action' => 'setgender', 'module' => 'default'), array('action' => 'set_gender')));

$router->addRoute('get_aeria_token',
    new Sa_Controller_Router_Route_Params('',
    array('controller' => 'index', 'action' => 'getaeriatoken', 'module' => 'default'), array('action' => 'get_aeria_token')));

$router->addRoute('refresh_aeria_token',
    new Sa_Controller_Router_Route_Params('',
    array('controller' => 'index', 'action' => 'refreshaeriatoken', 'module' => 'default'), array('action' => 'refresh_aeria_token')));

$router->addRoute('get_user_sn_list',
    new Sa_Controller_Router_Route_Params('',
    array('controller' => 'index', 'action' => 'getusersnlist', 'module' => 'default'), array('action' => 'get_user_sn_list')));

$router->addRoute('mark_login',
    new Sa_Controller_Router_Route_Params('',
    array('controller' => 'index', 'action' => 'marklogin', 'module' => 'default'), array('action' => 'mark_login')));

$router->addRoute('list_sn',
    new Sa_Controller_Router_Route_Params('',
    array('controller' => 'index', 'action' => 'listsn', 'module' => 'default'), array('action' => 'list_sn')));

$router->addRoute('get_users_by_ruid',
    new Sa_Controller_Router_Route_Params('',
        array('controller' => 'index', 'action' => 'getusersbyruid', 'module' => 'default'), array('action' => 'get_users_by_ruid')));

?>
