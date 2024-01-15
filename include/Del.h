#pragma once
#include <Arduino.h>

class DEL{
public:
    DEL(uint8_t p_pinDEL);
    void allumer();
    void allumer(float p_poucentageIntensite);
    void clignoter(int p_allumer, int p_eteint);
    int getPourcentageIntensite();
    void eteindre();
private:
    uint8_t m_pinDEL;
    int m_etapeCycle;
    unsigned long m_dureeActionMS;
    uint32_t m_dateDernierDecrementdureeActionUs;
    int m_poucentageIntensite;
};