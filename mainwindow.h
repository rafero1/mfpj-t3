#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPushButton>
#include <QLabel>
#include "graphview.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_resetBtn_clicked();

    void on_oneVecBtn_toggled(bool checked);
    void on_twoVecBtn_toggled(bool checked);

private:
    Ui::MainWindow *ui;

    GraphView *gView;
    QGraphicsScene *scene;
    QPushButton *resetBtn;
    QPushButton *oneVectorBtn;
    QPushButton *TwoVectorBtn;
};

#endif // MAINWINDOW_H
