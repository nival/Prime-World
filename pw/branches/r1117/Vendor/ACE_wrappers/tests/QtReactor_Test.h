/* -*- C++ -*- */
// $Id: QtReactor_Test.h 80826 2008-03-04 14:51:23Z wotte $
#ifndef QTREACTOR_TEST_H
#define QTREACTOR_TEST_H

#include <qapplication.h>
#include <qtimer.h>

class QTestApplication: public QApplication
{
  Q_OBJECT
public:
  typedef QApplication inherited;
public:
  QTestApplication( int argc, char *argv[] );
  virtual void exec( int msec = 0 );
public slots:
  virtual void finishTest(); //!< slot to finish the test, connected to finishTimer_
private:
  QTimer finishTimer_; //!< timer to finish the test
};

#endif /*QTREACTOR_TEST_H*/
