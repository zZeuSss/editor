#include "texthandler.h"

TextHandler::TextHandler(QObject *parent) :
    QObject(parent)
{
    const QString Video = "[^>]+<object type=\"player/video_player\" data=\"([^>]+)\" width=\"[^>]+\" height=\"[^>]+\"></object>[^>]+";

    const QString Audio = "[^>]+<object type=\"player/audio_player\" data=\"([^>]+)\" width=\"[^>]+\" height=\"[^>]+\"></object>[^>]+";
    links = new linksMultimediaFiles;
    this->reVideo.setPattern(Video);
    this->reAudio.setPattern(Audio);
}

linksMultimediaFiles TextHandler::getLinksFromText(/*textEditor.text()*/)
{
    QString content;     // textEditor.text();

    if (reAudio.exactMatch(content))
    {
        links->audioLinks.append(reAudio.cap(1));
    }
    if (reAudio.exactMatch(content))
    {
        links->videoLinks.append(reAudio.cap(1));
    }
    return *links;
}
QStringList TextHandler::getVideoLinks(QString content/*textEditor.text()*/)
{
     //textEditor.text()
    QStringList contentList = content.split("\n");


        //qDebug() << contentList.at(it);
    foreach(const QString& temp, contentList)
    {
        if (reVideo.exactMatch(temp))
        {
            qDebug() << reVideo.cap(1);
            //return append.reVideo.cap(1);
        }
    }

}

QStringList TextHandler::getAudioLinks( QString content/*textEditor.text()*/)
{
  //textEditor.text()
    QStringList contentList = content.split("\n");

    foreach(const QString& temp, contentList)
    {
        if (reAudio.exactMatch(temp))
        {
            qDebug() << reAudio.cap(1);
            //return reAudio.cap(1);
        }
    }
}

TextHandler::TextHandler(QString Video, QString Audio)
{
    links = new linksMultimediaFiles;
    this->reVideo.setPattern(Video);
    this->reAudio.setPattern(Audio);
}
void TextHandler::setRegExp(QString Video, QString Audio)
{
    this->reVideo.setPattern(Video);
    this->reAudio.setPattern(Audio);
}
