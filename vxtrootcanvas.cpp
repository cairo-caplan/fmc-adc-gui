#include "vxtrootcanvas.h"

VxtRootCanvas::VxtRootCanvas(QWidget *parent) : QWidget(parent)
{
    // QMainCanvas constructor.

    QVBoxLayout *l = new QVBoxLayout(this);
    l->addWidget(canvas = new QRootCanvas(this));
    //l->addWidget(b = new QPushButton("&Draw", this));
    //connect(b, SIGNAL(clicked()), this, SLOT(updateGraph()));
    fRootTimer = new QTimer( this );
    QObject::connect( fRootTimer, SIGNAL(timeout()), this, SLOT(handle_root_events()) );
    connect(canvas,SIGNAL(sMouseReleaseEvent(QMouseEvent*)),this, SLOT(teste(QMouseEvent*)));

    fRootTimer->start( 20 );

    tAxisEnabled = true;
    vAxisEnabled = true;
    lThresholdEnabled = true;
    ch1Enabled = true;
    ch2Enabled = true;
    ch3Enabled = true;
    ch4Enabled = true;

    vCursor1Enabled = false;
    vCursor2Enabled = false;

    vCursor1Updated = false;
    vCursor2Updated = false;

    lThresholdLineUpdated = false;
    tAxisUpdated = false;
    vAxisUpdated = false;

 }

void VxtRootCanvas::teste(QMouseEvent *e){

   // if (fCanvas) {
       switch (e->button()) {
          case Qt::LeftButton :
             //fCanvas->HandleInput(kButton1Up, e->x(), e->y());
             break;
          case Qt::MidButton :
             //fCanvas->HandleInput(kButton2Up, e->x(), e->y());
             break;
          case Qt::RightButton :
             // does not work properly on Linux...
             // ...adding setAttribute(Qt::WA_PaintOnScreen, true)
             // seems to cure the problem
             //fCanvas->HandleInput(kButton3Up, e->x(), e->y());
             break;
          default:
             break;
       }

       if (canvas->getCanvas()) {
           //TLine *l=new TLine(canvas->getCanvas()->GetUxmin(),100.0,canvas->getCanvas()->GetUxmax(),100.0);
           //TLine *l=new TLine(-DBL_MAX,100.0,-DBL_MAX,100.0);
           //l->SetLineColor(kRed);
           //l->Draw();
           if (vCursor1){
               cursor1_pos_x = vCursor1->GetX1();
               emit this->sVCursor1Updated(cursor1_pos_x);
           }

           if (vCursor2){
               cursor2_pos_x = vCursor2->GetX1();
               emit this->sVCursor2Updated(cursor2_pos_x);
           }

           if (lThresholdLine){
                threshold_pos_y = lThresholdLine->GetY1();
                 lThresholdLineUpdated = true;
               emit this->slThresholdLineUpdated(threshold_pos_y);
          }
         canvas->getCanvas()->Resize();
          canvas->getCanvas()->Update();
       }
    //}
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

 double ch1_selected_samples[20000];
 int ch1_n_selected_samples = 0;

void VxtRootCanvas::updateGraph(bool success){
            gSystem->ProcessEvents();

            //If the acquisition had success, there are new samples available
            if (success){
                mg = new TMultiGraph();
                gr[0] = new TGraph("/dev/shm/fmcadc.0x0200.dat", "%lg %lg %*lg %*lg %*lg");
                gr[1] = new TGraph("/dev/shm/fmcadc.0x0200.dat", "%lg %*lg %lg %*lg %*lg");
                gr[2] = new TGraph("/dev/shm/fmcadc.0x0200.dat", "%lg %*lg %*lg %lg %*lg");
                gr[3] = new TGraph("/dev/shm/fmcadc.0x0200.dat", "%lg %*lg %*lg %*lg %lg");
                if (gr[0]==0){
                        //cout << "An exception occurred. Exception Nr. " << e << '\n';
                        //printf("exception e = %d \n",e);
                        qDebug("Failed to build graphic, the acquisition data file may not be available");
                }
                // Signal
                //(gr[0]->GetYaxis())->SetRangeUser(-33000,33000);
                // Noise floor
                //(gr->GetYaxis())->SetRangeUser(-150,30);
                //
                //TH1D *hfft = new TH1D("hfft","hfft",2000,0,2e-6);
                //for(Int_t ibin = 0; ibin<2000; ibin++) {
                //  hfft->SetBinContent(ibin+1,
                //


                //gr[0]->SetLineColor(2);
                gr[0]->SetLineColor(kRed);
                gr[1]->SetLineColor(kBlue);
                gr[2]->SetLineColor(kGreen+4);
                gr[3]->SetLineColor(kOrange+7);

                gr[0]->SetMarkerColor(kRed);
                gr[1]->SetMarkerColor(kBlue);
                gr[2]->SetMarkerColor(kGreen+4);
                gr[3]->SetMarkerColor(kOrange+7);


                for (int i=0;i<=3;i++){
                     gr[i]->SetLineWidth(2);
                     gr[i]->SetMarkerStyle(4);
                     (gr[i]->GetYaxis())->SetRangeUser(-32768,32767);
                }




                //cout <<"a simple graph" <<endl;
                gr[0]->SetTitle("Vxt");
                gr[0]->GetXaxis()->SetTitle("time sample");
                gr[0]->GetYaxis()->SetTitle("ADC read");

                //l=new TLine(canvas->getCanvas()->GetUxmin(),100.0,canvas->getCanvas()->GetUxmax(),100.0);
                //TLine *l=new TLine(-DBL_MAX,100.0,-DBL_MAX,100.0);


                Double_t plotX2[2] = {0 ,  0};
                 Double_t plotY2[2] = {-32768,32767};
                gr[4] = new TGraph(2,plotX2,plotY2);
                //gr[4]->SetMarkerStyle(kBlue);
                gr[4]->SetFillColor(kBlue);



                if (ch1Enabled) mg->Add(gr[0],"ACP");
                if (ch2Enabled) mg->Add(gr[1],"ACP");
                if (ch3Enabled) mg->Add(gr[2],"ACP");
                if (ch4Enabled) mg->Add(gr[3],"ACP");
                mg->Add(gr[4]);

                //Get points between the vertical cursors

                cursor1_pos_x = round(cursor1_pos_x);
                cursor2_pos_x = round(cursor2_pos_x);

                int n = abs(cursor1_pos_x - cursor2_pos_x);


                grshade = new TGraph(2*n-1);

                int k=0;//Fill area iterator
               for (int i=0;i<gr[0]->GetN();i++) {
                   if (((gr[0]->GetX()[i] >= cursor1_pos_x) && (gr[0]->GetX()[i] <= cursor2_pos_x)) ||
                       ((gr[0]->GetX()[i] >= cursor2_pos_x) && (gr[0]->GetX()[i] <= cursor1_pos_x)) ) {
                      grshade->SetPoint(k,gr[0]->GetX()[i],gr[0]->GetY()[i]);
                      ch1_selected_samples[k] = gr[0]->GetY()[i];
                      k+=1;
                   }
               }

               ch1_n_selected_samples = k;


                emit this->SelectedCh1Samples(ch1_selected_samples, ch1_n_selected_samples);

                int l = k;
                k = k-1;
                while (k>=0){
                   grshade->SetPoint(l,grshade->GetX()[k],0.0);
                   k-=1;
                   l+=1;
                }
                grshade->SetFillStyle(3013);
                grshade->SetFillColor(kRed);
                mg->Add(grshade,"f");
            }

            canvas->getCanvas()->cd();


            if (mg)
                mg->Draw("ACP");

            //if (l)
            if ((lThresholdLineUpdated==false)&&(mg)){
                lThresholdLine=new TLine(mg->GetXaxis()->GetXmin(),threshold_pos_y,mg->GetXaxis()->GetXmax(),threshold_pos_y);
                lThresholdLine->SetLineColor(kBlue);
                lThresholdLine->SetLineWidth(3);
                lThresholdLineUpdated = true;
            }
            if (lThresholdLine)
                lThresholdLine->Draw();

            // Draw Voltage Axis on the right side of the canvas
            if ((vAxisUpdated==false)&&(mg)){

               vAxis = new TGaxis(mg->GetXaxis()->GetXmax(),mg->GetYaxis()->GetXmin(),mg->GetXaxis()->GetXmax(),mg->GetYaxis()->GetXmax(),-5.0,5.0,2048,"+L");
               vAxis->SetLabelColor(kRed);

               switch (this->acq_visual_conf.range){
               case R_100mV:
                   this->vAxis->SetWmin(-50.0);
                   this->vAxis->SetWmax(50.0);
                   break;
               case R_1V:
                   this->vAxis->SetWmin(-500.0);
                   this->vAxis->SetWmax(500.0);
                   break;
               default:
                   this->vAxis->SetWmin(-5.0);
                   this->vAxis->SetWmax(5.0);
                   break;
               }

               vAxisUpdated = true;
             }
            if (vAxis)
             vAxis->Draw();

             if ((tAxisUpdated==false)&&(mg)){
                 //canvas->getCanvas()->GetFrame()->

               tAxis = new TGaxis(mg->GetXaxis()->GetXmin() ,mg->GetYaxis()->GetXmax(),mg->GetXaxis()->GetXmax(),mg->GetYaxis()->GetXmax(), 0.0 , 100.0 ,2048,"+L");
               tAxis->SetLabelColor(kRed);
               tAxisUpdated = true;
             }
            if (tAxis)
             tAxis->Draw();


             if ((vCursor1Updated==false)&&(mg)){
                vCursor1 = new TLine(
                            (mg->GetXaxis()->GetXmin()+mg->GetXaxis()->GetXmax())/4,
                            mg->GetYaxis()->GetXmin(),
                            (mg->GetXaxis()->GetXmin()+mg->GetXaxis()->GetXmax())/4,
                            mg->GetYaxis()->GetXmax()
                        );

                vCursor1->SetLineColor(kRed+3);
                vCursor1->SetLineWidth(3);

                if (vCursor1){
                    cursor1_pos_x = vCursor1->GetX1();
                    emit this->sVCursor1Updated(cursor1_pos_x);
                }

                vCursor1Updated = true;
             }

             if (vCursor1Enabled)
                vCursor1->Draw();

             if ((vCursor2Updated==false)&&(mg)){
                vCursor2 = new TLine(
                            (mg->GetXaxis()->GetXmin()+mg->GetXaxis()->GetXmax())/2,
                            mg->GetYaxis()->GetXmin(),
                            (mg->GetXaxis()->GetXmin()+mg->GetXaxis()->GetXmax())/2,
                            mg->GetYaxis()->GetXmax()
                        );

                vCursor2->SetLineColor(kGreen);
                vCursor2->SetLineWidth(3);

                if (vCursor2){
                    cursor2_pos_x = vCursor2->GetX1();
                    emit this->sVCursor2Updated(cursor2_pos_x);
                }

                vCursor2Updated = true;
             }

             if (vCursor2Enabled)
                vCursor2->Draw();


            canvas->getCanvas()->Update();
            //canvas->getCanvas()->Modified(); It seems it is not needed
            gSystem->ProcessEvents();


}

void VxtRootCanvas::saveGraph(char *path){
    this->canvas->getCanvas()->SaveAs(path);

}


