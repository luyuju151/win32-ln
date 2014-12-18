#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#include "controler.h"

#include <QTextCodec>
#include <QStringList>
#include <QClipboard>
#include <QMessageBox>
#include <QFileInfo>
#include <QProcess>
#include <QDir>
#include <QStringList>
#include <QRegularExpression>


#include <QDebug>

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
    int symbolHardFlag=Symol;
    if (arguments.length() == 2)
    {
        QRegularExpression matchHard("[/-]hard");
        if(matchHard.match(arguments.at(1).toLower()).hasMatch())
            symbolHardFlag=Hard;
//        qDebug()<<symbolHardFlag;
    }
    if (arguments.length() >= 1)
    {
        QClipboard *clipboard = QApplication::clipboard();
        
        QString clipStr = clipboard->text();
//        qDebug(qPrintable("clipStr: " + clipStr));
        QStringList clipStrList;
//        qDebug()<<clipStr;
        if(clipStr.contains("file:///"))
        {
            clipStrList = clipStr.replace('\n',"").split("file:///", QString::SkipEmptyParts);
        }
        else //contains ''\n''
        {
            qDebug()<<"has \\n";
            clipStrList = clipStr.replace('"',"").split("\n", QString::SkipEmptyParts);
        }
            
        int clipListLength=clipStrList.length();
        for (int i = 0; i < clipListLength; i++)
        {
            if (clipStrList.at(i).length() == 0)
            {
                clipStrList.removeAt(i);
            }
            
        }
        qDebug()<<"clipStrList: "<< clipStrList;
        
        if (clipListLength == 0)
        {
            return this->exit(tr("不是合法的文件/目录"));
        }
        
//        QFileInfo *destination = new QFileInfo(arguments.at(0));
//        qDebug(qPrintable("arguments.at(0): " + arguments.at(0)));
        QFileInfo source;
        for(int i=0;i<clipListLength;++i)
        {
            source.setFile(clipStrList.at(i));
            if (!(source.isDir() || source.isFile()))
            {
                return this->exit(clipStrList.at(i)+tr("源不存在"));
            }
            
            this->sourcePath = source.absoluteFilePath();
            this->destinationPath = QDir::currentPath() + "/" + source.fileName();
            if(source.isFile())
            {
                if(symbolHardFlag) //hard
                    fileHardAction();
                else
                    fileSymbolAction();
            }
            else
            {
                if(symbolHardFlag) //hard
                    dirJunctionAction();
                else
                    dirSymbolAction();
            }
            
        }

        return this->exit(NULL);
//        if (destination->exists()) {
//            return this->exit(tr("目标文件/目录已存在"));
//        }

        
    }
    else
    {
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
    if (errString != NULL)
    {
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
//    qDebug(qPrintable(arg));
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
//    qDebug(qPrintable(arg));
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
//    qDebug(qPrintable(arg));
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
//    qDebug(qPrintable(arg));
    ShellExecute(NULL, L"runas",(wchar_t*) cmd.utf16(), (wchar_t*) arg.utf16(), NULL, SW_HIDE);
    QApplication::exit(0);
}
