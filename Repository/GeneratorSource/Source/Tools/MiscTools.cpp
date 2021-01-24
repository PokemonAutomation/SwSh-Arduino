/*  Json Helpers
 *
 *  From: https://github.com/Mysticial/Pokemon-Automation-SwSh-Arduino-Scripts
 *
 */

#include <QString>
#include "SharedCpp/QtJsonTools.h"
#include "Tools.h"

const QString STRING_POKEMON = QString("Pok") + QChar(0xe9) + "mon";




//QJsonObject json_get_object(const QJsonObject& obj, const QString& key);



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
            throw StringException("Invalid code digit.");
        }
        c++;
        if (c > digits){
            throw StringException("Code is too long.");
        }
        ret += ch;
    }
    if (c < digits){
        throw StringException("Code is too short.");
    }
    return ret;
}








