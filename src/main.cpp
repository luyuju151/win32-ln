#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

#include <QApplication>
#include "controler.h"

int main(int argc, char *argv[])
{
    QApplication *app = new QApplication(argc, argv);
    Controler *controler = new Controler(app);
    return controler->exec();
}
