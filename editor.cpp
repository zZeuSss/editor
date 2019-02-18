#include "editor.h"
#include <QDebug>
Editor::Editor(QWidget *parent)
    : QWidget(parent)
{
// Создание главного окна программы
    sqlCntrlr = new SQLcontroller;// переменная для хранения обьекта позволяющего
                                  // взаимодействовать с базой данных
    sqlCntrlr->Connection();
    //fileHandler = new FileHandler(sqlCntrlr->getConnection());

    webTextEdit = new TextEdit; //  текстовое поле для работы текстом
    MaterialsTree = new TreeWidget; // дерево иерархии для базы данных

    MenuBar = new QMenuBar; // основное меню
    // выполняет подключение сигнала trigged() пунктов меню к
    // слотам обрабатывающим события
    CreateAction();
    // создаем меню
    MenuBar = CreateMenu();
    // добавляем подвижный разделитель между дерево и текстовым полем
    QSplitter *splitter = new QSplitter;
    splitter->setChildrenCollapsible(false);
    splitter->addWidget(MaterialsTree);
    splitter->addWidget(webTextEdit);

    QBoxLayout* mainLayout = new QVBoxLayout;

    mainLayout->setMargin(0);
    mainLayout->setMenuBar(MenuBar); // устанавливаем меню

    QBoxLayout* vLayout = new QVBoxLayout;
    vLayout->addWidget(splitter);

    mainLayout->addLayout(vLayout);
    setLayout(mainLayout);

    //QTextCodec *codec =  QTextCodec::codecForName("utf8");
    //QTextCodec::setCodecForCStrings(codec);

    Direction =  selectGroup(); // ф-ция взятия имени направления из бд

    //qDebug()<< Direction;

    // установка предмета направления как название дерева
    MaterialsTree->setHeaderLabel(Direction);
    // создание дерева
     MaterialsTree->createTree(sqlCntrlr,Direction);
    // перерисовка окна с размером
    resize(800,600);

}
// деструктор
Editor::~Editor()
{
}
QMenuBar* Editor::CreateMenu()
{
    QMenuBar* mnuBar = new QMenuBar;

    QMenu* mnuFile = new QMenu("Файл");
    //mnuFile->addAction(OpenFile);
    mnuFile->addAction(OpenDBfile);
    mnuFile->addSeparator();
    mnuFile->addAction(SavePc);
    mnuFile->addAction(SaveFileAs);
    mnuFile->addAction(SaveDBfile);

    QMenu* mnuAdd = new QMenu("Добавить");
    mnuAdd->addAction(AddSection);
    mnuAdd->addAction(AddTopic);
    mnuAdd->addAction(AddChapter);

    QMenu* mnuPaste = new QMenu("Вставка");

    QMenu* suBmnuVid = new QMenu("Видео файл",mnuPaste);
    QMenu* suBmnuAud = new QMenu("Аудио файл",mnuPaste);
    QMenu* suBmnuImg = new QMenu("Изображение",mnuPaste);

    mnuPaste->addMenu(suBmnuVid);
    mnuPaste->addMenu(suBmnuAud);
    mnuPaste->addMenu(suBmnuImg);

    suBmnuVid->addAction(vidFromPC);
    suBmnuVid->addAction(vidFromDB);

    suBmnuAud->addAction(audFromPC);
    suBmnuAud->addAction(audFromDB);

    suBmnuImg->addAction(imgFromPC);
    suBmnuImg->addAction(imgFromDB);


    mnuBar->addMenu(mnuFile);
    mnuBar->addMenu(mnuAdd);
    mnuBar->addMenu(mnuPaste);

   return mnuBar;
}
void Editor::CreateAction()
{
    OpenFile = new QAction("Открыть...",this);
    OpenFile->setShortcut(QKeySequence::Open);
    connect(OpenFile,SIGNAL(triggered()),this,SLOT(Open()));

    OpenDBfile = new QAction("Открыть из базы данных",this);
    connect(OpenDBfile,SIGNAL(triggered()),this,SLOT(OpenFileDB()));

    SavePc = new QAction("Сохранить",this);
    SavePc->setShortcut(QKeySequence::Save);
    connect(SavePc,SIGNAL(triggered()),this,SLOT(Save()));

    SavePc->setDisabled(true);

    SaveFileAs = new QAction("Сохранить как",this);
    SaveFileAs->setShortcut(QKeySequence::SaveAs);
    connect(SaveFileAs,SIGNAL(triggered()),this,SLOT(SaveAs()));

    SaveDBfile = new QAction("Сохранить в базу данных",this);
    connect(SaveDBfile,SIGNAL(triggered()),this,SLOT(SaveToDB()));

    AddSection = new QAction("Раздел",this);
    connect(AddSection,SIGNAL(triggered()),this,SLOT(fAddSection()));

    AddTopic = new QAction("Главу",this);
    connect(AddTopic,SIGNAL(triggered()),this,SLOT(fAddTopic()));

    AddChapter = new QAction("Параграф",this);
    connect(AddChapter,SIGNAL(triggered()),this,SLOT(AddChapt()));

    vidFromPC = new QAction("С компьютера",this);
    connect(vidFromPC,SIGNAL(triggered()),this,SLOT(fvidFromPC()));
    vidFromDB = new QAction("Из базы данных",this);
    connect(vidFromDB,SIGNAL(triggered()),this,SLOT(fvidFromDB()));

    audFromPC = new QAction("С компьютера",this);
    connect(audFromPC,SIGNAL(triggered()),this,SLOT(faudFromPC()));
    audFromDB = new QAction("Из базы данных",this);
    connect(audFromDB,SIGNAL(triggered()),this,SLOT(faudFromDB()));

    imgFromPC = new QAction("С компьютера",this);
    connect(imgFromPC,SIGNAL(triggered()),this,SLOT(fimgFromPC()));
    imgFromDB = new QAction("Из базы данных",this);
    connect(imgFromDB,SIGNAL(triggered()),this,SLOT(fimgFromDB()));
}

void Editor::Open()
{
   QString strFileName = QFileDialog::getOpenFileName(this,"Open File",
                                               "","*.html;;*.doc");

    QFile file;
    file.setFileName(strFileName);

    if (!file.exists()){
        QMessageBox::warning(this,QString::fromLocal8Bit("Ошибка файла"),
                             QString::fromLocal8Bit("Файла не существует либо поврежден"));
    } else {
        if (!file.open(QIODevice::ReadOnly)){
            QMessageBox::warning(this,QString::fromLocal8Bit("Ошибка чтения файла"),
                                 QString::fromLocal8Bit("Файл защищен для чтения либо поврежден"));
     } else {
            QTextStream in(&file);
            in.setCodec("UTF-8");
            QString ContentFile = in.readAll();
            webTextEdit->setHtml(ContentFile);

         file.close();
        }

    }
}
void Editor::OpenFileDB()
{
    webTextEdit->setText("OpenDBfile() slot has done");
}
void Editor::Save()
{
    QFile file(SavedFile);
    if (!file.open(QIODevice::WriteOnly)){
        QMessageBox::warning(this,QString::fromLocal8Bit("Ошибка сохранения"),
                             QString::fromLocal8Bit("Файл не существует либо заблокирован"));
    } else {
        QTextStream in(&file);
        in << webTextEdit->toPlainText();
        in.flush();
        file.close();
        QMessageBox::information(this,QString::fromLocal8Bit("Сохранение "),
                             QString::fromLocal8Bit("Файл успешно сохранен"));

    }
}
void Editor::SaveAs()
{
     SavedFile = QFileDialog::getSaveFileName(this,
                                              QString::fromLocal8Bit("Сохранить как"),
                                              QString::fromLocal8Bit(""),
                                              QString::fromLocal8Bit("*.html"));


     if (SavedFile !=""){
        QFile file(SavedFile);
        if (!file.open(QIODevice::WriteOnly)){
            QMessageBox::warning(this,QString::fromLocal8Bit("Ошибка файла"),
                                 QString::fromLocal8Bit("Файл закрыт для записи"));
        } else {
            QTextStream in(&file);
            in << webTextEdit->toHtml();
            in.flush();
            file.close();
            SavePc->setEnabled(true);
            QMessageBox::information(this,QString::fromLocal8Bit("Сохранение "),
                                 QString::fromLocal8Bit("Файл успешно сохранен"));
        }
    }
}
void Editor::SaveToDB()
{
    webTextEdit->setText("SaveToDB() slot has done");
}
void Editor::fAddSection()
{
    QString SubjectName;
    InputDialog* inputdlg = new InputDialog();
    inputdlg->wait();
    SubjectName = inputdlg->data();
    //qDebug()<< SubjectName;
    sqlCntrlr->queryAddSubject(SubjectName,Direction);

}
void Editor::AddChapt()
{
  QComboBox* sub_box = new QComboBox;
  QStringList sub_list = sqlCntrlr->queryGetSubject(Direction);
  QStringList chpt_list = sqlCntrlr->queryGetChapter(sub_list[0]);
  sub_box->addItems(sub_list);

  InputDialog* inputdlg = new InputDialog(sub_box,chpt_list);
  inputdlg->wait();

  sqlCntrlr->queryAddParagraph(inputdlg->getBoxContent(),inputdlg->getEditContent());



}
void Editor::fAddTopic()
{
     QStringList values = sqlCntrlr->queryGetSubject(Direction);
     InputDialog* inputdlg = new InputDialog(values);
     inputdlg->wait();

     sqlCntrlr->queryAddChapter(inputdlg->getBoxContent(),inputdlg->getEditContent());

}
void Editor::fvidFromPC()
{
    //загрузка ссылок на видео с пк
    QString file = QFileDialog::getOpenFileName(this,"Выберите видео файл",".",
                                                "Audio Video Interleave (*.avi)\n"
                                                   "Movie (*.mov)\n"
                                                   "MP4 (*.mp4)\n"
                                                    "Web Movie (*.webm)\n");
    if(file != "")
    {
        // загрузка ссылок в бд, где countVid - количество
        //видео, file - ссылка на файл
        // формирование отображение видео для просмоторщика
        sqlCntrlr->queryAddFileToDB(file);
        QString videoName = "<video width='600' height='400' controls src='"+file+"'></video>";
        // запись форматированой ссылки в html документ
        webTextEdit->append(videoName);
    }


}
void Editor::fvidFromDB()
{
   // переменная для хранения массива ссылок на файлы
    QStringList values;
   // переносим данные в переменную из запроса
    values.append(sqlCntrlr->queryVidfromDB());
   // todo() дописать отображение видео файлов при помощи QFileDialog


}
void Editor::faudFromPC()
{


}
void Editor::faudFromDB()
{
    webTextEdit->setText("faudFromDB() slot has done");
}
void Editor::fimgFromPC()
{
    webTextEdit->insertImage();
}
void Editor::fimgFromDB()
{
    webTextEdit->setText("fimgFromDB() slot has done");

}
QString Editor::selectGroup()
{
     QStringList values;
     values.append(sqlCntrlr->querySelectGroup());
     bool ok;
     QString direction = QInputDialog::getItem(this,"Выберете направление",
                                               "Направление: ",
                                               values,1,false,&ok);
     if(ok)
     return direction;
}
