#include "controler.h"

#include <QTextCodec>
#include <QStringList>
#include <QClipboard>
#include <QMessageBox>
#include <QFileInfo>
#include <QProcess>
#include <QDir>
#include <QStringList>

#include "mainwindow.h"
#include "welcomewindow.h"

#include <windows.h>

Controler::Controler(QApplication *app)
{
    this->app = app;

//    QTextCodec *codec = QTextCodec::codecForName("UTF8");
//    QTextCodec::setCodecForLocale(codec);
//    QTextCodec::setCodecForCStrings(codec);
//    QTextCodec::setCodecForTr(codec);
}

int Controler::exec()
{
    QStringList arguments = QApplication::arguments();
    if (arguments.length() == 10) {
        QMessageBox::information(NULL, arguments.at(0), arguments.at(0));
        //        WelcomeWindow *welcomeWindow = new WelcomeWindow();
        //        welcomeWindow->show();
    } else if (arguments.length() == 1){
        QClipboard *clipboard = QApplication::clipboard();
        QString clipStr = clipboard->text();
        qDebug(qPrintable("clipStr: " + clipStr));
        QStringList clipStrList = clipStr.split("file:///");
        for (int i = 0; i < clipStrList.length(); i++) {
            if (clipStrList.at(i).length() == 0) {
                clipStrList.removeAt(i);
            }
        }
        if (clipStrList.length() == 0) {
            return this->exit(tr("不是合法的文件/目录"));
        } else if (clipStrList.length() > 1){
            return this->exit(tr("请每次选择一个目录/文件"));
        }
        QFileInfo *source = new QFileInfo(clipStr.mid(8));
//        QFileInfo *destination = new QFileInfo(arguments.at(1));
        QFileInfo *destination = new QFileInfo(arguments.at(0));
        if (!(source->isDir() || source->isFile())) {
            return this->exit(tr("源文件/目录不存在"));
        }
//        if (destination->exists()) {
//            return this->exit(tr("目标文件/目录已存在"));
//        }

        MainWindow *mainWindow = new MainWindow();
        if (source->isDir()) {
            mainWindow->show("dir");
        } else if (source->isFile()) {
            mainWindow->show("file");
        }
        QObject::connect(mainWindow, SIGNAL(fileSymbolAction()), this, SLOT(fileSymbolAction()));
        QObject::connect(mainWindow, SIGNAL(fileHardAction()), this, SLOT(fileHardAction()));
        QObject::connect(mainWindow, SIGNAL(dirSymbolAction()), this, SLOT(dirSymbolAction()));
        QObject::connect(mainWindow, SIGNAL(dirJunctionAction()), this, SLOT(dirJunctionAction()));

        this->sourcePath = source->absoluteFilePath();
//        this->destinationPath = destination->absoluteFilePath();
        this->destinationPath = QDir::currentPath() + "/" + source->fileName();

    } else {
        return this->exit(NULL);
    }
    return this->app->exec();
}

void Controler::setSourcePath(QString sourcePath)
{
    this->sourcePath = sourcePath;
}

void Controler::setDesinationPath(QString desinationPath)
{
    this->destinationPath = desinationPath;
}

int Controler::exit(QString errString)
{
    if (errString != NULL) {
        QMessageBox::warning(NULL, "Win32Ln Error", errString);
    }
    return 0;
}

QString Controler::getSourcePath()
{
    return this->sourcePath;
}

QString Controler::getDesinationPath()
{
    return this->destinationPath;
}

void Controler::fileSymbolAction()
{
    QString cmd = "cmd.exe";
    QString arg = "/c mklink \""
            + this->destinationPath.replace('/', "\\\\")
            + "\" \"" + this->sourcePath.replace('/', "\\\\")
            + "\"";
    qDebug(qPrintable(arg));
    ShellExecute(NULL, L"runas",(wchar_t*) cmd.utf16(), (wchar_t*) arg.utf16(), NULL, SW_HIDE);
    QApplication::exit(0);
}

void Controler::fileHardAction()
{
    QString cmd = "cmd.exe";
    QString arg = "/c mklink /H \""
            + this->destinationPath.replace('/', "\\\\")
            + "\" \"" + this->sourcePath.replace('/', "\\\\")
            + "\"";
    qDebug(qPrintable(arg));
    ShellExecute(NULL, L"runas",(wchar_t*) cmd.utf16(), (wchar_t*) arg.utf16(), NULL, SW_HIDE);
    QApplication::exit(0);
}

void Controler::dirSymbolAction()
{
    QString cmd = "cmd.exe";
    QString arg = "/c mklink /D \""
            + this->destinationPath.replace('/', "\\\\")
            + "\" \"" + this->sourcePath.replace('/', "\\\\")
            + "\"";
    qDebug(qPrintable(arg));
    ShellExecute(NULL, L"runas",(wchar_t*) cmd.utf16(), (wchar_t*) arg.utf16(), NULL, SW_HIDE);
    QApplication::exit(0);
}

void Controler::dirJunctionAction()
{
    QString cmd = "cmd.exe";
    QString arg = "/c mklink /J \""
            + this->destinationPath.replace('/', "\\\\")
            + "\" \"" + this->sourcePath.replace('/', "\\\\")
            + "\"";
    qDebug(qPrintable(arg));
    ShellExecute(NULL, L"runas",(wchar_t*) cmd.utf16(), (wchar_t*) arg.utf16(), NULL, SW_HIDE);
    QApplication::exit(0);
}
