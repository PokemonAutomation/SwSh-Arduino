/*  Pokemon Automation Bot Base Client
 * 
 *  From: https://github.com/Mysticial/Pokemon-Automation-SwSh-Arduino-Scripts
 * 
 */

#include <iostream>
#include "Programs.h"

int main(){
    try{

        //  By default, this program runs the logging program.
        device_logger();

        //  You can also runs programs directly from the computer.
//        program_TurboA();
//        program_ClothingBuyer();
//        program_BallThrower();
//        program_BeamReset();
//        program_FriendDelete();


    }catch (const char* str){
        std::cout << std::endl;
        std::cout << "Exception: " << str << std::endl;
    }catch (const std::string& str){
        std::cout << std::endl;
        std::cout << "Exception: " << str << std::endl;
    }
    std::cout << std::endl;

    system("pause");
}
