#ifndef JOC_H
#define JOC_H

#include <stdio.h>
#include "tauler.hpp"
#include "info_joc.hpp"

using namespace std;


class Joc 
{

public:
    Joc() :m_modeRepl(0), m_posFocus(""), m_movFocus(0), m_torn(1) {};
    void inicialitza(void);//tester
    void inicialitza(ModeJoc mode, const string& nomFitxerTauler, const string& nomFitxerMoviments);
    bool actualitza(int mousePosX, int mousePosY, bool mouseStatus);
    void printTauler(void) const;
    void printMovsFitxa(const Posicio& pos) const;
    void guardarMov() const;
    bool isRepl(void) const { return m_modeRepl; }
    void nextMov(void);
    void closeFile(void) const;
    bool finalitza(void) const;
    void printTxt(const string& txt) const;

private:
    bool posToPx(int& x, int& y) const;
    bool notTorn(const Posicio& pos) const;
    void escriureMoviment(const Posicio& inicial, const Posicio & final) const;

    Tauler m_tauler;
    
    string m_movFileName;
    bool m_modeRepl;
    
    Posicio m_posFocus;
    bool m_movFocus;

    bool m_torn;
};

#endif 
