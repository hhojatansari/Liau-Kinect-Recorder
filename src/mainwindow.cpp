#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>

void mkDir(QString&, int);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    isRecording = false;
    ready = false;
    changeInfo = true;
    rgbCheckBox = false;
    depthCheckBox = false;
    skeletCheckBox = false;
    up = false;
    recordNumber = 0;
    frameRate = 1;
    recordSize = 0;
    imgIndex = 1;
    
    QPixmap logo(":/image/img/logo.png");
    QPixmap veiw("C:/Users/hhak/Desktop/tools/1.png");
    ui->label_view->setPixmap(veiw);
    ui->logo->setPixmap(logo);
    ui->statusBar->showMessage("Wellcome");


    isRecording = false;
    time = new TimeThread();
    camera = new CameraThread();
    write = new WriteThread();
    connect(time, &TimeThread::timeStartSignal, camera, &CameraThread::cameraStartSlot);
    connect(time, &TimeThread::timeStopSignal, camera, &CameraThread::cameraStopSlot);
    connect(camera, &CameraThread::write, write, &WriteThread::setInfo);
    connect(write, &WriteThread::writeFinished, camera, &CameraThread::stopWrite);
    connect(this, &MainWindow::showUpper, camera, &CameraThread::showUpper);
    connect(this, &MainWindow::showUpper, write, &WriteThread::uprWrite);
    camera->start(QThread::HighestPriority);
    write->start(QThread::HighestPriority);

    connect(camera, &CameraThread::record_pb, this, &MainWindow::on_pb_record_clicked);
    connect(&createProject, &CreateProject::createPrjct, this, &MainWindow::loadPrjct);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateISLFile()
{
    std::ofstream ofs;
    ofs.open(directory.toStdString()+ "/" +proName.toStdString()+".isl", std::ofstream::out | std::ofstream::trunc);
    ofs.close();

    fstream file;
    file.open(directory.toStdString()+ "/" +proName.toStdString()+".isl");
    file << proName.toStdString() << endl;
    file << recordNumber+1 << endl;
    file << frameRate << endl;
    file << rgbCheckBox << " " << depthCheckBox << " " << skeletCheckBox << endl;
    file << up ;
    file.close();
}

void MainWindow::loadListView()
{
    ui->list_record->clear();
    QDir root(directory);
    QFileInfoList fList = root.entryInfoList(QDir::AllDirs | QDir::NoDotAndDotDot, QDir::DirsFirst);
    for(int i=0;i < fList.size(); ++i)
    {
        QFileInfo file = fList.at(i);
        if(file.isDir()){
            std::string str (file.absoluteFilePath().toStdString());
            std::size_t found = str.find_last_of("/\\");
            ui->list_record->addItem(QString::fromStdString(str.substr(found+1)));
        }
    }
}

void MainWindow::showImage()
{
    ui->statusBar->showMessage(QString::number(imgIndex));
    src = imread(directory.toStdString()+"/"+recordText.toStdString()+"/RGB/"+QString::number(imgIndex).toStdString()+".png", 1);
    loadCoordinate();
    drawPoints();
    cvtColor(src, src, CV_BGR2RGB);
    QPixmap p = QPixmap::fromImage(QImage((unsigned char*) src.data,
                                   src.cols, src.rows, QImage::Format_RGB888));
    p = p.scaledToWidth(500);
    ui->label_view->setPixmap(p);
}

void MainWindow::imgIndexCounter(int p)
{
    imgIndex += p;
    if(imgIndex > recordSize)
        imgIndex = recordSize;
    else if(imgIndex < 1)
        imgIndex = 1;
}

void MainWindow::loadCoordinate()
{
    fstream file;
    QString d = directory+"/"+recordText+"/Skelet/"+QString::number(imgIndex)+"_2D.txt";
    int index, x, y;
    file.open(d.toStdString());
    for(int i = 0; i <= 24; i++){
        file >> index >> x >> y;
        switch (index) {
        case 0:
            xColor[0] = x;
            yColor[0] = y;
            break;
        case 1:
            xColor[1] = x;
            yColor[1] = y;
            break;
        case 2:
            xColor[2] = x;
            yColor[2] = y;
            break;
        case 3:
            xColor[3] = x;
            yColor[3] = y;
            break;
        case 4:
            xColor[4] = x;
            yColor[4] = y;
            break;
        case 5:
            xColor[5] = x;
            yColor[5] = y;
            break;
        case 6:
            xColor[6] = x;
            yColor[6] = y;
            break;
        case 7:
            xColor[7] = x;
            yColor[7] = y;
            break;
        case 8:
            xColor[8] = x;
            yColor[8] = y;
            break;
        case 9:
            xColor[9] = x;
            yColor[9] = y;
            break;
        case 10:
            xColor[10] = x;
            yColor[10] = y;
            break;
        case 11:
            xColor[11] = x;
            yColor[11] = y;
            break;
        case 12:
            xColor[12] = x;
            yColor[12] = y;
            break;
        case 13:
            xColor[13] = x;
            yColor[13] = y;
            break;
        case 14:
            xColor[14] = x;
            yColor[14] = y;
            break;
        case 15:
            xColor[15] = x;
            yColor[15] = y;
            break;
        case 16:
            xColor[16] = x;
            yColor[16] = y;
            break;
        case 17:
            xColor[17] = x;
            yColor[17] = y;
            break;
        case 18:
            xColor[18] = x;
            yColor[18] = y;
            break;
        case 19:
            xColor[19] = x;
            yColor[19] = y;
            break;
        case 20:
            xColor[20] = x;
            yColor[20] = y;
            break;
        case 21:
            xColor[21] = x;
            yColor[21] = y;
            break;
        case 22:
            xColor[22] = x;
            yColor[22] = y;
            break;
        case 23:
            xColor[23] = x;
            yColor[23] = y;
            break;
        case 24:
            xColor[24] = x;
            yColor[24] = y;
            break;
        default:
            break;
        }
    }
        file.close();
}

void MainWindow::drawPoints()
{
    for(int i = 0; i <= 24; i++)
        circle(src, Point(xColor[i]*0.35, yColor[i]*0.35), 2, Scalar(0,0,255), 6, cv::LINE_AA);
}


void MainWindow::on_pb_record_clicked()
{
    if(!ready){
        QMessageBox::information(0, "Set Info","Set your project informatoin please.");
        return;
    }
    if( !isRecording ){
        isRecording = true;
        rgbCheckBox = ui->chb_rgb->checkState();
        depthCheckBox = ui->chb_depth->checkState();
        skeletCheckBox = ui->chb_skelet->checkState();
        recordNumber = ui->le_record->text().toInt();
        mkDir(directory, recordNumber);
        ui->pb_record->setText("Stop");
        ui->statusBar->showMessage("Recording ..");
        updateISLFile();
        time->getInformation(frameRate);
        camera->getInformation(directory, recordNumber, rgbCheckBox, depthCheckBox, skeletCheckBox);
        time->start(QThread::HighestPriority);
    }
    else{
        time->stop();
        isRecording = false;
        ui->pb_record->setText("Record");
        ui->statusBar->showMessage("Stopped !");
        recordNumber++;
        ui->le_record->setText(QString::number(recordNumber));
        loadListView();
    }
}



void MainWindow::on_pb_about_clicked()
{
    QMessageBox::information(0, "About", "<p>&nbsp;</p>\
            <p>This app is written by Hossein Hojat Ansari</p>\
            <ul>\
            <li>HHojatAnsari [at] Gmail.Com</li>\
            </ul>\
            <p>Thanks to Tsukasa Sugiura</p>\
            <ul>\
            <li>https://github.com/UnaNancyOwen</a></li>\
            </ul>\
            <p>&nbsp;</p>");
}

void MainWindow::on_go_dir_clicked()
{

    QString d = QFileDialog::getOpenFileName(this, tr("Open File"), directory, tr("ISL Files (*.isl)"));
    directory = QString::fromStdString(d.toStdString().substr(0, d.toStdString().find_last_of("\\/")));

    if( directory.isEmpty() )
        return;

    string projectName;
    fstream file;
    file.open(d.toStdString().c_str());
    file >> projectName;
    file >> recordNumber;
    file >> frameRate;
    file >> rgbCheckBox >> depthCheckBox >> skeletCheckBox;
    file >> up;
    file.close();

    emit showUpper(up);
    loadListView();

    ui->le_directory->setText(directory);
    ui->le_record->setText(QString::fromStdString(to_string(recordNumber)));
    ui->le_proName->setText(QString::fromStdString(projectName));
    ui->le_framerate->setText(QString::fromStdString(to_string(frameRate)));
    ui->statusBar->showMessage("Loaded");
    ui->chb_rgb->setChecked(rgbCheckBox);
    ui->chb_depth->setChecked(depthCheckBox);
    ui->chb_skelet->setChecked(skeletCheckBox);
    ui->chb_upper->setChecked(up);
}

void MainWindow::on_setInfo_clicked()
{
    if(isRecording)
    {
        QMessageBox::information(0, "Recording","you must stop recording.");
        return;
    }

    if(changeInfo){
        if(ui->le_proName->text().isEmpty() | ui->le_framerate->text().isEmpty() |
                ui->le_directory->text().isEmpty() | ui->le_record->text().isEmpty() |
                ((!ui->chb_rgb->checkState()) && (!ui->chb_depth->checkState()) &&
                 (!ui->chb_skelet->checkState())))
        {
            QMessageBox::information(0, "Project Info","Enter your project information please.");            
            return;
        }

        proName = ui->le_proName->text();
        frameRate = ui->le_framerate->text().toInt();
        recordNumber = ui->le_record->text().toInt();
        rgbCheckBox = ui->chb_rgb->checkState();
        depthCheckBox = ui->chb_depth->checkState();
        skeletCheckBox = ui->chb_skelet->checkState();
        up = ui->chb_upper->checkState();

        updateISLFile();

//        if(QDir(directory+"/"+proName).exists()){
//            QMessageBox::StandardButton reply;
//            reply = QMessageBox::question(this, "Exist", "This directory has existed. is there any problem?", QMessageBox::Yes|QMessageBox::No);
//            if(reply == 16384){
//                ui->statusBar->showMessage("Change your project's name.");
//                return;
//            }
//        }

        ready = true;
        changeInfo = false;

        ui->go_dir->setDisabled(true);
        ui->chb_rgb->setDisabled(true);
        ui->chb_depth->setDisabled(true);
        ui->chb_skelet->setDisabled(true);
        ui->le_proName->setDisabled(true);
        ui->le_framerate->setDisabled(true);
        ui->le_directory->setDisabled(true);
        ui->setInfo->setText("Change Info");
        ui->statusBar->showMessage("Ready");
    }
    else{
        ready = false;
        changeInfo = true;

        ui->setInfo->setText("Set Info");
        ui->go_dir->setDisabled(false);
        ui->chb_rgb->setDisabled(false);
        ui->chb_depth->setDisabled(false);
        ui->chb_skelet->setDisabled(false);
        ui->le_proName->setDisabled(false);
        ui->le_framerate->setDisabled(false);
        ui->le_directory->setDisabled(false);
    }
}

void MainWindow::on_pb_exit_clicked()
{
    camera->stop();
    time->stop();
    write->stop();
    camera->wait();
    time->wait();
    camera->terminate();
    time->terminate();
    write->terminate();
    QApplication::quit();
}

void MainWindow::on_chb_upper_clicked(bool checked)
{
    emit showUpper(checked);
}

void MainWindow::loadPrjct(QString & dir, QString & proName)
{
    directory = dir;
    dir = directory+"/"+proName+".isl";
    string projectName;
    fstream file;
    file.open(dir.toStdString().c_str());
    file >> projectName;
    file >> recordNumber;
    file >> frameRate;
    file >> rgbCheckBox >> depthCheckBox >> skeletCheckBox;
    file >> up;
    file.close();



    emit showUpper(up);

    ui->le_directory->setText(dir);
    ui->le_record->setText(QString::fromStdString(to_string(recordNumber)));
    ui->le_proName->setText(QString::fromStdString(projectName));
    ui->le_framerate->setText(QString::fromStdString(to_string(frameRate)));
    ui->statusBar->showMessage("Loaded");
    ui->chb_rgb->setChecked(rgbCheckBox);
    ui->chb_depth->setChecked(depthCheckBox);
    ui->chb_skelet->setChecked(skeletCheckBox);
    ui->chb_upper->setChecked(up);
}

void mkDir(QString& directory, int recordNumber){
    QDir(directory+"/").mkdir("Record"+QString::number(recordNumber));
    QDir(directory+"/"+"/Record"+QString::number(recordNumber)).mkdir("RGB");
    QDir(directory+"/"+"/Record"+QString::number(recordNumber)).mkdir("Depth");
    QDir(directory+"/"+"/Record"+QString::number(recordNumber)).mkdir("Skelet");
}

void MainWindow::on_actionCreate_New_Project_triggered()
{
    createProject.show();
}

void MainWindow::on_actionOpen_Project_triggered()
{
    on_go_dir_clicked();
}

void MainWindow::on_list_record_currentTextChanged(const QString &currentText)
{
    recordText = currentText;
    imgIndex = 1;
    QString dir = directory+"/"+currentText+"/RGB";
    QDir root(dir);
    QFileInfoList fList = root.entryInfoList(QDir::Files);
    recordSize = fList.size();
    if(recordSize < 1)
        return;
    showImage();
}

void MainWindow::on_pb_next1_clicked()
{
    if(recordSize < 1){
        ui->statusBar->showMessage("Record is empty..");
        return;
    }
    imgIndexCounter(1);
    showImage();
}

void MainWindow::on_pb_next2_clicked()
{
    if(recordSize < 1){
        ui->statusBar->showMessage("Record is empty..");
        return;
    }
    imgIndexCounter(5);
    showImage();
}

void MainWindow::on_pb_previous1_clicked()
{
    if(recordSize < 1){
        ui->statusBar->showMessage("Record is empty..");
        return;
    }
    imgIndexCounter(-1);
    showImage();
}

void MainWindow::on_pb_previous2_clicked()
{
    if(recordSize < 1){
        ui->statusBar->showMessage("Record is empty..");
        return;
    }
    imgIndexCounter(-5);
    showImage();
}

void MainWindow::on_pb_next3_clicked()
{
    if(recordSize < 1){
        ui->statusBar->showMessage("Record is empty..");
        return;
    }
    imgIndexCounter(10);
    showImage();
}

void MainWindow::on_pb_previous3_clicked()
{
    if(recordSize < 1){
        ui->statusBar->showMessage("Record is empty..");
        return;
    }
    imgIndexCounter(-10);
    showImage();
}
