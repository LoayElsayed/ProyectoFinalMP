#ifndef TAULER_H
#define TAULER_H

#include "header.h"
#include "posicio.hpp"

string intToPos(const int& f, const int& c);
void posToInt(const string& posicio, int& f, int& c);

class Tauler
{
public:
	Tauler() {};
	void inicialitza(const string& nomFitxer);
	void inicialitza(void);
	void actualitzaMovimentsValids();
	void getPosicionsPossibles(const Posicio& origen,
		int& nPosicions, Posicio posicionsPossibles[]) const;
	bool mouFitxa(const Posicio& origen, const Posicio& desti);
	bool isInit(void) const;
	string toString() const;
	void matarFitxes(string mortes[], const int nMortes);
	bool comprovarMillorMoviment(Fitxa* fitxa, int& f, int& c);
	void clearMovs(void);
	bool isWin(void) const;
	int getNFitxesNegres(void) const;
	int getNFitxesBlancas(void) const;
	int getNMovNegres(void) const;
	int getNMovBlancas(void) const;

	Posicio getPos(int x, int y) const { return m_tauler[x][y]; }

private:
	//moviments normals pel tauler sense captura
	bool movimentEstret(const Posicio& pos) const;
	//moviments normals pel tauler amb captura
	bool movimentAmpli(const Posicio& pos, Fitxa* fitxa, string mortes[MAX_FITXES_JUGADOR], int& nMortes, const Posicio & final) const;
	//moviments de dama en diagonal pel tauler
	void movimentDama(const Posicio& pos, Fitxa* fitxa) const;

	void concatenarMoviments(const Posicio& pos, Fitxa* fitxa) const;

	Posicio cercaPosicio(const string& pos) const;


	Posicio m_tauler[N_FILES][N_COLUMNES];
};


#endif 