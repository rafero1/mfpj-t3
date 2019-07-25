#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <string>
#include <QGraphicsSceneMouseEvent>
#include <QMouseEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    gView = ui->gView;
    scene = new QGraphicsScene(gView);

    scene->setSceneRect(gView->rect());
    gView->setScene(scene);
    gView->init();
    gView->drawUnitSquare();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_resetBtn_clicked()
{
    gView->reset();
}

void MainWindow::on_oneVecBtn_toggled(bool checked)
{
    if (checked)
    {
        gView->reset();
        gView->twoVecMode = false;
    }
}

void MainWindow::on_twoVecBtn_toggled(bool checked)
{
    if (checked)
    {
        gView->reset();
        gView->twoVecMode = true;
    }
}
