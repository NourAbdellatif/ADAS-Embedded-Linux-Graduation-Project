#ifndef PROGDIALOG_H
#define PROGDIALOG_H

#include <QDialog>
#include <QListWidgetItem>
//#include "customerdialog.h"

namespace Ui {
class ProgDialog;
}

class ProgDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ProgDialog(QWidget *parent = nullptr);
    ~ProgDialog();
    static QList<QListWidgetItem *> custArr;
    static QListWidgetItem * progArr;

private slots:
    void on_addButton_clicked();

    void on_deleteButton_clicked();

    void on_pushButton_clicked();

    void on_saveButton_clicked();

    void on_listWidget_currentRowChanged(int currentRow);

private:
    Ui::ProgDialog *ui;
    int mnSelected = -1;
};

#endif // PROGDIALOG_H
