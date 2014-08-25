/*

    Qt OpenGL Tutorial - Lesson 05

    main.cpp
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

#include <qapplication.h>
#include <qmessagebox.h>
#include<widget.h>
#include "nehewidget.h"

int main( int argc, char **argv )
{
  bool fs = false;

  QApplication a(argc,argv);

  switch( QMessageBox::information( 0,
      "Start FullScreen?",
      "Would You Like To Run In Fullscreen Mode?",
      QMessageBox::Yes,
      QMessageBox::No | QMessageBox::Default ) )
  {
  case QMessageBox::Yes:
    fs = true;
    break;
  case QMessageBox::No:
    fs = false;
    break;
  }

//  Widget wg;
  NeHeWidget w( 0, 0, fs );

//  w.setParent(&wg);

  w.show();
//  wg.show();

  return a.exec();
}
