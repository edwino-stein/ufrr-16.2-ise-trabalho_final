<?php
include("common.php");

$configFile = "WebManager/data/config.json";
$message = 'u';

$uid = isset($_GET['uid']) ? $_GET['uid'] : "";

$response = sendMessageForResponse($configFile, $message.$uid);
echo json_encode(array(
    'uid' => $uid
));
