#ifndef TAULER_H
#define TAULER_H

#include "header.h"
#include "posicio.hpp"


class Tauler
{
public:
	Tauler() {};
	void inicialitza(const string& nomFitxer);
	void actualitzaMovimentsValids();
	void getPosicionsPossibles(const Posicio& origen,
		int& nPosicions, Posicio posicionsPossibles[]);
	bool mouFitxa(const Posicio& origen, const Posicio& desti);
	bool isInit(void) const;
	string toString() const;

private:
	//moviments normals pel tauler sense captura
	bool movimentEstret(const Posicio& pos) const;
	//moviments normals pel tauler amb captura
	bool movimentAmpli(const Posicio& pos, Fitxa* fitxa, string mortes[MAX_FITXES_JUGADOR], int& nMortes, const Posicio& final) const;
	//moviments de dama en diagonal pel tauler
	void movimentDama(const Posicio& pos, Fitxa* fitxa) const;

	void concatenarMoviments(const Posicio& pos, Fitxa* fitxa) const;

	Posicio cercaPosicio(const string& pos) const;

	string intToPos(int& f, int& c) const;

	Posicio m_tauler[N_FILES][N_COLUMNES];
};


#endif 