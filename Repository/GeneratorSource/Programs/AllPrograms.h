/*  List of all Programs
 *
 *  From: https://github.com/Mysticial/Pokemon-Automation-SwSh-Arduino-Scripts
 *
 */

#ifndef PokemonAutomation_AllPrograms_H
#define PokemonAutomation_AllPrograms_H

#include <memory>
#include <vector>
#include <map>
#include "Program.h"


extern const std::vector<std::unique_ptr<Program>>& PROGRAM_LIST();
extern const std::map<QString, Program*>& PROGRAM_MAP();


#endif
