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

ostream& operator<<(ostream& out, const Posicio& pos)
{
	out << pos.getPosicio();
	return out;
}

void Posicio::posToInt(const string& posicio, int& f, int& c)
{
	f = (N_FILES - 1) - (posicio[1] - '1');
	c = posicio[0] - 'a';
}

void Posicio::setFitxa(const char& tipus)
{
	m_fitxa = new Fitxa();
	m_fitxa->setTipus(tipus);
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
	m_fitxa = nullptr;
}