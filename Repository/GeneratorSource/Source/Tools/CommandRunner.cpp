/*  Build Command Runner
 *
 *  From: https://github.com/Mysticial/Pokemon-Automation-SwSh-Arduino-Scripts
 *
 */

#include <iostream>
#include <Windows.h>
#include <QFile>
#include <QMessageBox>
#include "SharedCpp/Unicode.h"
#include "Tools/PersistentSettings.h"
#include "Tools.h"


#if _WIN32

int build_hexfile(const std::string& mcu, const QString& program_name){
//    if (system("make -v") != 0){
//        QMessageBox box;
//        box.critical(nullptr, "Error", "make not found. Please install WinAVR.");
//        return;
//    }

    QString hex_file = settings.path + program_name + ("-" + mcu + ".hex").c_str();
    QString log_file = settings.path + program_name + ("-" + mcu + ".hex").c_str();

    QFile file(hex_file);
    file.remove();

    using PokemonAutomation::utf8_to_wstr;
    QString module;
    for (auto ch : settings.path + CONFIG_FOLDER_NAME + "/BuildWindows.cmd"){
        module += ch == '/' ? '\\' : ch;
    }

    STARTUPINFOW si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));
    QString command = module + " " + mcu.c_str() + " " + program_name + " > " + log_file + ".log 2>&1";
    bool ret = CreateProcessW(
        nullptr,
        &utf8_to_wstr(command.toUtf8().data())[0],
        nullptr,
        nullptr,
        false,
        CREATE_NO_WINDOW,
        nullptr,
        nullptr,
        &si,
        &pi
    );
    if (!ret){
        ret = GetLastError();
        std::cout << "error = " << ret << std::endl;
        run_on_main_thread([=]{
            QMessageBox box;
            box.critical(nullptr, "Error", "Unable to open: " + module);
        });
        return 1;
    }
    ret = WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    return ret;
}


#else
#error "Platform not supported."
#endif
