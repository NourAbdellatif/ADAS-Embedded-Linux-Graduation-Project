#include "infodialog.h"
#include "ui_infodialog.h"
#include <QDebug>
#include <QProcess>
#include <QTimer>

infoDialog::infoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::infoDialog)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::CustomizeWindowHint);

    QTimer::singleShot(3000, [&]()
    {
        // Run the 'ifconfig' command and capture its output
        QProcess process;
        process.start("ifconfig");
        process.waitForFinished();

        // Store the IP of the RPi4
        QString targetID;

        // Read the output of the command
        QString output = process.readAllStandardOutput();

        // Split the output into lines
        QStringList lines = output.split(QRegExp("[\r\n]"), QString::SkipEmptyParts);
        qDebug() << lines;
        // Search for the 'wlan0' string and extract the IPv4 address
        for (int i = 0; i < lines.size(); i++)
        {
            if (lines[i].contains("wl"))
            {
                QStringList tokens = lines[i+1].split(" ");
                qDebug() << tokens;
                for (int j = 0; j < tokens.size(); j++)
                {
                    if (tokens[j] == "inet")
                    {
                        qDebug() << tokens[j+1];
                        targetID.remove(QChar::fromLatin1('\n'));
                        qDebug() << targetID;
                        targetID = tokens[j+1].remove("addr:");
                        qDebug() << targetID;
                        targetID.toInt();
                        // 'ip' contains the IPv4 address
                        qDebug() << "IP address: " << targetID;
                    }
                }
            }
        }

        ui->label_11->setText(targetID);
    });
}

infoDialog::~infoDialog()
{
    delete ui;
}

void infoDialog::on_back_button_clicked()
{
    reject();
}
