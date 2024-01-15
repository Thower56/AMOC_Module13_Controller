#include "Controller.h"
#include <config.h>

Controller::Controller(int p_Buttonpin, int p_RedLightPin, int p_GreenLightPin){
    m_button = new Button(p_Buttonpin);
    m_RedDel = new DEL(p_RedLightPin);
    m_GreenDel = new DEL(p_GreenLightPin);
    m_derniereDateChangement = 0;
    m_button->setFunction([this]() {
            Serial.println("#####| Function button |#####");
            String actif = "{\"etat\":\"actif\"}" ;
            String repos = "{\"etat\":\"repos\"}" ;
            String json = (this->m_ReactorStatus == "actif") ? repos : actif;
            Serial.println("Send: " + json + " to API");
            this->m_wifiManager->PutJsonToAPI(m_API, json);
        });
};

void Controller::connectionToReactor(String p_ssid, String p_password, String p_API) {
    m_wifiManager = new WifiManager(p_ssid, p_password);
    m_API = p_API;
    this->getReactorStatus();
}
void Controller::getReactorStatus() {
    Serial.println("");
    Serial.println("#####| GetReactorStatus | #####");
    Serial.println("Getting json from + " + m_API);
    String reactorStatus = m_wifiManager->GetJsonFromAPI(m_API);
    DynamicJsonDocument doc(20000);
    DeserializationError error = deserializeJson(doc, reactorStatus);

    if(error){
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.f_str());
    }

    String status = doc["etat"];

    if(status != m_ReactorStatus){
        updateReactorLightStatus(status);
    }
    
}

void Controller::updateReactorLightStatus(String p_status) {
    if(p_status == "actif"){
        m_RedDel->allumer();
        m_GreenDel->eteindre();
        m_ReactorStatus = p_status;
        Serial.println(m_ReactorStatus);
    }
    else if (p_status == "repos")
    {
        m_RedDel->eteindre();
        m_GreenDel->allumer();
        m_ReactorStatus = p_status;
        Serial.println(m_ReactorStatus);
    }
}

void Controller::checkForUpdateStatus(){
    long dateActuelle = millis();
    if(dateActuelle - m_derniereDateChangement > 5000 ) {
        Serial.println("#####| Update | #####");
        getReactorStatus();
        m_derniereDateChangement = dateActuelle;
        Serial.println("#####################");
    }
};

void Controller::toggleReactorCore() {
    if(m_wifiManager->isConnected()) {
        m_button->tick();
    }
}