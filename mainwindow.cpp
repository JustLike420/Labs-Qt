#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tableView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->tableView, SIGNAL(customContextMenuRequested(QPoint)), SLOT(CustomMenuReq(QPoint)));
    fl = 0;
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
    fl = 1;
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

// выбирается строка которую выбрал пользователь, но только первый столбец 59
void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    int temp_nom;
    temp_nom = ui->tableView->model()->data(ui->tableView->model()->index(index.row(), 0)).toInt();
    ui->lineEdit->setText(QString::number(temp_nom));

    QSqlQuery* query = new QSqlQuery();
    query->prepare("SELECT name, post FROM primer1 WHERE id=:id");
    query->bindValue(":id", temp_nom);

    if (query->exec()){
        query->next();
        ui->lineEdit_2->setText(query->value(0).toString());
        ui->lineEdit_3->setText(query->value(1).toString());
    }
}


void MainWindow::on_pushButton_3_clicked()
{
    QSqlQuery* query = new QSqlQuery();
    query->prepare("UPDATE primer1 SET name=?, post=? WHERE id=?");
    query->bindValue(0, ui->lineEdit_2->text());
    query->bindValue(1, ui->lineEdit_3->text());
    query->bindValue(2, ui->lineEdit->text());

    if (query->exec()){
        on_pushButton_clicked();
    }
}


void MainWindow::on_pushButton_4_clicked()
{
    QSqlQuery* query = new QSqlQuery();
    query->prepare("DELETE FROM primer1 WHERE id=?");
    query->bindValue(0, ui->lineEdit->text());

    if (query->exec()){
        on_pushButton_clicked();
    }
}

void MainWindow::CustomMenuReq(QPoint pos)
{
 if (fl==1){
     QModelIndex index = ui->tableView->indexAt(pos);
     globid = ui->tableView->model()->data(ui->tableView->model()->index(index.row(), 0)).toInt();
     QMenu* menu = new QMenu(this);
     QAction* izm = new QAction("Изменить", this);
     connect(izm, SIGNAL(triggered()), this, SLOT(izm_zap()));

     QAction* ud = new QAction("Удалить", this);
     connect(ud, SIGNAL(triggered()), this, SLOT(del_zap()));

     menu->addAction(izm);
     menu->addAction(ud);
     menu->popup(ui->tableView->viewport()->mapToGlobal(pos));
 }
}

void MainWindow::del_zap()
{
    QSqlQuery* query = new QSqlQuery();
    query->prepare("DELETE FROM primer1 WHERE id=?");
    query->bindValue(0, globid);

    if (query->exec()){
        on_pushButton_clicked();
    }
}

void MainWindow::izm_zap()
{
    izm = new izmenenie();
    connect(this, SIGNAL(sendID(int)), izm, SLOT(obr_sendID(int)));
    emit sendID(globid);
    izm->show();
    disconnect(this, SIGNAL(sendID(int)), izm, SLOT(obr_sendID(int)));

}
