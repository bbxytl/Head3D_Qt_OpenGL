/*

    Qt OpenGL Tutorial - Lesson 05

    nehewidget.cpp
    v 1.00
    2002/12/18

    Copyright (C) 2002 Cavendish
                       cavendish@qiliang.net
                       http://www.qiliang.net/nehe_qt

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

*/


#include"chead.h"
#include "nehewidget.h"
#include<QKeyEvent>
#include<iostream>
using namespace std;

Chead ch("headdata.den");

NeHeWidget::NeHeWidget( QWidget* parent, const QGLWidget* name, bool fs )
    : QGLWidget( parent, name )
{
  rothead=90.0;
  trfhead=-2.0;
  nl=0;
  fullscreen = fs;
  setGeometry( 0, 0, 640, 480 );
  setWindowTitle( "NeHe's Solid Object Tutorial" );

  if ( fullscreen )
    showFullScreen();
  ch.readheads();
//  ch.optdatas();
}

NeHeWidget::~NeHeWidget()
{
}

void NeHeWidget::paintGL()
{
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  glLoadIdentity();
//  paintP();
  ch.show3d(-0.5,  -0.4, trfhead, rothead, 1, 1, 1);
}

void NeHeWidget::initializeGL()
{
  glShadeModel( GL_SMOOTH );
  glClearColor( 0, 0, 0, 0.5 );
  glClearDepth( 1.0 );
  glEnable( GL_DEPTH_TEST );
  glDepthFunc( GL_LEQUAL );
  glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
}

void NeHeWidget::resizeGL( int width, int height )
{
  if ( height == 0 )
  {
    height = 1;
  }
  glViewport( 0, 0, (GLint)width, (GLint)height );
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();  
  gluPerspective( 60.0, (GLfloat)width/(GLfloat)height, 0.1, 100.0 );
  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity();
}


void NeHeWidget::paintP()
{
//    glNewList(1,GL_COMPILE);
    glTranslatef( -0.8,  -0.7, trfhead );
    glRotatef( rothead,  1,  1,  1 );

    glBegin(GL_QUADS);
//    glBegin(GL_POINTS);
        QVector<Hdata> vdata=ch.getdatas();
        int ct=vdata.count(),v=nl;
        for(v=0;v<ct-1;v++)

//            if(v<ct)
        {
            int i,j;
            GLfloat k=v/113.0;
            for(i=0;i<127;i++)
            {
                for(j=0;j<127;j++)
                {
                    if(vdata[v].data[i][j]<140)continue;
                    GLfloat rgb=vdata[v].data[i][j];    glColor3f(rgb/255.0,0,0);   glVertex3f(i/128.0,j/128.0,k);
                    rgb=vdata[v].data[i+1][j];      glColor3f(rgb/255.0,0,0);   glVertex3f((i+1)/128.0,j/128.0,k);
                    rgb=vdata[v].data[i+1][j+1];    glColor3f(rgb/255.0,0,0);   glVertex3f((i+1)/128.0,(j+1)/128.0,k);
                    rgb=vdata[v].data[i][j+1];      glColor3f(rgb/255.0,0,0);   glVertex3f(i/128.0,(j+1)/128.0,k);

//                    //2
//                    rgb=vdata[v].data[i][j];    glColor3f(rgb/255.0,0,0);   glVertex3f(i/128.0,j/128.0,k);
//                    rgb=vdata[v].data[i+1][j];      glColor3f(rgb/255.0,0,0);   glVertex3f((i+1)/128.0,j/128.0,k);
//                    rgb=vdata[v].data[i+1][j+1];    glColor3f(rgb/255.0,0,0);   glVertex3f((i+1)/128.0,(j+1)/128.0,k);
//                    rgb=vdata[v].data[i][j+1];      glColor3f(rgb/255.0,0,0);   glVertex3f(i/128.0,(j+1)/128.0,k);

                }
            }
        }

    glEnd();
//glEndList();
    nl+=1;
    if(nl>=ct)nl=0;
}


void NeHeWidget::keyPressEvent( QKeyEvent *e )
{
  switch ( e->key() )
  {
  case Qt::Key_F2:
    fullscreen = !fullscreen;
    if ( fullscreen )
    {
      showFullScreen();
    }
    else
    {
      showNormal();
      setGeometry( 0, 0, 640, 480 );
    }
    update();
    break;
  case Qt::Key_R:   //press the key "R" to rotation the draw
      rothead-=13;
      update();
      break;
  case Qt::Key_Down:   //press the key "R" to rotation the draw
      rothead-=3;
      trfhead-=1;
      update();
      break;
  case Qt::Key_Up:   //press the key "R" to rotation the draw
      rothead-=3;
      trfhead+=1;
      update();
      break;
  case Qt::Key_Escape:
    close();break;
  case Qt::Key_Space:
      update();
      break;
  }
}

