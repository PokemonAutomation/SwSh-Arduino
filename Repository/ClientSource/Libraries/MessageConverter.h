/*  Message Pretty Printing
 * 
 *  From: https://github.com/Mysticial/Pokemon-Automation-SwSh-Arduino-Scripts
 * 
 */

#include <string>

namespace PokemonAutomation{


using MessageConverter = std::string (*)(const char* message, size_t length);
void register_message_converter(uint8_t type, MessageConverter converter);

std::string message_to_string(uint8_t type, const std::string& message);
std::string message_to_string(uint8_t type, const char* message, size_t length);


std::string program_name(uint8_t id);


}

