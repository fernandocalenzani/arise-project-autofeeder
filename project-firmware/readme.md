---
BMS TECHNOLOGY

name: Autofeeder-IoT
base version: 1.0.0.0
author: BMS Technology <contato.grupobms@gmail.com>
maintainer: BMS Technology <contato.grupobms@gmail.com>
sentence: automatic powder solids doser with integrated IoT
paragraph: automatic powder solids doser with integrated IoT
category: IoT Technology
url: https://github.com/BMS-Technology/bms-projects
architectures: *
firmware-language: C++ [.cpp]
framework: arduino [.ino]
---

# AUTOFEEDER: FIRMWARE

Autofeeder firmware is a specific class of computer software that provides low-level control for device-
specific hardware. Among them are:

- http request;
- temperature and humidity sensor;
- mass sensor;
- ultrasonic sensor;
- local timer;
- online timer;
- Serial Number: node: require('crypto').randomBytes(16).toString('hex')
- Login: SerialNumber@bms.com.br
- Password: node: require('crypto').randomBytes(16).toString('hex')

## ALERTS LED

- LED RANDOM COLOR: restarting system
- BLUE LED : connected to internet
- RED LED : something wrong
- YELLOW LED: alerts
- GREEN LED : everything okay
- LED frequency: 1 hz normal
- LED frequency: 2 hz update
- LED frequency: 4 hz critical

## VERSION

### X.Y.Z.W

X) inclusão ou extensão de funcionalidades;
Y) correções de bugs;
Z) mudança de arquitetura ou refatoração de código;
W) correções pequenas e ajustes estéticos.

## WIFI CONFIGURATION

STEP 1) press reset button
STEP 2) press button wifi configuration for 10 seconds;
STEP 3) access your device's wifi settings;
STEP 4) search for bms_wifi, click connect by entering the default password: 12345678;
STEP 5) click connect;
STEP 6) open your browser and insert the address shown on the display, something like: 192.168.4.1;
STEP 7) click "wifi configuration";
STEP 8) insert your SSID, password and click in save;
STEP 9) close your browser;

## OBS:

1°) DATE FORMATE SEND REQUEST: Friday, December 09 2022 21:46:2
2°) Numero máximo de vezes simultaneas que se pode inserir dosagem: 100
3°) dosador não trabalha de 00h até as 00:05 (transformação de variavel)
4°) formato de envio das datas:

