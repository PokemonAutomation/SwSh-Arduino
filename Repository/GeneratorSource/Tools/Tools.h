/*  Various Utilities
 *
 *  From: https://github.com/Mysticial/Pokemon-Automation-SwSh-Arduino-Scripts
 *
 */

#ifndef PokemonAutomation_Tools_H
#define PokemonAutomation_Tools_H

#include <stdint.h>
#include <string>
#include <map>
#include <QDate>
#include <QJsonObject>
#include <QJsonDocument>

extern const QString STRING_POKEMON;


//  Expression Evaluator
uint32_t parse_ticks_i32(const QString& expression);


//  Json
QJsonDocument read_json_file(const QString& path);
void write_json_file(const QString& path, const QJsonDocument& json);

int json_cast_int(const QJsonValue& value);
QString json_cast_string(const QJsonValue& value);
QJsonObject json_cast_object(const QJsonValue& value);

bool json_get_bool(const QJsonObject& obj, const QString& key);
int json_get_int(const QJsonObject& obj, const QString& key);
double json_get_double(const QJsonObject& obj, const QString& key);
QString json_get_string(const QJsonObject& obj, const QString& key);
QJsonArray json_get_array(const QJsonObject& obj, const QString& key);
QJsonObject json_get_object(const QJsonObject& obj, const QString& key);

bool valid_switch_date(const QDate& date);
QJsonArray json_write_date(const QDate& date);
QDate json_get_date(const QJsonObject& obj, const QString& key);

bool validate_code(size_t digits, const QString& code);
QString sanitize_code(size_t digits, const QString& code);


//  Build the .hex

void build_hexfile(const std::string& mcu, const std::string& program_name);

#endif
