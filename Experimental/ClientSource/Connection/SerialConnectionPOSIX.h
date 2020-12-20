/*  Serial Connection for POSIX
 * 
 *  From: https://github.com/Mysticial/Pokemon-Automation-SwSh-Arduino-Scripts
 * 
 */

#ifndef PokemonAutomation_SerialConnectionPOSIX_H
#define PokemonAutomation_SerialConnectionPOSIX_H

#pragma warning "This file has not been tested like at all. :("

#include <string>
#include <atomic>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include "StreamInterface.h"

namespace PokemonAutomation{

class SerialConnection : public StreamConnection{
public:
    //  UTF-8
    SerialConnection(const std::string& name, uint32_t baud_rate)
        : m_exit(false)
    {
        speed_t baud = B9600;
        switch (baud_rate){
        case 9600:  baud = B9600;   break;
        case 19200: baud = B19200;  break;
        case 38400: baud = B38400;  break;
        case 57600: baud = B57600;  break;
        case 115200: baud = B115200;break;
        default:
            throw "Unsupported Baud Rate: " + std::to_string(baud_rate);
        }

        m_fd = open(name.c_str(), O_RDWR | O_NOCTTY | O_NDELAY);
        if (m_fd == -1){
            int error = errno;
            throw "Unable to open serial connection. Error = " + std::to_string(error);
        }

        struct termios options;
        if (tcgetattr(m_fd, &options) == -1){
            int error = errno;
            throw "tcgetattr() failed. Error = " + std::to_string(error);
        }

        //  Baud Rate
        cfsetispeed(&options, baud);
        cfsetospeed(&options, baud);

        //  Byte Size
        options.c_cflag &= ~CSIZE;
        options.c_cflag |= CS8;

        //  No Parity
        options.c_cflag &= ~PARENB
        options.c_cflag &= ~CSTOPB
        options.c_cflag &= ~CSIZE;
        options.c_cflag |= CS8;

        tcsetattr(m_fd, TCSANOW, &options);

        if (tcgetattr(m_fd, &options) == -1){
            int error = errno;
            throw "tcgetattr() failed. Error = " + std::to_string(error);
        }
        if (cfgetispeed(&options) != baud){
            throw "Unable to set baud rate.";
        }
        if (cfgetospeed(&options) != baud){
            throw "Unable to set baud rate.";
        }

        //  Start receiver thread.
        try{
            m_listener = std::thread(&SerialConnection::recv_loop, this);
        }catch (...){
            close(m_fd);
        }
    }

    ~SerialConnection(){
        if (!m_exit.load(std::memory_order_acquire)){
            stop();
        }
    }

    virtual void stop() final{
        m_exit.store(true, std::memory_order_release);
        close(m_fd);
        m_listener.join();
    }

private:
    virtual void send(const void* data, size_t bytes){
        std::lock_guard<std::mutex> lg(m_send_lock);
        write(m_fd, data, bytes);
    }

    void recv_loop(){
        char buffer[32];
        while (!m_exit.load(std::memory_order_acquire)){
            int actual = read(m_fd, buffer, sizeof(buffer));
            if (actual > 0){
                on_recv(buffer, actual);
            }
        }
    }
    


private:
    int m_fd;
    std::atomic<bool> m_exit;
    std::mutex m_send_lock;
    std::thread m_listener;
};


}

#endif
