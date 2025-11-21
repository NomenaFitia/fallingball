#ifndef SIMULATIONWIDGET_H
#define SIMULATIONWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QTimer>

class SimulationWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit SimulationWidget(QWidget *parent = nullptr);

    // Fonctions de contrôle
    void dropObject();
    void resetObject();

    // Setters pour les sliders
    void setMass(float m);
    void setHeight(float h);
    void setGravity(float g);

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    void drawSphere(float radius, int slices, int stacks);

private slots:
    void updateLoop();

private:
    QTimer *m_timer;
    float m_yPos = 10.0f;
    float m_velocity = 0.0f;

    // Paramètres
    float m_mass = 1.0f;
    float m_startHeight = 10.0f;
    float m_gravity = 9.81f;
    bool m_isFalling = false;
};

#endif // SIMULATIONWIDGET_H
