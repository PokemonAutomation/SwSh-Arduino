
#include <vector>
#include <iostream>
#include <QApplication>
#include "Tools/PersistentSettings.h"
#include "Dialogs/MainWindow.h"

//using std::cout;
//using std::endl;

//#include <QFile>


int main(int argc, char *argv[])
{
#if 0
    FILE* f = fopen("../GeneratorConfig/TurboA.json", "r");
    if (f == nullptr){
        cout << "fopen returned null" << endl;
    }
    fclose(f);

    QFile file("../GeneratorConfig/TurboA.json");
    if (!file.open(QFile::ReadOnly | QIODevice::ExistingOnly)){
        cout << "cannot open file" << endl;
    }
    cout << "size = " << file.size() << endl;
#endif

    try{
        settings.read();
    }catch (...){
    }

    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    int ret = a.exec();
    settings.write();
    return ret;
}
