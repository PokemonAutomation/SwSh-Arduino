/*  Serial Connection for Windows
 * 
 *  From: https://github.com/Mysticial/Pokemon-Automation-SwSh-Arduino-Scripts
 * 
 */

#ifndef PokemonAutomation_SerialConnectionWinAPI_H
#define PokemonAutomation_SerialConnectionWinAPI_H

#include <string>
#include <atomic>
#include <thread>
#include <windows.h>
#include "Common/Clientside/Unicode.h"
#include "ClientSource/Libraries/Logging.h"
#include "StreamInterface.h"

namespace PokemonAutomation{

class SerialConnection : public StreamConnection{
public:
    //  UTF-8
    SerialConnection(const std::string& name, uint32_t baud_rate)
        : SerialConnection(utf8_to_wstr(name), baud_rate)
    {}
    SerialConnection(const std::wstring& name, uint32_t baud_rate)
        : m_exit(false)
    {
        m_handle = CreateFileW(
            (L"\\\\.\\" + name).c_str(),
            GENERIC_READ | GENERIC_WRITE,
            0, 0,
            OPEN_EXISTING,
            FILE_ATTRIBUTE_NORMAL,
            0
        );
        if (m_handle == INVALID_HANDLE_VALUE){
            DWORD error = GetLastError();
            throw "Unable to open serial connection. Error = " + std::to_string(error);
        }

        DCB serial_params{0};
        serial_params.DCBlength = sizeof(serial_params);

        if (!GetCommState(m_handle, &serial_params)){
            DWORD error = GetLastError();
            CloseHandle(m_handle);
            throw "GetCommState() failed. Error = " + std::to_string(error);
        }
//        cout << "BaudRate = " << (int)serial_params.BaudRate << endl;
//        cout << "ByteSize = " << (int)serial_params.ByteSize << endl;
//        cout << "StopBits = " << (int)serial_params.StopBits << "0 means 1 bit" << endl;
//        cout << "Parity   = " << (int)serial_params.Parity << endl;
        serial_params.BaudRate = baud_rate;
        serial_params.ByteSize = 8;
        serial_params.StopBits = 0;
        serial_params.Parity = 0;
        if (!SetCommState(m_handle, &serial_params)){
            DWORD error = GetLastError();
            CloseHandle(m_handle);
            throw "SetCommState() failed. Error = " + std::to_string(error);
        }

#if 1
        COMMTIMEOUTS timeouts{0};
        if (!GetCommTimeouts(m_handle, &timeouts)){
            DWORD error = GetLastError();
            CloseHandle(m_handle);
            throw "GetCommTimeouts() failed. Error = " + std::to_string(error);
        }

//        std::cout << "ReadIntervalTimeout = " << timeouts.ReadIntervalTimeout << std::endl;
//        std::cout << "ReadTotalTimeoutMultiplier = " << timeouts.ReadTotalTimeoutMultiplier << std::endl;
//        std::cout << "ReadTotalTimeoutConstant = " << timeouts.ReadTotalTimeoutConstant << std::endl;

        //  Need to set a read timer. In some cases, a pending ReadFile() call
        //  will block a WriteFile() call until it returns - leading to a
        //  deadlock if the device isn't sending any information.
        timeouts.ReadIntervalTimeout = 0;
        timeouts.ReadTotalTimeoutMultiplier = 0;
        timeouts.ReadTotalTimeoutConstant = 1;

        if (!SetCommTimeouts(m_handle, &timeouts)){
            DWORD error = GetLastError();
            CloseHandle(m_handle);
            throw "SetCommTimeouts() failed. Error = " + std::to_string(error);
        }
#endif

        //  Start receiver thread.
        try{
            m_listener = std::thread(&SerialConnection::recv_loop, this);
        }catch (...){
            CloseHandle(m_handle);
        }
    }
    ~SerialConnection(){
        if (!m_exit.load(std::memory_order_acquire)){
            stop();
        }
    }

    virtual void stop() final{
        m_exit.store(true, std::memory_order_release);
        CloseHandle(m_handle);
        m_listener.join();
    }

private:
    void clear_error(){
        DWORD comm_error;
        if (ClearCommError(m_handle, &comm_error, nullptr) == 0){
            DWORD error = GetLastError();
            log("ClearCommError() failed. Error = " + std::to_string(error));
        }
        log("ClearCommError error flag = " + std::to_string(comm_error));
    }


    virtual void send(const void* data, size_t bytes){
        std::lock_guard<std::mutex> lg(m_send_lock);
#if 0
        for (size_t c = 0; c < bytes; c++){
            std::cout << "Send: " << (int)((const char*)data)[c] << std::endl;
        }
#endif

        DWORD written;
        if (WriteFile(m_handle, data, (DWORD)bytes, &written, nullptr) == 0 || bytes != written){
            DWORD error = GetLastError();
            log(
                "Failed to write: " + std::to_string(written) +
                " / " + std::to_string(bytes) +
                ", error = " + std::to_string(error)
            );
            clear_error();
        }

//        std::cout << "end send()" << std::endl;
    }

    void recv_loop(){
//        std::lock_guard<std::mutex> lg(m_send_lock);
        char buffer[32];
        while (!m_exit.load(std::memory_order_acquire)){
            DWORD read;
            if (ReadFile(m_handle, buffer, 32, &read, nullptr) == 0){
                DWORD error = GetLastError();
                log("ReadFile() failed. Error = " + std::to_string(error));
                clear_error();
            }
//            std::cout << "read = " << read << std::endl;
#if 0
            for (size_t c = 0; c < read; c++){
                cout << "Recv: " << (int)buffer[c] << endl;
            }
#endif
            if (read != 0){
                on_recv(buffer, read);
            }
        }
    }

private:
    HANDLE m_handle;
    std::atomic<bool> m_exit;
    std::mutex m_send_lock;
    std::thread m_listener;
};



}

#endif
