<?php

function readConfig($configFile){
    chdir(realpath(__DIR__.'/../'));
    return json_decode(file_get_contents($configFile), true);
}

function clearFileBuffer($fileBuffer){
    system("echo -n \"\" > $fileBuffer");
}

function readFileBuffer($fileBuffer){
    $buffer = explode("\n", file_get_contents($fileBuffer));
    clearFileBuffer($fileBuffer);
    return $buffer;
}


function sendMessage($dev, $message){
    system("echo -n \"$message\" >> $dev");
}

function saveLog($logFile, $data){

    $jsonLog = json_decode(file_get_contents($logFile), true);
    if($jsonLog == null){
        $jsonLog = array();
    }

    $jsonLog[] = array(
        'dateTime' => date("d/m/Y-H:i:s"),
        'occurrences' => $data
    );

    file_put_contents($logFile, json_encode($jsonLog), FILE_TEXT);
}

function sendMessageForResponse($cfgFile, $message){

    $cfg = readConfig($cfgFile);
    $preBuffer = readFileBuffer($cfg['filebuffer']);

    sendMessage($cfg['dev'], $message);
    sleep($cfg['responseDelay']);

    $buffer = readFileBuffer($cfg['filebuffer']);
    $bufferLen = count($buffer);

    for($i = $bufferLen - 1; $i >= 0; $i--){
        if(preg_match("/^\d+S\(.*\)/", $buffer[$i]) == 1) break;
    }

    saveLog($cfg['logFile'], array_merge($preBuffer, $buffer));
    return $buffer[$i];
}
