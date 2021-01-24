/*  Utilities
 * 
 *  From: https://github.com/Mysticial/Pokemon-Automation-SwSh-Arduino-Scripts
 * 
 */

#include <memory>
#include "ClientSource/Connection/PABotBase.h"

namespace PokemonAutomation{


//  Helpers
std::unique_ptr<PABotBase> start_connection(
    bool require_pabotbase,
    const std::string& device_name = "",
    MessageLogger* logger = nullptr
);



}
