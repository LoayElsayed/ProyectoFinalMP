#include "header.h"
#include "posicio.h"

class Fitxa
{
public:
	Fitxa() : m_colorFitxa(COLOR_NEGRE), m_tipusFitxa(TIPUS_EMPTY) {};
	Fitxa(int& tipusFitxa, int& colorFitxa) : m_tipusFitxa(tipusFitxa), m_colorFitxa(colorFitxa) {};
	//-------------------Setters-------------------//
	void setNormal(void) { m_tipusFitxa = TIPUS_NORMAL; }
	void setDama(void) { m_tipusFitxa = TIPUS_DAMA; }
	void setEmpty(void) { m_tipusFitxa = TIPUS_EMPTY; }
	void setTipus(const char& tipus);

	//-------------------Getters-------------------//
	int getColor(void) const { return m_colorFitxa; }
	int getTipus(void) const { return m_tipusFitxa; }

private:
	int m_colorFitxa;
	int m_tipusFitxa;
	Posicio m_posicio;
};
