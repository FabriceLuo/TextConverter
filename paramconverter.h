#ifndef PARAMCONVERTER_H
#define PARAMCONVERTER_H

#include <QMainWindow>

class QPlainTextEdit;
class QAction;
class QMenuBar;
class QMenu;

class ParamConverter : public QMainWindow
{
    Q_OBJECT

private:
    QPlainTextEdit *mainEdit;

    QMenuBar *mainMenuBar;

    QMenu *editMenu;
    QAction *copyAction;
    QAction *cutAction;
    QAction *pasteAction;
    QAction *convertAction;

    QMenu *helpMenu;
    QAction *aboutAction;
    QAction *aboutQtAction;

    bool initMenuBar();
    bool initActions();
    void clearSpace(QString &str, int from);
    void clearRSpace(QString &str, int from);

private slots:
    //edit menu
    void editCopy();
    void editCut();
    void editPaste();

    void editConvert();


    //help menu
    void showAboutQt();
    void showAbout();

protected:
     QString convertString(QString str);

public:
    ParamConverter(QWidget *parent = 0);
    ~ParamConverter();
};

#endif // PARAMCONVERTER_H
