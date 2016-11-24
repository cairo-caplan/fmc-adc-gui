#ifndef MAINWINDOW_H
#define MAINWINDOW_H



#include <QMainWindow>

#if QT_VERSION>=0x050000
#include <QtWidgets>
#else
#include <QtGui>
#endif

#include "qmaincanvas.h"
#include "vxtrootcanvas.h"
#include "histogram.h"

#include "aboutwindow.h"
#include "frmsettings.h"
#include "daqmodule.h"




namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
     Histogram *m;
     VxtRootCanvas *vxt;
     DAQmodule* daqModule;

private slots:

     void on_btnStartAcquisition_toggled(bool checked);

     void openAboutWindow();
     void openFrmSettings();

     void updateChannels();
     void updateTerminations();
     void updateCbScale(int value);
     void updateSliderScale(int id);
     void updateDialTrigger(double value);
     void updateSbTriggerValue(int value);
     void updateTriggerChannel();

     void TimeUnitsChanged();
     void updateTimeUnits(int index);
     void updateSbSampling(int value);
     void updateDialSampling();

     void updateAcqConf();
     void checkTimingAndSampling();

     void startAcquisition(bool state);
     void GetUpdatedDaqState(DaqState_t DaqState);

     void on_cbVCursor1_toggled(bool checked);

     void on_cbVCursor2_toggled(bool checked);


     void on_btnHistSave_released();

     void on_btnVxtSave_released();

private:
    Ui::MainWindow *ui;
    AboutWindow *aboutwindow;
    FrmSettings *frmsettings;


    acq_conf_t acq_conf;
    acq_visual_conf_t acq_visual_conf;
    acq_path_settings_t acq_path_settings;

    double acq_time_window_max;

signals:
    void saveHist(char* path);
    void saveGraph(char* path);

};

#endif // MAINWINDOW_H
