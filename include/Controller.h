#pragma once
#include <ArduinoJson.h>
#include <WifiManager.h>
#include <Del.h>
#include <Button.h>
#include <Arduino.h>

class Controller{
public:
    Controller(int p_pinButton, int p_RedLightPin, int p_GreenLightPin);
    void connectionToReactor(String p_ssid, String p_password, String p_API);
    void getReactorStatus();
    void updateReactorLightStatus(String p_status);
    void checkForUpdateStatus();
    void toggleReactorCore();
private:
    int m_derniereDateChangement;
    String m_API;
    String m_ReactorStatus;
    Button* m_button;
    DEL* m_RedDel;
    DEL* m_GreenDel;
    WifiManager* m_wifiManager;
};


