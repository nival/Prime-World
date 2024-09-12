<?php
ini_set('display_errors', true);
header('Content-type: text/plain');

$sSocAgrPath = "217.174.109.183:89";

/**
 * @param array $request formatted into json/xml, send as post body
 * @return array
 */
function sendGetRequest($params)
{
	global $sSocAgrPath;
	$params_encodes = array();
	foreach($params as $k => $v)
		$params_encodes[] = $k.'='.urlencode($v);

	$url = 'http://'.$sSocAgrPath.'/?'.join('&', $params_encodes);

	printf("CALL METHOD: GET");
	print_r("\n---------------------------------------------------\n");
	printf("URL: \n%s\n", $url);

	$ch = curl_init();
	curl_setopt($ch, CURLOPT_URL, $url);
	curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
	curl_setopt($ch, CURLOPT_HEADER, 0);
	$output = curl_exec($ch);
	curl_close($ch);
	printf("RESULT: \n%s\n", $output);
	echo "\n\n\n";
	$response =  json_decode($output, true);
	return $response;
}

$auid=36;
echo "\n";

echo "Set property_name fsn to arc :\n";

$params = array();
$params['action'] = 'set_property';
$params['auid'] = $auid;
$params['version'] = '0.3.93';
$params['property_name'] = 'fsn';
$params['property_value'] = 'arc';
$response = sendGetRequest($params) ;

echo "Set property_name reg to 1 :\n";
$params = array();
$params['action'] = 'set_property';
$params['auid'] = $auid;
$params['version'] = '0.3.93';
$params['property_name'] = 'reg';
$params['property_value'] = '1';
$response = sendGetRequest($params) ;

echo "get_info :\n";
//http://217.174.109.183:89/?action=get_info&auid=34&version=0.3.93&include_secure_data=1
$params = array();
$params['action'] = 'get_info';
$params['auid'] = $auid;
$params['version'] = '0.3.93';
$params['include_secure_data'] = '1';
$response = sendGetRequest($params) ;

echo "get_all_properties :\n";
//http://217.174.109.183:89/?action=get_all_properties&auid=2&version=0.3.93&include_secure_data=1
$params = array();
$params['action'] = 'get_all_properties';
$params['auid'] = $auid;
$params['version'] = '0.3.93';
$response = sendGetRequest($params) ;
