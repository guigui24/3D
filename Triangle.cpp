#include "Triangle.h"

using namespace glm;

Triangle::Triangle(float basse, float hauteur, std::string const vertexShader, std::string const fragmentShader) : m_shader(vertexShader, fragmentShader)
{
    m_shader.charger();

    m_basse=basse;

    m_hauteur = hauteur;

    m_position = vec3(0.0, 0.0, 0.0);

    m_angle = vec3(0.0, 0.0, 0.0);

    // Vertices temporaires

    float verticesTmp[] = {0.0, 0.0, 0.0,   basse, 0.0, 0.0,  0.0, hauteur, 0.0};      // Face


    // Couleurs temporaires

    float couleursTmp[] = {1.0, 0.0, 0.0,   1.0, 0.0, 0.0,   1.0, 0.0, 0.0};          // Face


    // Copie des valeurs dans les tableaux finaux

    for(int i(0); i < T_VERTICES; i++)
    {
        m_vertices[i] = verticesTmp[i];
        m_couleurs[i] = couleursTmp[i];
    }
}

Triangle::~Triangle()
{

}

void Triangle::afficher(glm::mat4 &projection, glm::mat4 &modelview)
{
    mat4 sauvegardeModelview = modelview;


    // Translation pour positionner le cube

    modelview = translate(modelview, m_position);
    modelview = rotate(modelview,m_angle.x,vec3(1.0,0,0.0));
    modelview = rotate(modelview,m_angle.z,vec3(0.0,0.0,1.0));

    glUseProgram(m_shader.getProgramID());


        // Envoi des vertices

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, m_vertices);
        glEnableVertexAttribArray(0);


        // Envoi de la couleur

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, m_couleurs);
        glEnableVertexAttribArray(1);


        // Envoi des matrices

        glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "projection"), 1, GL_FALSE, value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(m_shader.getProgramID(), "modelview"), 1, GL_FALSE, value_ptr(modelview));


        // Rendu

        glDrawArrays(GL_TRIANGLES, 0, T_VERTICES/3);


        // Désactivation des tableaux

        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(0);


    // Désactivation du shader

    glUseProgram(0);

    // Restauration de la matrice

    modelview = sauvegardeModelview;
}
    /*glm::vec3 getTaille();*/
    void setPosition(glm::vec3 position);
    glm::vec3 getPosition();
