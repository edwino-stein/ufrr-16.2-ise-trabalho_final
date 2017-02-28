<?php
include("common.php");

$configFile = "WebManager/data/config.json";
$message = 't';
$unities = array('hour' => 0x80, 'minute' => 0x0);

$unit = isset($_GET['u']) ? $_GET['u'] : "minute";
$unit = isset($unities[$unit]) ? $unities[$unit] : $unities['minute'];

$time = isset($_GET['t']) ? (int) $_GET['t'] : 30;
if($time < 0) $time = 0;
if($time > 127) $time = 127;

if(isset($_GET['r'])){
    $message = $message . chr($unit | $time) . chr(1);
}
else{
    $message = $message . chr($unit | $time);
}

$response = sendMessageForResponse($configFile, $message);
$data = explode('(', $response);

echo json_encode(array(
    'timeLeft' => explode(')', $data[1])[0],
    'serialResponse' => $data[0],
    'response' => trim($response)
));
