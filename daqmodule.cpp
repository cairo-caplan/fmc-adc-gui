#include "daqmodule.h"

DAQmodule::DAQmodule(){
    setup();
    finished=true;
    QStrFinal.reserve(200);
}

void DAQmodule::setup(){
    m_run_acq = false;
}

void DAQmodule::run(){
    qDebug()<<"From worker thread: "<<currentThreadId();
}

void DAQmodule::start_acq()
    {
        qDebug()<<"Thread::start called from main thread: "<<currentThreadId();
        QMutexLocker locker(&m_mutex);
        m_run_acq=true;

        proc = new QProcess();
        connect(proc,SIGNAL(finished(int)),this,SLOT(setFinished(int)));
        lol = new QTimer(0);
        connect(lol,SIGNAL(timeout()),this,SLOT(doAcq()));
        lol->setInterval(100);
        lol->start();
    }


void DAQmodule::stop_acq()
    {
        qDebug()<<"Thread::stop called from main thread: "<<currentThreadId();
        QMutexLocker locker(&m_mutex);
        m_run_acq=false;
        proc->kill();
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
    //acq_program_arg.append(" 1> /dev/shm/fmcadc.0x0200.dat 2> /dev/shm/fmcadc.err.txt");


    //const char* final = acq_program_arg.toAscii().data();
    //puts(final);



}

void DAQmodule::setFinished(int ExitCode){
    this->finished = true;
    emit this->acqAvailable();
}

void DAQmodule::doAcq(){
    {
        QMutexLocker locker(&m_mutex);
        if (m_run_acq==true){
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

                proc->closeWriteChannel();
                proc->waitForStarted();
                //printf("pid = %lld\n",proc->pid());

                //proc->waitForFinished();
                //QByteArray output = sh.readAll();
                //proc->close();

                //proc->waitForStarted();
                //printf("pid = %lld\n",proc->pid());
                //proc->waitForFinished();

            }
            else{
                //puts ("Running");

            }
        }
    }
}

void DAQmodule::update_acq_path_settings(acq_path_settings_t acq_path_settings){
    QMutexLocker locker(&m_mutex);
    this->acq_path_settings = acq_path_settings;

}


