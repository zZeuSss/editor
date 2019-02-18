#ifndef SQLCONTROLLER_H
#define SQLCONTROLLER_H
//#include <QSql>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>
#include <inputdialog.h>

class SQLcontroller
{
private:
    bool connection;
public:
    QSqlDatabase    db;
                    SQLcontroller();
                    SQLcontroller(int);
                    ~SQLcontroller();
    void            Connection();
    void            ErrorMessage(QString);
    QStringList     querySelectGroup();
    void            queryAddFileToDB(QString);
    QStringList     queryVidfromDB();
    QStringList     queryTopLevelTreeFromDB(QString);
    QStringList     queryChapterLevelTreeFromDB(QString);
    QStringList     queryParagraphLevelTreeFromDB(QString);
    QStringList     queryLoadContent(QString chpt_name, QString prg_name);
    void            queryAddChapter(QString sub_name,QString chpt_name);
    void            queryAddSubject(QString sub_name, QString direction);
    void            queryAddParagraph(QString chpt_name, QString prg_name);
    int             queryLastSubNum();
    int             queryLastChptNum();
    int             queryLastPrgNum();
    QStringList     queryGetSubject(QString  direction);
    QStringList     queryGetChapter(QString subject);
    void            queryDeleteFromSubject(QString subject, QString direction);
    void            queryDeleteFromChapter(QString chapter, QString subject);
    void            queryDeleteFromParagraph(QString paragraph);
    QStringList     queryGetFileName(QString server_path);
    QSqlDatabase    &getConnection();
};

#endif // SQLCONTROLLER_H
