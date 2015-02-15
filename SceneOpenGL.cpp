#include "SceneOpenGL.h"


// Permet d'éviter la ré-écriture du namespace glm::

using namespace glm;


// Constructeur de Destucteur

SceneOpenGL::SceneOpenGL(std::string titreFenetre, int largeurFenetre, int hauteurFenetre) : m_titreFenetre(titreFenetre), m_largeurFenetre(largeurFenetre),
                                                                                             m_hauteurFenetre(hauteurFenetre), m_fenetre(0), m_contexteOpenGL(0),
                                                                                             m_input()
{

}


SceneOpenGL::~SceneOpenGL()
{
    SDL_GL_DeleteContext(m_contexteOpenGL);
    SDL_DestroyWindow(m_fenetre);
    SDL_Quit();
}


// Méthodes

bool SceneOpenGL::initialiserFenetre()
{
    // Initialisation de la SDL

    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << std::endl;
        SDL_Quit();

        return false;
    }


    // Version d'OpenGL

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);


    // Double Buffer

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);


    // Création de la fenêtre

    m_fenetre = SDL_CreateWindow(m_titreFenetre.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_largeurFenetre, m_hauteurFenetre, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

    if(m_fenetre == 0)
    {
        std::cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << std::endl;
        SDL_Quit();

        return false;
    }


    // Création du contexte OpenGL

    m_contexteOpenGL = SDL_GL_CreateContext(m_fenetre);

    if(m_contexteOpenGL == 0)
    {
        std::cout << SDL_GetError() << std::endl;
        SDL_DestroyWindow(m_fenetre);
        SDL_Quit();

        return false;
    }

    return true;
}


bool SceneOpenGL::initGL()
{
    #ifdef WIN32

        // On initialise GLEW

        GLenum initialisationGLEW( glewInit() );


        // Si l'initialisation a échoué :

        if(initialisationGLEW != GLEW_OK)
        {
            // On affiche l'erreur grâce à la fonction : glewGetErrorString(GLenum code)

            std::cout << "Erreur d'initialisation de GLEW : " << glewGetErrorString(initialisationGLEW) << std::endl;


            // On quitte la SDL

            SDL_GL_DeleteContext(m_contexteOpenGL);
            SDL_DestroyWindow(m_fenetre);
            SDL_Quit();

            return false;
        }

    #endif


    // Activation du Depth Buffer

    glEnable(GL_DEPTH_TEST);


    // Tout s'est bien passé, on retourne true

    return true;
}


void SceneOpenGL::bouclePrincipale()
{
   // Variables

    Uint32 frameRate (1000 / 50);
    Uint32 debutBoucle(0), finBoucle(0), tempsEcoule(0);

    // Matrices

    mat4 projection; //matrice perspective
    mat4 modelview; // matrice scenne

    projection = perspective(70.0, (double) m_largeurFenetre / m_hauteurFenetre, .5, 200.0); //mat4 perspective(double angle, double ratio, double near vue devant , double far vue au loin);
    modelview = mat4(1.0);

    // Déclaration d'un objet Triangle

    Triangle triangle(1.0, 2.0, "Shaders/couleur3D.vert", "Shaders/couleur3D.frag");


    // Caméra

    m_input.afficherPointeur(false);
    m_input.capturerPointeur(true);

    // Boucle principale

    while(!m_input.terminer())
    {
        // On définit le temps de début de boucle

        debutBoucle = SDL_GetTicks();


        // Gestion des évènements

        // Gestion des évènements

        m_input.updateEvenements();

        //sortie prog

        if(m_input.getTouche(SDL_SCANCODE_ESCAPE))
            break;


        /* ***** Rendu OpenGL ***** */

        // Nettoyage de l'écran

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        modelview = mat4(1.0);
        modelview = lookAt(vec3(5.0, 5.0, 5.0), vec3(0.0, 0.0, 0.0), vec3(0.0, 0.0, 1.0));

        triangle.setPosition(vec3(2.5,0.0,0.0));
        triangle.setAngle(triangle.getAngle()+vec3(360/100,0.0,0.0));

        triangle.afficher(projection,modelview);

        // Actualisation de la fenêtre

        SDL_GL_SwapWindow(m_fenetre);

        // Calcul du temps écoulé

        finBoucle = SDL_GetTicks();
        tempsEcoule = finBoucle - debutBoucle;


        // Si nécessaire, on met en pause le programme

        if(tempsEcoule < frameRate)
            SDL_Delay(frameRate - tempsEcoule);
    }
}

