#include "fitxa.h"

void Fitxa::setTipus(const char& tipus)
{
	switch (tipus)
	{
	case 'O': {
		m_colorFitxa = COLOR_BLANC;
		m_tipusFitxa = TIPUS_NORMAL;
		break;
	}
	case 'X': {
		m_colorFitxa = COLOR_NEGRE;
		m_tipusFitxa = TIPUS_NORMAL;
		break;
	}
	case 'D': {
		m_colorFitxa = COLOR_BLANC;
		m_tipusFitxa = TIPUS_DAMA;
		break;
	}
	case 'R': {
		m_colorFitxa = COLOR_NEGRE;
		m_tipusFitxa = TIPUS_DAMA;
		break;
	}
	default:
		m_colorFitxa = -1;
		m_tipusFitxa = -1;
	}

}