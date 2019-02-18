#include "treewidget.h"

TreeWidget::TreeWidget()
{
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this,SIGNAL(itemClicked(QTreeWidgetItem*,int)),this,
            SLOT(treeItemChange(QTreeWidgetItem*,int)));

    connect(this,SIGNAL(customContextMenuRequested(QPoint)),
            this,SLOT(treeContextMenu(QPoint)));
}
TreeWidget::~TreeWidget()
{

}
void TreeWidget::createTree(SQLcontroller* sqlCntrlr, QString Direction)
{
    sqlHandler = sqlCntrlr;
    direction = Direction;
    QList<QTreeWidgetItem*> subjectTreeList;
    QStringList subValues;
    subValues.append(sqlCntrlr->queryTopLevelTreeFromDB(Direction));

    for(int it = 0; it != subValues.size(); ++it)
    {
        QString subValue = subValues.at(it);
        subjectTreeList.append(new QTreeWidgetItem((QTreeWidget*)0,
                                                  QStringList(subValue)));
    }
       // qDebug()<< subValues;
    this->insertTopLevelItems(0, subjectTreeList);
    //строка принимает предметы из базы данных
}
void TreeWidget::createTree()
{
    QList<QTreeWidgetItem*> subjectTreeList;
    QStringList subValues;
    subValues.append(sqlHandler->queryTopLevelTreeFromDB(direction));

    for(int it = 0; it != subValues.size(); ++it)
    {
        QString subValue = subValues.at(it);
        subjectTreeList.append(new QTreeWidgetItem((QTreeWidget*)0,
                                                  QStringList(subValue)));
    }
       // qDebug()<< subValues;
    this->insertTopLevelItems(0, subjectTreeList);
    //строка принимает предметы из базы данных
}
void TreeWidget::treeItemChange(QTreeWidgetItem *item, int column)
{
    QList<QTreeWidgetItem* > chapterItemList;
    QList<QTreeWidgetItem* > paragraphItemList;
    QStringList chpt_name;
    if( item->childCount() <= 0)
    {
        chpt_name.append(sqlHandler->queryChapterLevelTreeFromDB(item->data(0,0).toString()));
        for ( int it = 0; it != chpt_name.size(); ++it)
        {
            QString temp = chpt_name.at(it);

            chapterItemList.append(new QTreeWidgetItem((QTreeWidget*)0,
                                                       QStringList(temp)));
            item->addChild(chapterItemList.at(it));
        }

   }

    QStringList prg_name;
    if (item->parent() != nullptr && item->childCount() <= 0)
    {
       QString temp;
       prg_name.append(sqlHandler->queryParagraphLevelTreeFromDB(item->data(0,0).toString()));
       for ( int it = 0; it != prg_name.size(); ++it)
       {
           temp = prg_name.at(it);
           paragraphItemList.append(new QTreeWidgetItem((QTreeWidget*)0,
                                                      QStringList(temp)));
           item->addChild(paragraphItemList.at(it));
       }

    }
    if (!paragraphItemList.isEmpty())
    {
        for(int it =0 ;it != paragraphItemList.size(); ++it)
        {
            if (item->child(it)->data(0,0).toString() == paragraphItemList.at(it)->data(0,0).toString())
            {
                   filePath.append(sqlHandler->queryLoadContent(item->data(0,0).toString(),
                                                           item->child(it)->data(0,0).toString()));

            }
        }
    }

}
void TreeWidget::treeContextMenu(QPoint pos)
{
     itemDelete = this->itemAt(pos);

    QAction *deleteItem = new QAction("Удалить",this);
    QAction *refresh = new QAction("Обновить",this);

    connect(refresh,SIGNAL(triggered()),this,SLOT(refreshTree()));
    connect(deleteItem,SIGNAL(triggered()),this,SLOT(DeleteItem()));

    QMenu menu(this);
    menu.addAction(deleteItem);
    menu.addAction(refresh);
    menu.exec(this->mapToGlobal(pos));

}
void TreeWidget::refreshTree()
{
    this->clear();
    this->createTree();
}
void TreeWidget::DeleteItem()
{
    if( itemDelete != nullptr )
    {
        if(itemDelete->parent() != nullptr && itemDelete->childCount() <= 0)
        {
            sqlHandler->queryDeleteFromParagraph(itemDelete->text(0) );

            qDebug()<< itemDelete->text(0) << " delete from paragraph";
        }
        if(itemDelete->parent() != nullptr && itemDelete->childCount() > 0)
        {
            //sqlHandler->queryDeleteFromChapter(itemDelete->text(0));
            qDebug()<< itemDelete->text(0) << " delete from chapter and paragraph";
        }
        if(itemDelete->parent() == nullptr)
        {
            //sqlHandler->queryDeleteFromSubject(itemDelete->text(0));
            qDebug()<< itemDelete->text(0) << " delete from subject, chapter and paragraph";
        }
    }
}
