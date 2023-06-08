#include "s21_window.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    S21Window w;
    w.show();
    return a.exec();
}
