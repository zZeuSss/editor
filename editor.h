#ifndef EDITOR_H
#define EDITOR_H
// подключение необходимых библиотек
#include <QWidget>
#include <QBoxLayout>
#include <QSplitter>
#include <QMenuBar>
#include <QTreeWidget>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QInputDialog>
#include <QImage>
#include <QImageReader>
#include <QTextDocument>
#include <QStringList>
#include <QVariant>
#include <QUrl>
#include <QTextCodec>
#include <QEventLoop>
#include <QMetaObject>
#include "textedit.h"
#include "sqlcontroller.h"
#include "inputdialog.h"
#include "treewidget.h"
#include "filehandler.h"
QT_BEGIN_NAMESPACE
class QPushButton;
class QAction;
class QMenu;
class QComboBox;
QT_END_NAMESPACE

// класс Editor наследуем от класса QWidget, базового класса
class Editor : public QWidget
{
    Q_OBJECT // определение макроса сигналов и слотов
private: // приватные поля класса
    SQLcontroller*  sqlCntrlr;
    QMenuBar*       MenuBar;
    TextEdit*       webTextEdit;// поле редактирования
    QAction*        AddTopic; // пункт меню Добавить(подменю Добавить тему)
    QAction*        AddChapter; // пункт меню Добавить (подменю добавить главу)
    QAction*        AddSection;
    QAction*        SaveFileAs; // пункт меню файла (подменю сохранить как)
    QAction*        SavePc;     // пункт меню файла (подменю сохранить)
    QAction*        OpenFile; //   пункт меню файла (открыть файл с компьютера)
    QAction*        SaveDBfile; // пункт меню файла (сохранить файл в БД)
    QAction*        OpenDBfile; // пункт меню файла (открыть файл с БД)
    QAction*        vidFromPC;  // пункт меню загрузки видео файлов из пк
    QAction*        vidFromDB;  // пункт меню загрузки видео файлов из бд
    QAction*        audFromPC;  // пункт меню загрузки аудио файлов из пк
    QAction*        audFromDB;  // пункт меню загрузки аудио файлов из бд
    QAction*        imgFromPC;  // пункт меню загрузки изображений  из пк
    QAction*        imgFromDB;  // пункт меню загрузки изображений  из бд
    TreeWidget*    MaterialsTree; // класс для отображения каталогов бд
    QString         SavedFile;     // переменная хранящая путь к сохраненому файлу
    QString         Direction; // перемення хранящая возвращенные данные функции selectGroup();
    QString         subjectFromDb;
    QStringList     filePath;
    FileHandler*     fileHandler;
protected: // защищенные методы
    QMenuBar        *CreateMenu();// создание меню
    void            CreateAction(); // Создание событий для пунктов меню


    
public:
                    Editor(QWidget *parent = 0);// конструктор класса
                    ~Editor();// деструктор
    QString         selectGroup();
    void            wait();

public slots:
    void    Open();
    void    OpenFileDB();
    void    Save();
    void    SaveAs();
    void    SaveToDB();
    void    fAddSection();
    void    AddChapt();
    void    fAddTopic();
    void    fvidFromPC();
    void    fvidFromDB();
    void    faudFromPC();
    void    faudFromDB();
    void    fimgFromPC();
    void    fimgFromDB(); 
};

#endif // EDITOR_H
