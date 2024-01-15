#include "Program.h"
#include "config.h"


Program::Program(){
    Serial.begin(9600);
    Serial.println();
    Serial.println("Controller started");
    m_controller = new Controller(25,17,16);
    m_controller->connectionToReactor(SSID, MOTDEPASSE, API);
};

void Program::loop() {
    m_controller->toggleReactorCore();
}