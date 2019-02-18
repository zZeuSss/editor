#include "inputdialog.h"
#include "sqlcontroller.h"

InputDialog::InputDialog(QWidget *parent) :
    QWidget(parent)
{
    QBoxLayout*  vlay = new QVBoxLayout;
    QBoxLayout*  hlay  = new QHBoxLayout;
    edtSub = new QLineEdit;
    QLabel* lbl = new QLabel;
    QPushButton* btn = new QPushButton("Отправить");
    QPushButton* CancelBtn = new QPushButton("Отмена");

    connect(btn,SIGNAL(clicked()),this,SLOT(changeStringData()));
    connect(btn,SIGNAL(clicked()),this,SLOT(close()));

    connect(CancelBtn,SIGNAL(clicked()),this,SLOT(close()));

    lbl->setText("Введите название предмета");

    hlay->addWidget(btn);
    hlay->addWidget(CancelBtn);

    vlay->addWidget(lbl);
    vlay->addWidget(edtSub);
    vlay->addLayout(hlay);

    this->setLayout(vlay);
    this->show();
}
InputDialog::InputDialog(QComboBox *sub_box, QStringList begin_list)
{
    box = new QComboBox;
    QBoxLayout*  vlay = new QVBoxLayout;
    QBoxLayout*  hlay  = new QHBoxLayout;
    edt = new QLineEdit;
    QLabel*      subLbl = new QLabel;
    QLabel*      chptLbl = new QLabel;
    QLabel*      edtLbl = new QLabel;
    QPushButton* btn = new QPushButton("Отправить");
    QPushButton* CancelBtn = new QPushButton("Отмена");

    connect(btn,SIGNAL(clicked()),this,SLOT(changeData()));
    connect(btn,SIGNAL(clicked()),this,SLOT(close()));

    connect(CancelBtn,SIGNAL(clicked()),this,SLOT(close()));

    connect(sub_box,SIGNAL(currentIndexChanged(QString)),this,SLOT(ComboBoxItem(QString)));

    box->addItems(begin_list);

    chptLbl->setText("Выберите главу:");
    subLbl->setText("Выберите предмет:");
    edtLbl->setText("Введите имя параграфа:");

    hlay->addWidget(btn);
    hlay->addWidget(CancelBtn);

    vlay->addWidget(subLbl);
    vlay->addWidget(sub_box);
    vlay->addWidget(chptLbl);
    vlay->addWidget(box);
    vlay->addWidget(edtLbl);
    vlay->addWidget(edt);
    vlay->addLayout(hlay);

    this->setLayout(vlay);
    this->show();
}
InputDialog::InputDialog(QStringList subjects)
{
    box = new QComboBox;
    QBoxLayout*  vlay = new QVBoxLayout;
    QBoxLayout*  hlay  = new QHBoxLayout;
    edt = new QLineEdit;
    QLabel*      subLbl = new QLabel;
    QLabel*      edtLbl = new QLabel;
    QPushButton* btn = new QPushButton("Отправить");
    QPushButton* CancelBtn = new QPushButton("Отмена");

    connect(btn,SIGNAL(clicked()),this,SLOT(changeData()));
    connect(btn,SIGNAL(clicked()),this,SLOT(close()));

    connect(CancelBtn,SIGNAL(clicked()),this,SLOT(close()));

    subLbl->setText("Выберите предмет:");
    edtLbl->setText("Введите название главы:");

    hlay->addWidget(btn);
    hlay->addWidget(CancelBtn);

    box->addItems(subjects);
    vlay->addWidget(subLbl);
    vlay->addWidget(box);
    vlay->addWidget(edtLbl);
    vlay->addWidget(edt);
    vlay->addLayout(hlay);

    this->setLayout(vlay);
    this->show();
}
InputDialog::~InputDialog()
{
}
void InputDialog::changeStringData()
{
    DATA = edtSub->text();
}
void InputDialog::changeData()
{
   // strPair->setData(box->currentText(),edt->text());
}
void InputDialog::wait()
{
    QEventLoop loop;
    connect(this,SIGNAL(finished()),&loop,SLOT(quit()));
    loop.exec();
    qDebug()<<"loop end";

}
void InputDialog::closeEvent(QCloseEvent *event)
{
    emit finished();
    event->accept();
}
QString InputDialog::data()
{
    return DATA;
}

void InputDialog::ComboBoxItem(QString index)
{
    box->clear();
    SQLcontroller* sqlHandler = new SQLcontroller(0);
    chpt_list = sqlHandler->queryGetChapter(index);
    box->addItems(chpt_list);
}
QString InputDialog::getEditContent()
{
    return edt->text();
}
QString InputDialog::getBoxContent()
{
    return box->currentText();
}
