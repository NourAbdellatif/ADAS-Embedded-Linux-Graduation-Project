#ifndef PASSDIALOG_H
#define PASSDIALOG_H

#include <QDialog>
#include "progdialog.h"

namespace Ui {
class PassDialog;
}

class PassDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PassDialog(QWidget *parent = 0);
    ~PassDialog();

private slots:
    void on_forgotButton_clicked();

    void on_signButton_clicked();

    void on_checkBox_clicked();

    void on_back_button_clicked();

private:
    Ui::PassDialog *ui;
    ProgDialog *dialog_prog;
};

#endif // PASSDIALOG_H
