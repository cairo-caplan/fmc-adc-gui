#include "frmsettings.h"
#include "ui_frmsettings.h"
#include <iostream>

FrmSettings::FrmSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::frmSettings)
{
    ui->setupUi(this);

    QDir adcBoardDir("/sys/bus/zio/devices/");
    QStringList filters;
         filters << "adc-100m14b-*";
    QStringList adcBoardsList = adcBoardDir.entryList(filters);

    ui->cbAdcBoard->clear();
    ui->cbAdcBoard->addItems(adcBoardsList);
    ui->cbAdcBoard->setCurrentIndex(0);

    for (int i = 0; i < adcBoardsList.size(); ++i)
             std::cout << adcBoardsList.at(i).toLocal8Bit().constData() << endl;


    strcpy(acq_path_settings.acq_prog_path,
            this->ui->txtAcqProgPath->text().toLocal8Bit().data());
    strcpy( acq_path_settings.acq_buffer_path,
            this->ui->txtBufferPath->text().toLocal8Bit().data());
    puts(acq_path_settings.acq_buffer_path);

    connect(this->ui->btnboxGuiSettings,SIGNAL(accepted()),this,SLOT(updateSettings()));

    emit updateSettings();
}

FrmSettings::~FrmSettings()
{
    delete ui;
}

void FrmSettings::updateSettings(){

    strcpy(acq_path_settings.adc_board_pci_id,
           this->ui->cbAdcBoard->currentText().toLocal8Bit().data());
    strcpy(acq_path_settings.acq_prog_path,
            this->ui->txtAcqProgPath->text().toLocal8Bit().data());
    strcpy( acq_path_settings.acq_buffer_path,
            this->ui->txtBufferPath->text().toLocal8Bit().data());
    puts(acq_path_settings.acq_buffer_path);

    emit this->newAcqPathSettings(acq_path_settings);

}

char* FrmSettings::getBoardId(){
    char board_id[5];
    //strcpy(this->ui->cbAdcBoard->currentText().at(.toLocal8Bit().data();
    return NULL;
}
