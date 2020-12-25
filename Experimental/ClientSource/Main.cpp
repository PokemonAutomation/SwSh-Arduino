/*  Pokemon Automation Bot Base Client
 * 
 *  From: https://github.com/Mysticial/Pokemon-Automation-SwSh-Arduino-Scripts
 * 
 */

#include <ctime>
#include <iostream>
#include "Programs.h"

namespace PokemonAutomation{
    void sandbox(const std::string& device_name);
}


int main(){
    using namespace PokemonAutomation;

    try{

        //  By default, this program runs the logging program.
        device_logger();

        //  You can also run programs directly from the computer.
//        program_TurboA();
//        program_ClothingBuyer();
//        program_BallThrower();
//        program_BeamReset();
//        program_FriendDelete();
//        program_DateSpam_WattFarmer();

//        sandbox("");
    }catch (const char* str){
        std::cout << std::endl;
        std::cout << "Exception: " << str << std::endl;
    }catch (const std::string& str){
        std::cout << std::endl;
        std::cout << "Exception: " << str << std::endl;
    }
    std::cout << std::endl;

#if _WIN32
    system("pause");
#endif
}
