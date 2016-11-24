#ifndef FRMSETTINGS_H
#define FRMSETTINGS_H

#include <QDialog>

#include "daqmodule.h"

namespace Ui {
class frmSettings;
}

class FrmSettings : public QDialog
{
    Q_OBJECT

public:
    explicit FrmSettings(QWidget *parent = 0);
    ~FrmSettings();
    acq_path_settings_t acq_path_settings;
    char* getBoardId();

signals:
    void newAcqPathSettings(acq_path_settings_t acq_path_settings);


private:
    Ui::frmSettings *ui;

private slots:
    void updateSettings();
};

#endif // FRMSETTINGS_H
