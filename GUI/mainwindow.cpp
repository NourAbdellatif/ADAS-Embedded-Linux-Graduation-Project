#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QProcess>
#include <QSettings>


// Comment 1
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /* Take all readings immediately first */
    Clock();
    ReadTempAndHumidity();

    /* Clock */
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()),this,SLOT(Clock()));
    timer->start(1000);

    /* Temp and humidity */
    tempTimer = new QTimer(this);
    connect(tempTimer, SIGNAL(timeout()),this,SLOT(ReadTempAndHumidity()));
    tempTimer->start(5000);

    /* Remove window title */
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::CustomizeWindowHint);

    /* Construct any dialogs here to avoid re-construction */
    dialog_customer = new CustomerDialog(this);
    dialog_info = new infoDialog(this);
}

MainWindow::~MainWindow()
{
    qDebug() << "Main destructor call";
    delete ui;
    delete dialog_customer;
    delete dialog_info;
}

void MainWindow::Clock()
{
    QTime time = QTime::currentTime();
    QString noon = "A";
    if(time.hour()>12)
    {
        time.setHMS(time.hour()-12,time.minute(),time.second());
        noon = "PM";
    }
    QString time_text = time.toString("hh : mm : ss "+ noon);
    ui->time_label->setText(time_text);
}

void MainWindow::SetTempAndHumidityIcons()
{
   int tempReading = ui->temperature_label->text().toInt();
   QPixmap pixmap;
   if(tempReading < 15)
   {
       pixmap.load(":/Images/snow.png");
   }
   else if(tempReading < 25)
   {
       pixmap.load(":/Images/cloudy.png");

   }
   else
   {
       pixmap.load(":/Images/sun.png");
   }
   QIcon icon(pixmap);
   ui->tempImg->setIcon(icon);
}

void MainWindow::ReadTempAndHumidity()
{
    QProcess process;
    QStringList args;
//    args << "cat" << "/home/hussam/test_file";
    args << "cat" << "/dev/dht11km";
    process.start("cat", args);
    if (!process.waitForFinished())
    {
        qDebug() << "Error running command.";
        return;
    }
    QString output = process.readAll();
    /* Extract temp and humidity from QString output */
    QList<double> numbers;
    QRegularExpression re("\\d+(?:\\.\\d+)?"); // regular expression to match numbers
    QRegularExpressionMatchIterator i = re.globalMatch(output);
    while (i.hasNext())
    {
        QRegularExpressionMatch match = i.next();
        QString number_str = match.captured(0);
        double number = number_str.toDouble();
        numbers.append(number);
    }
    double tempReading  = numbers[0];
    double humidityReading = numbers[1];
    /* Don't print if the result of cat /dev/dht11km is buggy */
    if( !( (tempReading <= 0.1) || (humidityReading <= 0.1) ) )
    {
        ui->temperature_label->setNum(tempReading);
        ui->humidity_label-> setNum(humidityReading);
        SetTempAndHumidityIcons();
    }
}

void MainWindow::on_settings_button_clicked()
{
    /* Show the dialog */
    dialog_customer->exec();
}

void MainWindow::on_app_button_clicked()
{
    static int toggle = 1;
    if(toggle % 2)
    {
        ui->app_button->setStyleSheet("background-color: black;");
        QSettings settings("Used", "Saved");
        QString index = "Current %1";
        settings.beginGroup("Used");
        QString savedPath = settings.value( index.arg(QString::number(1)) ).toString();
        settings.endGroup();
        /* Run the selected model */
        thread = new ProcessThread(savedPath);
        thread->start();
    }
    else
    {
        /* Terminate the current model */
//        delete thread;
        thread->terminate();
        ui->app_button->setStyleSheet("background-color: transparent;");
//        delete thread;
    }
    toggle++;
}


void MainWindow::on_back_button_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_back_button_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_back_button_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_back_button_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_calendar_button_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}


void MainWindow::on_Info_button_clicked()
{
    /* Show the dialog */
    dialog_info->exec();
}

