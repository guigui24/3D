#include <SDL2/SDL.h>
#include <iostream>
#include "SceneOpenGL.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

int main(int argc, char *argv[])
{
   // Création de la sène

    SceneOpenGL scene("OpenGL", WINDOW_WIDTH, WINDOW_HEIGHT);


    // Initialisation de la scène

    if(scene.initialiserFenetre() == false)
	return -1;

    if(scene.initGL() == false)
	return -1;


    // Boucle Principale

    scene.bouclePrincipale();


    // Fin du programme

    return 0;
}
