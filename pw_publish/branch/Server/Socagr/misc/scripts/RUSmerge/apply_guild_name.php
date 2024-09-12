<?php
/*
 */

require __DIR__ . '/config.php';
require __DIR__ . '/common.php';

class Renamer extends Common
{
	private $gsnMap; // array of auid => newNick

	public function parse_options($shortOptions, $longOptions)
	{
		$longOptions[] = "names:";  // Requires a file name of pwc_snuid translation table
		parent::parse_options($shortOptions, $longOptions);
		if (!isset($this->params["names"]))
		{
			print "ERROR! No new guildshotname data! Use --names FILENAME parameter.\n";
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
		$this->gsnMap = $this->load_json_file($this->params['names']);
		print count($this->gsnMap) . " new nicks found.\n";
	}

	function perform()
	{
		foreach ($this->gsnMap as $auid => $gsn)
		{
			printf("Setting guildshortname '%s' to user %d\n", $gsn, $auid);
			$this->ruUsers->edit($auid, array('guildshortname' => $gsn));
		}
	}

	function finalize()
	{
		print "Done\n";
	}
}

$ren = new Renamer($config);
$ren->run();
