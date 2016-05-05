#include "vxtrootcanvas.h"

VxtRootCanvas::VxtRootCanvas(QWidget *parent) : QWidget(parent)
{
    // QMainCanvas constructor.

    QVBoxLayout *l = new QVBoxLayout(this);
    l->addWidget(canvas = new QRootCanvas(this));
    l->addWidget(b = new QPushButton("&Draw", this));
    connect(b, SIGNAL(clicked()), this, SLOT(updateGraph()));
    fRootTimer = new QTimer( this );
    QObject::connect( fRootTimer, SIGNAL(timeout()), this, SLOT(handle_root_events()) );
    fRootTimer->start( 20 );
 }

 //______________________________________________________________________________
 void VxtRootCanvas::clicked1()
 {
    // Handle the "Draw Histogram" button clicked() event.

    static TH1F *h1f = 0;
    new TFormula("form1","abs(sin(x)/x)");
    TF1 *sqroot = new TF1("sqroot","x*gaus(0) + [3]*form1", 0, 10);
    sqroot->SetParameters(10, 4, 1, 20);

    // Create a one dimensional histogram (one float per bin)
    // and fill it following the distribution in function sqroot.
    canvas->getCanvas()->Clear();
    canvas->getCanvas()->cd();
    canvas->getCanvas()->SetBorderMode(0);
    canvas->getCanvas()->SetFillColor(0);
    canvas->getCanvas()->SetGrid();
    if (h1f) delete h1f;
    h1f = new TH1F("h1f","Test random numbers", 200, 0, 10);
    h1f->SetFillColor(kViolet + 2);
    h1f->SetFillStyle(3001);
    h1f->FillRandom("sqroot", 10000);
    h1f->Draw();
    canvas->getCanvas()->Modified();
    canvas->getCanvas()->Update();
    TLine *l=new TLine(canvas->getCanvas()->GetUxmin(),100.0,canvas->getCanvas()->GetUxmax(),100.0);
    //TLine *l=new TLine(-DBL_MAX,100.0,-DBL_MAX,100.0);
    l->SetLineColor(kRed);
    l->Draw();
    canvas->getCanvas()->Modified();
    canvas->getCanvas()->Update();
 }

 //______________________________________________________________________________
 void VxtRootCanvas::handle_root_events()
 {
    //call the inner loop of ROOT
    gSystem->ProcessEvents();
 }

 //______________________________________________________________________________
 void VxtRootCanvas::changeEvent(QEvent * e)
 {
    if (e->type() == QEvent ::WindowStateChange) {
       QWindowStateChangeEvent * event = static_cast< QWindowStateChangeEvent * >( e );
       if (( event->oldState() & Qt::WindowMaximized ) ||
           ( event->oldState() & Qt::WindowMinimized ) ||
           ( event->oldState() == Qt::WindowNoState &&
             this->windowState() == Qt::WindowMaximized )) {
          if (canvas->getCanvas()) {
              TLine *l=new TLine(canvas->getCanvas()->GetUxmin(),100.0,canvas->getCanvas()->GetUxmax(),100.0);
              //TLine *l=new TLine(-DBL_MAX,100.0,-DBL_MAX,100.0);
              l->SetLineColor(kRed);
              l->Draw();
             canvas->getCanvas()->Resize();
             canvas->getCanvas()->Update();
          }
       }
    }
 }

void VxtRootCanvas::updateGraph(){        
            gr = new TGraph("/dev/shm/fmcadc.0x0200.dat", "%lg %lg %*lg %*lg %*lg");
            if (gr==0){
                    //cout << "An exception occurred. Exception Nr. " << e << '\n';
                    //printf("exception e = %d \n",e);
                    qDebug("Failed to build graphic, the acquisition data file may not be available");
            }
            // Signal
            (gr->GetYaxis())->SetRangeUser(-33000,33000);
            // Noise floor
            //(gr->GetYaxis())->SetRangeUser(-150,30);
            //
            //TH1D *hfft = new TH1D("hfft","hfft",2000,0,2e-6);
            //for(Int_t ibin = 0; ibin<2000; ibin++) {
            //  hfft->SetBinContent(ibin+1,
            //

            gr->SetLineColor(2);
            gr->SetLineWidth(4);
            gr->SetMarkerColor(4);
            gr->SetMarkerStyle(21);
            //cout <<"a simple graph" <<endl;
            gr->SetTitle("Vxt");
            gr->GetXaxis()->SetTitle("time sample");
            gr->GetYaxis()->SetTitle("ADC reading");
            //cout <<"3" <<endl;

            canvas->getCanvas()->cd(1);

            gr->Draw("ACP");

            //canvas->GetFrame()->SetFillColor(21);

            canvas->getCanvas()->Update();
            canvas->getCanvas()->Modified();

            //int N_Samples = this->NrPosSamples + this->NrPreSamples;

}


