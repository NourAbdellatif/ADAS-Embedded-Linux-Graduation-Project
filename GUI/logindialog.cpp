#include "ui_logindialog.h"
#include <QMessageBox>
#include "preprocessing.h"
#include "customerdialog.h"
#include <QDebug>
#include <QLabel>
#include <QMovie>
#include <QtNetwork>
#include <QCoreApplication>
#include "logindialog.h"

/* Static globals */
QString LoginDialog::global_user_email;

/* Constructor */
LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);

    /* Add icon photos */
    QIcon user(":/Images/user.png");

    /* Add actions */
    ui->idLineEdit->addAction(user, QLineEdit::LeadingPosition);

    /* Place holder text */
    ui->idLineEdit->setPlaceholderText("Enter your email");

    /* Enable Clear button */
    ui->idLineEdit->setClearButtonEnabled(true);

    /* Remove window title */
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::CustomizeWindowHint);
}

/* Destructor */
LoginDialog::~LoginDialog()
{
    qDebug() << "Login destructor call";
    delete ui;
}

/* Custom public functions */
void LoginDialog::insert_char(QString new_text)
{
    QString current_text = ui->idLineEdit->text();
    new_text = current_text + new_text;
    ui->idLineEdit->setText(new_text);
}


/* Show the available IDs to choose 1 (if you don't remember yours) */
void LoginDialog::on_validIdsButton_clicked()
{
    /* Read the email in the line edit and remove any spaces*/
    auto email = ui->idLineEdit->text().remove(" ").remove("\n");
    /* ID line edit is empty */
    if(email.isEmpty())
    {
        return;
    }

    /* Display a popup message with no buttons */
    auto msgbox = new QMessageBox(this);
    msgbox->setGeometry(850, 450, 250, 200);
    msgbox->setWindowTitle("Loading...");
    msgbox->setText(tr("%1 registeration in progress.").arg(email));
    msgbox->setStandardButtons(QMessageBox::NoButton);
    msgbox->open();

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    connect(manager, &QNetworkAccessManager::finished, this, [=](QNetworkReply *reply)
    {
        delete msgbox;
        QMessageBox registerMB;
        if (reply->error() == QNetworkReply::NoError)
        {
            registerMB.information(this,
                                tr("Check your email."),
                                tr("%1 has been registered successfuly.").arg(email),
                                QMessageBox::Ok);
        }else
        {
            /* If the connection is incomplete */
            if( reply->errorString().contains("Bad Request") )
            {
                registerMB.information(this,
                                    tr("Incomplete registeration."),
                                    tr("%1 is invalid format of an email or already registered.").arg(email),
                                    QMessageBox::Ok);
                qDebug() << "Request failed:" << reply->errorString();            }
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
    QNetworkRequest request(QUrl("https://adas-eece2023.azurewebsites.net/User/Register"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    /* Create the JSON data to send */
    QByteArray jsonData = QString(R"({"email": "%1"})").arg(email).toUtf8();
    manager->post(request, jsonData);
}


/* Submit the ID */
void LoginDialog::on_submitButton_clicked()
{
    /* Read the email in the life edit and remove any spaces and new lines */
    auto email = ui->idLineEdit->text().remove(" ").remove("\n");
    /* ID line edit is empty */
    if(email.isEmpty())
    {
        return;
    }
    /* Link to the signal and slot */
    QNetworkRequest request(QUrl("https://adas-eece2023.azurewebsites.net/User/ValidateEmail"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    /* Create the JSON data to send */
    QByteArray jsonData = QString(R"({"email": "%1"})").arg(email).toUtf8();

    /* Display a popup message with no buttons */
    auto msgbox = new QMessageBox(this);
    msgbox->setGeometry(850, 450, 250, 200);
    msgbox->setWindowTitle("Loading...");
    msgbox->setText( tr("%1 confirmation in progress.").arg(email) );
    msgbox->setStandardButtons(QMessageBox::NoButton);
    msgbox->open();

    /* Connect to the server */
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    manager->post(request, jsonData);
    connect(manager, &QNetworkAccessManager::finished, this, [=](QNetworkReply *reply)
    {
        qDebug() << email;
        delete msgbox;
        if (reply->error() == QNetworkReply::NoError)
        {
            QByteArray responseData = reply->readAll();
            /* ID is banned */
            if(responseData == "banned")
            {
                QMessageBox bannMB;
                bannMB.critical(this,
                                tr("Banned account."),
                                tr("Check your email: %1 to unlock.").arg(email),
                                QMessageBox::Ok);
            }
            /* ID exists */
            else if(responseData == "true")
            {
                global_user_email = email;
                dialog_Pass = new PassDialog(this);
                dialog_Pass->exec();
                accept();
            }
            /* ID doesn't exist */
            else if(responseData == "false")
            {
                QMessageBox bannMB;
                bannMB.critical(this,
                                tr("Please register first."),
                                tr("%1 doesn't have access.").arg(email),
                                QMessageBox::Ok);
            }
            else
            {
                /* Do nothing */
            }
        }
        else
        {
            /* If the connection is incomplete */
            if( reply->errorString().contains("Bad Request") )
            {
                qDebug() << "Request failed:" << reply->errorString();            }
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


void LoginDialog::on_back_button_clicked()
{
    this->reject();
}
