<?php
/* Import all users from anover db to current.
 * Assing new auid's to them, apply pwc_snuid changes and rebuild friend lists.
 * Prepare auid replacement list for the subsequent stages.
 * http://devjira.nivalnetwork.com/browse/PF-80368
 */

require __DIR__ . '/config.php';
require __DIR__ . '/common.php';

class Dropper extends Common
{
	private $checkMode = false;
	private $anyOne = false;

	function prepare()
	{
		parent::prepare();
	}

	public function parse_options($shortOptions, $longOptions)
	{
		$longOptions[] = "check";  // Check mode - verify 'dt_last_login' and 'dt_register' existance
		$longOptions[] = "any";    // If one of 'dt_last_login' and 'dt_register' doesn't exist - use another one only
		parent::parse_options($shortOptions, $longOptions);
		if (isset($this->params['check']))
			$this->checkMode = true;
		if (isset($this->params['any']))
			$this->anyOne = true;
	}

	function perform()
	{
		if ($this->checkMode)
		{
			list($nologin, $noreg) = $this->usUsers->getOnlyRegOrLogin($this->config->us_start_date);
			if ($nologin || $noreg)
			{
				print "NO dt_last_login: " . count($nologin) . " users:\n";
				if ($nologin) {
					print "Auid ";
					foreach ($nologin as $user) print " " . $user['_id'];
					print "\n";
				}
				print "NO dt_register: " . count($noreg) . " users:\n";
				if ($noreg) {
					print "Auid ";
					foreach ($noreg as $user) print " " . $user['_id'];
					print "\n";
				}
			}
			else
			{
				print "All users have both dt_last_login and dt_register\n";
			}
			return;
		}
		$oldUsers = $this->usUsers->getByRegAndLogin($this->config->us_start_date, $this->anyOne);
		print "Old users found: " . count($oldUsers) . "\n";
		foreach ($oldUsers as $user)
		{
			print "Removing user " . $user['_id'] . "\n";
			// delete user
			$this->usUsers->remove($user['_id']);
			// delete friends
			$this->usFriends->removeByAuid($user['_id']);
			// delete sn_friends
			$this->usFriends->removeSnFriendsAll($user['_id']);
			// mark unused
			foreach (Assistant::$SNLIST as $snid)
			{
				if (isset($user[$snid]['snuid']))
                    $this->usFriends->markUnusedBySnuid($snid, $user[$snid]['snuid']);
			}
		}
	}

	function finalize()
	{
		print "Done\n";
	}
}

$d = new Dropper($config);
$d->run();
