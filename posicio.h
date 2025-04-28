#include "header.h"
#include "fitxa.h"

class Posicio
{
public:
	Posicio() :m_posicio("") {};
	Posicio(const string& posicio) : m_posicio(posicio) {};

	int getColumna(void) const { return int(m_posicio[0] - 'a'); }
	int getFila(void) const { return int(m_posicio[1] - '1'); }

	void setPosicio(const string& pos) { m_posicio = pos; }

	void posToInt(const string& posicio, int& f, int& c);
	string intToPos(int& f, int& c);

	bool operator==(const Posicio& posicio) const;

private:
	string m_posicio;
	Fitxa* m_fitxa;
};

ifstream& operator>>(ifstream& fitxer, Posicio& posicio);