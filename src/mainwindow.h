#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <QDir>
#include <QFileDialog>
#include "timethread.h"
#include "camerathread.h"
#include "writethread.h"
#include "createproject.h"
#include <fstream>
#include <string>

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();

    void updateISLFile();

    void loadListView();

    void showImage();

    void imgIndexCounter(int);

    void loadCoordinate();
    void drawPoints();

    CameraThread *camera;
    TimeThread *time;
    WriteThread *write;
    CreateProject createProject;

signals:
    void showUpper(bool checked);
private slots:

    void on_pb_record_clicked();

    void on_pb_about_clicked();

    void on_go_dir_clicked();

    void on_setInfo_clicked();

    void on_pb_exit_clicked();

    void on_chb_upper_clicked(bool checked);

    void loadPrjct(QString &, QString &);

    void on_actionCreate_New_Project_triggered();

    void on_actionOpen_Project_triggered();

    void on_list_record_currentTextChanged(const QString &currentText);

    void on_pb_next1_clicked();

    void on_pb_next2_clicked();

    void on_pb_previous1_clicked();

    void on_pb_previous2_clicked();

    void on_pb_next3_clicked();

    void on_pb_previous3_clicked();

private:
    Ui::MainWindow *ui;

    QString directory;
    QString proName;
    QString recordText;
    int recordSize;
    int imgIndex;
    int frameRate;
    int scale;
    int recordNumber;
    volatile bool isRecording;
    volatile bool ready; // for start/stop pb
    volatile bool changeInfo; // for set/change Info pb
    bool rgbCheckBox;
    bool depthCheckBox;
    bool skeletCheckBox;
    bool up;
    int xColor[24];
    int yColor[24];
    Mat src;
};

#endif // MAINWINDOW_H
