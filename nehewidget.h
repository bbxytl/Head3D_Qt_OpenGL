
#ifndef NEHEWIDGET_H
#define NEHEWIDGET_H

#include <QWidget>
#include <qgl.h>
#include <GL/glu.h>
#include "widget.h"

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

protected:

  bool fullscreen;
  GLfloat trfhead;
  GLfloat rothead;

  GLint showAngle;
  GLint showNLevel;
  GLboolean bOnlySkull;

  Widget *w;

};

#endif//NEHEWIDGET_H
