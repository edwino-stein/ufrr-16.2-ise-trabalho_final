# Trabalho final de Sistemas Embarcados 2016.2

- Componenetes:
    - Edwino Alberto Lopes Stein
    - Pedro Daniel da Silva Gohl
 - Professor: Herbet Oliveira Rocha
 - Instituição: Universidade Federal de Roraima

## Bibliotecas necessárias:
- Servo (Micro servo 9g):
    - Compatível com a biblioteca **Servo.h** padrão do Arduino
- MsTimer2:
    - Disponível para download pelo gerenciador de bibliotecas da IDE do Arduino
    - Também Disponível na [Página da PJRC](https://www.pjrc.com/teensy/td_libs_MsTimer2.html)
- HC-SR04 Ultrasonic sensor:
    - Disponível no [Repositório Felipeflop](https://github.com/filipeflop/Ultrasonic)
    - Também no arquivo **Libs/HC-SR04 Ultrasonic sensor.zip**
- MFRC522 RFID sensor:
    -  Disponível no [Repositório de miguelbalboa](https://github.com/miguelbalboa/rfid)
    -  Também no arquivo **Libs/MFRC522 RFID sensor.zip**

## Utilizando comunicação serial com programa externo
Para a comunição serial **funcionar sem a IDE do Arduino**, é necessário realizar um workaround no Arduino para desabilitar o **autoreset**, como é ilustrado neste [artigo do Arduino playground](http://playground.arduino.cc/Main/DisablingAutoResetOnSerialConnection).
Para o Arduino Uno, basta conectar um capacitor de **10µF** nos pinos GND (polo negativo) e RESET (polo positivo).
