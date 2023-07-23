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

    /* Add icon photos */
    QIcon title(":/Images/medal.png");
    QIcon description(":/Images/description.png");

    /* Add actions */
//    ui->titleLineEdit->addAction(title, QLineEdit::LeadingPosition);
//    ui->descriptionLineEdit->addAction(description, QLineEdit::LeadingPosition);

//    /* Place holder text */
//    ui->titleLineEdit->setPlaceholderText("Title");
//    ui->descriptionLineEdit->setPlaceholderText("Description");

//    /* Enable Clear button */
//    ui->titleLineEdit->setClearButtonEnabled(true);
//    ui->descriptionLineEdit->setClearButtonEnabled(true);

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
    /* Display a popup message with no buttons */
    auto msgbox = new QMessageBox(this);
    msgbox->setGeometry(850, 450, 250, 200);
    msgbox->setWindowTitle("Loading...");
    msgbox->setText("Posting your bug.");
    msgbox->setStandardButtons(QMessageBox::NoButton);
    msgbox->open();

    QString carID = "ADAS2023";

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
            qDebug() << "Request failed:" << reply->errorString();
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
