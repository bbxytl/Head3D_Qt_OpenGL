#ifndef CHEAD_H
#define CHEAD_H

#include<QFile>
#include<QDataStream>
#include<QVector>
#include <qgl.h>
#include <GL/glu.h>

struct Hdata
{
    unsigned char data[128][128];
};


class Chead
{

public:

    Chead( QString s_filepath);
    ~Chead();

    void readheads();
    QVector<Hdata> getdatas();
    void optdatas();

    void show2dLeft();
    void show2dRight();
    void show2dBack();
    void show2dAhead();
    void show2dTop();
    void show2dBelow();

    void show3d(GLfloat translatef_x=0,GLfloat translatef_y=0,GLfloat translatef_z=0,
                GLfloat rotatef_angle=0,GLfloat rotatef_x=0,GLfloat rotatef_y=0,GLfloat rotatef_z=0);

private:
    QString ms_filepath;
    QVector<Hdata> vhd;
};

#endif // CHEAD_H
