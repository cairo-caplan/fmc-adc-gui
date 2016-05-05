#include "frmsettings.h"
#include "ui_frmsettings.h"

FrmSettings::FrmSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::frmSettings)
{
    ui->setupUi(this);
    strcpy(acq_path_settings.acq_prog_path,
            this->ui->txtAcqProgPath->text().toLocal8Bit().data());
    strcpy( acq_path_settings.acq_buffer_path,
            this->ui->txtBufferPath->text().toLocal8Bit().data());
    puts(acq_path_settings.acq_buffer_path);

    connect(this->ui->btnboxGuiSettings,SIGNAL(accepted()),this,SLOT(updateSettings()));
}

FrmSettings::~FrmSettings()
{
    delete ui;
}

void FrmSettings::updateSettings(){
    strcpy(acq_path_settings.acq_prog_path,
            this->ui->txtAcqProgPath->text().toLocal8Bit().data());
    strcpy( acq_path_settings.acq_buffer_path,
            this->ui->txtBufferPath->text().toLocal8Bit().data());
    puts(acq_path_settings.acq_buffer_path);

    emit this->newAcqPathSettings(acq_path_settings);

}
