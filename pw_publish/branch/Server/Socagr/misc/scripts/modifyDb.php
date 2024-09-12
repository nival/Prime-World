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
if($connection->selectDb($dbConfig['name'])->execute("function(){}"))
{
    $db = $connection->selectDB($dbConfig['name']);
    $collection = $db->users;

    // FB
    $result = $collection->deleteIndex('fb.snuid');
    if($result)
    {
        echo "Delete users.fb.snuid index.Ok.\n";
    }
    $result = $collection->ensureIndex(array('fb.snuid' => 1), array("unique" => false));
    if($result)
    {
        echo "Create users.fb.snuid index.Ok.\n";
    }

    // VK
    $result = $collection->deleteIndex('vk.snuid');
    if($result)
    {
        echo "Delete users.vk.snuid index.Ok.\n";
    }
    $result = $collection->ensureIndex(array('vk.snuid' => 1), array("unique" => false));
    if($result)
    {
        echo "Create users.vk.snuid index.Ok.\n";
    }

    // OK
    $result = $collection->deleteIndex('ok.snuid');
    if($result)
    {
        echo "Delete users.ok.snuid index.Ok.\n";
    }
    $result = $collection->ensureIndex(array('ok.snuid' => 1), array("unique" => false));
    if($result)
    {
        echo "Create users.ok.snuid index.Ok.\n";
    }

    // PWC
    $result = $collection->deleteIndex('pwc.snuid');
    if($result)
    {
        echo "Delete users.pwc.snuid index.Ok.\n";
    }
    $result = $collection->ensureIndex(array('pwc.snuid' => 1), array("unique" => false));
    if($result)
    {
        echo "Create users.pwc.snuid index.Ok.\n";
    }

    // Steam
    $result = $collection->deleteIndex('st.snuid');
    if($result)
    {
        echo "Delete users.st.snuid index.Ok.\n";
    }
    $result = $collection->ensureIndex(array('st.snuid' => 1), array("unique" => false));
    if($result)
    {
        echo "Create users.st.snuid index.Ok.\n";
    }

    // AeriaGames
    $result = $collection->deleteIndex('ae.snuid');
    if($result)
    {
        echo "Delete users.ae.snuid index.Ok.\n";
    }
    $result = $collection->ensureIndex(array('ae.snuid' => 1), array("unique" => false));
    if($result)
    {
        echo "Create users.st.snuid index.Ok.\n";
    }
    // mailru
    $result = $collection->deleteIndex('mru.snuid');
    if($result)
    {
        echo "Delete users.mru.snuid index.Ok.\n";
    }
    $result = $collection->ensureIndex(array('mru.snuid' => 1), array("unique" => false));
    if($result)
    {
        echo "Create users.mru.snuid index.Ok.\n";
    }
    // Massive
    $result = $collection->deleteIndex('msv.snuid');
    if($result)
    {
        echo "Delete users.msv.snuid index.Ok.\n";
    }
    $result = $collection->ensureIndex(array('msv.snuid' => 1), array("unique" => false));
    if($result)
    {
        echo "Create users.msv.snuid index.Ok.\n";
    }

    // draugas
    $result = $collection->deleteIndex('dlt.snuid');
    if($result)
    {
        echo "Delete users.dlt.snuid index.Ok.\n";
    }
    $result = $collection->ensureIndex(array('dlt.snuid' => 1), array("unique" => false));
    if($result)
    {
        echo "Create users.dlt.snuid index.Ok.\n";
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
    $userProperties = $collection->find();
    foreach ($userProperties as $userProperty)
    {
        $propertyData = explode('_',$userProperty['_id']);
        if(isset($propertyData[1]))
        {
            $auid = $propertyData[0];
            $eAuid = $propertyData[1];
            $name = $propertyData[2];
        }
        $collection->update(array('_id' => $userProperty['_id']), array('value' => $userProperty['value'],'name' => $name, 'auid' => (int)$auid, 'e_auid' => (int)$eAuid),array('upsert' => true,'safe' => true));
    }
}
?>
