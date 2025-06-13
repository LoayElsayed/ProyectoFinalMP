//
//  CurrentGame.cpp
//  LearnChess
//
//  Created by Enric Vergara on 21/2/22.
//

#include "joc.hpp"
#include <iostream>
#include <fstream>
#include "GraphicManager.h"

ifstream movFile;

void Joc::inicialitza(void)
{
	m_tauler.inicialitza();
	m_tauler.actualitzaMovimentsValids();
	printTauler();
}

void Joc::inicialitza(ModeJoc mode, const string& nomFitxerTauler, const string& nomFitxerMoviments)
{
	ifstream tableFile(nomFitxerTauler);
	movFile.open(nomFitxerMoviments);
	m_movFileName = nomFitxerMoviments;

	if (tableFile.is_open())
		m_tauler.inicialitza(nomFitxerTauler);

	if (mode == MODE_JOC_REPLAY)
		m_modeRepl = true;
	else if (mode == MODE_JOC_NORMAL)
		m_tauler.actualitzaMovimentsValids();

	tableFile.close();
	movFile.close();
}

bool haveMov(const Posicio& pos)
{
	if (pos.teFitxa())
		if (pos.getFitxa()->getNMoviments() > 0)
			return true;
	return false;
}

bool screenLimit(const int& x, const int& y)
{
	return (x <= TAMANY_PANTALLA_X || y <= TAMANY_PANTALLA_Y);
}

bool limitTable(const int& x, const int& y)
{
	return ((x < NUM_COLS_TAULER && x >= 0) && (y < NUM_FILES_TAULER && y >= 0));
}

bool inTable(const int& x, const int& y)
{
	return (x >= (POS_X_TAULER + CASELLA_INICIAL_X)) &&
		(y >= POS_Y_TAULER + CASELLA_INICIAL_Y) &&
		(x <= (POS_X_TAULER + CASELLA_INICIAL_X + AMPLADA_CASELLA * NUM_COLS_TAULER)) &&
		(y <= (POS_Y_TAULER + CASELLA_INICIAL_Y + ALCADA_CASELLA * NUM_FILES_TAULER));
}

bool Joc::posToPx(int& x, int& y) const
{
	x = POS_X_TAULER + CASELLA_INICIAL_X + AMPLADA_CASELLA * ((NUM_COLS_TAULER - 1) - x);
	y = POS_Y_TAULER + CASELLA_INICIAL_Y + ALCADA_CASELLA * ((NUM_FILES_TAULER - 1) - y);
	if (!screenLimit(x, y))
		return false;
	else
		return true;
}

IMAGE_NAME imageFitxa(const char& tipus)
{
	switch (tipus)
	{
	case 'O': {
		return GRAFIC_FITXA_BLANCA;
		break;
	}
	case 'X': {
		return GRAFIC_FITXA_NEGRA;
		break;
	}
	case 'D': {
		return GRAFIC_DAMA_BLANCA;
		break;
	}
	case 'R': {
		return GRAFIC_DAMA_NEGRA;
		break;
	}
	default:
		return GRAFIC_NUM_MAX;
		break;
	}
}

void Joc::printTauler(void) const
{
	GraphicManager::getInstance()->drawSprite(GRAFIC_FONS, 0, 0);
	GraphicManager::getInstance()->drawSprite(GRAFIC_TAULER, POS_X_TAULER, POS_Y_TAULER);
	for (int y = 0; y < NUM_FILES_TAULER; y++)
		for (int x = 0; x < NUM_COLS_TAULER; x++)
			if(m_tauler.getPos(x, y).teFitxa())
			{
				Posicio pos = m_tauler.getPos(x, y);
				int posX = pos.getColumna();
				int posY = pos.getFila();
				char tipus = pos.getTFitxa();

				if (posToPx(posX, posY))
					GraphicManager::getInstance()->drawSprite(imageFitxa(tipus), posX, posY);
			}
}

void Joc::printMovsFitxa(const Posicio& pos) const
{
	if (haveMov(pos))
	{
		const Fitxa* fitxa = pos.getFitxa();
		int nMov = fitxa->getNMoviments();

		Posicio* posicions = new Posicio[nMov];
		m_tauler.getPosicionsPossibles(pos, nMov, posicions);

		for (int i = 0; i < nMov; i++)
		{
			const Posicio aux = posicions[i];
			int posX = aux.getColumna();
			int posY = aux.getFila();
			if(limitTable(posX, posY))
				if (posToPx(posX, posY))
					if(inTable(posX, posY))
						GraphicManager::getInstance()->drawSprite(GRAFIC_POSICIO_VALIDA, posX, posY);
		}

		delete[] posicions;
	}
}
bool Joc::notTorn(const Posicio& pos) const
{
	if (pos.teFitxa())
	{
		const Fitxa* fitxa = pos.getFitxa();
		if (fitxa->getColor() == COLOR_BLANC && !m_torn)
			return true;
		else if (fitxa->getColor() == COLOR_NEGRE && m_torn)
			return true;
	}
	return false;
}

bool Joc::actualitza(int mousePosX, int mousePosY, bool mouseStatus)
{
	int xRel = mousePosX - (POS_X_TAULER + CASELLA_INICIAL_X);
	int yRel = mousePosY - (POS_Y_TAULER + CASELLA_INICIAL_Y);
	int fila = yRel / AMPLADA_CASELLA;
	int columna = xRel / ALCADA_CASELLA;
	if (!m_modeRepl)
	{
		if (mouseStatus && inTable(mousePosX, mousePosY))
		{
			if (limitTable(columna, fila))
			{
				const int posF = (NUM_FILES_TAULER - 1 - fila);
				const int posY = (NUM_COLS_TAULER - 1 - columna);
				Posicio posAux = m_tauler.getPos(posF, posY);
		
				if (posAux.teFitxa())
				{
					const Fitxa* fitxa = posAux.getFitxa();
					if (!notTorn(posAux))
					{
						if (fitxa->getColor() == COLOR_BLANC && m_tauler.getNMovBlancas() == 0)
						{
							m_torn = false;
							m_movFocus = false;
						}
						else if (fitxa->getColor() == COLOR_BLANC && m_tauler.getNMovBlancas() == 0)
						{
							m_torn = true;
							m_movFocus = false;
						}
						else if (posAux == m_posFocus && m_movFocus)
							m_movFocus = false;
						else
						{
							m_posFocus = posAux;
							m_movFocus = true;
						}
					}
				}
				else
				{
					posAux.setPosicio(intToPos(posF, posY));
					if (!(posAux == m_posFocus) && m_movFocus)
					{
						if (m_tauler.mouFitxa(m_posFocus, posAux))
						{
							Posicio posAux = m_tauler.getPos(posF, posY);
							m_posFocus = posAux;
							m_movFocus = false;

							if (!m_modeRepl)
								escriureMoviment(m_posFocus, posAux);

							if (m_torn)
								m_torn = false;
							else
								m_torn = true;

						}
					}
				}

			}
		}
		printTauler();

		if (m_movFocus)
			printMovsFitxa(m_posFocus);
	}
	else
		nextMov();

	if (finalitza())
	{
		printTxt("FINAL DE LA PARTIDA");
		return true;
	}
	else 
	{
		string msg = "Mode joc: ";
		if (m_modeRepl)
			msg += "Replay";
		else
			msg += "Normal";
		msg += "\nJugador Actual: ";
		if (m_torn)
			msg += "Blanques";
		else
			msg += "Negres";

		printTxt(msg);
	}
	
	return false;
}

void Joc::printTxt(const string& txt) const
{
	int posTextX = POS_X_TAULER;
	int posTextY = POS_Y_TAULER + (ALCADA_CASELLA * NUM_FILES_TAULER) + 120;
	GraphicManager::getInstance()->drawFont(FONT_WHITE_30, posTextX, posTextY, 0.8, txt);
}

void Joc::escriureMoviment(const Posicio& inicial, const Posicio & final) const
{
	ofstream fitxer;
	fitxer.open(m_movFileName, ofstream::app);
	if (fitxer.is_open())
	{
		fitxer << inicial.getPosicio() << " " << final.getPosicio() << "\n";
		fitxer.close();
	}
}

void Joc::guardarMov() const
{
	ofstream movFileO(m_movFileName);
	if (movFileO.is_open())
	{
		for (int y = 0; y < NUM_FILES_TAULER; y++)
			for (int x = 0; x < NUM_COLS_TAULER; x++)
				if (m_tauler.getPos(x, y).teFitxa())
				{
					const Posicio& pos = m_tauler.getPos(x, y);

					if (haveMov(pos))
					{
						const Fitxa* fitxa = pos.getFitxa();
						int nMov = fitxa->getNMoviments();

						Posicio* posicions = new Posicio[nMov];
						m_tauler.getPosicionsPossibles(pos, nMov, posicions);

						for (int i = 0; i < nMov; i++)
						{
							const string& inicial = pos.getPosicio();
							const string& final = posicions[i].getPosicio();
							movFileO << inicial << " " << final << "\n";
						}

						delete[] posicions;
					}
				}
	}
	movFileO.close();
}

void Joc::nextMov(void)
{
	if (movFile.is_open())
	{
		string inicial = "";
		string final = "";
		movFile >> inicial >> final;
		Posicio posInicial(inicial);
		Posicio posFinal(final);
		m_tauler.mouFitxa(posInicial, posFinal);
	}
}

void Joc::closeFile() const
{
	if(movFile.is_open())
		movFile.close();
}


bool Joc::finalitza(void) const
{
	return m_tauler.isWin();
}
