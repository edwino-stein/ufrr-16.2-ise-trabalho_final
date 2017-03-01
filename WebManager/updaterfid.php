<?php
include("common.php");

$configFile = "WebManager/data/config.json";
$message = 'r';

$response = sendMessageForResponse($configFile, $message);
$data = explode('(', $response);

echo json_encode(array(
    'success' => true,
    'data' => array(
        'status' => explode(')', $data[1])[0],
        'serialResponse' => $data[0],
        'response' => trim($response)
    )
));
