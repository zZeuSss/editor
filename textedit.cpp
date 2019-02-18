#include "textedit.h"

TextEdit::TextEdit()
{
    frame = new LineFrame(this->viewport());

    connect(frame,SIGNAL(resizeSignal(QSize)),this,SLOT(resizeImage(QSize)));
}
bool TextEdit::canInsertFromMimeData(const QMimeData* source) const
{
    return source->hasImage() || source->hasUrls() ||
        QTextEdit::canInsertFromMimeData(source);
}
void TextEdit::insertFromMimeData(const QMimeData* source)
{
    if (source->hasImage())
    {
        static int i = 1;
        QUrl url(QString("dropped_image_%1").arg(i++));
        dropImage(url, qvariant_cast<QImage>(source->imageData()));
    }
    else if (source->hasUrls())
    {
        foreach (QUrl url, source->urls())
        {
            QFileInfo info(url.toLocalFile());
            if (QImageReader::supportedImageFormats().contains(info.suffix().toLower().toLatin1()))
                dropImage(url, QImage(info.filePath()));
            else
                dropTextFile(url);
        }
    }
    else
    {
        QTextEdit::insertFromMimeData(source);
    }
}
void TextEdit::dropImage(const QUrl& url, const QImage& image)
{
    qDebug()<< url;
    if (!image.isNull())
    {
        document()->addResource(QTextDocument::ImageResource, url, image);
        textCursor().insertImage(url.toString());
    }
}
void TextEdit::dropTextFile(const QUrl& url)
{
    QFile file(url.toLocalFile());
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        textCursor().insertText(file.readAll());
}
void TextEdit::insertImage()
{
    QString file = QFileDialog::getOpenFileName(this, "Выберите изображение",
                                  ".", tr("Bitmap Files (*.bmp)\n"
                                    "JPEG (*.jpg *jpeg)\n"
                                    "GIF (*.gif)\n"
                                    "PNG (*.png)\n"));
       QUrl Uri ( QString ( "file://%1" ).arg ( file ) );

       QImage image = QImageReader ( file ).read();

        //frame->setImage(image);

       QTextDocument * textDocument = this->document();
       textDocument->addResource( QTextDocument::ImageResource, Uri, QVariant ( image ) );
       QTextCursor cursor = this->textCursor();
       QTextImageFormat imageFormat;
       imageFormat.setWidth( image.width() );
       imageFormat.setHeight( image.height() );
       imageFormat.setName( Uri.toString() );
       cursor.insertImage(imageFormat);

       rect = this->cursorRect(this->textCursor());
      // frame->sizeFrame(rect.x()- image.width(),
      //                  rect.y(),image.width(),image.height());

    //"&lt;p&gt;&lt;img src='"+file+"' align='top'&gt;&lt;//p&gt;"
 }
void TextEdit::resizeImage(QSize size)
{
    QTextBlock currentBlock = this->textCursor().block();
    QTextBlock::iterator it;

    for (it = currentBlock.begin(); !(it.atEnd()); ++it)
    {
        QTextFragment fragment = it.fragment();
        if (fragment.isValid())
        {
            if(fragment.charFormat().isImageFormat ())
            {


                QTextImageFormat newImageFormat = fragment.charFormat().toImageFormat();
                //
                //tempSize = size;
                newImageFormat.setWidth(size.width());
                newImageFormat.setHeight(size.height());

                if (newImageFormat.isValid())
                {
                    QTextCursor helper = this->textCursor();
                    helper.setPosition(fragment.position());
                    helper.setPosition(fragment.position() + fragment.length(),
                                        QTextCursor::KeepAnchor);
                    helper.setCharFormat(newImageFormat);

                }
            }
        }
    }
}
void TextEdit::mousePressEvent(QMouseEvent *event)
{
//    if(event->posF().x() >= frame->pos().x() &&
//       event->posF().y() >= frame->pos().y() &&
//       event->posF().x() <= frame->width() &&
//       event->posF().y() <= frame->height())
//        if(event->screenPos().x() >= frame->pos().x() &&
//           event->screenPos().y() >= frame->pos().y() &&
//           event->screenPos().x() <= frame->width() &&
//           event->screenPos().y() <= frame->height())
//    {
//        this->setReadOnly(true);
//    }
//   else
//   {
//       this->setReadOnly(false);
//   }
//    if(event->button() == Qt::LeftButton){

//        QTextBlock currentBlock = this->textCursor().block();
//        QTextBlock::iterator it;

//        for (it = currentBlock.begin(); !(it.atEnd()); ++it)
//        {
//            QTextFragment fragment = it.fragment();
//            if (fragment.isValid())
//            {
//                if(fragment.charFormat().isImageFormat ())
//                {
//                    frame->sizeFrame(rect.x(),rect.y(),340,rect.height());
//                }else{
//                    frame->sizeFrame(0,0,0,0);
//               }
//            }
//        }
//    }
//    return QTextEdit::mousePressEvent(event);

}
