#ifndef PROCESSTHREAD_H
#define PROCESSTHREAD_H

#include <QProcess>
#include <QThread>

class ProcessThread : public QThread
{
    Q_OBJECT

public:
    ProcessThread(QString path);

protected:
    void run() override;

private:
    QString m_path;
};

#endif // PROCESSTHREAD_H
