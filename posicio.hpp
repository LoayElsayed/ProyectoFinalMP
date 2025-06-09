#ifndef POSICIO_H
#define POSICIO_H

#include "header.h"
#include "fitxa.h"

class Posicio
{
public:
	Posicio() :m_posicio(""), m_fitxa(nullptr) {};
	Posicio(const string& posicio) : m_posicio(posicio), m_fitxa(nullptr) {};

	//-------------------Getters-------------------//
	int getColumna(void) const { return int(m_posicio[0] - 'a'); }
	int getFila(void) const { return int(m_posicio[1] - '1'); }
	char getTFitxa(void) const;
	Fitxa* getFitxa(void) const { return m_fitxa; }
	string getPosicio(void) const { return m_posicio; }

	bool teFitxa(void) const { return m_fitxa != nullptr; }

	//-------------------Conversors-------------------//
	void posToInt(const string& posicio, int& f, int& c);

	//-------------------Setters-------------------//
	void setPosicio(const string& pos) { m_posicio = pos; }
	void setFitxa(const char& tipus);
	void setFitxa(Fitxa* tipus) { m_fitxa = tipus; }
	void eliminaFitxa();

	//-------------------Others-------------------//
	bool operator==(const Posicio& posicio) const;

private:
	string m_posicio;
	Fitxa* m_fitxa;
};

ifstream& operator>>(ifstream& fitxer, Posicio& posicio);
ostream& operator<<(ostream& out, const Posicio& pos);


#endif 