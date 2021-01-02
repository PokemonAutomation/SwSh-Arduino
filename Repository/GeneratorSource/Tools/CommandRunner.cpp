/*  Program from JSON File.
 *
 *  From: https://github.com/Mysticial/Pokemon-Automation-SwSh-Arduino-Scripts
 *
 */

#include <QMessageBox>
#include "Tools/PersistentSettings.h"
#include "Tools.h"


#if _WIN32

void build_hexfile(const std::string& mcu, const std::string& program_name){
    if (system("make -v") != 0){
        QMessageBox box;
        box.critical(nullptr, "Error", "make not found. Please install WinAVR.");
        return;
    }

    std::string cmd;
    cmd += "cmd /c \"";
    cmd += settings.config_path.toUtf8().data();
    cmd += "\\BuildWindows.cmd\" ";
    cmd += mcu + " ";
    cmd += program_name;
//    cmd += " > " + program_name + ".log 2>&1";
//    cout << cmd << endl;
    system(cmd.c_str());
}


#else
#error "Platform not supported."
#endif
