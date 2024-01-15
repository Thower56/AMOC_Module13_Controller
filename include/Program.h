#pragma once
#include <WifiManager.h>
#include <Controller.h>

class Program{
public:
    Program();
    void loop();
private:
    Controller* m_controller;
};

