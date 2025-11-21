#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
/*
    // Connexion des boutons
    connect(ui->dropButton, &QPushButton::clicked,
            ui->openGLWidget, &SimulationWidget::dropObject);

    connect(ui->resetButton, &QPushButton::clicked,
            ui->openGLWidget, &SimulationWidget::resetObject);

    // Connexion des sliders
    // Attention: les sliders envoient des INT, il faut parfois convertir ou diviser
    connect(ui->heightSlider, &QSlider::valueChanged, this, [this](int val){
        ui->openGLWidget->setHeight((float)val);
    });

    connect(ui->gravitySlider, &QSlider::valueChanged, this, [this](int val){
        // Exemple si gravitySlider va de 0 à 200 pour représenter 0.0 à 20.0
        ui->openGLWidget->setGravity(val / 10.0f);
    });

*/
}

MainWindow::~MainWindow()
{
    delete ui;
}
