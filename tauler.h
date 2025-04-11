#include "header.h"
#include "posicio.h"
#include "fitxa.h"

const int MAX_FITXES_JUGADOR = 12;

const int N_FILES = 8;
const int N_COLUMNES = 8;

class Tauler
{
public:
	Tauler();
	void inicialitza(const string& nomFitxer);
	void actualitzaMovimentsValids();
	bool mouFitxa(const Posicio& origen, const Posicio& desti);
	void getPosicionsPossibles(const Posicio& origen,
		int& nPosicions, Posicio posicionsPossibles[]);
	string toString() const;
private:
	istream pp;
	Fitxa m_tauler[N_FILES][N_COLUMNES];
};

	