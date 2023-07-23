#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "customerdialog.h"

// Test Comment
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void Clock();
    void ReadTempAndHumidity();
    void SetTempAndHumidityIcons();

private slots:


    void on_app_button_clicked();

    void on_back_button_clicked();

    void on_back_button_2_clicked();

    void on_back_button_3_clicked();

    void on_back_button_4_clicked();

    void on_settings_button_clicked();

    void on_calendar_button_clicked();

    void on_Info_button_clicked();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    QTimer *tempTimer;
    CustomerDialog * dialog_customer;
    ProcessThread * thread;
};
#endif // MAINWINDOW_H
