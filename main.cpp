
#include <qapplication.h>
#include <qmessagebox.h>
#include<QDesktopWidget>
#include "nehewidget.h"

int main( int argc, char **argv )
{
  bool fs = true;

  QApplication a(argc,argv);

//  switch( QMessageBox::information( 0,
//      "Start FullScreen?",
//      "Would You Like To Run In Fullscreen Mode?",
//      QMessageBox::Yes,
//      QMessageBox::No | QMessageBox::Default ) )
//  {
//  case QMessageBox::Yes:
//    fs = true;
//    break;
//  case QMessageBox::No:
//    fs = false;
//    break;
//  }

  NeHeWidget w( 0, 0, fs );
  w.show();
  w.move((QApplication::desktop()->width()-w.width())/2,(QApplication::desktop()->height()-w.height())/2);

  return a.exec();
}
