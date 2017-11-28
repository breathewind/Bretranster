/***********************************************************************
 *           Author: Wenlong Wang
 *      Create date: 20/11/2017
 * Modifiacion date: 21/11/2017
 *      Description: Options dialog
 *  Functoin Number: 0XX - normal logic
 *                   1XX - slot
 *                   8XX - get/set functions
 *                   9XX - debug functions
 ***********************************************************************/
#ifndef C0100_OPTIONS_DIALOG_H
#define C0100_OPTIONS_DIALOG_H

#include <QDialog>

#include "c0001_conf_info.h"
#include "c0000_parameters.h"

namespace Ui {
class Options_Dialog;
}

class Options_Dialog : public QDialog
{
    Q_OBJECT

public:
    //Function 000: Construction function of options dialog
    explicit Options_Dialog(QWidget *parent = 0);
    //Function 001: Deconstruction function of options dialog
    ~Options_Dialog();
    //Function 002: Set options information
    void setOptions_information(Conf_Info* info);
    //Function 003: Update all the option information up-to-date
    void updateInformation();
    //Function 004: Update language configuration file
    void updateLanguage_configuration_file();

private slots:
    //Function 100: Accept option update
    void on_buttonBox_accepted();

private:
    Ui::Options_Dialog *ui;
    Conf_Info* conf_info;
signals:
    void updateOptions_information();
};

#endif // C0100_OPTIONS_DIALOG_H
