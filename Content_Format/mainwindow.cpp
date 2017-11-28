/***********************************************************************
 *           Author: Wenlong Wang
 *      Create date: 20/11/2017
 * Modifiacion date: 28/11/2017
 *      Description: Main window of content format application
 *  Functoin Number: 0XX - normal logic
 *                   3XX - slot
 *                   8XX - get/set functions
 *                   9XX - debug functions
 ***********************************************************************/
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QMessageBox>

/***********************************************************************
 *             Name: MainWindow
 *      Function ID: 000
 *      Create date: 20/11/2017
 * Modifiacion date: 28/11/2017
 *      Description: Construction function of main window
 ***********************************************************************/
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    option_dialog = new Options_Dialog();
    conf_info = new Conf_Info();
    file_dialog = new File_Dialog();
    connect(option_dialog, SIGNAL(updateOptions_information()), this, SLOT(updateOption_information()));
    connect(file_dialog, SIGNAL(data_process(QStringList, QStringList)), this, SLOT(getProcessed_data(QStringList, QStringList)));
}

/***********************************************************************
 *             Name: ~MainWindow
 *      Function ID: 001
 *      Create date: 20/11/2017
 * Modifiacion date: 20/11/2017
 *      Description: Deconstruction function of main window
 ***********************************************************************/
MainWindow::~MainWindow()
{
    delete ui;
}

/***********************************************************************
 *             Name: initilaize
 *      Function ID: 002
 *      Create date: 20/11/2017
 * Modifiacion date: 28/11/2017
 *      Description: Initialization
 ***********************************************************************/
bool MainWindow::initilaize()
{
    setWindowTitle("Bretranster");
    loadProject_information(PROJECT_INFO_FILE);
    if(!conf_info->getLanguage_information(LANGUAGE_INFO_FILE)){
        QMessageBox::critical(NULL, "Error", "Language configuration file is missing");
        return false;
    }
    option_dialog->setOptions_information(conf_info);
    updateLanguage_details();
    return true;
}

/***********************************************************************
 *             Name: convertText_format
 *      Function ID: 003
 *      Create date: 20/11/2017
 * Modifiacion date: 28/11/2017
 *      Description: Convert text format
 ***********************************************************************/
void MainWindow::convertText_format(QString text)
{
    QStringList info_list = handleInput_text(text);

    file_dialog->getInformation(info_list);
    file_dialog->show();
}

/***********************************************************************
 *             Name: handleInput_text
 *      Function ID: 004
 *      Create date: 20/11/2017
 * Modifiacion date: 20/11/2017
 *      Description: Extract useful information from text and save into
 *                   a QStringList
 ***********************************************************************/
QStringList MainWindow::handleInput_text(QString text)
{
    QStringList line_list;

    int line_count = text.count("\n");
    int line_num = 1;

    for(int i=0; i<line_count; i++){
        QString first_line_in_text = text.left(text.indexOf("\n"));
        text = text.right(text.length() - text.indexOf("\n") - 1);
        QString processed_line = QString().number(line_num) ;
        int counter = 0;
        while(first_line_in_text.contains("\t") && counter < 2){
            processed_line.append("|" + first_line_in_text.left(first_line_in_text.indexOf("\t")));
            first_line_in_text = first_line_in_text.right(first_line_in_text.length() - first_line_in_text.indexOf("\t") - 1);
            counter++;
        }
        processed_line.append("\n");
        line_list.append(processed_line);
        line_num++;
    }
    // Process the last line
    if(text.length()>0){
        QString processed_line = QString().number(line_num) ;
        int counter = 0;
        while(text.contains("\t") && counter < 2){
            processed_line.append("|" + text.left(text.indexOf("\t")));
            text = text.right(text.length() - text.indexOf("\t") - 1);
            counter++;
        }
        processed_line.append("\n");
        line_list.append(processed_line);
    }
    return line_list;
}

/***********************************************************************
 *             Name: updateLanguage_details
 *      Function ID: 005
 *      Create date: 21/11/2017
 * Modifiacion date: 28/11/2017
 *      Description: Update language details
 ***********************************************************************/
void MainWindow::updateLanguage_details()
{
    ui->label_project_name->setText(conf_info->getProject_name());
    ui->label_project_crowdin->setText(conf_info->getProject_crowdin());
    ui->label_project_url->setText(conf_info->getProject_url());
    ui->label_project_info->setText(conf_info->getProject_info());
    ui->label_source->setText(conf_info->getOrigin_text());
    ui->label_destination->setText(conf_info->getFormated_text());
    file_dialog->setWindowTitle(conf_info->getFile_dialoag_title());
}

/***********************************************************************
 *             Name: saveProject_information
 *      Function ID: 006
 *      Create date: 28/11/2017
 * Modifiacion date: 28/11/2017
 *      Description: Save project informatin to file
 ***********************************************************************/
void MainWindow::saveProject_information(QString filename)
{
    QFile file(filename);
    if(file.exists()){
        file.remove();
    }
    if(!file.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this, "Warning", "Failed to open file:\n" + file.fileName() + "\nfor writing. Error information:\n" + file.errorString());
        return;
    }
    QTextStream out(&file);
    out << ui->lineEdit_project_name->text() << "\n";
    out << ui->lineEdit_project_crowdin->text() << "\n";
    out << ui->lineEdit_project_url->text() << "\n";
    out << ui->lineEdit_your_contribution_url->text() << "\n";
    out << ui->textEdit_project_info->toPlainText() << "\n";
    file.flush();
    file.close();
}


/***********************************************************************
 *             Name: loadProject_information
 *      Function ID: 007
 *      Create date: 28/11/2017
 * Modifiacion date: 28/11/2017
 *      Description: Load project informatin to file
 ***********************************************************************/
bool MainWindow::loadProject_information(QString filename)
{
    QFile file(filename);
    if(!file.open(QFile::ReadOnly | QFile::Text)){
//        QMessageBox::warning(this, "Warning", "Failed to open file:\n" + file.fileName() + "\nfor writing. Error information:\n" + file.errorString());
        return false;
    }
    QTextStream in(&file);
    ui->lineEdit_project_name->setText(in.readLine());
    ui->lineEdit_project_crowdin->setText(in.readLine());
    ui->lineEdit_project_url->setText(in.readLine());
    ui->lineEdit_your_contribution_url->setText(in.readLine());
    ui->textEdit_project_info->setText(in.readAll());
    file.close();
    return true;
}

/***********************************************************************
 *             Name: on_pushButton_convert_text_format_clicked
 *      Function ID: 100
 *      Create date: 20/11/2017
 * Modifiacion date: 28/11/2017
 *      Description: Slot for Convert_Text_Format button pressed
 ***********************************************************************/
void MainWindow::on_pushButton_convert_text_format_clicked()
{
    convertText_format(ui->plainTextEdit_source->toPlainText());
}

/***********************************************************************
 *             Name: on_actionCopy_Translated_Text_triggered
 *      Function ID: 101
 *      Create date: 20/11/2017
 * Modifiacion date: 20/11/2017
 *      Description: Slot for Copy_Translated_Text button pressed
 ***********************************************************************/
void MainWindow::on_actionCopy_Translated_Text_triggered()
{
    ui->textBrowser_destination->selectAll();
    ui->textBrowser_destination->copy();
}

/***********************************************************************
 *             Name: on_actionClear_triggered
 *      Function ID: 102
 *      Create date: 20/11/2017
 * Modifiacion date: 20/11/2017
 *      Description: Slot for Clear button pressed
 ***********************************************************************/
void MainWindow::on_actionClear_triggered()
{
    ui->textBrowser_destination->clear();
    ui->plainTextEdit_source->clear();
}

/***********************************************************************
 *             Name: on_actionUndo_triggered
 *      Function ID: 103
 *      Create date: 20/11/2017
 * Modifiacion date: 20/11/2017
 *      Description: Slot for Undo button pressed
 ***********************************************************************/
void MainWindow::on_actionUndo_triggered()
{
    ui->plainTextEdit_source->undo();
}

/***********************************************************************
 *             Name: on_actionRedo_triggered
 *      Function ID: 104
 *      Create date: 20/11/2017
 * Modifiacion date: 20/11/2017
 *      Description: Slot for Redo button pressed
 ***********************************************************************/
void MainWindow::on_actionRedo_triggered()
{
    ui->plainTextEdit_source->redo();
}

/***********************************************************************
 *             Name: on_actionCopy_triggered
 *      Function ID: 105
 *      Create date: 20/11/2017
 * Modifiacion date: 20/11/2017
 *      Description: Slot for Copy button pressed
 ***********************************************************************/
void MainWindow::on_actionCopy_triggered()
{
    ui->plainTextEdit_source->copy();
}

/***********************************************************************
 *             Name: on_actionCut_triggered
 *      Function ID: 106
 *      Create date: 20/11/2017
 * Modifiacion date: 20/11/2017
 *      Description: Slot for Cut button pressed
 ***********************************************************************/
void MainWindow::on_actionCut_triggered()
{
    ui->plainTextEdit_source->cut();
}

/***********************************************************************
 *             Name: on_actionPaste_triggered
 *      Function ID: 107
 *      Create date: 20/11/2017
 * Modifiacion date: 20/11/2017
 *      Description: Slot for Paste button pressed
 ***********************************************************************/
void MainWindow::on_actionPaste_triggered()
{
    ui->plainTextEdit_source->paste();
}

/***********************************************************************
 *             Name: on_actionOptions_triggered
 *      Function ID: 108
 *      Create date: 20/11/2017
 * Modifiacion date: 21/11/2017
 *      Description: Slot for Options button pressed
 ***********************************************************************/
void MainWindow::on_actionOptions_triggered()
{
    option_dialog->show();
}

/***********************************************************************
 *             Name: on_actionInformation_triggered
 *      Function ID: 109
 *      Create date: 20/11/2017
 * Modifiacion date: 24/11/2017
 *      Description: Slot for Information button pressed
 ***********************************************************************/
void MainWindow::on_actionInformation_triggered()
{
    QString about_text;
    about_text = "Author : Wenlong Wang\n";
    about_text += "Version : 1.0.0.0\n";
    about_text += "Create Date : 20/11/2017\n";
    about_text += "Last Modification : 28/11/2017\n";
    QMessageBox::about(this,"Information",about_text);
}

/***********************************************************************
 *             Name: on_actionExit_triggered
 *      Function ID: 110
 *      Create date: 20/11/2017
 * Modifiacion date: 20/11/2017
 *      Description: Slot for Exit button pressed
 ***********************************************************************/
void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

/***********************************************************************
 *             Name: on_updateOption_information
 *      Function ID: 111
 *      Create date: 21/11/2017
 * Modifiacion date: 28/11/2017
 *      Description: Slot for updating options information
 ***********************************************************************/
void MainWindow::updateOption_information()
{
    qDebug() << "updateOption_information";
    saveProject_information(PROJECT_INFO_FILE);
    option_dialog->updateInformation();
    updateLanguage_details();
    update();
}

/***********************************************************************
 *             Name: on_actionSave_project_information_triggered
 *      Function ID: 112
 *      Create date: 28/11/2017
 * Modifiacion date: 28/11/2017
 *      Description: Slot for Save button pressed
 ***********************************************************************/
void MainWindow::on_actionSave_project_information_triggered()
{
    saveProject_information(PROJECT_INFO_FILE);
}

/***********************************************************************
 *             Name: getProcessed_data
 *      Function ID: 113
 *      Create date: 28/11/2017
 * Modifiacion date: 28/11/2017
 *      Description: Slot for receiving processed data
 ***********************************************************************/
void MainWindow::getProcessed_data(QStringList data_list, QStringList file_info_list)
{
    QString converted_text;
    converted_text.append("I performed translation for " + ui->lineEdit_project_name->text() + " in simplified Chinese.\n");
    converted_text.append(">");
    converted_text.append(ui->textEdit_project_info->toPlainText());
    converted_text.append("\n You can check " + ui->lineEdit_project_name->text() + " project information on ");
    converted_text.append("[crowdin](" + ui->lineEdit_project_crowdin->text() + ")");
    converted_text.append(" or ");
    converted_text.append("[its website](" + ui->lineEdit_project_url->text() + ")");
    converted_text.append(".\n");
    converted_text.append("\n");

    converted_text.append("I suggested " + QString().number(data_list.size()) + " translations. You can verify my contributions on following url:\n");
    converted_text.append(ui->lineEdit_your_contribution_url->text());
    converted_text.append("\n");

    converted_text.append("\n");
    converted_text.append("In details, I translated following files:\n");
    converted_text.append("File name | My contribution percentage | Starting translation percentage | Ending translation percentage\n");
    converted_text.append("------------ | ----------------------  | -------------  | -------------\n");
    for(int i=0; i<file_info_list.size(); i++){
        converted_text.append(file_info_list.at(i));
    }

    converted_text.append("\n");
    converted_text.append("<br>\n");
    converted_text.append("\n");
    converted_text.append("Snap shots before translation:\n");
    converted_text.append("\n");
    converted_text.append("<center></center>\n");
    converted_text.append("\n");
    converted_text.append("<br>\n");
    converted_text.append("\n");
    converted_text.append("Snap shots after translation:\n");
    converted_text.append("\n");
    converted_text.append("<center></center>\n");
    converted_text.append("\n");
    converted_text.append("<br>\n");
    converted_text.append("\n");
    converted_text.append("I also list all the translations which I contributed in following part:\n");
    converted_text.append("No.|Translation                           | File\n");
    converted_text.append("--- | ---------------------------------------------- | -------------\n");
    for(int i=0; i<data_list.size(); i++){
        converted_text.append(data_list.at(i));
    }

    ui->textBrowser_destination->setText(converted_text);
    ui->textBrowser_destination->moveCursor(QTextCursor::End);
}
