/*  Persistent Settings
 *
 *  From: https://github.com/Mysticial/Pokemon-Automation-SwSh-Arduino-Scripts
 *
 */

#include <QJsonValue>
#include <QJsonObject>
#include <QJsonDocument>
#include "Tools.h"
#include "PersistentSettings.h"

PersistentSettings settings;


void PersistentSettings::write() const{
    QJsonObject root;
    root.insert("ConfigPath", QJsonValue(config_path));
    root.insert("SourcePath", QJsonValue(source_path));
    root.insert("MCU", QJsonValue((int)mcu_index));
    write_json_file("Settings.json", QJsonDocument(root));
}
void PersistentSettings::read(){
    QJsonDocument doc = read_json_file("Settings.json");
    if (!doc.isObject()){
        throw "Invalid settings file.";
    }
    QJsonObject root = doc.object();
    config_path = json_get_string(root, "ConfigPath");
    source_path = json_get_string(root, "SourcePath");
    mcu_index = json_get_int(root, "MCU");
    if (mcu_index >= 3){
        mcu_index = 0;
    }

}

