#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidgetItem>
#include <QMessageBox>
#include <String>
#include <QString>
#include <iostream>
#include <QGraphicsView>
#include <QtMath>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    int n = 0;
    int start_vertex = 0;
    int **graph = new int*[n];
    bool *visited = new bool[n];

    void dfs(int v, int **graph, bool *visited, int n);

private slots:
    void on_pushButton_setParams_clicked();

    void on_pushButton_setGraph_clicked();
    void on_pushButton_drawGraph_clicked();

    void on_pushButton_restart_clicked();

private:
    Ui::MainWindow *ui;
};





#endif // MAINWINDOW_H
