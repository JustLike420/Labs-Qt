#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "login.h"
#include "ui_login.h"
#include "addrecord.h"
#include "ui_addrecord.h"
#include "izmenenie.h"
#include "ui_izmenenie.h"+

#include <QMainWindow>

//#include <QSqlTableModel>
#include <QSqlQueryModel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    login* logwin;
    addrecord* dopzap;
    izmenenie* izm;

    int globid;
    int fl; // флаг изменяется после нажатия пользователя

private slots:
    void on_action_triggered();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void obr_ref_tab();

    void on_tableView_clicked(const QModelIndex &index);

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();
    // наведение на таблицу
    void CustomMenuReq(QPoint);

    void del_zap();

    void izm_zap();
signals:
    void sendID(int);
private:
    Ui::MainWindow *ui;
//    QSqlTableModel* model;
    QSqlQueryModel* model;
};
#endif // MAINWINDOW_H
