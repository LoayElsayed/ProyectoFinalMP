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

void Tauler::inicialitza(void)
{
	const int N = 24;
	const string pos[N] = { "a1", "c1", "e1", "g1", "b2", "d2", "f2", "h2", "a3", "c3", "e3", "g3",//white
	"b8", "d8", "f8", "h8", "a7", "c7", "e7", "g7", "b6", "d6", "f6", "h6"};//black

	for (int i = 0; i < N; i++)
	{
		Posicio aux(pos[i]);
		char tipusFitxa = 'O';
		if (i >= N / 2)
			tipusFitxa = 'X';
		m_tauler[aux.getFila()][aux.getColumna()].setPosicio(aux.getPosicio());
		m_tauler[aux.getFila()][aux.getColumna()].setFitxa(tipusFitxa);
	}
}

bool Tauler::isInit(void) const
{
	bool found = 0;
	int x = 0;
	while (x < N_COLUMNES && !found)
	{
		int y = 0; 
		while (y < N_FILES && !found)
		{
			if (m_tauler[y][x].teFitxa())
				found = 1;
			y++;
		}
		x++;
	}
	return found;
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
		return aux;
}

void Tauler::clearMovs(void)
{
	if (this->isInit())
		for (int f = 0; f < N_FILES; f++)
		{
			for (int c = 0; c < N_COLUMNES; c++)
			{
				Posicio& pos = m_tauler[f][c];
				if (pos.teFitxa())
				{
					Fitxa* fitxa = pos.getFitxa();
					fitxa->resetMoviments();
				}
			}
		}
}

void Tauler::actualitzaMovimentsValids()
{
	clearMovs();
	if(this->isInit())
		for (int f = 0; f < N_FILES; f++)
		{
			for (int c = 0; c < N_COLUMNES; c++)
			{
				if (m_tauler[f][c].teFitxa())
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
							movimentDama(m_tauler[f][c], fitxa);
						}
				}
			}
		}
}

void Tauler::getPosicionsPossibles(const Posicio& origen,
	int& nPosicions, Posicio posicionsPossibles[]) const
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
	bool posible = false;
	int i = 0;
	int nMortes = 0;
	string mortes[MAX_FITXES_JUGADOR];
	
	Posicio& posFitxa = m_tauler[origen.getFila()][origen.getColumna()];
	Posicio & final = m_tauler[desti.getFila()][desti.getColumna()];

	if (!posFitxa.teFitxa()) {
		return false;
	}
	Fitxa* aux = posFitxa.getFitxa();
	Moviment movimentsValids[MAX_FITXES_JUGADOR];
	int nMovimentsValids = 0;
	aux->getMovimentsValids(movimentsValids, nMovimentsValids);


	while (i < nMovimentsValids && !posible)
	{
		if (movimentsValids[i].getPosFinal() == desti.getPosicio())
			posible = true;
		else
			i++;
	}
	if (posible)
	{
		int f, c;
		if (!comprovarMillorMoviment(aux, f, c))
		{
			m_tauler[f][c].eliminaFitxa();

			final.setFitxa(aux);
			string posaux = desti.getPosicio();
			final.setPosicio(posaux);

			posFitxa.eliminaFitxa();
		}
		else
		{
			if (aux->getMillorN() == movimentsValids[i].getNMortes())
			{
				final.setFitxa(aux);
				string posaux = desti.getPosicio();
				final.setPosicio(posaux);

				movimentsValids[i].getMortes(mortes, nMortes);
				matarFitxes(mortes, nMortes);

				posFitxa.eliminaFitxa();

				if (aux->getColor() == COLOR_BLANC && desti.getFila() == 7)
					aux->setTipus('D');
				else if ((aux->getColor() == COLOR_NEGRE && desti.getFila() == 0))
					aux->setTipus('R');
			}
			else
			{
				posFitxa.eliminaFitxa();
				movimentsValids[i].getMortes(mortes, nMortes);
				matarFitxes(mortes, nMortes);
			}
		}

	}
	actualitzaMovimentsValids();
	return posible;
}
bool Tauler::comprovarMillorMoviment(Fitxa* fitxa, int& f, int& c)
{
	bool millorFitxa = true;
	Fitxa* aux = new Fitxa;
	for (int i = 0; i < N_FILES; i++)
	{
		for (int j = 0; j < N_COLUMNES; j++)
		{
			if (m_tauler[i][j].getFitxa() != nullptr)
			{
				if ((fitxa->getColor() == m_tauler[i][j].getFitxa()->getColor()) && (m_tauler[i][j].getFitxa()->getNMoviments() > 0))
				{
					if (fitxa->getUltimMoviment().getNMortes() >= m_tauler[i][j].getFitxa()->getUltimMoviment().getNMortes())
						millorFitxa = true;
					else
					{
						millorFitxa = false;
						f = i;
						c = j;
					}

				}
			}
		}
	}
	return millorFitxa;
}
void posToInt(const string& posicio, int& f, int& c)
{
	f = (posicio[1] - '1');
	c = posicio[0] - 'a';
}


void Tauler::matarFitxes(string mortes[], const int nMortes)
{
	int x; //no las inicializo a 0 pq como lo haga a lo mejor me cargo la ficha q esta en 0 0 y como q no
	int y;
	for (int i = 0; i < nMortes; i++)
	{
		posToInt(mortes[i], x, y);
		m_tauler[x][y].eliminaFitxa();
	}
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

string intToPos(const int& f, const int& c)
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

bool isInStrArr(const string arr[MAX_FITXES_JUGADOR], const string& str)
{
	int i = 0;
	bool found = 0;
	while (i < MAX_FITXES_JUGADOR && !found)
	{
		if (arr[i] == str)
			found = 1;
		i++;
	}
	return found;
}

void strArrCpy(string origen[MAX_FITXES_JUGADOR], string destino[MAX_FITXES_JUGADOR])
{
	for (int i = 0; i < MAX_FITXES_JUGADOR; i++)
		destino[i] = origen[i];
}

void Tauler::concatenarMoviments(const Posicio& posicio, Fitxa* fitxa) const
{
	if (fitxa == nullptr)
		return;

	string mortes[MAX_FITXES_JUGADOR];
	int nMortes = 0;

	int nMov = fitxa->getNMoviments();

	if (fitxa->getTipus() == TIPUS_DAMA)
	{
		Moviment ultMov = fitxa->getUltimMoviment();
		ultMov.getMortes(mortes, nMortes);
		movimentAmpli(ultMov.getPosFinal(), fitxa, mortes, nMortes, posicio);
	}
	else
		movimentAmpli(posicio, fitxa, mortes, nMortes, posicio);

	while (nMov < fitxa->getNMoviments())
	{
		int nAntiga = nMov;
		nMov = fitxa->getNMoviments();

		for (int i = nAntiga; i < nMov; i++)
		{
			Moviment mov = fitxa->getMoviment(i);
			mov.getMortes(mortes, nMortes);
			Posicio inicial = mov.getPosInicial();
			Posicio posVirtual = mov.getPosFinal();
			movimentAmpli(posVirtual, fitxa, mortes, nMortes, inicial);
		}
	}
}

bool Tauler::movimentEstret(const Posicio& pos) const
{
	int x = pos.getColumna();
	int y = pos.getFila();

	Fitxa* fitxa = pos.getFitxa();
	bool possible = false;

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
				possible = true;
			}
		}
	}
	return possible;
}

bool Tauler::movimentAmpli(const Posicio& pos, Fitxa* fitxa, string mortes[MAX_FITXES_JUGADOR], int& nMortes, const Posicio& inicial) const
{
	int x = pos.getColumna();
	int y = pos.getFila();

	bool possible = false;

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

	for (int i = 0; i < N; ++i)
	{
		int max = x + ax[i]; //moviment ampli x
		int may = y + ay[i]; //moviment ampli y
		int mex = x + ex[i]; //moviment estret x
		int mey = y + ey[i]; //moviment estret y

		if (xLimit(max) && yLimit(may))
		{
			//les posicions x y estan invertides per la forma en la que está estructurada la taula
			Posicio fitxaTrobada = m_tauler[mey][mex];
			Posicio seguentPos = m_tauler[may][max];

			if (fitxa->isContraria(fitxaTrobada.getTFitxa()))
				if (!seguentPos.teFitxa())
					if (!isInStrArr(mortes, fitxaTrobada.getPosicio()))
					{
						seguentPos.setPosicio(intToPos(may, max));

						string arrAux[MAX_FITXES_JUGADOR];
						strArrCpy(mortes, arrAux);
						arrAux[nMortes] = fitxaTrobada.getPosicio();

						fitxa->setMoviment(inicial.getPosicio(), seguentPos.getPosicio(), arrAux, (nMortes + 1));
						possible = true;
					}
		}
	}
	return possible;
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
				fitxa->setMoviment(pos.getPosicio(), intToPos(my, mx));
			else
			{
				int max = x + px[j] * (i + 1); //moviment ampli x
				int may = y + py[j] * (i + 1); //moviment ampli y

				if (xLimit(max) && yLimit(may))
				{
					Posicio fitxaTrobada = m_tauler[my][mx];
					Posicio seguentPos = m_tauler[may][max];

					if (fitxa->isContraria(fitxaTrobada.getTFitxa()))
						if (!seguentPos.teFitxa())
						{
							seguentPos.setPosicio(intToPos(may, max));
							//forzamos el primer movimiento en esa direccion
							fitxa->setMoviment(pos.getPosicio(), seguentPos.getPosicio(), fitxaTrobada.getPosicio());
							//esta funcion detecta si es una dama
							//y adquiere como posicion inicial la pos 
							//inicial del ultimo movimiento que en este
							//caso como solo hay uno es el primero
							//y ya concatena teniendo en cuenta la primera muerte
							concatenarMoviments(pos, fitxa);
						}
				}
				found = true; //s'ha trobat una fitxa i es deixa de buscar en la direcció
			}
				
			i++;
		}
		i = 1;
	}
}

bool Tauler::isWin(void) const
{
	int white = getNFitxesBlancas();
	int black = getNFitxesNegres();

	if (black == 0 || white == 0)
		return true;
	else
		return false;
}

int Tauler::getNFitxesBlancas(void) const
{
	int white = 0;
	if (this->isInit())
		for (int f = 0; f < N_FILES; f++)
		{
			for (int c = 0; c < N_COLUMNES; c++)
			{
				const Posicio pos = m_tauler[f][c];
				if (pos.teFitxa())
				{
					const Fitxa* fitxa = pos.getFitxa();
					if (fitxa->getColor() == COLOR_BLANC)
						white++;
				}
			}
		}
	return white;
}

int Tauler::getNFitxesNegres(void) const
{
	int black = 0;
	if (this->isInit())
		for (int f = 0; f < N_FILES; f++)
		{
			for (int c = 0; c < N_COLUMNES; c++)
			{
				const Posicio pos = m_tauler[f][c];
				if (pos.teFitxa())
				{
					const Fitxa* fitxa = pos.getFitxa();
					if (fitxa->getColor() == COLOR_NEGRE)
						black++;
				}
			}
		}
	return black;
}

int Tauler::getNMovBlancas(void) const
{
	int nMov = 0;
	if (this->isInit())
		for (int f = 0; f < N_FILES; f++)
		{
			for (int c = 0; c < N_COLUMNES; c++)
			{
				const Posicio pos = m_tauler[f][c];
				if (pos.teFitxa())
				{
					const Fitxa* fitxa = pos.getFitxa();
					if (fitxa->getColor() == COLOR_BLANC)
						nMov += fitxa->getNMoviments();
				}
			}
		}
	return nMov;
}

int Tauler::getNMovNegres(void) const
{
	int nMov = 0;
	if (this->isInit())
		for (int f = 0; f < N_FILES; f++)
		{
			for (int c = 0; c < N_COLUMNES; c++)
			{
				const Posicio pos = m_tauler[f][c];
				if (pos.teFitxa())
				{
					const Fitxa* fitxa = pos.getFitxa();
					if (fitxa->getColor() == COLOR_NEGRE)
						nMov += fitxa->getNMoviments();
				}
			}
		}
	return nMov;
}