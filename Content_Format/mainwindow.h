/***********************************************************************
 *           Author: Wenlong Wang
 *      Create date: 20/11/2017
 * Modifiacion date: 28/11/2017
 *      Description: Main window of content format application
 *  Functoin Number: 0XX - normal logic
 *                   1XX - slot
 *                   8XX - get/set functions
 *                   9XX - debug functions
 ***********************************************************************/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "c0000_parameters.h"
#include "c0001_conf_info.h"
#include "c0100_options_dialog.h"
#include "c0101_file_dialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    //Function 000: Construction function of main window
    explicit MainWindow(QWidget *parent = 0);
    //Function 001: Deconstruction function of main window
    ~MainWindow();
    //Function 002: Initialization
    bool initilaize();

private:
    //Function 003: Convert text format
    void convertText_format(QString text);
    //Function 004: Extract useful information from text and save into a QStringList
    QStringList handleInput_text(QString text);
    //Function 005: Update language details
    void updateLanguage_details();
    //Function 006: Save project informatin to file
    void saveProject_information(QString filename);
    //Function 007: Load project informatin from file
    bool loadProject_information(QString filename);

private slots:
    //Function 100: Slot for Convert_Text_Format button pressed -
    void on_pushButton_convert_text_format_clicked();

    //Function 101: Slot for Copy_Translated_Text button pressed -
    void on_actionCopy_Translated_Text_triggered();

    //Function 102: Slot for Clear button pressed -
    void on_actionClear_triggered();

    //Function 103: Slot for Undo button pressed -
    void on_actionUndo_triggered();

    //Function 104: Slot for Redo button pressed -
    void on_actionRedo_triggered();

    //Function 105: Slot for Copy button pressed -
    void on_actionCopy_triggered();

    //Function 106: Slot for Cut button pressed -
    void on_actionCut_triggered();

    //Function 107: Slot for Paste button pressed -
    void on_actionPaste_triggered();

    //Function 108: Slot for Options button pressed
    void on_actionOptions_triggered();

    //Function 109: Slot for Information button pressed -
    void on_actionInformation_triggered();

    //Function 110: Slot for Exit button pressed -
    void on_actionExit_triggered();

    //Function 111: Slot for updating options information
    void updateOption_information();

    //Function 112: Slot for Save button pressed
    void on_actionSave_project_information_triggered();

    //Function 113: Slot for receiving processed data
    void getProcessed_data(QStringList data_list, QStringList file_info_list);

private:
    Ui::MainWindow *ui;
    Options_Dialog *option_dialog;
    File_Dialog *file_dialog;
    Conf_Info *conf_info;
};

#endif // MAINWINDOW_H
