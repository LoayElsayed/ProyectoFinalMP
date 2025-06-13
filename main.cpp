//
//  main.cpp
//
//  Copyright � 2018 Compiled Creations Limited. All rights reserved.
//

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__) || defined  (_WIN64)

#include <iostream>
//Definicio necesaria per poder incloure la llibreria i que trobi el main
#define SDL_MAIN_HANDLED
#include <windows.h>
//Llibreria grafica
#include "../Graphic Lib/libreria.h"
#include "../Graphic Lib/NFont/NFont.h"
#include <conio.h>      /* getch */ 

#elif __APPLE__
//Llibreria grafica
#include "../Graphic Lib/libreria.h"
#include "../Graphic Lib/NFont/NFont.h"
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation"
#include <SDL2/SDL.h>
#pragma clang diagnostic pop

#endif

#include "joc.hpp"
#include "info_joc.hpp"

bool clickDetect()
{
    static bool lastState = false;
    bool actualState = Mouse_getBtnLeft();
    bool clickDetectado = (actualState && !lastState);
    lastState = actualState;
    return clickDetectado;
}

int main(int argc, const char* argv[])
{
    //Instruccions necesaries per poder incloure la llibreria i que trobi el main
    SDL_SetMainReady();
    SDL_Init(SDL_INIT_VIDEO);

    //Inicialitza un objecte de la classe Screen que s'utilitza per gestionar la finestra grafica
    Screen pantalla(TAMANY_PANTALLA_X, TAMANY_PANTALLA_Y);
    pantalla.show();

    Joc joc;
    joc.inicialitza();

    bool final = false;

   do
    {
        pantalla.processEvents();

        bool mouseStatus = clickDetect();
        int mousePosX = Mouse_getX();
        int mousePosY = Mouse_getY();

        final = joc.actualitza(mousePosX, mousePosY, mouseStatus);

        pantalla.update();

    } while (!Keyboard_GetKeyTrg(KEYBOARD_ESCAPE) && !final);

   pantalla.update();
   system("pause");

   if (joc.isRepl())
       joc.guardarMov();

    joc.closeFile();

    SDL_Quit();
    return 0;
}

