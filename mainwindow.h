#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include "evenement.h"
#include "arduino.h"

#include <QMessageBox>
#include <QIntValidator>
#include <QDebug>
#include <QSqlQuery>
#include <QMainWindow>
#include <QDate>
#include <QDateTime>
#include <QPrinter>
#include <QTextStream>
#include <QFile>
#include <QDataStream>
#include <QSortFilterProxyModel>
#include <QTextTableFormat>
#include <QStandardItemModel>
#include <QDialog>
#include <QFileDialog>
#include <QDialog>
#include <QDesktopWidget>
#include <QSettings>
#include <QMediaPlayer>
#include <QVideoWidget>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QSortFilterProxyModel *proxy;


private slots:

    void on_pb_ajouter_clicked();

    void on_pb_supprimer_clicked();

    void on_pb_modifer_clicked();


    void on_pb_rechercher_clicked();


    void on_radioButton_id_clicked();

    void on_radioButton_nom_clicked();

    void on_radioButton_invites_clicked();

    void on_radioButton_date_clicked();


    void on_pb_pdf_clicked();

    void on_pb_imprimer_clicked();


    void on_load_clicked();

    void on_comboBox_load_currentIndexChanged(const QString &arg1);

    void on_buttonBox_accepted();


    void on_statistique_clicked();


    void on_calendarWidget_selectionChanged();


    void on_tab_evenement_clicked(const QModelIndex &index);




    void on_excel_clicked();


    void on_play_clicked();

    void on_stop_clicked();


    void update_label();



private:
    Ui::MainWindow *ui;
    Evenement E;
    QMediaPlayer * player;
    QVideoWidget * vw;

    int selected=0;
    QString eid;

    QByteArray data;
    QString ch="";
    //arduino a;
};

#endif // MAINWINDOW_H
