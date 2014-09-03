
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
  bOnlySkull=true;
  bframe=true;
  showNLevel=0;

  trfhead=-2.3;

  xRot=90;zRot=0;yRot=0;

  dg =new Dialog();
  connect(dg,SIGNAL(infoSend(const GLint &)),this,SLOT(infoRecv(const GLint &)));
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

void NeHeWidget::paintGL()
{
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  glLoadIdentity();

  switch (showAngle) {
  case 0:
      ch.show3d(bOnlySkull,bframe,-0.0,  -0.0, trfhead,  xRot, yRot, zRot);
      break;
  case 1:
      ch.show2dAhead(showNLevel, trfhead,  -0.5, -0.5);
      break;
  case 2:
      ch.show2dBack(showNLevel, -trfhead,  -0.5, -0.5);
      break;
  case 3:
      ch.show2dLeft(showNLevel,-0.5, -trfhead,  -0.5);
      break;
  case 4:
      ch.show2dRight(showNLevel,-0.5, trfhead,  -0.5);
      break;
  case 5:
      ch.show2dTop(showNLevel,-0.5,  -0.5, trfhead);
      break;
  case 6:
      ch.show2dBelow(showNLevel,-0.5,  -0.5, trfhead);
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


  glEnable( GL_BLEND );
  glDisable( GL_DEPTH_TEST );
  glBlendFunc( GL_SRC_ALPHA, GL_ONE );

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

void NeHeWidget::infoRecv(const GLint &info)
{
    if(showAngle!=0)
    {
        showNLevel=info;
    }
    else
    {
        switch (info) {
        case 0:
            xRot=90; yRot=0; zRot=-90;
            break;
        case 1:
            xRot=90; yRot=0; zRot=90;
            break;
        case 2: //Left
            xRot=90; yRot=0; zRot=180;
            break;
        case 3: //Right
            xRot=90; yRot=0; zRot=0;
            break;
        case 4:
            xRot=180; yRot=0; zRot=0;
            break;
        case 5:
            xRot=0; yRot=0; zRot=0;
            break;
        }
    }
}

static void qNormalizeAngle(int &angle)
{
    while (angle < 0)
        angle += 360 ;
    while (angle > 360)
        angle -= 360;
}
static void ALPEnable(GLint showAngle)
{
    if(showAngle==0)
    {
        glDisable(  GL_DEPTH_TEST);
        glEnable( GL_BLEND);
    }
    else
    {
        glDisable( GL_BLEND );
        glEnable( GL_DEPTH_TEST );
    }
}


void NeHeWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->buttons()&Qt::RightButton)
    {
        w->show();
        w->move((QApplication::desktop()->width()-w->width())/2,(QApplication::desktop()->height()-w->height())/2);
    }
    if(event->button()&Qt::LeftButton)
    {
        dg->initcb(showAngle);
        dg->show();
        update();
    }
}

void NeHeWidget::keyPressEvent( QKeyEvent *e )
{
  switch ( e->key() )
  {
  case Qt::Key_H:
      if(1){
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
  case Qt::Key_F:
      bframe=!bframe;
      update();
      break;
  case Qt::Key_G:
      dg->initcb(showAngle);
      dg->show();
      update();
      break;
  case Qt::Key_C:
      if(showAngle!=0)
      {
          trfhead=-1;
          bOnlySkull=false;
          showNLevel=0;
      }
      else
      {
         trfhead=-2.3;
         bOnlySkull=true;
         xRot=90;yRot=0;zRot=0;
      }
      update();
      break;

  case Qt::Key_I: //x+
  xRot+=15;
//  yRot=0; zRot=0;
  qNormalizeAngle(xRot);
  update();
  break;
  case Qt::Key_K:  //x-
  xRot-=15;
//  yRot=0; zRot=0;
  qNormalizeAngle(xRot);
  update();
  break;
  case Qt::Key_L:  //y+
  yRot+=15;
//  xRot=0; zRot=0;
  qNormalizeAngle(yRot);
  update();
  break;
  case Qt::Key_J:   //y-
  yRot-=15;
//  xRot=0; zRot=0;
  qNormalizeAngle(yRot);
  update();
  break;
  case Qt::Key_N:   //z+
  zRot+=15;
//  yRot=0; xRot=0;
  qNormalizeAngle(zRot);
  update();
  break;
  case Qt::Key_M:   //z-
  zRot-=15;
//  yRot=0; xRot=0;
  qNormalizeAngle(zRot);
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
      bOnlySkull=true;
      trfhead=-2.3;      
      ALPEnable( showAngle);
      update();
      break;
      //showAngle-->show2dAhead
  case Qt::Key_1:
      showAngle=1;      
      bOnlySkull=false;
      trfhead=-1;
      ALPEnable( showAngle);
      update();
      break;
      //showAngle-->show2dBack
  case Qt::Key_2:
      showAngle=2;
      bOnlySkull=false;
      trfhead=-1;
      ALPEnable(showAngle);
      update();
      break;
      //showAngle-->show2dLeft
  case Qt::Key_3:
      showAngle=3;
      bOnlySkull=false;
      trfhead=-1;
      ALPEnable( showAngle);
      update();
      break;
      //showAngle-->show2dRight
  case Qt::Key_4:
      showAngle=4;
      bOnlySkull=false;
      trfhead=-1;
      ALPEnable( showAngle);
      update();
      break;
      //showAngle-->show2dTop
  case Qt::Key_5:
      showAngle=5;
      bOnlySkull=false;
      trfhead=-1;
      ALPEnable( showAngle);
      update();
      break;
      //showAngle-->show2dBelow
  case Qt::Key_6:
      showAngle=6;
      bOnlySkull=false;
      trfhead=-1;
      ALPEnable( showAngle);
      update();
      break;
  default:
      QMessageBox::information( 0,
            "按键提醒！",
            "只能使用【0-9,Q,A,S,F,G,C,H,I,J,K,M,N,UP,DOWN,LEFT,RIGHT】键！\n使用方法请查看帮助窗口：右键点击或单击‘H’键！",
            QMessageBox::Ok);

  }
}



