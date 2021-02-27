/*  Pokemon Sword & Shield Arduino Programs
 * 
 *  From: https://github.com/Mysticial/Pokemon-Automation-SwSh-Arduino-Scripts
 * 
 */

//
//  This is a template making your own program. The example here is a copy/paste
//  of the TurboA program. Feel free to modify accordingly.
//
//  Every program that is fully integrated into the package has 4 files:
//      1.  DeviceSource/PokemonSwShPrograms/ProgramName.h
//      2.  DeviceSource/ProgramName.c
//      3.  DeviceSource/ProgramName_Core.c
//      4.  GeneratorConfig/ProgramName.json
//
//  The program is then referenced by the following files/scripts:
//      1.  DeviceSource/Scripts/BuildAll.cmd
//      2.  DeviceSource/Scripts/BuildAllUnix.sh
//      3.  GeneratorConfig/ProgramList.txt
//
//  Thus to add a new program, you must edit all of the above.
//

#include "Common/SwitchFramework/FrameworkSettings.h"
#include "Common/SwitchFramework/PushButtons.h"
#include "Common/PokemonSwSh/PokemonSettings.h"
#include "Common/PokemonSwSh/PokemonProgramIDs.h"
#include "DeviceSource/DeviceFramework/DeviceSettings.h"
#include "DeviceSource/PokemonSwShPrograms/CustomProgram.h"


int main(void){
    //  Do not delete these two lines!
    start_program_callback();
    initialize_framework(PABB_PID_CUSTOM_PROGRAM);

    //  Start the program in the grip menu. Then go home.
    start_program_flash(CONNECT_CONTROLLER_DELAY);
    grip_menu_connect_go_home();

    //  Enter the game.
    pbf_press_button(BUTTON_HOME, 10, HOME_TO_GAME_DELAY);

    //  Turbo A forever...
    while (true){
        pbf_press_button(BUTTON_A, 5, 5);
    }

    //  Not really relevant here, but for programs that finish, go to
    //  Switch home to idle.
    pbf_press_button(BUTTON_HOME, 10, GAME_TO_HOME_DELAY_SAFE);
    end_program_callback();
    end_program_loop();
};

