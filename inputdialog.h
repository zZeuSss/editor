#ifndef INPUTDIALOG_H
#define INPUTDIALOG_H

#include <QWidget>
#include <QLabel>
#include <QBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QDebug>
#include <QEventLoop>
#include <QCloseEvent>
#include <QComboBox>
#include <QDebug>
class InputDialog : public QWidget
{
    Q_OBJECT
public:
    explicit     InputDialog(QWidget *parent = 0);

                 InputDialog(QComboBox* sub_box, QStringList begin_list);
                 InputDialog(QStringList subjects);
                 InputDialog(int){}
                 ~InputDialog();

    QString      DATA;
    QString      data();
    void         wait();
    QString      getEditContent();
    QString      getBoxContent();
private:
    QLineEdit*   edt;
    QLineEdit*   edtSub;
    QComboBox*   box;
    QString      subCurrentItem;
    QStringList  chpt_list;
protected:
    virtual void closeEvent(QCloseEvent *);
    
signals:
  void  finished();

public slots:
    void  ComboBoxItem(QString index);
    void changeData();
    void changeStringData();
};

#endif // INPUTDIALOG_H
