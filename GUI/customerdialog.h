#ifndef CUSTOMERDIALOG_H
#define CUSTOMERDIALOG_H

#include <QDialog>
#include "preprocessing.h"
#include <QListWidgetItem>
#include "processthread.h"
#include "logindialog.h"
#include "bugreportingdialog.h"

namespace Ui {
class CustomerDialog;
}

class CustomerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CustomerDialog(QWidget *parent = nullptr);
    ~CustomerDialog();
    static QList<QListWidgetItem *> usedOptions;

private slots:

    void on_reportButton_clicked();

    void on_saveButton_clicked();

    void on_programmerButton_clicked();

    void on_back_button_clicked();

    void on_cameraButton_clicked();

private:
//    ProcessThread * thread;
    LoginDialog * dialog_Login;
    bugReportingDialog * dialog_report;

/* To be accessed by progdialog.cpp save customer button */
public:
    static Ui::CustomerDialog *ui;
};

#endif // CUSTOMERDIALOG_H
