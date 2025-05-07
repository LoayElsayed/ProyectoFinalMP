#include "posicio.hpp"

bool Posicio::operator==(const Posicio& posicio) const
{
	return (m_posicio == posicio.m_posicio);
}

ifstream& operator>>(ifstream& fitxer, Posicio& posicio)
{
	string pos;
	fitxer >> pos;
	posicio.setPosicio(pos);
	return fitxer;
}

void Posicio::posToInt(const string& posicio, int& f, int& c)
{
	f = (N_FILES - 1) - (posicio[1] - '1');
	c = posicio[0] - 'a';
}

string Posicio::intToPos(int& f, int& c)
{
	string pos = "";
	pos += c + 'a';
	pos += (N_FILES - 1) - f + '1';
	return pos;
}

void Posicio::setFitxa(const char& tipus)
{
	m_fitxa = new Fitxa();
	m_fitxa->setTipus(tipus);
	m_tefitxa = true;
}

char Posicio::getTFitxa(void) const
{
	if (m_fitxa != nullptr)
		return m_fitxa->getTipusString();
	else
		return '_';
}

void Posicio::eliminaFitxa()
{
	m_tefitxa = false;
	m_fitxa->setTipus(TIPUS_EMPTY);
}