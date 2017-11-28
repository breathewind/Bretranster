/***********************************************************************
 *           Author: Wenlong Wang
 *      Create date: 28/11/2017
 * Modifiacion date: 28/11/2017
 *      Description: Contribution files dialog
 *  Functoin Number: 0XX - normal logic
 *                   1XX - slot
 *                   8XX - get/set functions
 *                   9XX - debug functions
 ***********************************************************************/
#ifndef C0101_FILE_DIALOG_H
#define C0101_FILE_DIALOG_H

#include <QDialog>
#include <QTableWidgetItem>

namespace Ui {
class File_Dialog;
}

class File_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit File_Dialog(QWidget *parent = 0);
    ~File_Dialog();

    //Function 002: Get file information
    bool getInformation(QStringList info_list);

private slots:
    //Function 100: Slot for Add file button clicked
    void on_pushButton_add_clicked();
    //Function 101: Slot for Remove file button clicked
    void on_pushButton_remove_clicked();
    //Function 102: Slot for updatinging file information when certain cell content changed
    void on_tableWidget_cellChanged(int row, int column);
    //Function 103: Slot for OK buttoon clicked
    void on_buttonBox_accepted();

private:
    Ui::File_Dialog *ui;
    int row_count;
    QStringList file_name_list;
    QStringList data_list;
    QStringList start_percent_list;
    QStringList end_percent_list;
    bool update_flag;

    //Function 003: Insert one row into table widget
    void insertRow(QString file_name, QString start, QString end);
    //Function 004: Delete one row from table widget
    void deleteRow();
    //Function 005: Update table widget
    void updateTable();
    //Function 900: Debug function - print all file information
    void debug_output_file_info();
signals:
    void data_process(QStringList data_list, QStringList file_info_list);
};

#endif // C0101_FILE_DIALOG_H
