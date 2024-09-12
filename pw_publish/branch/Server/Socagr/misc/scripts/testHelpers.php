<?php
/**
 * @param array $request formatted into json/xml, send as post body
 * @return array
 */
function sendRequest($request,$url){
	$data = json_encode($request);

	$random = getRandonString(RANDOM_CHARS, RANDOM_LENGTH);
	$time = time();
	$version = 1;
	$game = GAME;
	$key = SECRET;
	$sig = hash_hmac('sha1', $random.$time.$version.$game.$data, $key);

	$params = array();
	$params['f'] = FORMAT;
	$params['r'] = $random;
	$params['t'] = $time;
	$params['v'] = $version;
	$params['g'] = $game;
	$params['sig'] = $sig;
	$params_encodes = array();
	foreach($params as $k => $v){
		$params_encodes[] = $k.'='.urlencode($v);
	}

	$url = $url.'/?'.join('&', $params_encodes);

	printf("CALL METHOD: %s", $request['method']);
	print_r("\n---------------------------------------------------\n");
	printf("URL: \n%s\n", $url);
	printf("BODY: \n%s\n", $data);

	$ch = curl_init();
	curl_setopt($ch, CURLOPT_URL, $url);
	curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
	curl_setopt($ch, CURLOPT_HEADER, 0);
	curl_setopt($ch, CURLOPT_POST, 1);
	curl_setopt($ch, CURLOPT_POSTFIELDS, $data);
	$output = curl_exec($ch);
	curl_close($ch);
	printf("RESULT: \n%s\n", $output);
	echo "\n\n\n";
	$response = json_decode($output, true);
	return $response;
}