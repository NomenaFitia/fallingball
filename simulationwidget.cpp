#include "simulationwidget.h"
#include <cmath>

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
