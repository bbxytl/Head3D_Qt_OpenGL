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

    bool isClose();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Widget *ui;
    bool bclose;
};

#endif // WIDGET_H
