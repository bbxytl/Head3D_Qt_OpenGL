#include "dialog.h"
#include "ui_dialog.h"


Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::initcb(int showAngle)
{
    ui->comboBox->clear();
    switch (showAngle) {
    case 0:
        showAngle=0;

        break;
    case 1:
        showAngle=128;
        break;
    case 2:
        showAngle=128;
        break;
    case 3:
        showAngle=128;
        break;
    case 4:
        showAngle=128;
        break;
    case 5:
        showAngle=113;
        break;
    case 6:
        showAngle=113;
        break;
    }
    if(showAngle!=0)
        for(int i=1;i<=showAngle;i++)
            ui->comboBox->addItem(QString::number(i));
    else
    {
        ui->comboBox->addItem("Ahead");
        ui->comboBox->addItem("Back");
        ui->comboBox->addItem("Left");
        ui->comboBox->addItem("Right");
        ui->comboBox->addItem("Top");
        ui->comboBox->addItem("Below");
    }
    ui->comboBox->setCurrentIndex(0);
}

void Dialog::on_buttonBox_clicked(QAbstractButton *button)
{
    const GLint info=ui->comboBox->currentIndex();
    emit infoSend(info);

}
