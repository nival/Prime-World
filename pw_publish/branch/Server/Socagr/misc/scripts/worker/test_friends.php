<?php
require_once dirname(__FILE__).'/../../../application/background/settings/config.php';
$paths = implode(PATH_SEPARATOR, array(
	$config['path']['library'],
	implode(PATH_SEPARATOR, $config['path']['models'])
));
set_include_path($paths);
require_once dirname(__FILE__).'/../../../application/background/Initializer.php';
require_once dirname(__FILE__).'/../../../library/Sa/Log.php';
require_once dirname(__FILE__).'/../../../application/background/workers/workerHelpers.php';

// fb
// http://217.174.109.183:89/?action=login&snid=fb&snuid=100002263785988&sntoken=CAAB9M8ptmXMBAKcRMNQuAxeynMeaFZCA9tbhITnobjWvAvQ3YzapsgnsVy0UKTqZBaofflkOirytay2gSqW2VICh00qZAdCd3oOtPFjYmdkH5bJOwtcZBZC7jzJqanSCuMP1QlUIquiDMoZCGxsLPZASZB4nOkZB1PcPHkjEWvIinizlALYsyKNmEBaSTMGLfUjYZD&version=0.3.93&auto=0&snrefresh_token=None&use_billing=1&referral=RU/EN0
/*
refreshInfo(array(
	'_id'=>100002263785988,
	'sntoken'=>'CAAB9M8ptmXMBAKcRMNQuAxeynMeaFZCA9tbhITnobjWvAvQ3YzapsgnsVy0UKTqZBaofflkOirytay2gSqW2VICh00qZAdCd3oOtPFjYmdkH5bJOwtcZBZC7jzJqanSCuMP1QlUIquiDMoZCGxsLPZASZB4nOkZB1PcPHkjEWvIinizlALYsyKNmEBaSTMGLfUjYZD',
	'sn'=>'fb'
));
refreshInfo(array(
	'_id'=>806312,
	'sntoken'=>'CAAB9M8ptmXMBAKcRMNQuAxeynMeaFZCA9tbhITnobjWvAvQ3YzapsgnsVy0UKTqZBaofflkOirytay2gSqW2VICh00qZAdCd3oOtPFjYmdkH5bJOwtcZBZC7jzJqanSCuMP1QlUIquiDMoZCGxsLPZASZB4nOkZB1PcPHkjEWvIinizlALYsyKNmEBaSTMGLfUjYZD',
	'sn'=>'fb'
));
*/

// action=login&snid=ok&snuid=166789425438&sntoken=f1i.YBcaIr68YJomJpskeIH03p31WMozLc&version=0.3.93&auto=0&snrefresh_token=6e10b6q6G984a5HZOd59bWl5qe27YUk7He98XSq_N000dXp0M2_ddWKdHe&use_billing=1&referral=RU/EN0
refreshInfo(array(
	'_id'=>21,
	'sntoken'=>'f1i.YBcaIr68YJomJpskeIH03p31WMozLc',
	'sn'=>'ok'
));