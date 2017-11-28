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
#include "c0101_file_dialog.h"
#include "ui_c0101_file_dialog.h"

#include <QDebug>

File_Dialog::File_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::File_Dialog)
{
    ui->setupUi(this);
    setModal(true);

    row_count = 0;
    update_flag = false;

// Horizontal header setting
    ui->tableWidget->setColumnCount(3);
//    ui->tableWidget->horizontalHeader()->resizeSection(0,121);
    // The last visible section in the header takes up all the available space.
//    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    // Set horizontal header
    QStringList header;
    header << tr("File name") << tr("Starting %") << tr("Ending %");
    ui->tableWidget->setHorizontalHeaderLabels(header);
    // Font set bold
    QFont font = ui->tableWidget->horizontalHeader()->font();
    font.setBold(true);
    ui->tableWidget->horizontalHeader()->setFont(font);
    // Set horizontal content always fit table widget size
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
// Vertical header setting
    ui->tableWidget->verticalHeader()->setDefaultSectionSize(18);

// General setting
    // Set content uneditable
//    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    // Select entire row when you select one item in a row
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    // Single-select mode
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);

//    ui->pushButton_remove->setEnabled(false);
}

File_Dialog::~File_Dialog()
{
    delete ui;
}

/***********************************************************************
 *             Name: getInformation
 *      Function ID: 002
 *      Create date: 28/11/2017
 * Modifiacion date: 28/11/2017
 *      Description: Get file information
 ***********************************************************************/
bool File_Dialog::getInformation(QStringList info_list)
{
    QString line_text;
    QString file_name_text;
    file_name_list.clear();
    data_list.clear();
    row_count = 0;
    update_flag = true;
    ui->tableWidget->setRowCount(0);
    update_flag = false;

    data_list = info_list;

    for(int i=0; i<info_list.size(); i++){
        line_text = info_list.at(i);
//        qDebug() << line_text;
        file_name_text = line_text.right(line_text.size() - line_text.lastIndexOf("|")-1);
        file_name_text = file_name_text.left(file_name_text.size() - 1);
        if(!file_name_list.contains(file_name_text)){
            file_name_list.append(file_name_text);
            start_percent_list.append("0");
            end_percent_list.append("100");
            update_flag = true;
            insertRow(file_name_text, "0", "100");
            update_flag = false;
        }
    }
    return true;
}

/***********************************************************************
 *             Name: insertRow
 *      Function ID: 003
 *      Create date: 28/11/2017
 * Modifiacion date: 28/11/2017
 *      Description: Insert one row into table widget
 ***********************************************************************/
void File_Dialog::insertRow(QString file_name, QString start, QString end)
{
    ui->tableWidget->insertRow(row_count);

    QTableWidgetItem *name = new QTableWidgetItem();
    QTableWidgetItem *start_percent = new QTableWidgetItem();
    QTableWidgetItem *end_percent = new QTableWidgetItem();

    name->setText(file_name);
    start_percent->setText(start);
    end_percent->setText(end);

    start_percent->setTextAlignment(Qt::AlignCenter);
    end_percent->setTextAlignment(Qt::AlignCenter);

    ui->tableWidget->setItem(row_count,0,name);
    ui->tableWidget->setItem(row_count,1,start_percent);
    ui->tableWidget->setItem(row_count,2,end_percent);

    row_count++;
}

/***********************************************************************
 *             Name: deleteRow
 *      Function ID: 004
 *      Create date: 28/11/2017
 * Modifiacion date: 28/11/2017
 *      Description: Delete one row from table widget
 ***********************************************************************/
void File_Dialog::deleteRow()
{
    int row = ui->tableWidget->selectedItems().at(0)->row();
    file_name_list.takeAt(row);
    start_percent_list.takeAt(row);
    end_percent_list.takeAt(row);

    update_flag = true;
    updateTable();
    update_flag = false;
}

/***********************************************************************
 *             Name: updateTable
 *      Function ID: 005
 *      Create date: 28/11/2017
 * Modifiacion date: 28/11/2017
 *      Description: Update table widget
 ***********************************************************************/
void File_Dialog::updateTable()
{
    row_count = 0;
    ui->tableWidget->setRowCount(0);
    for(int i=0; i<file_name_list.size(); i++){
        insertRow(file_name_list.at(i), start_percent_list.at(i), end_percent_list.at(i));
    }
}

/***********************************************************************
 *             Name: on_pushButton_add_clicked
 *      Function ID: 100
 *      Create date: 28/11/2017
 * Modifiacion date: 28/11/2017
 *      Description: Slot for Add file button clicked
 ***********************************************************************/
void File_Dialog::on_pushButton_add_clicked()
{
    file_name_list.append("");
    start_percent_list.append("0");
    end_percent_list.append("100");

    update_flag = true;
    insertRow("","0","100");
    update_flag = false;
}

/***********************************************************************
 *             Name: on_pushButton_remove_clicked
 *      Function ID: 101
 *      Create date: 28/11/2017
 * Modifiacion date: 28/11/2017
 *      Description: Slot for Remove file button clicked
 ***********************************************************************/
void File_Dialog::on_pushButton_remove_clicked()
{
    deleteRow();
}

/***********************************************************************
 *             Name: on_tableWidget_cellChanged
 *      Function ID: 102
 *      Create date: 28/11/2017
 * Modifiacion date: 28/11/2017
 *      Description: Slot for updatinging file information when certain
 *                   cell content changed
 ***********************************************************************/
void File_Dialog::on_tableWidget_cellChanged(int row, int column)
{
//    qDebug() << "row: " << row << " column:" << column;
    if(!update_flag){
//        qDebug() << "inside == row: " << row << " column:" << column;
//        debug_output_file_info();
        switch (column) {
        case 0:
//            qDebug() << "0: " << text;
            file_name_list.replace(row, ui->tableWidget->item(row, column)->text());
            break;
        case 1:
//            qDebug() << "1: " << text;
            start_percent_list.replace(row, ui->tableWidget->item(row, column)->text());
            break;
        case 2:
//            qDebug() << "2: " << text;
            end_percent_list.replace(row, ui->tableWidget->item(row, column)->text());
            break;
        default:
            break;
        }
    }
}

/***********************************************************************
 *             Name: on_buttonBox_accepted
 *      Function ID: 103
 *      Create date: 28/11/2017
 * Modifiacion date: 28/11/2017
 *      Description: Slot for OK buttoon clicked
 ***********************************************************************/
void File_Dialog::on_buttonBox_accepted()
{
    QStringList file_info_list;

    for(int i=0; i<file_name_list.size(); i++){
        QString single_line;
        single_line.append("`" + file_name_list.at(i) + "`|");
        single_line.append(QString().number(end_percent_list.at(i).toInt() - start_percent_list.at(i).toInt()) + "%|");
        single_line.append(start_percent_list.at(i) + "%|");
        single_line.append(end_percent_list.at(i) + "%\n");
        file_info_list.append(single_line);
    }
//    for(int i=0; i<file_info_list.size(); i++){
//        qDebug() << file_info_list.at(i);
//    }
    emit data_process(data_list, file_info_list);
}

/***********************************************************************
 *             Name: debug_output_file_info
 *      Function ID: 900
 *      Create date: 28/11/2017
 * Modifiacion date: 28/11/2017
 *      Description: Debug function - print all file information
 ***********************************************************************/
void File_Dialog::debug_output_file_info()
{
    for(int i=0; i<file_name_list.size(); i++){
        qDebug() << i << ": " << file_name_list.at(i) << " " << start_percent_list.at(i) << " " << end_percent_list.at(i);
    }
}
