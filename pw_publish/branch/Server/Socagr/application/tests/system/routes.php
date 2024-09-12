<?php
$router = new Zend_Controller_Router_Rewrite();
$router->addRoute('load_test',
    new Zend_Controller_Router_Route('load_test',
        array('module' => 'default', 'controller' => 'index', 'action' => 'loadtest')));
$router->addRoute('pwg_test',
    new Zend_Controller_Router_Route('pwg_test',
        array('module' => 'default', 'controller' => 'index', 'action' => 'pwgtest')));
?>
