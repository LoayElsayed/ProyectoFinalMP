#include "header.h"

typedef enum
{
	TIPUS_NORMAL,
	TIPUS_DAMA,
	TIPUS_EMPTY
} TipusFitxa;

typedef enum
{
	COLOR_NEGRE,
	COLOR_BLANC,
	COLOR_NUL
} ColorFitxa;

class Fitxa
{
public:
	Fitxa() : m_tipusFitxa(TIPUS_EMPTY), m_colorFitxa(COLOR_NUL) {};

	//-------------------Setters-------------------//
	void setTipus(const char& tipus);

	//-------------------Getters-------------------//
	int getColor(void) const { return m_colorFitxa; }
	int getTipus(void) const { return m_tipusFitxa; }
private:
	TipusFitxa m_tipusFitxa;
	ColorFitxa m_colorFitxa;
};
