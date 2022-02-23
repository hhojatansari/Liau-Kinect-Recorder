#include "createproject.h"
#include "ui_createproject.h"

CreateProject::CreateProject(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateProject)
{
    ui->setupUi(this);

}

CreateProject::~CreateProject()
{
    delete ui;
}


void CreateProject::on_pb_selectDir_clicked()
{
    directory = QFileDialog::getExistingDirectory(this);
    if( directory.isEmpty() )
        return;
    ui->le_proDir->setText(directory);
}

void CreateProject::on_pb_create_clicked()
{
    proName = ui->le_proName->text();
    recordNumber = ui->le_record->text().toInt();
    frameRate = ui->le_frameRate->text().toInt();
    rgbCheckBox = ui->chb_rgb->checkState();
    depthCheckBox = ui->chb_depth->checkState();
    skeletCheckBox = ui->chb_skelet->checkState();
    up = ui->chb_up->checkState();

    QDir(directory+"/").mkdir(proName);

    cout << "on_pb_create_clicked() : " << directory.toStdString() << endl;

    fstream file;
    file.open(directory.toStdString()+"/"+proName.toStdString()+"/"+proName.toStdString()+".isl");
    if (!file)
        file.open(directory.toStdString()+"/"+proName.toStdString()+"/"+proName.toStdString()+".isl",  fstream::in | fstream::out | fstream::trunc);
    file << proName.toStdString() << endl;
    file << recordNumber << endl;
    file << frameRate << endl;
    file << rgbCheckBox << " " << depthCheckBox << " " << skeletCheckBox << endl;
    file << up ;
    file.close();
    QString url = directory+"/"+proName;
    emit createPrjct(url, proName);
    CreateProject::reject();
}
