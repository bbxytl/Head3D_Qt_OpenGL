
#include "chead.h"


Chead::Chead(QString s_filepath)
{
    ms_filepath=s_filepath;
    vhd.clear();
}
Chead::~Chead()
{

}

void Chead::readheads()
{
    QFile file(ms_filepath);
    if(file.open(QFile::ReadOnly))
    {        
        QDataStream sm_data(&file);
        sm_data.setVersion(QDataStream::Qt_5_3);        
            for(int i=0;i<113;i++)
            {
                Hdata tmpdata;
                for(int j=0;j<128;j++)
                {
                    for(int k=0;k<128;k++)
                    {
                        sm_data>>tmpdata.data[j][k];
                    }
                }
                vhd.append(tmpdata);
            }
    }

    file.close();
}

void Chead::optdatas()
{
   for(int k=0;k<113;k++)
       for(int i=0;i<128;i++)
           for(int j=0;j<128;j++)
           {
               if(vhd[k].data[i][j]<140)
                   vhd[k].data[i][j]=0;
           }
}

QVector<Hdata> Chead::getdatas()
{
    return vhd;
}

void Chead::show2dAhead()
{

}

void Chead::show2dBack()
{

}

void Chead::show2dBelow()
{

}

void Chead::show2dLeft()
{

}

void Chead::show2dRight()
{

}

void Chead::show2dTop()
{

}

void Chead::show3d(GLfloat translatef_x,GLfloat translatef_y,GLfloat translatef_z,
                   GLfloat rotatef_angle,GLfloat rotatef_x,GLfloat rotatef_y,GLfloat rotatef_z)
{
    glTranslatef( translatef_x, translatef_y, translatef_z );
    glRotatef(rotatef_angle,rotatef_x,rotatef_y,rotatef_z);

    glBegin(GL_QUADS);
        QVector<Hdata> vdata=getdatas();
        int ct=vdata.count();
        for(int v=0;v<ct-1-1;v++)
        {
            int i,j;
            for(i=0;i<127;i++)
            {
                for(j=0;j<127;j++)
                {

                    GLfloat x0,x1,y0,y1,z0,z1,rgb;
                    x0=i/128.0; x1=(i+1)/128.0;
                    y0=j/128.0; y1=(j+1)/128.0;
                    z0=v/113.0; z1=(v+1)/113.0;
                    rgb=vdata[v].data[i][j];
                    if(rgb<140)continue;
                    rgb=vdata[v].data[i][j]/255.0;        glColor3f(rgb,rgb,rgb);   glVertex3f(x0,y0,z0);
                    rgb=vdata[v].data[i+1][j]/255.0;      glColor3f(rgb,rgb,rgb);   glVertex3f(x1,y0,z0);
                    rgb=vdata[v].data[i+1][j+1]/255.0;    glColor3f(rgb,rgb,rgb);   glVertex3f(x1,y1,z0);
                    rgb=vdata[v].data[i][j+1]/255.0;      glColor3f(rgb,rgb,rgb);   glVertex3f(x0,y1,z0);
                    //2
                    rgb=vdata[v].data[i][j]/255.0;        glColor3f(rgb,rgb,rgb);   glVertex3f(x0,y0,z0);
                    rgb=vdata[v].data[i][j+1]/255.0;      glColor3f(rgb,rgb,rgb);   glVertex3f(x0,y1,z0);
                    rgb=vdata[v+1].data[i][j+1]/255.0;    glColor3f(rgb,rgb,rgb);   glVertex3f(x0,y1,z1);
                    rgb=vdata[v+1].data[i][j]/255.0;      glColor3f(rgb,rgb,rgb);   glVertex3f(x0,y0,z1);
                    //3
                    rgb=vdata[v+1].data[i][j]/255.0;      glColor3f(rgb,rgb,rgb);   glVertex3f(x0,y0,z1);
                    rgb=vdata[v+1].data[i+1][j]/255.0;    glColor3f(rgb,rgb,rgb);   glVertex3f(x1,y0,z1);
                    rgb=vdata[v+1].data[i+1][j+1]/255.0;  glColor3f(rgb,rgb,rgb);   glVertex3f(x1,y1,z1);
                    rgb=vdata[v+1].data[i][j+1]/255.0;    glColor3f(rgb,rgb,rgb);   glVertex3f(x0,y1,z1);
                    //4
                    rgb=vdata[v].data[i+1][j]/255.0;        glColor3f(rgb,rgb,rgb);   glVertex3f(x1,y0,z0);
                    rgb=vdata[v].data[i+1][j+1]/255.0;      glColor3f(rgb,rgb,rgb);   glVertex3f(x1,y1,z0);
                    rgb=vdata[v+1].data[i+1][j+1]/255.0;    glColor3f(rgb,rgb,rgb);   glVertex3f(x1,y1,z1);
                    rgb=vdata[v+1].data[i+1][j]/255.0;      glColor3f(rgb,rgb,rgb);   glVertex3f(x1,y0,z1);
                    //5
                    rgb=vdata[v+1].data[i][j]/255.0;      glColor3f(rgb,rgb,rgb);   glVertex3f(x0,y0,z1);
                    rgb=vdata[v+1].data[i+1][j]/255.0;    glColor3f(rgb,rgb,rgb);   glVertex3f(x1,y0,z1);
                    rgb=vdata[v].data[i+1][j]/255.0;      glColor3f(rgb,rgb,rgb);   glVertex3f(x1,y0,z0);
                    rgb=vdata[v].data[i][j]/255.0;        glColor3f(rgb,rgb,rgb);   glVertex3f(x0,y0,z0);
                    //6
                    rgb=vdata[v].data[i+1][j+1]/255.0;      glColor3f(rgb,rgb,rgb);   glVertex3f(x1,y1,z0);
                    rgb=vdata[v].data[i][j+1]/255.0;        glColor3f(rgb,rgb,rgb);   glVertex3f(x0,y1,z0);
                    rgb=vdata[v+1].data[i][j+1]/255.0;      glColor3f(rgb,rgb,rgb);   glVertex3f(x0,y1,z1);
                    rgb=vdata[v+1].data[i+1][j+1]/255.0;    glColor3f(rgb,rgb,rgb);   glVertex3f(x1,y1,z1);

                }
            }
        }

    glEnd();
}
