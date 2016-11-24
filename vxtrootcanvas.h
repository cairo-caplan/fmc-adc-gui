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
#include <TMultiGraph.h>
#include <TGaxis.h>

#include <TLine.h>

#include <QWidget>
#include "qrootcanvas.h"

#include "acq_types.h"




class VxtRootCanvas : public QWidget
{
   Q_OBJECT

public:
    VxtRootCanvas( QWidget *parent = 0);
    virtual ~VxtRootCanvas() {}
    virtual void changeEvent(QEvent * e);


    acq_visual_conf_t acq_visual_conf;

    bool tAxisEnabled;
    bool vAxisEnabled;
    bool lThresholdEnabled;
    bool ch1Enabled;
    bool ch2Enabled;
    bool ch3Enabled;
    bool ch4Enabled;

    bool vCursor1Enabled;
    bool vCursor2Enabled;


    bool vCursor1Updated;
    bool vCursor2Updated;


    //It is not a good practice to let them public but...
    bool lThresholdLineUpdated;
    bool tAxisUpdated;
    bool vAxisUpdated;
    TGaxis *tAxis;
    TGaxis *vAxis;

    int threshold_pos_y;


 public slots:
    void clicked1();
    void handle_root_events();
    void updateGraph(bool success);

    void teste(QMouseEvent *e);

    void saveGraph(char* path);
 protected:
    QRootCanvas    *canvas;
    QPushButton    *b;
    QTimer         *fRootTimer;
    TGraph         *gr[5];
    TMultiGraph     *mg;
    TGraph *grshade;

    TLine *lThresholdLine;
    TLine *vCursor1;
    TLine *vCursor2;

    double cursor1_pos_x;
    double cursor2_pos_x;

signals:
    void sVCursor1Updated(double x);
    void sVCursor2Updated(double x);
    void slThresholdLineUpdated(int y);

    void SelectedCh1Samples(double *ch1_samples, int n_samples);



};

#endif // VXTROOTCANVAS_H
