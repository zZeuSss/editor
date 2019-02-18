#include "sqlcontroller.h"

SQLcontroller::SQLcontroller()
{
     db =  QSqlDatabase::addDatabase("QMYSQL");
}
SQLcontroller::SQLcontroller(int)
{

}
SQLcontroller::~SQLcontroller()
{
}
void SQLcontroller::Connection()
{
    QSqlQuery query (db);

    //db.setHostName("172.21.241.35");
     db.setHostName("127.0.0.1");
    db.setPort(3306);
    db.setUserName("root");
    //db.setPassword("123");
    db.setPassword("");
    //db.setDatabaseName("test");
    db.setDatabaseName("diplom");


    connection = db.open();

    qDebug() << connection;
}
QStringList SQLcontroller::querySelectGroup()
{
    QSqlQuery query (db);
    QStringList values;
    if(!query.exec("SELECT `dir_id`,`dir_name` FROM  `direction`"))
    {
       // ErrorMessage(db.lastError().text());
    }
    QSqlRecord rec = query.record();

     int dir_name = rec.indexOf("dir_name");

    while (query.next() )
    {
        values.append(query.value(dir_name).toString());
    }
    return values;
}
void SQLcontroller::ErrorMessage(QString error)
{
    QMessageBox::critical(0,QString::fromLocal8Bit("SQL Error"),error);
}
void SQLcontroller::queryAddFileToDB(QString file_name)
{
    QSqlQuery query(db);

    query.prepare("INSERT INTO `file` (source_file) "
                  "VALUES (:source_file)");
    query.bindValue(":source_file", file_name);

    query.exec();

}
QStringList SQLcontroller::queryVidfromDB()
{
    // хранит ссылку на видео файл
    QStringList valuesList;
    // отправляет запрос к бд
    QSqlQuery query(db);
    // если не возможно отправить запрос то...
    if(!query.exec("SELECT `file_id`,`source_file` FROM `file`"))
    {
        //... вывод сообщения об ошибке
        ErrorMessage(db.lastError().text());
    }
    // класс для получения данных
    QSqlRecord rec = query.record();
    // будет считываться поле source_file
    int source_name = rec.indexOf("source_file");
    // пока есть следующий элемент...
    while (query.next() )
    {
        //... записываем все результаты в массив строк
        valuesList.append(query.value(source_name).toString());
    }
    // возвращаем массив
    return valuesList;
}
QStringList SQLcontroller::queryTopLevelTreeFromDB(QString direction)
{
    // хранит массив строк наименования предметов
    QStringList values;
    // класс для взаимодействия с бд
    QSqlQuery query(db);
    // если не возможно отправить запрос то...
    if (!query.exec("SELECT sub_name FROM subject WHERE dir_name = '"+direction+"'"))
    {
        //... выводим сообщение об ошибке
        ErrorMessage(db.lastError().text());
    }
    //
    QSqlRecord rec = query.record();
    //
    int sub_name = rec.indexOf("sub_name");
    //
    while(query.next() )
    {
        values.append(query.value(sub_name).toString());
    }
    return values;
}
QStringList SQLcontroller::queryChapterLevelTreeFromDB(QString subjectName)
{
    // хранит массив строк наименования предметов
    QStringList values;
    //qDebug()<< subjectName;
    // класс для взаимодействия с бд
    QSqlQuery query(db);
    // если не возможно отправить запрос то...
    if (!query.exec("SELECT chpt_name FROM chapter "
                    "WHERE sub_name = '"+subjectName+"'"))
    {
        //... выводим сообщение об ошибке
        ErrorMessage(db.lastError().text());
    }
    // хранит получаемый результат
    QSqlRecord rec = query.record();
    // хранит названия глав
    int cpt_name = rec.indexOf("chpt_name");
    //
    while(query.next() )
    {
        values.append(query.value(cpt_name).toString());
    }
   // qDebug()<< values;
    return values;
}

QStringList SQLcontroller::queryParagraphLevelTreeFromDB(QString chapter_name)
{
    // хранит массив строк наименования предметов
    QStringList values;
    // класс для взаимодействия с бд
    QSqlQuery query(db);
    // если не возможно отправить запрос то...
    if (!query.exec("SELECT prg_name FROM paragraph "
                    "WHERE chpt_name = '"+chapter_name+"'"))
    {
        //... выводим сообщение об ошибке
        ErrorMessage(db.lastError().text());
    }
    // хранит получаемый результат
    QSqlRecord rec = query.record();
    // хранит названия глав
    int prg_name = rec.indexOf("prg_name");
    //
    while(query.next() )
    {
        values.append(query.value(prg_name).toString());
    }
   // qDebug()<< values;
    return values;
}
QStringList SQLcontroller::queryLoadContent(QString chpt_name,QString  prg_name)
{
    // хранит массив строк наименования предметов
    QStringList values;
    // класс для взаимодействия с бд
    QSqlQuery query(db);
    // если не возможно отправить запрос то...
    if (!query.exec("SELECT `cont_path` FROM `content` "
                    "WHERE `chpt_name` = '"+chpt_name+"' AND "
                    "`prg_name` = '"+prg_name+"'"))
    {
        //... выводим сообщение об ошибке
        ErrorMessage(db.lastError().text());
    }
    // хранит получаемый результат
    QSqlRecord rec = query.record();
    // хранит названия глав
    int cont_name = rec.indexOf("cont_path");
    //
    while(query.next() )
    {
        values.append(query.value(cont_name).toString());
    }
    return values;
}
// функция выполняет создание предмета в базе данных
// принимает два параметра
// sub_name - название предмета
// chpt_name - имя параграфа
void SQLcontroller::queryAddChapter(QString sub_name,QString chpt_name)
{
    // получаем кол-во глав в таблице
    int column_count = this->queryLastChptNum();
    // создаем переменую для хранения запроса с указанием соединения db
    QSqlQuery   query(db);
    // создания запроса
    query.prepare("INSERT INTO chapter (chpt_id,chpt_name,sub_name)"
                  "VALUES (:chpt_id,:chpt_name,:sub_name);");
    // записываем кол-во предметов + 1
    query.addBindValue(column_count + 1);
    // записываем имя предмета
    query.addBindValue(chpt_name);
    // записываем имя главы
    query.addBindValue(sub_name);
    // если не удалось отправить запрос
    if(!query.exec())
    {
        // вывести сообщение об ошибке
        ErrorMessage( query.lastError().text());
    }
}
// функция выполняет создание предмета в базе данных
// принимает два параметра
// sub_name - название предмета
// direction -направление
void SQLcontroller::queryAddSubject(QString sub_name, QString direction)
{
    // получаем кол-во предметов в таблице
    int column_count = this->queryLastSubNum();
    // создаем переменую для хранения запроса с указанием соединения db
    QSqlQuery   query(db);
    // создания запроса
    query.prepare("INSERT INTO subject (sub_id,sub_name, dir_name) "
                    "VALUES (:sub_id,:sub_name,:dir_name);");
    // записываем кол-во предметов + 1
    query.addBindValue(column_count + 1);
    // записываем имя предмета
    query.addBindValue(sub_name);
    // записываем имя направления
    query.addBindValue(direction);
    // если не удалось отправить запрос
    if(!query.exec())
    {
        // вывести сообщение об ошибке
        ErrorMessage( query.lastError().text());
    }

}
void SQLcontroller::queryAddParagraph(QString chpt_name, QString prg_name)
{
    int column_count = this->queryLastPrgNum();
    QSqlQuery   query(db);
    query.prepare("INSERT INTO paragraph (prg_id, prg_name, chpt_name) "
                    "VALUES (:prg_id,:prg_name,:chpt_name);");
    query.addBindValue(column_count + 1);
    query.addBindValue(prg_name);
    query.addBindValue(chpt_name);
    if(!query.exec())
    {
        ErrorMessage( query.lastError().text());
    }

}
int SQLcontroller::queryLastSubNum()
{
    // хранит массив строк наименования предметов
    QString value;
    // класс для взаимодействия с бд
    QSqlQuery query(db);
    // если не возможно отправить запрос то...
    if (!query.exec("SELECT sub_id FROM subject"))
    {
        //... выводим сообщение об ошибке
        ErrorMessage(query.lastError().text());
    }
    //
    QSqlRecord rec = query.record();
    //
    int columns_count = 1;
    int sub_id = rec.indexOf("sub_id");
    //
    while(query.next())
    {
    columns_count++;
    value = query.value(sub_id).toString();
    }
    qDebug()<< columns_count;
    return columns_count;
}
int SQLcontroller::queryLastChptNum()
{
    // хранит массив строк наименования предметов
    QString value;
    // класс для взаимодействия с бд
    QSqlQuery query(db);
    // если не возможно отправить запрос то...
    if (!query.exec("SELECT chpt_id FROM chapter"))
    {
        //... выводим сообщение об ошибке
        ErrorMessage(query.lastError().text());
    }
    //
    QSqlRecord rec = query.record();
    int column_count = 1;
    int chpt_id = rec.indexOf("chpt_id");
    //
    while(query.next())
    {
    value = query.value(chpt_id).toString();
    column_count++;
    }
    qDebug()<< column_count;
    return column_count;
}
int SQLcontroller::queryLastPrgNum()
{
    // хранит массив строк наименования предметов
    QString value;
    // класс для взаимодействия с бд
    QSqlQuery query(db);
    // если не возможно отправить запрос то...
    if (!query.exec("SELECT prg_id FROM paragraph"))
    {
        //... выводим сообщение об ошибке
        ErrorMessage(query.lastError().text());
    }
    //
    QSqlRecord rec = query.record();
    int column_count = 1;
    int prg_id = rec.indexOf("prg_id");
    //
    while(query.next())
    {
    value = query.value(prg_id).toString();
    ++column_count;
    }
    qDebug()<< column_count;
    return column_count;
}
QStringList SQLcontroller::queryGetSubject(QString direction)
{
    qDebug()<< direction;
    QStringList values;
    // класс для взаимодействия с бд
    QSqlQuery query(db);
    // если не возможно отправить запрос то...
    if (!query.exec("SELECT sub_name FROM subject "
                    "WHERE dir_name = '"+direction+"'"))
    {
        //... выводим сообщение об ошибке
        ErrorMessage(query.lastError().text());
    }
    // хранит получаемый результат
    QSqlRecord rec = query.record();
    // хранит названия глав
    int sub_name = rec.indexOf("sub_name");
    //
    while(query.next() )
    {
        values.append(query.value(sub_name).toString());
    }
    qDebug()<<values;
    return values;
}
QStringList SQLcontroller::queryGetChapter(QString subject)
{

    QStringList values;
    // класс для взаимодействия с бд
    QSqlQuery query(db);
    // если не возможно отправить запрос то...
    if (!query.exec("SELECT chpt_name FROM chapter "
                    "WHERE sub_name = '"+subject+"'"))
    {
        //... выводим сообщение об ошибке
        ErrorMessage(query.lastError().text());
    }
    // хранит получаемый результат
    QSqlRecord rec = query.record();
    // хранит названия глав
    int chpt_name = rec.indexOf("chpt_name");
    //
    while(query.next() )
    {
        values.append(query.value(chpt_name).toString());
    }
    qDebug()<<values;
    return values;
}
// функция для удаления глав из предметов
// принимает два аргумента
// chapter - имя удаляемой главы
// subject - предмет из которого удаляется
void SQLcontroller::queryDeleteFromChapter(QString chapter, QString subject)
{
    QSqlQuery query(db);
    if (!query.exec(""))
    {
        ErrorMessage(query.lastError().text());
    }
}
// функция для удаления глав из предметов
// принимает два аргумента
// chapter - имя удаляемого предмета
// direction - направление из которого удаляется
void SQLcontroller::queryDeleteFromSubject(QString subject, QString direction)
{
    QSqlQuery query(db);
    if (!query.exec("DELETE"))
    {
        ErrorMessage(query.lastError().text());
    }
}
// функция для удаления глав из предметов
// принимает два аргумента
// paragraph - имя удаляемого параграфа
void SQLcontroller::queryDeleteFromParagraph(QString paragraph)
{
    QSqlQuery query(db);
    if (!query.exec(""))
    {
        ErrorMessage(query.lastError().text());
    }
}
QStringList SQLcontroller::queryGetFileName(QString server_path)
{
    QStringList values;
    QSqlQuery query(db);
    if(!query.exec("SELECT "+server_path+" FROM path"))
    {
        ErrorMessage(query.lastError().text());
    }
    QSqlRecord rec = query.record();
    // хранит названия глав
    int path = rec.indexOf(server_path);
    //
    while(query.next())
    {
        values.append(query.value(path).toString());
    }
    qDebug()<<values;
    return values;
}
QSqlDatabase& SQLcontroller::getConnection()
{
    return db;
}
