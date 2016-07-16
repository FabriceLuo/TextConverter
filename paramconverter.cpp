#include "paramconverter.h"
#include <QPlainTextEdit>
#include <QClipboard>
#include <QApplication>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QString>
#include <QStringList>
#include <QKeySequence>
#include <QRegularExpression>

ParamConverter::ParamConverter(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Param Converter");
    setMinimumSize(800, 600);

    mainEdit = new QPlainTextEdit();
    setCentralWidget(mainEdit);

    initMenuBar();
}

ParamConverter::~ParamConverter()
{

}

void ParamConverter::editCopy()
{
    mainEdit->copy();
}

void ParamConverter::editCut()
{
    mainEdit->cut();
}

void ParamConverter::editPaste()
{
    mainEdit->paste();
}

void ParamConverter::showAbout()
{
    QMessageBox::about(this, "About ParamConverter", "A esay converter");
}

void ParamConverter::showAboutQt()
{
    QMessageBox::aboutQt(this, "About Qt");
}

bool ParamConverter::initMenuBar()
{
    mainMenuBar = menuBar();

    //edit menu
    editMenu = new QMenu("Edit");
    copyAction = new QAction("Copy", this);
    copyAction->setShortcut(QKeySequence::Copy);
    connect(copyAction, SIGNAL(triggered()), this, SLOT(editCopy()));

    cutAction  = new QAction("Cut", this);
    cutAction->setShortcut(QKeySequence::Cut);
    connect(cutAction, SIGNAL(triggered()), this, SLOT(editCut()));

    pasteAction  = new QAction("Paste", this);
    pasteAction->setShortcut(QKeySequence::Paste);
    connect(pasteAction, SIGNAL(triggered()), this, SLOT(editPaste()));

    convertAction = new QAction("Convert", this);
    connect(convertAction, SIGNAL(triggered()), this, SLOT(editConvert()));

    editMenu->addAction(copyAction);
    editMenu->addAction(cutAction);
    editMenu->addAction(pasteAction);

    editMenu->addSeparator();
    editMenu->addAction(convertAction);

    helpMenu = new QMenu("Help");

    aboutAction = new QAction("About", this);
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(showAbout()));

    aboutQtAction = new QAction("About Qt", this);
    connect(aboutQtAction, SIGNAL(triggered()), this, SLOT(showAboutQt()));

    helpMenu->addAction(aboutAction);
    helpMenu->addAction(aboutQtAction);

    mainMenuBar->addMenu(editMenu);
    mainMenuBar->addMenu(helpMenu);

    return true;
}

bool ParamConverter::initActions()
{
    return true;
}

void ParamConverter::editConvert()
{
    QString editContent = mainEdit->toPlainText();

    QStringList contentList = editContent.split('\n');
    int stringCount = contentList.size();

    QString tempString;
    QStringList convertedList;
    for(int i = 0;i < stringCount; i++)
    {
        tempString = contentList.at(i);
        if(tempString.length() == 0)
        {
            continue;
        }
        tempString = convertString(tempString);
        convertedList.push_back(tempString);
    }
    tempString = convertedList.join(' ');
    mainEdit->setPlainText(tempString);
}

QString ParamConverter::convertString(QString str)
{
    if(str.isEmpty())
    {
        return str;
    }

    clearSpace(str, 0);
    str.insert(0, '-');
    int indexEnd = str.indexOf(':');
    if(-1 == indexEnd)
    {
        str.clear();
        return str;
    }
    clearSpace(str, indexEnd+1);
    clearRSpace(str, indexEnd - 1);
    clearRSpace(str, str.length() - 1);

    indexEnd = str.indexOf(':');
    str.replace(indexEnd, 1, ' ');
    str.insert(indexEnd+1, '\'');

    str.insert(str.length(), '\'');

    return str;
}

void ParamConverter::clearSpace(QString &str, int from)
{
    while(str.at(from) == ' ')
    {
        str.remove(from, 1);
    }
    return;
}
void ParamConverter::clearRSpace(QString &str, int from)
{
    while(str.at(from) == ' ')
    {
        str.remove(from, 1);
        from--;
    }
    return;
}
