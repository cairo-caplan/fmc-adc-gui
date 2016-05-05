#ifndef DAQMODULE_H
#define DAQMODULE_H

#include <QObject>
#if QT_VERSION>=0x050000
#include <QtWidgets>
#else
#include <QtGui>
#endif

#include <QString>

enum trigger_edge_t {RISING,FALLING,BOTH};
enum range_t {R_100mV=100,R_1V=1,R_10V=10};
enum trigger_t {INTERNAL,EXTERNAL};

enum trigger_channel_t {CH1=1,CH2=2,CH3=3,CH4=4};

#define MAX_SAMPLES 2048

typedef struct {
    char acq_prog_path[100];
    char acq_buffer_path[100];
} acq_path_settings_t;



typedef struct{
    range_t range = R_10V;
    unsigned int presamples = 100;
    unsigned int posamples = 100;
    int trigger_threshold = 10;
    unsigned int undersampling = 1;
    trigger_t trigger = INTERNAL;
    trigger_channel_t trigger_channel = CH1;
    trigger_edge_t trigger_edge = RISING;
} acq_conf_t;

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

private:
    QMutex m_mutex;
    bool m_run_acq;
    acq_conf_t acq_conf;

    QString QStrFinal;
    QString acq_program_arg;    
    QProcess* proc;
    QTimer* lol;
    bool finished;
private slots:
    void run();
    void setFinished(int ExitCode);

signals:
    void acqAvailable();

};

#endif // DAQMODULE_H
