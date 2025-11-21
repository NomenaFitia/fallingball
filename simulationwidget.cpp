#include "simulationwidget.h"
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

SimulationWidget::SimulationWidget(QWidget *parent)
    : QOpenGLWidget(parent)
{
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &SimulationWidget::updateLoop);
}

void SimulationWidget::initializeGL() {
    initializeOpenGLFunctions();
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
}

void SimulationWidget::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // Remplacement simple de gluPerspective
    float aspect = (float)w / (h ? h : 1);
    float fov = 45.0f;
    float zNear = 0.1f, zFar = 100.0f;
    float ymax = zNear * tanf(fov * M_PI / 360.0f);
    float xmax = ymax * aspect;
    glFrustum(-xmax, xmax, -ymax, ymax, zNear, zFar);
    glMatrixMode(GL_MODELVIEW);
}

// Fonction utilitaire pour dessiner une sphère centrée en (0,0,0)
// slices = nombre de découpes verticales (quartiers d'orange)
// stacks = nombre de découpes horizontales (empilement de disques)
void SimulationWidget::drawSphere(float radius, int slices, int stacks) {
    for (int i = 0; i <= stacks; ++i) {
        float lat0 = M_PI * (-0.5 + (float) (i - 1) / stacks);
        float z0  = radius * sin(lat0);
        float zr0 = radius * cos(lat0);

        float lat1 = M_PI * (-0.5 + (float) i / stacks);
        float z1  = radius * sin(lat1);
        float zr1 = radius * cos(lat1);

        glBegin(GL_QUAD_STRIP);
        for (int j = 0; j <= slices; ++j) {
            float lng = 2 * M_PI * (float) (j - 1) / slices;
            float x = cos(lng);
            float y = sin(lng);

            // On dessine deux sommets pour créer la bande
            // Optionnel : ajouter glNormal3f(x * zr0, y * zr0, z0) pour l'éclairage futur
            glVertex3f(x * zr0, y * zr0, z0);
            // Optionnel : ajouter glNormal3f(x * zr1, y * zr1, z1) pour l'éclairage futur
            glVertex3f(x * zr1, y * zr1, z1);
        }
        glEnd();
    }
}

// paintGl pour un cube
/*
void SimulationWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0f, -5.0f, -25.0f); // Caméra

    // Sol (Pied)
    glColor3f(0.8f, 0.6f, 0.5f);
    glBegin(GL_QUADS);
    glVertex3f(-2, 0, 2); glVertex3f( 2, 0, 2);
    glVertex3f( 2, 0, -2); glVertex3f(-2, 0, -2);
    glEnd();

    // Objet tombant
    glPushMatrix();
    glTranslatef(0.0f, m_yPos, 0.0f);
    glColor3f(1.0f, 0.0f, 0.0f);

    // Cube simple pour représenter la balle (car glutSolidSphere n'est pas standard)
    float r = 0.5f;
    glBegin(GL_QUADS);
    // Juste une face pour tester, fais un cube complet si tu veux
    glVertex3f(-r, 0, r); glVertex3f(r, 0, r);
    glVertex3f(r, 2*r, r); glVertex3f(-r, 2*r, r);
    glEnd();

    glPopMatrix();
}
*/

void SimulationWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0f, -5.0f, -25.0f); // Caméra reculée

    // --- Sol (Pied) ---
    glColor3f(0.8f, 0.6f, 0.5f);
    glBegin(GL_QUADS);
    glVertex3f(-2, 0, 2); glVertex3f( 2, 0, 2);
    glVertex3f( 2, 0, -2); glVertex3f(-2, 0, -2);
    glEnd();

    // --- Objet tombant (Sphère) ---
    glPushMatrix();

    float r = 0.5f; // Rayon de la balle

    // IMPORTANT : On positionne le CENTRE de la sphère.
    // Si m_yPos est le bas de la balle, le centre est à (m_yPos + r)
    glTranslatef(0.0f, m_yPos + r, 0.0f);

    glColor3f(1.0f, 0.0f, 0.0f); // Balle Rouge

    // Appel de la fonction utilitaire
    // 30 slices, 30 stacks donne un résultat assez lisse
    SimulationWidget::drawSphere(r, 30, 30);

    glPopMatrix();
}

void SimulationWidget::updateLoop() {
    if(!m_isFalling) return;

    float dt = 0.016f;
    m_velocity += m_gravity * dt;
    m_yPos -= m_velocity * dt;

    if (m_yPos <= 0) {
        m_yPos = 0;
        m_isFalling = false;
        m_timer->stop();
        // TODO: Appeler le cri ici !
    }
    update();
}

void SimulationWidget::dropObject() {
    m_yPos = m_startHeight;
    m_velocity = 0.0f;
    m_isFalling = true;
    m_timer->start(16);
}

void SimulationWidget::resetObject() {
    m_isFalling = false;
    m_timer->stop();
    m_yPos = m_startHeight;
    m_velocity = 0.0f;
    update();
}

void SimulationWidget::setMass(float m) { m_mass = m; }
void SimulationWidget::setHeight(float h) { m_startHeight = h; resetObject(); }
void SimulationWidget::setGravity(float g) { m_gravity = g; }
