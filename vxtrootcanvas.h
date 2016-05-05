#ifndef VXTROOTCANVAS_H
#define VXTROOTCANVAS_H

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
#include <TGraph.h>

#include <TLine.h>

#include <QWidget>
#include "qrootcanvas.h"


class VxtRootCanvas : public QWidget
{
   Q_OBJECT

public:
    VxtRootCanvas( QWidget *parent = 0);
    virtual ~VxtRootCanvas() {}
    virtual void changeEvent(QEvent * e);

 public slots:
    void clicked1();
    void handle_root_events();
    void updateGraph();

 protected:
    QRootCanvas    *canvas;
    QPushButton    *b;
    QTimer         *fRootTimer;
    TGraph         *gr;
};

#endif // VXTROOTCANVAS_H
