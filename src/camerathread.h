#ifndef CAMERATHREAD_H
#define CAMERATHREAD_H

#include <QObject>
#include <QtCore>
#include <QThread>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <Windows.h>
#include <Kinect.h>
#include <vector>
#include <array>
#include <wrl/client.h>
#include <thread>
#include <chrono>
#include <ppl.h>
#include "util.h"
#include "structbody.h"
#include <QFile>
#include <QTextStream>

using namespace Microsoft::WRL;

using namespace cv;
using namespace std;

class CameraThread : public QThread
{
    Q_OBJECT
public:
    explicit CameraThread();
    ~CameraThread();
    void run();
    void stop();
    void getInformation(QString &, int, bool, bool, bool);
    MEMORYSTATUSEX memInfo;


private:
    //functions
    inline void getBodyIndex(const Joint &, const ColorSpacePoint &);
    inline void drawLines();
    void initialize();
    inline void initializeSensor();
    inline void initializeColor();
    inline void initializeBody();
    void finalize();
    void update();
    inline void updateDepth();
    inline void updateColor();
    inline void updateBody();
    void draw();
    inline void drawDepth();
    inline void initializeDepth();
    inline void drawColor();
    inline void drawBody();
    inline void drawEllipse( cv::Mat& image, const Joint& joint, const int radius, const cv::Vec3b& color, const int thickness = -1 );
    inline void drawHandState( cv::Mat& image, const Joint& joint, HandState handState, TrackingConfidence handConfidence );
    void show();
    inline void showBody();
    inline void showDepth();

    int counter;
    volatile bool recording;
    volatile bool stopped;
    volatile bool countFlag;
    volatile bool rgb_chb;
    volatile bool depth_chb;
    volatile bool skelet_chb;
    bool up;
    bool writeflag;
    bool waitForWriting;
    QString directory;
    QTextStream out;
    int recordNumber;
    ComPtr<IKinectSensor> kinect;
    ComPtr<ICoordinateMapper> coordinateMapper;
    ComPtr<IColorFrameReader> colorFrameReader;
    ComPtr<IBodyFrameReader> bodyFrameReader;
    std::vector<BYTE> colorBuffer;
    int xColor[24];
    int yColor[24];

    double rgbScale;
    int colorWidth;
    int colorHeight;
    unsigned int colorBytesPerPixel;
    cv::Mat colorMat;
    Mat bodyMat;
    cv::Mat resizeMat;
    Mat src;
    std::array<IBody*, BODY_COUNT> bodies = { nullptr };
    std::array<cv::Vec3b, BODY_COUNT> colors;
    ComPtr<IDepthFrameReader> depthFrameReader;
    std::vector<UINT16> depthBuffer;
    int depthWidth;
    int depthHeight;
    unsigned int depthBytesPerPixel;
    cv::Mat depthMat;
    cv::Mat scaleMat;
    StructBody Body;

    string rgb_dir;
    string depth_dir;
    string skelet_dir;
    vector<Mat> rgbVec;
    vector<Mat> depthVec;
    vector<StructBody> skeletVec;
signals:
    void write(vector<Mat>*, vector<Mat>*, vector<StructBody>*, QString);
    void record_pb();
public slots:
    void cameraStartSlot();
    void cameraStopSlot();
    void stopWrite();
    void showUpper(bool checked);

};

#endif // CAMERATHREAD_H
