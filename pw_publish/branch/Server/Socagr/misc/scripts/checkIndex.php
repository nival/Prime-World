<?php
ini_set('memory_limit','1024M');
$app = __DIR__ . '/../../application/';
require  $app . '/frontend/settings/config.php';
$dbConfig = $config['db'];
echo "Connecting to mongo " . $dbConfig['host'].':'.$dbConfig['port'] . "\n";
$connection = new Mongo($dbConfig['host'].':'.$dbConfig['port'],$dbConfig['options']);
echo "Seelcting DB " . $dbConfig['name'] . "\n";
$db = $connection->selectDb($dbConfig['name']);
if($db->execute("function(){}"))
{
    echo "Ok\n";
    $collection = $db->users;
    ensure($collection, 'users', 'fb.snuid');
    ensure($collection, 'users', 'vk.snuid');
    ensure($collection, 'users', 'ok.snuid');
    ensure($collection, 'users', 'pwc.snuid');
    ensure($collection, 'users', 'st.snuid');
    ensure($collection, 'users', 'ae.snuid');
    ensure($collection, 'users', 'msv.snuid');
    ensure($collection, 'users', 'mru.snuid');
    ensure($collection, 'users', 'arc.snuid');
    ensure($collection, 'users', 'arc.passportid');
    ensure($collection, 'users', 'zzma.snuid');
    ensure($collection, 'users', 'gmg.snuid');
    ensure($collection, 'users', 'gmg.name');
    ensure($collection, 'users', 'gmg.passportid');
    ensure($collection, 'users', 'dlt.snuid');
    ensure($collection, 'users', 'ruid');

    $collection = $db->friends;
    ensure($collection, 'friends', 'auid');
    ensure($collection, 'friends', 'friend_auid');
    ensure($collection, 'friends', 'snid');

    $collection = $db->sn_friends;
    ensure($collection, 'sn_friends', 'auid');
    ensure($collection, 'sn_friends', 'snuid');
    ensure($collection, 'sn_friends', 'snid');

    $collection = $db->user_properties;
    ensure($collection, 'user_properties', 'auid');
    ensure($collection, 'user_properties', 'e_auid');
}
else
{
    echo "ERROR: Can't work with DB\n";
}

function ensure($collection, $name, $field)
{
    echo "Ensure index on $name.$field ... ";
    $result = $collection->ensureIndex(array($field => 1), array("unique" => false));
    echo ($result?"OK":"FAIL") . "\n";
}
?>