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
//    float alp[128][128];
};


class Chead
{

public:

    Chead( QString s_filepath);
    ~Chead();

    void readheads();
    QVector<Hdata> getdatas();

    void show2dLeft(GLint nlevel,GLfloat translatef_x,GLfloat translatef_y,GLfloat translatef_z);
    void show2dRight(GLint nlevel,GLfloat translatef_x,GLfloat translatef_y,GLfloat translatef_z);
    void show2dBack(GLint nlevel,GLfloat translatef_x,GLfloat translatef_y,GLfloat translatef_z);
    void show2dAhead(GLint nlevel,GLfloat translatef_x,GLfloat translatef_y,GLfloat translatef_z);
    void show2dTop(GLint nlevel,GLfloat translatef_x,GLfloat translatef_y,GLfloat translatef_z);
    void show2dBelow(GLint nlevel,GLfloat translatef_x,GLfloat translatef_y,GLfloat translatef_z);

    void show3d(bool bOnlySkull=true,bool bframe=true,
                GLfloat translatef_x=0,GLfloat translatef_y=0,GLfloat translatef_z=0,
                GLfloat rotatef_x=0,GLfloat rotatef_y=0,GLfloat rotatef_z=0);

private:
    GLfloat getAlpha(unsigned char vhd_data,unsigned char s_alp,bool bOnlySkull,
                     GLfloat nAlp1=0.035,GLfloat nAlp2=0.015,GLfloat nAlp3=0.08);

    QString ms_filepath;
    QVector<Hdata> vhd;

};

#endif // CHEAD_H
