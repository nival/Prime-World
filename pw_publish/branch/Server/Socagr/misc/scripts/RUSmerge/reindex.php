<?php
/* Ensures index existance in both ru and us db
 */

require __DIR__ . '/config.php';
require __DIR__ . '/common.php';

class Indexer extends Common
{
	function prepare()
	{
		; // Empty!
	}

	function finalize()
	{
		; // Empty;
	}

	function perform()
	{
		echo "Processing RU...\n";
		$this->indexes($this->ru_db);
		echo "Processing US...\n";
		$this->indexes($this->us_db);
	}

	function indexes($db)
	{
    	$collection = $db->users;
		$result = $collection->ensureIndex(array('fb.snuid' => 1), array("unique" => false));
		echo "Create users.fb.snuid index: " . ($result?"OK":"FAIL") . "\n";
		$result = $collection->ensureIndex(array('vk.snuid' => 1), array("unique" => false));
		echo "Create users.vk.snuid index: " . ($result?"OK":"FAIL") . "\n";
		$result = $collection->ensureIndex(array('ok.snuid' => 1), array("unique" => false));
		echo "Create users.ok.snuid index: " . ($result?"OK":"FAIL") . "\n";
		$result = $collection->ensureIndex(array('pwc.snuid' => 1), array("unique" => false));
		echo "Create users.pwc.snuid index: " . ($result?"OK":"FAIL") . "\n";
		$result = $collection->ensureIndex(array('st.snuid' => 1), array("unique" => false));
		echo "Create users.st.snuid index: " . ($result?"OK":"FAIL") . "\n";
		$result = $collection->ensureIndex(array('ae.snuid' => 1), array("unique" => false));
		echo "Create users.ae.snuid index: " . ($result?"OK":"FAIL") . "\n";

		$collection = $db->friends;
		$result = $collection->ensureIndex(array('auid' => 1), array("unique" => false));
		echo "Create friends.auid index: " . ($result?"OK":"FAIL") . "\n";
		$result = $collection->ensureIndex(array('friend_auid' => 1), array("unique" => false));
		echo "Create friends.friend_auid index: " . ($result?"OK":"FAIL") . "\n";

		$collection = $db->sn_friends;
		$result = $collection->ensureIndex(array('auid' => 1), array("unique" => false));
		echo "Create sn_friends.auid index: " . ($result?"OK":"FAIL") . "\n";
		$result = $collection->ensureIndex(array('snuid' => 1), array("unique" => false));
		echo "Create sn_friends.snuid index: " . ($result?"OK":"FAIL") . "\n";
		$result = $collection->ensureIndex(array('snid' => 1), array("unique" => false));
		echo "Create sn_friends.snid index: " . ($result?"OK":"FAIL") . "\n";

		$collection = $db->user_properties;
		$result = $collection->ensureIndex(array('auid' => 1), array("unique" => false));
		echo "Create user_properties.auid index: " . ($result?"OK":"FAIL") . "\n";
		$result = $collection->ensureIndex(array('e_auid' => 1), array("unique" => false));
		echo "Create user_properties.e_auid index: " . ($result?"OK":"FAIL") . "\n";
	}
}

$i = new Indexer($config);
$i->run();

