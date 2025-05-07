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
			m_tauler[aux.getFila()][aux.getColumna()].setFitxa(tipusFitxa);
		}
	}
	fitxer.close();
}

Posicio Tauler::cercaPosicio(const string& pos)
{
	int f = 0;
	bool found = false;
	Posicio output;
	while (f < N_FILES && !found) {
		int c = 0;
		while (c < N_COLUMNES && !found) {
			if (m_tauler[f][c].getPosicio() == pos) {
				output = m_tauler[f][c];
			}
			c++;
		}
		f++;
	}
	return output;
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
				if (fitxa->getTipus() == TIPUS_NORMAL)
				{
					movimentEstret(m_tauler[f][c]);

					//ahora miramos el movimiento amplio y controlamos si hay o no captura
					int nMoviments = fitxa->getNMoviments();
					movimentAmpli(m_tauler[f][c], fitxa);
					while (fitxa->getNMoviments() > nMoviments)
					{
						nMoviments = fitxa->getNMoviments();
						Moviment moviment = fitxa->getUltimMoviment();
						Posicio pos = cercaPosicio(moviment.getPosFinal());
						movimentAmpli(pos, fitxa);
					}
				}
				else {
					//logica de la dama
				}
			}
		}
	}
}

void Tauler::getPosicionsPossibles(const Posicio& origen,
	int& nPosicions, Posicio posicionsPossibles[])
{
	if (origen.teFitxa())
	{
		Fitxa* fitxa = origen.getFitxa();

		if (fitxa != nullptr)
		{
			nPosicions = fitxa->getNMoviments();

			for (int i = 0; i < nPosicions; i++)
			{
				const Moviment& mov = fitxa->getMoviment(i);
				posicionsPossibles[i].setPosicio(mov.getPosFinal());
			}
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
	string posicions[8] = { "8", "7", "6", "5", "4", "3", "2", "1" };
	for (int i = 0; i < N_FILES; i++)
	{
		output += posicions[i];
		output += ":";

		for (int j = 0; j < N_COLUMNES; j++)
		{
			output += m_tauler[i][j].getFitxa()->getTipusString();
		}
		output += "\n";

	}

	output += "  ABCDEFGH\n";
	return output;
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

	int ex[] = {-1, 1, 0};
	int ey[] = {1, 1, 1 };

	for (int i = 0; i < 3; ++i)
	{
		int mex = x + ex[i]; //moviment estret x
		int mey = y + ey[i]; //moviment estret y

		if (xLimit(mex) && yLimit(mey))
		{
			if (m_tauler[mex][mey].getTFitxa() == '-')
			{
				fitxa->setMoviment(pos.getPosicio(), m_tauler[mex][mey].getPosicio());
			}
		}
	}
}

void Tauler::movimentAmpli(const Posicio& pos, Fitxa* fitxa) const
{
	int x = pos.getColumna();
	int y = pos.getFila();

	int ax[] = { -2, 2 }; // ampli x
	int ay[] = { 2, 2 }; // ampli y
	int ex[] = { -1, 1 }; // estret x
	int ey[] = { 1, 1 }; // estret y

	for (int i = 0; i < 2; ++i)
	{
		int max = x + ax[i]; //moviment ampli x
		int may = y + ay[i]; //moviment ampli y
		int mex = x + ex[i]; //moviment estret x
		int mey = y + ey[i]; //moviment estret y

		string mortes[MAX_FITXES_JUGADOR];
		int nMortes = 0;

		if (xLimit(max) && yLimit(may))
		{
			if (fitxa->isContraria(m_tauler[mex][mey].getTFitxa()))
			{
				if (m_tauler[max][may].getTFitxa() == '-')
				{
					mortes[nMortes] = m_tauler[mex][mey].getPosicio();
					nMortes++;
					fitxa->setMoviment(pos.getPosicio(), m_tauler[max][may].getPosicio(), mortes, nMortes);
				}
			}
		}
	}
}

void Tauler::movimentsDama(const Posicio& pos) const
{
	if(pos.teFitxa())
		if (pos.getFitxa()->getTipus() == TIPUS_DAMA)
		{
			string mortes[MAX_FITXES_JUGADOR];
			int nMortes = 0;

			Fitxa* dama = pos.getFitxa();

			int x = pos.getColumna();
			int y = pos.getFila();

			int ax[] = { -2, 2, -2, 2, 0, 0, -2, 2 }; // ampli x
			int ay[] = { 2, 2, -2, -2, 2, -2, 0, 0 }; // ampli y
			int ex[] = { -1, 1, -1, 1, 0, 0, -1, 1 }; // estret x
			int ey[] = { 1, 1, -1, -1, 1, -1, 0, 0 }; // estret y

			for (int i = 0; i < 8; i++)
			{
				int max = x + ax[i]; //moviment ampli x
				int may = y + ay[i]; //moviment ampli y
				int mex = x + ex[i]; //moviment estret x
				int mey = y + ey[i]; //moviment estret y


			}
		}
}