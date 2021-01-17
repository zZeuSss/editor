#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QWidget>
#include <QFile>
#include <QFileDialog>
#include "texthandler.h"


class FileManager : public QFile
{
    Q_OBJECT
private:
    TextHandler*txtHndlr;
    QString     filePath;
    QString     fileName;
    QString     serverPath;
    QString     fullFilePath;
    QFileDialog*dialog;
public:
                FileManager(QFile *parent = 0);
                ~FileManager();

    void        setFullFilePath(QString serverPath, QString filePath);
    void        setFilePath(QString filePath);
    void        setServerPath(QString serverPath);
    QString     getFileName();

    void        saveOnServer();
    void        deleteFromServer();
    void        updateFromServer();

    void        Dialog();
public slots:


};

#endif // FILEMANAGER_H
