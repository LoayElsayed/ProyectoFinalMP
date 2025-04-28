#include "tauler.h"

void Tauler::inicialitza(const string& nomFitxer)
{
	ifstream fitxer(nomFitxer);
	int i = 0;
	int j = 0;
	if (fitxer.is_open())
	{
		while (!fitxer.eof())
		{
			Posicio aux;
			char tipusFitxa;
			fitxer >> tipusFitxa;
			fitxer >> aux;
			m_tauler[aux.getFila()][aux.getColumna()].setTipus(tipusFitxa);
		}
	}
	fitxer.close();
}

void Tauler::actualitzaMovimentsValids()
{

}

void Tauler::getPosicionsPossibles(const Posicio& origen,
	int& nPosicions, Posicio posicionsPossibles[])
{

}

bool Tauler::mouFitxa(const Posicio& origen, const Posicio& desti)
{
	return false;
}

string Tauler::toString() const
{
	return "";
}