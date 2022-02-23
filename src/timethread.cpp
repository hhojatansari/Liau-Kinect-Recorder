#include "timethread.h"

TimeThread::TimeThread()
{
    stopped = false;
}

void TimeThread::run()
{
    this->setPriority(QThread::HighestPriority);

    while(!stopped){
        emit timeStartSignal();
        msleep(rate);
    }
    stopped = false;
}

void TimeThread::stop()
{
    stopped = true;
    emit timeStopSignal();
}

void TimeThread::getInformation(int rate)
{
    this->rate = 1000 / rate;
}


