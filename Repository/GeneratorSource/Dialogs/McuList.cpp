/*  MCU List
 *
 *  From: https://github.com/Mysticial/Pokemon-Automation-SwSh-Arduino-Scripts
 *
 */

#include <vector>
#include "Tools/PersistentSettings.h"
#include "McuList.h"


const std::vector<std::pair<std::string, QString>> MCU_LIST{
    {"atmega16u2", "atmega16u2 - (Arduino Uno R3)"},
    {"atmega32u4", "atmega32u4 - (Teensy 2.0)"},
    {"at90usb1286", "at90usb1286 - (Teensy++ 2.0)"},
};

McuList::McuList(QWidget& parent)
    : QComboBox(&parent)
{
    for (const auto& item : MCU_LIST){
        addItem(item.second);
    }
    setCurrentIndex(settings.mcu_index);

    connect(
        this, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
        this, [&](int index){ settings.mcu_index = index; }
    );
}

const std::string& McuList::get_MCU() const{
    return MCU_LIST[currentIndex()].first;
}

