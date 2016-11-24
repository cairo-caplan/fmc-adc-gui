#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m = new Histogram();
    m->resize(m->sizeHint());
    m->setWindowTitle("Qt Example - Canvas");
    m->setGeometry(ui->hlRootContainer->geometry());
    m->show();
    this->ui->hlRootContainer->addWidget(m);


    this->acq_time_window_max = 0.0000001;
    //--------------------------------------------------------------
    // First tab of the main window, Voltage vs Time module

    vxt = new VxtRootCanvas();
    vxt->resize(vxt->sizeHint());
    vxt->setWindowTitle("Qt Example - Canvas");
    vxt->setGeometry(ui->hlVxt->geometry());
    //m->setGeometry( 100, 100, 700, 500 );
    vxt->show();
    this->ui->hlVxt->addWidget(vxt);

    //--------------------------------------------------------------

    daqModule = new DAQmodule();
    frmsettings = new FrmSettings();

    connect(this->ui->action_About,SIGNAL(triggered()),this,SLOT(openAboutWindow()));
    connect(this->ui->action_Settings,SIGNAL(triggered()),this,SLOT(openFrmSettings()));

    connect(this->ui->cbCh1,SIGNAL(stateChanged(int)),this,SLOT(updateChannels()));
    connect(this->ui->cbCh2,SIGNAL(stateChanged(int)),this,SLOT(updateChannels()));
    connect(this->ui->cbCh3,SIGNAL(stateChanged(int)),this,SLOT(updateChannels()));
    connect(this->ui->cbCh4,SIGNAL(stateChanged(int)),this,SLOT(updateChannels()));

    connect(this->ui->chkTermCh1,SIGNAL(stateChanged(int)),this,SLOT(updateTerminations()));
    connect(this->ui->chkTermCh2,SIGNAL(stateChanged(int)),this,SLOT(updateTerminations()));
    connect(this->ui->chkTermCh3,SIGNAL(stateChanged(int)),this,SLOT(updateTerminations()));
    connect(this->ui->chkTermCh4,SIGNAL(stateChanged(int)),this,SLOT(updateTerminations()));

    connect(this->ui->sliderScale,SIGNAL(valueChanged(int)),this,SLOT(updateCbScale(int)));
    connect(this->ui->cbScale,SIGNAL(currentIndexChanged(int)),this,SLOT(updateSliderScale(int)));
    connect(this->ui->sbTriggerValue,SIGNAL(valueChanged(double)),this,SLOT(updateDialTrigger(double)));
    connect(this->ui->dialTrigger,SIGNAL(valueChanged(int)),this,SLOT(updateSbTriggerValue(int)));
    connect(this->ui->cbTriggerChannel,SIGNAL(currentIndexChanged(int)),this,SLOT(updateTriggerChannel()));

    connect(this->ui->cbTimeScale,SIGNAL(currentIndexChanged(int)),this,SLOT(updateTimeUnits(int)));
    //connect(this->ui->sbSampling,SIGNAL(valueChanged(int)),this,SLOT(updateDialSampling(int)));
    connect(this->ui->dialSampling,SIGNAL(valueChanged(int)),this,SLOT(updateSbSampling(int)));

    connect(this->ui->btnStartAcquisition,SIGNAL(toggled(bool)),this,SLOT(startAcquisition(bool)));
    connect(this->daqModule,SIGNAL(updateState(DaqState_t)),this,SLOT(GetUpdatedDaqState(DaqState_t)));

    connect(this->daqModule,SIGNAL(acqAvailable(bool)),this->vxt,SLOT(updateGraph(bool)));
    connect(this->frmsettings,SIGNAL(newAcqPathSettings(acq_path_settings_t)),
            this->daqModule,SLOT(update_acq_path_settings(acq_path_settings_t)));

    connect(this->ui->sbPreSamples,SIGNAL(editingFinished()),this,SLOT(TimeUnitsChanged()));
    connect(this->ui->sbPosSamples,SIGNAL(editingFinished()),this,SLOT(TimeUnitsChanged()));
    //connect(this->daqModule,SIGNAL()
    //connect(this->daqModule,SIGNAL()

    connect(this->vxt,SIGNAL(slThresholdLineUpdated(int)),this,SLOT(updateSbTriggerValue(int)));
    connect(this->vxt,SIGNAL(SelectedCh1Samples(double*,int)),this->m,SLOT(getCh1Event(double*,int)));

    connect(this->ui->btnHistClear,SIGNAL(released()),this->m,SLOT(clear()));
    connect(this,SIGNAL(saveHist(char*)),m,SLOT(saveHist(char*)));
    connect(this,SIGNAL(saveGraph(char*)),vxt,SLOT(saveGraph(char*)));


    acq_visual_conf.undersample = 1;
    acq_visual_conf.pre_samples_time = 100;
    acq_visual_conf.pre_samples_time = 100;

    acq_visual_conf.threshold_max = 5.0;
    acq_visual_conf.threshold_min = -5.0;

    acq_visual_conf.range = R_10V;

    ui->sbTriggerValue->setMaximum(acq_visual_conf.threshold_max);
    ui->sbTriggerValue->setMinimum(acq_visual_conf.threshold_min);


    acq_visual_conf.sampling = ui->sbSampling->value();

    daqModule->acq_path_settings =  frmsettings->acq_path_settings;


    daqModule->start();

    this->statusBar()->showMessage("Ready");

}

MainWindow::~MainWindow()
{
    delete ui;
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

void MainWindow::updateChannels(){
    if (ui->cbCh1->isChecked()){
        ui->chkTermCh1->show();
        this->vxt->ch1Enabled = true;
    }
    else{
        ui->chkTermCh1->hide();
        this->vxt->ch1Enabled = false;
    }

    if (ui->cbCh2->isChecked()){
        ui->chkTermCh2->show();
        this->vxt->ch2Enabled = true;
    }
    else{
        ui->chkTermCh2->hide();
        this->vxt->ch2Enabled = false;
    }

    if (ui->cbCh3->isChecked()){
        ui->chkTermCh3->show();
        this->vxt->ch3Enabled = true;
    }
    else{
        ui->chkTermCh3->hide();
        this->vxt->ch3Enabled = false;
    }

    if (ui->cbCh4->isChecked()){
        ui->chkTermCh4->show();
        this->vxt->ch4Enabled = true;
    }
    else{
        ui->chkTermCh4->hide();
        this->vxt->ch4Enabled = false;
    }

}

void MainWindow::updateTerminations(){

    QString adc_board_path;
    adc_board_path.append("/sys/bus/zio/devices/");
    adc_board_path += frmsettings->acq_path_settings.adc_board_pci_id;
    adc_board_path.append("/cset0");
    //QProcess proc;


    QFile *file;
    QTextStream *stream;
    // Channel 1
    file = new QFile(QString(adc_board_path + "/ch0-50ohm-term"));
    file->open(QIODevice::ReadWrite | QIODevice::Text);
    stream = new QTextStream(file);
    if (ui->chkTermCh1->isChecked()){
         (*stream) << "1" << endl;
    }
    else{
        (*stream) << "0" << endl;
    }
    file->close();
    stream->flush();
    // Channel 2
    file = new QFile(QString(adc_board_path + "/ch1-50ohm-term"));
    file->open(QIODevice::ReadWrite | QIODevice::Text);
    stream = new QTextStream(file);
    if (ui->chkTermCh2->isChecked()){
         (*stream) << "1" << endl;
    }
    else{
        (*stream) << "0" << endl;
    }
    file->close();
    stream->flush();
    // Channel 3
    file = new QFile(QString(adc_board_path + "/ch2-50ohm-term"));
    file->open(QIODevice::ReadWrite | QIODevice::Text);
    stream = new QTextStream(file);
    if (ui->chkTermCh3->isChecked()){
         (*stream) << "1" << endl;
    }
    else{
        (*stream) << "0" << endl;
    }
    file->close();
    stream->flush();
    // Channel 4
    file = new QFile(QString(adc_board_path + "/ch3-50ohm-term"));
    file->open(QIODevice::ReadWrite | QIODevice::Text);
    stream = new QTextStream(file);
    if (ui->chkTermCh4->isChecked()){
         (*stream) << "1" << endl;
    }
    else{
        (*stream) << "0" << endl;
    }
    file->close();
    stream->flush();

    ///////////////////////////////////////
    updateAcqConf();
    emit this->daqModule->update_acq_conf(this->acq_conf);
}

void MainWindow::updateCbScale(int value){
    if (value <=34){
        // +- 50mV
        ui->cbScale->setCurrentIndex(0);
        acq_visual_conf.threshold_min = -0.05;
        acq_visual_conf.threshold_max = 0.05;
        acq_visual_conf.range = R_100mV;
    }
    else if (value <= 67){
        // +- 500mV
        ui->cbScale->setCurrentIndex(1);
        acq_visual_conf.threshold_min = -0.5;
        acq_visual_conf.threshold_max = 0.5;
        acq_visual_conf.range = R_1V;
    }
    else{
        // +- 5 V
       ui->cbScale->setCurrentIndex(2);
       acq_visual_conf.threshold_min = -5.0;
       acq_visual_conf.threshold_max = 5.0;
       acq_visual_conf.range = R_10V;
    }
    ////////////////////
    updateAcqConf();
    emit this->daqModule->update_acq_conf(this->acq_conf);
}

void MainWindow::updateSliderScale(int id){
    switch (id) {
    case 0:
        ui->sliderScale->setValue(0);
        acq_visual_conf.threshold_min = -0.05;
        acq_visual_conf.threshold_max = 0.05;
        break;
    case 1:
        ui->sliderScale->setValue(50);
        acq_visual_conf.threshold_min = -0.5;
        acq_visual_conf.threshold_max = 0.5;
        break;
    default:
        ui->sliderScale->setValue(100);
        acq_visual_conf.threshold_min = -5.0;
        acq_visual_conf.threshold_max = 5.0;
        break;
    }
    ui->sbTriggerValue->setMaximum(acq_visual_conf.threshold_max);
    ui->sbTriggerValue->setMinimum(acq_visual_conf.threshold_min);
    /////////
    updateAcqConf();
    emit this->daqModule->update_acq_conf(this->acq_conf);
}

void MainWindow::updateDialTrigger(double value){
    int DialTriggerValue =
            ((value - acq_visual_conf.threshold_min)/(acq_visual_conf.threshold_max - acq_visual_conf.threshold_min))
            *(ui->dialTrigger->maximum() - ui->dialTrigger->minimum())
            + ui->dialTrigger->minimum();
    this->ui->dialTrigger->setValue(DialTriggerValue);

    vxt->threshold_pos_y = DialTriggerValue;
    vxt->lThresholdLineUpdated = false;
    ///////////////////////////////
    updateAcqConf();
    emit this->daqModule->update_acq_conf(this->acq_conf);
}

void MainWindow::updateSbTriggerValue(int value){
    this->ui->sbTriggerValue->setValue(
                (((double)(value - ui->dialTrigger->minimum()))/(ui->dialTrigger->maximum() - ui->dialTrigger->minimum()))
                *(ui->sbTriggerValue->maximum() - ui->sbTriggerValue->minimum())
                + ui->sbTriggerValue->minimum()
            );
    ///////////////////////////
    updateAcqConf();
    emit this->daqModule->update_acq_conf(this->acq_conf);
}

void MainWindow::TimeUnitsChanged(){
    int index;
    index = ui->cbTimeScale->currentIndex();
    emit this->updateTimeUnits(index);
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
    updateAcqConf();
    emit this->daqModule->update_acq_conf(this->acq_conf);

}

void MainWindow::updateSbSampling(int value){
    double Sampling = (1.0/(100000000.0 - value+1.0))*100000000.0;
    this->ui->sbSampling->setValue(Sampling);

    acq_visual_conf.sampling = (unsigned long)Sampling;
    acq_time_window_max = (1/Sampling)*MAX_SAMPLES;
    acq_visual_conf.undersample = (int)(100000000.0 - value+1.0);


}

void MainWindow::updateDialSampling(){
    //this->ui->dialSampling->setValue((int)value);
    //acq_visual_conf.sampling = value;

}



void MainWindow::updateAcqConf(){
    checkTimingAndSampling();

    //if (this->frmsettings-) board_id

    this->acq_conf.range = this->acq_visual_conf.range;
    this->acq_conf.posamples = (unsigned long)(acq_visual_conf.pos_samples_time*acq_visual_conf.sampling);
    this->acq_conf.presamples = (unsigned long)(acq_visual_conf.pre_samples_time*acq_visual_conf.sampling);
    this->acq_conf.trigger_threshold = this->ui->dialTrigger->value();
    this->acq_conf.undersampling =1;

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
    this->vxt->vAxisUpdated = false;
    this->vxt->tAxisUpdated = false;
    //this->vxt->vCursor1Updated = false;
    //this->vxt->vCursor2Updated = false;
    //this->vxt->lThresholdLineUpdated = false;

    this->vxt->acq_visual_conf = this->acq_visual_conf;


}

void MainWindow::checkTimingAndSampling(){
    double preTime = ui->sbPreSamples->value();
    double posTime = ui->sbPosSamples->value();




    switch (this->ui->cbTimeScale->currentIndex()) {
    case 0:
        //ns
        preTime=preTime*pow(10.0,-9.0);
        posTime=posTime*pow(10.0,-9.0);
        break;
    case 1:
        //us
        preTime=preTime*pow(10.0,-6.0);
        posTime=posTime*pow(10.0,-6.0);
        break;
    case 2:
        //ms
        preTime=preTime*pow(10.0,-3.0);
        posTime=posTime*pow(10.0,-3.0);
        break;
    default:
        //s
        break;
    }

    acq_visual_conf.pre_samples_time = preTime;
    acq_visual_conf.pos_samples_time = posTime;

    /*
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

void MainWindow::updateTriggerChannel(){

    updateAcqConf();
    emit this->daqModule->update_acq_conf(this->acq_conf);

}

void MainWindow::on_cbVCursor1_toggled(bool checked)
{
    this->vxt->vCursor1Enabled = checked;
}

void MainWindow::on_cbVCursor2_toggled(bool checked)
{
    this->vxt->vCursor2Enabled = checked;
}


void MainWindow::GetUpdatedDaqState(DaqState_t DaqState){
    QPalette palette;
    switch (DaqState) {
    case IDLE :
        palette.setColor( QPalette::WindowText, Qt::darkGreen );
        this->statusBar()->setPalette(palette);
        this->statusBar()->showMessage("Ready");
        break;
    case NON_TRIGGERED :
        palette.setColor( QPalette::WindowText, Qt::red  );
        this->statusBar()->setPalette(palette);
        this->statusBar()->showMessage("Waiting for trigger");
        break;
    default:
        palette.setColor( QPalette::WindowText, Qt::blue  );
        this->statusBar()->setPalette(palette);;
        this->statusBar()->showMessage("Acquiring data");
        break;
    }
}

void MainWindow::on_btnHistSave_released()
{
    emit saveHist(this->ui->txtHistFilePath->text().toLocal8Bit().data());
}

void MainWindow::on_btnVxtSave_released()
{
    emit saveGraph(this->ui->txtVxtFilePath->text().toLocal8Bit().data());
}
