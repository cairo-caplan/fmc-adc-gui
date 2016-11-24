#ifndef HISTOGRAM_H
#define HISTOGRAM_H

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
#include <TMultiGraph.h>
#include <TGaxis.h>

#include <TLine.h>

#include "qrootcanvas.h"

#include "acq_types.h"

#include <QObject>
#include <QWidget>
#include <unistd.h>

class Histogram : public QWidget
{
    Q_OBJECT
public:
    explicit Histogram(QWidget *parent = 0);
    //virtual ~VxtRootCanvas() {}
    virtual void changeEvent(QEvent * e);

signals:

public slots:

    //void clicked1();
    void handle_root_events();
    //void updateGraph();
    void clear();
    void draw();
    //void save(char* path);
    void saveHist(char *path);
    void getCh1Event(double *ch1_samples, int n_samples);

protected:
    QRootCanvas    *canvas;
    QPushButton    *b;
    QPushButton     *btnClear;
    QTimer         *fRootTimer;
    TGraph         *gr[5];
    TMultiGraph     *mg;
    TH1F *h1f;

};

#endif // HISTOGRAM_H
