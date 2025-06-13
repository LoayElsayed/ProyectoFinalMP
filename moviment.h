#include "header.h"

class Moviment
{
public:
	Moviment() : m_nMortes(0), m_posInicial(""), m_posFinal("") {
		for (int i = 0; i < MAX_FITXES_JUGADOR; i++)
			m_mortes[i] = "";
	};
	Moviment(const string& posInicial) : m_posInicial(posInicial), m_nMortes(0), m_posFinal("") {
		for (int i = 0; i < MAX_FITXES_JUGADOR; i++)
			m_mortes[i] = "";
	};

	//-------------------Setters-------------------//
	void setPosInicial(const string& posicio) { m_posInicial = posicio; }
	void setPosFinal(const string& posicio) { m_posFinal = posicio; }
	void afageixMorta(const string& morta);
	void reset(void);

	//-------------------Getters-------------------//
	string getPosInicial(void) const { return m_posInicial; }
	string getPosFinal(void) const { return m_posFinal; }
	void getMortes(string mortes[MAX_FITXES_JUGADOR], int& nMortes) const;
	string getUtlimaMorta(void) const { return m_mortes[m_nMortes - 1]; }
	int getNMortes(void) const { return m_nMortes; }

	//-------------------Others-------------------//
	

private:
	//la posicion de las fitxas muertas
	string m_mortes[MAX_FITXES_JUGADOR];
	int m_nMortes;
	//la posicion donde empieza
	string m_posInicial;
	//la posicion donde acaba
	string m_posFinal;
};	