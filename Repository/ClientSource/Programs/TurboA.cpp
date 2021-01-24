/*  Turbo A
 * 
 *  From: https://github.com/Mysticial/Pokemon-Automation-SwSh-Arduino-Scripts
 * 
 *  This program is identical to TurboA in the Arduino programs.
 *  Please follow the same start instructions.
 * 
 */

#include <iostream>
#include "ClientSource/CommonFramework/FrameworkSettings.h"
#include "ClientSource/CommonFramework/PushButtons.h"
#include "ClientSource/CommonPokemon/PokemonSettings.h"
#include "ClientSource/CommonPokemon/PokemonRoutines.h"
#include "ClientSource/Libraries/Utilities.h"

namespace PokemonAutomation{


void program_TurboA(const std::string& device_name){
    std::cout << "Starting PABotBase - TurboA..." << std::endl;
    std::cout << std::endl;
    std::unique_ptr<PABotBase> pabotbase = start_connection(true, device_name);
    global_connection = pabotbase.get();

    std::cout << "Begin Message Logging..." << std::endl;
    MessageLogger logger;
    pabotbase->set_sniffer(&logger);


    //  Start Program
    start_program_flash(CONNECT_CONTROLLER_DELAY);
    grip_menu_connect_go_home();
    resume_game_no_interact(TOLERATE_SYSTEM_UPDATE_MENU_FAST);

    while (true){
        pbf_press_button(BUTTON_A, 5, 5);
    }
}


}
