/*  Various Utilities
 *
 *  From: https://github.com/Mysticial/Pokemon-Automation-SwSh-Arduino-Scripts
 *
 */

#ifndef PokemonAutomation_Tools_H
#define PokemonAutomation_Tools_H

#include <stdint.h>
#include <memory>
#include <string>
#include <map>
#include <QApplication>
#include <QDate>
#include <QJsonObject>
#include <QJsonDocument>

extern const QString STRING_POKEMON;


//  Expression Evaluator
uint32_t parse_ticks_i32(const QString& expression);


//  Json



bool valid_switch_date(const QDate& date);

bool validate_code(size_t digits, const QString& code);
QString sanitize_code(size_t digits, const QString& code);


//  Build the .hex

int build_hexfile(const std::string& mcu, const QString& program_name);



extern std::unique_ptr<QApplication> application;

template <typename Lambda>
void run_on_main_thread(Lambda&& lambda){
    QMetaObject::invokeMethod(application.get(), std::move(lambda));
}


#endif
