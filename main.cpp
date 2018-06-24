#include "mymovie.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyMovie w;
    w.setStyleSheet("QPushButton{background:transparent;}"
                                "QPushButton:hover{border-radius:5px; border:1px solid rgb(210, 225, 230);}");
    w.show();

    return a.exec();
}
