#ifndef WRITETHREAD_H
#define WRITETHREAD_H

#include <QObject>
#include <QtCore>
#include <QThread>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>
#include "structbody.h"

using namespace cv;
using namespace std;

class WriteThread : public QThread
{
    Q_OBJECT
public:
    explicit WriteThread();
    ~WriteThread();
    void run();
    void stop();
private:
    volatile bool writeStopped;
    volatile bool write;
    bool upWrite;
    vector<Mat> rgbVector;
    vector<Mat> depthVector;
    vector<StructBody> skeletVector;
    string dir;
    string rgb_dir;
    string depth_dir;
    struct JointBody{
        bool trackingState[24];
        float X[24];
        float Y[24];
        float Z[24];
    };

signals:
    void writeFinished();
public slots:
    void setInfo(vector<Mat> *, vector<Mat> *, vector<StructBody> *, QString );
    void uprWrite(bool checked);
};

#endif // WRITETHREAD_H
