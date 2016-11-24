#include "histogram.h"

Histogram::Histogram(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *l = new QVBoxLayout(this);
    l->addWidget(canvas = new QRootCanvas(this));
//    l->addWidget(b = new QPushButton("&Draw", this));
//    connect(b, SIGNAL(clicked()), this, SLOT(draw()));

//    l->addWidget(btnClear = new QPushButton("&Clear", this));
//     connect(b, SIGNAL(clicked()), this, SLOT(clear()));

    fRootTimer = new QTimer( this );
    QObject::connect( fRootTimer, SIGNAL(timeout()), this, SLOT(handle_root_events()) );

    //if (h1f) delete h1f;
    h1f = new TH1F("h1f","Signal energy", 100000, 0, 1e7);
    h1f->SetFillColor(kViolet + 2);
    h1f->SetFillStyle(3001);

    fRootTimer->start( 20 );
}

//Clear the Histogram
void Histogram::clear(){
    h1f->Reset();
    h1f->Draw();
    canvas->getCanvas()->Modified();
    canvas->getCanvas()->Update();

}

void Histogram::saveHist(char *path){
    h1f->SaveAs(path);
    if( access( path, F_OK ) != -1 ) {
        // file exists
        //qDebug("Histogram probably saved");
    } else {
        // file doesn't exist
        //qDebug("Couldn't save Histogram");
    }


}


void Histogram::draw(){


    // Handle the "Draw Histogram" button clicked() event.

    //static TH1F *h1f = 0;
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

    //h1f->FillRandom("sqroot", 10000);
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

void Histogram::handle_root_events()
{
   //call the inner loop of ROOT
   gSystem->ProcessEvents();


}

//______________________________________________________________________________
void Histogram::changeEvent(QEvent * e)
{
   if (e->type() == QEvent ::WindowStateChange) {
      QWindowStateChangeEvent * event = static_cast< QWindowStateChangeEvent * >( e );
      if (( event->oldState() & Qt::WindowMaximized ) ||
          ( event->oldState() & Qt::WindowMinimized ) ||
          ( event->oldState() == Qt::WindowNoState &&
            this->windowState() == Qt::WindowMaximized )) {
         if (canvas->getCanvas()) {
             //TLine *l=new TLine(canvas->getCanvas()->GetUxmin(),100.0,canvas->getCanvas()->GetUxmax(),100.0);
             //TLine *l=new TLine(-DBL_MAX,100.0,-DBL_MAX,100.0);
             //l->SetLineColor(kRed);
             //l->Draw();
           canvas->getCanvas()->Resize();
            canvas->getCanvas()->Update();
         }
      }
   }


}

void Histogram::getCh1Event(double *ch1_samples, int n_samples){
    double signal_energy = 0.0;
    //Compute area or energy of the signal:
    for (int i=0;i<n_samples;i++){
        signal_energy += abs(ch1_samples[i]);
    }

    canvas->getCanvas()->cd();
    canvas->getCanvas()->SetBorderMode(0);
    canvas->getCanvas()->SetFillColor(0);
    canvas->getCanvas()->SetGrid();

    h1f->Fill(signal_energy);
    h1f->Draw();
    canvas->getCanvas()->Modified();
    canvas->getCanvas()->Update();
}
