#include "processthread.h"
#include "preprocessing.h"
#include <QDebug>

ProcessThread::ProcessThread(QString path):
    m_path(path)
{

}

void ProcessThread::run()
{
    qDebug() << m_path;

    // Create a QProcess object
    QProcess process;

    /* If the path is for a python code */
    if( !m_path.right(3).compare(".py") )
    {
        qDebug() << "I'm python";
        // Start the process
        process.start("python3", QStringList() << m_path);
    }
    else
    {
        qDebug() << "I'm C++";
        process.setWorkingDirectory(CVISION_MODELS_DIRECTORY);
        // Start the process
        process.start(m_path);
    }

    // Check if the process is not started
    if (!process.waitForStarted())
    {
        qDebug() << "Failed to start the process.";
        return;
    }

    // Keep the process running indefinitely
    while(true)
    {
        // Wait for a short duration to allow the process to continue executing
        QThread::msleep(100);
    }
}
