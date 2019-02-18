#ifndef TEXTHANDLER_H
#define TEXTHANDLER_H

#include <QObject>
#include <QRegExp>
#include <QStringList>
#include <QDebug>
#include <QTextCodec>

const QString text = "<p align='center'><object type='player/video_player'data='sintel-trailer.mp4' width='164' height='164'></object></p>";


struct linksMultimediaFiles
{
public:
    QStringList videoLinks;
    QStringList audioLinks;
};

class TextHandler : public QObject
{
    Q_OBJECT
private:
    linksMultimediaFiles* links;
    QRegExp reVideo;
    QRegExp reAudio;
public:

    explicit TextHandler(QObject *parent = 0);
    TextHandler(QString Video, QString Audio);
    void setRegExp(QString Video, QString Audio);
    linksMultimediaFiles getLinksFromText();
    QStringList getVideoLinks(QString content/*textEditor.text()*/);
    QStringList getAudioLinks(QString content);
signals:
    
public slots:
    
};

#endif // TEXTHANDLER_H
