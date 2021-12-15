#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_action_triggered()
{
    logwin = new login();
    logwin->show();
}


void MainWindow::on_pushButton_clicked()
{

    model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM primer1");

//    model = new QSqlTableModel();
//    model->setTable("primer");
//    model->select();

    model->setHeaderData(0, Qt::Horizontal,"Номер п/п");
    model->setHeaderData(1, Qt::Horizontal,"Название товара");
    model->setHeaderData(2, Qt::Horizontal, "Производитель");

    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->show();
}


void MainWindow::on_pushButton_2_clicked()
{
    dopzap = new addrecord();
    connect(dopzap, SIGNAL(refresh_table()), this, SLOT(obr_ref_tab()));
    dopzap->show();
}

void MainWindow::obr_ref_tab(){
    on_pushButton_clicked();
}

