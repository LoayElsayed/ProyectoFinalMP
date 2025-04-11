#include "header.h"
#include "posicio.h"

using namespace std;

typedef enum
{
	TIPUS_NORMAL,
	TIPUS_DAMA,
	TIPUS_EMPTY
} TipusFitxa;

typedef enum
{
	COLOR_NEGRE,
	COLOR_BLANC
} ColorFitxa;

class Posicio
{
public:
	Posicio() : m_fila(-1), m_columna(-1) {};
	Posicio(const string& posicio);
	bool operator==(const Posicio& posicio) const;
	void fromString(const string& posicio);
	string toString();
	int getFila() { return m_fila; }
	int getColumna() { return m_columna; }
	void inicialitzaPosicio(int fila, int columna) { m_fila = fila, m_columna = columna; }
private:
	int m_fila;
	int m_columna;
};

ifstream& operator>>(ifstream& fitxer, Posicio& posicio);