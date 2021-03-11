#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QString>
#include <QtSql/QSqlTableModel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT



public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



private slots:
    void on_button_clear_clicked();

    void on_pushButton_clicked();

    void on_push_import_clicked();

    void on_btnSubmit_clicked();

    void on_btnSelectTable_clicked();

    void on_btnAdd_clicked();

    void on_btndelete_clicked();

    void on_btnOk_clicked();

    void on_btnData_clicked();

    void on_btnExport_clicked();

    void on_btnOkEport_clicked();

    void on_button_edit_clicked();

    void on_push_add_clicked();

    void on_push_add_pressed();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
    QSqlTableModel* model;
    QString data_path;
    QString data_export;
    int countRow();

};
#endif // MAINWINDOW_H

