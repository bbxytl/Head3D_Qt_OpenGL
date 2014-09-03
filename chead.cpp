
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

                        unsigned char tpdt;
                        float tpal;
                        tpdt=tmpdata.data[j][k];
                        tpal=0.0;
                        if(tpdt<10)  tpal=0;
                        else if(tpdt>=10&&tpdt<30) tpal=0.01;
                        else if(tpdt>=30&&tpdt<60) tpal=0.004*tpdt-0.11;
                        else if(tpdt>=60&&tpdt<140)tpal=0.003*tpdt-0.05;
                        else if(tpdt>=140&&tpdt<190) tpal=0.004*tpdt-0.12;
                        else if(tpdt>=190)tpal=0.004*tpdt-0.12;

                        tmpdata.alp[j][k]=tpal;
                    }
                }
                vhd.append(tmpdata);
            }
    }

    file.close();
}

QVector<Hdata> Chead::getdatas()
{
    return vhd;
}


void Chead::show2dAhead(GLint v,GLfloat translatef_x,GLfloat translatef_y,GLfloat translatef_z)
{
    glRotatef(90,1,0,0);
    glRotatef(90,0,0,1);
    glTranslatef( translatef_x, translatef_y, translatef_z );
    if(v<0)v+=128;
    v=v%128;


    GLfloat x0,y1,y0,z0,z1,rgb;

    glBegin(GL_QUADS);
    for(int i=1;i<127;i++)
        for(int j=1;j<112;j++)
        {
            x0=0;
            y0=i/128.0; y1=(i+1)/128.0;
            z0=j/113.0; z1=(j+1)/113.0;

            rgb=vhd[j].data[v][i]/255.0;             glColor3f(rgb,rgb,rgb);   glVertex3f(x0,y0,z0);
            rgb=vhd[j+1].data[v][i]/255.0;         glColor3f(rgb,rgb,rgb);   glVertex3f(x0,y0,z1);
            rgb=vhd[j+1].data[v][i+1]/255.0;     glColor3f(rgb,rgb,rgb);   glVertex3f(x0,y1,z1);
            rgb=vhd[j].data[v][i+1]/255.0;         glColor3f(rgb,rgb,rgb);   glVertex3f(x0,y1,z0);

        }
    glEnd();
    glBegin(GL_LINES);
        glColor3f(0,1,1);
        glVertex3f(0,0,0);          glVertex3f(0,1,0);
        glVertex3f(0,1,0);        glVertex3f(0,1,1);
        glVertex3f(0,1,1);      glVertex3f(0,0,1);
        glVertex3f(0,0,1);        glVertex3f(0,0,0);
    glEnd();
}

void Chead::show2dBack(GLint v,GLfloat translatef_x,GLfloat translatef_y,GLfloat translatef_z)
{
    glRotatef(90,1,0,0);
    glRotatef(-90,0,0,1);
    glTranslatef( translatef_x, translatef_y, translatef_z );
    if(v<0)v+=128;
    v=v%128;
    v=128-v;

    GLfloat x0,y1,y0,z0,z1,rgb;

    glBegin(GL_QUADS);
    for(int i=1;i<127;i++)
        for(int j=1;j<112;j++)
        {
            x0=0;
            y0=i/128.0; y1=(i+1)/128.0;
            z0=j/113.0; z1=(j+1)/113.0;

            rgb=vhd[j].data[v][i]/255.0;                 glColor3f(rgb,rgb,rgb);   glVertex3f(x0,y0,z0);
            rgb=vhd[j+1].data[v][i]/255.0;               glColor3f(rgb,rgb,rgb);   glVertex3f(x0,y0,z1);
            rgb=vhd[j+1].data[v][i+1]/255.0;             glColor3f(rgb,rgb,rgb);   glVertex3f(x0,y1,z1);
            rgb=vhd[j].data[v][i+1]/255.0;               glColor3f(rgb,rgb,rgb);   glVertex3f(x0,y1,z0);

        }
    glEnd();
    glBegin(GL_LINES);
        glColor3f(0,1,1);
        glVertex3f(0,0,0);      glVertex3f(0,1,0);
        glVertex3f(0,1,0);      glVertex3f(0,1,1);
        glVertex3f(0,1,1);      glVertex3f(0,0,1);
        glVertex3f(0,0,1);      glVertex3f(0,0,0);
    glEnd();
}

void Chead::show2dLeft(GLint v,GLfloat translatef_x,GLfloat translatef_y,GLfloat translatef_z)
{
    glRotatef(90,1,0,0);
    glRotatef(180,0,0,1);
    glTranslatef( translatef_x, translatef_y, translatef_z );
    if(v<0)v+=128;
    v=v%128;
    v=127-v;

    GLfloat x0,x1,y0,z0,z1,rgb;

    glBegin(GL_QUADS);
    for(int i=1;i<127;i++)
        for(int j=1;j<112;j++)
        {
            x0=i/128.0; x1=(i+1)/128.0;
            y0=0;
            z0=j/113.0; z1=(j+1)/113.0;

            rgb=vhd[j].data[i][v]/255.0;                 glColor3f(rgb,rgb,rgb);   glVertex3f(x0,y0,z0);
            rgb=vhd[j+1].data[i][v]/255.0;               glColor3f(rgb,rgb,rgb);   glVertex3f(x0,y0,z1);
            rgb=vhd[j+1].data[i+1][v]/255.0;             glColor3f(rgb,rgb,rgb);   glVertex3f(x1,y0,z1);
            rgb=vhd[j].data[i+1][v]/255.0;               glColor3f(rgb,rgb,rgb);   glVertex3f(x1,y0,z0);


        }
    glEnd();
    glBegin(GL_LINES);
        glColor3f(0,1,1);
        glVertex3f(0,0,0);      glVertex3f(0,0,1);
        glVertex3f(0,0,1);      glVertex3f(1,0,1);
        glVertex3f(1,0,1);      glVertex3f(1,0,0);
        glVertex3f(1,0,0);      glVertex3f(0,0,0);
    glEnd();
}

void Chead::show2dRight(GLint v,GLfloat translatef_x,GLfloat translatef_y,GLfloat translatef_z)
{    
    glRotatef(90,1,0,0);
    glTranslatef( translatef_x, translatef_y, translatef_z );
    if(v<0)v+=128;
    v=v%128;
    GLfloat x0,x1,y0,z0,z1,rgb;

    glBegin(GL_QUADS);
    for(int i=1;i<127;i++)
        for(int j=1;j<112;j++)
        {
            x0=i/128.0; x1=(i+1)/128.0;
            y0=0;
            z0=j/113.0; z1=(j+1)/113.0;

            rgb=vhd[j].data[i][v]/255.0;                 glColor3f(rgb,rgb,rgb);   glVertex3f(x0,y0,z0);
            rgb=vhd[j+1].data[i][v]/255.0;               glColor3f(rgb,rgb,rgb);   glVertex3f(x0,y0,z1);
            rgb=vhd[j+1].data[i+1][v]/255.0;             glColor3f(rgb,rgb,rgb);   glVertex3f(x1,y0,z1);
            rgb=vhd[j].data[i+1][v]/255.0;               glColor3f(rgb,rgb,rgb);   glVertex3f(x1,y0,z0);


        }
    glEnd();
    glBegin(GL_LINES);
        glColor3f(0,1,1);
        glVertex3f(0,0,0);      glVertex3f(0,0,1);
        glVertex3f(0,0,1);      glVertex3f(1,0,1);
        glVertex3f(1,0,1);      glVertex3f(1,0,0);
        glVertex3f(1,0,0);      glVertex3f(0,0,0);
    glEnd();
}

void Chead::show2dTop(GLint v,GLfloat translatef_x,GLfloat translatef_y,GLfloat translatef_z)
{
    glTranslatef( translatef_x, translatef_y, translatef_z );
    if(v<0)v+=113;
    v=v%113;
    GLfloat x0,x1,y0,y1,z0,rgb;

    glBegin(GL_QUADS);
    for(int i=1;i<127;i++)
        for(int j=1;j<127;j++)
        {
            x0=i/128.0; x1=(i+1)/128.0;
            y0=j/128.0; y1=(j+1)/128.0;
            z0=0;

            rgb=vhd[v].data[i][j]/255.0;                 glColor3f(rgb,rgb,rgb);   glVertex3f(x0,y0,z0);
            rgb=vhd[v].data[i+1][j]/255.0;               glColor3f(rgb,rgb,rgb);   glVertex3f(x1,y0,z0);
            rgb=vhd[v].data[i+1][j+1]/255.0;             glColor3f(rgb,rgb,rgb);   glVertex3f(x1,y1,z0);
            rgb=vhd[v].data[i][j+1]/255.0;               glColor3f(rgb,rgb,rgb);   glVertex3f(x0,y1,z0);


        }
    glEnd();
    glBegin(GL_LINES);
        glColor3f(0,1,1);
        glVertex3f(0,0,0);     glVertex3f(0,1,0);
        glVertex3f(0,1,0);     glVertex3f(1,1,0);
        glVertex3f(1,1,0);     glVertex3f(1,0,0);
        glVertex3f(1,0,0);     glVertex3f(0,0,0);
    glEnd();

}

void Chead::show2dBelow(GLint v,GLfloat translatef_x,GLfloat translatef_y,GLfloat translatef_z)
{
    glRotatef(180,1,0,0);
    glTranslatef( translatef_x, translatef_y, -translatef_z );
    if(v<0)v+=113;
    v=v%113;
    v=112-v;
    GLfloat x0,x1,y0,y1,z0,rgb;

    glBegin(GL_QUADS);
    for(int i=1;i<127;i++)
        for(int j=1;j<127;j++)
        {
            x0=i/128.0; x1=(i+1)/128.0;
            y0=j/128.0; y1=(j+1)/128.0;
            z0=0;

            rgb=vhd[v].data[i][j]/255.0;                 glColor3f(rgb,rgb,rgb);   glVertex3f(x0,y0,z0);
            rgb=vhd[v].data[i+1][j]/255.0;               glColor3f(rgb,rgb,rgb);   glVertex3f(x1,y0,z0);
            rgb=vhd[v].data[i+1][j+1]/255.0;             glColor3f(rgb,rgb,rgb);   glVertex3f(x1,y1,z0);
            rgb=vhd[v].data[i][j+1]/255.0;               glColor3f(rgb,rgb,rgb);   glVertex3f(x0,y1,z0);

        }
    glEnd();

    glBegin(GL_LINES);
        glColor3f(0,1,1);
        glVertex3f(0,0,0);     glVertex3f(0,1,0);
        glVertex3f(0,1,0);     glVertex3f(1,1,0);
        glVertex3f(1,1,0);     glVertex3f(1,0,0);
        glVertex3f(1,0,0);     glVertex3f(0,0,0);
    glEnd();
}

void Chead::show3d(bool bOnlySkull,bool bframe,GLint showAg3D,
                   GLfloat translatef_x,GLfloat translatef_y,GLfloat translatef_z,
                   GLfloat rotatef_x,GLfloat rotatef_y,GLfloat rotatef_z)
{
    glTranslatef( translatef_x, translatef_y, translatef_z );
    if(showAg3D==-1)
    {
        glRotatef(rotatef_x,1,0,0);
        glRotatef(rotatef_y,0,1,0);
        glRotatef(rotatef_z,0,0,1);
    }
    else
    {
        switch (showAg3D) {
        case 0:
            glRotatef(90,1,0,0);
            glRotatef(-90,0,0,1);
            break;
        case 1:
            glRotatef(90,1,0,0);
            glRotatef(90,0,0,1);
            break;
        case 2: //Left
            glRotatef(90,1,0,0);
            glRotatef(180,0,0,1);
            break;
        case 3: //Right
            glRotatef(90,1,0,0);
            break;
        case 4:
            glRotatef(180,1,0,0);
            break;
        case 5:

            break;
        }
    }
    int s_alp=100;
    glBegin(GL_QUADS);
        int ct=vhd.count();
        for(int v=1;v<ct-1-1;v++)
        {
            int i,j,kxy=127/2,kz=112/2;
            for(i=1;i<127;i++)
            {
                for(j=1;j<127;j++)
                {
                    if(bOnlySkull==true)
                        if(vhd[v].data[i][j]<140)continue;
                    GLfloat x0,x1,y0,y1,z0,z1,rgb,alp;
                    x0=(i-kxy)/128.0; x1=(i+1-kxy)/128.0;
                    y0=(j-kxy)/128.0; y1=(j+1-kxy)/128.0;
                    z0=(v-kz)/113.0; z1=(v+1-kz)/113.0;

                    //1
                    rgb=vhd[v].data[i][j]/255.0;        alp=vhd[v].alp[i][j];       if(!bOnlySkull){if(alp<s_alp){alp=alp*0.035;}else{alp=alp*0.015;}}else{alp=alp*0.08;}  glColor4f(rgb,rgb,rgb,alp);   glVertex3f(x0,y0,z0);
                    rgb=vhd[v].data[i+1][j]/255.0;      alp=vhd[v].alp[i+1][j];       if(!bOnlySkull){if(alp<s_alp){alp=alp*0.035;}else{alp=alp*0.015;}}else{alp=alp*0.08;}  glColor4f(rgb,rgb,rgb,alp);   glVertex3f(x1,y0,z0);
                    rgb=vhd[v].data[i+1][j+1]/255.0;    alp=vhd[v].alp[i+1][j+1];       if(!bOnlySkull){if(alp<s_alp){alp=alp*0.035;}else{alp=alp*0.015;}}else{alp=alp*0.08;}  glColor4f(rgb,rgb,rgb,alp);   glVertex3f(x1,y1,z0);
                    rgb=vhd[v].data[i][j+1]/255.0;      alp=vhd[v].alp[i][j+1];       if(!bOnlySkull){if(alp<s_alp){alp=alp*0.035;}else{alp=alp*0.015;}}else{alp=alp*0.08;}  glColor4f(rgb,rgb,rgb,alp);   glVertex3f(x0,y1,z0);
                    //2
                    rgb=vhd[v].data[i][j]/255.0;        alp=vhd[v].alp[i][j];       if(!bOnlySkull){if(alp<s_alp){alp=alp*0.035;}else{alp=alp*0.015;}}else{alp=alp*0.08;}  glColor4f(rgb,rgb,rgb,alp);   glVertex3f(x0,y0,z0);
                    rgb=vhd[v].data[i][j+1]/255.0;      alp=vhd[v].alp[i][j+1];       if(!bOnlySkull){if(alp<s_alp){alp=alp*0.035;}else{alp=alp*0.015;}}else{alp=alp*0.08;}  glColor4f(rgb,rgb,rgb,alp);   glVertex3f(x0,y1,z0);
                    rgb=vhd[v+1].data[i][j+1]/255.0;    alp=vhd[v+1].alp[i][j+1];       if(!bOnlySkull){if(alp<s_alp){alp=alp*0.035;}else{alp=alp*0.015;}}else{alp=alp*0.08;}  glColor4f(rgb,rgb,rgb,alp);   glVertex3f(x0,y1,z1);
                    rgb=vhd[v+1].data[i][j]/255.0;      alp=vhd[v+1].alp[i][j];       if(!bOnlySkull){if(alp<s_alp){alp=alp*0.035;}else{alp=alp*0.015;}}else{alp=alp*0.08;}  glColor4f(rgb,rgb,rgb,alp);   glVertex3f(x0,y0,z1);
                    //3
                    rgb=vhd[v+1].data[i][j]/255.0;      alp=vhd[v+1].alp[i][j];       if(!bOnlySkull){if(alp<s_alp){alp=alp*0.035;}else{alp=alp*0.015;}}else{alp=alp*0.08;}  glColor4f(rgb,rgb,rgb,alp);   glVertex3f(x0,y0,z1);
                    rgb=vhd[v+1].data[i+1][j]/255.0;    alp=vhd[v+1].alp[i+1][j];       if(!bOnlySkull){if(alp<s_alp){alp=alp*0.035;}else{alp=alp*0.015;}}else{alp=alp*0.08;}  glColor4f(rgb,rgb,rgb,alp);   glVertex3f(x1,y0,z1);
                    rgb=vhd[v+1].data[i+1][j+1]/255.0;  alp=vhd[v+1].alp[i+1][j+1];       if(!bOnlySkull){if(alp<s_alp){alp=alp*0.035;}else{alp=alp*0.015;}}else{alp=alp*0.08;}  glColor4f(rgb,rgb,rgb,alp);   glVertex3f(x1,y1,z1);
                    rgb=vhd[v+1].data[i][j+1]/255.0;    alp=vhd[v+1].alp[i][j+1];       if(!bOnlySkull){if(alp<s_alp){alp=alp*0.035;}else{alp=alp*0.015;}}else{alp=alp*0.08;}  glColor4f(rgb,rgb,rgb,alp);   glVertex3f(x0,y1,z1);
                    //4
                    rgb=vhd[v].data[i+1][j]/255.0;        alp=vhd[v].alp[i+1][j];       if(!bOnlySkull){if(alp<s_alp){alp=alp*0.035;}else{alp=alp*0.015;}}else{alp=alp*0.08;}  glColor4f(rgb,rgb,rgb,alp);   glVertex3f(x1,y0,z0);
                    rgb=vhd[v].data[i+1][j+1]/255.0;      alp=vhd[v].alp[i+1][j+1];       if(!bOnlySkull){if(alp<s_alp){alp=alp*0.035;}else{alp=alp*0.015;}}else{alp=alp*0.08;}  glColor4f(rgb,rgb,rgb,alp);   glVertex3f(x1,y1,z0);
                    rgb=vhd[v+1].data[i+1][j+1]/255.0;    alp=vhd[v+1].alp[i+1][j+1];       if(!bOnlySkull){if(alp<s_alp){alp=alp*0.035;}else{alp=alp*0.015;}}else{alp=alp*0.08;}  glColor4f(rgb,rgb,rgb,alp);   glVertex3f(x1,y1,z1);
                    rgb=vhd[v+1].data[i+1][j]/255.0;      alp=vhd[v+1].alp[i+1][j];       if(!bOnlySkull){if(alp<s_alp){alp=alp*0.035;}else{alp=alp*0.015;}}else{alp=alp*0.08;}  glColor4f(rgb,rgb,rgb,alp);   glVertex3f(x1,y0,z1);
                    //5
                    rgb=vhd[v+1].data[i][j]/255.0;      alp=vhd[v+1].alp[i][j];       if(!bOnlySkull){if(alp<s_alp){alp=alp*0.035;}else{alp=alp*0.015;}}else{alp=alp*0.08;}  glColor4f(rgb,rgb,rgb,alp);   glVertex3f(x0,y0,z1);
                    rgb=vhd[v+1].data[i+1][j]/255.0;    alp=vhd[v+1].alp[i+1][j];       if(!bOnlySkull){if(alp<s_alp){alp=alp*0.035;}else{alp=alp*0.015;}}else{alp=alp*0.08;}  glColor4f(rgb,rgb,rgb,alp);   glVertex3f(x1,y0,z1);
                    rgb=vhd[v].data[i+1][j]/255.0;      alp=vhd[v].alp[i+1][j];       if(!bOnlySkull){if(alp<s_alp){alp=alp*0.035;}else{alp=alp*0.015;}}else{alp=alp*0.08;}  glColor4f(rgb,rgb,rgb,alp);   glVertex3f(x1,y0,z0);
                    rgb=vhd[v].data[i][j]/255.0;        alp=vhd[v].alp[i][j];       if(!bOnlySkull){if(alp<s_alp){alp=alp*0.035;}else{alp=alp*0.015;}}else{alp=alp*0.08;}  glColor4f(rgb,rgb,rgb,alp);   glVertex3f(x0,y0,z0);
                    //6
                    rgb=vhd[v].data[i+1][j+1]/255.0;      alp=vhd[v].alp[i+1][j+1];       if(!bOnlySkull){if(alp<s_alp){alp=alp*0.035;}else{alp=alp*0.015;}}else{alp=alp*0.08;}  glColor4f(rgb,rgb,rgb,alp);   glVertex3f(x1,y1,z0);
                    rgb=vhd[v].data[i][j+1]/255.0;        alp=vhd[v].alp[i][j+1];       if(!bOnlySkull){if(alp<s_alp){alp=alp*0.035;}else{alp=alp*0.015;}}else{alp=alp*0.08;}  glColor4f(rgb,rgb,rgb,alp);   glVertex3f(x0,y1,z0);
                    rgb=vhd[v+1].data[i][j+1]/255.0;      alp=vhd[v+1].alp[i][j+1];       if(!bOnlySkull){if(alp<s_alp){alp=alp*0.035;}else{alp=alp*0.015;}}else{alp=alp*0.08;}  glColor4f(rgb,rgb,rgb,alp);   glVertex3f(x0,y1,z1);
                    rgb=vhd[v+1].data[i+1][j+1]/255.0;    alp=vhd[v+1].alp[i+1][j+1];       if(!bOnlySkull){if(alp<s_alp){alp=alp*0.035;}else{alp=alp*0.015;}}else{alp=alp*0.08;}  glColor4f(rgb,rgb,rgb,alp);   glVertex3f(x1,y1,z1);

                }
            }
        }

    glEnd();

    if(bframe)
    {
        glBegin(GL_LINES);

            glColor3f(0,1,1);
            glVertex3f(-0.5,-0.5,-0.5);  glVertex3f(-0.5,0.5,-0.5);
            glVertex3f(-0.5,-0.5,-0.5);  glVertex3f(0.5,-0.5,-0.5);
            glVertex3f(-0.5,-0.5,-0.5);  glVertex3f(-0.5,-0.5,0.5);

            glVertex3f(0.5,0.5,-0.5);  glVertex3f(-0.5,0.5,-0.5);
            glVertex3f(0.5,0.5,-0.5);  glVertex3f(0.5,-0.5,-0.5);
            glVertex3f(0.5,0.5,-0.5);  glVertex3f(0.5,0.5,0.5);

            glVertex3f(0.5,-0.5,0.5);  glVertex3f(-0.5,-0.5,0.5);
            glVertex3f(0.5,-0.5,0.5);  glVertex3f(0.5,0.5,0.5);
            glVertex3f(0.5,-0.5,0.5);  glVertex3f(0.5,-0.5,-0.5);

            glVertex3f(-0.5,0.5,0.5);  glVertex3f(-0.5,-0.5,0.5);
            glVertex3f(-0.5,0.5,0.5);  glVertex3f(0.5,0.5,0.5);
            glVertex3f(-0.5,0.5,0.5);  glVertex3f(-0.5,0.5,-0.5);

        glEnd();
    }
}

