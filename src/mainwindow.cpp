#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSize>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QObject::connect(this->ui->buttonFileSymbol, SIGNAL(clicked()), this, SIGNAL(fileSymbolAction()));
    QObject::connect(this->ui->buttonFileHard, SIGNAL(clicked()), this, SIGNAL(fileHardAction()));
    QObject::connect(this->ui->buttonDirSymbol, SIGNAL(clicked()), this, SIGNAL(dirSymbolAction()));
    QObject::connect(this->ui->buttonDirJunction, SIGNAL(clicked()), this, SIGNAL(dirJunctionAction()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::show(QString type)
{
    QMainWindow::show();
    if (type.compare("dir") == 0) {
        this->ui->buttonDirSymbol->show();
        this->ui->buttonDirJunction->show();
        this->ui->buttonFileSymbol->hide();
        this->ui->buttonFileHard->hide();
    } else if (type.compare("file") == 0) {
        this->ui->buttonDirSymbol->hide();
        this->ui->buttonDirJunction->hide();
        this->ui->buttonFileSymbol->show();
        this->ui->buttonFileHard->show();
    } else {
        QApplication::exit(0);
    }
}
