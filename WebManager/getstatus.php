<?php
include("common.php");

$configFile = "WebManager/data/config.json";
$message = 's';

$response = sendMessageForResponse($configFile, $message);

if(empty($response)){
    echo json_encode(array(
        'success' => false,
        'data' => array()
    ));
    exit;
}

$data = explode(';', $response);
echo json_encode(array(
    'success' => true,
    'data' => array(
        'state' => (int) explode('(', $data[0])[1],
        'currentUid' => $data[1],
        'foodPercentage' => (float) $data[2],
        'time' => (int) $data[3],
        'timeLeft' => (int) explode(')', $data[4])[0],
        'serialResponse' => explode('(', $data[0])[0],
        'response' => trim($response)
    )
));
