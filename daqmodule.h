#ifndef DAQMODULE_H
#define DAQMODULE_H

#include "acq_types.h"

#include <QObject>
#if QT_VERSION>=0x050000
#include <QtWidgets>
#else
#include <QtGui>
#endif

#include <QString>



class DAQmodule : public QThread
{
    Q_OBJECT

public:
    DAQmodule();

    acq_path_settings_t acq_path_settings;

public slots:
    void update_acq_conf(acq_conf_t acq_conf);
    void update_acq_path_settings(acq_path_settings_t acq_path_settings);

    void start_acq();
    void stop_acq();
    void setup();
    void doAcq();
    DaqState_t getState();

private:
    QMutex m_mutex;

    ///Defines if the acquisition mode is on
    bool m_run_acq;
    acq_conf_t acq_conf;
    DaqState_t DaqState;

    QString QStrFinal;
    QString acq_program_arg;    
    QProcess* proc;
    QTimer* acqTimer;
    QTimer* procTimer;
    bool finished;
private slots:
    void run();
    void setFinished(int dummy);

signals:
    void acqAvailable(bool success);
    void updateState(DaqState_t DaqState);

};

#endif // DAQMODULE_H
