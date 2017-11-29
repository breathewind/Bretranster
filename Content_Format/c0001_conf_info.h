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
#ifndef C0001_CONF_INFO_H
#define C0001_CONF_INFO_H

#include <QStringList>

class Conf_Info
{
public:
    //Function 000: Construction function of configuration information class
    Conf_Info();
    //Function 001: Deconstruction function of configuration information class
    ~Conf_Info();
    //Function 002: Retrieve language information from file
    bool getLanguage_information(QString filename);
    //Function 003: Retrieve language details from file
    bool getLanguage_details();

    //Function 800: Get current language index
    int getCurrent_language_index();
    //Function 801: Set current language index
    void setCurrent_language_index(int value);

    //Function 802: Get language name list
    QStringList getLanguage_name();
    //Function 803: Set language name list
    void setLanguage_name(QStringList &value);

    //Function 804: Get the pointer of language file list
    QStringList* getLanguage_file_pointer();
    //Function 805: Set language name file
    void setLanguage_file(QStringList &value);

    //Function 806: Get the pointer of language name list
    QStringList* getLanguage_name_pointer();

    //Function 810: Get text for label_source
    QString getOrigin_text() const;

    //Function 811: Get text for label_destination
    QString getFormated_text() const;

    //Function 812: Get project name
    QString getProject_name() const;
    //Function 813: Set project name
    void setProject_name(const QString &value);

    //Function 814: Get project crowdin link
    QString getProject_crowdin() const;
    //Function 815: Set project crowdin link
    void setProject_crowdin(const QString &value);

    //Function 816: Get project url
    QString getProject_url() const;
    //Function 817: Get project url
    void setProject_url(const QString &value);

    //Function 818: Get project information
    QString getProject_info() const;
    //Function 819: Get project information
    void setProject_info(const QString &value);

    //Function 820: Get file dialog title
    QString getFile_dialoag_title() const;
    //Function 821: Set file dialog title
    void setFile_dialoag_title(const QString &value);

    //Function 822: Get Crowdin activity url
    QString getCrowdin_activity_url() const;
    //Function 823: Set Crowdin activity url
    void setCrowdin_activity_url(const QString &value);

    //Function 824: Get option dialog title text
    QString getOption_dialog_title() const;
    //Function 824: Set option dialog title text
    void setOption_dialog_title(const QString &value);

    //Function 900: Print all language related information
    void printLanguage_information();

private:
    int current_language_index;
    QStringList language_name;
    QStringList language_file;

    QString project_name;
    QString project_crowdin;
    QString project_url;
    QString project_info;
    QString origin_text;
    QString formated_text;
    QString file_dialoag_title;
    QString crowdin_activity_url;
    QString option_dialog_title;
};

#endif // C0001_CONF_INFO_H
