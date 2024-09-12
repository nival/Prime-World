<?php
ini_set('display_errors', true);
header('Content-type: text/plain');
//$id="109886800";
$id="shtest177"; // accaunt
$sntoken="d630be7fbbfdc1c91235f1b270c305d4";

$sSocAgrPath = "217.174.109.183:89";

//$cont = file_get_contents("http://217.174.109.183:89/?action=register&snid=arc&snuid=".$id."&sntoken=".$sntoken."&version=0.3.93&snrefresh_token=None&use_billing=0&referral=RU/RU0");
													//action=register&snid=arc&snuid=shtest177&sntoken=hsbf2j4ccoqwhcs1&version=0.3.93&snrefresh_token=None&use_billing=1&referral=RU/RU0
//$cont = file_get_contents("http://217.174.109.183:89/?action=register&snid=arc&snuid=shtest177&sntoken=hsbf2j4ccoqwhcs1&version=0.3.93&snrefresh_token=None&use_billing=1&referral=RU/RU0");
$cont = file_get_contents("http://{$sSocAgrPath}/?action=register&snid=arc&snuid=".$id."&sntoken=".$sntoken."&version=0.3.93&snrefresh_token=None&use_billing=0&referral=RU/RU0");
var_dump($cont);
$cont = file_get_contents("http://{$sSocAgrPath}/?action=login&snid=arc&snuid==".$id."&sntoken=".$sntoken."&version=0.3.93&auto=0&snrefresh_token=None&use_billing=0&referral=RU/RU0");
var_dump($cont);
