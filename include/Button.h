#pragma once
#include <Arduino.h>
#include <functional>

class Button{
public:
    typedef std::function<void(void)> THandlerFunction;
    Button(uint8_t p_pinButton);
    void setFunction(THandlerFunction p_fn);
    void tick();
    int getPin();
private:
    THandlerFunction m_fn;
    int m_pin;
    bool m_boutonPresse;
    int etatBouton;

    long derniereDateChangement;
    int dernierEtatBouton;
    int dernierEtatStableBouton;
    const int delaiMinPression;
};