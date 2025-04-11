#include "posicio.h"

Posicio::Posicio(const string& posicio)
{
	m_fila = (N_FILES - 1) - (posicio[1] - '1');
	m_columna = posicio[0] - 'a';
}

void Posicio::fromString(const string& posicio)
{
	m_fila = (N_FILES - 1) - (posicio[1] - '1');
	m_columna = posicio[0] - 'a';
}

string Posicio::toString()
{
	string pos = "a1";
	pos[0] = 'a' + m_columna;
	pos[1] = '1' + (N_FILES - 1) - m_fila;
	return pos;
}

bool Posicio::operator==(const Posicio& posicio) const
{
	return (m_fila == posicio.m_fila && m_columna == posicio.m_columna);
}

ifstream& operator>>(ifstream& fitxer, Posicio& posicio)
{
	string pos;
	fitxer >> pos;
	posicio.fromString(pos);
	return fitxer;
}