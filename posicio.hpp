#ifndef POSICIO_H
#define POSICIO_H

#include "header.h"
#include "fitxa.h"

class Posicio
{
public:
	Posicio() :m_posicio(""), m_fitxa(nullptr), m_tefitxa(false) {};
	Posicio(const string& posicio) : m_posicio(posicio), m_fitxa(nullptr) {};

	//-------------------Getters-------------------//
	int getColumna(void) const { return int(m_posicio[0] - 'a'); }
	int getFila(void) const { return int(m_posicio[1] - '1'); }
	char getTFitxa(void) const;
	Fitxa* getFitxa(void) const { return m_fitxa; }
	string getPosicio(void) const { return m_posicio; }

	bool teFitxa(void) const { return m_tefitxa; }

	//-------------------Conversors-------------------//
	void posToInt(const string& posicio, int& f, int& c);
	string intToPos(int& f, int& c);

	//-------------------Setters-------------------//
	void setPosicio(const string& pos) { m_posicio = pos; }
	void setFitxa(const char& tipus);
	void setFitxa(Fitxa* tipus) { m_fitxa = tipus; }
	void eliminaFitxa();

	//-------------------Others-------------------//
	bool operator==(const Posicio& posicio) const;

private:
	bool m_tefitxa;
	string m_posicio;
	Fitxa* m_fitxa;
};

ifstream& operator>>(ifstream& fitxer, Posicio& posicio);

#endif 