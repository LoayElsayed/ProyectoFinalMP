#include "header.h"
#include "moviment.h"

typedef enum
{
	TIPUS_NORMAL,
	TIPUS_DAMA,
	TIPUS_EMPTY
} TipusFitxa;

typedef enum
{
	COLOR_NEGRE,
	COLOR_BLANC,
	COLOR_NUL
} ColorFitxa;

class Fitxa
{
public:
	Fitxa() : m_tipusFitxa(TIPUS_EMPTY), m_colorFitxa(COLOR_NUL), m_nMoviments(0) {};

	//-------------------Setters-------------------//
	void setTipus(const char& tipus);
	void setMoviment(const string& posInicial, const string& posFinal);
	void setMoviment(const string& posInicial, const string& posFinal, string m_morta);
	void resetMoviments(void);

	//-------------------Getters-------------------//
	int getColor(void) const { return m_colorFitxa; }
	int getTipus(void) const { return m_tipusFitxa; }

	char getTipusString(void) const;

	Moviment getMoviment(int i) const { return m_moviments[i]; }
	int getNMoviments(void) const { return m_nMoviments; }
	Moviment getUltimMoviment(void) const { return m_moviments[m_nMoviments - 1]; }

	bool isContraria(const char& c) const;

private:
	//damos por hecho que solo podra hacer tantos movimientos como fitxas haya
	Moviment m_moviments[MAX_FITXES_JUGADOR];
	int m_nMoviments;
	TipusFitxa m_tipusFitxa;
	ColorFitxa m_colorFitxa;
};
