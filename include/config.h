#pragma once

#define SERVEURWEB true
#define TESTDEMO false

#if SERVEURWEB

    #define SSID "ESP32AP_2292860"
    #define MOTDEPASSE "12345678"
    #define API "http://192.168.23.1/coeur-reacteur"

#elif TESTDEMO

    #define SSID "iot_lab"
    #define MOTDEPASSE "engagelejeuquejelegagne"
    #define API "http://10.23.208.10/coeur-reacteur"

#endif