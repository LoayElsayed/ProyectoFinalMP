#include "posicio.h"

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