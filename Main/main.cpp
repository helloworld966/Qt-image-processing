#include "Login_window.h"
#include <QtWidgets/QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Login_window w;
    w.show();
    return a.exec();
}
