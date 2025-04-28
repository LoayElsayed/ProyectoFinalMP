#include "header.h"

class Moviment
{
public:
	Moviment() : m_nMortes(0), m_posInicial(""), m_posFinal("") {};
	Moviment(const string& posInicial) : m_posInicial(posInicial), m_nMortes(0), m_posFinal("") {};

	//-------------------Setters-------------------//
	void setPosInicial(const string& posicio) { m_posInicial = posicio; }
	void setPosFinal(const string& posicio) { m_posFinal = posicio; }
	void afageixMorta(const string& morta);

	//-------------------Getters-------------------//
	string getPosInicial(void) const { return m_posInicial; }
	string getPosFinal(void) const { return m_posFinal; }
	void getMortes(string mortes[MAX_FITXES_JUGADOR]) const;

private:
	//la posicion de las fitxas muertas
	string m_mortes[MAX_FITXES_JUGADOR];
	int m_nMortes;
	//la posicion donde empieza
	string m_posInicial;
	//la posicion donde acaba
	string m_posFinal;
};