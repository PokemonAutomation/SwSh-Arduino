/*  MCU List
 *
 *  From: https://github.com/Mysticial/Pokemon-Automation-SwSh-Arduino-Scripts
 *
 */

#ifndef PokemonAutomation_McuList_H
#define PokemonAutomation_McuList_H

#include <QComboBox>


class McuList : public QComboBox{
public:
    McuList(QWidget& parent);
    const std::string& get_MCU() const;
private:
};


#endif
