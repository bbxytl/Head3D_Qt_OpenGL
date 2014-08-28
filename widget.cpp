#include <QKeyEvent>
#include "widget.h"
#include "ui_widget.h"
#include "nehewidget.h"
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    setFixedSize(577,397);
    ui->setupUi(this);    
}

Widget::~Widget()
{
    delete ui;    
}

void Widget::on_pushButton_clicked()
{
    this->close();
}

void Widget::keyPressEvent(QKeyEvent *e)
{
    if(e->key()==Qt::Key_W)
    {
        this->close();
    }
}
