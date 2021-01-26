/*  Persistent Settings
 *
 *  From: https://github.com/Mysticial/Pokemon-Automation-SwSh-Arduino-Scripts
 *
 */

#include <QJsonValue>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDir>
#include "SharedCpp/QtJsonTools.h"
#include "Tools.h"
#include "PersistentSettings.h"

#include <iostream>
using std::cout;
using std::endl;


const QString VERSION = "v0.3.2";
const QString DISCORD = "https://discord.gg/cQ4gWxN";
const QString GITHUB_REPO = "https://github.com/Mysticial/Pokemon-Automation-SwSh-Arduino-Scripts";

const QString SETTINGS_NAME = "Settings.json";
const QString CONFIG_FOLDER_NAME = "GeneratorConfig";
const QString SOURCE_FOLDER_NAME = "DeviceSource";
const QString LOG_FOLDER_NAME = "Logs";


PersistentSettings settings;


void PersistentSettings::determine_paths(){
    path = QCoreApplication::applicationDirPath() + "/";

    for (size_t c = 0; c < 3; c++){
        cout << path.toUtf8().data() << endl;
//        QFileInfo info(path + SETTINGS_NAME);
//        if (info.exists() && info.isFile()){
//            return;
//        }
        QDir basedir(path);

        if (!QDir(path + LOG_FOLDER_NAME).exists()){
            basedir.mkdir(LOG_FOLDER_NAME);
        }
        if (QDir(path + CONFIG_FOLDER_NAME).exists()){
            return;
        }
        path += "../";
    }

    path = "";
//    throw StringException("Unable to find working directory.");
}
void PersistentSettings::load(){
    determine_paths();
    cout << ("Root Path: " + path).toUtf8().data() << endl;

    try{
        QJsonDocument doc = read_json_file(path + SETTINGS_NAME);
        if (!doc.isObject()){
            throw StringException("Invalid settings file.");
        }

        QJsonObject root = doc.object();

        mcu_index = json_get_int(root, "MCU");
        if (mcu_index >= 3){
            mcu_index = 0;
        }

    }catch (const StringException& str){
        std::cout << ("Error Parsing " + SETTINGS_NAME + ": " + str.message).toUtf8().data() << std::endl;
    }
}


void PersistentSettings::write() const{
    QJsonObject root;
    root.insert("MCU", QJsonValue((int)mcu_index));
    write_json_file("Settings.json", QJsonDocument(root));
}

