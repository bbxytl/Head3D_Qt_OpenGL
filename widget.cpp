#include <QKeyEvent>
#include "widget.h"
#include "ui_widget.h"
#include "nehewidget.h"
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    setFixedSize(639,637);
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

//void Widget::closeEvent(QCloseEvent *e)
//{
//    if(bfirst)
//    {
//        NeHeWidget w( 0, 0, true );
//        w.show();
//        bfirst=!bfirst;
//    }
//}

//void Widget::setFirst(bool bf)
//{
//    bfirst=bf;
//}
