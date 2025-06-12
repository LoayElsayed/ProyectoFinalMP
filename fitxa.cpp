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
		m_colorFitxa = COLOR_NUL;
		m_tipusFitxa = TIPUS_EMPTY;
	}

}

char Fitxa::getTipusString(void) const
{
	if (this != nullptr)
		if (m_colorFitxa == COLOR_BLANC)
		{
			if (m_tipusFitxa == TIPUS_NORMAL)
				return 'O';
			else
				return 'D';
		}
		else if (m_colorFitxa == COLOR_NEGRE)
		{
			if (m_tipusFitxa == TIPUS_NORMAL)
				return 'X';
			else
				return 'R';
		}
		else
			return '_';
	else
		return '_';
}

bool Fitxa::isContraria(const char& c) const
{
	if (m_colorFitxa == COLOR_BLANC)
	{
		if (c == 'X' || c == 'R')
			return true;
	}
	else if (m_colorFitxa == COLOR_NEGRE)
	{
		if (c == 'O' || c == 'D')
			return true;
	}
	return false;
}

void Fitxa::setMoviment(const string& posInicial, const string& posFinal)
{
	if (m_nMoviments < MAX_FITXES_JUGADOR)
	{
		m_moviments[m_nMoviments].setPosInicial(posInicial);
		m_moviments[m_nMoviments].setPosFinal(posFinal);
		m_nMoviments++;
	}
}

void Fitxa::setMoviment(const string& posInicial, const string& posFinal, const string& morta)
{
	if (m_nMoviments < MAX_FITXES_JUGADOR)
	{
		m_moviments[m_nMoviments].setPosInicial(posInicial);
		m_moviments[m_nMoviments].setPosFinal(posFinal);
		m_moviments[m_nMoviments].afageixMorta(morta);
		m_nMoviments++;
	}
}

void Fitxa::setMoviment(const string& posInicial, const string& posFinal, const string mortes[MAX_FITXES_JUGADOR], const int& n)
{
	if (m_nMoviments < MAX_FITXES_JUGADOR)
	{
		m_moviments[m_nMoviments].setPosInicial(posInicial);
		m_moviments[m_nMoviments].setPosFinal(posFinal);
		for (int i = 0; i < n; i++)
			m_moviments[m_nMoviments].afageixMorta(mortes[i]);
		m_nMoviments++;
	}
}

void Fitxa::resetMoviments(void)
{
	for (int i = 0; i < MAX_FITXES_JUGADOR; i++)
	{
		m_moviments[i].reset();
	}
	m_nMoviments = 0;
}

void Fitxa::getMovimentsValids(Moviment moviments[MAX_FITXES_JUGADOR], int& nMovimentsr)
{
	for (int i = 0; i < m_nMoviments; i++)
	{
		moviments[i] = m_moviments[i];
	}
	nMovimentsr = m_nMoviments;
}

bool Fitxa::cercaMovPerUPos(const string& pos, Moviment& mov) const
{
	int i = 0;
	bool found = 0;
	while (i < MAX_FITXES_JUGADOR && !found)
	{
		if (m_moviments[i].getPosFinal() == pos)
		{
			found = 1;
			mov = m_moviments[i];
		}
		i++;
	}
	return found;
}

int Fitxa::getMillorN(void)
{
	int aux = 0;
	for (int i = 0; i < m_nMoviments; i++)
		if (m_moviments[i].getNMortes() > aux)
			aux = m_moviments[i].getNMortes();
	return aux;
}