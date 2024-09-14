#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Graph");
    ui->spinBox_startVertex->setMinimum(1);
    ui->spinBox_countVertex->setMinimum(1);

    ui->lineEdit_infoGraph->setVisible(false);
    ui->tableWidget_graph->setVisible(false);
    ui->pushButton_setGraph->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::dfs(int v, int **graph, bool *visited, int n) {
    visited[v] = true;
    ui->lineEdit_result->setText(ui->lineEdit_result->text() + QString::fromStdString(" ") + QString::number(v + 1));
    for (int i = 0; i < n; i++) {
        if (graph[i][v] == 1 && !visited[i]) {
            dfs(i, graph, visited, n);
        }
    }
}

void MainWindow::on_pushButton_setParams_clicked()
{
    n = ui->spinBox_countVertex->value();
    start_vertex = ui->spinBox_startVertex->value() - 1;

    if (n <= 0 || start_vertex < 0 || start_vertex >= n) {  // обработка ошибки пользователя
            QMessageBox::critical(this, "Error", "Invalid start vertex");
            return;
        }

    ui->lineEdit_infoGraph->setVisible(true);
    ui->tableWidget_graph->setVisible(true);
    ui->pushButton_setGraph->setVisible(true);

    ui->tableWidget_graph->setColumnCount(n);
    ui->tableWidget_graph->setRowCount(n);
    ui->tableWidget_graph->setShowGrid(true);
    ui->tableWidget_graph->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget_graph->setSelectionBehavior(QAbstractItemView::SelectRows);

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            QTableWidgetItem* item = new QTableWidgetItem(QString::number(0));
            ui->tableWidget_graph->setItem(i, j, item);
        }
    }

    ui->tableWidget_graph->resizeColumnsToContents();
}

void MainWindow::on_pushButton_setGraph_clicked()
{
    for (int j = 0; j < n; j++) {
        graph[j] = new int[n];
    }

    for (int i = 0; i < n; i++){
           for (int j = 0; j < n; j++){
               bool ok;
               int value = ui->tableWidget_graph->item(i, j)->text().toInt(&ok);
               if (!ok || (value != 0 && value != 1)) {
                   QMessageBox::critical(this, "Error", "Invalid graph value");
                   return;
               }
               graph[i][j] = value;
           }
       }

    for (int i = 0; i < n; i++) {
        visited[i] = false;
    }

    dfs(start_vertex, graph, visited, n);
}

void MainWindow::on_pushButton_restart_clicked()
{
    n = 0;
    start_vertex = 0;
    ui->tableWidget_graph->clear();
    ui->lineEdit_result->setText(QString::fromStdString(""));

}
