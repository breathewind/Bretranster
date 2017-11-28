/***********************************************************************
 *           Author: Wenlong Wang
 *      Create date: 20/11/2017
 * Modifiacion date: 28/11/2017
 *      Description: Options dialog
 *  Functoin Number: 0XX - normal logic
 *                   1XX - slot
 *                   8XX - get/set functions
 *                   9XX - debug functions
 ***********************************************************************/
#include "c0100_options_dialog.h"
#include "ui_c0100_options_dialog.h"

#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QDebug>

/***********************************************************************
 *             Name: Options_Dialog
 *      Function ID: 000
 *      Create date: 20/11/2017
 * Modifiacion date: 20/11/2017
 *      Description: Construction function of options dialog
 ***********************************************************************/
Options_Dialog::Options_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Options_Dialog)
{
    ui->setupUi(this);
    setModal(true);
}

/***********************************************************************
 *             Name: ~Options_Dialog
 *      Function ID: 001
 *      Create date: 20/11/2017
 * Modifiacion date: 20/11/2017
 *      Description: Deconstruction function of options dialog
 ***********************************************************************/
Options_Dialog::~Options_Dialog()
{
    delete ui;
}

/***********************************************************************
 *             Name: setOptions_information
 *      Function ID: 002
 *      Create date: 20/11/2017
 * Modifiacion date: 21/11/2017
 *      Description: Set options information
 ***********************************************************************/
void Options_Dialog::setOptions_information(Conf_Info *info)
{
    conf_info = info;
    updateInformation();
}

/***********************************************************************
 *             Name: updateInformation
 *      Function ID: 003
 *      Create date: 20/11/2017
 * Modifiacion date: 21/11/2017
 *      Description: Update all the option information up-to-date
 ***********************************************************************/
void Options_Dialog::updateInformation()
{
    ui->comboBox_language->clear();
    ui->comboBox_language->addItems(conf_info->getLanguage_name());
    ui->comboBox_language->setCurrentIndex(conf_info->getCurrent_language_index());
}

/***********************************************************************
 *             Name: updateLanguage_configuration_file
 *      Function ID: 004
 *      Create date: 21/11/2017
 * Modifiacion date: 25/11/2017
 *      Description: Update language configuration file
 ***********************************************************************/
void Options_Dialog::updateLanguage_configuration_file()
{
    QFile file("conf/language_info.conf");
//    qDebug() << "exists?              " << file.exists();
//    qDebug() << "writable?            " << file.isWritable();
//    qDebug() << "permissions before?  " << file.permissions();
//    qDebug() << "permissions set?     " << file.setPermissions(QFileDevice::WriteOther | QFileDevice::ReadOther);
//    qDebug() << "permissions after?   " << file.permissions();

//    qDebug() << "opened?              " << file.open(QIODevice::Append);
//    qDebug() << "errors?              " << file.errorString();
//    qDebug() << "errnum?              " << file.error();

    if(!file.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this, "Warning", "Failed to open file:\n" + file.fileName() + "\nfor writing. Error information:\n" + file.errorString());
    }else{
        QTextStream out(&file);
        out << conf_info->getCurrent_language_index() << "\n";
        qDebug() << conf_info->getCurrent_language_index();
        for(int i=0; i<conf_info->getLanguage_name().size(); i++){
            out << conf_info->getLanguage_name().at(i) << " " << conf_info->getLanguage_file_pointer()->at(i) << "\n";
            qDebug() << conf_info->getLanguage_name().at(i) << " " << conf_info->getLanguage_file_pointer()->at(i);
        }
        file.flush();
        file.close();
    }
}

/***********************************************************************
 *             Name: on_buttonBox_accepted
 *      Function ID: 100
 *      Create date: 20/11/2017
 * Modifiacion date: 21/11/2017
 *      Description: Accept option update
 ***********************************************************************/
void Options_Dialog::on_buttonBox_accepted()
{
    conf_info->setCurrent_language_index(ui->comboBox_language->currentIndex());
    conf_info->getLanguage_details();
    updateLanguage_configuration_file();

    emit updateOptions_information();
}
