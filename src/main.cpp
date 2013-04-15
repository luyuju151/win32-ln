#include <QApplication>
#include "controler.h"

int main(int argc, char *argv[])
{
    QApplication *app = new QApplication(argc, argv);
    Controler *controler = new Controler(app);
    return controler->exec();
}
