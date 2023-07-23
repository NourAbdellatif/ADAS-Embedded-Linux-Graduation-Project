#include "passdialog.h"
#include "ui_passdialog.h"
#include <QDebug>
#include "customerdialog.h"
#include "logindialog.h"
#include <QtNetwork>
#include <QCoreApplication>
#include <QMessageBox>

PassDialog::PassDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PassDialog)
{
    ui->setupUi(this);

    /* Add icon photos */
    QIcon userPass(":/Images/sad.png");
    /* Add actions */
    ui->passLineEdit->addAction(userPass, QLineEdit::LeadingPosition);

    /* Place holder text */
    ui->passLineEdit->setPlaceholderText("Enter your password");

    /* Enable Clear button */
    ui->passLineEdit->setClearButtonEnabled(true);

    /* Password appear as stars */
    ui->passLineEdit->setEchoMode(QLineEdit::Password);

    /* Change the dialog title */
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::CustomizeWindowHint);
}

PassDialog::~PassDialog()
{
    qDebug() << "Pass destructor call";
    delete ui;
}

void PassDialog::on_forgotButton_clicked()
{
    /* Link to the signal and slot */
    QNetworkRequest request(QUrl("https://adas-eece2023.azurewebsites.net/User/ForgotPassword"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject jsonObject;
    jsonObject["email"] = LoginDialog::global_user_email;

    // Convert the JSON object to a JSON document
    QJsonDocument jsonDocument(jsonObject);

    // Convert the JSON document to a QByteArray
    QByteArray jsonData = jsonDocument.toJson();

    /* Display a popup message with no buttons */
    auto msgbox = new QMessageBox(this);
    msgbox->setGeometry(850, 450, 250, 200);
    msgbox->setWindowTitle("Loading...");
    msgbox->setText("Re-generating a new password.");
    msgbox->setStandardButtons(QMessageBox::NoButton);
    msgbox->open();

    /* Connect to the server */
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);

    manager->post(request, jsonData);

    connect(manager, &QNetworkAccessManager::finished, this, [=](QNetworkReply *reply)
    {
        delete msgbox;
        if (reply->error() == QNetworkReply::NoError)
        {
            QMessageBox forgotPassMB;
            forgotPassMB.information(this,
                            tr("Password has changed."),
                            tr("You have received the new password on %1.").arg(LoginDialog::global_user_email),
                            QMessageBox::Ok);
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

void PassDialog::on_signButton_clicked()
{
    /* Read the password in the line edit and remove any spaces*/
    auto pass = ui->passLineEdit->text().remove(" ").remove("\n");
    /* ID line edit is empty */
    if(pass.isEmpty())
    {
        return;
    }
    /* Link to the signal and slot */
    QNetworkRequest request(QUrl("https://adas-eece2023.azurewebsites.net/User/Login"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    /* Create the JSON data to send */
    QByteArray jsonData = QString(R"({"email": "%1", "password": "%2"})").arg(LoginDialog::global_user_email) \
                                                                          .arg(pass).toUtf8();
    qDebug() << jsonData;
    qDebug() << LoginDialog::global_user_email;

    /* Display a popup message with no buttons */
    auto msgbox = new QMessageBox(this);
    msgbox->setGeometry(850, 450, 250, 200);
    msgbox->setWindowTitle("Loading...");
    msgbox->setText("Email confirmation in progress.");
    msgbox->setStandardButtons(QMessageBox::NoButton);
    msgbox->open();

    /* Connect to the server */
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    manager->post(request, jsonData);
    connect(manager, &QNetworkAccessManager::finished, this, [=](QNetworkReply *reply)
    {
        delete msgbox;
        if (reply->error() == QNetworkReply::NoError)
        {
            QByteArray responseData = reply->readAll();

            QString jsonString = QString::fromUtf8(responseData);

            // Parse the JSON response
            QJsonDocument jsonResponse = QJsonDocument::fromJson(jsonString.toUtf8());

            // Check if parsing was successful
            if (!jsonResponse.isNull())
            {
                if (jsonResponse.isObject())
                {
                    QJsonObject jsonObject = jsonResponse.object();

                    // Access individual values
                    int remainingLoginAttempts = jsonObject["remainingLoginAttempts"].toInt();
                    QString id = jsonObject["id"].toString();

                    /* Correct password */
                    if(!id.isEmpty())
                    {
                        dialog_prog = new ProgDialog(this);
                        dialog_prog->exec();
                        reject();
                    }
                    else
                    {
                        if(remainingLoginAttempts != 0)
                        {
                            QMessageBox wrongPassMB;
                            wrongPassMB.critical(this,
                                            tr("Wrong password."),
                                            tr("You only have %1 remaining login attempts.").arg(remainingLoginAttempts),
                                            QMessageBox::Ok);
                        }
                        else
                        {
                            QMessageBox bannMB;
                            bannMB.critical(this,
                                            tr("Banned account."),
                                            tr("Check your email: %1 to unlock.").arg(LoginDialog::global_user_email),
                                            QMessageBox::Ok);
                            reject();
                        }
                    }
                }
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

void PassDialog::on_checkBox_clicked()
{
    /* Odd state means unchecked, while even means checked. */
    static int state = 1;
    /* Variable to add icon photos */
    static QIcon userPass;
    /* Get the current action and remove it */
    QAction* action = ui->passLineEdit->actions().at(0);
    ui->passLineEdit->removeAction(action);
    /* Remove place holder text */
    ui->passLineEdit->setPlaceholderText("Enter your password");
    /* If it's checked */
    if(state % 2)
    {
        /* Add icon photos */
        userPass.addFile(":/Images/emoji.png");
        /* Password appears */
        ui->passLineEdit->setEchoMode(QLineEdit::Normal);
    }
    else if( !(state % 2) )
    {
        /* Add icon photos */
        userPass.addFile(":/Images/sad.png");
        /* Password is hidden */
        ui->passLineEdit->setEchoMode(QLineEdit::Password);
    }
    /* Add actions */
    ui->passLineEdit->addAction(userPass, QLineEdit::LeadingPosition);
    state++;
}

void PassDialog::on_back_button_clicked()
{
    this->reject();
}
