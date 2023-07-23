#include "processthread.h"
#include "preprocessing.h"

ProcessThread::ProcessThread(QString path):
    m_path(path)
{

}

void ProcessThread::run()
{
    QProcess process;
    process.setWorkingDirectory(CVISION_MODELS_DIRECTORY);
    process.start("python3", QStringList() << "-u" << m_path);
    process.waitForFinished();
}
