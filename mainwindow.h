#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qmaincanvas.h"
#include "vxtrootcanvas.h"

#include "aboutwindow.h"
#include "frmsettings.h"
#include "daqmodule.h"

#include <QMainWindow>

#if QT_VERSION>=0x050000
#include <QtWidgets>
#else
#include <QtGui>
#endif




typedef struct{
    range_t range;
    double threshold_max;
    double threshold_min;
    double pre_samples_time;
    double pos_samples_time;
    unsigned long undersample;
    unsigned long sampling;

} acq_visual_conf_t;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
     QMainCanvas *m;
     VxtRootCanvas *vxt;
     DAQmodule* daqModule;

private slots:
     void on_btnStartAcquisition_pressed();

     void on_btnStartAcquisition_released();

     void on_btnStartAcquisition_toggled(bool checked);

     void openAboutWindow();
     void openFrmSettings();

     void updateChannels(int state);
     void updateCbScale(int value);
     void updateSliderScale(int id);
     void updateDialTrigger(double value);
     void updateSbTriggerValue(int value);

     void updateTimeUnits(int index);
     void updateSbSampling(int value);
     void updateDialSampling(int value);

     void updateAcqConf();
     void checkTimingAndSampling();

     void startAcquisition(bool state);


private:
    Ui::MainWindow *ui;
    AboutWindow *aboutwindow;
    FrmSettings *frmsettings;


    acq_conf_t acq_conf;
    acq_visual_conf_t acq_visual_conf;
    acq_path_settings_t acq_path_settings;

    double acq_time_window_max = 0.0000001;
};

#endif // MAINWINDOW_H
