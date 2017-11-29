/***********************************************************************
 *           Author: Wenlong Wang
 *      Create date: 20/11/2017
 * Modifiacion date: 29/11/2017
 *      Description: Configuration information
 *  Functoin Number: 0XX - normal logic
 *                   1XX - slot
 *                   8XX - get/set functions
 *                   9XX - debug functions
 ***********************************************************************/
#include "c0001_conf_info.h"

#include <QMessageBox>
#include <QFile>
#include <QDebug>
#include <QDir>


/***********************************************************************
 *             Name: Conf_Info
 *      Function ID: 000
 *      Create date: 20/11/2017
 * Modifiacion date: 20/11/2017
 *      Description: Construction function of configuration information
 *                   class
 ***********************************************************************/
Conf_Info::Conf_Info()
{

}

/***********************************************************************
 *             Name: ~Conf_Info
 *      Function ID: 001
 *      Create date: 20/11/2017
 * Modifiacion date: 20/11/2017
 *      Description: Deconstruction function of configuration
 *                   information class
 ***********************************************************************/
Conf_Info::~Conf_Info()
{

}

/***********************************************************************
 *             Name: getLanguage_information
 *      Function ID: 002
 *      Create date: 20/11/2017
 * Modifiacion date: 28/11/2017
 *      Description: Retrieve language information from file
 ***********************************************************************/
bool Conf_Info::getLanguage_information(QString filename)
{
    // Open language configuration file
    QFile file(filename);
    qDebug() << "language_info.conf exists? " << file.exists();
    if(!file.open(QFile::ReadOnly | QFile::Text)){
        qDebug() << "Failed to open language configuration file: " + file.fileName();
        qDebug() << "Error information: " + file.errorString();

        if(!QDir("conf/").exists()){
            QDir().mkdir("conf");
        }
        qDebug() << "conf/ exists?              " << QDir("conf/").exists();
        // Create language configuration file
        if(QFile("conf/language_info.conf").exists()){
            QFile("conf/language_info.conf").remove();
        }
        QFile conf_file(":/file/conf/language_info.conf");
        qDebug() << "language_info.conf exists? " << conf_file.exists();

        conf_file.open(QFile::ReadOnly | QFile:: Text);
        file.open(QFile::WriteOnly | QFile:: Text);

        QTextStream conf_in(&conf_file);
        QTextStream new_out(&file);
        new_out << conf_in.readAll();
        file.flush();
        file.close();
        conf_file.close();


        if(!QDir("conf/language/").exists()){
            QDir().mkdir("conf/language/");
        }

        // Create default language file (cn.conf and en.conf)
        if(QFile("conf/language/en.conf").exists()){
            QFile("conf/language/en.conf").remove();
        }
        if(!QFile::copy(":/file/conf/language/en.conf", "conf/language/en.conf")){
            qDebug() << "Failed to create language file: conf/language/en.conf";
            return false;
        }

        if(QFile("conf/language/cn.conf").exists()){
            QFile("conf/language/cn.conf").remove();
        }
        if(!QFile::copy(":/file/conf/language/cn.conf", "conf/language/cn.conf")){
            qDebug() << "Failed to create language file: conf/language/cn.conf";
            return false;
        }

        if(!file.open(QFile::ReadOnly | QFile::Text)){
            qDebug() << "Failed to open new language configuration file: " + file.fileName();
            qDebug() << "Error information: " + file.errorString();
        }
    }
    QTextStream in(&file);
    QString text;
    current_language_index = in.readLine().toInt();
    while(!in.atEnd()){
        text = in.readLine();
        language_name.append(text.left(text.indexOf(" ")));
        language_file.append(text.right(text.size() - text.indexOf(" ") - 1));
    }
    file.close();
    // Retrieve language details and return
    return getLanguage_details();
}

/***********************************************************************
 *             Name: getLanguage_details
 *      Function ID: 003
 *      Create date: 21/11/2017
 * Modifiacion date: 29/11/2017
 *      Description: Retrieve language details from file
 ***********************************************************************/
bool Conf_Info::getLanguage_details()
{
    QFile file("conf/language/" + language_file.at(current_language_index));
    if(!file.open(QFile::ReadOnly | QFile::Text)){
        qDebug() << "Failed to open file: " + file.fileName() + " for writing.";
        qDebug() << "Error information: " + file.errorString();
    }

    QTextStream in(&file);

    project_name = in.readLine();
    project_crowdin = in.readLine();
    project_url = in.readLine();
    project_info = in.readLine();
    origin_text = in.readLine();
    formated_text = in.readLine();
    file_dialoag_title = in.readLine();
    crowdin_activity_url = in.readLine();
    option_dialog_title = in.readLine();
    file.close();

    //    printLanguage_information(); //Function 900
    return true;
}

/***********************************************************************
 *             Name: getCurrent_language_index
 *      Function ID: 800
 *      Create date: 20/11/2017
 * Modifiacion date: 20/11/2017
 *      Description: Get current language index
 ***********************************************************************/
int Conf_Info::getCurrent_language_index()
{
    return current_language_index;
}

/***********************************************************************
 *             Name: setCurrent_language_index
 *      Function ID: 801
 *      Create date: 20/11/2017
 * Modifiacion date: 20/11/2017
 *      Description: Set current language index
 ***********************************************************************/
void Conf_Info::setCurrent_language_index(int value)
{
    current_language_index = value;
}

/***********************************************************************
 *             Name: getLanguage_name
 *      Function ID: 802
 *      Create date: 21/11/2017
 * Modifiacion date: 21/11/2017
 *      Description: Get language name list
 ***********************************************************************/
QStringList Conf_Info::getLanguage_name()
{
    return language_name;
}

/***********************************************************************
 *             Name: setLanguage_name
 *      Function ID: 803
 *      Create date: 20/11/2017
 * Modifiacion date: 20/11/2017
 *      Description: Set language name list
 ***********************************************************************/
void Conf_Info::setLanguage_name(QStringList &value)
{
    language_name = value;
}

/***********************************************************************
 *             Name: getLanguage_file_pointer
 *      Function ID: 804
 *      Create date: 20/11/2017
 * Modifiacion date: 20/11/2017
 *      Description: Get the pointer of language file list
 ***********************************************************************/
QStringList* Conf_Info::getLanguage_file_pointer()
{
    return &language_file;
}

/***********************************************************************
 *             Name: setLanguage_file
 *      Function ID: 805
 *      Create date: 20/11/2017
 * Modifiacion date: 20/11/2017
 *      Description: Set language name file
 ***********************************************************************/
void Conf_Info::setLanguage_file(QStringList &value)
{
    language_file = value;
}

/***********************************************************************
 *             Name: getLanguage_name_pointer
 *      Function ID: 806
 *      Create date: 20/11/2017
 * Modifiacion date: 20/11/2017
 *      Description: Get the pointer of language name list
 ***********************************************************************/
QStringList* Conf_Info::getLanguage_name_pointer()
{
    return &language_name;
}

/***********************************************************************
 *             Name: getOrigin_text
 *      Function ID: 810
 *      Create date: 21/11/2017
 * Modifiacion date: 21/11/2017
 *      Description: Get text for label_source
 ***********************************************************************/
QString Conf_Info::getOrigin_text() const
{
    return origin_text;
}

/***********************************************************************
 *             Name: getFormated_text
 *      Function ID: 811
 *      Create date: 21/11/2017
 * Modifiacion date: 21/11/2017
 *      Description: Get text for label_destination
 ***********************************************************************/
QString Conf_Info::getFormated_text() const
{
    return formated_text;
}

/***********************************************************************
 *             Name: getProject_name
 *      Function ID: 812
 *      Create date: 27/11/2017
 * Modifiacion date: 27/11/2017
 *      Description: Get project name
 ***********************************************************************/
QString Conf_Info::getProject_name() const
{
    return project_name;
}

/***********************************************************************
 *             Name: setProject_name
 *      Function ID: 813
 *      Create date: 27/11/2017
 * Modifiacion date: 27/11/2017
 *      Description: Set project name
 ***********************************************************************/
void Conf_Info::setProject_name(const QString &value)
{
    project_name = value;
}

/***********************************************************************
 *             Name: getProject_crowdin
 *      Function ID: 814
 *      Create date: 27/11/2017
 * Modifiacion date: 27/11/2017
 *      Description: Get project crowdin link
 ***********************************************************************/
QString Conf_Info::getProject_crowdin() const
{
    return project_crowdin;
}

/***********************************************************************
 *             Name: setProject_crowdin
 *      Function ID: 815
 *      Create date: 27/11/2017
 * Modifiacion date: 27/11/2017
 *      Description: Set project crowdin link
 ***********************************************************************/
void Conf_Info::setProject_crowdin(const QString &value)
{
    project_crowdin = value;
}

/***********************************************************************
 *             Name: getProject_url
 *      Function ID: 816
 *      Create date: 27/11/2017
 * Modifiacion date: 27/11/2017
 *      Description: Get project url
 ***********************************************************************/
QString Conf_Info::getProject_url() const
{
    return project_url;
}

/***********************************************************************
 *             Name: setProject_url
 *      Function ID: 817
 *      Create date: 27/11/2017
 * Modifiacion date: 27/11/2017
 *      Description: Set project url
 ***********************************************************************/
void Conf_Info::setProject_url(const QString &value)
{
    project_url = value;
}

/***********************************************************************
 *             Name: getProject_info
 *      Function ID: 818
 *      Create date: 27/11/2017
 * Modifiacion date: 27/11/2017
 *      Description: Get project information
 ***********************************************************************/
QString Conf_Info::getProject_info() const
{
    return project_info;
}

/***********************************************************************
 *             Name: setProject_info
 *      Function ID: 819
 *      Create date: 27/11/2017
 * Modifiacion date: 27/11/2017
 *      Description: Set project information
 ***********************************************************************/
void Conf_Info::setProject_info(const QString &value)
{
    project_info = value;
}

/***********************************************************************
 *             Name: getFile_dialoag_title
 *      Function ID: 820
 *      Create date: 28/11/2017
 * Modifiacion date: 28/11/2017
 *      Description: Get file dialog title
 ***********************************************************************/
QString Conf_Info::getFile_dialoag_title() const
{
    return file_dialoag_title;
}

/***********************************************************************
 *             Name: setFile_dialoag_title
 *      Function ID: 821
 *      Create date: 28/11/2017
 * Modifiacion date: 28/11/2017
 *      Description: Set file dialog title
 ***********************************************************************/
void Conf_Info::setFile_dialoag_title(const QString &value)
{
    file_dialoag_title = value;
}

/***********************************************************************
 *             Name: getCrowdin_activity_url
 *      Function ID: 822
 *      Create date: 29/11/2017
 * Modifiacion date: 29/11/2017
 *      Description: Get Crowdin activity url
 ***********************************************************************/
QString Conf_Info::getCrowdin_activity_url() const
{
    return crowdin_activity_url;
}

/***********************************************************************
 *             Name: setCrowdin_activity_url
 *      Function ID: 823
 *      Create date: 29/11/2017
 * Modifiacion date: 29/11/2017
 *      Description: Set Crowdin activity url
 ***********************************************************************/
void Conf_Info::setCrowdin_activity_url(const QString &value)
{
    crowdin_activity_url = value;
}

/***********************************************************************
 *             Name: getOption_dialog_title
 *      Function ID: 824
 *      Create date: 29/11/2017
 * Modifiacion date: 29/11/2017
 *      Description: Get option dialog title text
 ***********************************************************************/
QString Conf_Info::getOption_dialog_title() const
{
    return option_dialog_title;
}

/***********************************************************************
 *             Name: setOption_dialog_title
 *      Function ID: 825
 *      Create date: 29/11/2017
 * Modifiacion date: 29/11/2017
 *      Description: Set option dialog title text
 ***********************************************************************/
void Conf_Info::setOption_dialog_title(const QString &value)
{
    option_dialog_title = value;
}

/***********************************************************************
 *             Name: printLanguage_information
 *      Function ID: 900
 *      Create date: 20/11/2017
 * Modifiacion date: 20/11/2017
 *      Description: Print all language related information
 ***********************************************************************/
void Conf_Info::printLanguage_information()
{
    qDebug() << "Current Language Index: " << current_language_index;
    qDebug() << "Information:";
    for(int i=0; i<language_file.size(); i++){
        qDebug() << language_name.at(i) << "  " << language_file.at(i);
    }
}
