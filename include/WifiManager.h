#pragma once 
#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>

class WifiManager
{
public:
    WifiManager();
    WifiManager(String ssid, String password);
    String GetJsonFromAPI(String api);
    void PutJsonToAPI(String api, String json);
    String GetIp();
    String obtenirIPPublique();
    bool isConnected();
private:
    String m_Ip;
};