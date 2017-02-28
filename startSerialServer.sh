#!/bin/bash

dev="$1";

speed="9600";
logFile="WebManager/data/log.json";
configFile="WebManager/data/config.json";
fileBuffer="WebManager/data/buffer.txt";
responseDelay="2";
dataDir="WebManager/data/";

cd $( cd -P "$( dirname "${BASH_SOURCE[0]}" )" && pwd )

if [[ ! -d "$dataDir" ]]; then
    mkdir $dataDir
fi

cfg=$(php -r "echo json_encode(['dev' => '$dev', 'filebuffer' => '$fileBuffer', 'logFile' => '$logFile', 'responseDelay' => $responseDelay]);");
echo "Arquivo de configuração \"$configFile\"";
echo "$cfg" > "$configFile";

echo "Iniciando servidor";
bash -c "stty -F $dev raw speed $speed >> /dev/null";
cat $dev >> $fileBuffer
