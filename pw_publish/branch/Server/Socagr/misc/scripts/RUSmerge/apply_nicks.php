<?php
/*
 */

require __DIR__ . '/config.php';
require __DIR__ . '/common.php';

class Renamer extends Common
{
	private $nickMap; // array of auid => newNick

	public function parse_options($shortOptions, $longOptions)
	{
		$longOptions[] = "nicks:";  // Requires a file name of pwc_snuid translation table
		parent::parse_options($shortOptions, $longOptions);
		if (!isset($this->params["nicks"]))
		{
			print "ERROR! No nicks translation data! Use --nicks FILENAME parameter.\n";
			exit(2);
		}
	}

	function prepare()
	{
		parent::prepare();
		$this->load_nicks();
	}

	function load_nicks()
	{
		$this->nickMap = $this->load_json_file($this->params['nicks']);
		print count($this->nickMap) . " new nicks found.\n";
	}

	function perform()
	{
		foreach ($this->nickMap as $auid => $nick)
		{
			printf("Setting nick %s to user %d\n", $nick, $auid);
			$this->ruUsers->edit($auid, array('nick' => $nick));
		}
	}

	function finalize()
	{
		print "Done\n";
	}
}

$ren = new Renamer($config);
$ren->run();
