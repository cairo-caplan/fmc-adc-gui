#include "daqmodule.h"
#include <iostream>

static acq_conf_t init_acq_conf(acq_conf_t acq_conf){
    acq_conf.range = R_10V;
    acq_conf.presamples = 100;
    acq_conf.posamples = 100;
    acq_conf.trigger_threshold = 10;
    acq_conf.undersampling = 1;
    acq_conf.trigger = INTERNAL;
    acq_conf.trigger_channel = CH1;
    acq_conf.trigger_edge = RISING;
    return acq_conf;
}


DAQmodule::DAQmodule(){
    setup();
    finished=true;
    QStrFinal.reserve(200);
}

void DAQmodule::setup(){
    m_run_acq = false;
    this->DaqState = IDLE;
    emit this->updateState(DaqState);
    this->acq_conf = init_acq_conf(this->acq_conf);

}

void DAQmodule::run(){
    qDebug()<<"From worker thread: "<<currentThreadId();
}


// Start acquisition process loop
void DAQmodule::start_acq()
    {
        qDebug()<<"Thread::start called from main thread: "<<currentThreadId();
        QMutexLocker locker(&m_mutex);
        m_run_acq=true;

        //Create an asynchronous process to execute que command line acq_program
        proc = new QProcess();
        connect(proc,SIGNAL(finished(int)),this,SLOT(setFinished(int)));
        acqTimer = new QTimer(0);
        //After the timeout of the process, run doAcq function
        connect(acqTimer,SIGNAL(timeout()),this,SLOT(doAcq()));
        //Set run intervals/timeout to 100 ms
        //Empirically, 200ms = 13% CPU usage and 100ms = 65% CPU usage
        acqTimer->setInterval(100);
        DaqState = RUNNING;
        acqTimer->start();
    }


void DAQmodule::stop_acq()
    {
        qDebug()<<"Thread::stop called from main thread: "<<currentThreadId();
        QMutexLocker locker(&m_mutex);
        m_run_acq=false;
        acqTimer->stop();

        //volatile int pid = proc->pid();
        //std::cout << "PID = " << pid << std::endl;
        //If process is still alive, try to finish it
        while ((proc->state() != QProcess::NotRunning)){
            //if it hasn't finsihed yet
            QCoreApplication::processEvents();
            //(proc->waitForFinished(100)==false
            //proc->waitForFinished(100);
            proc->terminate();
        }

        DaqState = IDLE;
        emit this->updateState(DaqState);
    }

void DAQmodule::update_acq_conf(acq_conf_t acq_conf){
    QMutexLocker locker(&m_mutex);
    this->acq_conf = acq_conf;


    acq_program_arg.clear();

    //acq_program_arg.append("./acq-program ");
    acq_program_arg.append(" -b ");
    acq_program_arg.append(QString::number(acq_conf.presamples));
    acq_program_arg.append(" -a ");
    acq_program_arg.append(QString::number(acq_conf.posamples));
    acq_program_arg.append(" -n 1");
    acq_program_arg.append(" -u ");
    acq_program_arg.append(QString::number(acq_conf.undersampling));
    if (acq_conf.trigger==INTERNAL){
        acq_program_arg.append(" -t ");
        acq_program_arg.append(QString::number(acq_conf.trigger_threshold));
        acq_program_arg.append(" -c ");
        acq_program_arg.append(QString::number(acq_conf.trigger_channel));
    }
    else{
        acq_program_arg.append(" -e ");
    }

    if (acq_conf.trigger_edge==FALLING){
        acq_program_arg.append(" --negative-edge");
    }

    acq_program_arg.append(" -r ");
    acq_program_arg.append(QString::number(acq_conf.range));

    acq_program_arg.append(" 0x200 ");


}

//Function that emits a signal acqAvailable once the execution
// of the acq_program was completed
void DAQmodule::setFinished(int dummy){
    //If it was not terminated by the doAcq procedure
    if (this->finished==false){
        DaqState = RUNNING;
        this->finished = true;
        emit this->acqAvailable(true);
        emit updateState(DaqState);
    }
}

void DAQmodule::doAcq(){
    {
        QMutexLocker locker(&m_mutex);
        //If the acquisition mode is active
        if (m_run_acq==true){
            // If the process is not running, because it finished before for instance
            if ((proc->state() == QProcess::NotRunning) || this->finished==true){
                finished=false;
                //puts ("Not Running");
                //proc->start("/usr/bin/kwrite");
                QStrFinal.clear();

                QStrFinal.append(acq_path_settings.acq_prog_path);
                QStrFinal.append(" ");
                QStrFinal.append(acq_program_arg);
                QStrFinal.append(" 1> ");
                QStrFinal.append(acq_path_settings.acq_buffer_path);
                QStrFinal.append("/fmcadc.0x0200.dat");

                QStrFinal.append(" 2> ");
                QStrFinal.append(acq_path_settings.acq_buffer_path);
                QStrFinal.append("/fmcadc.0x0200.err.txt");

                //puts(QStrFinal.toLocal8Bit().data());
                proc->start("sh");

                proc->write(QStrFinal.toLocal8Bit().data());
                //proc->write("kate");
                //std::cout << QStrFinal.toLocal8Bit().data() << '\n' << endl;

                proc->closeWriteChannel();
                proc->waitForStarted();
                //connect(procTimer,SIGNAL(timeout()),proc,SLOT(terminate()));
                //printf("pid = %lld\n",proc->pid());

                //proc->waitForFinished();
                //QByteArray output = sh.readAll();
                //proc->close();

                //proc->waitForStarted();
                //printf("pid = %lld\n",proc->pid());
                //proc->waitForFinished();

            }
            //else if it is still running
            else{
                DaqState = NON_TRIGGERED;
                 emit this->updateState(DaqState);
                QCoreApplication::processEvents();

                this->finished = true;

                //Update the canvas, but with no new samples
                emit this->acqAvailable(false);

                if ((proc->state() != QProcess::NotRunning)){
                    //if it hasn't finsihed yet
                    //proc->waitForFinished(100);
                    proc->terminate();
                    //lol->stop();

                }

//                if (proc->waitForFinished(100)==false){
//                    QCoreApplication::processEvents();
//                    volatile int pid = proc->pid();
//                    std::cout << "PID = " << pid << std::endl;
//                    proc->terminate();
//                    pid = proc->pid();
//                    std::cout << "PID = " << pid << std::endl;
//                    DaqState = NON_TRIGGERED;
//                }else{
//                    DaqState = RUNNING;
//                }


            }
        }
    }
}

void DAQmodule::update_acq_path_settings(acq_path_settings_t acq_path_settings){
    QMutexLocker locker(&m_mutex);
    this->acq_path_settings = acq_path_settings;

}

DaqState_t DAQmodule::getState(){
    return this->DaqState;
}


