/*  Friend Delete
 * 
 *  From: https://github.com/Mysticial/Pokemon-Automation-SwSh-Arduino-Scripts
 * 
 *  This program is identical to FriendDelete in the Arduino programs.
 *  Please follow the same start instructions.
 * 
 */

#include <iostream>
#include "CommonFramework/FrameworkSettings.h"
#include "CommonFramework/PushButtons.h"
#include "CommonPokemon/PokemonSettings.h"
#include "CommonPokemon/PokemonRoutines.h"
#include "Libraries/Utilities.h"

namespace PokemonAutomation{



//  Set to a large number to delete all friends.
const uint16_t FRIENDS_TO_DELETE    =   3;

//  Instead of deleting friends, block them.
const bool BLOCK_FRIENDS            =   false;

//  Timings: You may need to increase if your internet is slow.
const uint16_t VIEW_FRIEND_DELAY    =   2 * TICKS_PER_SECOND;   //  Delay from opening a friend to when you can press buttons.
const uint16_t DELETE_FRIEND_DELAY  =   4 * TICKS_PER_SECOND;   //  Delay to delete the friend.
const uint16_t FINISH_DELETE_DELAY  =   2 * TICKS_PER_SECOND;   //  Delay after deleting a friend.



void program_FriendDelete(const std::string& device_name){
    std::cout << "Starting PABotBase - FriendDelete..." << std::endl;
    std::cout << std::endl;
    std::unique_ptr<PABotBase> pabotbase = start_connection(true, device_name);
    global_connection = pabotbase.get();

    std::cout << "Begin Message Logging..." << std::endl;
    MessageLogger logger;
    pabotbase->add_message_snooper(logger);


    //  Start Program
    start_program_flash(CONNECT_CONTROLLER_DELAY);
    pbf_press_button(BUTTON_A, 5, 5);

    for (uint16_t c = 0; c < FRIENDS_TO_DELETE; c++){
        pbf_press_button(BUTTON_A, 5, VIEW_FRIEND_DELAY);       //  View friend
        pbf_press_dpad(DPAD_DOWN, 5, 5);
        pbf_press_button(BUTTON_A, 10, 90);                     //  Click on Options
        if (BLOCK_FRIENDS){
            pbf_press_dpad(DPAD_DOWN, 5, 5);
        }
        pbf_press_button(BUTTON_A, 10, 90);                     //  Click on Remove/Block Friend
        if (BLOCK_FRIENDS){
            pbf_press_button(BUTTON_A, 5, VIEW_FRIEND_DELAY);   //  Confirm 
        }
        pbf_press_button(BUTTON_A, 5, DELETE_FRIEND_DELAY);     //  Confirm 
        pbf_press_button(BUTTON_A, 5, FINISH_DELETE_DELAY);     //  Finish delete friend.
    }

    end_program_callback();
    end_program_loop();
}


}
