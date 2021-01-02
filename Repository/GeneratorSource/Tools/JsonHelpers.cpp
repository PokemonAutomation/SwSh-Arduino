/*  Json Helpers
 *
 *  From: https://github.com/Mysticial/Pokemon-Automation-SwSh-Arduino-Scripts
 *
 */

#include <QString>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>
#include "Tools.h"

const QString STRING_POKEMON = QString("Pok") + QChar(0xe9) + "mon";

QJsonDocument read_json_file(const QString& path){
    QFile file(path);
    if (!file.open(QFile::ReadOnly)){
        throw "Unable to open file: " + path;
    }
//    auto data = file.readAll();
//    return QJsonDocument::fromJson(data);
    return QJsonDocument::fromJson(file.readAll());
}
void write_json_file(const QString& path, const QJsonDocument& json){
    std::string json_raw = json.toJson().toStdString();
    std::string json_out = "\xef\xbb\xbf";
    //  Convert to CRLF.
    char previous = 0;
    for (char ch : json_raw){
        if (ch == '\n' && previous != '\r'){
            json_out += '\r';
        }
        json_out += ch;
        previous = ch;
    }

    QFile file(path);
    if (!file.open(QFile::WriteOnly)){
        throw "Unable to create settings file.";
    }
    if (file.write(json_out.c_str(), json_out.size()) != json_out.size()){
        throw "Unable to write settings file.";
    }
    file.close();
}


int json_cast_int(const QJsonValue& value){
    if (!value.isDouble()){
        throw "Config Error - Expected a number.";
    }
    return value.toInt();
}
QString json_cast_string(const QJsonValue& value){
    if (!value.isString()){
        throw "Config Error - Expected a string.";
    }
    return value.toString();
}
QJsonObject json_cast_object(const QJsonValue& value){
    if (!value.isObject()){
        throw "Config Error - Expected an object.";
    }
    return value.toObject();
}

bool json_get_bool(const QJsonObject& obj, const QString& key){
    auto iter = obj.find(key);
    if (iter == obj.end()){
        throw "Config Error - Key not found: " + key;
    }
    if (!iter->isBool()){
        throw "Config Error - Expected a boolean: " + key;
    }
    return iter->toBool();
}
int json_get_int(const QJsonObject& obj, const QString& key){
    auto iter = obj.find(key);
    if (iter == obj.end()){
        throw "Config Error - Key not found: " + key;
    }
    if (!iter->isDouble()){
        throw "Config Error - Expected a number: " + key;
    }
    return iter->toInt();
}
double json_get_double(const QJsonObject& obj, const QString& key){
    auto iter = obj.find(key);
    if (iter == obj.end()){
        throw "Config Error - Key not found: " + key;
    }
    if (!iter->isDouble()){
        throw "Config Error - Expected a number: " + key;
    }
    return iter->toDouble();
}
QString json_get_string(const QJsonObject& obj, const QString& key){
    auto iter = obj.find(key);
    if (iter == obj.end()){
        throw "Config Error - Key not found: " + key;
    }
    if (!iter->isString()){
        throw "Config Error - Expected a string: " + key;
    }
    return iter->toString();
}
QJsonArray json_get_array(const QJsonObject& obj, const QString& key){
    auto iter = obj.find(key);
    if (iter == obj.end()){
        throw "Config Error - Key not found: " + key;
    }
    if (!iter->isArray()){
        throw "Config Error - Expected an array: " + key;
    }
    return iter->toArray();
}
//QJsonObject json_get_object(const QJsonObject& obj, const QString& key);

bool valid_switch_date(const QDate& date){
    if (date < QDate(2000, 1, 1)){
        return false;
    }
    if (date > QDate(2060, 12, 31)){
        return false;
    }
    return true;
}
QJsonArray json_write_date(const QDate& date){
    QJsonArray array;
    array += date.year();
    array += date.month();
    array += date.day();
    return array;
}
QDate json_get_date(const QJsonObject& obj, const QString& key){
    QJsonArray array = json_get_array(obj, key);
    if (array.size() != 3){
        throw "Config Error - Date should be 3 elements: " + key;
    }
    int year = json_cast_int(array[0]);
    int month = json_cast_int(array[1]);
    int day = json_cast_int(array[2]);
    QDate date(year, month, day);
    if (!date.isValid()){
        throw "Config Error - Invalid Date: " + key;
    }
    if (!valid_switch_date(date)){
        throw "Config Error - Invalid Switch Date: " + key;
    }
    return date;
}


//#include <iostream>
//using namespace std;

bool validate_code(size_t digits, const QString& code){
    if (code.isEmpty()){
        return true;
    }
    size_t c = 0;
    for (const auto& ch : code){
        if (ch == ' ' || ch == '-'){
            continue;
        }
        if (ch < '0'){
            return false;
        }
        if (ch > '9'){
            return false;
        }
        c++;
        if (c > digits){
            return false;
        }
    }
    return c == digits;
}

QString sanitize_code(size_t digits, const QString& code){
    QString ret;
    size_t c = 0;
    for (const auto& ch : code){
        if (ch == ' ' || ch == '-'){
            continue;
        }
        if (ch < '0' || ch > '9'){
            throw "Invalid code digit.";
        }
        c++;
        if (c > digits){
            throw "Code is too long.";
        }
        ret += ch;
    }
    if (c < digits){
        throw "Code is too short.";
    }
    return ret;
}








