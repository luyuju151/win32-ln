#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void show(QString type);

public slots:

signals:
    void fileSymbolAction();
    void fileHardAction();
    void dirSymbolAction();
    void dirJunctionAction();

    
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
