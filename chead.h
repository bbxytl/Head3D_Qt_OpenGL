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

    void show2dLeft(GLint nlevel,GLboolean bOnlySkull,GLfloat translatef_x,GLfloat translatef_y,GLfloat translatef_z);
    void show2dRight(GLint nlevel,GLboolean bOnlySkull,GLfloat translatef_x,GLfloat translatef_y,GLfloat translatef_z);
    void show2dBack(GLint nlevel,GLboolean bOnlySkull,GLfloat translatef_x,GLfloat translatef_y,GLfloat translatef_z);
    void show2dAhead(GLint nlevel,GLboolean bOnlySkull,GLfloat translatef_x,GLfloat translatef_y,GLfloat translatef_z);
    void show2dTop(GLint nlevel,GLboolean bOnlySkull,GLfloat translatef_x,GLfloat translatef_y,GLfloat translatef_z);
    void show2dBelow(GLint nlevel,GLboolean bOnlySkull,GLfloat translatef_x,GLfloat translatef_y,GLfloat translatef_z);

    void show3d(GLboolean bOnlySkull,GLfloat translatef_x=0,GLfloat translatef_y=0,GLfloat translatef_z=0,
                GLfloat rotatef_angle=0,GLfloat rotatef_x=0,GLfloat rotatef_y=0,GLfloat rotatef_z=0);

private:
    QString ms_filepath;
    QVector<Hdata> vhd;
};

#endif // CHEAD_H
