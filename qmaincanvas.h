#ifndef QMAINCANVAS_H
#define QMAINCANVAS_H


#include <QTimer>
#include <QPaintEvent>
#include <QResizeEvent>
#include <QMouseEvent>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QPushButton>

#include <stdlib.h>

#include <TCanvas.h>
#include <TVirtualX.h>
#include <TSystem.h>
#include <TFormula.h>
#include <TF1.h>
#include <TH1.h>
#include <TFrame.h>
#include <TTimer.h>

#include <TLine.h>

#include <TQObject.h>
#include "TROOT.h"

#include <QWidget>
#include "qrootcanvas.h"

class QMainCanvas : public QWidget
{
   Q_OBJECT

public:
   QMainCanvas( QWidget *parent = 0);
   virtual ~QMainCanvas() {}
   virtual void changeEvent(QEvent * e);

public slots:
   void clicked1();
   void handle_root_events();

protected:
   QRootCanvas    *canvas;
   QPushButton    *b;
   QTimer         *fRootTimer;
};

#endif // QMAINCANVAS_H
