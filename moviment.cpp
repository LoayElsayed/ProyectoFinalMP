#include "moviment.h"

void Moviment::afageixMorta(const string& morta)
{
	m_mortes[m_nMortes];
	m_nMortes++;
}

void Moviment::getMortes(string mortes[MAX_FITXES_JUGADOR]) const
{
	for (int i = 0; i < m_nMortes; i++)
		mortes[i] = m_mortes[i];
}