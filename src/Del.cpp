#include <DEL.h>

DEL::DEL(uint8_t p_pinDEL){
    m_pinDEL = p_pinDEL;
    m_etapeCycle = 0;
    m_dureeActionMS = 0;
    m_dateDernierDecrementdureeActionUs = 0;
};
void DEL::allumer(){
    analogWrite(m_pinDEL, 255);
};
void DEL::allumer(float p_poucentageIntensite){
    m_poucentageIntensite = p_poucentageIntensite;
    analogWrite(m_pinDEL, p_poucentageIntensite);
};
void DEL::eteindre(){
    analogWrite(m_pinDEL, 0);
};

int DEL::getPourcentageIntensite(){
    return m_poucentageIntensite;
};

void DEL::clignoter(int p_allumer, int p_eteint){
    while (m_dureeActionMS > 0 && (micros() - m_dateDernierDecrementdureeActionUs) >= 1000) {
    m_dureeActionMS--;
    m_dateDernierDecrementdureeActionUs += 1000;
  }

  if (m_dureeActionMS == 0) {
    switch (m_etapeCycle) {
      case 0:
        allumer();
        m_dureeActionMS = p_allumer;
        ++m_etapeCycle;
        break;
      case 1:
        eteindre();
        m_dureeActionMS = p_eteint;
        m_etapeCycle = 0;
      default:
        break;
    }
  }

};