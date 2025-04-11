#include "header.h"
#include "posicio.h"
#include "tauler.h"
#include "fitxa.h"

class Moviment
{
public:
	Moviment();
	//-------------------Setters-------------------//
	void setPosInicial(const Posicio& posicio) { m_posInicial = posicio; }
	void setPosFinal(const Posicio& posicio) { m_posFinal = posicio; }

	//-------------------Getters-------------------//
	bool isInit(const Moviment& move) const;
	Posicio getPosFinal(void) const { return m_posFinal; }

	//-------------------Others-------------------//
	void determinaPosPosibles(const Tauler& tauler, const Posicio& pos);
private:
	Fitxa m_mortes[MAX_FITXES_JUGADOR];
	Posicio m_posInicial;
	Posicio m_posFinal;
};