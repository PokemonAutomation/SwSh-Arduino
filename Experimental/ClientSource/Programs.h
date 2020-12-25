/*  Sample Programs
 * 
 *  From: https://github.com/Mysticial/Pokemon-Automation-SwSh-Arduino-Scripts
 * 
 */

#ifndef PokemonAutomation_SamplePrograms_H
#define PokemonAutomation_SamplePrograms_H

#include <memory>
#include "Connection/PABotBase.h"

namespace PokemonAutomation{


//  Helpers
std::unique_ptr<PABotBase> start_connection(
    bool require_pabotbase,
    const std::string& device_name = "",
    MessageLogger* logger = nullptr
);


//  Device Logger
void device_logger          (const std::string& device_name = "");


//  Programs
void program_TurboA             (const std::string& device_name = "");
void program_ClothingBuyer      (const std::string& device_name = "");
void program_BallThrower        (const std::string& device_name = "");
void program_BeamReset          (const std::string& device_name = "");
void program_FriendDelete       (const std::string& device_name = "");
void program_DateSpam_WattFarmer(const std::string& device_name = "");


}

#endif
