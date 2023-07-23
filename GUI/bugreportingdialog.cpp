#include "bugreportingdialog.h"
#include "ui_bugreportingdialog.h"
#include <QNetworkAccessManager>
#include <QJsonObject>
#include <QJsonDocument>
#include <QNetworkReply>
#include <QByteArray>
#include <QMessageBox>

QString bugReportingDialog::bugOption = "Option 1";

bugReportingDialog::bugReportingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::bugReportingDialog)
{
    ui->setupUi(this);

    /* Remove window title */
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::CustomizeWindowHint);
}

bugReportingDialog::~bugReportingDialog()
{
    qDebug() << "Bug reporting destructor call";
    delete ui;
}

void bugReportingDialog::on_submitReportButton_clicked()
{
    /* Skip if the user didn't choose an option */
    if( !ui->bugOptions->currentText().compare("Select your bug topic to report") )
    {
        QMessageBox noSelectionMB;
        noSelectionMB.information(this,
                        tr("Incomplete report."),
                        tr("You didn't choose an option to report."),
                        QMessageBox::Ok);
        return;
    }
    /* Display a popup message with no buttons */
    auto msgbox = new QMessageBox(this);
    msgbox->setGeometry(850, 450, 250, 200);
    msgbox->setWindowTitle("Loading...");
    msgbox->setText("Posting your bug.");
    msgbox->setStandardButtons(QMessageBox::NoButton);
    msgbox->open();

    auto carID = "ADAS2023";

    /* Link to the signal and slot */
    QNetworkRequest request(QUrl("https://adas-eece2023.azurewebsites.net/Bug/Create"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject jsonObject;

    jsonObject["title"] = bugOption;
    jsonObject["carId"] = carID;


    // Convert the JSON object to a JSON document
    QJsonDocument jsonDocument(jsonObject);

    // Convert the JSON document to a QByteArray
    QByteArray jsonData = jsonDocument.toJson();

    /* Connect to the server */
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);

    manager->post(request, jsonData);

    connect(manager, &QNetworkAccessManager::finished, this, [=](QNetworkReply *reply)
    {
        delete msgbox;
        if (reply->error() == QNetworkReply::NoError)
        {
            QMessageBox bugMB;
            bugMB.information(this,
                            tr("Well received."),
                            tr("We're reaching you ASAP."),
                            QMessageBox::Ok);
            accept();
        }
        else
        {
            /* If the connection is incomplete */
            if( reply->errorString().contains("Bad Request") )
            {
                QMessageBox duplicateMB;
                duplicateMB.critical(this,
                                tr("Duplicate report."),
                                tr("The development team is still working on it."),
                                QMessageBox::Ok);
                qDebug() << "Request failed:" << reply->errorString();
            }
            /* If their's no internet */
            else
            {
                QMessageBox failedConnectionMB;
                failedConnectionMB.critical(this,
                                tr("Failed to reach server."),
                                tr("Check your internet connection."),
                                QMessageBox::Ok);
            }
        }
    });
}

void bugReportingDialog::on_backButton_clicked()
{
    this->reject();
}


void bugReportingDialog::on_bugOptions_currentTextChanged(const QString &option)
{
    bugOption = option;
}
