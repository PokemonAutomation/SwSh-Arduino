/*  Right-Side Panel Options
 *
 *  From: https://github.com/Mysticial/Pokemon-Automation-SwSh-Arduino-Scripts
 *
 */

#ifndef PokemonAutomation_RightPanel_H
#define PokemonAutomation_RightPanel_H

#include <QWidget>

class MainWindow;

class RightPanel : public QObject{
    Q_OBJECT

public:
    virtual QWidget* make_ui(MainWindow& parent) = 0;

};


#endif
