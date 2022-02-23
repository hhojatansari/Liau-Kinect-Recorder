#ifndef CREATEPROJECT_H
#define CREATEPROJECT_H

#include <QDialog>
#include <QFileDialog>
#include <fstream>
#include <iostream>

using namespace std;
namespace Ui {
class CreateProject;
}

class CreateProject : public QDialog
{
    Q_OBJECT

public:
    explicit CreateProject(QWidget *parent = 0);
    ~CreateProject();

private slots:

    void on_pb_selectDir_clicked();

    void on_pb_create_clicked();

signals:
    void createPrjct(QString &, QString &);
private:
    Ui::CreateProject *ui;
    QString directory;
    QString proName;
    int frameRate;
    int scale;
    int recordNumber;
    bool rgbCheckBox;
    bool depthCheckBox;
    bool skeletCheckBox;
    bool up;
};

#endif // CREATEPROJECT_H
