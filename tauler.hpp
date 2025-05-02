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
	string toString() const;

private:
	//moviments normals pel tauler sense captura
	void movimentEstret(const Posicio& pos) const;
	//moviments normals pel tauler amb captura
	void movimentAmpli(const Posicio& pos, Fitxa* fitxa) const;

	Posicio cercaPosicio(const string& pos);

	Posicio m_tauler[N_FILES][N_COLUMNES];
};


#endif 