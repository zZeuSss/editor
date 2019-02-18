#ifndef TREEWIDGET_H
#define TREEWIDGET_H

#include <QObject>
#include <QTreeWidget>
#include <QStringList>
#include <QAction>
#include <QMenu>
#include <QMessageBox>
#include "sqlcontroller.h"

class TreeWidget : public QTreeWidget
{
    Q_OBJECT
public:
                TreeWidget();
                ~TreeWidget();
    void        createTree(SQLcontroller* sqlCntrlr, QString Direction);

private:
    SQLcontroller*   sqlHandler;
    QStringList      filePath;
    QString          direction;
    void             createTree();
    QTreeWidgetItem* itemDelete;

public slots:
    void        treeItemChange(QTreeWidgetItem* item, int column);
    void        treeContextMenu( const QPoint);
    void        refreshTree();
    void        DeleteItem();

};

#endif // TREEWIDGET_H
