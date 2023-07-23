#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include "progdialog.h"
#include <QString>
#include "passdialog.h"

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();

    void insert_char(QString new_text);

    static QString global_user_email;

private slots:
    void on_validIdsButton_clicked();

    void on_submitButton_clicked();

    void on_back_button_clicked();

private:
    Ui::LoginDialog *ui;
    PassDialog* dialog_Pass;
    // This'll block doing an object of this class.
    // void setupUi();
};

#endif // LOGINDIALOG_H
