#ifndef TIMETHREAD_H
#define TIMETHREAD_H

#include <QObject>
#include <QtCore>
#include <QThread>
#include <iostream>
using namespace std;

class TimeThread : public QThread
{
    Q_OBJECT
public:
    explicit TimeThread();
    void run();
    void stop();
    void getInformation(int);

private:
    volatile bool stopped;
    int rate;

signals:
    void timeStartSignal();
    void timeStopSignal();

public slots:
};

#endif // TIMETHREAD_H
