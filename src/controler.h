#ifndef CONTROLER_H
#define CONTROLER_H

#include <QObject>
#include <QApplication>

class Controler : public QObject
{
    Q_OBJECT
public:
    explicit Controler(QApplication *app);
    int exec();

private:
    QApplication *app;
    QString sourcePath;
    QString destinationPath;

protected:
    void setSourcePath(QString sourcePath);
    void setDesinationPath(QString desinationPath);
    static int exit(QString errString);

public:
    QString getSourcePath();
    QString getDesinationPath();
    
signals:
    
public slots:
    void fileSymbolAction();
    void fileHardAction();
    void dirSymbolAction();
    void dirJunctionAction();

};

#endif // CONTROLER_H
