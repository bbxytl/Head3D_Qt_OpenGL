#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

//    void closeEvent(QCloseEvent *e);

//    void setFirst(bool bfirst);

    void keyPressEvent(QKeyEvent *e);
private slots:
    void on_pushButton_clicked();

private:
    Ui::Widget *ui;
//    bool bfirst;

};

#endif // WIDGET_H
