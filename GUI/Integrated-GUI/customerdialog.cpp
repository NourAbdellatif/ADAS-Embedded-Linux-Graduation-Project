#include "customerdialog.h"
#include "ui_customerdialog.h"
#include <QSettings>
#include <QPixmap>
#include <QDebug>
#include <QMovie>
#include "mainwindow.h"
#include <QMessageBox>

/* Static master class variables */
QList<QListWidgetItem *> CustomerDialog::usedOptions;
Ui::CustomerDialog *CustomerDialog::ui = new Ui::CustomerDialog;

/* Constructor */
CustomerDialog::CustomerDialog(QWidget *parent) :
    QDialog(parent)
{
   /*
     * This line should be after the QMovie or the animation will overwrite the ui
     */
    ui->setupUi(this);


    /* Load previously saved data from ProgDialog.cpp customer save button */
    QSettings settings1("Customer", "Configured");
    QString index = "Current %1";
    settings1.beginGroup("Customer");
    QVariant savedPathsLen = settings1.value(index.arg(0));
    for(int i = 1; i <= savedPathsLen.toInt(); i++)
    {
        ui->listWidget_2->addItem(settings1.value( index.arg( QString::number(i) ) ).toString());
    }
    settings1.endGroup();

//    if (ui->listWidget_2->count() == 0)
//    {
//        QMessageBox noFeaturesMB;
//        noFeaturesMB.critical(this,
//                        tr("You don't have access to any features."),
//                        tr("Visit your nearest agency."),
//                        QMessageBox::Ok);
//    }
//    else
//    {
//        /* Load the chosen options and run */
//        QSettings settings2("Used", "Saved");
//        settings2.beginGroup("Used");
//        thread = new ProcessThread( settings2.value( index.arg(QString::number(1)) ).toString() );
//        thread->start();
//        settings2.endGroup();
//    }
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::CustomizeWindowHint);
}


/* Destructor */
CustomerDialog::~CustomerDialog()
{
    qDebug() << "Customer destructor call";
    delete ui;
}


/* Report bugs to the agency */
void CustomerDialog::on_reportButton_clicked()
{
    dialog_report = new bugReportingDialog(this);
    dialog_report->exec();
    delete dialog_report;
}


/* Save the selected application to future use */
void CustomerDialog::on_saveButton_clicked()
{
    usedOptions = ui->listWidget_2->selectedItems();
    if(usedOptions.isEmpty())
    {
//        QMessageBox noFeaturesMB;
//        noFeaturesMB.critical(this,
//                        tr("Nothing to save."),
//                        tr("Visit your nearest agency."),
//                        QMessageBox::Ok);
        return;
    }
    QString index = "Current %1";
    /* Load the chosen options and run */
    QSettings settings("Used", "Saved");
    settings.beginGroup("Used");
    /* Store here the number of paths */
    settings.setValue(index.arg(0), usedOptions.count());
    /* Store all the highlighted paths */
    for(int i = 1; i <= usedOptions.count(); i++)
    {
        settings.setValue(index.arg(QString::number(i)), usedOptions.at(i-1)->text());
    }
    settings.endGroup();
    accept();
}

/* Go to agency login */
void CustomerDialog::on_programmerButton_clicked()
{
    /* Construct any dialogs here to avoid re-construction */
    dialog_Login = new LoginDialog(this);
    dialog_Login->exec();
    delete dialog_Login;
}

void CustomerDialog::on_back_button_clicked()
{
    this->reject();
}

void CustomerDialog::on_cameraButton_clicked()
{
    QMessageBox cameraMB;
    cameraMB.information(this,
                    tr("Available cameras."),
                    tr("You only have 1 front camera."),
                    QMessageBox::Ok);
}
