#ifndef TEXTEDIT_H
#define TEXTEDIT_H

#include <QTextEdit>
#include <QMimeData>
#include <QFileInfo>
#include <QWidget>
#include <QUrl>
#include <QImageReader>
#include <QFileDialog>
#include <QTextBlock>
#include <QTextFragment>
#include <QPair>
#include <QDebug>
#include <QString>
#include <QTextLine>
#include "lineframe.h"

class TextEdit : public QTextEdit
{
    Q_OBJECT
public:
    TextEdit();
    void insertImage();

    bool canInsertFromMimeData(const QMimeData* source) const;
    void insertFromMimeData(const QMimeData* source);


    LineFrame* frame;
    QRect rect;

public slots:
        void resizeImage(QSize);
private:
    void dropImage(const QUrl& url, const QImage& image);
    void dropTextFile(const QUrl& url);
protected:
    virtual void mousePressEvent(QMouseEvent *e);
};
#endif // TEXTEDIT_H
