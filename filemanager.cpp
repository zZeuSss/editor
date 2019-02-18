#include "filemanager.h"




FileManager::FileManager(QFile *parent)
    : QFile(parent)
{
    txtHndlr = new TextHandler();
}

FileManager::~FileManager()
{
    
}
void FileManager::setFullFilePath(QString serverPath,QString filePath)
{
    this->fullFilePath = serverPath + filePath;
}

void FileManager::setFilePath(QString filePath)
{
    this->filePath = filePath;
}

void FileManager::setServerPath(QString serverPath)
{
    this->serverPath = serverPath;
}

void FileManager::saveOnServer()
{
    // get text from textedit
    // textEdit.text();
    //this->setFileName();
    QStringList VideoList = txtHndlr->getVideoLinks(text);
    QStringList AudioList = txtHndlr->getAudioLinks(text);

    foreach(const QString& VideoName, VideoList)
    {
        this->copy(VideoName,this->serverPath + VideoName);
    }
    foreach(const QString& AudioName, AudioList)
    {
        this->copy(AudioName, this->serverPath + AudioName);
    }
    //QFile tmp(this->serverPath + /**/);
}

void FileManager::deleteFromServer()
{

}

void FileManager::updateFromServer()
{

}

void FileManager::Dialog()
{
    QFileDialog* dlg = new QFileDialog();

    //dlg->setDirectory(QString::fromLocal8Bit("//S413c15/оям-15/"));
   // dlg->setOption();
    dlg->getOpenFileName(0,"Dialog",QString::fromLocal8Bit("//S413c15/оям-15/"),
                         "*.*",0,QFileDialog::ReadOnly);
}

QString FileManager::getFileName()
{
    return this->fileName;
}
