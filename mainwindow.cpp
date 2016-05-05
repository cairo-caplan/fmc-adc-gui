#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m = new QMainCanvas();
    m->resize(m->sizeHint());
    m->setWindowTitle("Qt Example - Canvas");
    m->setGeometry(ui->hlRootContainer->geometry());
    //m->setGeometry( 100, 100, 700, 500 );
    m->show();
    this->ui->hlRootContainer->addWidget(m);

    vxt = new VxtRootCanvas();
    vxt->resize(vxt->sizeHint());
    vxt->setWindowTitle("Qt Example - Canvas");
    vxt->setGeometry(ui->hlVxt->geometry());
    //m->setGeometry( 100, 100, 700, 500 );
    vxt->show();
    this->ui->hlVxt->addWidget(vxt);

    daqModule = new DAQmodule();
    frmsettings = new FrmSettings();



    connect(this->ui->action_About,SIGNAL(triggered()),this,SLOT(openAboutWindow()));
    connect(this->ui->action_Settings,SIGNAL(triggered()),this,SLOT(openFrmSettings()));

    connect(this->ui->cbCh1,SIGNAL(stateChanged(int)),this,SLOT(updateChannels(int)));
    connect(this->ui->cbCh2,SIGNAL(stateChanged(int)),this,SLOT(updateChannels(int)));
    connect(this->ui->cbCh3,SIGNAL(stateChanged(int)),this,SLOT(updateChannels(int)));
    connect(this->ui->cbCh4,SIGNAL(stateChanged(int)),this,SLOT(updateChannels(int)));

    connect(this->ui->sliderScale,SIGNAL(valueChanged(int)),this,SLOT(updateCbScale(int)));
    connect(this->ui->cbScale,SIGNAL(currentIndexChanged(int)),this,SLOT(updateSliderScale(int)));
    connect(this->ui->sbTriggerValue,SIGNAL(valueChanged(double)),this,SLOT(updateDialTrigger(double)));
    connect(this->ui->dialTrigger,SIGNAL(valueChanged(int)),this,SLOT(updateSbTriggerValue(int)));

    connect(this->ui->cbTimeScale,SIGNAL(currentIndexChanged(int)),this,SLOT(updateTimeUnits(int)));
    connect(this->ui->sbSampling,SIGNAL(valueChanged(int)),this,SLOT(updateDialSampling(int)));
    connect(this->ui->dialSampling,SIGNAL(valueChanged(int)),this,SLOT(updateSbSampling(int)));

    connect(this->ui->btnStartAcquisition,SIGNAL(toggled(bool)),this,SLOT(startAcquisition(bool)));

    connect(this->daqModule,SIGNAL(acqAvailable()),this->vxt,SLOT(updateGraph()));
    connect(this->frmsettings,SIGNAL(newAcqPathSettings(acq_path_settings_t)),
            this->daqModule,SLOT(update_acq_path_settings(acq_path_settings_t)));
    //connect(this->daqModule,SIGNAL()
    //connect(this->daqModule,SIGNAL()


    acq_visual_conf.undersample = 1;
    acq_visual_conf.pre_samples_time = 100;
    acq_visual_conf.pre_samples_time = 100;

    acq_visual_conf.threshold_max = 5.0d;
    acq_visual_conf.threshold_min = -5.0d;

    acq_visual_conf.range = R_10V;

    ui->sbTriggerValue->setMaximum(acq_visual_conf.threshold_max);
    ui->sbTriggerValue->setMinimum(acq_visual_conf.threshold_min);


    acq_visual_conf.sampling = ui->sbSampling->value();

    daqModule->acq_path_settings =  frmsettings->acq_path_settings;


    daqModule->start();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnStartAcquisition_pressed()
{
    //this->ui->btnStartAcquisition->setText("■ Stop Acquisition");

}

void MainWindow::on_btnStartAcquisition_released()
{
     //this->ui->btnStartAcquisition->setText("► Start Acquisition");
    //this->ui->btnStartAcquisition->setText("Start Acquisition");
}

void MainWindow::on_btnStartAcquisition_toggled(bool checked)
{
    if (checked){
        #if QT_VERSION>=0x050000
            this->ui->btnStartAcquisition->setText("■ Stop\nAcquisition");
        #else
            this->ui->btnStartAcquisition->setText(QString::fromUtf8("■ Stop\nAcquisition"));
        #endif
        //this->ui->btnStartAcquisition->setStyleSheet("background-color: rgb(207, 255, 206)");
        qDebug()<<"From main thread: "<<QThread::currentThreadId();
        //daqModule =  new DAQmodule();
    }
    else{
        #if QT_VERSION>=0x050000
            this->ui->btnStartAcquisition->setText("► Start\nAcquisition");
        #else
            this->ui->btnStartAcquisition->setText(QString::fromUtf8("► Start\nAcquisition"));
        #endif
        qDebug()<<"From main thread: "<<QThread::currentThreadId();
        //emit daqModule.stop();
    }
}

void MainWindow::openAboutWindow(){
    this->aboutwindow = new AboutWindow();
    this->aboutwindow->show();
}

void MainWindow::openFrmSettings(){
    this->frmsettings->show();
}

void MainWindow::updateChannels(int state){
    if (ui->cbCh1->isChecked()){
        ui->sbOffsetCh1->show();
    }
    else{
        ui->sbOffsetCh1->hide();
    }

    if (ui->cbCh2->isChecked()){
        ui->sbOffsetCh2->show();
    }
    else{
        ui->sbOffsetCh2->hide();
    }

    if (ui->cbCh3->isChecked()){
        ui->sbOffsetCh3->show();
    }
    else{
        ui->sbOffsetCh3->hide();
    }

    if (ui->cbCh4->isChecked()){
        ui->sbOffsetCh4->show();
    }
    else{
        ui->sbOffsetCh4->hide();
    }

}

void MainWindow::updateCbScale(int value){
    if (value <=34){
        // +- 50mV
        ui->cbScale->setCurrentIndex(0);
        acq_visual_conf.threshold_min = -0.05d;
        acq_visual_conf.threshold_max = 0.05d;
        acq_visual_conf.range = R_100mV;
    }
    else if (value <= 67){
        // +- 500mV
        ui->cbScale->setCurrentIndex(1);
        acq_visual_conf.threshold_min = -0.5d;
        acq_visual_conf.threshold_max = 0.5d;
        acq_visual_conf.range = R_1V;
    }
    else{
        // +- 5 V
       ui->cbScale->setCurrentIndex(2);
       acq_visual_conf.threshold_min = -5.0d;
       acq_visual_conf.threshold_max = 5.0d;
       acq_visual_conf.range = R_10V;
    }
}

void MainWindow::updateSliderScale(int id){
    switch (id) {
    case 0:
        ui->sliderScale->setValue(0);
        acq_visual_conf.threshold_min = -0.05d;
        acq_visual_conf.threshold_max = 0.05d;
        break;
    case 1:
        ui->sliderScale->setValue(50);
        acq_visual_conf.threshold_min = -0.5d;
        acq_visual_conf.threshold_max = 0.5d;
        break;
    default:
        ui->sliderScale->setValue(100);
        acq_visual_conf.threshold_min = -5.0d;
        acq_visual_conf.threshold_max = 5.0d;
        break;
    }
    ui->sbTriggerValue->setMaximum(acq_visual_conf.threshold_max);
    ui->sbTriggerValue->setMinimum(acq_visual_conf.threshold_min);
}

void MainWindow::updateDialTrigger(double value){
    this->ui->dialTrigger->setValue(
                ((value - acq_visual_conf.threshold_min)/(acq_visual_conf.threshold_max - acq_visual_conf.threshold_min))
                *(ui->dialTrigger->maximum() - ui->dialTrigger->minimum())
                + ui->dialTrigger->minimum()
            );
}

void MainWindow::updateSbTriggerValue(int value){
    this->ui->sbTriggerValue->setValue(
                (((double)(value - ui->dialTrigger->minimum()))/(ui->dialTrigger->maximum() - ui->dialTrigger->minimum()))
                *(ui->sbTriggerValue->maximum() - ui->sbTriggerValue->minimum())
                + ui->sbTriggerValue->minimum()
            );
}

void MainWindow::updateTimeUnits(int index){

    switch (index) {
    case 0:
        //ns
        this->ui->sbPreSamples->setSingleStep(10.0);
        this->ui->sbPosSamples->setSingleStep(10.0);
        break;
    case 1:
        //us
        this->ui->sbPreSamples->setSingleStep(0.01);
        this->ui->sbPosSamples->setSingleStep(0.01);
        break;
    case 2:
        //ms
        this->ui->sbPreSamples->setSingleStep(0.00001);
        this->ui->sbPosSamples->setSingleStep(0.00001);
        break;
    default:
        break;
    }

}

void MainWindow::updateSbSampling(int value){
    double Sampling = (1.0/(100000000.0 - value+1.0))*100000000.0;
    this->ui->sbSampling->setValue(Sampling);

    acq_visual_conf.sampling = (unsigned long)Sampling;
    acq_time_window_max = (1/Sampling)*MAX_SAMPLES;
    acq_visual_conf.undersample = (int)(100000000.0 - value+1.0);


}

void MainWindow::updateDialSampling(int value){
    //this->ui->dialSampling->setValue((int)value);
    //acq_visual_conf.sampling = value;

}



void MainWindow::updateAcqConf(){
    checkTimingAndSampling();

    this->acq_conf.range = this->acq_visual_conf.range;
    this->acq_conf.posamples = (unsigned long)(acq_visual_conf.pos_samples_time*pow(10.0,-9.0)*acq_visual_conf.sampling);
    this->acq_conf.presamples = (unsigned long)(acq_visual_conf.pre_samples_time*pow(10.0,-9.0)*acq_visual_conf.sampling);
    this->acq_conf.trigger_threshold = this->ui->dialTrigger->value();

    if (this->ui->rbInternalTrigger->isChecked()){
        this->acq_conf.trigger= INTERNAL;
    }
    else{
        this->acq_conf.trigger= EXTERNAL;
    }

    switch (this->ui->cbTriggerEdge->currentIndex()) {
    case 0:
        //Rising
        this->acq_conf.trigger_edge = RISING;
        break;
    case 1:
        //Falling
        this->acq_conf.trigger_edge = FALLING;
        break;
    default:
        //Both
        this->acq_conf.trigger_edge = BOTH;
        break;
    }

    switch (this->ui->cbTriggerChannel->currentIndex()){
    case 0:
        //Channel 1
        this->acq_conf.trigger_channel = CH1;
        break;
    case 1:
        //Channel 2
        this->acq_conf.trigger_channel = CH2;
        break;
    case 2:
        //Channel 3
        this->acq_conf.trigger_channel = CH3;
        break;
    default:
        //Channel 4
        this->acq_conf.trigger_channel = CH4;
        break;

    }

}

void MainWindow::checkTimingAndSampling(){
    double preTime = ui->sbPreSamples->value();
    double posTime = ui->sbPosSamples->value();

    acq_visual_conf.pre_samples_time = preTime;
    acq_visual_conf.pos_samples_time = posTime;

    /*
    switch (this->ui->cbTimeScale->currentIndex()) {
    case 0:
        //ns
        preTime=preTime/1000000000.0;
        posTime=posTime/1000000000.0;
        break;
    case 1:
        //us
        preTime=preTime/1000000.0;
        posTime=posTime/1000000.0;
        break;
    case 2:
        //ms
        preTime=preTime/1000.0;
        posTime=posTime/1000.0;
        break;
    default:
        //s
        break;
    }

    if (acq_time_window < (posTime+preTime)){
        double previousTotalTime = preTime + posTime;

    }
    */


}

void MainWindow::startAcquisition(bool state){
    if (state==true){
        updateAcqConf();
        emit this->daqModule->update_acq_conf(this->acq_conf);
        emit this->daqModule->start_acq();
    }
    else{
        emit this->daqModule->stop_acq();
    }
}
