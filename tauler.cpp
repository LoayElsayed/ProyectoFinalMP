#include "tauler.hpp"

void Tauler::inicialitza(const string& nomFitxer)
{
	ifstream fitxer(nomFitxer);
	int i = 0;
	int j = 0;
	if (fitxer.is_open())
	{
		while (!fitxer.eof())
		{
			Posicio aux;
			char tipusFitxa;
			fitxer >> tipusFitxa;
			fitxer >> aux;
			m_tauler[aux.getFila()][aux.getColumna()].setPosicio(aux.getPosicio());
			m_tauler[aux.getFila()][aux.getColumna()].setFitxa(tipusFitxa);
		}
	}
	fitxer.close();
}

Posicio Tauler::cercaPosicio(const string& pos) const
{
	Posicio aux;
	aux.setPosicio(pos);
	int x = aux.getColumna();
	int y = aux.getFila();
	if (m_tauler[y][x].teFitxa())
		return m_tauler[y][x];
	else
	{
		return aux;
	}	
}

void Tauler::concatenarMoviments(const Posicio& posicio, Fitxa* fitxa) const
{
	int nMoviments = fitxa->getNMoviments();
	movimentAmpli(posicio, fitxa);
	while (fitxa->getNMoviments() > nMoviments)
	{
		nMoviments = fitxa->getNMoviments();
		Moviment moviment = fitxa->getUltimMoviment();
		Posicio pos = cercaPosicio(moviment.getPosFinal());
		movimentAmpli(pos, fitxa);
	}
}


void Tauler::actualitzaMovimentsValids()
{
	for (int f = 0; f < N_FILES; f++)
	{
		for (int c = 0; c < N_COLUMNES; c++)
		{
			if (m_tauler[f][c].getTFitxa() != '-')
			{
				Fitxa* fitxa = m_tauler[f][c].getFitxa();
				if (fitxa != nullptr)
					if (fitxa->getTipus() == TIPUS_NORMAL)
					{
						movimentEstret(m_tauler[f][c]);

						//ahora miramos el movimiento amplio y controlamos si hay o no captura
						concatenarMoviments(m_tauler[f][c], fitxa);
					}
					else {
						//logica de la dama
						/*
						Hare una funcion que recorra el tablero diagonalmente hasta encontrar
						una casilla con fitxa ya sea amiga o enemiga, luego buscara un
						movimiento ancho a partir de esa posicion, evidentemente debe buscar en las 
						4 direcciones diagonales
						*/
						movimentDama(m_tauler[f][c], fitxa);
						concatenarMoviments(m_tauler[f][c], fitxa);
					}
			}
		}
	}
}

void Tauler::getPosicionsPossibles(const Posicio& origen,
	int& nPosicions, Posicio posicionsPossibles[])
{
	const Posicio& pos = cercaPosicio(origen.getPosicio());
	if (pos.teFitxa())
	{
		Fitxa* fitxa = pos.getFitxa();

		nPosicions = fitxa->getNMoviments();

		for (int i = 0; i < nPosicions; i++)
		{
			const Moviment& mov = fitxa->getMoviment(i);
			posicionsPossibles[i].setPosicio(mov.getPosFinal());
		}
	}
}

bool Tauler::mouFitxa(const Posicio& origen, const Posicio& desti)
{
	bool posible = true;
	int i = 0;
	bool trobat = false;
	// Comprovar si hi ha fitxa a la posicio d'origen
	if (!m_tauler[origen.getFila()][origen.getColumna()].teFitxa()) {
		return false;
	}
	Fitxa* aux = m_tauler[origen.getFila()][origen.getColumna()].getFitxa();
	Moviment movimentsValids[MAX_FITXES_JUGADOR];
	int nMovimentsValids = 0;
	aux->getMovimentsValids(movimentsValids, nMovimentsValids);

	while (i < MAX_FITXES_JUGADOR && posible)
	{
		if (aux->getMoviment(i).getPosFinal() != desti.getPosicio())
			posible = false;
		i++;
	}
	if (posible)
	{
		if (aux->getUltimMoviment().getPosInicial() == origen.getPosicio() &&
			aux->getUltimMoviment().getPosFinal() == desti.getPosicio())
		{
			m_tauler[desti.getFila()][desti.getColumna()].setFitxa(aux);
			m_tauler[origen.getFila()][origen.getColumna()].eliminaFitxa();

			if ((aux->getColor() == COLOR_BLANC && desti.getFila() == 0) ||
				(aux->getColor() == COLOR_NEGRE && desti.getFila() == N_FILES - 1))
			{
				m_tauler[desti.getFila()][desti.getColumna()].getFitxa()->setTipus(TIPUS_DAMA);
			}
		}
		else
		{
			m_tauler[origen.getFila()][origen.getColumna()].eliminaFitxa();
		}

	}
	actualitzaMovimentsValids();

	return posible;
}

string Tauler::toString() const
{
	string output;
	string posicions[8] = { "1", "2", "3", "4", "5", "6", "7", "8" };
	for (int i = N_FILES - 1; i >= 0; i--)
	{
		output += posicions[i];
		output += ":";

		for (int j = 0; j < N_COLUMNES; j++)
		{
			output += " ";
			output += m_tauler[i][j].getFitxa()->getTipusString();
		}
		output += "\n";

	}

	output += "   a b c d e f g h\n";
	return output;
}

//LOGICA DE MOVIMENTS

string Tauler::intToPos(int& f, int& c) const
{
	string pos = "";
	pos += c + 'a';
	pos += f + '1';
	return pos;
}

bool xLimit(int x)
{
	return (x >= 0 && x < N_COLUMNES);
}

bool yLimit(int y)
{
	return (y >= 0 && y < N_FILES);
}

void Tauler::movimentEstret(const Posicio& pos) const
{
	int x = pos.getColumna();
	int y = pos.getFila();

	Fitxa* fitxa = pos.getFitxa();

	int ex[2] = { -1, 1 };
	int ey[2] = { 1, 1 };

	if (fitxa->getColor() == COLOR_NEGRE)
	{
		ey[0] = -1; ey[1] = -1;
	}

	for (int i = 0; i < 2; ++i)
	{
		int mex = x + ex[i]; //moviment estret x
		int mey = y + ey[i]; //moviment estret y

		if (xLimit(mex) && yLimit(mey))
		{
			if (!m_tauler[mey][mex].teFitxa())
			{
				fitxa->setMoviment(pos.getPosicio(), intToPos(mey, mex));
			}
		}
	}
}

void Tauler::movimentAmpli(const Posicio& pos, Fitxa* fitxa) const
{
	int x = pos.getColumna();
	int y = pos.getFila();

	string ultimaMorta = "";

	if (fitxa->getNMoviments() > 0)
		if(fitxa->getUltimMoviment().getNMortes() > 0)
			ultimaMorta = fitxa->getUltimMoviment().getUtlimaMorta();

	int ax[] = { -2, 2, -2, 2 }; // ampli x
	int ay[] = { 2, 2, -2, -2 }; // ampli y
	int ex[] = { -1, 1, -1, 1 }; // estret x
	int ey[] = { 1, 1, -1, -1 }; // estret y

	int N = 4; // nombre de moviments possibles

	if (fitxa->getTipus() == TIPUS_NORMAL)
	{
		if (fitxa->getColor() == COLOR_NEGRE)
		{
			ey[0] = -1; ey[1] = -1;
			ay[0] = -2; ay[1] = -2;
		}
		N = 2; // només es poden fer moviments en la mateixa direcció
	}
	
	//aqui guardem les fitxes mortes acomulativament
	string mortes[MAX_FITXES_JUGADOR];
	int nMortes = 0;

	for (int i = 0; i < N; ++i)
	{
		int max = x + ax[i]; //moviment ampli x
		int may = y + ay[i]; //moviment ampli y
		int mex = x + ex[i]; //moviment estret x
		int mey = y + ey[i]; //moviment estret y

		if (xLimit(max) && yLimit(may))
		{
			//les posicions x y estan invertides per la forma en la que está estructurada la taula
			
			//comprovamos que la fitxa que intentaremos matar no haya sido la ultima muerta
			if(ultimaMorta != m_tauler[mey][mex].getPosicio())
				//miramos si la fitxa en la direccion que miramos sea contraria
				if (fitxa->isContraria(m_tauler[mey][mex].getTFitxa()))
				{
					//comprovamos que la posicion siguiente esta vacia
					if (!m_tauler[may][max].teFitxa())
					{
						mortes[nMortes] = m_tauler[mey][mex].getPosicio();
						nMortes++;
						fitxa->setMoviment(pos.getPosicio(), intToPos(may, max), mortes, nMortes);
					}
				}
		}
	}
}

void Tauler::movimentDama(const Posicio& pos, Fitxa* fitxa) const
{
	int x = pos.getColumna();
	int y = pos.getFila();

	int px[] = { -1, 1, -1, 1 }; // movimiento x
	int py[] = { -1, -1, 1, 1 }; // movimiento y

	int i = 1;
	for (int j = 0; j < 4; j++)
	{
		int mx = x + px[j]; //moviment x
		int my = y + py[j]; //moviment y
		bool found = false; //si s'ha trobat una fitxa
		while (xLimit(mx) &&  yLimit(my) && !found)
		{
			mx = x + px[j] * i; //moviment x
			my = y + py[j] * i; //moviment y

			if (!m_tauler[my][mx].teFitxa())
			{
				Posicio aux;
				aux.setPosicio(intToPos(my, mx));
				fitxa->setMoviment(pos.getPosicio(), intToPos(my, mx));
			}
			else
				found = true; //s'ha trobat una fitxa i es deixa de buscar en la direcció
			i++;
		}
		i = 1;
	}
}