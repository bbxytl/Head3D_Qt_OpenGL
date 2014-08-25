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
  showAngle=5;//3d
  bOnlySkull=1;
  showNLevel=0;
  rothead=0.0;
  trfhead=-2.3;
  nl=0;
  fullscreen = fs;
  setGeometry( 0, 0, 640, 480 );
  setWindowTitle( "NeHe's Solid Object Tutorial" );

  if ( fullscreen )
    showFullScreen();
  ch.readheads();
}

NeHeWidget::~NeHeWidget()
{
}

void NeHeWidget::paintGL()
{
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  glLoadIdentity();
  switch (showAngle) {
  case 0:
      ch.show3d(bOnlySkull,-0.5,  -0.5, trfhead, rothead, 1, 1, 1);
      break;
  case 1:
      ch.show2dAhead(showNLevel,bOnlySkull, -1,  -0.5, -0.5);
      break;
  case 2:
      ch.show2dBack(showNLevel,bOnlySkull, 1,  -0.5, -0.5);
      break;
  case 3:
      ch.show2dLeft(showNLevel,bOnlySkull,-0.5, -1,  -0.5);
      break;
  case 4:
      ch.show2dRight(showNLevel,bOnlySkull,-0.5, 1,  -0.5);
      break;
  case 5:
      ch.show2dTop(showNLevel,bOnlySkull,-0.5,  -0.5, -1);
      break;
  case 6:
      ch.show2dBelow(showNLevel,bOnlySkull,-0.5,  -0.5, -1);
      break;
  }

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
  case Qt::Key_Down:
      if(showAngle==0)
      {
        trfhead-=0.3;
      }
      else
      {
          showNLevel--;
      }
      update();
      break;
  case Qt::Key_Up:   //press the key "R" to rotation the draw
      if(showAngle==0)
      {
          trfhead+=0.3;
          if(trfhead>=0)trfhead=-2.3;
      }
      else
      {
          showNLevel++;
      }
      update();
      break;
  case Qt::Key_Escape:
    close();break;
  case Qt::Key_S:
      bOnlySkull=!bOnlySkull;      
      update();
      break;
  case Qt::Key_C:
      trfhead=-2.3;
      bOnlySkull=0;
      showAngle=0;
      showNLevel=0;
      update();
      break;

      //showAngle-->show3d
  case Qt::Key_0:
      showAngle=0;
      update();
      break;
      //showAngle-->show2dAhead
  case Qt::Key_1:
      showAngle=1;
      update();
      break;
      //showAngle-->show2dBack
  case Qt::Key_2:
      showAngle=2;
      update();
      break;
      //showAngle-->show2dLeft
  case Qt::Key_3:
      showAngle=3;
      update();
      break;
      //showAngle-->show2dRight
  case Qt::Key_4:
      showAngle=4;
      update();
      break;
      //showAngle-->show2dTop
  case Qt::Key_5:
      showAngle=5;
      update();
      break;
      //showAngle-->show2dBelow
  case Qt::Key_6:
      showAngle=6;
      update();
      break;

  }
}

