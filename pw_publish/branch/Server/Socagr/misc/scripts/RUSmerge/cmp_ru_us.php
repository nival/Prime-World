<?php
/* Fix US accounts' pwc-logins.
 * Than compare all sn lognis for all users in US and RU databses.
 * All US account with no logins intersections list into sa_copy.json
 * All intersections list into sa_dups.json
 * http://devjira.nivalnetwork.com/browse/PF-81952
 */

require __DIR__ . '/config.php';
require __DIR__ . '/common.php';

class AccountComparer extends Common
{
	private $pwc_uids = array(); # pwc snuid translation table
	private $no_pwc = false;
	private $prepared_ts = 0;
	private $compared_ts = 0;
	private $finish_ts = 0;
	private $sa_copy, $sa_dups;

	/* public function __construct($config_array)
	{
		parent::__construct($config_array);
		// ...	
	} */
 
	public function parse_options($shortOptions, $longOptions)
	{
		$longOptions[] = "pwc:";   // Requires a file name of pwc_snuid translation table
		$longOptions[] = "nopwc";
		parent::parse_options($shortOptions, $longOptions);
		if (isset($this->params["nopwc"]))
		{
			print "PWC snuid mapping disbled\n";
			$this->no_pwc = true;
		}
		elseif (!isset($this->params["pwc"]))
		{
			print "ERROR! No pwc_snuid translation data!\n";
			exit(2);
		}
	}

	/* Load pwc_suid translation map and duplicate list.
	 * They should be prepared on PWC merge stage. */
	function load_pwc()
	{
		$fname = $this->params['pwc'];
		$pwc_json = file_get_contents($fname, "r");
		$this->pwc_uids = json_decode($pwc_json, true);
		print count($this->pwc_uids["map"]) . " PWC snuid translations loaded.\n";
		print count($this->pwc_uids["dup"]) . " duplicate e-mails listed.\n";
	}

	function prepare()
	{
		parent::prepare();
		if (!$this->no_pwc) $this->load_pwc();
		print $this->ruUsers->getUsersCount() . " RU users found.\n";
		print "Importing " . $this->usUsers->getUsersCount() . " US users.\n";
	}

	function fix_pwc()
	{
		foreach(iterator_to_array($this->usUsers->getAllBySn('pwc')) as $usUser)
		{
			$old = $usUser['pwc']['snuid'];
			if (!isset($this->pwc_uids["map"][$old]))
			{
				$ru = $this->ruUsers->getSnUser('pwc', $old);
				if ($ru && isset($ru['pwc']['email']) && isset($usUser['pwc']['email']) && $ru['pwc']['email'] == $usUser['pwc']['email'])
				{
					print "INFO: US pwc_snuid $old not found in pwc snuids map BUT exists in RU, so it's just a copy.\n";
				}
				else
				{
					print "WARNING: US pwc_snuid " . $old . " not found both in pwc snuids map in " . $this->params['pwc'] . " and in RU SA!\n";
				}
				continue;
			}
			$usUser['pwc']['snuid'] = $this->pwc_uids["map"][$old] . '';
			$this->usUsers->edit($usUser['_id'], array("pwc.snuid" => $usUser['pwc']['snuid']));
			printf("US user %s, updated pwc.snuid %s -> %s (%s)\n", $usUser['_id'], $old, $usUser['pwc']['snuid'], $usUser['pwc']['email']);
			if (strlen($usUser['pwc']['email']) == 0)
				printf("WARNING: US user %s has PWC login %s with EMPTY email!\n", $usUser['_id'], $usUser['pwc']['snuid']);
		}
	}

	/* Copy `users` collection records, assigning new auids.
	 * Prepare auid translation map. */
	function perform()
	{
		$dups = array(); # list of lists of duplicates, keys are duplist head's auid (heads are always from RU)
		$copy = array(); # list of US (auid, fsn_lofin) for copy to RU
		$heads = array(); # keys - auids of already found duplicated account at RU (used to find chains), values - heads of their chains
		                  # heads themselves also listed here (refering to themselves)

		# Really fix_pwc could be a separate step with it's own script, but now it's too late to change
		if (!$this->no_pwc) $this->fix_pwc();
		#
		foreach ($this->usUsers->getAll() as $usUser)
		{
			$fsnLogin = UsersExt::getFsnLogin($usUser);
			$head = null;
			$usMixId = array('US', $usUser['_id'], $fsnLogin, UsersExt::checkGhost($usUser));
			foreach (Assistant::$SNLIST as $snid)
			{
				if (isset($usUser[$snid]['snuid']))
				{
					$snuid = $usUser[$snid]['snuid'];
					$ruUser = $this->ruUsers->getSnUser($snid, $snuid);
					if ($ruUser)
					{
						printf("US user %s and RU user %s duplicate by %s.snuid %s\n", $usUser['_id'], $ruUser['_id'], $snid, $snuid);
						$ruAuid = $ruUser['_id'];
						$ruMixId = array('RU', $ruAuid, UsersExt::getFsnLogin($ruUser), UsersExt::checkGhost($usUser));
						if ($head != null) # it's not the first dup for this $usUser
						{
							$first = true;
							foreach($dups[$head] as $mix)
							{
								if ($mix[1] == $ruAuid)
								{
									$first = false;
									break;
								}
							}
							if ($first)
							{
								if (isset($heads[$ruAuid])) # and $ruUser is also linked already - has to link two lists
								{
									#printf("RU %s has a head %s\n", $ruAuid, $heads[$ruAuid]);
									$current = $dups[$head];
									$dups[$heads[$ruAuid]] = array_merge($dups[$heads[$ruAuid]], $dups[$head]);
									unset($dups[$head]);
									$head = $heads[$ruAuid];
								}
								else
								{
									$dups[$head][] = $ruMixId;
									$heads[$ruAuid] = $head;
									#printf("RU acc joined to the chain %s\n", $head);
								}
							}
						}
						else // the first dup for this $usUser
						{
							if (isset($heads[$ruAuid])) // this RU acc is already in a chain
							{
								$head = $heads[$ruAuid]; // take that chain head
								$dups[$head][] = $usMixId; // add US acc to the chain
								#printf("Joined to the chain %s\n", $head);
							}
							else // create a new chain
							{
								$heads[$ruAuid] = $head = $ruAuid;
								$dups[$ruAuid] = array($ruMixId, $usMixId);
								#printf("%s is a new chain head\n", $head);
							}
						}
					}
				}
			}
			if (!$head) # no $head - no dupes found
			{
				$copy[] = array($usUser['_id'], $fsnLogin);
			}
		}
		$this->sa_copy = $copy;
		$this->sa_dups = $dups; // перед записью в файл превратить в обычный список значений
	}

	function finalize()
	{
		print count($this->sa_copy) . " US accounts listed to be copied.\n";
		print count($this->sa_dups) . " duplication chains found.\n";
		file_put_contents('sa_copy.json', json_encode($this->sa_copy));
		$duplist = array();
		$us_dups = array();
		$ru_dups = array();
		foreach($this->sa_dups as $head => $data)
		{
			$chain = array();
			foreach($data as $acc)
			{
				$chain[] = array('locale' => $acc[0], 'auid' => $acc[1], 'login' => $acc[2], 'ghost' => $acc[3]);
				if ($acc[0] == 'RU')
				{
					$ru_dups[] = $acc[1]."\n";
				}
				else
				{
					$us_dups[] = $acc[1]."\n";
				}
			}
			$duplist[] = $chain;
		}
		file_put_contents('sa_dups.json', json_encode($duplist));
		file_put_contents('sa_dups_ru.txt', implode('', $ru_dups));
		file_put_contents('sa_dups_us.txt', implode('', $us_dups));

	}
}

$cmp = new AccountComparer($config);
$cmp->run();


