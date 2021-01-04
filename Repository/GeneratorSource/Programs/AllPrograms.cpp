/*  List of all Programs
 *
 *  From: https://github.com/Mysticial/Pokemon-Automation-SwSh-Arduino-Scripts
 *
 */

#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include "JsonSettings.h"
#include "JsonProgram.h"
#include "Tools/PersistentSettings.h"
#include "AllPrograms.h"

#include <iostream>
using std::cout;
using std::endl;



const std::vector<std::unique_ptr<ConfigSet>>& SETTINGS_LIST(){
    static std::vector<std::unique_ptr<ConfigSet>> list;
    if (!list.empty()){
        return list;
    }

    QFile file;
    do{
        file.setFileName(settings.config_path + "/SettingsList.txt");
        if (file.open(QFile::ReadOnly)){
            break;
        }
        file.setFileName("../" + settings.config_path + "/SettingsList.txt");
        if (file.open(QFile::ReadOnly)){
            settings.config_path = "../" + settings.config_path;
            break;
        }
        QMessageBox box;
        box.critical(nullptr, "Error", "Unable to open settings list.");
        return list;
    }while (false);

    QTextStream stream(&file);
    while (!stream.atEnd()){
        QString line = stream.readLine();
        if (line.isEmpty()){
            continue;
        }
        cout << "Open: " << line.toUtf8().data() << endl;
        try{
            list.emplace_back(new Settings_JsonFile(settings.config_path + "/" + line + ".json"));
        }catch (const char* str){
            cout << "Error: " << str << endl;
        }catch (const QString& str){
            cout << "Error: " << str.toUtf8().data() << endl;
        }
    }
    file.close();

    return list;
}
const std::map<QString, ConfigSet*>& SETTINGS_MAP(){
    static std::map<QString, ConfigSet*> map;
    if (map.empty()){
        for (const auto& program : SETTINGS_LIST()){
            auto ret = map.emplace(program->name(), program.get());
            if (!ret.second){
                throw "Duplicate program name: " + program->name();
            }
        }
    }
    return map;
}


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
const std::map<QString, Program*>& PROGRAM_MAP(){
    static std::map<QString, Program*> map;
    if (map.empty()){
        for (const auto& program : PROGRAM_LIST()){
            auto ret = map.emplace(program->name(), program.get());
            if (!ret.second){
                throw "Duplicate program name: " + program->name();
            }
        }
    }
    return map;
}




