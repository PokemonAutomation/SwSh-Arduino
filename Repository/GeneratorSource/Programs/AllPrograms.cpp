/*  List of all Programs
 *
 *  From: https://github.com/Mysticial/Pokemon-Automation-SwSh-Arduino-Scripts
 *
 */

#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include "JsonProgram.h"
#include "Tools/PersistentSettings.h"
#include "AllPrograms.h"

#include <iostream>
using std::cout;
using std::endl;

#if 0
void add_if_not_null(
    std::vector<std::unique_ptr<Program>>& list,
    std::unique_ptr<Program> program
){
    if (program){
        list.emplace_back(std::move(program));
    }
}

void add_if_ok(
    std::vector<std::unique_ptr<Program>>& list,
    const QString& filename
){
    try{
        list.emplace_back(new Program_JsonFile(filename));
    }catch (const char* str){
        QMessageBox box;
        box.warning(nullptr, "Unable to load file: " + filename, str);
    }catch (const QString& str){
        QMessageBox box;
        box.warning(nullptr, "Unable to load file: " + filename, str);
    }
}
#endif


const std::vector<std::unique_ptr<Program>>& PROGRAM_LIST(){
    static std::vector<std::unique_ptr<Program>> list;
    if (!list.empty()){
        return list;
    }

    QFile file;
    do{
        file.setFileName(settings.config_path + "/ProgramList.txt");
        if (file.open(QFile::ReadOnly)){
            break;
        }
        file.setFileName("../" + settings.config_path + "/ProgramList.txt");
        if (file.open(QFile::ReadOnly)){
            settings.config_path = "../" + settings.config_path;
            break;
        }
        QMessageBox box;
        box.critical(nullptr, "Error", "Unable to open program list.");
        return list;
    }while (false);

    QTextStream stream(&file);
    while (!stream.atEnd()){
        QString line = stream.readLine();
        if (line.isEmpty()){
            continue;
        }
        cout << "Open: " << line.toUtf8().data() << endl;
//        add_if_ok(list, settings.config_path + "/" + line + ".json");
        try{
            list.emplace_back(new Program_JsonFile(settings.config_path + "/" + line + ".json"));
        }catch (const char* str){
            cout << "Error: " << str << endl;
        }catch (const QString& str){
            cout << "Error: " << str.toUtf8().data() << endl;
        }
    }
    file.close();

    return list;
}


std::map<QString, Program*> make_program_map(){
    std::map<QString, Program*> map;
#if 1
    for (const auto& program : PROGRAM_LIST()){
        auto ret = map.emplace(program->name(), program.get());
        if (!ret.second){
            throw "Duplicate program name: " + program->name();
        }
    }
#endif
    return map;
}

const std::map<QString, Program*>& PROGRAM_MAP(){
    static std::map<QString, Program*> map = make_program_map();
    return map;
}




