#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QString>
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlRelationalTableModel>




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
            ui->statusbar->showMessage( "no row");
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
