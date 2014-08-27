
#include <qmessagebox.h>
#include <QtWidgets>
#include "nehewidget.h"
#include<QKeyEvent>
#include"widget.h"
#include"chead.h"

Chead ch("../Head3D_Qt_OpenGL/headData/headdata.den");

NeHeWidget::NeHeWidget( QWidget* parent, const QGLWidget* name, bool fs )
    : QGLWidget( parent, name )
{
  showAngle=0;//3d
  bOnlySkull=0;
  showNLevel=0;
  rothead=90.0;
  trfhead=-2.3;


  w=new Widget(0);

  fullscreen = fs;
  setGeometry( 0, 0, 640, 480 );
  setWindowTitle( "Head 2D/3D ---Press 'H' to help !" );
  QMessageBox::information( 0,
        "Read Help",
        "Press 'H' to read help !",
        QMessageBox::Ok,
        QMessageBox::Default );

  if ( fullscreen )
    showFullScreen();
  ch.readheads();
}

NeHeWidget::~NeHeWidget()
{
}

void enble()
{
    glEnable(GL_BLEND);
    glBlendFunc( GL_SRC_ALPHA, GL_ONE );

//    glEnable(GL_POINT_SMOOTH);
//    glHint(GL_POINT_SMOOTH,GL_NICEST);
//    glEnable(GL_LINE_SMOOTH);
//    glHint(GL_LINE_SMOOTH,GL_NICEST);
//    glEnable(GL_POLYGON_SMOOTH);
//    glHint(GL_POLYGON_SMOOTH,GL_NICEST);

}

void NeHeWidget::paintGL()
{
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  glLoadIdentity();


  switch (showAngle) {
  case 0:
      enble();
      ch.show3d(bOnlySkull,-0.5,  -0.5, trfhead, rothead, 1, 1, 1);
      break;
  case 1:
      enble();
      ch.show2dAhead(showNLevel,bOnlySkull, trfhead,  -0.5, -0.5);
      break;
  case 2:
      enble();
      ch.show2dBack(showNLevel,bOnlySkull, -trfhead,  -0.5, -0.5);
      break;
  case 3:
      enble();
      ch.show2dLeft(showNLevel,bOnlySkull,-0.5, -trfhead,  -0.5);
      break;
  case 4:
      enble();
      ch.show2dRight(showNLevel,bOnlySkull,-0.5, trfhead,  -0.5);
      break;
  case 5:
      enble();
      ch.show2dTop(showNLevel,bOnlySkull,-0.5,  -0.5, trfhead);
      break;
  case 6:
      enble();
      ch.show2dBelow(showNLevel,bOnlySkull,-0.5,  -0.5, trfhead);
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
  case Qt::Key_H:
      if(1){
//      Widget *w=new Widget(0);
      w->show();
      w->move((QApplication::desktop()->width()-w->width())/2,(QApplication::desktop()->height()-w->height())/2);
      }
      break;
  case Qt::Key_A:
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
  case Qt::Key_Q:
      delete w;
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
  case Qt::Key_R:   //press the key "R" to rotation the draw
      rothead-=13.63;
      update();
      break;
  case Qt::Key_Down:
      trfhead-=0.2;
      update();
      break;
  case Qt::Key_Up:
      trfhead+=0.2;
      if(trfhead>=0)
      {
          if(showAngle==0)trfhead=-2.3;
          else trfhead=-1;
      }
      update();
      break;
  case Qt::Key_Left:
      showNLevel--;
      update();
      break;
  case Qt::Key_Right:
      showNLevel++;
      update();
      break;
      //showAngle-->show3d
  case Qt::Key_0:
      showAngle=0;
      bOnlySkull=0;
      trfhead=-2.3;
      update();
      break;
      //showAngle-->show2dAhead
  case Qt::Key_1:
      showAngle=1;      
      bOnlySkull=1;
      trfhead=-1;
      update();
      break;
      //showAngle-->show2dBack
  case Qt::Key_2:
      showAngle=2;
      bOnlySkull=1;
      trfhead=-1;
      update();
      break;
      //showAngle-->show2dLeft
  case Qt::Key_3:
      showAngle=3;
      bOnlySkull=1;
      trfhead=-1;
      update();
      break;
      //showAngle-->show2dRight
  case Qt::Key_4:
      showAngle=4;
      bOnlySkull=1;
      trfhead=-1;
      update();
      break;
      //showAngle-->show2dTop
  case Qt::Key_5:
      showAngle=5;
      bOnlySkull=1;
      trfhead=-1;
      update();
      break;
      //showAngle-->show2dBelow
  case Qt::Key_6:
      showAngle=6;
      bOnlySkull=1;
      trfhead=-1;
      update();
      break;

  }
}

