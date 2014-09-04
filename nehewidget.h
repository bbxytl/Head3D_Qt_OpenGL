
#ifndef NEHEWIDGET_H
#define NEHEWIDGET_H

#include <QWidget>
#include <qgl.h>
#include <GL/glu.h>
#include "widget.h"
#include "dialog.h"

QT_BEGIN_NAMESPACE
class QLabel;
QT_END_NAMESPACE

class NeHeWidget : public QGLWidget
{
    Q_OBJECT

public:
    
  NeHeWidget( QWidget* parent = 0, const QGLWidget* name = 0, bool fs = false );
  ~NeHeWidget();

protected:

  void initializeGL();
  void paintGL();
  void resizeGL( int width, int height );

  void keyPressEvent( QKeyEvent *e );
  void mousePressEvent(QMouseEvent *e);


protected:

  bool fullscreen;
  GLfloat trfhead;


  GLint showAngle;
  GLint showNLevel;
  bool bOnlySkull;
  bool bframe;

  Widget *w;  //Help

  int xRot;
  int yRot;
  int zRot;

  Dialog *dg;   //Choice

public slots:
  void infoRecv(const GLint &);

};

#endif//NEHEWIDGET_H
