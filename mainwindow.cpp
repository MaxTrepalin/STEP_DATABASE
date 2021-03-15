#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QString>
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlRelationalTableModel>
#include <QDir>


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

void MainWindow::on_push_import_clicked()
{
      QSqlDatabase db;
      db = QSqlDatabase::addDatabase("QSQLITE");

       data_path = ui->input_path->text();
       ui->statusbar->showMessage("База данных загружена из SQLITE " + data_path);


       db = QSqlDatabase::addDatabase("QSQLITE");

       db.setDatabaseName(data_path);

       if (db.open()) {

       model = new QSqlTableModel(this, db);
       model -> setTable("table_person");
       model->select();
       ui->tableView->setModel(model);

}

}

void MainWindow::on_button_clear_clicked()
{
    {
        int selectedRow = ui->tableView->currentIndex().row();
        if (selectedRow >= 0 ) {
           model->removeRow(selectedRow);
     model->select();
        } else {
            ui->statusbar->showMessage( "нет строки");
        }
    }
}

void MainWindow::on_button_edit_clicked()
{
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
}

void MainWindow::on_push_add_clicked()
{
      model->insertRow(model->rowCount());
}

void MainWindow::on_push_export_clicked()
{
    data_export = ui->input_path->text();
    ui->statusbar->showMessage("База данных экспортирована в CSV" + data_export);

    QSqlQuery query = QSqlQuery(db);
    if (!query.exec("select* from table_person"))
    {
        return;
            }
    while (query.next()) {
        export_all = export_all + query.value(0).toString() + ";"+
                query.value(1).toString() + ";" + query.value(2).toString() + "\n";}


    QString path = "C:\\Max_Trepalin\\STEP_database\\Step_database\\Step_base222.csv";
    QFile file(path);
    if (file.open(QIODevice::WriteOnly))
    {
    file.write(export_all.toLocal8Bit());
    file.close();
    }
     file.close();
    }

void MainWindow::on_button_find_clicked()
{

        QString find =  ui->input_select->text();
    QSqlQuery query = QSqlQuery(db);
              if(!query.exec("select* from table_person")){
                       return;
    }
              while(query.next()) {
                 if (find == query.value(0) || find == query.value(1) || find == query.value(2) || find == query.value(3) ){
                     QString row_find = query.value(0).toString()
                             + "; " + query.value(1).toString() + "; "
                             + query.value(2).toString() + "; " + query.value(3).toString();

                     ui->input_select->clear();
                     ui->statusbar->showMessage("Найдено " + row_find);
                 }
              }

    }
