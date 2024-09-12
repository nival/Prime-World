<?php
ini_set('error_reporting', E_ALL);
ini_set('display_errors', 1);

require '../../application/tests/settings/config.php';

$paths = implode(PATH_SEPARATOR, array(
    $config['path']['library'],
    implode(PATH_SEPARATOR, $config['path']['models']),
    $config['path']['system']
));
set_include_path($paths);

require '../../application/Bootstrap.php';

$bootstrap = new Bootstrap();
$bootstrap->run($config);
?>
