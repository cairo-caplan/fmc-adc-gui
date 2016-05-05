#include "qmaincanvas.h"

//------------------------------------------------------------------------------

//______________________________________________________________________________
QMainCanvas::QMainCanvas(QWidget *parent) : QWidget(parent)
{
   // QMainCanvas constructor.

   QVBoxLayout *l = new QVBoxLayout(this);
   l->addWidget(canvas = new QRootCanvas(this));
   l->addWidget(b = new QPushButton("&Draw Histogram", this));
   connect(b, SIGNAL(clicked()), this, SLOT(clicked1()));
   fRootTimer = new QTimer( this );
   QObject::connect( fRootTimer, SIGNAL(timeout()), this, SLOT(handle_root_events()) );
   fRootTimer->start( 20 );
}

//______________________________________________________________________________
void QMainCanvas::clicked1()
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
void QMainCanvas::handle_root_events()
{
   //call the inner loop of ROOT
   gSystem->ProcessEvents();
}

//______________________________________________________________________________
void QMainCanvas::changeEvent(QEvent * e)
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
