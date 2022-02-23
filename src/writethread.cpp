#include "writethread.h"

WriteThread::WriteThread()
{
    writeStopped = false;
    write = false;
    upWrite = false;
}

WriteThread::~WriteThread()
{
    this->terminate();
}

void WriteThread::run()
{
    while(!writeStopped){
        if(write){
            if(!rgbVector.empty())
                for(size_t i = rgbVector.size(); i != 0; i--){
                    rgb_dir = dir+"/RGB/"+QString::number(rgbVector.size()).toStdString()+".png";
                    imwrite(rgb_dir, rgbVector.back());
                    rgbVector.pop_back();
                }

            if(!depthVector.empty())
                for(size_t i = depthVector.size(); i != 0; i--){
                    depth_dir = dir+"/Depth/"+QString::number(depthVector.size()).toStdString()+".png";
                    imwrite(depth_dir, depthVector.back());
                    depthVector.pop_back();
                }

            if(!skeletVector.empty() && !upWrite){
                for(size_t i = skeletVector.size(); i != 0; i--){
                    QString qdir = QString::fromStdString(dir);
                    QFile file3D(qdir+"/Skelet/"+QString::number(skeletVector.size())+"_3D"+".txt");
                    file3D.open(QFile::WriteOnly | QFile::Text);
                    QTextStream out(&file3D);
                    for(size_t x = 0; x <= 24; x++){
                        out << x << " " << skeletVector.back().joint.X[x] << " " <<
                               skeletVector.back().joint.Y[x] << " " <<
                               skeletVector.back().joint.Z[x] << " " << skeletVector.back().joint.trackingState[x] << endl;
                    }
                    file3D.flush();
                    file3D.close();

                    QFile file2D(qdir+"/Skelet/"+QString::number(skeletVector.size())+"_2D"+".txt");
                    file2D.open(QFile::WriteOnly | QFile::Text);
                    QTextStream out2(&file2D);
                    for(size_t x = 0; x <= 24; x++){
                        out2 << x << " " << skeletVector.back().joint.xColor[x] << " " <<
                               skeletVector.back().joint.yColor[x] << endl;
                    }
                    file2D.flush();
                    file2D.close();

                    skeletVector.pop_back();
                }
            }
            else if (!skeletVector.empty()) {
                for(size_t i = skeletVector.size(); i != 0; i--){
                    QString qdir = QString::fromStdString(dir);
                    QFile file3D(qdir+"/Skelet/"+QString::number(skeletVector.size())+"_3D"+".txt");
                    file3D.open(QFile::WriteOnly | QFile::Text);
                    QTextStream out(&file3D);

                        out << 3 << " " << skeletVector.back().joint.X[3] << " " << skeletVector.back().joint.Y[3] << " " <<
                               skeletVector.back().joint.Z[3] << " " << skeletVector.back().joint.trackingState[3] << endl;

                        out << 2 << " " << skeletVector.back().joint.X[2] << " " << skeletVector.back().joint.Y[2] << " " <<
                               skeletVector.back().joint.Z[2] << " " << skeletVector.back().joint.trackingState[2] << endl;

                        out << 20 << " " << skeletVector.back().joint.X[20] << " " << skeletVector.back().joint.Y[20] << " " <<
                               skeletVector.back().joint.Z[20] << " " << skeletVector.back().joint.trackingState[20] << endl;

                        out << 4 << " " << skeletVector.back().joint.X[4] << " " << skeletVector.back().joint.Y[4] << " " <<
                               skeletVector.back().joint.Z[4] << " " << skeletVector.back().joint.trackingState[4] << endl;

                        out << 5 << " " << skeletVector.back().joint.X[5] << " " << skeletVector.back().joint.Y[5] << " " <<
                               skeletVector.back().joint.Z[5] << " " << skeletVector.back().joint.trackingState[5] << endl;

                        out << 6 << " " << skeletVector.back().joint.X[6] << " " << skeletVector.back().joint.Y[6] << " " <<
                               skeletVector.back().joint.Z[6] << " " << skeletVector.back().joint.trackingState[6] << endl;

                        out << 7 << " " << skeletVector.back().joint.X[7] << " " << skeletVector.back().joint.Y[7] << " " <<
                               skeletVector.back().joint.Z[7] << " " << skeletVector.back().joint.trackingState[7] << endl;

                        out << 21 << " " << skeletVector.back().joint.X[21] << " " << skeletVector.back().joint.Y[21] << " " <<
                               skeletVector.back().joint.Z[21] << " " << skeletVector.back().joint.trackingState[21] << endl;

                        out << 22 << " " << skeletVector.back().joint.X[22] << " " << skeletVector.back().joint.Y[22] << " " <<
                               skeletVector.back().joint.Z[22] << " " << skeletVector.back().joint.trackingState[22] << endl;

                        out << 1 << " " << skeletVector.back().joint.X[1] << " " << skeletVector.back().joint.Y[1] << " " <<
                               skeletVector.back().joint.Z[1] << " " << skeletVector.back().joint.trackingState[1] << endl;

                        out << 8 << " " << skeletVector.back().joint.X[8] << " " << skeletVector.back().joint.Y[8] << " " <<
                               skeletVector.back().joint.Z[8] << " " << skeletVector.back().joint.trackingState[8] << endl;

                        out << 9 << " " << skeletVector.back().joint.X[9] << " " << skeletVector.back().joint.Y[9] << " " <<
                               skeletVector.back().joint.Z[9] << " " << skeletVector.back().joint.trackingState[9] << endl;

                        out << 10 << " " << skeletVector.back().joint.X[10] << " " << skeletVector.back().joint.Y[10] << " " <<
                               skeletVector.back().joint.Z[10] << " " << skeletVector.back().joint.trackingState[10] << endl;

                        out << 24 << " " << skeletVector.back().joint.X[24] << " " << skeletVector.back().joint.Y[24] << " " <<
                               skeletVector.back().joint.Z[24] << " " << skeletVector.back().joint.trackingState[24] << endl;

                        out << 11 << " " << skeletVector.back().joint.X[11] << " " << skeletVector.back().joint.Y[11] << " " <<
                               skeletVector.back().joint.Z[11] << " " << skeletVector.back().joint.trackingState[11] << endl;

                        out << 23 << " " << skeletVector.back().joint.X[23] << " " << skeletVector.back().joint.Y[23] << " " <<
                               skeletVector.back().joint.Z[23] << " " << skeletVector.back().joint.trackingState[23] << endl;

                    file3D.flush();
                    file3D.close();

                    QFile file2D(qdir+"/Skelet/"+QString::number(skeletVector.size())+"_2D"+".txt");
                    file2D.open(QFile::WriteOnly | QFile::Text);
                    QTextStream out2(&file2D);

                        out2 << 3 << " " << skeletVector.back().joint.xColor[3] << " " << skeletVector.back().joint.yColor[3] << endl;

                        out2 << 2 << " " << skeletVector.back().joint.xColor[2] << " " << skeletVector.back().joint.yColor[2] << endl;

                        out2 << 20 << " " << skeletVector.back().joint.xColor[20] << " " << skeletVector.back().joint.yColor[20] << endl;

                        out2 << 4 << " " << skeletVector.back().joint.xColor[4] << " " << skeletVector.back().joint.yColor[4] << endl;

                        out2 << 5 << " " << skeletVector.back().joint.xColor[5] << " " << skeletVector.back().joint.yColor[5] << endl;

                        out2 << 6 << " " << skeletVector.back().joint.xColor[6] << " " << skeletVector.back().joint.yColor[6] << endl;

                        out2 << 7 << " " << skeletVector.back().joint.xColor[7] << " " << skeletVector.back().joint.yColor[7] << endl;

                        out2 << 21 << " " << skeletVector.back().joint.xColor[21] << " " << skeletVector.back().joint.yColor[21] << endl;

                        out2 << 22 << " " << skeletVector.back().joint.xColor[22] << " " << skeletVector.back().joint.yColor[22] << endl;

                        out2 << 1 << " " << skeletVector.back().joint.xColor[1] << " " << skeletVector.back().joint.yColor[1] << endl;

                        out2 << 8 << " " << skeletVector.back().joint.xColor[8] << " " << skeletVector.back().joint.yColor[8] << endl;

                        out2 << 9 << " " << skeletVector.back().joint.xColor[9] << " " << skeletVector.back().joint.yColor[9] << endl;

                        out2 << 10 << " " << skeletVector.back().joint.xColor[10] << " " << skeletVector.back().joint.yColor[10] << endl;

                        out2 << 24 << " " << skeletVector.back().joint.xColor[24] << " " << skeletVector.back().joint.yColor[24] << endl;

                        out2 << 11 << " " << skeletVector.back().joint.xColor[11] << " " << skeletVector.back().joint.yColor[11] << endl;

                        out2 << 23 << " " << skeletVector.back().joint.xColor[23] << " " << skeletVector.back().joint.yColor[23] << endl;

                    file2D.flush();
                    file2D.close();

                    skeletVector.pop_back();
                }

            }
            emit writeFinished();
            write = false;
        }
    }
    writeStopped = false;
}

void WriteThread::stop()
{
    writeStopped = true;
}

void WriteThread::setInfo(vector<Mat> *rgbVec, vector<Mat> *depthVec, vector<StructBody> *skeletVec, QString directory)
{
    dir = directory.toStdString();
    this->rgbVector = *rgbVec;
    this->depthVector = *depthVec;
    this->skeletVector = *skeletVec;
    write = true;
}

void WriteThread::uprWrite(bool checked)
{
    upWrite = checked;
}
