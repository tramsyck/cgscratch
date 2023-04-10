#include "mainwindow.h"
#include "canvas.h"
#include "ui_mainwindow.h"

#include <QImage>
#include <QPixmap>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Viewport viewport;
    Scene scene;
    scene.addSampleObject();
    _canvas = new Canvas(600, 600, viewport, scene);
    _canvas->setCameraPosition(Vector3d { 0, 0, 0 });
    QImage image = _canvas->generate();
    ui->label->setPixmap(QPixmap::fromImage(image));
}

MainWindow::~MainWindow()
{
    delete _canvas;
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
}
