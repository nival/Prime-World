<?php
ini_set('memory_limit','1024M');
$dbConfig = array(
    'host' => '192.168.1.16', // MongoDB connect host
    'port' => '27017',// MongoDB connection port
    'name' => 'sa',
    'options' => array(
        'connect' => true, //If true the constructor should connect before returning.
        //'username' => '*******', // MongoDB connection username
        //'password' => '*******', // MongoDB connection password
        //'persist' => 'foo', //If the connection should be persistent. If set, the connection will be persistent.
        //'timeout' => 300, // For how long the driver should try to connect to the database (in milliseconds).
        //'replicaSet' => true //If this hosts listed are seeds of a replica set.
    )
);
$connection = new Mongo($dbConfig['host'].':'.$dbConfig['port'],$dbConfig['options']);
$connection->selectDb($dbConfig['name'])->drop();
if($connection->selectDb($dbConfig['name'])->execute("function(){}"))
{
    echo "Create Database.Ok\n";
    $db = $connection->selectDB($dbConfig['name']);
    $collection = $db->seq;
    $result = $collection->insert(array('_id' => 'users','seq' => new MongoInt64(1)));
    if($result['ok'] == 1)
    {
        echo "Create seq. collection.Ok.\n";
    }
    $collection = $db->users;
    $result = $collection->ensureIndex(array('fb.snuid' => 1), array("unique" => false));
    if($result)
    {
        echo "Create users.fb.snuid index.Ok.\n";
    }
    $result = $collection->ensureIndex(array('vk.snuid' => 1), array("unique" => false));
    if($result)
    {
        echo "Create users.vk.snuid index.Ok.\n";
    }
    $result = $collection->ensureIndex(array('ok.snuid' => 1), array("unique" => false));
    if($result)
    {
        echo "Create users.ok.snuid index.Ok.\n";
    }
    $result = $collection->ensureIndex(array('pwc.snuid' => 1), array("unique" => false));
    if($result)
    {
        echo "Create users.pwc.snuid index.Ok.\n";
    }
    $result = $collection->ensureIndex(array('st.snuid' => 1), array("unique" => false));
    if($result)
    {
        echo "Create users.st.snuid index.Ok.\n";
    }
    $result = $collection->ensureIndex(array('ae.snuid' => 1), array("unique" => false));
    if($result)
    {
        echo "Create users.ae.snuid index.Ok.\n";
    }
    $result = $collection->ensureIndex(array('mru.snuid' => 1), array("unique" => false));
    if($result)
    {
        echo "Create users.mru.snuid index.Ok.\n";
    }
    $result = $collection->ensureIndex(array('msv.snuid' => 1), array("unique" => false));
    if($result)
    {
        echo "Create users.msv.snuid index.Ok.\n";
    }
    $result = $collection->ensureIndex(array('arc.snuid' => 1), array("unique" => false));
    if($result)
    {
        echo "Create users.arc.snuid index.Ok.\n";
    }
    $result = $collection->ensureIndex(array('arc.passportid' => 1), array("unique" => false));
    if($result)
    {
        echo "Create users.arc.snuid index.Ok.\n";
    }
    $result = $collection->ensureIndex(array('zzma.snuid' => 1), array("unique" => false));
    if($result)
    {
        echo "Create users.zzma.snuid index.Ok.\n";
    }
    $result = $collection->ensureIndex(array('gmg.snuid' => 1), array("unique" => false));
    if($result)
    {
        echo "Create users.gmg.snuid index.Ok.\n";
    }
    $result = $collection->ensureIndex(array('gmg.name' => 1), array("unique" => false));
    if($result)
    {
        echo "Create users.gmg.name index.Ok.\n";
    }

    $result = $collection->ensureIndex(array('dlt.snuid' => 1), array("unique" => false));
    if($result)
    {
        echo "Create users.dlt.snuid index.Ok.\n";
    }
    $result = $collection->ensureIndex(array('$ruid' => 1), array("unique" => false));
    if($result)
    {
        echo "Create users.ruid index.Ok.\n";
    }

    $collection = $db->friends;
    $result = $collection->ensureIndex(array('auid' => 1), array("unique" => false));
    if($result)
    {
        echo "Create friends.auid index.Ok.\n";
    }
    $result = $collection->ensureIndex(array('friend_auid' => 1), array("unique" => false));
    if($result)
    {
        echo "Create friends.friend_auid index.Ok.\n";
    }

    $collection = $db->sn_friends;
    $result = $collection->ensureIndex(array('auid' => 1), array("unique" => false));
    if($result)
    {
        echo "Create sn_friends.auid index.Ok.\n";
    }
    $result = $collection->ensureIndex(array('snuid' => 1), array("unique" => false));
    if($result)
    {
        echo "Create sn_friends.snuid index.Ok.\n";
    }
    $result = $collection->ensureIndex(array('snid' => 1), array("unique" => false));
    if($result)
    {
        echo "Create sn_friends.snid index.Ok.\n";
    }

    $collection = $db->user_properties;
    $result = $collection->ensureIndex(array('auid' => 1), array("unique" => false));
    if($result)
    {
        echo "Create user_properties.auid index.Ok.\n";
    }
    $result = $collection->ensureIndex(array('e_auid' => 1), array("unique" => false));
    if($result)
    {
        echo "Create user_properties.e_auid index.Ok.\n";
    }
}
?>
